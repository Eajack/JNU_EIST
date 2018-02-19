#include "stdafx.h"

BITMAPINFO *lpBitsInfo = NULL;
DWORD H[256];

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
	int LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

	//计算实际图象数据占用的字节数
	DWORD ImgSize = LineBytes * bi.biHeight;

	int NumColors;  //实际用到的颜色数，即调色板数组中的颜色个数
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

	//将文件内容读入lpBitsInfo
	fread((char*)lpBitsInfo, size, 1, fp);
	fclose(fp);

	lpBitsInfo->bmiHeader.biClrUsed = NumColors;

	return TRUE;
}

//计算灰度直方图数组（统计各灰度级的像素个数）
void Histogram()
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 计算源图像中每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 指向图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i, j;
	BYTE* pixel;

	// 重置计数为0
	for (i = 0; i < 256; i ++)
		H[i] = 0;

	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			// 指向像素点(i,j)的指针
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			// 计数加1
			H[*pixel] ++;
		}
	}
}

//线性点运算
void LinerTrans(float a, float b)
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 计算源图像中每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 指向图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i, j;
	BYTE* pixel;
	float temp;

	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			// 指向像素点(i,j)的指针
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			// 线性变换
			temp = a * (*pixel) + b;
			
			// 判断是否超出范围
			if (temp > 255)
			{
				// 直接赋值为255
				*pixel = 255;
			}
			else if (temp < 0)
			{
				// 直接赋值为0
				*pixel = 0;
			}
			else
			{
				// 四舍五入
				*pixel = (BYTE) (temp + 0.5);
			}
		}
	}
}

//灰度均衡
void Equalize()
{
	int i, j;
	BYTE* pixel;
	DWORD temp;

	//图像宽与高
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 计算源图像中每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	//lpBits为指向图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	//灰度映射表
	BYTE Map[256];

	//计算灰度直方图数组（统计各灰度级的像素个数）
	Histogram();

	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		temp = 0;
		//累加求和		
		for (j = 0; j <= i ; j++)
			temp += H[j];
				
		// 计算对应的新灰度值
		Map[i] = (BYTE) (temp * 255 / w / h);
	}

	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			// 指向像素点(i,j)的指针
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			// 计算新的灰度值
			*pixel = Map[*pixel];
		}
	}
}