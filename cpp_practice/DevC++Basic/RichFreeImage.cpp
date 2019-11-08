//=====================================================================
// This class is created by Rich Wang. It is freeware for any purposes.
// Parts of the codes are copied from FreeImage and modified
// by richwang.
//
//=====================================================================
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <mem.h>

#include "RichFreeImage.hpp"

//==============================================================
/** Generic image loader
    @param lpszPathName Pointer to the full file name
    @param flag Optional load flag constant
    @return Returns the loaded dib if successful, returns NULL otherwise
*/
FIBITMAP* GenericLoader(const char* lpszPathName, int flag)
{
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

  // check the file signature and deduce its format
  // (the second argument is currently not used by FreeImage)
  fif = FreeImage_GetFileType(lpszPathName, 0);
  if (fif == FIF_UNKNOWN)
  {
    // no signature ?
    // try to guess the file format from the file extension
    fif = FreeImage_GetFIFFromFilename(lpszPathName);
  }
  // check that the plugin has reading capabilities ...
  if ( (fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif) )
  {
    // ok, let's load the file
    FIBITMAP *dib = FreeImage_Load(fif, lpszPathName, flag);
    // unless a bad file format, we are done !
    return dib;
  }
  return NULL;
}
/** Generic image writer
    @param dib Pointer to the dib to be saved
    @param lpszPathName Pointer to the full file name
    @param flag Optional save flag constant
    @return Returns true if successful, returns false otherwise
*/
// modified by richwang to save 32-bits format file, July 9, 2006.
bool GenericWriter(FIBITMAP* dib, const char* lpszPathName, int flag=0)
{
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
  BOOL bSuccess = FALSE;

  if (dib)
  {
    // try to guess the file format from the file extension
    fif = FreeImage_GetFIFFromFilename(lpszPathName);
    if ( fif != FIF_UNKNOWN )
     { // check that the plugin has sufficient writing and export capabilities ...
       WORD bpp = FreeImage_GetBPP(dib);
       if ( FreeImage_FIFSupportsWriting(fif) )
       { if ( FreeImage_FIFSupportsExportBPP(fif, bpp) )
           { // ok, we can save the file
                  bSuccess = FreeImage_Save(fif, dib, lpszPathName, flag);
                  // unless an abnormal bug, we are done !
           }
         else
           {  FIBITMAP *temp = FreeImage_ConvertTo24Bits(dib);  // transfer to 24-bits
              bSuccess = FreeImage_Save(fif, temp, lpszPathName, flag);
              FreeImage_Unload(temp);
           }
       }
       else
       { MessageBox(GetFocus(), "Unsupported file format!", "Warning!",
       		   MB_OK | MB_APPLMODAL);
       }
     }
     else
     { MessageBox(GetFocus(), "Unknown file format!", "Something wrong",
     	          MB_OK | MB_APPLMODAL);
     }
   }
  return (bSuccess == TRUE) ? true : false;
}

#define RED   2
#define GREEN 1
#define BLUE  0

/*===== the content of class RichFreeImage 
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
    void getBits();
    void setBitmapBits();
    void draw(HDC hdc, int px, int py);
    void show(HDC hdc, int px, int py);
    bool isValid();
};
*/

int setupPixel(unsigned char *image, long rows, long cols, BitmapPt ** &ptr)
{ if ( ptr != NULL )
    delete [] ptr;

  ptr = new BitmapPt* [rows];
  if ( ptr==NULL ) return (0);

  for (int r=0; r<rows; ++r)
     ptr[r] = (BitmapPt *) (image+r*4*cols);

  return rows;
}

RichFreeImage::RichFreeImage()
{ FIdib = NULL;
  hbitmap = 0;
  image = NULL;
  pt = NULL;
}

RichFreeImage::~RichFreeImage()
{ if ( FIdib!=NULL ) FreeImage_Unload(FIdib);
  if ( image!=NULL ) delete [] image;
  if ( pt!=NULL )    delete [] pt;
  if ( hbitmap!=0 )  DeleteObject(hbitmap);
}

void RichFreeImage::loadFromFile(char* fileName, int flag)
{
  if ( FIdib!=NULL )
    { FreeImage_Unload(FIdib);
      FIdib = NULL;
    }

  FIdib = GenericLoader(fileName, flag);
  if ( FIdib==NULL ) return;

  bytesPerPixel = (FreeImage_GetBPP(FIdib)+7)/8;
  if ( bytesPerPixel<3 )  // not a 24-bits file reading
    {
      FIBITMAP *temp = FIdib;
      FIdib = FreeImage_ConvertTo24Bits(temp);  // transfer to 24-bits
      FreeImage_Unload(temp); // release original FIBITMAP object
      bytesPerPixel = 3;

      MessageBox(GetFocus(), "已轉換成 24 位元格式的全彩圖檔", "File transferred!",
	  	     MB_OK | MB_APPLMODAL);
    }
  setupData();
}

void RichFreeImage::setupData()
{
  if ( bytesPerPixel==3 )
    imgByteWidth = (4*FreeImage_GetWidth(FIdib)+3)/4 * 4; // devided by 4
  else
    imgByteWidth = FreeImage_GetPitch(FIdib);

  if ( image!=NULL ) delete [] image;
  image = (unsigned char*) new unsigned char [FreeImage_GetHeight(FIdib)*imgByteWidth];
  if ( image==NULL ) return;

  unsigned char *img, *ptr;
  if ( bytesPerPixel==3 )
    {
      long idx, h, w;
      h = FreeImage_GetHeight(FIdib);
      w = FreeImage_GetWidth(FIdib);
      for (int r=0; r<h; ++r)
         { ptr = (unsigned char*) FreeImage_GetScanLine(FIdib, r);
           img = image + r*imgByteWidth;
           idx = 0;
           for (int c=0; c<w; ++c)
              { img[0] = ptr[idx  ];
                img[1] = ptr[idx+1];
                img[2] = ptr[idx+2];
                img += 4;  // for r,g,b,a
                idx += 3;
              }
         }
    }
  else
    { memmove(image, (void *)FreeImage_GetBits(FIdib), FreeImage_GetHeight(FIdib)*imgByteWidth);
    }

  if ( pt!=NULL ) delete [] pt;

  // bitmap saves bits upside down
  int rows = FreeImage_GetHeight(FIdib);
  pt = new BitmapPt * [rows];
  /*
  for (int r=0; r<rows; ++r)
     { pt[r] = (BitmapPt *) (image + (rows-1-r) * imgByteWidth);
     }
  //*/
  //* ===== OK
  int stride = imgByteWidth / 4;
  pt[rows-1] = (BitmapPt*) image;
  for (int r=rows-2; r>=0; --r)
     { pt[r] = pt[r+1] + stride;  // note that each step in size of BitmapPt
     }
  //*/
  HDC hdc = GetDC(NULL); // get screen's device context
  hbitmap = CreateDIBitmap(hdc,
                           FreeImage_GetInfoHeader(FIdib),
                	       CBM_INIT,
                           FreeImage_GetBits(FIdib),
                           FreeImage_GetInfo(FIdib),
                           DIB_RGB_COLORS
                          );

  if ( hbitmap!=0 )
    { GetObject(hbitmap, sizeof(BITMAP), &bitmap);
    }

  ReleaseDC(NULL, hdc);
}

void RichFreeImage::showAttribute()
{
  if ( FIdib==NULL ) return;
  // show the attributes of the read in image
  char msg[128];
  sprintf(msg,"width=%d\nheight=%d\nbytesPerPixel=%d\npitch=%d",
              FreeImage_GetWidth(FIdib),FreeImage_GetHeight(FIdib),
              bytesPerPixel, FreeImage_GetPitch(FIdib));
  MessageBox(GetFocus(), msg, "Save File",
		 MB_OK | MB_APPLMODAL);
}

bool RichFreeImage::saveToFile(char* fileName, int flag)
{ bool result=false;
  //*
  unsigned char *img, *ptr;
  if ( bytesPerPixel==3 )
    {
      ptr = FreeImage_GetBits(FIdib);
      int idx;
      for (int r=0; r<FreeImage_GetHeight(FIdib); ++r)
      { img = image + r*imgByteWidth;
        ptr = FreeImage_GetScanLine(FIdib, r);
        idx = 0;
        for (int c=0; c<FreeImage_GetWidth(FIdib); ++c)
          { ptr[idx  ] = img[0];
            ptr[idx+1] = img[1];
            ptr[idx+2] = img[2];
            img += 4;  // for r,g,b,a
            idx += 3;
          }
      }
    }
  else
    { 
       memmove((void *)FreeImage_GetBits(FIdib), image, FreeImage_GetHeight(FIdib)*imgByteWidth);
    }
  //*/
  result = GenericWriter(FIdib, fileName, flag);

  return result;
}

bool RichFreeImage::saveToFileOld(char* fileName, int flag) // it doesn't work properly with saving jpg file
{ bool result=false;
  // the following code assumes that you have a valid HBITMAP loaded into the memory
  FIBITMAP *dib = NULL;
  if (hbitmap)
    { BITMAP bm;
      GetObject(hbitmap, sizeof(BITMAP), (LPSTR) &bm);
      dib = FreeImage_Allocate(bm.bmWidth, bm.bmHeight, 32); //bm.bmBitsPixel);
      // The GetDIBits function clears the biClrUsed and biClrImportant BITMAPINFO members (dont't know why)
      // So we save these infos below. This is needed for palettized images only.
      int nColors = FreeImage_GetColorsUsed(dib);
      HDC dc = GetDC(NULL);
      int Success = GetDIBits(dc, hbitmap, 0, FreeImage_GetHeight(dib),
                      FreeImage_GetBits(dib), FreeImage_GetInfo(dib), DIB_RGB_COLORS);
      ReleaseDC(NULL, dc);
      // restore BITMAPINFO members
      FreeImage_GetInfoHeader(dib)->biClrUsed = nColors;
      FreeImage_GetInfoHeader(dib)->biClrImportant = nColors;

      result = GenericWriter(dib, fileName, flag);
      // don't forget to call FreeImage_Unload when you no longer need the dib
      FreeImage_Unload(dib);
      MessageBox(GetFocus(), "File saved successfully!", "Save File",
		     MB_OK | MB_APPLMODAL); 
    }
  else
    { MessageBox(GetFocus(), "File saved fail!", "Save File",
		     MB_OK | MB_APPLMODAL);
    }

  return result;
}

bool RichFreeImage::resize(int newW, int newH)
{
  int bpp = FreeImage_GetBPP(FIdib);

  if ( newW==FreeImage_GetWidth(FIdib) && newH==FreeImage_GetHeight(FIdib) )
    return true;

  // allocate and clear dst image
  FIBITMAP *dib = NULL; // save the original FIdib
  dib = FreeImage_Allocate(newW, newH, bpp);
  if ( NULL==dib ) return false;  // cannot be created

  FreeImage_Unload(FIdib);
  FIdib = dib;
  dib = NULL;

  // to save and initialize the data
  bytesPerPixel = (FreeImage_GetBPP(FIdib)+7)/8;
  if ( bytesPerPixel<3 )  // not a 24-bits file reading
    {
      FIBITMAP *temp = FIdib;
      FIdib = FreeImage_ConvertTo24Bits(temp);  // transfer to 24-bits
      FreeImage_Unload(temp); // release original FIBITMAP object
      bytesPerPixel = 3;

      //MessageBox(GetFocus(), "已轉換成 24 位元格式的全彩圖檔", "File transferred!",
	  //	     MB_OK | MB_APPLMODAL);
    }
  setupData();
  return true;
}

bool RichFreeImage::getClone(RichFreeImage *priSrc)
{
  if ( priSrc->hbitmap==0 ) return false;

  FIBITMAP *temp =  FreeImage_Clone(priSrc->FIdib);
  if ( temp==NULL ) return false;

  if ( FIdib!=NULL )
    { FreeImage_Unload(FIdib);
    }
  FIdib = temp;
  if ( hbitmap!=0 )
    { DeleteObject(hbitmap);
      if ( image!=NULL )
        { delete [] image;
          image = NULL;
        }
      if ( pt!=NULL )
        { delete [] pt;
          pt = NULL;
        }
    }
  // to save and initialize the data
  bytesPerPixel = (FreeImage_GetBPP(FIdib)+7)/8;
  if ( bytesPerPixel<3 )  // not a 24-bits file reading
    {
      FIBITMAP *temp = FIdib;
      FIdib = FreeImage_ConvertTo24Bits(temp);  // transfer to 24-bits
      FreeImage_Unload(temp); // release original FIBITMAP object
      bytesPerPixel = 3;

      MessageBox(GetFocus(), "已轉換成 24 位元格式的全彩圖檔", "File transferred!",
	  	     MB_OK | MB_APPLMODAL);
    }

  setupData();
  fillBits();
}

void RichFreeImage::fillBits()
{ if ( image==NULL ) return;

  unsigned char *img, *ptr;
  if ( bytesPerPixel==3 )
    {
      ptr = FreeImage_GetBits(FIdib);
      int skip = FreeImage_GetPitch(FIdib);
      int idx;
      for (int r=0; r<FreeImage_GetHeight(FIdib); ++r)
      { img = image + r*imgByteWidth;
        ptr = FreeImage_GetScanLine(FIdib, r);
        idx = 0;
        for (int c=0; c<FreeImage_GetWidth(FIdib); ++c)
          { ptr[idx  ] = img[0];
            ptr[idx+1] = img[1];
            ptr[idx+2] = img[2];
            img += 4;  // for r,g,b,a
            idx += 3;
          }
      }
    }
  else
    {
       memmove((void *)FreeImage_GetBits(FIdib), image, FreeImage_GetHeight(FIdib)*imgByteWidth);
    }
}

HBITMAP RichFreeImage::getHBitmap()
{ return (HBITMAP) hbitmap;
}

long RichFreeImage::getWidth()
{ return (bitmap.bmWidth);
}

long RichFreeImage::getHeight()
{ return (bitmap.bmHeight);
}

void RichFreeImage::getBitmapBits()
{
  BITMAP bmp;
  if ( hbitmap==0 ) return;

  GetObject(hbitmap, sizeof(BITMAP), &bmp);

  DWORD cBytes = bmp.bmWidthBytes * bmp.bmHeight;
  //Allocate memory for the bits
  if ( image!=NULL ) delete [] image;
  image = new unsigned char[cBytes];

  //get the bits
  LPBITMAPINFO srcBmpi=(LPBITMAPINFO)new char[sizeof(BITMAPINFO)];
  ZeroMemory(srcBmpi, sizeof(BITMAPINFO));
  //initialize BitmapInfo struct
  srcBmpi->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
  srcBmpi->bmiHeader.biWidth       = bmp.bmWidth;
  srcBmpi->bmiHeader.biHeight      = bmp.bmHeight;
  srcBmpi->bmiHeader.biPlanes      = 1;
  srcBmpi->bmiHeader.biCompression = BI_RGB;
  srcBmpi->bmiHeader.biBitCount    = 32;

  HDC hdc = GetDC(NULL);
  GetDIBits(hdc, hbitmap, 0, bmp.bmHeight, image, srcBmpi, DIB_RGB_COLORS);
  setupPixel(image, bmp.bmHeight, bmp.bmWidth, pt);
  ReleaseDC(NULL, hdc);
}

void RichFreeImage::setBitmapBits()
{
  BITMAP bmp;
  if ( hbitmap==0 ||image==NULL ) return;

  GetObject(hbitmap, sizeof(BITMAP), &bmp);

  DWORD cBytes = bmp.bmWidthBytes * bmp.bmHeight;
  //set the bits
  LPBITMAPINFO srcBmpi=(LPBITMAPINFO)new char[sizeof(BITMAPINFO)];
  ZeroMemory(srcBmpi, sizeof(BITMAPINFO));
  //initialize BitmapInfo struct
  srcBmpi->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
  srcBmpi->bmiHeader.biWidth       = bmp.bmWidth;
  srcBmpi->bmiHeader.biHeight      = bmp.bmHeight;
  srcBmpi->bmiHeader.biPlanes      = 1;
  srcBmpi->bmiHeader.biCompression = BI_RGB;
  srcBmpi->bmiHeader.biBitCount    = 32;

  HDC hdc = GetDC(NULL);
  SetDIBits(hdc, hbitmap, 0, bmp.bmHeight, image, srcBmpi, DIB_RGB_COLORS);
  ReleaseDC(NULL, hdc);
}

void RichFreeImage::draw(HDC hdc, int px, int py)
{
  if ( hdc==NULL || hbitmap==0 ) return;

  HDC hdcMemory;
  hdcMemory = CreateCompatibleDC(hdc);
  BITMAP bmp;
  GetObject(hbitmap, sizeof(BITMAP), &bmp);
  SelectObject(hdcMemory, hbitmap);
  BitBlt(hdc, px, py, bmp.bmWidth, bmp.bmHeight,
         hdcMemory, 0, 0, SRCCOPY);
  DeleteDC(hdcMemory);
}

void RichFreeImage::show(HDC hdc, int px, int py)
{
  draw(hdc, px, py);
}

bool RichFreeImage::isValid()
{
  return ( FIdib!=NULL );
}
