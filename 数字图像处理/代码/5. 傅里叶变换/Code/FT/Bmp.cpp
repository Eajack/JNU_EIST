#include "stdafx.h"

#include <complex>
using namespace std;

BITMAPINFO *lpBitsInfo = NULL;
LONG size;

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

#define PI 3.1415926535
complex<double>* gFD; 

void FT(complex<double> * TD, complex<double> * FD, int m)
{
	int u, x;
	double angle;
	for (u = 0; u < m; u ++)
	{
		FD[u] = 0;
		for (x = 0; x < m; x ++)
		{
			angle = -2 * PI * u * x / m;
			FD[u] += TD[x] * complex<double> (cos(angle), sin(angle)); 
		}
		FD[u] /= m;
	}
}

void IFT(complex<double> * FD, complex<double> * TD, int m)
{
	int u, x;
	double angle;
	for (x = 0; x < m; x ++)
	{
		TD[x] = 0;
		for (u = 0; u < m; u ++)
		{
			angle = 2 * PI * u * x / m;
			TD[x] += FD[u] * complex<double> (cos(angle), sin(angle)); 
		}

	}
	/*
	int u, x;
	complex<double> *X = new complex<double>[m];
	memcpy(X, FD, sizeof(complex<double>) * m);
	
	// 求共轭
	for (u = 0; u < m; u ++)
	{
		X[u] = complex<double> (X[u].real(), -X[u].imag());
	}
	  
	// 调用付立叶变换
	FT(X, TD, m);
	
	// 求时域点的共轭
	for (x = 0; x < m; x ++)
	{
		TD[x] = complex<double> (TD[x].real() * m, -TD[x].imag() * m);
	}
		  
	delete X;
	*/
}

void Fourier()
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// 分配内存
	complex<double>* TD = new complex<double>[w * h];
	complex<double>* FD = new complex<double>[w * h];
	
	// 给时域赋值
	int i, j;
	BYTE* pixel;

	for (i = 0; i < h; i ++)
	{
		for(j = 0; j < w; j ++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			TD[j + w * i] = complex<double>(*pixel * pow(-1, i + j), 0);
		}
	}
	
	//对图像中每行像素做一个w（图像宽度）点的1D_FFT变换
	for (i = 0; i < h; i ++)
	{
		FT(&TD[w * i], &FD[w * i], w);
	}
	
	//利用TD保存中间变换结果，将FD转置后赋给TD
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			TD[i + h * j] = FD[j + w * i];
		}
	}
	
	//因为前面TD是中间结果FD的转置，所以此处相当于对图像中每列像素做一个h（图像高度）点的1DFT变换
	for (i = 0; i < w; i ++)
	{
		FT(&TD[i * h], &FD[i * h], h);
	}//注意，此时FD为图像的转置

	//生成频谱图像
	//为频谱图像分配内存
	BITMAPINFO* lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);

	//指向频谱图像数据指针
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			//计算频谱幅度.注意下标的写法，转置回来
			temp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() + 
				        FD[j * h + i].imag() * FD[j * h + i].imag()) * 2000;
			
			if (temp > 255)
				temp = 255;
			*pixel = (BYTE)(temp);
		}
	}
	
	// 删除临时变量
	delete TD;
	gFD = FD;

	//释放原图像
	free(lpBitsInfo);
	
	//更新为新图象
	lpBitsInfo = lpDIB_FT;
}

void IFourier()
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	//分配内存
	complex<double>* TD = new complex<double>[w * h];
	complex<double>* FD = new complex<double>[w * h];

	int i, j;

	//将gFD的转置赋给FD，注：gFD为图像的转置，转置后FD恢复正常
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			FD[w * i + j] = gFD[i + h * j];
		}
	}

	//对FD中每行数据做一个w（图像宽度）点的1DIFT变换。
	for (i = 0; i < h; i ++)
	{
		IFT(&FD[w * i], &TD[w * i], w);
	}
	
	//利用FD保存中间变换结果，将TD转置后赋给FD。
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			FD[i + h * j] = TD[j + w * i];
		}
	}

	//因为前面FD是中间结果TD的转置，所以此处相当于FD中每列数据做一个h（图像高度）点的1DIFT变换
	for (i = 0; i < w; i ++)
	{
		IFT(&FD[i * h], &TD[i * h], h);
	}
	
	//为图像分配内存
	BITMAPINFO* lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);
	
	//指向频域图像数据指针
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	BYTE* pixel;
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			*pixel = (BYTE)(TD[j * h + i].real() / pow(-1, i + j));
		}
	}
	
	// 删除临时变量
	delete FD;
	delete gFD;
	delete TD;
	
	//释放原图像
	free(lpBitsInfo);
	
	//更新为新图象
	lpBitsInfo = lpDIB_FT;
}