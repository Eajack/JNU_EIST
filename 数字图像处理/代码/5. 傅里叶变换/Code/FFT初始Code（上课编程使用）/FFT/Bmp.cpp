#include "stdafx.h"

BITMAPINFO *lpDIB = NULL;

//图像每行像素所占字节数
static DWORD LineBytes = 0;

//图像实际数据所占字节数
static LONG size = 0;

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
	LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

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
	size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (lpDIB = (LPBITMAPINFO) malloc(size)))
		return FALSE;

	//文件指针重新定位到BITMAPINFOHEADER开始处
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//将文件内容读入lpBitsInfo
	fread((char*)lpDIB, size, 1, fp);
	fclose(fp);

	lpDIB->bmiHeader.biClrUsed = NumColors;

	return TRUE;
}