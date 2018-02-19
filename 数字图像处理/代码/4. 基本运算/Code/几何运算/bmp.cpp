#include "stdafx.h"
#include "math.h"

BITMAPINFO* lpBitsInfo = NULL;

BOOL LoadBmpFile(char* BmpFileName)
{
	FILE* fp;
	if (NULL == (fp = fopen(BmpFileName,"rb")))
		return FALSE;

	BITMAPFILEHEADER bf;  //文件头结构
	BITMAPINFOHEADER bi;  //信息头结构

	//将文件头BITMAPFILEHEADER结构从文件中读出，填写到bf中
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);

	//将信息头BITMAPINFOHEADER结构从文件中读出，填写到bi中
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);

	//计算图像中每一行像素共占多少字节
	DWORD LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

	//计算实际图象数据占用的字节数
	DWORD ImgSize = LineBytes * bi.biHeight;

	DWORD NumColors;//实际用到的颜色数，即调色板数组中的颜色个数
	if (bi.biClrUsed != 0)
		NumColors = bi.biClrUsed; //如果bi.biClrUsed不为零，就是本图象实际用到的颜色数
	else {
		switch(bi.biBitCount) {
		case 1:
			NumColors = 2;
			break;
		case 4:
			NumColors = 16;
			break;
		case 8:
			NumColors = 256;
			break;
		case 24:
			NumColors = 0; //对于真彩色图，没用到调色板
			break;
		}
	}

	//仅处理256色图像
	if (NumColors != 256) 
	{
		fclose(fp);
		AfxMessageBox("不是256色图像!");
		return FALSE;
	}

	//分配内存，大小为BITMAPINFOHEADER结构长度+调色板+实际位图数据
	LONG size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;

	//文件指针重新定位到BITMAPINFOHEADER开始处
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//将文件内容读入lpBmpInfo
	fread((char*)lpBitsInfo, size, 1, fp);

	fclose(fp);

	lpBitsInfo->bmiHeader.biClrUsed = NumColors;

	return FALSE;
}

//水平镜像
void Mirror()
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 计算图像中每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 找到图像象素起始位置
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE *pixel1, *pixel2, temp;

	//向前映射
	// 针对图像每行进行操作
	for(i = 0; i < h; i++)
	{
		// 针对图像每列进行操作
		for(j = 0; j < w/2; j++)
		{
			// 指向新图像第i行，第j个象素的指针
			pixel1 = lpBits + LineBytes * (h - 1 - i) + j;

			// 指向新图像第i行，第w-j-1个象素的指针
			pixel2 = lpBits + LineBytes * (h - 1 - i) + (w - 1 - j);

			//交换*pixel1与*pixel2的值
			temp = *pixel1;
			*pixel1 = *pixel2;
			*pixel2 = temp;
		}
	}
}

void Zoom(float xratio, float yratio)
{
	// 源图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 计算源图像中每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 缩放后图像的宽度和高度
	int new_w = (int)(w * xratio + 0.5);
	int new_h = (int)(h * yratio + 0.5);

	// 计算新图像每行的字节数（必须是4的倍数）
	int new_LineBytes = (new_w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 为新图象分配内存
	BITMAPINFO* new_lpBitsInfo;
	LONG new_size = 40 + 1024 + new_h * new_LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(new_size)))
		return;

	// 复制BMP信息头和调色板
	memcpy(new_lpBitsInfo, lpBitsInfo, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

	// 更新信息头宽、高属性
	new_lpBitsInfo->bmiHeader.biWidth = new_w;
	new_lpBitsInfo->bmiHeader.biHeight = new_h;

	// 找到源图像象素起始位置
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// 找到新图像象素起始位置
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, i0, j0;
	BYTE *pixel, *new_pixel;

	// 向后映射
	// 针对图像每行进行操作
	for(i = 0; i < new_h; i++)
	{
		// 针对图像每列进行操作
		for(j = 0; j < new_w; j++)
		{
			// 指向新图像第i行，第j个象素的指针
			new_pixel = lpNewBits + new_LineBytes * (new_h - 1 - i) + j;

			// 计算该象素在源图像中的坐标（四舍五入取整，0阶插值）
			i0 = (int)(i / yratio + 0.5);
			j0 = (int)(j / xratio + 0.5);

			pixel = lpBits + LineBytes * (h - 1 - i0) + j0;
			*new_pixel = *pixel;

		}
	}

	//释放原图像
	free(lpBitsInfo);

	//更新为新图象
	lpBitsInfo = new_lpBitsInfo;
}

BYTE Interpolation (float,float);
void Rotate(int angle)
{
	// 源图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 计算源图像中每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 旋转角度（弧度）
	float RotateAngle = (float)(angle * 3.141592654 / 180.0);
	
	// 计算旋转角度的正弦
	float Sina = (float) sin((double)RotateAngle);
	
	// 计算旋转角度的余弦
	float Cosa = (float) cos((double)RotateAngle);
	
	// 计算原图的四个角的坐标（以图像中心为坐标系原点）
	float X1 = (float) (-(w - 1) / 2);
	float Y1 = (float) ( (h - 1) / 2);
	float X2 = (float) ( (w - 1) / 2);
	float Y2 = (float) ( (h - 1) / 2);
	float X3 = (float) (-(w - 1) / 2);
	float Y3 = (float) (-(h - 1) / 2);
	float X4 = (float) ( (w - 1) / 2);
	float Y4 = (float) (-(h - 1) / 2);
	
	// 计算新图四个角的坐标（以图像中心为坐标系原点）
	float newX1 =  Cosa * X1 + Sina * Y1;
	float newY1 = -Sina * X1 + Cosa * Y1;
	float newX2 =  Cosa * X2 + Sina * Y2;
	float newY2 = -Sina * X2 + Cosa * Y2;
	float newX3 =  Cosa * X3 + Sina * Y3;
	float newY3 = -Sina * X3 + Cosa * Y3;
	float newX4 =  Cosa * X4 + Sina * Y4;
	float newY4 = -Sina * X4 + Cosa * Y4;

	// 计算旋转后的图像实际宽度和高度
	int new_w = (int) (max(fabs(newX4 - newX1), fabs(newX3 - newX2)) + 0.5);
	int new_h = (int) (max(fabs(newY4 - newY1), fabs(newY3 - newY2)) + 0.5);

	// 计算新图像中每行的字节数（必须是4的倍数）
	int new_LineBytes =  (new_w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 为新图象分配内存
	BITMAPINFO* new_lpBitsInfo;
	LONG new_size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + new_h * new_LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(new_size)))
		return;

	// 复制BMP信息头和调色板
	memcpy(new_lpBitsInfo, lpBitsInfo, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

	// 更新信息头宽、高属性
	new_lpBitsInfo->bmiHeader.biWidth = new_w;
	new_lpBitsInfo->bmiHeader.biHeight = new_h;

	// 找到源图像象素起始位置
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// 找到新图像象素起始位置
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	// 两个常数，这样不用以后每次都计算了
	float f1 = (float) (-0.5 * (new_w - 1) * Cosa - 0.5 * (new_h - 1) * Sina + 0.5 * (w - 1));
	float f2 = (float) ( 0.5 * (new_w - 1) * Sina - 0.5 * (new_h - 1) * Cosa + 0.5 * (h - 1));

	int i, j;
	float i0, j0;
	BYTE *pixel, *new_pixel;

	// 向后映射
	// 针对图像每行进行操作
	for(i = 0; i < new_h; i++)
	{
		// 针对图像每列进行操作
		for(j = 0; j < new_w; j++)
		{
			// 指向新图像第i行，第j个象素的指针
			new_pixel = lpNewBits + new_LineBytes * (new_h - 1 - i) + j;

			// 计算该象素在源图像中的坐标
			i0 = (-((float) j) * Sina + ((float) i) * Cosa + f2 + (float) 0.5);
			j0 = ( ((float) j) * Cosa + ((float) i) * Sina + f1 + (float) 0.5);

			// 判断是否在源图范围内
			if ((j0 >= 0) && (j0 < w) && (i0 >= 0) && (i0 < h))
			{
				// 指向源图像第i0行，第j0个象素的指针
	//			pixel = lpBits + LineBytes * (h - 1 - (int)i0) + (int)j0;
				
				// 复制象素（0阶插值）
	//			*new_pixel = *pixel;

				// 一阶插值
				*new_pixel = Interpolation(j0, i0);
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为0
				*new_pixel = 0;
			}
		}
	}

	//释放原图像
	free(lpBitsInfo);

	//更新为新图象
	lpBitsInfo = new_lpBitsInfo;

}

BYTE Interpolation (float x, float y)
{
	// 四个最临近象素的坐标(i1, j1), (i2, j1), (i1, j2), (i2, j2)
	int	i1, j1, i2, j2;
	
	// 四个最临近象素值
	BYTE f1, f2, f3, f4;
	
	// 二个插值中间值
	BYTE f12, f34;

	//图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 图像每行的字节数
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 图像象素起始位置
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	// 定义一个值，当象素坐标相差小于该值时认为坐标相同
	float EXP = (float) 0.0001;
	
	// 计算四个最临近象素的坐标
	i1 = (int)x;
	i2 = i1 + 1;
	j1 = (int)y;
	j2 = j1 + 1;

	// 根据不同情况分别处理
	if( (x < 0) || (x > w - 1) || (y < 0) || (y > h - 1))
	{
		// 要计算的点不在源图范围内，直接返回0。
		return 0;
	}
	else
	{
		if (fabs(x - w + 1) <= EXP)
		{
			// 要计算的点在图像右边缘上
			if (fabs(y - h + 1) <= EXP)
			{
				// 要计算的点正好是图像最右下角那一个象素，直接返回该点象素值
				f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
				return f1;
			}
			else
			{
				//在图像右边缘上且不是最后一点
				f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
				f3 = *(lpBits + LineBytes * (h - 1 - j1) + i2);
				
				//直接一次插值即可，返回插值结果
				return (BYTE)((f1 + (y - j1) * (f3 - f1)));
			}
		}
		else if (fabs(y - h + 1) <= EXP)
		{
			// 要计算的点在图像下边缘上且不是最后一点
			f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
			f2 = *(lpBits + LineBytes * (h - 1 - j2) + i1);
			
			// 直接一次插值即可，返回插值结果
			return (BYTE)((f1 + (x - i1) * (f2 - f1)));
		}
		else
		{
			// 计算四个最临近象素值
			f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
			f2 = *(lpBits + LineBytes * (h - 1 - j2) + i1);
			f3 = *(lpBits + LineBytes * (h - 1 - j1) + i2);
			f4 = *(lpBits + LineBytes * (h - 1 - j2) + i2);
			
			// 插值1
			f12 = (BYTE)(f1 + (x - i1) * (f2 - f1));
			
			// 插值2
			f34 = (BYTE)(f3 + (x - i1) * (f4 - f3));
			
			// 插值3
			return (BYTE)(f12 + (y - j1) * (f34 - f12));
		}
	}
}