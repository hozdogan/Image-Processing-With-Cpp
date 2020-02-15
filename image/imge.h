#pragma once
#include <windows.h>

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
bool  SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height);
BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long% newsize);
BYTE* DrawShape(BYTE* Buffer, int width, int height, int x, int y, int w_size, int h_size);
BYTE* Crop(BYTE* Buffer, int buffer_width, int Box_w, int Box_h, int x, int y);
BYTE* BinaryImage(BYTE* Buffer, int Width, int Height, int);
int D2_K_Mean_Clustering(BYTE* Buffer, int Width, int Height);
BYTE* RGBScale(BYTE* Buffer, int width, int height, long newsize);
BYTE* Dilation(BYTE* Buffer, int Width, int Height, BYTE* Mask, int m_w, int m_h);
BYTE* Erosion(BYTE* Buffer, int Width, int Height, BYTE* Mask, int m_w, int m_h);
BYTE* MirrorImage(BYTE* Buffer, long size);
BYTE* MULTID_K_Means_Clustering(BYTE* Buffer, int Width, int Height, int Tnumber);
BYTE* MultD_K_Means_Clustering(BYTE* Buffer, int Width, int Height,int Tnumber);
BYTE* Boundary(BYTE* Buffer, BYTE* DBuffer, int Width, int Height);
BYTE* CCL(BYTE* Buffer, int Width, int Height);
BYTE* CCLColoring(BYTE* Buffer, BYTE* CBuffer,int Width, int Height,int Size);
int CounterObject(BYTE* Buffer, int Width, int Height);
int* Convolution(BYTE* Buffer, int Width, int Height, int* Mask, int m_w, int m_h);
double* edgeimage(int* buffer, int* buffer2, int maxvalue,int w_new,int h_new);//normalization
double* gradient(int* buffer, int* buffer2, int width, int height);
double *nms(double* edge, double* angle, int width, int height);//türev yonunde baktýk 
double* histerize_threshold(double* Buffer, int Width, int Height);
double* binaryedge(double* buffer, double *angle,int width, int height);//kenar yönünde baktýk

