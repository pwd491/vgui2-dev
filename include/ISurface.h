/*
Copyright (C) 2022 Bien Pham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

In addition, as a special exception, the author gives permission
to link the code of this program with VGUI library developed by
Valve, L.L.C ("Valve"). You must obey the GNU General Public License
in all respects for all of the code used other than VGUI library.
If you modify this file, you may extend this exception to your
version of the file, but you are not obligated to do so. If
you do not wish to do so, delete this exception statement
from your version.

*/

#ifndef ISURFACE_H
#define ISURFACE_H

#include "Color.h"
#include "IAppSystem.h"
#include "VGUI2.h"
#include "VGuiVertex.h"
#include "interface.h"

class IHTMLResponses;
class IHTMLChromeController;

namespace vgui2
{

class IHTML;
class IHTMLEvents;

class ISurface : public IBaseInterface, public IAppSystem
{
public:
	enum SurfaceFeature_e
	{
		ANTIALIASED_FONTS = 1,
		DROPSHADOW_FONTS = 2,
		ESCAPE_KEY = 3,
		OPENING_NEW_HTML_WINDOWS = 4,
		FRAME_MINIMIZE_MAXIMIZE = 5,
		DIRECT_HWND_RENDER = 6,
	};

	enum EFontFlags
	{
		FONTFLAG_NONE,
		FONTFLAG_ITALIC = 0x001,
		FONTFLAG_UNDERLINE = 0x002,
		FONTFLAG_STRIKEOUT = 0x004,
		FONTFLAG_SYMBOL = 0x008,
	};

	virtual void Shutdown() = 0;
	virtual void RunFrame() = 0;
	virtual VPANEL GetEmbeddedPanel() = 0;
	virtual void SetEmbeddedPanel( VPANEL panel ) = 0;
	virtual void PushMakeCurrent( VPANEL panel, bool useInsets ) = 0;
	virtual void PopMakeCurrent( VPANEL panel ) = 0;
	virtual void DrawSetColor( int r, int g, int b, int a ) = 0;
	virtual void DrawSetColor( Color col ) = 0;
	virtual void DrawFilledRect( int x0, int y0, int x1, int y1 ) = 0;
	virtual void DrawOutlinedRect( int x0, int y0, int x1, int y1 ) = 0;
	virtual void DrawLine( int x0, int y0, int x1, int y1 ) = 0;
	virtual void DrawPolyLine( int *px, int *py, int numPoints ) = 0;
	virtual void DrawSetTextFont( HFont font ) = 0;
	virtual void DrawSetTextColor( int r, int g, int b, int a ) = 0;
	virtual void DrawSetTextColor( Color col ) = 0;
	virtual void DrawSetTextPos( int x, int y ) = 0;
	virtual void DrawGetTextPos( int &x, int &y ) = 0;
	virtual void DrawPrintText( const wchar_t *text, int textLen ) = 0;
	virtual void DrawUnicodeChar( wchar_t wch ) = 0;
	virtual void DrawUnicodeCharAdd( wchar_t wch ) = 0;
	virtual void DrawFlushText() = 0;
	virtual IHTML *CreateHTMLWindow( IHTMLEvents *events, VPANEL context ) = 0;
	virtual void PaintHTMLWindow( IHTML *htmlwin ) = 0;
	virtual void DeleteHTMLWindow( IHTML *htmlwin ) = 0;
	virtual void DrawSetTextureFile( int id, const char *filename, int hardwareFilter, bool forceReload ) = 0;
	virtual void DrawSetTextureRGBA( int id, const unsigned char *rgba, int wide, int tall, int hardwareFilter, bool forceReload ) = 0;
	virtual void DrawSetTexture( int id ) = 0;
	virtual void DrawGetTextureSize( int id, int &wide, int &tall ) = 0;
	virtual void DrawTexturedRect( int x0, int y0, int x1, int y1 ) = 0;
	virtual bool IsTextureIDValid( int id ) = 0;
	virtual int CreateNewTextureID( bool procedural ) = 0;
	virtual void GetScreenSize( int &wide, int &tall ) = 0;
	virtual void SetAsTopMost( VPANEL panel, bool state ) = 0;
	virtual void BringToFront( VPANEL panel ) = 0;
	virtual void SetForegroundWindow( VPANEL panel ) = 0;
	virtual void SetPanelVisible( VPANEL panel, bool state ) = 0;
	virtual void SetMinimized( VPANEL panel, bool state ) = 0;
	virtual bool IsMinimized( VPANEL panel ) = 0;
	virtual void FlashWindow( VPANEL panel, bool state ) = 0;
	virtual void SetTitle( VPANEL panel, const wchar_t *title ) = 0;
	virtual void SetAsToolBar( VPANEL panel, bool state ) = 0;
	virtual void CreatePopup( VPANEL panel, bool minimised, bool showTaskbarIcon, bool disabled, bool mouseInput, bool kbInput ) = 0;
	virtual void SwapBuffers( VPANEL panel ) = 0;
	virtual void Invalidate( VPANEL panel ) = 0;
	virtual void SetCursor( HCursor cursor ) = 0;
	virtual bool IsCursorVisible() = 0;
	virtual void ApplyChanges() = 0;
	virtual bool IsWithin( int x, int y ) = 0;
	virtual bool HasFocus() = 0;
	virtual bool SupportsFeature( SurfaceFeature_e feature ) = 0;
	virtual void RestrictPaintToSinglePanel( VPANEL panel ) = 0;
	virtual void SetModalPanel( VPANEL panel ) = 0;
	virtual VPANEL GetModalPanel() = 0;
	virtual void UnlockCursor() = 0;
	virtual void LockCursor() = 0;
	virtual void SetTranslateExtendedKeys( bool state ) = 0;
	virtual VPANEL GetTopmostPopup() = 0;
	virtual void SetTopLevelFocus( VPANEL panel ) = 0;
	virtual HFont CreateFont() = 0;
	virtual bool AddGlyphSetToFont( HFont font, const char *fontName, int tall, int weight, int blur, int scanlines, int flags, int lowRange, int highRange ) = 0;
	virtual bool AddCustomFontFile( const char *fontFileName ) = 0;
	virtual int GetFontTall( HFont font ) = 0;
	virtual void GetCharABCwide( HFont font, int ch, int &a, int &b, int &c ) = 0;
	virtual int GetCharacterWidth( HFont font, int ch ) = 0;
	virtual void GetTextSize( HFont font, const wchar_t *text, int &wide, int &tall ) = 0;
	virtual VPANEL GetNotifyPanel() = 0;
	virtual void SetNotifyIcon( VPANEL context, HTexture icon, VPANEL panelToReceiveMessages, const char *text ) = 0;
	virtual void PlaySound( const char *fileName ) = 0;
	virtual int GetPopupCount() = 0;
	virtual VPANEL GetPopup( int index ) = 0;
	virtual bool ShouldPaintChildPanel( VPANEL panel ) = 0;
	virtual bool RecreateContext( VPANEL panel ) = 0;
	virtual void AddPanel( VPANEL panel ) = 0;
	virtual void ReleasePanel( VPANEL panel ) = 0;
	virtual void MovePopupToFront( VPANEL panel ) = 0;
	virtual void MovePopupToBack( VPANEL panel ) = 0;
	virtual void SolveTraverse( VPANEL panel, bool forceApplySchemeSettings ) = 0;
	virtual void PaintTraverse( VPANEL panel ) = 0;
	virtual void EnableMouseCapture( VPANEL panel, bool state ) = 0;
	virtual void GetWorkspaceBounds( int &x, int &y, int &wide, int &tall ) = 0;
	virtual void GetAbsoluteWindowBounds( int &x, int &y, int &wide, int &tall ) = 0;
	virtual void GetProportionalBase( int &width, int &height ) = 0;
	virtual void CalculateMouseVisible() = 0;
	virtual bool NeedKBInput() = 0;
	virtual bool HasCursorPosFunctions() = 0;
	virtual void SurfaceGetCursorPos( int &x, int &y ) = 0;
	virtual void SurfaceSetCursorPos( int x, int y ) = 0;
	virtual void DrawTexturedPolygon( VGuiVertex *pVertices, int n ) = 0;
	virtual int GetFontAscent( HFont font, wchar_t wch ) = 0;
	virtual void SetAllowHTMLJavaScript( bool state ) = 0;
	virtual void SetLanguage( const char *pchLang ) = 0;
	virtual const char *GetLanguage() = 0;
	virtual bool DeleteTextureByID( int id ) = 0;
	virtual void DrawUpdateRegionTextureBGRA( int nTextureID, int x, int y, const unsigned char *pchData, int wide, int tall ) = 0;
	virtual void DrawSetTextureBGRA( int id, const unsigned char *bgra, int wide, int tall ) = 0;
	virtual void CreateBrowser( VPANEL panel, IHTMLResponses *pBrowser, bool bPopupWindow, const char *pchUserAgentIdentifier ) = 0;
	virtual void RemoveBrowser( VPANEL panel, IHTMLResponses *pBrowser ) = 0;
	virtual IHTMLChromeController *AccessChromeHTMLController() = 0;
	virtual void DrawTexturedRectAdd( int x0, int y0, int x1, int y1 ) = 0;
	virtual void SetSupportsEsc( bool bSupportsEsc ) = 0;
	virtual int GetFontBlur( vgui2::HFont font ) = 0;
	virtual bool IsAdditive( vgui2::HFont font ) = 0;
	virtual void SetProportionalBase( int width, int height ) = 0;
	virtual void GetHDProportionalBase( int &width, int &height ) = 0;
	virtual void SetHDProportionalBase( int nWidth, int nHeight ) = 0;
};

#define VGUI_SURFACE_INTERFACE_VERSION "VGUI_Surface026"

} // namespace vgui2

#endif // ISURFACE_H
