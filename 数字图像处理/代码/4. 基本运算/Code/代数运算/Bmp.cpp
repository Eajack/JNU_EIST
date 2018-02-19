#include "stdafx.h"

BITMAPINFO* lpBitsInfo1 = NULL;
BITMAPINFO* lpBitsInfo2 = NULL;
BITMAPINFO* lpBitsInfo3 = NULL;

//LineBytesΪͼ��ÿ��������ռ�ֽ���
static DWORD LineBytes = 0;

//sizeΪͼ��ʵ��������ռ�ֽ���
static LONG size = 0;

BITMAPINFO* LoadBmpFile(char* BmpFileName)
{
	FILE* fp;
	if (NULL == (fp = fopen(BmpFileName,"rb")))
		return NULL;

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

	DWORD NumColors;  //ʵ���õ�����ɫ��������ɫ�������е���ɫ����
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

	//�����ڴ棬��СΪBITMAPINFOHEADER�ṹ����+��ɫ��+ʵ��λͼ����
	size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	BITMAPINFO* lpDIB = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB)
		return NULL;

	//�ļ�ָ�����¶�λ��BITMAPINFOHEADER��ʼ��
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//���ļ����ݶ���lpDIB
	fread((char*)lpDIB, size, 1, fp);
	fclose(fp);

	lpDIB->bmiHeader.biClrUsed = NumColors;

	return lpDIB;
}

//�ӷ�����ı���ֵ
#define ALPHA 0.5

BITMAPINFO* Algebra(BITMAPINFO* lpDIB1, BITMAPINFO* lpDIB2)
{
	if (NULL == lpDIB1 || NULL == lpDIB2)
		return NULL;

	//Ϊ���ͼ������ڴ�
	BITMAPINFO* lpDIB3 = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB3)
		return NULL;
	memcpy(lpDIB3, lpDIB1, size);

	//ָ�����롢���ͼ�����ݵ�ָ��
	BYTE *lpBits1, *lpBits2, *lpBits3;

	lpBits1 = (BYTE*)&lpDIB1->bmiColors[lpDIB1->bmiHeader.biClrUsed];
	lpBits2 = (BYTE*)&lpDIB2->bmiColors[lpDIB2->bmiHeader.biClrUsed];
	lpBits3 = (BYTE*)&lpDIB3->bmiColors[lpDIB3->bmiHeader.biClrUsed];

	for (int i = 0; i < lpDIB1->bmiHeader.biHeight; i ++)
	{
		for (int j = 0; j < (int)LineBytes; j ++)
		{
			//�ӷ�����
		//	*lpBits3 =  (BYTE)((*lpBits1) * ALPHA + (*lpBits2) * (1 - ALPHA));

			//�˷�����
		//	*lpBits3 =  (BYTE)((*lpBits2) * (*lpBits1) / 255);

			//��������
			*lpBits3 =  (BYTE)((*lpBits1) - (*lpBits2));
			if (*lpBits3 < 100)  *lpBits3 = 255;

			lpBits1 ++;
			lpBits2 ++;
			lpBits3 ++;
		}
	}

	return lpDIB3;
}