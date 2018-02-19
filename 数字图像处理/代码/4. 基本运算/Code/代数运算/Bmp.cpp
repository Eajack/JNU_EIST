#include "stdafx.h"

BITMAPINFO* lpBitsInfo1 = NULL;
BITMAPINFO* lpBitsInfo2 = NULL;
BITMAPINFO* lpBitsInfo3 = NULL;

//LineBytes为图像每行像素所占字节数
static DWORD LineBytes = 0;

//size为图像实际数据所占字节数
static LONG size = 0;

BITMAPINFO* LoadBmpFile(char* BmpFileName)
{
	FILE* fp;
	if (NULL == (fp = fopen(BmpFileName,"rb")))
		return NULL;

	BITMAPFILEHEADER bf;  //文件头结构
	BITMAPINFOHEADER bi;  //信息头结构

	//将文件头BITMAPFILEHEADER结构从文件中读出，填写到bf中
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);

	//将信息头BITMAPINFOHEADER结构从文件中读出，填写到bi中
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);

	//计算图像中每一行像素共占多少字节
	LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

	//计算实际图象数据占用的字节数
	DWORD ImgSize = LineBytes * bi.biHeight;

	DWORD NumColors;  //实际用到的颜色数，即调色板数组中的颜色个数
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

	//分配内存，大小为BITMAPINFOHEADER结构长度+调色板+实际位图数据
	size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	BITMAPINFO* lpDIB = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB)
		return NULL;

	//文件指针重新定位到BITMAPINFOHEADER开始处
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//将文件内容读入lpDIB
	fread((char*)lpDIB, size, 1, fp);
	fclose(fp);

	lpDIB->bmiHeader.biClrUsed = NumColors;

	return lpDIB;
}

//加法运算的比例值
#define ALPHA 0.5

BITMAPINFO* Algebra(BITMAPINFO* lpDIB1, BITMAPINFO* lpDIB2)
{
	if (NULL == lpDIB1 || NULL == lpDIB2)
		return NULL;

	//为输出图像分配内存
	BITMAPINFO* lpDIB3 = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB3)
		return NULL;
	memcpy(lpDIB3, lpDIB1, size);

	//指向输入、输出图像数据的指针
	BYTE *lpBits1, *lpBits2, *lpBits3;

	lpBits1 = (BYTE*)&lpDIB1->bmiColors[lpDIB1->bmiHeader.biClrUsed];
	lpBits2 = (BYTE*)&lpDIB2->bmiColors[lpDIB2->bmiHeader.biClrUsed];
	lpBits3 = (BYTE*)&lpDIB3->bmiColors[lpDIB3->bmiHeader.biClrUsed];

	for (int i = 0; i < lpDIB1->bmiHeader.biHeight; i ++)
	{
		for (int j = 0; j < (int)LineBytes; j ++)
		{
			//加法运算
		//	*lpBits3 =  (BYTE)((*lpBits1) * ALPHA + (*lpBits2) * (1 - ALPHA));

			//乘法运算
		//	*lpBits3 =  (BYTE)((*lpBits2) * (*lpBits1) / 255);

			//减法运算
			*lpBits3 =  (BYTE)((*lpBits1) - (*lpBits2));
			if (*lpBits3 < 100)  *lpBits3 = 255;

			lpBits1 ++;
			lpBits2 ++;
			lpBits3 ++;
		}
	}

	return lpDIB3;
}