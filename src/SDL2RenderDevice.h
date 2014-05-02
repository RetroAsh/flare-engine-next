/*
Copyright © 2013 Igor Paliychuk

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

#pragma once
#ifndef SDL2RENDERDEVICE_H
#define SDL2RENDERDEVICE_H

#if SDL_VERSION_ATLEAST(2,0,0)

#include "RenderDevice.h"

/** Provide rendering device using SDL_BlitSurface backend.
 *
 * Provide an SDL_BlitSurface implementation for renderning a Renderable to
 * the screen.  Simply dispatches rendering to SDL_BlitSurface().
 *
 * As this is for the FLARE engine, the implementation uses the engine's
 * global settings context, which is included by the interface.
 *
 * @class SDL2RenderDevice
 * @see RenderDevice
 * @author Kurt Rinnert
 * @date 2013-07-06
 *
 */

#define SDLKey SDL_Keycode

#define SDL_JoystickName SDL_JoystickNameForIndex


/** SDL Image */
class SDL2Image : public Image {
public:
  SDL2Image(RenderDevice *device);
  virtual ~SDL2Image();
  int getWidth() const;
  int getHeight() const;

  SDL_Texture *surface;
};

class SDL2RenderDevice : public RenderDevice {

public:

	SDL2RenderDevice();
	int createContext(int width, int height);
	Rect getContextSize();

	virtual int render(Renderable& r, Rect dest);
	virtual int render(Sprite* r);
	virtual int renderImage(Image* image, Rect& src);
	virtual int renderToImage(Image* src_image, Rect& src, Image* dest_image, Rect& dest, bool dest_is_transparent = false);

	int renderText(TTF_Font *ttf_font, const std::string& text, Color color, Rect& dest);

	Image *renderTextToImage(TTF_Font* ttf_font, const std::string& text, Color color, bool blended = true);

	void drawPixel(int x, int y, Uint32 color);

	void drawPixel(Image *image, int x, int y, Uint32 pixel);

	void drawLine(int x0, int y0, int x1, int y1, Uint32 color);

	void drawLine(const Point& p0, const Point& p1, Uint32 color);

	void drawRectangle(const Point& p0, const Point& p1, Uint32 color);

	void blankScreen();

	void commitFrame();

	void destroyContext();

	void fillImageWithColor(Image *dst, Rect *dstrect, Uint32 color);

	Uint32 MapRGB(Image *src, Uint8 r, Uint8 g, Uint8 b);

	Uint32 MapRGB(Uint8 r, Uint8 g, Uint8 b);

	Uint32 MapRGBA(Image *src, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	Uint32 MapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	Image *createAlphaSurface(int width, int height);

	void scaleSurface(Image *source, int width, int height);

	void setGamma(float g);

	void listModes(std::vector<Rect> &modes);

	Uint32 readPixel(Image *image, int x, int y);

	bool checkPixel(Point px, Image *image);

	void freeImage(Image *image);

	Image* loadGraphicSurface(std::string filename,
								std::string errormessage = "Couldn't load image",
								bool IfNotFoundExit = false);
private:

	SDL_Window *screen;
	SDL_Renderer *renderer;
	SDL_Surface* titlebar_icon;
};

#endif // SDL_VERSION_ATLEAST(2,0,0)

#endif // SDL2RENDERDEVICE_H