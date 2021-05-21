#include	<stdio.h>
#include	<stdlib.h>
#include	<windows.h>

#include  "resource.h"

#include "RichFreeImage.hpp"

//#include "FreeImageDev.h"
//#pragma comment(lib, "FreeImage.lib")
//#pragma comment(lib, "FreeImageBCB6.lib")

//*
#define	WIN		  0
#define WOUT		  1
#define WWORK		  2
#define WKEY		  3
#define MENU_POSX	 10
#define MENU_POSY	 10
#define MENU_SIZEX	600
#define MENU_SIZEY	 80	
#define WIN_POSX	 10
#define WIN_POSY	100
#define WOUT_POSX	290
#define WOUT_POSY	100
#define WWORK_POSX	 10
#define WWORK_POSY	390
#define WKEY_POSX	290
#define WKEY_POSY	390
//*/
#define MAX_NAME_LENGTH 256

#define X_SIZE	400
#define Y_SIZE	350

#define P_X_SIZE	X_SIZE*4
#define P_Y_SIZE	Y_SIZE*4

//===== for scrolling window
//#define min(x,y)   (x)>(y)?(y):(x)
//#define max(x,y)   (x)>(y)?(x):(y)

char	*wTitle[4] = {"IN", "OUT", "WORK", "KEY"};	/*視窗標題*/
typedef struct{
	HWND	hWnd;
	HBITMAP	hBitmap;
}ImageWin;

HINSTANCE	ghInst;			/*當前控制碼	*/
HWND		hGWnd;			/*主視窗		*/
HBITMAP		hBitmap;		/*位元圖		*/
HMENU		hSubMenu;		/*子對話框		*/
ImageWin	imageWin[4];	/*影像視窗		*/
/*			公用對話變量				*/
OPENFILENAME ofn;
char szFilterSpec [128]=			/*指定檔案種類的過濾器	*/
				"影像檔案(*.*)\0*.*\0";
char szFileName[MAX_NAME_LENGTH];	/*檔案名(有pass)*/
char szFileTitle[MAX_NAME_LENGTH];	/*檔案名(無pass)*/

HCURSOR hCursor;
RECT rect;
HBITMAP	hBGBitmap=NULL;
HDC hBGDC;
bool swapImage = false;
int screenW, screenH;

//##############################
// 宣告自行寫作的程式，
// 亦可存成一個 header 檔再 include 進來
extern void toGray(HDC, int);
extern void toMosaic(HDC);
extern void filtering(HDC);
extern void myProcessing(HDC);
//##############################

RichFreeImage gRichImage, rich, richTo;
//###############

LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
/*--- WinMain --- 主程式 ----------------
	hInstance:		面向應用的當前控制碼
	hPrevInstance:	前個執行控制碼
	lpCmdLine:		命令形的字符串
	nCmdShow:		啟動時的顯示方法
---------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;

	if (!hPrevInstance)
	  if (!InitApplication(hInstance))
		return 0;

	if (!InitInstance(hInstance, nCmdShow))
	  return 0;

	ghInst = hInstance;

	while (GetMessage(&msg, (HWND)NULL, (UINT)NULL, (UINT)NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
/*--- InitApplication ---    登入的視窗類別-----------------
	hInstance: 給應用的控制碼
----------------------------------------------------------*/
BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASSEX	wc, wcm;

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LENA)); //IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "MainClass";
	//wc.hIconSm = LoadIcon(hInstance, "lena"); // getting icon from string "lena"
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LENA)); // getting icon from number
	if (!RegisterClassEx(&wc)) return FALSE;

	wcm.cbSize = sizeof(wcm);
	wcm.style = CS_HREDRAW | CS_VREDRAW;
	wcm.lpfnWndProc = (WNDPROC)MainWndProc;
	wcm.cbClsExtra = 0;
	wcm.cbWndExtra = 0;
	wcm.hInstance = hInstance;
	wcm.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcm.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcm.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcm.lpszMenuName = "FrameMenu";
	wcm.lpszClassName = "ImageClass";
	wcm.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	return RegisterClassEx(&wcm);
}
/*--- MainWndProc --- 有關訊息的處理    --------------------
----------------------------------------------------------*/

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT	ps;
    HDC		hDC, hMemDC;
    POINT	point;
    int		wno;
    FIBITMAP    *FIdib=NULL;
    BITMAP      bmp;
    COLORREF    color;
    char        msg[80];
    int maxW, maxH;
    static int  xCurPos, yCurPos, xPrevPos, yPrevPos, xThumb, yThumb,
                yMin, xMin, yMax, xMax, cxClient, cyClient;
	switch (message)
        {
             case WM_CREATE:
                  //ShowScrollBar(hWnd, SB_BOTH, true);
                  screenW = GetSystemMetrics(SM_CXFULLSCREEN);
                  screenH = GetSystemMetrics(SM_CYFULLSCREEN);
                  GetClientRect(hWnd, &rect);

                  gRichImage.loadFromFile("lena.jpg");
                  rich.getClone(&gRichImage);

                  // xMax and yMax both are the ranges to view all the client area.
                  // richwang

                  if ( rect.right < gRichImage.getWidth()*2+1 )
                    xMax = (gRichImage.getWidth()*2+1) - rect.right;
                  else xMax = 0;
                  if ( rect.bottom < gRichImage.getHeight() )
                    yMax = gRichImage.getHeight() - rect.bottom;
                  else yMax = 0;

                  xCurPos = yCurPos = 0;
                  xThumb = xMax / 4;  yThumb = yMax / 4;
                  SetScrollRange(hWnd, SB_VERT, 0, yMax, true);
                  SetScrollPos(hWnd, SB_VERT, yCurPos, true);
                  SetScrollRange(hWnd, SB_HORZ, 0, xMax, true);
                  SetScrollPos(hWnd, SB_HORZ, xCurPos, true);

                  hDC = GetDC(NULL);
                  hBGBitmap = CreateCompatibleBitmap(hDC, screenW, screenH);
                  hBGDC = CreateCompatibleDC(hDC);
	     	      SelectObject(hBGDC, hBGBitmap);
                  SetRect(&rect, 0, 0, screenW, screenH);
                  FillRect(hMemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	     	      rich.draw(hBGDC, 0, 0);
                  ReleaseDC(NULL, hDC);

                  break;
             case WM_SIZE:
                  GetClientRect(hWnd, &rect);
                  maxW = max(gRichImage.getWidth()*2+1, gRichImage.getWidth()+richTo.getWidth()+1);
                  //if ( rect.right < gRichImage.getWidth()*2+1 )
                  if ( rect.right < maxW )
                    xMax = maxW - rect.right;
                  else xMax = 0;
                  maxH = max(gRichImage.getHeight(), richTo.getHeight());
                  if ( rect.bottom < maxH )
                    yMax = maxH - rect.bottom;
                  else yMax = 0;

                  xThumb = xMax/4;  yThumb = yMax/4;
                  xCurPos = 0;  yCurPos = 0;
                  InvalidateRect(hWnd, NULL, false);
                  break;
             case WM_VSCROLL:
                  yPrevPos = yCurPos;
                  switch(LOWORD(wParam))
                  { case SB_LINEUP:
                         yCurPos -= 1;
                         break;
                    case SB_LINEDOWN:
                         yCurPos += 1;
                         break;
                    case SB_PAGEUP:
                         yCurPos -= yThumb;
                         break;
                    case SB_PAGEDOWN:
                         yCurPos += yThumb;
                         break;
                    case SB_TOP:
                         yCurPos = 0;
                         break;
                    case SB_BOTTOM:
                         yCurPos = yMax;
                         break;
                    case SB_THUMBPOSITION:
                         yCurPos = HIWORD(wParam);
                         break;
                  }
                  yMin = min(yCurPos, yMax);
                  yCurPos = max(0, yMin);

                  if ( yCurPos!=GetScrollPos(hWnd, SB_VERT) )
                    {
                      SetScrollPos(hWnd, SB_VERT, yCurPos, true);
                      InvalidateRect(hWnd, NULL, false);
                    }

                  break;
             case WM_HSCROLL:
                  xPrevPos = xCurPos;
                  switch(LOWORD(wParam))
                  { case SB_LINEUP:
                         xCurPos -= 1;
                         break;
                    case SB_LINEDOWN:
                         xCurPos += 1;
                         break;
                    case SB_PAGEUP:
                         xCurPos -= xThumb;
                         break;
                    case SB_PAGEDOWN:
                         xCurPos += xThumb;
                         break;
                    case SB_TOP:
                         xCurPos = 0;
                         break;
                    case SB_BOTTOM:
                         xCurPos = xMax;
                         break;
                    case SB_THUMBPOSITION:
                         xCurPos = HIWORD(wParam);
                         break;
                  }
                  xMin = min(xCurPos, xMax);
                  xCurPos = max(0, xMin);
                  if ( xCurPos!=GetScrollPos(hWnd, SB_HORZ) )
                    {
                      SetScrollPos(hWnd, SB_HORZ, xCurPos, true);
                      InvalidateRect(hWnd, NULL, false);
                    }
                  break;
             case WM_MOUSEMOVE:
                  break;
             case WM_LBUTTONDOWN:
                  point.x = LOWORD(lParam);
	              point.y = HIWORD(lParam);
                  hDC = GetDC(hWnd);
                  color = GetPixel(hDC, point.x, point.y);
                  ReleaseDC(hWnd, hDC);
                  sprintf(msg, "(%d,%d) => (r, g, b)=(%3d,%3d,%3d)",
                               point.x, point.y,
                               GetRValue(color), GetGValue(color), GetBValue(color) );
                  ModifyMenu(GetMenu(hWnd), 2, MF_BYPOSITION, MF_STRING,
                              msg);
                  DrawMenuBar(hWnd);
	              //GetMenuString(hSubMenu, MENU_SWAP, msg, 79, 0);
                  //ModifyMenu(hSubMenu, MENU_SWAP, MF_BYCOMMAND, MF_STRING,
                  //            "Richwang");
                  //MessageBox(GetFocus(), msg, "Modify Menu Item",
	              //  	   	            MB_OK | MB_APPLMODAL);
	          break;
	     case WM_RBUTTONDOWN:
	          point.x = LOWORD(lParam);
	          point.y = HIWORD(lParam);
	          ClientToScreen(hWnd, &point);
	          TrackPopupMenu (hSubMenu, 0, point.x, point.y, 0, hWnd, NULL);
	          break;
	     case WM_COMMAND:
	          switch(wParam)
                  {
                    case MENU_READ:
                         hCursor = LoadCursor(ghInst, IDC_WAIT);
                         if ( hCursor ) SetCursor(hCursor);

                         if ( GetOpenFileName((LPOPENFILENAME)&ofn) )
	          	           {
                             gRichImage.loadFromFile(ofn.lpstrFile);
                             rich.getClone(&gRichImage);
                             richTo.getClone(&gRichImage);

                             GetClientRect(hWnd, &rect);
                             if ( rect.right < gRichImage.getWidth()*2+1 )
                               xMax = (gRichImage.getWidth()*2+1) - rect.right;
                             else xMax = 0;
                             if ( rect.bottom < gRichImage.getHeight() )
                               yMax = gRichImage.getHeight() - rect.bottom;
                             else yMax = 0;
                             //xMax = max(rect.right, gRichImage.getWidth()*2+1);
                             //yMax = max(rect.bottom, gRichImage.getHeight());
                             xCurPos = yCurPos = 0;
                             xThumb = xMax / 4;  yThumb = yMax / 4;

                             SetScrollRange(hWnd, SB_VERT, 0, yMax, true);
                             SetScrollPos(hWnd, SB_VERT, yCurPos, true);
                             SetScrollRange(hWnd, SB_HORZ, 0, xMax, true);
                             SetScrollPos(hWnd, SB_HORZ, xCurPos, true);

                             InvalidateRect(hWnd, NULL, false);
                           };
                         hCursor = LoadCursor(ghInst, IDC_ARROW);
                         if ( hCursor ) SetCursor(hCursor);
	                 break;
                    case MENU_WRITE:
                         if ( GetSaveFileName((LPOPENFILENAME)&ofn))
	          	         { hCursor = LoadCursor(ghInst, IDC_WAIT);
                             if ( hCursor ) SetCursor(hCursor);
                             if ( gRichImage.saveToFile(ofn.lpstrFile, 0) )
	          	      	       { MessageBox(GetFocus(), "File has been saved successfully!",
                                            "Save File with RichFreeImage",
	          	      	               MB_OK | MB_APPLMODAL);
                               }
                             hCursor = LoadCursor(ghInst, IDC_ARROW);
                             if ( hCursor ) SetCursor(hCursor);
                         }
	                 break;
                    case MENU_GRAY:
                         //===== for testing class RichBitmap
                         hDC = GetDC(hWnd);
                         toGray(hDC, 0);
                         ReleaseDC(hWnd, hDC);
                         break;
                    case MENU_RED:
                         //===== for testing class RichBitmap
                         hDC = GetDC(hWnd);
                         toGray(hDC, 1);
                         ReleaseDC(hWnd, hDC);
                         break;
                    case MENU_GREEN:
                         //===== for testing class RichBitmap
                         hDC = GetDC(hWnd);
                         toGray(hDC, 2);
                         ReleaseDC(hWnd, hDC);
                         break;
                    case MENU_BLUE:
                         //===== for testing class RichBitmap
                         hDC = GetDC(hWnd);
                         toGray(hDC, 3);
                         ReleaseDC(hWnd, hDC);
                         break;
                    case MENU_MOSAIC:
                         hDC = GetDC(hWnd);
                         toMosaic(hDC);
                         ReleaseDC(hWnd, hDC);
                         break;
                    case MENU_QUIT:
                         DestroyWindow(hWnd);
                         break;
                    case MENU_FILTERING:
                         hDC = GetDC(hWnd);
                         filtering(hDC);
                         ReleaseDC(hWnd, hDC);
                         break;
                    case MENU_MINE:
                         //===== user processing
                         hDC = GetDC(hWnd);
                         myProcessing(hDC);
                         ReleaseDC(hWnd, hDC);
                         //======================

                         GetClientRect(hWnd, &rect);
                         maxW = max(gRichImage.getWidth()*2+1, gRichImage.getWidth()+richTo.getWidth()+1);
                         if ( rect.right < maxW )
                           xMax = maxW - rect.right;
                         else xMax = 0;
                         maxH = max(gRichImage.getHeight(), richTo.getHeight());
                         if ( rect.bottom < maxH )
                           yMax = maxH - rect.bottom;
                         else yMax = 0;
                         xCurPos = yCurPos = 0;
                         xThumb = xMax / 4;  yThumb = yMax / 4;

                         SetScrollRange(hWnd, SB_VERT, 0, yMax, true);
                         SetScrollPos(hWnd, SB_VERT, yCurPos, true);
                         SetScrollRange(hWnd, SB_HORZ, 0, xMax, true);
                         SetScrollPos(hWnd, SB_HORZ, xCurPos, true);
                         break;
                    case MENU_SWAP:
                         swapImage = ! swapImage;
                         if ( swapImage )
                            CheckMenuItem(hSubMenu, MENU_SWAP, MF_CHECKED);
                         else CheckMenuItem(hSubMenu, MENU_SWAP, MF_UNCHECKED);

                         InvalidateRect(hWnd, NULL, false);
                         UpdateWindow(hWnd);
                         break;
                    case MENU_PASTE:
                         if ( richTo.isValid() )
                           { richTo.fillBits();
                             gRichImage.getClone(&richTo);
                             rich.getClone(&richTo);
                             InvalidateRect(hWnd, NULL, false);
                             UpdateWindow(hWnd);
                           }
                         break;
                    case MENU_SAVE_RESULT:
                         if ( GetSaveFileName((LPOPENFILENAME)&ofn))
	            	     { if ( richTo.saveToFile(ofn.lpstrFile, 0) )
	            	       { MessageBox(GetFocus(), "File has been saved successfully!",
                                            "Save File with RichFreeImage",
	            	   	            MB_OK | MB_APPLMODAL);
                           }
                         }
                         break;
                    default: ;
	          }
	          break;
	     case WM_PAINT: // repaint the form
                  /*wno = -1;
	     	      for (int i = 0; i < 4; i++)
	     	         if (hWnd == imageWin[i].hWnd) wno = i;
	     	      if (wno != -1)
	     	      { BeginPaint(imageWin[wno].hWnd, &ps);
	     	        hMemDC = CreateCompatibleDC(ps.hdc);
	     	        SelectObject(hMemDC, hBitmap);
	     	        BitBlt(ps.hdc, 0, 0, X_SIZE, Y_SIZE, hMemDC, 0, 0, SRCCOPY);

                    hDC = GetDC(hGWnd);
	     	        BitBlt(hDC, 0, 0, X_SIZE, Y_SIZE, hMemDC, 0, 0, SRCCOPY);
                    ReleaseDC(hWnd, hDC);

	     	        DeleteDC(hMemDC);
	     	        EndPaint(hWnd, &ps);
                  }
                  else
                  */
                    { hDC = BeginPaint(hWnd, &ps);  // Note that it is needed!
                      /*
                      hDC = GetDC(hWnd);
                      hMemDC = CreateCompatibleDC(hDC);
                      SelectObject(hMemDC, hBGBitmap);
                      if ( swapImage )
                        { richTo.show(hMemDC, -xCurPos, -yCurPos);
                          rich.show(hMemDC, -xCurPos+rich.getWidth()+1, -yCurPos);
                        }
                      else
                        { rich.show(hMemDC, -xCurPos, -yCurPos);
                          richTo.show(hMemDC, -xCurPos+rich.getWidth()+1, -yCurPos);
                        }
                      BitBlt(hDC, 0, 0, screenW, screenW,
                             hMemDC, 0, 0, SRCCOPY
                            );
                      DeleteDC(hMemDC);
                      ReleaseDC(hWnd, hDC);
                      //*/
                      SetRect(&rect, 0, 0, screenW, screenH);
                      FillRect(hBGDC, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
                      if ( swapImage )
                        { richTo.show(hBGDC, -xCurPos, -yCurPos);
                          rich.show(hBGDC, -xCurPos+richTo.getWidth()+1, -yCurPos);
                        }
                      else
                        { rich.show(hBGDC, -xCurPos, -yCurPos);
                          richTo.show(hBGDC, -xCurPos+rich.getWidth()+1, -yCurPos);
                        }
                      GetClientRect(hWnd, &rect);
                      BitBlt(hDC, 0, 0, rect.right, rect.bottom,
                             hBGDC, 0, 0, SRCCOPY
                            );
                      //DeleteObject(hrgn);
                      //ReleaseDC(hWnd, hDC);
                      EndPaint(hWnd, &ps);
                    }
	     	  break;
	     case WM_DESTROY:
              DeleteObject(hBitmap);
              DeleteObject(hBGBitmap);
              DeleteDC(hBGDC);
	     	  PostQuitMessage(0);
              break;

	     default:
	     	return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*--- InitInstance ---    做成視窗  ------------------------
	hInstance:	 給應用的控制碼
	nCmdShow:	 啟動時的表示方法
-----------------------------------------------------------*/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND	hWnd;
	HDC	hDC;
	RECT	rect;
	int	i, j;

	hGWnd = hWnd = CreateWindowEx(
	                 0,                   /* Extended possibilites for variation */
                     "MainClass",         /* Classname */
                     "東南科技大學 資工系、電通系、資訊科技與通訊學系 影像處理課程",  /* Title Text */
		             WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL, /* default window */
                     CW_USEDEFAULT,       /* Windows decides the position */
                     CW_USEDEFAULT,       /* where the window ends up on the screen */
		             CW_USEDEFAULT,       /* The program's width */
                     CW_USEDEFAULT,       /* and height in pixels */
                     HWND_DESKTOP,        /* The window is a child-window to desktop */
                     NULL,                /* No menu */
                     hInstance,           /* Program Instance handler */
                     NULL                 /* No Window Creation data */
                   );
	if (hWnd == NULL) return FALSE;
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	hSubMenu = LoadMenu(ghInst, "SubMenu");
	hSubMenu = GetSubMenu(hSubMenu, 0);

	//*
        hDC = GetDC(hWnd);
	int bitspixel = GetDeviceCaps (hDC, BITSPIXEL);
	if (bitspixel == 16){
		MessageBox(GetFocus(),
				"請採用全彩色顯示(24位元或32位元)",
				"警告",
				MB_ICONHAND | MB_APPLMODAL);
	}
	else if (bitspixel != 24 && bitspixel !=32){
		MessageBox(GetFocus(),
				"請採用全彩色顯示(24位元或32位元)",
				"警告",
				MB_ICONHAND | MB_APPLMODAL);
		return FALSE;
	}
    /*/
	for (i = 0; i < 4; i++){
		imageWin[i].hBitmap = CreateCompatibleBitmap(hDC, X_SIZE, Y_SIZE);
	}
	rect.top = 0;
	rect.left = 0;
	rect.bottom = rect.top+Y_SIZE;
	rect.right = rect.left+X_SIZE;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);  //<-- rich

        imageWin[WIN].hWnd = CreateWindowEx(
                          0,
                          "ImageClass",
                          wTitle[WIN],
			  WS_OVERLAPPED,
                          WIN_POSX,
                          WIN_POSY,
			  rect.right-rect.left,
                          rect.bottom-rect.top,
                          NULL,
                          NULL,
                          hInstance, 
			  NULL
                         );
	if (imageWin[WIN].hWnd == NULL) return FALSE;
	ShowWindow(imageWin[WIN].hWnd, nCmdShow);

	imageWin[WOUT].hWnd = CreateWindowEx(0, "ImageClass", wTitle[WOUT],
			WS_OVERLAPPED, WOUT_POSX, WOUT_POSY,
			rect.right-rect.left, rect.bottom-rect.top, NULL, NULL, hInstance, 
			NULL);
	if (imageWin[WOUT].hWnd == NULL) return FALSE;
	ShowWindow(imageWin[WOUT].hWnd, nCmdShow);

	imageWin[WWORK].hWnd = CreateWindowEx(0, "ImageClass", wTitle[WWORK],
			WS_OVERLAPPED, WWORK_POSX, WWORK_POSY,
			rect.right-rect.left, rect.bottom-rect.top, NULL, NULL, hInstance, 
			NULL);
	if (imageWin[WWORK].hWnd == NULL) return FALSE;
	ShowWindow(imageWin[WWORK].hWnd, nCmdShow);

	imageWin[WKEY].hWnd = CreateWindowEx(0, "ImageClass", wTitle[WKEY],
			WS_OVERLAPPED, WKEY_POSX, WKEY_POSY,
			rect.right-rect.left, rect.bottom-rect.top, NULL, NULL, hInstance, 
			NULL);
	if (imageWin[WKEY].hWnd == NULL) return FALSE;
	ShowWindow(imageWin[WKEY].hWnd, nCmdShow);
	*/

	/*設定OPENFILENAME結構的成員*/
 	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.hwndOwner			= hWnd;
	ofn.lpstrFilter			= szFilterSpec;
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 1;
	ofn.lpstrFile			= szFileName;
	ofn.nMaxFile			= MAX_NAME_LENGTH;
	ofn.lpstrInitialDir		= NULL;
	ofn.lpstrFileTitle		= szFileTitle;
	ofn.nMaxFileTitle		= MAX_NAME_LENGTH;
	ofn.lpstrTitle			= NULL;
	ofn.lpstrDefExt			= NULL;
	ofn.Flags		       	= 0;

	return TRUE;	
}
