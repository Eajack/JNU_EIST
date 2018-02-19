#include "stdafx.h"
#include <math.h>

BITMAPINFO *lpBitsInfo = NULL;

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
	int LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

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
	LONG size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
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

void Template(int* Array, float coef)
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ָ��ԭͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// Ϊ��ͼ������ڴ�
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;

	// ����BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// �ҵ���ͼ��������ʼλ��
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	float result;

	// ��(��ȥ��Ե����)
	for(i = 1; i < h - 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = 1; j < w - 1; j++)
		{
			// ָ����ͼ��i�У���j�����ص�ָ��
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			result = 0;

			// ����3x3ģ�������ػҶ�ֵ�ĺ�
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// ָ��ԭͼ��ģ����ÿ�����ص�ĻҶ�ֵ����i - 1 + k�У���j - 1 + l�����ص�ָ��
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					
					// �Ҷ�ֵ����ģ��ϵ�����ۼ�
					result += (*pixel) * Array[k * 3 + l];
				}
			}

			// ����ϵ��
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
	int Array[9]; //3x3ģ��

	//��׼��ֵ�˲�
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
	//��˹�˲�
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
	
	// ��ð�ݷ��������������
	for (j = 0; j < 9 - 1; j ++)
	{
		for (i = 0; i < 9 - j - 1; i ++)
		{
			if (Array[i] > Array[i + 1])
			{
				// ����
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
			}
		}
	}
	
	// ������ֵ
	return Array[4];
}

void MedianFilter() 
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ָ��ԭͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// Ϊ��ͼ������ڴ�
	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;

	// ����BMP
	memcpy(new_lpBitsInfo, lpBitsInfo, size);
	// �ҵ���ͼ��������ʼλ��
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	
	BYTE Value[9]; //3x3ģ��

	// ��(��ȥ��Ե����)
	for(i = 1; i < h - 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = 1; j < w - 1; j++)
		{
			// ָ����ͼ��i�У���j�����ص�ָ��
			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;

			// ���� 3x3ģ�������صĻҶ�ֵ
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					// ָ��ԭͼ��i - 1 + k�У���j - 1 + l�����ص�ָ��
					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					
					// ��������ֵ
					Value[k * 3 + l] = *pixel;
				}
			}

			// ��ȡ��ֵ
			*new_pixel = GetMedianNum(Value);
		}
	}

	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;

}

//�ݶ���
void GradSharp() 
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ָ��ԭͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// ָ��Դͼ���ָ��
	BYTE *lpSrc, *lpSrc1, *lpSrc2;
	
	int i, j;
	BYTE temp;
	
	// ÿ��
	for(i = 0; i < h-1; i++)
	{
		// ÿ��
		for(j = 0; j < w-1; j++)
		{
			// ָ��ͼ���i�У���j�����ص�ָ��
			lpSrc  = lpBits + LineBytes * (h - 1 - i) + j;
			
			// ָ��ͼ���i+1�У���j�����ص�ָ��
			lpSrc1 = lpBits + LineBytes * (h - 2 - i) + j;
			
			// ָ��ͼ���i�У���j+1�����ص�ָ��
			lpSrc2 = lpBits + LineBytes * (h - 1 - i) + j + 1;
			
			//�ݶ�����
			temp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			
			if (temp > 255)
				*lpSrc = 255;
			else
				*lpSrc = temp;
		}
	}
}

//������˹��
void RaplasSharp() 
{
	int Array[9]; //3x3ģ��
/*
	//������˹����
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

	//������˹��
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