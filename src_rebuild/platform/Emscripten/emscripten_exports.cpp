#include "platform.h"
#include <libcd.h>
#include "PsyX/PsyX_globals.h"
#include "PsyX/PsyX_render.h"
/*
// TEMP
#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#endif // EMSCRIPTEN_KEEPALIVE
*/

extern bool DumpImageFile(const char* data, unsigned int size);
extern int FrAng;

extern "C" {

	void EMSCRIPTEN_KEEPALIVE WebLoadCDImage(char* data, int size) 
	{
		PsyX_CDFS_Init_Mem((u_int*)data, size, 0, 0);
	}

	// Browser canvas resizes do not generate an SDL_WINDOWEVENT_RESIZED in
	// Emscripten. Keep PsyCross' render dimensions in sync explicitly so its
	// viewport, projection, clipping, and framebuffer operations agree.
	void EMSCRIPTEN_KEEPALIVE WebResizeGame(int width, int height)
	{
		if (width < 1 || height < 1)
			return;

		g_windowWidth = width;
		g_windowHeight = height;
		GR_SetViewPort(0, 0, width, height);
	}

	int EMSCRIPTEN_KEEPALIVE WebGetWindowWidth() { return g_windowWidth; }
	int EMSCRIPTEN_KEEPALIVE WebGetWindowHeight() { return g_windowHeight; }
	int EMSCRIPTEN_KEEPALIVE WebGetFrustumAngle() { return FrAng; }
}
