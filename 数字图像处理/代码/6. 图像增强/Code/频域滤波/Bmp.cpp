#include "stdafx.h"
#include <math.h>
#include <complex>
using namespace std;

BITMAPINFO* lpDIB = NULL;      //ԭʱ��ͼ��
BITMAPINFO* lpDIB_FFT = NULL;  //Ƶ��ͼ��
BITMAPINFO* lpDIB_IFFT = NULL;  //FFT���任��ʱ��ͼ��

complex<double>* g_FD = NULL; //ԭͼ���Ƶ������

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

// ������
#define PI 3.1415926535

// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
static int FFT_w = 1;
static int FFT_h = 1;
static int wp = 0;
static int hp = 0;

//FFT�任
/*************************************************************************
 *   complex<double> * TD	- ָ��ʱ�������ָ��
 *   complex<double> * FD	- ָ��Ƶ�������ָ��
 *   r						��2������������������
 ************************************************************************/
void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	
	// ѭ������
	int	i,j,k;
	
	// �м����
	int	size,p;
	
	// �Ƕ�
	double	angle;
	
	complex<double> *W,*X1,*X2,*temp;
	
	// ���㸶��Ҷ�任����
	count = 1 << r;
	
	// ������������洢�ռ�
	W  = new complex<double>[count / 2];
	X1 = new complex<double>[count];
	X2 = new complex<double>[count];

	// �����Ȩϵ��
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// ��ʱ���д��X1
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// ���õ����㷨���п��ٸ���Ҷ�任
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

		FD[j] /= count;//complex<double> (FD[j].real() / count, FD[j].imag() / count);
	}
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}

//FFT���任
void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	
	// ѭ������
	int		i;
	
	complex<double> *X;
	
	// ���㸶��Ҷ�任����
	count = 1 << r;
	
	// ������������洢��
	X = new complex<double>[count];
	
	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// ����
	for(i = 0; i < count; i++)
	{
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	}
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ���Ĺ���
	for(i = 0; i < count; i++)
	{
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	}
	
	// �ͷ��ڴ�
	delete X;
}

//FFT�任������ͼ�����ݣ�ȫ�֣�������Ƶ������FD
complex<double>* Fourier()
{
	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//ָ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];

	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}
	
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
			TD[j + FFT_w * i] = complex<double>(*pixel * pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// ����任���
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

	return FD;
}

//����Ƶ�����ݣ�����Ƶ��ͼ��
BITMAPINFO* Create_FFT_Image(complex<double>* FD)
{
	//ԭͼ��Ŀ�Ⱥ͸߶�
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//ΪƵ��ͼ������ڴ�
	BITMAPINFO* lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FFT)
		return NULL;
	memcpy(lpDIB_FFT, lpDIB, size);

	//ָ��Ƶ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];

	int i, j;
	double temp;
	BYTE* pixel;

	// ��
	for(i = 0; i < FFT_h; i++)
	{
		// ��
		for(j = 0; j < FFT_w; j++)
		{
			// ����Ƶ��
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) * 2000 ;
			
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

	return lpDIB_FFT;
}

BITMAPINFO* FFT_Image()
{
	if (g_FD)
		delete g_FD;

	g_FD = Fourier();

	return Create_FFT_Image(g_FD);
}

//����Ƶ������FD������FFT��任���ָ�ʱ������ͼ��
BITMAPINFO* Create_IFFT_Image(complex<double>* FD)
{
	int i, j;
	complex<double>* tmp = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		tmp[n] = FD[n];

	for (i = 0; i < FFT_h; i ++)
	{
		for (j = 0; j < FFT_w; j ++)
		{
			FD[FFT_w * i + j] = tmp[i + FFT_h * j];
		}
	}
	delete tmp;

	// �����ڴ�
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];

	for(i = 0; i < FFT_h; i++)
	{
		// ��y������п��ٸ���Ҷ��任
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	}
	
	// ����任���
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// ��x������п��ٸ�����Ҷ�任
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);
	}

	//ͼ��Ŀ�Ⱥ͸߶�
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//Ϊ�µ�ʱ��ͼ������ڴ�
	BITMAPINFO* new_lpDIB = (LPBITMAPINFO) malloc(size);
	if (NULL == new_lpDIB)
		return NULL;
	memcpy(new_lpDIB, lpDIB, size);

	//ָ���µ�ʱ��ͼ������ָ��
	BYTE* lpBits = (BYTE*)&new_lpDIB->bmiColors[new_lpDIB->bmiHeader.biClrUsed];

	BYTE* pixel;
	double temp;
	// ��
	for(i = 0; i < FFT_h; i++)
	{
		// ��
		for(j = 0; j < FFT_w; j++)
		{
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// ����Դͼ��
			temp = (TD[j * FFT_h + i].real() / pow(-1,i+j));

			if (temp > 255)
				temp = 255;
			if (temp < 0)
				temp = 0;

			*pixel = (BYTE) temp;
		}
	}

	// ɾ����ʱ����
	delete TD;

	return new_lpDIB;
}

BITMAPINFO* IFFT_Image()
{
	//IFFT��ʹFD�ı䣬���ִ��IFFT֮ǰ�踴��FD
	complex<double>* temp = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		temp[n] = g_FD[n];

	BITMAPINFO* image = Create_IFFT_Image(temp);

	delete temp;

	return image;
}

//�����ͨ(D>0)����ͨ(D<0)�˲�
void Ideal_Filter_FFT(int D)
{
	complex<double>* temp = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		temp[n] = g_FD[n];

	int i, j;
	double dis;

	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			
			if (D > 0) //��ͨ
			{
				if (dis > D) 
				{
					temp[i * FFT_h + j] = 0; //�����ͨ���ضϸ�Ƶ
				}
			}
			else { //��ͨ
				if (dis <= -D) 
				{
					temp[i * FFT_h + j] = 0; //�����ͨ���ضϵ�Ƶ
				}
			}
		}
	}

	if (lpDIB_FFT)
		free(lpDIB_FFT);
	lpDIB_FFT = Create_FFT_Image(temp);

	if (lpDIB_IFFT)
		free(lpDIB_IFFT);
	lpDIB_IFFT = Create_IFFT_Image(temp);

	delete temp;
}

//������˹��ͨ(D>0)����ͨ(D<0)�˲�������n=1
void Butterworth_Filter_FFT(int D)
{
	complex<double>* temp = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		temp[n] = g_FD[n];

	int i, j;
	double dis;

	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			
			if (D > 0) //������˹��ͨ�˲�
				temp[i * FFT_h + j] *= 1/(1 + pow(dis/D, 2));
			else	   //������˹��ͨ�˲�
				temp[i * FFT_h + j] *= 1/(1 + pow(D/dis, 2));
		}
	}

	if (lpDIB_FFT)
		free(lpDIB_FFT);
	lpDIB_FFT = Create_FFT_Image(temp);

	if (lpDIB_IFFT)
		free(lpDIB_IFFT);
	lpDIB_IFFT = Create_IFFT_Image(temp);

	delete temp;
}

//��˹��ͨ(D>0)����ͨ(D<0)�˲�
void Gauss_Filter_FFT(int D)
{
	complex<double>* temp = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		temp[n] = g_FD[n];

	int i, j;
	double dis;

	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			
			if (D > 0) //��˹��ͨ�˲�
				temp[i * FFT_h + j] *= exp(-dis*dis/(2*D*D));
			else	   //��˹��ͨ�˲�
				temp[i * FFT_h + j] *= 1-exp(-dis*dis/(2*D*D));
		}
	}

	if (lpDIB_FFT)
		free(lpDIB_FFT);
	lpDIB_FFT = Create_FFT_Image(temp);

	if (lpDIB_IFFT)
		free(lpDIB_IFFT);
	lpDIB_IFFT = Create_IFFT_Image(temp);

	delete temp;
}