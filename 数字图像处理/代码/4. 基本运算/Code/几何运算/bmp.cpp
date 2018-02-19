#include "stdafx.h"
#include "math.h"

BITMAPINFO* lpBitsInfo = NULL;

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
	LONG size = sizeof(BITMAPINFOHEADER) + NumColors * sizeof(RGBQUAD) + ImgSize;
	if (NULL == (lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return FALSE;

	//�ļ�ָ�����¶�λ��BITMAPINFOHEADER��ʼ��
	fseek(fp, sizeof(BITMAPFILEHEADER),SEEK_SET);

	//���ļ����ݶ���lpBmpInfo
	fread((char*)lpBitsInfo, size, 1, fp);

	fclose(fp);

	lpBitsInfo->bmiHeader.biClrUsed = NumColors;

	return FALSE;
}

//ˮƽ����
void Mirror()
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ����ͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// �ҵ�ͼ��������ʼλ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE *pixel1, *pixel2, temp;

	//��ǰӳ��
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < h; i++)
	{
		// ���ͼ��ÿ�н��в���
		for(j = 0; j < w/2; j++)
		{
			// ָ����ͼ���i�У���j�����ص�ָ��
			pixel1 = lpBits + LineBytes * (h - 1 - i) + j;

			// ָ����ͼ���i�У���w-j-1�����ص�ָ��
			pixel2 = lpBits + LineBytes * (h - 1 - i) + (w - 1 - j);

			//����*pixel1��*pixel2��ֵ
			temp = *pixel1;
			*pixel1 = *pixel2;
			*pixel2 = temp;
		}
	}
}

void Zoom(float xratio, float yratio)
{
	// Դͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ����Դͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ���ź�ͼ��Ŀ�Ⱥ͸߶�
	int new_w = (int)(w * xratio + 0.5);
	int new_h = (int)(h * yratio + 0.5);

	// ������ͼ��ÿ�е��ֽ�����������4�ı�����
	int new_LineBytes = (new_w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// Ϊ��ͼ������ڴ�
	BITMAPINFO* new_lpBitsInfo;
	LONG new_size = 40 + 1024 + new_h * new_LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(new_size)))
		return;

	// ����BMP��Ϣͷ�͵�ɫ��
	memcpy(new_lpBitsInfo, lpBitsInfo, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

	// ������Ϣͷ��������
	new_lpBitsInfo->bmiHeader.biWidth = new_w;
	new_lpBitsInfo->bmiHeader.biHeight = new_h;

	// �ҵ�Դͼ��������ʼλ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// �ҵ���ͼ��������ʼλ��
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, i0, j0;
	BYTE *pixel, *new_pixel;

	// ���ӳ��
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < new_h; i++)
	{
		// ���ͼ��ÿ�н��в���
		for(j = 0; j < new_w; j++)
		{
			// ָ����ͼ���i�У���j�����ص�ָ��
			new_pixel = lpNewBits + new_LineBytes * (new_h - 1 - i) + j;

			// �����������Դͼ���е����꣨��������ȡ����0�ײ�ֵ��
			i0 = (int)(i / yratio + 0.5);
			j0 = (int)(j / xratio + 0.5);

			pixel = lpBits + LineBytes * (h - 1 - i0) + j0;
			*new_pixel = *pixel;

		}
	}

	//�ͷ�ԭͼ��
	free(lpBitsInfo);

	//����Ϊ��ͼ��
	lpBitsInfo = new_lpBitsInfo;
}

BYTE Interpolation (float,float);
void Rotate(int angle)
{
	// Դͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ����Դͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ��ת�Ƕȣ����ȣ�
	float RotateAngle = (float)(angle * 3.141592654 / 180.0);
	
	// ������ת�Ƕȵ�����
	float Sina = (float) sin((double)RotateAngle);
	
	// ������ת�Ƕȵ�����
	float Cosa = (float) cos((double)RotateAngle);
	
	// ����ԭͼ���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float X1 = (float) (-(w - 1) / 2);
	float Y1 = (float) ( (h - 1) / 2);
	float X2 = (float) ( (w - 1) / 2);
	float Y2 = (float) ( (h - 1) / 2);
	float X3 = (float) (-(w - 1) / 2);
	float Y3 = (float) (-(h - 1) / 2);
	float X4 = (float) ( (w - 1) / 2);
	float Y4 = (float) (-(h - 1) / 2);
	
	// ������ͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float newX1 =  Cosa * X1 + Sina * Y1;
	float newY1 = -Sina * X1 + Cosa * Y1;
	float newX2 =  Cosa * X2 + Sina * Y2;
	float newY2 = -Sina * X2 + Cosa * Y2;
	float newX3 =  Cosa * X3 + Sina * Y3;
	float newY3 = -Sina * X3 + Cosa * Y3;
	float newX4 =  Cosa * X4 + Sina * Y4;
	float newY4 = -Sina * X4 + Cosa * Y4;

	// ������ת���ͼ��ʵ�ʿ�Ⱥ͸߶�
	int new_w = (int) (max(fabs(newX4 - newX1), fabs(newX3 - newX2)) + 0.5);
	int new_h = (int) (max(fabs(newY4 - newY1), fabs(newY3 - newY2)) + 0.5);

	// ������ͼ����ÿ�е��ֽ�����������4�ı�����
	int new_LineBytes =  (new_w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// Ϊ��ͼ������ڴ�
	BITMAPINFO* new_lpBitsInfo;
	LONG new_size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + new_h * new_LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(new_size)))
		return;

	// ����BMP��Ϣͷ�͵�ɫ��
	memcpy(new_lpBitsInfo, lpBitsInfo, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

	// ������Ϣͷ��������
	new_lpBitsInfo->bmiHeader.biWidth = new_w;
	new_lpBitsInfo->bmiHeader.biHeight = new_h;

	// �ҵ�Դͼ��������ʼλ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	// �ҵ���ͼ��������ʼλ��
	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	// �������������������Ժ�ÿ�ζ�������
	float f1 = (float) (-0.5 * (new_w - 1) * Cosa - 0.5 * (new_h - 1) * Sina + 0.5 * (w - 1));
	float f2 = (float) ( 0.5 * (new_w - 1) * Sina - 0.5 * (new_h - 1) * Cosa + 0.5 * (h - 1));

	int i, j;
	float i0, j0;
	BYTE *pixel, *new_pixel;

	// ���ӳ��
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < new_h; i++)
	{
		// ���ͼ��ÿ�н��в���
		for(j = 0; j < new_w; j++)
		{
			// ָ����ͼ���i�У���j�����ص�ָ��
			new_pixel = lpNewBits + new_LineBytes * (new_h - 1 - i) + j;

			// �����������Դͼ���е�����
			i0 = (-((float) j) * Sina + ((float) i) * Cosa + f2 + (float) 0.5);
			j0 = ( ((float) j) * Cosa + ((float) i) * Sina + f1 + (float) 0.5);

			// �ж��Ƿ���Դͼ��Χ��
			if ((j0 >= 0) && (j0 < w) && (i0 >= 0) && (i0 < h))
			{
				// ָ��Դͼ���i0�У���j0�����ص�ָ��
	//			pixel = lpBits + LineBytes * (h - 1 - (int)i0) + (int)j0;
				
				// �������أ�0�ײ�ֵ��
	//			*new_pixel = *pixel;

				// һ�ײ�ֵ
				*new_pixel = Interpolation(j0, i0);
			}
			else
			{
				// ����Դͼ��û�е����أ�ֱ�Ӹ�ֵΪ0
				*new_pixel = 0;
			}
		}
	}

	//�ͷ�ԭͼ��
	free(lpBitsInfo);

	//����Ϊ��ͼ��
	lpBitsInfo = new_lpBitsInfo;

}

BYTE Interpolation (float x, float y)
{
	// �ĸ����ٽ����ص�����(i1, j1), (i2, j1), (i1, j2), (i2, j2)
	int	i1, j1, i2, j2;
	
	// �ĸ����ٽ�����ֵ
	BYTE f1, f2, f3, f4;
	
	// ������ֵ�м�ֵ
	BYTE f12, f34;

	//ͼ��Ŀ�Ⱥ͸߶�
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	// ͼ��ÿ�е��ֽ���
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	// ͼ��������ʼλ��
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	
	// ����һ��ֵ���������������С�ڸ�ֵʱ��Ϊ������ͬ
	float EXP = (float) 0.0001;
	
	// �����ĸ����ٽ����ص�����
	i1 = (int)x;
	i2 = i1 + 1;
	j1 = (int)y;
	j2 = j1 + 1;

	// ���ݲ�ͬ����ֱ���
	if( (x < 0) || (x > w - 1) || (y < 0) || (y > h - 1))
	{
		// Ҫ����ĵ㲻��Դͼ��Χ�ڣ�ֱ�ӷ���0��
		return 0;
	}
	else
	{
		if (fabs(x - w + 1) <= EXP)
		{
			// Ҫ����ĵ���ͼ���ұ�Ե��
			if (fabs(y - h + 1) <= EXP)
			{
				// Ҫ����ĵ�������ͼ�������½���һ�����أ�ֱ�ӷ��ظõ�����ֵ
				f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
				return f1;
			}
			else
			{
				//��ͼ���ұ�Ե���Ҳ������һ��
				f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
				f3 = *(lpBits + LineBytes * (h - 1 - j1) + i2);
				
				//ֱ��һ�β�ֵ���ɣ����ز�ֵ���
				return (BYTE)((f1 + (y - j1) * (f3 - f1)));
			}
		}
		else if (fabs(y - h + 1) <= EXP)
		{
			// Ҫ����ĵ���ͼ���±�Ե���Ҳ������һ��
			f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
			f2 = *(lpBits + LineBytes * (h - 1 - j2) + i1);
			
			// ֱ��һ�β�ֵ���ɣ����ز�ֵ���
			return (BYTE)((f1 + (x - i1) * (f2 - f1)));
		}
		else
		{
			// �����ĸ����ٽ�����ֵ
			f1 = *(lpBits + LineBytes * (h - 1 - j1) + i1);
			f2 = *(lpBits + LineBytes * (h - 1 - j2) + i1);
			f3 = *(lpBits + LineBytes * (h - 1 - j1) + i2);
			f4 = *(lpBits + LineBytes * (h - 1 - j2) + i2);
			
			// ��ֵ1
			f12 = (BYTE)(f1 + (x - i1) * (f2 - f1));
			
			// ��ֵ2
			f34 = (BYTE)(f3 + (x - i1) * (f4 - f3));
			
			// ��ֵ3
			return (BYTE)(f12 + (y - j1) * (f34 - f12));
		}
	}
}