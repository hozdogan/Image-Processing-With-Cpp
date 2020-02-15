
#include<Windows.h>
#include<iostream>
#include <windows.h>
#include <iostream>
#include<atlstr.h>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<math.h>

using namespace std;

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	// declare bmp structures 
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;

	// andinitialize them to zero
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;		// number of bytes to start of bitmap bits

								// fill the infoheader

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;			// we only have one bitplane
	info.biBitCount = 24;		// RGB mode is 24 bits
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;		// can be 0 for 24 bit images
	info.biXPelsPerMeter = 0x0ec4;     // paint and PSP use this values
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;			// we are in RGB mode and have no palette
	info.biClrImportant = 0;    // all colors are important

								// now we open the file to write to
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == NULL) {
		CloseHandle(file);
		return false;
	}
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write infoheader
	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}

	// and close file
	CloseHandle(file);

	return true;
} // SaveBMP

BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	BYTE* newbuf = new BYTE[width*height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11*Buffer[bufpos + 2] + 0.59*Buffer[bufpos + 1] + 0.3*Buffer[bufpos]);
		}

	return newbuf;
}//ConvetBMPToIntensity

BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long% newsize)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// now we have to find with how many bytes
	// we have to pad for the next DWORD boundary	

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	// we can already store the size of the new padded buffer
	newsize = height * psw;

	// and create new buffer
	BYTE* newbuf = new BYTE[newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, newsize);
	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			bufpos = row * width + column;     // position in original buffer
			newpos = (height - row - 1) * psw + column * 3;           // position in padded buffer
			newbuf[newpos] = Buffer[bufpos];       //  blue
			newbuf[newpos + 1] = Buffer[bufpos];   //  green
			newbuf[newpos + 2] = Buffer[bufpos];   //  red
		}

	return newbuf;
} //ConvertIntensityToBMP

BYTE* DrawShape(BYTE* Buffer, int width, int height, int x, int y, int w_size, int h_size)
{

	for (int i = 1; i <= h_size; i++) {

		for (int j = 1; j <= w_size; j++)
		{
			Buffer[(y + i)*width + x + j] = 0;
		}
	}
	return Buffer;
	//ConvertIntensityToBMP
}
BYTE* Crop(BYTE* Buffer, int buffer_width, int Box_w,int Box_h,int x,int y)
{
	BYTE* newbuf = new BYTE[Box_w*Box_h*3];
	
	long newpos = 0;
	long bufpos = 0;
	for (unsigned int row = 0; row < Box_h; row++)
	{
		for (unsigned int column = 0; column < Box_w; column++)
		{
			newpos = row * Box_w + column;
			bufpos = ((y + row)*buffer_width+(x-1)+column)*3;//renkli kýrpma
			newbuf[3*newpos] = Buffer[bufpos];
			newbuf[3*newpos + 1] = Buffer[bufpos+1];
			newbuf[3 * newpos + 2] = Buffer[bufpos+2];
			
		}
	}
	return newbuf;
}
BYTE* BinaryImage(BYTE* Buffer, int Width, int Height,int Threshold)
{
	
	for (int j = 0; j < Width*Height; j++)
	{
		if (int(Buffer[j] < Threshold))
		{
			Buffer[j] = 0;
		}
		if (int(Buffer[j] >= Threshold))
		{
			Buffer[j] = 255;
		}
	}
	return Buffer;//binary*/
	
	
}
int D2_K_Mean_Clustering(BYTE* Buffer, int Width, int Height)//hocanýn istediði
{
	int T1, T2;
	int T1Complement,T2Complement,Mean;
	FLOAT  SumT1=0.0f, SumT2=0.0f,sumindisT1=0.0f,sumindisT2=0.0f;
	int *Hist = new int[256];
	for (int i = 0; i < 256; i++)
	{
		Hist[i] = 0;
	}
	for (int i = 0; i < Width*Height; i++)
	{
		Hist[(int)Buffer[i]]++;
	}


	srand(time(NULL));
	T1 = rand() % 256;
	T2 = rand() % 256;
	if (T1 == T2)
	{
		T1 = rand() % 256;
		T2 = rand() % 256;
	}

	while (true)
	{
		
		Mean = (T1 + T2) / 2;
		for (int i = 0; i < Mean; i++)
		{
			SumT1 += i * Hist[i];
			sumindisT1 += Hist[i];
		}
		T1Complement = SumT1/ sumindisT1;
		for (int j = Mean; j < 256; j++)
		{
			SumT2 += j * Hist[j];
			sumindisT2 += Hist[j];
		}
		T2Complement = SumT2 / sumindisT2;
		if (T1 == T1Complement && T2 == T2Complement)
		{
			return Mean;
			break;
		}
		else 
		{
			Mean = 0;
			sumindisT1 = 0.0f;
			sumindisT2 = 0.0f;
			SumT1 = 0.0f;
			SumT2 = 0.0f;
			T1 = T1Complement;
			T2 = T2Complement;
			T2Complement = 0.0f;
			T1Complement = 0.0f;
		}

	}
	
}
BYTE* RGBScale(BYTE* Buffer,int width,int height,long newsize)
{
	//BYTE* newbuf = new BYTE[Size];
	
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// now we have to find with how many bytes
	// we have to pad for the next DWORD boundary	

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	// we can already store the size of the new padded buffer
	newsize = height * psw;

	// and create new buffer
	BYTE* newbuf = new BYTE[newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, newsize);
	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			bufpos = row * width + column;     // position in original buffer
			newpos = (height - row - 1) * psw + column * 3;           // position in padded buffer
			newbuf[newpos] = Buffer[3*bufpos];       //  blue
			newbuf[newpos + 1] = Buffer[3*bufpos+1];   //  green
			newbuf[newpos + 2] = Buffer[3*bufpos+2];   //  red
		}

	return newbuf;
}

BYTE* Dilation(BYTE* Buffer, int Width, int Height, BYTE* Mask, int m_w, int m_h)
{

	int a, b,tep;
	int maskpw = (m_w - (m_w + 1 / 2)) * 2;
	int maskph = (m_h - (m_h + 1 / 2)) * 2;
	int w_new = Width + maskpw;
	int h_new = Height + maskph;
	//*******degerlerin 0 1 yapýlmasý
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep] == 0)
			{
				Buffer[tep] = 1;
			}
			else if (Buffer[tep] == 255)
			{
				Buffer[tep] = 0;
			}
		}
	}//end

	BYTE** newbuf = new BYTE*[w_new];//mask n*n olabilir belli bir degere kadar
	BYTE** Maske = new BYTE*[m_w];
	BYTE** tempbuf = new BYTE*[w_new];
	BYTE* tekbuf = new BYTE[Width*Height];
	for (int i = 0; i < m_w; i++)
	{
		Maske[i] = new BYTE[m_h];
	}
	for (int i = 0; i < w_new; i++)
	{
		newbuf[i] = new BYTE[h_new];
	}
	for (int i = 0; i < w_new; i++)
	{
		tempbuf[i] = new BYTE[h_new];
	}
	//maskenin 2 boyuta çevrilmesi
	for (int row = 0; row < m_h; row++)
	{
		for (int column = 0; column < m_w; column++)
		{
			int matemp = row * m_w + column;
			Maske[(matemp - column) / m_w][column] = Mask[matemp];
		}
	}
	
	for (int row = 0; row < h_new; row++)
	{
		for (int column = 0; column < w_new; column++)
		{
			newbuf[row][column] = 0;
			tempbuf[row][column] = 0;
		}
	}
	for (int row = maskph/2; row < h_new - (maskph/2); row++)
	{
		for (int column = maskpw/2; column <w_new -(maskpw/2); column++)
		{
			int temp = row * w_new-(maskpw/2) + column;
			newbuf[(temp - column) / w_new-(maskpw/2)][column] = Buffer[temp];
		}
	}
	//konvolüsyon 
	for (int i = 0; i <  w_new-(m_w-1); i++)
	{
		for (int j = 0; j <h_new-(m_h-1); j++)
		{

			for (a = i; a <i+m_w; a++)
			{
				for (b = j; b <j+ m_h; b++)
				{
					
					if ( newbuf[i+1][j+1]==1)
					{	
						tempbuf[a][b]= (newbuf[a][b] || Maske[a - i][b - j]);
						
					}
					
						
				}
			}
			//orlama iþlemi
			
		}
	}
	//end guya konvolüsyon
	for (int row = maskph/2; row < h_new-(maskph/2); row++)
	{
		for (int column = maskpw/2; column < w_new-(maskpw/2); column++)
		{
			int tp = row * (w_new - (maskpw/2)) + column;
			tekbuf[tp] = tempbuf[row][column];
		}
	}

	for (int row = 1; row < Height-1; row++)
	{
		for (int column = 1; column < Width-1; column++)
		{
			tep = row * Width + column;
			if (tekbuf[tep] == 1)
			{
				tekbuf[tep] = 0;
			}
			else if (tekbuf[tep] == 0)
			{
				tekbuf[tep] = 255;
			}
		}
	}
	
	return tekbuf;
}

BYTE* Erosion(BYTE* Buffer, int Width, int Height, BYTE* Mask, int m_w, int m_h)
{
	int a, b,equal=0,tep;
	int maskpw = (m_w - (m_w + 1 / 2)) * 2;
	int maskph = (m_h - (m_h + 1 / 2)) * 2;
	int countstructualelementsnumberone=0;
	int w_new = Width + maskpw;
	int h_new = Height + maskph;
	//deger degisimi yorum satýrýna al yanlýþ cýkarsa
	
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep] == 0)
			{
				Buffer[tep] = 1;
			}
			else if (Buffer[tep] == 255)
			{
				Buffer[tep] = 0;
			}
		}
	}//end





	BYTE** newbuf = new BYTE*[w_new];//mask 3*3 olursaki halidir bu
	BYTE** Maske = new BYTE*[m_w];
	BYTE** tempbuf = new BYTE*[w_new];
	BYTE* tekbuf = new BYTE[Width*Height];
	for (int i = 0; i < m_w; i++)
	{
		Maske[i] = new BYTE[m_h];
	}
	for (int i = 0; i < w_new; i++)
	{
		newbuf[i] = new BYTE[h_new];
	}
	for (int i = 0; i < w_new; i++)
	{
		tempbuf[i] = new BYTE[h_new];
	}
	
	//maskenin 2 boyuta çevrilmesi
	for (int row = 0; row < m_h; row++)
	{
		for (int column = 0; column < m_w; column++)
		{
			int matemp = row * m_w + column;
			if (Mask[matemp] == 1)
			{
				countstructualelementsnumberone++;
			}
			Maske[(matemp - column) / m_w][column] = Mask[matemp];
		}
	}

	for (int row = 0; row < h_new; row++)
	{
		for (int column = 0; column < w_new; column++)
		{
			newbuf[row][column] = 0;
			tempbuf[row][column] = 0;
		}
	}
	for (int row = maskph/2; row < h_new - (maskph / 2); row++)
	{
		for (int column = maskpw/2; column <w_new - (maskpw / 2); column++)
		{
			int temp = row * w_new - (maskpw / 2) + column;
			newbuf[(temp - column) / w_new - (maskpw / 2)][column] = Buffer[temp];
		}
	}
	//konvolüsyon 
	for (int i = 0; i < w_new - (m_w-1 ); i++)
	{
		for (int j = 0; j <h_new - (m_h-1); j++)
		{

			for (a = i; a <i + m_w ; a++)
			{
				for (b = j; b <j + m_h ; b++)
				{

					/*if (newbuf[i + 1][j + 1] == 1)
					{
						tempbuf[a][b] = (newbuf[a][b] && Maske[a - i][b - j]);
						//dilation or iþlemi ama 0 siyah renk oldugu için 1 ler fazla olursa maske azalýr onun için tersi olayý yapacagýz
					}*/
					if(Maske[a - i][b - j] ==1&& newbuf[a][b]==1)//ikiside bire eþitse
					{
						equal++;
					}
						
				}
			}
			//andleme iþlemi
			if (equal >=countstructualelementsnumberone)
			{
				tempbuf[i + 1][j + 1] = 1;
				equal = 0;
			}
			else
			{
				tempbuf[i + 1][j + 1] = 0;
				equal = 0;
			}
		}
	}
	//end guya konvolüsyon
	for (int row = maskph/2; row < h_new - (maskph / 2); row++)
	{
		for (int column = maskpw/2; column < w_new - (maskpw / 2); column++)
		{
			int tp = row * (w_new - (maskpw / 2)) + column;
			tekbuf[tp] = tempbuf[row][column];
		}
	}

	for (int row = 1; row < Height-1; row++)
	{
		for (int column = 1; column < Width-1; column++)
		{
			tep = row * Width + column;
			if (tekbuf[tep] == 1)
			{
				tekbuf[tep] = 0;
			}
			else if (tekbuf[tep] == 0)
			{
				tekbuf[tep] = 255;
			}
		}
	}

	
	return tekbuf;
	
}
BYTE* MirrorImage(BYTE* Buffer, long size)
{
	long newpos = 0;
	BYTE* newbuf = new BYTE[size];
	for (int i = size - 1; i >= 0; i--)
	{
		newbuf[newpos] = Buffer[i];
		newpos++;
	}
	return newbuf;


}
BYTE* MULTID_K_Means_Clustering(BYTE* Buffer, int Width, int Height, int Tnumber)//raw_intenste
{
	
	
	int *TComparray = new int[Tnumber];
	int temp,tp,control=0;//tp t1 2 3 degerimi onu tutuyor
	FLOAT MinT = 0.0f;
	int *Thresholdarraynumber = new int[Tnumber];
	FLOAT *Means = new FLOAT[Tnumber];
	int *TArrays = new int[Tnumber];
	BYTE *tempbuf = new BYTE[Width*Height];
	int *SumT = new int[Tnumber];
	

	for (int i = 0; i < Tnumber; i++)//dizi 0 lama
	{
		Thresholdarraynumber[i] = 0;
		Means[i] = 0;
		TComparray[i] = 0;
		SumT[i] = 0;
		TArrays[i] = 0;
	}
	srand(time(NULL));
	for (int i = 0; i < Tnumber; i++)//sayi üretilmesi
	{
		TArrays[i] = rand() % 256;
		//TArrays[i] = 256/(i+1);
	}

	while (true)
	{
		for (int row = 0; row < Height; row++)
		{
			for (int column = 0; column < Width; column++)
			{
				temp = row * Width + column;
				for (int j = 0; j < Tnumber; j++)
				{
					Means[j] = sqrt(pow((Buffer[temp] - TArrays[j]), 2));
				}
				MinT = Means[0];
				tp = 0;
				for (int j = 1; j < Tnumber; j++)//en kucuk uzakligin bulunmasi
				{
					if (Means[j] < MinT)
					{
						MinT = Means[j];
						tp = j;
					}

				}
				tempbuf[temp] = tp;
			}
		}

		for (int i = 0; i < Width*Height; i++)
		{
			Thresholdarraynumber[tempbuf[i]]++;//pixel sayýsý etiket toplam
			for (int j = 0; j < Tnumber; j++)
			{
				if (tempbuf[i] == j)
				{
					SumT[j] += Buffer[i];
				}
			}
		}
		for (int j = 0; j < Tnumber; j++)
		{
			if (Thresholdarraynumber[j] == 0)
			{
				TComparray[j] = SumT[j] / (Thresholdarraynumber[j]+1);
			}
			else
			{
				TComparray[j] = SumT[j] / Thresholdarraynumber[j];
			}
			
		}
		
		for (int i = 0; i < Tnumber; i++)
		{
			if (TArrays[i] == TComparray[i])
			{
				control++;
			}
		}
		if (control <=Tnumber)
		{
			for (int row = 0; row < Height; row++)
			{
				for (int column = 0; column < Width; column++)
				{
					temp = row * Width + column;
					Buffer[temp] = TArrays[tempbuf[temp]];
				}
			}
			break;
		}
		else
		{
			for (int i = 0; i < Tnumber; i++)
			{
				TArrays[i] = TComparray[i];
			}
		}
	}

	return Buffer;
}
BYTE* MultD_K_Means_Clustering(BYTE* Buffer, int Width, int Height,int Tnumber)
{
	
	int *TComparray = new int[Tnumber*3];
	int temp, tp, control = 0;//tp t1 2 3 degerimi onu tutuyor
	FLOAT MinT = 0.0f;
	int *Thresholdarraynumber = new int[Tnumber];
	FLOAT *Means = new FLOAT[Tnumber];
	int *TArrays = new int[Tnumber*3];
	BYTE *tempbuf = new BYTE[Width*Height];
	int *SumT = new int[Tnumber*3];

	for (int i = 0; i < Tnumber; i++)
	{
		Means[i] = 0.0f;
		SumT[3 * i] = 0;
		SumT[3 * i + 1] = 0;
		SumT[3 * i + 2] = 0;
		TComparray[3 * i] = 0;
		TComparray[3 * i+1] = 0;
		TComparray[3 * i+2] = 0;
		Thresholdarraynumber[i] = 0;
		TArrays[3 * i] = 0;
		TArrays[3 * i+1] = 0;
		TArrays[3 * i+2] = 0;

	}
	srand(time(NULL));

	for (int i = 0; i < Tnumber; i++)
	{
		
		TArrays[3 * i] = rand() % 256;
		TArrays[3 * i + 1] = rand() % 256;
		TArrays[3 * i + 2] = rand()%256;
	}


	while (true)
	{
		for (int row = 0; row < Height; row++)
		{
			for (int column = 0; column < Width; column++)
			{
				temp = row * Width + column;
				for (int j = 0; j < Tnumber; j++)
				{
					Means[j] = sqrt(pow((Buffer[3 * temp] - TArrays[3 * j] + Buffer[3 * temp + 1] - TArrays[3 * j + 1] + Buffer[3 * temp + 2] - TArrays[3 * j + 2]),2));//xr-tr xg-tg xb-tb
				}
				MinT = Means[0];
				tp = 0;
				for (int i = 1; i < Tnumber; i++)
				{
					if (Means[i] < MinT)
					{
						MinT = Means[i];
						tp = i;
					}
				}
				tempbuf[temp] = tp;
			}
		}
		for (int row = 0; row < Height; row++)
		{
			for (int column = 0; column < Width; column++)
			{
				temp = row * Width + column;
				Thresholdarraynumber[tempbuf[temp]]++;
				for (int j = 0; j < Tnumber; j++)
				{
					if (tempbuf[temp] == j)
					{
						SumT[3 * j+2] += Buffer[3 * temp+2];
						SumT[3 * j + 1] += Buffer[3 * temp + 1];
						SumT[3 * j] += Buffer[3 * temp];
					}
				}
			}
		}
		for (int j = 0; j < Tnumber; j++)
		{
			if (Thresholdarraynumber[j] == 0)
			{
				TComparray[3 * j+2] = SumT[3 * j+2] / (Thresholdarraynumber[j] + 1);
				TComparray[3 * j + 1] = SumT[3 * j + 1] / (Thresholdarraynumber[j] + 1);
				TComparray[3 * j ] = SumT[3 * j] / (Thresholdarraynumber[j] + 1);
			}
			else
			{
				TComparray[3 * j + 2] = SumT[3 * j + 2] / Thresholdarraynumber[j];
				TComparray[3 * j + 1] = SumT[3 * j + 1] / Thresholdarraynumber[j];
				TComparray[3 * j] = SumT[3 * j] / Thresholdarraynumber[j];
			}
		}
		for (int i = 0; i < Tnumber; i++)
		{
			if (TArrays[i] == TComparray[i])
			{
				control++;
			}
		}
		if (control <= Tnumber)
		{
			for (int row = 0; row < Height; row++)
			{
				for (int column = 0; column < Width; column++)
				{
					temp = row * Width + column;
					Buffer[3*temp+2] = TArrays[3*tempbuf[temp]+2];
					Buffer[3 * temp+1] = TArrays[3 * tempbuf[temp]+1];
					Buffer[3 * temp] = TArrays[3 * tempbuf[temp]];
					
				}
			}
			break;
		}
		else
		{
			for (int i = 0; i < Tnumber; i++)
			{
				TArrays[3*i+2] = TComparray[3*i+2];
				TArrays[3 * i+1] = TComparray[3*i+1];
				TArrays[3 * i] = TComparray[3*i];
			}
		}
	}//end loop
	return Buffer;



}
BYTE* Boundary(BYTE* Buffer, BYTE* DBuffer, int Width, int Height)
{
	BYTE* newbuf = new BYTE[Width*Height];
	int tep;
	for (int row = 0; row < Height; row++)//boundary
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			
		}
	}
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if(Buffer[tep] == 255)
			{
				Buffer[tep] = 1;
			}
			if (DBuffer[tep] == 255)
			{
				DBuffer[tep] = 1;
			}

		}
	}//end
	
	


	for (int row = 0; row < Height; row++)//boundary
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			newbuf[tep] = (Buffer[tep] ^ DBuffer[tep]);
		}
	}

	//siyah beyaz renk atamasý
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (newbuf[tep] == 1)
			{
				newbuf[tep] = 0;
			}
			else if (newbuf[tep] == 0)
			{
				newbuf[tep] = 255;
			}
		}
	}
	return newbuf;

}
BYTE* CCL(BYTE* Buffer, int Width, int Height)
{
	int temp,Label=2,tep;
	BYTE* newbuf = new BYTE[Width*Height];
	
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep] == 0)
			{
				Buffer[tep] = 1;
			}
			else if (Buffer[tep] == 255)
			{
				Buffer[tep] = 0;
			}
		}
	}//end
	
	
	for (int row = 1; row < Height; row++)
	{
		for (int column = 1; column < Width; column++)
		{
			temp = row * Width + column;
			newbuf[temp] = Buffer[temp];
		}
	}
	//olmazsa olmadý demektir
	for (int row = 0; row < Height; row++)
	{
		tep = row * Width;
		newbuf[tep] = 0;
	}
	for (int column = 0; column < Width; column++)
	{
		newbuf[column] = 0;
	}

	for (int row = 1; row < Height; row++)
	{
		for (int column = 1; column < Width; column++)
		{
			temp = row * Width + column;
			
			if (newbuf[temp] == 1)
			{
				if (newbuf[temp - Width] == 0 && newbuf[temp - 1] == 0)
				{
					newbuf[temp] = Label;
					Label++;
				} 
			
				else if (newbuf[temp - Width] != 0 && newbuf[temp - 1]!= 0)
				{
					if (newbuf[temp - 1] == newbuf[temp - Width])
					{
						newbuf[temp] = newbuf[temp - Width];
					}
					else { newbuf[temp] = 1; }//collision
				}
				else if (newbuf[temp - 1] == 0 || newbuf[temp - Width] == 0)
				{
					
					if (newbuf[temp - 1] >0)
					{
						newbuf[temp] = newbuf[temp - 1];
					}
					else if (newbuf[temp - Width] >0)
					{
						newbuf[temp] = newbuf[temp - Width];
					}
				}
				
			}//etiket kosullarýnýn bitiþi
			
		}
	}
	for (int row = 1; row < Height; row++)
	{
		for (int column = 1; column < Width; column++)
		{
			temp = row * Width + column;
			if (newbuf[temp] == 1)
			{
				if (newbuf[temp - 1] != 0 && newbuf[temp - Width] != 0)
				{
					if (newbuf[temp - 1] < newbuf[temp - Width])
					{
						newbuf[temp] = newbuf[temp - 1];
						for (int r = 1; r < Height; r++)
						{
							for (int col = 1; col < Width; col++)
							{
								tep = r * Width + col;
								if (newbuf[tep] == newbuf[temp - Width])
								{
									newbuf[tep] = newbuf[temp - 1];
								}
							}
						}
					}
					else if (newbuf[temp - Width] < newbuf[temp - 1])
					{
						newbuf[temp] = newbuf[temp - Width];
						for (int r = 1; r < Height; r++)
						{
							for (int col = 1; col < Width; col++)
							{
								tep = r * Width + col;
								if (newbuf[tep] == newbuf[temp - 1])
								{
									newbuf[tep] = newbuf[temp - Width];
								}
							}
						}
					}
					else if (newbuf[temp - 1] == newbuf[temp - Width])
					{
						newbuf[temp] = newbuf[temp - Width];
					}

				}
				else if (newbuf[temp - 1] == 0 || newbuf[temp - Width] == 0)
				{
					if (newbuf[temp - 1] == 0)
					{
						newbuf[temp] = newbuf[temp - Width];
					}
					else if (newbuf[temp - Width] == 0)
					{
						newbuf[temp] = newbuf[temp - 1];
					}
				}

			}

		}
	}//end labeling collision
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			if (newbuf[temp] == 0)
			{
				newbuf[temp] = 255;
			}
		}
	}
	
	return newbuf;
}
BYTE* CCLColoring(BYTE* Buffer,BYTE* CBuffer, int Width, int Height,int Size)
{
	int tep, Count = 1,temp = 2,tp;

	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep] == 255)
			{
				Buffer[tep] = 0;
			}
			
		}
	}//background 0
	
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep]!=0)
			{
				if (Buffer[tep] > temp)
				{
					Count++;
					temp = Buffer[tep];
				}
			}
		}
	}//sayýsýný bulma
	temp = 2;
	
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep] != 0&& Buffer[tep] > temp)
			{
				temp++;
				for (int r = 0; r < Height; r++)
				{
					for (int col = 0; col < Width; col++)
					{
						tp = r * Width + col;
						if (Buffer[tp] == Buffer[tep]) 
						{
							Buffer[tp] = temp;
						}
							
					}
				}
				
			}
			
		}
	}
	int* Color = new int[Count*3];

	srand(time(NULL));

	for (int i = 0; i < Count; i++)
	{
		Color[3 * i] = 1+rand()%255;
		Color[3 * i + 1] = 1+rand() % 255;
		Color[3 * i + 2] =  1+rand() % 255;
	}//random color
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * (Width) + column;
			if (Buffer[tep] != 0)
			{
				CBuffer[3 * tep] = Color[3 * (Buffer[tep])-2];
				CBuffer[3 * tep + 1] = Color[3 * (Buffer[tep]-2) + 1];
				CBuffer[3 * tep + 2] = Color[3 * (Buffer[tep]-2) + 2];
			}
			if (Buffer[tep] == 0)
			{
				CBuffer[3 * tep] = 255;
				CBuffer[3 * tep + 1] = 255;
				CBuffer[3 * tep + 2] = 255;
			}
		}
	}//renklendirme bitti
	
	return CBuffer;
}
int CounterObject(BYTE* Buffer, int Width, int Height)
{
	int Label = 2, tep,Count=1;

	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			if (Buffer[tep] == 255)
			{
				Buffer[tep] = 0;
			}
		}
	}//background 0

	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row *Width + column;
			
			if (Buffer[tep] != 0)
			{
				if (Buffer[tep] > Label)
				{
					Count++;
					Label = Buffer[tep];
				}
				
			}
			
		}
	}
	return Count;
}

int* Convolution(BYTE* Buffer, int Width, int Height, int* Mask, int m_w, int m_h)
{
	int sum = 0,tep;
	int w_new = Width - (m_w - 1);
	int h_new = Height - (m_h - 1);
	

	int** newbuf = new int*[Width];//mask 3*3 olursaki halidir bu
	int** Maske = new int*[m_w];
	int** tempbuf = new int*[w_new];
	int* tekbuf = new int[w_new*h_new];
	for (int i = 0; i < m_w; i++)
	{
		Maske[i] = new int[m_h];
	}
	for (int i = 0; i <Width; i++)
	{
		newbuf[i] = new int[Height];
	}
	for (int i = 0; i < w_new; i++)
	{
		tempbuf[i] = new int[h_new];
	}

	//maskenin 2 boyuta çevrilmesi
	for (int row = 0; row < m_h; row++)
	{
		for (int column = 0; column < m_w; column++)
		{
			int matemp = row * m_w + column;
			Maske[(matemp - column) / m_w][column] = Mask[matemp];
		}
	}
	for (int row = 0; row < Height; row++)
	{
		for (int column = 0; column < Width; column++)
		{
			tep = row * Width + column;
			newbuf[(tep - column) / Width][column] = Buffer[tep];
		}
	}
	
	for (int row = 0; row <h_new; row++)
	{
		for (int column = 0; column < w_new; column++)
		{
			tempbuf[row][column] = 0;
		}
	}
	
	for (int i = 0; i < h_new; i++)
	{
		for (int j = 0; j < w_new; j++)
		{
			for (int a = i; a < i+m_h; a++)
			{
				for (int b = j; b < j + m_w; b++)
				{
					sum+=(newbuf[a][b] * Maske[a-i][b-j]);
				}
			}
			tempbuf[i][j] = abs(sum);
			sum = 0;
		}
	}

	for (int row = 0; row < h_new; row++)
	{
		for (int column = 0; column < w_new; column++)
		{
			tep = row * w_new + column;
			tekbuf[tep] = tempbuf[(tep-column)/w_new][column];
		}
	}
	return tekbuf;


}
double* edgeimage(int* buffer, int* buffer2, int maxvalue, int w_new, int h_new)
{

	double* retbuf = new double[w_new*h_new];
	int tep;
	for (int row = 0; row < h_new; row++)
	{
		for (int column = 0; column < h_new; column++)
		{
			tep = row * w_new + column;
			if (maxvalue == 1020)
			{
				retbuf[tep] = buffer[tep] / 4 + buffer2[tep] / 4;
				if (retbuf[tep] > 255)
				{
					retbuf[tep] /= 4;
				}
			}
			if (maxvalue == 765)//yani prewitt kullanýlmýssa
			{
				retbuf[tep] = buffer[tep] / 3 + buffer2[tep] / 3;
				if (retbuf[tep] > 255)
				{
					retbuf[tep] /= 3;
				}
			}
		}
	}
	return retbuf;
}
double* gradient(int* buffer, int* buffer2, int width, int height)
{
	int tep;
	double* anglebuf = new double[width*height];
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			tep = row * width + col;
			if (buffer[tep] == 0&&buffer2[tep]!=0)
			{
				anglebuf[tep] = 90;
			}
			else if (buffer[tep] == 0 && buffer2[tep] == 0)
			{
				anglebuf[tep] = 0;
			}
			else
			{
				anglebuf[tep] = atan(buffer2[tep] / buffer[tep])*(180 / 3.14);
			}
		}

	}
	return anglebuf;

}//açý fonksiyonu
double *nms(double* edge, double* angle, int width, int height)
{
	int tep;
	double* newbuf = new double[width*height];
	
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			tep = row * width + col;
			if (angle[tep] >= 0 && angle[tep] < 22.5)
			{
				if (edge[tep] > edge[tep +1] && edge[tep] > edge[tep-1])
				{

					newbuf[tep] = edge[tep];
				}
				else
				{
					newbuf[tep] = 0;
				}
			}
			
			else if (angle[tep]>=22.5&&angle[tep]<67.5)
			{

				if (edge[tep] > edge[tep + width-1] && edge[tep] > edge[tep - (width-1)])
				{
					newbuf[tep] = edge[tep];
				}
				else
				{
					newbuf[tep] = 0;
				}
				
			}//y=-x*/
			else if (angle[tep] >= 67.5)
			{

				if (edge[tep] > edge[tep + width] && edge[tep] > edge[tep - width])
				{
					
					newbuf[tep] = edge[tep];
				}
				else
				{
					newbuf[tep] = 0;
				}

			}//x=3*/

		}
	}

	return newbuf;

}
double* histerize_threshold(double* Buffer, int Width, int Height)//hocanýn istediði
{
	int tp;
			for (int row = 0; row < Height; row++)
			{
				for (int col = 0; col < Width; col++)
				{
					tp = row * Width + col;
					if (Buffer[tp] <=30)
					{
						Buffer[tp] = 0;
					}
					else if (Buffer[tp] >=150)
					{
						Buffer[tp] = 1;
					}
				}

			}
			return Buffer;
			
	
}
double* binaryedge(double* edge, double* angle, int width, int height)
{
	int tep;
	double* newbuf = new double[width*height];//edge=histerize image
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			tep = row * width + col;
			if (edge[tep] != 0 && edge[tep] != 1)
			{

				if (angle[tep] >= 0.0 && angle[tep] < 22.5)//komsularýndan biri bossa
				{


					if (edge[tep + width] == 0 && edge[tep -width] == 0)
					{
						edge[tep] = 0;
					}
					else if (edge[tep + width] == 1 && edge[tep - width] == 1)
					{
						edge[tep] = 1;
					}
					else
					{
						edge[tep] = rand()%2;
					}
				}//y=2*/


				else if (angle[tep] >=22.5&&angle[tep]<67.5)
				{

					if (edge[tep + width +1] == 0 && edge[tep - (width +1)] == 0)
					{
						edge[tep] = 0;
					}
					else if (edge[tep + width +1] == 1 && edge[tep - (width +1)] == 1)
					{
						edge[tep] = 1;
					}
					else
					{
						edge[tep]=rand()%2;
					}
				}//y=-x
				

				else if (angle[tep] >= 67.5)
				{
					if (edge[tep + 1] == 0 && edge[tep - 1] == 0)
					{
						edge[tep] = 0;
					}
					else if (edge[tep  +1] == 1 && edge[tep - 1] == 1)
					{
						edge[tep] = 1;
					}
					else
					{
						edge[tep] = rand()%2;
					}


				}//x=3*/
			}
		}
	}
	
	return edge;
}
