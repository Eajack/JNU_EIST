#include "stdafx.h"

LONG size = 0;

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
	DWORD LineBytes = (bi.biWidth * bi.biBitCount + 31)/32 * 4;

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

//����Ҷ�ֱ��ͼ���飨ͳ�Ƹ��Ҷȼ������ظ�����
void Histogram(LPBITMAPINFO lpDIB, DWORD H[])
{
	// ͼ��Ŀ�Ⱥ͸߶�
	int w = lpDIB->bmiHeader.biWidth;
	int h = lpDIB->bmiHeader.biHeight;

	// ����Դͼ����ÿ�е��ֽ�����������4�ı�����
	int LineBytes = (w * lpDIB->bmiHeader.biBitCount + 31)/32 * 4;

	// ָ��ͼ�����ݵ�ָ��
	BYTE *lpBits = (BYTE*)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];

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


#define H_HISTOGRAM 200
void DrawHistogram(CDC& dcMem, DWORD H[])
{
	CClientDC dc(NULL);

	CBitmap bmp; //�����ڴ��м�����ʱͼ���λͼ����
	bmp.CreateCompatibleBitmap(&dc,256,H_HISTOGRAM);//��������λͼ

	dcMem.Detach();
	dcMem.CreateCompatibleDC(&dc); //��������DC���������ڴ�DC 
	dcMem.SelectObject(&bmp); //��λͼѡ����ڴ�DC 

	CRect rect(0,0,256,H_HISTOGRAM);
	CBrush brush(RGB(200,200,200));
	dcMem.FillRect(rect, &brush);

	//��dcMem�л���ֱ��ͼ
	int i;
	DWORD max = 0;

	//���H�����е����ֵ
	for (i = 0; i < 256; i ++)
	{
		if (H[i] > max)
			max = H[i];
	}

	for (i = 0; i < 256; i ++)
	{
		dcMem.MoveTo(i, H_HISTOGRAM);
		dcMem.LineTo(i, H_HISTOGRAM - (int)(H[i] * H_HISTOGRAM / max));
	}
}

void Equalize(LPBITMAPINFO lpDIB)
{
	//����Ҷ�ֱ��ͼ
	DWORD H[256];
	Histogram(lpDIB, H);

	int i, j;
	int w = lpDIB->bmiHeader.biWidth;
	int h = lpDIB->bmiHeader.biHeight;
	DWORD temp;

	//�Ҷ�ӳ���
	BYTE Map[256];
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

	int LineBytes = (w * lpDIB->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE *lpBits = (BYTE*)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];
	BYTE* pixel;
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

void Specify(LPBITMAPINFO lpDIB, DWORD dst[])
{
	//����ԭͼֱ��ͼ
	DWORD src[256];
	Histogram(lpDIB, src);

	//�ۼ�ֱ��ͼ
	DWORD accum_scr[256];
	DWORD accum_dst[256];

	int i,j;
	DWORD temp;
	// �����ۼ�ֱ��ͼ
	for (i = 0; i < 256; i++)
	{
		temp = 0;
		for (j = 0; j <= i ; j++)
			temp += src[j];
		accum_scr[i] = temp;
	}
	for (i = 0; i < 256; i++)
	{
		temp = 0;
		for (j = 0; j <= i ; j++)
			temp += dst[j];
		accum_dst[i] = temp;
	}

	//����ԭʼͼ��Ŀ��ͼ���ۻ�ֱ��ͼ���Ҷȼ��Ĳ�ľ���ֵ 
	DWORD diff[256][256]; 
    for (j = 0; j < 256; j++)   
    {   
        for (i = 0; i < 256; i++)   
        {   
            diff[i][j] = abs(accum_scr[j] - accum_dst[i]);   
        }   
    }   
 	
	//�Ҷ�ӳ���
	BYTE Map[256];

    /*************************** GML ****************************/
    DWORD minValue = 0;   
    short lastStartY = 0, lastEndY = 0, startY = 0, endY = 0; 
	int k;
    for (i = 0; i < 256; i++)   
    {   
        minValue = diff[i][0];   
        for (j = 0; j < 256; j++)   
        {   
            if (minValue > diff[i][j])   
            {   
                endY = j;   
                minValue = diff[i][j];   
            }   
        }   
   
        if (startY != lastStartY || endY != lastEndY)   
        {   
            for (k = startY; k <= endY; k++)   
            {   
                Map[k] = i;//����ӳ���ϵ   
            }   
            lastStartY = startY;   
            lastEndY = endY;   
            startY = lastEndY + 1;   
        }   
    }   

	/*************************** SML ****************************/
/*	DWORD minX = 0;
	for (j = 0; j < 256; j ++)
	{
		minX = 0;
		minValue = diff[0][j];
		for (i = 1; i < 256; i++)
		{
			if (minValue > diff[i][j])
			{
				minValue = diff [i][j];
				minX = i;
			}
		}
		Map[j] = minX;
	}
*/

	int w = lpDIB->bmiHeader.biWidth;
	int h = lpDIB->bmiHeader.biHeight;
	int LineBytes = (w * lpDIB->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE *lpBits = (BYTE*)&lpDIB->bmiColors[lpDIB->bmiHeader.biClrUsed];
	BYTE* pixel;
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