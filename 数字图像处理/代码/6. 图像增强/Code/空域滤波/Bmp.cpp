#include "stdafx.h"
#include <math.h>

BITMAPINFO *lpBitsInfo = NULL;

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

void Template(int* Array, float coef)
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 指向原图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// 为新图象分配内存
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;

	// 复制BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// 找到新图像象素起始位置
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	float result;

	// 行(除去边缘几行)
	for(i = 1; i < h - 1; i++)
	{
		// 列(除去边缘几列)
		for(j = 1; j < w - 1; j++)
		{
			// 指向新图第i行，第j个象素的指针
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			result = 0;

			// 计算3x3模板内像素灰度值的和
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// 指向原图在模板内每个像素点的灰度值，第i - 1 + k行，第j - 1 + l个象素的指针
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					
					// 灰度值乘上模板系数后累加
					result += (*pixel) * Array[k * 3 + l];
				}
			}

			// 乘上系数
			result *= coef;
	//		result = (float)fabs(result);

			if (result < 0)
				*new_pixel = 0;
			else if(result > 255)
				*new_pixel = 255;
			else
				*new_pixel = (BYTE) (result + 0.5);
		}
	}

	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;
}

void AverageFilter() 
{
	int Array[9]; //3x3模板

	//标准均值滤波
	Array[0] = 1;
	Array[1] = 1;
	Array[2] = 1;
	Array[3] = 1;
	Array[4] = 1;
	Array[5] = 1;
	Array[6] = 1;
	Array[7] = 1;
	Array[8] = 1;

	Template(Array, (float)1/9);

	/*
	//高斯滤波
	Array[0] = 1;
	Array[1] = 2;
	Array[2] = 1;
	Array[3] = 2;
	Array[4] = 4;
	Array[5] = 2;
	Array[6] = 1;
	Array[7] = 2;
	Array[8] = 1;

	Template(Array, (float)1/16);
  */
}

BYTE WINAPI GetMedianNum(BYTE* Array)
{
	int i,j;
	
	BYTE temp;
	
	// 用冒泡法对数组进行排序
	for (j = 0; j < 9 - 1; j ++)
	{
		for (i = 0; i < 9 - j - 1; i ++)
		{
			if (Array[i] > Array[i + 1])
			{
				// 互换
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
			}
		}
	}
	
	// 返回中值
	return Array[4];
}

void MedianFilter() 
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 指向原图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// 为新图象分配内存
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;

	// 复制BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// 找到新图像象素起始位置
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	
	BYTE Value[9]; //3x3模板

	// 行(除去边缘几行)
	for(i = 1; i < h - 1; i++)
	{
		// 列(除去边缘几列)
		for(j = 1; j < w - 1; j++)
		{
			// 指向新图第i行，第j个象素的指针
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;

			// 计算 3x3模板内像素的灰度值
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// 指向原图第i - 1 + k行，第j - 1 + l个象素的指针
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					
					// 保存象素值
					Value[k * 3 + l] = *pixel;
				}
			}

			// 获取中值
			*new_pixel = GetMedianNum(Value);
		}
	}

	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;

}

//梯度锐化
void GradSharp() 
{
	// 图像的宽度和高度
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// 每行的字节数（必须是4的倍数）
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// 指向原图像数据的指针
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// 指向源图像的指针
	BYTE *lpSrc, *lpSrc1, *lpSrc2;
	
	int i, j;
	BYTE temp;
	
	// 每行
	for(i = 0; i < h-1; i++)
	{
		// 每列
		for(j = 0; j < w-1; j++)
		{
			// 指向图像第i行，第j个象素的指针
			lpSrc  = lpBits + LineBytes * (h - 1 - i) + j;
			
			// 指向图像第i+1行，第j个象素的指针
			lpSrc1 = lpBits + LineBytes * (h - 2 - i) + j;
			
			// 指向图像第i行，第j+1个象素的指针
			lpSrc2 = lpBits + LineBytes * (h - 1 - i) + j + 1;
			
			//梯度算子
			temp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			
			if (temp > 255)
				*lpSrc = 255;
			else
				*lpSrc = temp;
		}
	}
}

//拉普拉斯锐化
void RaplasSharp() 
{
	int Array[9]; //3x3模板
/*
	//拉普拉斯算子
	Array[0] = 0;
	Array[1] = 1;
	Array[2] = 0;
	Array[3] = 1;
	Array[4] = -4;
	Array[5] = 1;
	Array[6] = 0;
	Array[7] = 1;
	Array[8] = 0;
*/	

	//拉普拉斯锐化
	Array[0] = -1;
	Array[1] = -1;
	Array[2] = -1;
	Array[3] = -1;
	Array[4] = 9;
	Array[5] = -1;
	Array[6] = -1;
	Array[7] = -1;
	Array[8] = -1;

	Template(Array, (float)1);
}