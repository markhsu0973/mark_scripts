//==============================================================
// This class is created by Rich Wang. It is freeware.
// Parts of the codes are copied from FreeImage and modified
// by richwang.
//
//==============================================================

#ifndef __RichFreeImage__
 #define __RichFreeImage__
#include <windows.h>

#include "FreeImageDev-3-11.h"

#include <mem.h>

struct BitmapPt
{ unsigned char b,g,r,a;
};

class RichFreeImage
{ protected:
    FIBITMAP *FIdib;        
    HBITMAP hbitmap;
    BITMAP  bitmap;
    unsigned char *image;
    int bytesPerPixel;
    int imgByteWidth;
  public:
    BitmapPt **pt;
  public:
    RichFreeImage();
    ~RichFreeImage();
    void loadFromFile(char* fileName, int flag=0);
    void setupData();
    void showAttribute();
    bool saveToFile(char* fileName, int flag=0);
    bool saveToFileOld(char* fileName, int flag=0); // it doesn't work properly with saving jpg file
    bool resize(int newW, int newH);
    bool getClone(RichFreeImage *priSrc);
    void fillBits();
    HBITMAP getHBitmap();
    long getWidth();
    long getHeight();
    void getBitmapBits();
    void setBitmapBits();
    void draw(HDC hdc, int px, int py);
    void show(HDC hdc, int px, int py);
    bool isValid();
};

#endif

