#include "stdafx.h"

BITMAPINFO *lpBitsInfo = NULL;
DWORD H[256];

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

//����Ҷ�ֱ��ͼ���飨ͳ�Ƹ��Ҷȼ������ظ�����
void Histogram()
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ����Դͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ָ��ͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i, j;
	BYTE* pixel;

	// ���ü���Ϊ0
	for (i = 0; i < 256; i ++)
		H[i] = 0;

	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			// ָ�����ص�(i,j)��ָ��
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			// ������1
			H[*pixel] ++;
		}
	}
}

//���Ե�����
void LinerTrans(float a, float b)
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ����Դͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ָ��ͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i, j;
	BYTE* pixel;
	float temp;

	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			// ָ�����ص�(i,j)��ָ��
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			// ���Ա任
			temp = a * (*pixel) + b;
			
			// �ж��Ƿ񳬳���Χ
			if (temp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*pixel = 255;
			}
			else if (temp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*pixel = 0;
			}
			else
			{
				// ��������
				*pixel = (BYTE) (temp + 0.5);
			}
		}
	}
}

//�ҶȾ���
void Equalize()
{
	int i, j;
	BYTE* pixel;
	DWORD temp;

	//ͼ������
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ����Դͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	//lpBitsΪָ��ͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	//�Ҷ�ӳ���
	BYTE Map[256];

	//����Ҷ�ֱ��ͼ���飨ͳ�Ƹ��Ҷȼ������ظ�����
	Histogram();

	// ����Ҷ�ӳ���
	for (i = 0; i < 256; i++)
	{
		// ��ʼΪ0
		temp = 0;
		//�ۼ����		
		for (j = 0; j <= i ; j++)
			temp += H[j];
				
		// �����Ӧ���»Ҷ�ֵ
		Map[i] = (BYTE) (temp * 255 / w / h);
	}

	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j ++)
		{
			// ָ�����ص�(i,j)��ָ��
			pixel = lpBits + LineBytes * (h - 1 - i) + j;

			// �����µĻҶ�ֵ
			*pixel = Map[*pixel];
		}
	}
}