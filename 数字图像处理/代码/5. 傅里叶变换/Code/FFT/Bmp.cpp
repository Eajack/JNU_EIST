#include "stdafx.h"
#include <math.h>

#include <complex>
using namespace std;

// ������
#define PI 3.1415926535

BITMAPINFO* lpDIB = NULL;      //ԭʱ��ͼ��
BITMAPINFO* lpDIB_FFT = NULL;  //Ƶ��ͼ��

//ͼ��ÿ��������ռ�ֽ���
static DWORD LineBytes = 0;

//ͼ��ʵ��������ռ�ֽ���
static LONG size = 0;

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
	LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

	//����ʵ��ͼ������ռ�õ��ֽ���
	DWORD ImgSize = LineBytes * bi.biHeight;

	DWORD NumColors;//ʵ���õ�����ɫ��������ɫ�������е���ɫ����
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
	if (NULL == (lpDIB = (LPBITMAPINFO) malloc(size)))
		return FALSE;

	//�ļ�ָ�����¶�λ��BITMAPINFOHEADER��ʼ��
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//���ļ����ݶ���lpBmpInfo
	fread((char*)lpDIB, size, 1, fp);

	fclose(fp);

	lpDIB->bmiHeader.biClrUsed = NumColors;

	return FALSE;
}

void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// ���㸶��Ҷ�任����
	LONG count = 1 << r;
	
	// �����Ȩϵ��
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// ��ʱ���д��X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// ���õ����㷨���п��ٸ���Ҷ�任�����ΪX2
	complex<double>* X2 = new complex<double>[count]; 

	int k,j,p,size;
	complex<double>* temp;

	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			size = 1 << (r-k);
			for (i = 0; i < size/2; i++)
			{
				p = j * size;
				X2[i + p] = X1[i + p] + X1[i + p + size/2];
				X2[i + p + size/2] = (X1[i + p] - X1[i + p + size/2]) * W[i * (1<<k)];
			}
		}
		temp  = X1;
		X1 = X2;
		X2 = temp;
	}
	
	// ����������λ�������У�
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
		FD[j] /= count;
	}
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}

void Fourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//ָ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];

	// FFT��ȣ�����Ϊ2�������η���
	int FFT_w = 1;
	// FFT��ȵ�����������������
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}

	// FFT�߶ȣ�����Ϊ2�������η���
	int FFT_h = 1;
	// FFT�߶ȵ�����������������
	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	// ��
	for(i = 0; i < FFT_h; i++)
	{
		// ��
		for(j = 0; j < FFT_w; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			pixel = (unsigned char*)lpBits + LineBytes * (height - 1 - i) + j;

			// ��ʱ��ֵ
			TD[j + FFT_w * i] = complex<double>(*pixel * pow(-1, i + j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// �����м�任���
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// ��x������п��ٸ���Ҷ�任
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	// ɾ����ʱ����
	delete TD;

	//����Ƶ��ͼ��
	//ΪƵ��ͼ������ڴ�
	lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FFT)
		return;
	memcpy(lpDIB_FFT, lpDIB, size);

	//ָ��Ƶ��ͼ������ָ��
	lpBits = (BYTE*)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];

	double temp;
	// ��
	for(i = 0; i < FFT_h; i++)
	{
		// ��
		for(j = 0; j < FFT_w; j++)
		{
			// ����Ƶ�׷���
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) * 1000;
			
			// �ж��Ƿ񳬹�255
			if (temp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// ����Դͼ��
			*pixel = (BYTE)(temp);
		}
	}

	// ɾ����ʱ����
	delete FD;

}
