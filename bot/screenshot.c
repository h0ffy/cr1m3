#include <windows.h>

HBITMAP __screenshot() {
	HDC hScreen, hMemory;
	int x,y;
	HBITMAT hOld, hBitMap;

	hScreen = GetDC(NULL); // CreateDC("DISPLAY", NULL, NULL, NULL);
	hMemory = CreateCompatibleDC(hScreen);
	x = GetDeviceCaps(hScreen, HORZRES);
	y = GetDeviceCaps(hScreen, VERTRES);
	hBitMap = CreateCompatibleBitmap(hScreen, x, y);
	hOld = SelectObject(hMemory,hBitMap);
	BitBlt(hScreen,hMemory);
		
	DeleteDC(hMemory);
	DeleteDC(hScreen);

	return hBitMap;

}
