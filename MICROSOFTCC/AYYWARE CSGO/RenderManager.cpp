#pragma once

#include "RenderManager.h"

#define _CRT_SECURE_NO_WARNINGS
#define IDR_FONT1                       101

#ifdef STRICT
typedef void *HANDLE;
#if 0 && (_MSC_VER > 1000)
#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
#else
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

namespace Render
{
	namespace Fonts
	{
		DWORD Default;
		DWORD Menu;
		DWORD MenuBold;
		DWORD ESP;
		DWORD MenuText;
		DWORD Icon;
		DWORD MenuTabs;
		DWORD Text;
		DWORD Slider;
		DWORD Clock;
		DWORD LBY;
		DWORD Tabs;
		DWORD List;
	};
};


enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

void Render::Initialise()
{
	Fonts::Default  = 0x1D; 
	Fonts::Menu     = Interfaces::Surface->FontCreate();
	Fonts::MenuBold = Interfaces::Surface->FontCreate();
	Fonts::ESP = Interfaces::Surface->FontCreate();
	Fonts::MenuText = Interfaces::Surface->FontCreate();
	Fonts::Icon = Interfaces::Surface->FontCreate();
	Fonts::MenuTabs = Interfaces::Surface->FontCreate();
	Fonts::MenuText = Interfaces::Surface->FontCreate();
	Fonts::Slider = Interfaces::Surface->FontCreate();
	Fonts::Clock = Interfaces::Surface->FontCreate();
	Fonts::LBY = Interfaces::Surface->FontCreate();
	Fonts::Tabs = Interfaces::Surface->FontCreate();
	Fonts::List = Interfaces::Surface->FontCreate();

	Interfaces::Surface->SetFontGlyphSet(Fonts::Menu, "DINPro-Regular", 14, 500, 0, 0, FONTFLAG_ANTIALIAS);
	Interfaces::Surface->SetFontGlyphSet(Fonts::Text, "DINPro-Regular", 30, 500, 0, 0, FONTFLAG_ANTIALIAS);
	Interfaces::Surface->SetFontGlyphSet(Fonts::MenuBold, "DINPro-Regular", 14, 900, 0, 0, FONTFLAG_ANTIALIAS);
	Interfaces::Surface->SetFontGlyphSet(Fonts::ESP, "Calibri", 14, 500, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	Interfaces::Surface->SetFontGlyphSet(Fonts::MenuText, "Calibri", 16, 500, 0, 0, FONTFLAG_ANTIALIAS);
	Interfaces::Surface->SetFontGlyphSet(Fonts::MenuTabs, "MyScriptFont", 18, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	Interfaces::Surface->SetFontGlyphSet(Fonts::Slider, "Arial", 17, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
	Interfaces::Surface->SetFontGlyphSet(Fonts::Clock, "Arial", 22, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE);
	Interfaces::Surface->SetFontGlyphSet(Fonts::Tabs, "MyScriptFont", 50, 600, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	Interfaces::Surface->SetFontGlyphSet(Fonts::LBY, "Verdana", 20, 800, 0, 0, FONTFLAG_OUTLINE | FONTFLAG_ANTIALIAS);
	Interfaces::Surface->SetFontGlyphSet(Fonts::List, "Tahoma", 14, 600, 0, 0, FONTFLAG_ANTIALIAS); //x88 style lol

	HRSRC hResInst = FindResource(nullptr, MAKEINTRESOURCE(IDR_FONT1), RT_FONT);
	HGLOBAL hGlobal = LoadResource(nullptr, hResInst);
	size_t __LEN = SizeofResource(nullptr, hResInst);
	DWORD dwFonts;
	Interfaces::__FNTHANDLE = AddFontMemResourceEx(nullptr, __LEN, nullptr, &dwFonts);
	auto __FONT = CreateFont(16, 0, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "undefeated");

	Interfaces::Surface->SetFontGlyphSet(Fonts::Icon, "undefeated", 10, 500, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW | FONTFLAG_OUTLINE);

	Utilities::Log("Render System Ready");
}

RECT Render::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	Interfaces::Engine->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}

void Render::Clear(int x, int y, int w, int h, Color color)
{
	Interfaces::Surface->DrawSetColor(color);
	Interfaces::Surface->DrawFilledRect(x, y, x + w, y + h);
}

void Render::Outline(int x, int y, int w, int h, Color color)
{
	Interfaces::Surface->DrawSetColor(color);
	Interfaces::Surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void Render::Line(int x, int y, int x2, int y2, Color color)
{
	Interfaces::Surface->DrawSetColor(color);
	Interfaces::Surface->DrawLine(x, y, x2, y2);
}

void Render::PolyLine(int *x, int *y, int count, Color color)
{
	Interfaces::Surface->DrawSetColor(color);
	Interfaces::Surface->DrawPolyLine(x, y, count);
}

void Render::DrawOutlinedRect(int x, int y, int w, int h, Color col)
{
	Interfaces::Surface->DrawSetColor(col);
	Interfaces::Surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void Render::DrawLine(int x0, int y0, int x1, int y1, Color col)
{
	Interfaces::Surface->DrawSetColor(col);
	Interfaces::Surface->DrawLine(x0, y0, x1, y1);
}
void Render::fillRGBA(int x, int y, int w, int h, Color c)
{
	Interfaces::Surface->DrawSetColor(c);
	Interfaces::Surface->DrawFilledRect(x, y, x + w, y + h);
}
bool Render::WorldToScreen(Vector &in, Vector &out)
{
	const matrix3x4& worldToScreen = Interfaces::Engine->WorldToScreenMatrix();

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3];
	out.z = 0; 

	if (w > 0.001) 
	{
		RECT ScreenSize = GetViewport();
		float fl1DBw = 1 / w; 
		out.x = (ScreenSize.right / 2) + (0.5f * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * fl1DBw) * ScreenSize.right + 0.5f); //Get the X dimension and push it in to the Vector.
		out.y = (ScreenSize.bottom / 2) - (0.5f * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * fl1DBw) * ScreenSize.bottom + 0.5f); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

void Render::Text(int x, int y, Color color, DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	Interfaces::Surface->DrawSetTextFont(font);

	Interfaces::Surface->DrawSetTextColor(color);
	Interfaces::Surface->DrawSetTextPos(x, y);
	Interfaces::Surface->DrawPrintText(wcstring, wcslen(wcstring));
	return;
}

void Render::Text(int x, int y, Color color, DWORD font, const wchar_t* text)
{
	Interfaces::Surface->DrawSetTextFont(font);
	Interfaces::Surface->DrawSetTextColor(color);
	Interfaces::Surface->DrawSetTextPos(x, y);
	Interfaces::Surface->DrawPrintText(text, wcslen(text));
}

void Render::Textf(int x, int y, Color color, DWORD font, const char* fmt, ...)
{
	if (!fmt) return; //if the passed string is null return
	if (strlen(fmt) < 2) return;

	//Set up va_list and buffer to hold the params 
	va_list va_alist;
	char logBuf[256] = { 0 };

	//Do sprintf with the parameters
	va_start(va_alist, fmt);
	_vsnprintf_s(logBuf + strlen(logBuf), 256 - strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
	va_end(va_alist);

	Text(x, y, color, font, logBuf);
}

RECT Render::GetTextSize(DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	RECT rect; int x, y;
	Interfaces::Surface->GetTextSize(font, wcstring, x, y);
	rect.left = x; rect.bottom = y;
	rect.right = x;
	return rect;
}

void Render::GradientV(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = i, fh = h;
		float a = fi / fh;
		DWORD ia = a * 255;
		Clear(x, y + i, w, 1, Color(first, second, third, ia));
	}
}

void Render::DrawCircle(float x, float y, float r, float segments, Color color)
{
	Interfaces::Surface->DrawSetColor(color);
	Interfaces::Surface->DrawOutlinedCircle(x, y, r, segments);
}

void Render::GradientH(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < w; i++)
	{
		float fi = i, fw = w;
		float a = fi / fw;
		DWORD ia = a * 255;
		Clear(x + i, y, 1, h, Color(first, second, third, ia));
	}
}

void Render::Polygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = Interfaces::Surface->CreateNewTextureID(true); //need to make a texture with procedural true
	unsigned char buffer[4] = { 255, 255, 255, 255 };//{ color.r(), color.g(), color.b(), color.a() };

	Interfaces::Surface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
	Interfaces::Surface->DrawSetColor(color); // keep this full color and opacity use the RGBA @top to set values.
	Interfaces::Surface->DrawSetTexture(Texture); // bind texture

	Interfaces::Surface->DrawTexturedPolygon(count, Vertexs);
}

void Render::PolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine)
{
	static int x[128];
	static int y[128];

	Render::Polygon(count, Vertexs, color);

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Render::PolyLine(x, y, count, colorLine);
}

void Render::PolyLine(int count, Vertex_t* Vertexs, Color colorLine)
{
	static int x[128];
	static int y[128];

	for (int i = 0; i < count; i++)
	{
		x[i] = Vertexs[i].m_Position.x;
		y[i] = Vertexs[i].m_Position.y;
	}

	Render::PolyLine(x, y, count, colorLine);
}

void Render::Triangle(Vector2D left, Vector2D right, Vector2D dir, Color color)
{
	int x0, x1, y0, y1, dx, dy;
	x0 = left.x;
	x1 = right.x;
	y0 = left.y;
	y1 = right.y;
	dx = dir.x;
	dy = dir.y;
	Render::DrawLine(x0, y0, x1, y1, color); //base
	Render::DrawLine(x0, y0, dx, dy, color); //left to top
	Render::DrawLine(x1, y1, dx, dy, color); //right to top
	//comments apply when the triangle is orientated upwards, or if dir.y is positive
}
