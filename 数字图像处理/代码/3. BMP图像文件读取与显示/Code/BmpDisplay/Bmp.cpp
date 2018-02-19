#include "stdafx.h"

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
	DWORD LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

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

#define WIDTHBYTES(i)    ((i+31)/32*4)
/**********************************************************
上面曾经提到过，每一行的字节数必须是4的整倍数，
只要调用(bi.biWidth * bi.biBitCount + 31)/32 * 4就能完成这一换算。

举一个例子，对于2色图，如果图象宽是31，则每一行需要31位存储，
合3个字节加7位，因为字节数必须是4的整倍数，所以应该是4，
而此时的biWidth=31,biBitCount=1,WIDTHBYTES(31*1)=4，和我们设想的一样。
再举一个256色的例子，如果图象宽是31，则每一行需要31个字节存储，
因为字节数必须是4的整倍数，所以应该是32，而此时
biWidth=31,biBitCount=8,WIDTHBYTES(31*8)=32，和我们设想的一样。
**********************************************************/