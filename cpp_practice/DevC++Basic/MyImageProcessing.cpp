//=========================================
// file: MyImageProcessing.cpp
//=== �Ѯv���ܽd�{���P�P�Ƿs�[�\�઺�{���� 
//=========================================

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "RichFreeImage.hpp"

extern HWND hGWnd; // ���ε{�������� HANDLE 
extern RichFreeImage gRichImage,  // �x�sŪ�J�� image 
                           rich,  // �Ψӽƻs gRichImage �����e�A��K���򪺳B�z 
                         richTo;  // �ΨӦs��v���B�z�L�᪺ image

//===== modify the original image and restore the result in it
void toGray(HDC hdc, int type)
// 0: gray;  1: red;  2: green; 3: blue
{
  rich.getClone(&gRichImage);  // get the image,
  rich.draw(hdc, 0, 0);        // then show it
  
  //===== get the pixels
  //rich.getBits();
  for (int r=0; r<rich.getHeight(); ++r)
     { for (int c=0; c<rich.getWidth(); ++c)
          { switch(type)
            { case 1: //rich.pt[r][c].r = 0;
                      rich.pt[r][c].g = 0;
                      rich.pt[r][c].b = 0;
                      break;
              case 2: rich.pt[r][c].r = 0;
                      //rich.pt[r][c].g = 0;
                      rich.pt[r][c].b = 0;
                      break;
              case 3: rich.pt[r][c].r = 0;
                      rich.pt[r][c].g = 0;
                      //rich.pt[r][c].b = 0;
                      break;                
              default:
                   { BYTE gray = (BYTE)( rich.pt[r][c].r * 0.299 +
                                         rich.pt[r][c].g * 0.587 +
                                         rich.pt[r][c].b * 0.114   );
                     rich.pt[r][c].r = rich.pt[r][c].g = rich.pt[r][c].b = gray;
                     break;
                   }
            }
          }
     }
  rich.setBitmapBits(); // copy data in image to FIdib's bits
  rich.draw(hdc, rich.getWidth()+1, 0);
}

void toMosaic(HDC hdc)
{
  rich.getClone(&gRichImage);
  rich.draw(hdc, 0, 0);
  richTo.getClone(&rich);
  richTo.resize(rich.getWidth(), rich.getHeight());

  float result;
  int shift, blkW=5, blkH=5, area;
  int red, green, blue;
  area = blkW * blkH;

  for (int r=0; r<rich.getHeight()-blkH; r+=blkH)
     {  for (int c=0; c<rich.getWidth()-blkW; c+=blkW)
           { red = green = blue = 0;
             for (int y=0; y<blkH; ++y)
                { for (int x=0; x<blkW; ++x)
                     { red   += rich.pt[r+y][c+x].r;
                       green += rich.pt[r+y][c+x].g;
                       blue  += rich.pt[r+y][c+x].b;
                     }
                }
             red   /= area;
             green /= area;
             blue  /= area;
             for (int y=0; y<blkH; ++y)
                { for (int x=0; x<blkW; ++x)
                     { richTo.pt[r+y][c+x].r = red;
                       richTo.pt[r+y][c+x].g = green;
                       richTo.pt[r+y][c+x].b = blue;
                     }
                }

           }
     }
  richTo.setBitmapBits();
  richTo.show(hdc, rich.getWidth()+1, 0);
}

float filter1[]={ 0, -1,  0,
                 -1,  4, -1,
                  0, -1,  0 };
float filter2[]={ 1, 0, -1,                  
                  2, 0, -2,
                  1, 0, -1 };  // You can add your own filters here.
                 
void filtering(HDC hdc)
{
  rich.getClone(&gRichImage);
  rich.draw(hdc, 0, 0);
  richTo.getClone(&rich);
       
  float result;
  int shift=1;
  float red, green, blue;
  
  float *filter = filter1; // �H���Ъ��覡�A���o filter (3x3) 

  for (int r=shift; r<rich.getHeight()-shift; ++r)
     {  for (int c=shift; c<rich.getWidth()-shift; ++c)
           { red = rich.pt[r-1][c-1].r * filter[0] +
                   rich.pt[r-1][c  ].r * filter[1] +
                   rich.pt[r-1][c+1].r * filter[2] +
                   rich.pt[r  ][c-1].r * filter[3] +
                   rich.pt[r  ][c  ].r * filter[4] +
                   rich.pt[r  ][c+1].r * filter[5] +
                   rich.pt[r+1][c-1].r * filter[6] +
                   rich.pt[r+1][c  ].r * filter[7] +
                   rich.pt[r+1][c+1].r * filter[8] ;

            green= rich.pt[r-1][c-1].g * filter[0] +
                   rich.pt[r-1][c  ].g * filter[1] +
                   rich.pt[r-1][c+1].g * filter[2] +
                   rich.pt[r  ][c-1].g * filter[3] +
                   rich.pt[r  ][c  ].g * filter[4] +
                   rich.pt[r  ][c+1].g * filter[5] +
                   rich.pt[r+1][c-1].g * filter[6] +
                   rich.pt[r+1][c  ].g * filter[7] +
                   rich.pt[r+1][c+1].g * filter[8] ;

            blue = rich.pt[r-1][c-1].b * filter[0] +
                   rich.pt[r-1][c  ].b * filter[1] +
                   rich.pt[r-1][c+1].b * filter[2] +
                   rich.pt[r  ][c-1].b * filter[3] +
                   rich.pt[r  ][c  ].b * filter[4] +
                   rich.pt[r  ][c+1].b * filter[5] +
                   rich.pt[r+1][c-1].b * filter[6] +
                   rich.pt[r+1][c  ].b * filter[7] +
                   rich.pt[r+1][c+1].b * filter[8] ;

             if ( red<0 ) red = 0;
             else if ( red>255 ) red = 255;
             if ( green<0 ) green = 0;
             else if ( green>255 ) green = 255;
             if ( blue<0 ) blue = 0;
             else if ( blue>255 ) blue = 255; 
                        
             richTo.pt[r][c].r = (BYTE) red;
             richTo.pt[r][c].g = (BYTE) green;
             richTo.pt[r][c].b = (BYTE) blue;
           }
     }
  richTo.setBitmapBits();
  richTo.show(hdc, rich.getWidth()+1, 0);
}

void halfImage(HDC hdc)
{
  int w, h;
  rich.getClone(&gRichImage);
  w = rich.getWidth();
  h = rich.getHeight();
  
  if ( ! richTo.resize(w/2, h/2) )  return;
  
  for (int r=0; r<h/2; ++r)
     { for (int c=0; c<w/2; ++c)
          {
            richTo.pt[r][c].r = rich.pt[r+r][c+c].r;
            richTo.pt[r][c].g = rich.pt[r+r][c+c].g;
            richTo.pt[r][c].b = rich.pt[r+r][c+c].b;
          }
     }
  richTo.setBitmapBits();
  richTo.show(hdc, w+1,0);
  //richTo.saveToFile("c:\\result.jpg");
}

void doubleImage(HDC hdc)
{
  int w, h, ph, pw;
  rich.getClone(&gRichImage);
  w = rich.getWidth();
  h = rich.getHeight();
  if ( ! richTo.resize(w*2, h*2) )  return;
  richTo.show(hdc, 0, 0);
  for (int r=0; r<h*2; ++r)
     { ph = r>>1;
       for (int c=0; c<w*2; ++c)
          { pw = c>>1;  // c = c/2
            richTo.pt[r][c].r = rich.pt[ph][pw].r;
            richTo.pt[r][c].g = rich.pt[ph][pw].g;
            richTo.pt[r][c].b = rich.pt[ph][pw].b;
          }
     }
  richTo.setBitmapBits();
  richTo.show(hdc, 0,0);
  //richTo.saveToFile("c:\\result.jpg");
}

void toGray(HDC hdc)
{
  richTo.getClone(&gRichImage);  // get the image,
  richTo.draw(hdc, 0, 0);        // then show it at (0,0)
  
  //===== get the pixels
  for (int r=0; r < richTo.getHeight(); ++r)
     { for (int c=0; c < richTo.getWidth(); ++c)
          { 
             BYTE gray = (BYTE)( richTo.pt[r][c].r * 0.299 +
                                 richTo.pt[r][c].g * 0.587 +
                                 richTo.pt[r][c].b * 0.114   );
             richTo.pt[r][c].r = gray;
			 richTo.pt[r][c].g = gray;
			 richTo.pt[r][c].b = gray;
          }
     }
  richTo.setBitmapBits(); // copy data in image to FIdib's bits
  richTo.draw(hdc, richTo.getWidth()+1, 0);
}

void addRGB(HDC hdc, int red, int blue, int green)
{
  richTo.getClone(&gRichImage);  // get the image,
  richTo.draw(hdc, 0, 0);        // then show it at (0,0)
  
  //===== get the pixels
  int value;
  
  for (int r=0; r < richTo.getHeight(); ++r)
     { for (int c=0; c < richTo.getWidth(); ++c)
          { 
             value = richTo.pt[r][c].r + red;
             /* === �Ѱ����q�����ѡA�H�� BYTE ��Ʒ�����^�����D 
             if ( value>255 ) 
               value = 255;
             else if ( value<0 )
               value = 0;  
             //*/  
             richTo.pt[r][c].r = (BYTE) value;
             
			 /* �P�W�z�ۦP�����k�A�h�W�[ red, green �����q 
             value = richTo.pt[r][c].g + green;
             if ( value>255 ) 
               value = 255;
             else if ( value<0 )
               value = 0;  
             richTo.pt[r][c].g = (BYTE) value;
             
             value = richTo.pt[r][c].b + blue;
             if ( value>255 ) 
               value = 255;
             else if ( value<0 )
               value = 0;  
             richTo.pt[r][c].b = (BYTE) value;
             //*/
          }
     }
  richTo.setBitmapBits(); // copy data in image to FIdib's bits
  richTo.draw(hdc, richTo.getWidth()+1, 0);
}

//==== �P�ɹ�v���i���سB�z���ܽd 
void halfGray(HDC hdc)
{
  //richTo.getClone(&gRichImage);  // ���h�o�@�B�J�A�O�d���e�B�z�����G 
  
  int halfW = richTo.getWidth() / 2;
  //===== get the pixels
  for (int r=0; r < richTo.getHeight(); ++r)
     { for (int c=0; c < halfW; ++c)
          { 
             BYTE gray = (BYTE)( richTo.pt[r][c].r * 0.299 +
                                 richTo.pt[r][c].g * 0.587 +
                                 richTo.pt[r][c].b * 0.114   );
             richTo.pt[r][c].r = gray;
			 richTo.pt[r][c].g = gray;
			 richTo.pt[r][c].b = gray;
          }
     }
  richTo.setBitmapBits(); // copy data in image to FIdib's bits
  richTo.draw(hdc, richTo.getWidth()+1, 0);
}

//==== �[�J�A���{���A�é� myProcessing(.) ���I�s���Y�i
// Add your code from here!

void myProcessing(HDC hdc)
{ 
  //=== �Y�p�v�� 
  halfImage(hdc);  // �N�v���e�����Y�p�� 1/2 
  //halfGray(hdc);  // �N�v�����b���ন�Ƕ� 
  
  //=== �W�[�v���� red, green, blue ���q 
  //int red=30, green=0, blue=0;
  //addRGB(hdc, red, green, blue);

  //=== �ন�Ƕ��v�� 
  //toGray(hdc);
  
  //=== ��j�v�� 
  //doubleImage(hdc);
  
  // or whatever processing you want to do.
}
 
