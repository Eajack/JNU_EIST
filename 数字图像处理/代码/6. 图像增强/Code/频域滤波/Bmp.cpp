#include "stdafx.h"
#include <math.h>
#include <complex>
using namespace std;

BITMAPINFO* lpDIB = NULL;      //原时域图像
BITMAPINFO* lpDIB_FFT = NULL;  //频谱图像
BITMAPINFO* lpDIB_IFFT = NULL;  //FFT反变换的时域图像

complex<double>* g_FD = NULL; //原图像的频域数据

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
	size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (lpDIB = (LPBITMAPINFO) malloc(size)))
		return FALSE;

	//文件指针重新定位到BITMAPINFOHEADER开始处
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//将文件内容读入lpBmpInfo
	fread((char*)lpDIB, size, 1, fp);

	fclose(fp);

	lpDIB->bmiHeader.biClrUsed = NumColors;

	return FALSE;
}

// 常数π
#define PI 3.1415926535

// 进行付立叶变换的宽度和高度（2的整数次方）
static int FFT_w = 1;
static int FFT_h = 1;
static int wp = 0;
static int hp = 0;

//FFT变换
/*************************************************************************
 *   complex<double> * TD	- 指向时域数组的指针
 *   complex<double> * FD	- 指向频域数组的指针
 *   r						－2的幂数，即迭代次数
 ************************************************************************/
void FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// 付立叶变换点数
	LONG	count;
	
	// 循环变量
	int	i,j,k;
	
	// 中间变量
	int	size,p;
	
	// 角度
	double	angle;
	
	complex<double> *W,*X1,*X2,*temp;
	
	// 计算付立叶变换点数
	count = 1 << r;
	
	// 分配运算所需存储空间
	W  = new complex<double>[count / 2];
	X1 = new complex<double>[count];
	X2 = new complex<double>[count];

	// 计算加权系数
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// 将时域点写入X1
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// 采用蝶形算法进行快速付立叶变换
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
	
	// 重新排序（码位倒序排列）
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
	
	// 释放内存
	delete W;
	delete X1;
	delete X2;
}

//FFT反变换
void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// 付立叶变换点数
	LONG	count;
	
	// 循环变量
	int		i;
	
	complex<double> *X;
	
	// 计算付立叶变换点数
	count = 1 << r;
	
	// 分配运算所需存储器
	X = new complex<double>[count];
	
	// 将频域点写入X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// 求共轭
	for(i = 0; i < count; i++)
	{
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	}
	
	// 调用快速付立叶变换
	FFT(X, TD, r);
	
	// 求时域点的共轭
	for(i = 0; i < count; i++)
	{
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	}
	
	// 释放内存
	delete X;
}

//FFT变换，输入图像数据（全局），返回频域数据FD
complex<double>* Fourier()
{
	//图像的宽度和高度
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//指向图像数据指针
	BYTE* lpBits = (BYTE*)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];

	// 计算进行付立叶变换的宽度和高度（2的整数次方）
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

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	// 行
	for(i = 0; i < FFT_h; i++)
	{
		// 列
		for(j = 0; j < FFT_w; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			pixel = (unsigned char*)lpBits + LineBytes * (height - 1 - i) + j;

			// 给时域赋值
			TD[j + FFT_w * i] = complex<double>(*pixel * pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// 对y方向进行快速付立叶变换
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// 保存变换结果
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// 对x方向进行快速付立叶变换
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	// 删除临时变量
	delete TD;

	return FD;
}

//输入频域数据，生成频谱图像
BITMAPINFO* Create_FFT_Image(complex<double>* FD)
{
	//原图像的宽度和高度
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//为频域图像分配内存
	BITMAPINFO* lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FFT)
		return NULL;
	memcpy(lpDIB_FFT, lpDIB, size);

	//指向频域图像数据指针
	BYTE* lpBits = (BYTE*)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];

	int i, j;
	double temp;
	BYTE* pixel;

	// 行
	for(i = 0; i < FFT_h; i++)
	{
		// 列
		for(j = 0; j < FFT_w; j++)
		{
			// 计算频谱
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) * 2000 ;
			
			// 判断是否超过255
			if (temp > 255)
			{
				// 对于超过的，直接设置为255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 更新源图像
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

//输入频域数据FD，经过FFT逆变换，恢复时域数据图像
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

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];

	for(i = 0; i < FFT_h; i++)
	{
		// 对y方向进行快速付立叶逆变换
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	}
	
	// 保存变换结果
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// 对x方向进行快速付立逆叶变换
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);
	}

	//图像的宽度和高度
	int width = lpDIB->bmiHeader.biWidth;
	int height = lpDIB->bmiHeader.biHeight;

	//为新的时域图像分配内存
	BITMAPINFO* new_lpDIB = (LPBITMAPINFO) malloc(size);
	if (NULL == new_lpDIB)
		return NULL;
	memcpy(new_lpDIB, lpDIB, size);

	//指向新的时域图像数据指针
	BYTE* lpBits = (BYTE*)&new_lpDIB->bmiColors[new_lpDIB->bmiHeader.biClrUsed];

	BYTE* pixel;
	double temp;
	// 行
	for(i = 0; i < FFT_h; i++)
	{
		// 列
		for(j = 0; j < FFT_w; j++)
		{
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 更新源图像
			temp = (TD[j * FFT_h + i].real() / pow(-1,i+j));

			if (temp > 255)
				temp = 255;
			if (temp < 0)
				temp = 0;

			*pixel = (BYTE) temp;
		}
	}

	// 删除临时变量
	delete TD;

	return new_lpDIB;
}

BITMAPINFO* IFFT_Image()
{
	//IFFT会使FD改变，因此执行IFFT之前需复制FD
	complex<double>* temp = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		temp[n] = g_FD[n];

	BITMAPINFO* image = Create_IFFT_Image(temp);

	delete temp;

	return image;
}

//理想低通(D>0)、高通(D<0)滤波
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
			
			if (D > 0) //低通
			{
				if (dis > D) 
				{
					temp[i * FFT_h + j] = 0; //理想低通，截断高频
				}
			}
			else { //高通
				if (dis <= -D) 
				{
					temp[i * FFT_h + j] = 0; //理想高通，截断低频
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

//巴特沃斯低通(D>0)、高通(D<0)滤波，阶数n=1
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
			
			if (D > 0) //巴特沃斯低通滤波
				temp[i * FFT_h + j] *= 1/(1 + pow(dis/D, 2));
			else	   //巴特沃斯高通滤波
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

//高斯低通(D>0)、高通(D<0)滤波
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
			
			if (D > 0) //高斯低通滤波
				temp[i * FFT_h + j] *= exp(-dis*dis/(2*D*D));
			else	   //高斯高通滤波
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