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

	BITMAPFILEHEADER bf;  //�ļ�ͷ�ṹ
	BITMAPINFOHEADER bi;  //��Ϣͷ�ṹ

	//���ļ�ͷBITMAPFILEHEADER�ṹ���ļ��ж�������д��bf��
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);

	//����ϢͷBITMAPINFOHEADER�ṹ���ļ��ж�������д��bi��
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);

	//����ͼ����ÿһ�����ع�ռ�����ֽ�
	DWORD LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

	//����ʵ��ͼ������ռ�õ��ֽ���
	DWORD ImgSize = LineBytes * bi.biHeight;

	int NumColors;  //ʵ���õ�����ɫ��������ɫ�������е���ɫ����
	if (bi.biClrUsed != 0)
		NumColors = bi.biClrUsed; //���bi.biClrUsed��Ϊ�㣬���Ǳ�ͼ��ʵ���õ�����ɫ��
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
			NumColors = 0; //�������ɫͼ��û�õ���ɫ��
			break;
		}
	}

	//������256ɫͼ��
	if (NumColors != 256) 
	{
		fclose(fp);
		AfxMessageBox("����256ɫͼ��!");
		return FALSE;
	}

	//�����ڴ棬��СΪBITMAPINFOHEADER�ṹ����+��ɫ��+ʵ��λͼ����
	size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;

	//�ļ�ָ�����¶�λ��BITMAPINFOHEADER��ʼ��
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//���ļ����ݶ���lpBitsInfo
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
	
	// ����
	for (u = 0; u < m; u ++)
	{
		X[u] = complex<double> (X[u].real(), -X[u].imag());
	}
	  
	// ���ø���Ҷ�任
	FT(X, TD, m);
	
	// ��ʱ���Ĺ���
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

	// �����ڴ�
	complex<double>* TD = new complex<double>[w * h];
	complex<double>* FD = new complex<double>[w * h];
	
	// ��ʱ��ֵ
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
	
	//��ͼ����ÿ��������һ��w��ͼ���ȣ����1D_FFT�任
	for (i = 0; i < h; i ++)
	{
		FT(&TD[w * i], &FD[w * i], w);
	}
	
	//����TD�����м�任�������FDת�ú󸳸�TD
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			TD[i + h * j] = FD[j + w * i];
		}
	}
	
	//��Ϊǰ��TD���м���FD��ת�ã����Դ˴��൱�ڶ�ͼ����ÿ��������һ��h��ͼ��߶ȣ����1DFT�任
	for (i = 0; i < w; i ++)
	{
		FT(&TD[i * h], &FD[i * h], h);
	}//ע�⣬��ʱFDΪͼ���ת��

	//����Ƶ��ͼ��
	//ΪƵ��ͼ������ڴ�
	BITMAPINFO* lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);

	//ָ��Ƶ��ͼ������ָ��
	lpBits = (BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			//����Ƶ�׷���.ע���±��д����ת�û���
			temp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() + 
				        FD[j * h + i].imag() * FD[j * h + i].imag()) * 2000;
			
			if (temp > 255)
				temp = 255;
			*pixel = (BYTE)(temp);
		}
	}
	
	// ɾ����ʱ����
	delete TD;
	gFD = FD;

	//�ͷ�ԭͼ��
	free(lpBitsInfo);
	
	//����Ϊ��ͼ��
	lpBitsInfo = lpDIB_FT;
}

void IFourier()
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	//�����ڴ�
	complex<double>* TD = new complex<double>[w * h];
	complex<double>* FD = new complex<double>[w * h];

	int i, j;

	//��gFD��ת�ø���FD��ע��gFDΪͼ���ת�ã�ת�ú�FD�ָ�����
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			FD[w * i + j] = gFD[i + h * j];
		}
	}

	//��FD��ÿ��������һ��w��ͼ���ȣ����1DIFT�任��
	for (i = 0; i < h; i ++)
	{
		IFT(&FD[w * i], &TD[w * i], w);
	}
	
	//����FD�����м�任�������TDת�ú󸳸�FD��
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			FD[i + h * j] = TD[j + w * i];
		}
	}

	//��Ϊǰ��FD���м���TD��ת�ã����Դ˴��൱��FD��ÿ��������һ��h��ͼ��߶ȣ����1DIFT�任
	for (i = 0; i < w; i ++)
	{
		IFT(&FD[i * h], &TD[i * h], h);
	}
	
	//Ϊͼ������ڴ�
	BITMAPINFO* lpDIB_FT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FT)
		return;
	memcpy(lpDIB_FT, lpBitsInfo, size);
	
	//ָ��Ƶ��ͼ������ָ��
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
	
	// ɾ����ʱ����
	delete FD;
	delete gFD;
	delete TD;
	
	//�ͷ�ԭͼ��
	free(lpBitsInfo);
	
	//����Ϊ��ͼ��
	lpBitsInfo = lpDIB_FT;
}