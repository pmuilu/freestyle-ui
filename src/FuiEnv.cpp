/*
 ============================================================================
 Name		: FreestyleEnv.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiEnv implementation
 ============================================================================
 */

#include <coemain.h>
#include <aknappui.h> 
#include "FuiEnv.h"
#include "FuiTheme.h"
#include "FuiControl.h"
#include "Freestyle.pan"


CFuiEnv::CFuiEnv() : CCoeStatic( KUidFreestyleEnv, CCoeStatic::EApp )
{
	// No implementation required
}

CFuiEnv::~CFuiEnv()
{
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i10pxPlain );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i10pxBold );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i12pxPlain );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i12pxBold );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i14pxPlain );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i14pxBold );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i17pxPlain );
	CCoeEnv::Static()->ScreenDevice()->ReleaseFont( i17pxBold );
		
    delete iGc;
	delete iDevice;
	delete iScreenBitmap;
	delete iTheme;
}

EXPORT_C CFuiEnv* CFuiEnv::Static()
{
	CFuiEnv* self = static_cast<CFuiEnv*>( CCoeEnv::Static()->FindStatic( KUidFreestyleEnv ) );

	if(!self)
	{
		CFuiEnv* self = new (ELeave) CFuiEnv();
		TRAPD( err, self->ConstructL() );
		__ASSERT_ALWAYS( !err, Panic( KFsPanicEnvInitFailed ) );
	}
	
	return self;
}

void CFuiEnv::ConstructL()
{
	// Create graphics context. 
	HandleSizeChangedEventL();
	
	// Create fonts
	CreateFontsL();
	
	// Add freestyle resource file to eikon environment.
	TFileName resourceName;
	GetResourcePath( resourceName, KFreestyleRsc );
	CEikonEnv::Static()->AddResourceFileL( resourceName );
}

/**
 * Add control to control stack. 
 */
EXPORT_C void CFuiEnv::AddControl( CFuiControl* aControl )
{
	iControlStack.Append( aControl );
}

/**
 * Switch to another control.
 */
EXPORT_C void CFuiEnv::SwitchToControl( CFuiControl* aControl )
{
	TInt indx = iControlStack.Find( aControl );
	
	if( indx >= 0 )
	{
		// Do the magic. 
		iCurrentControl = aControl;
	}
}

/**
 * Remove control from control stack.
 */
EXPORT_C void CFuiEnv::RemoveControl( CFuiControl* aControl )
{
	TInt indx = iControlStack.Find( aControl );
	
	if( indx >= 0 )
	{
		iControlStack.Remove( indx );
	}
}

/**
 * Create fonts;
 */
void CFuiEnv::CreateFontsL()
{
	i10pxPlain = CreateFont( 10, EFalse, EFalse );
	i10pxBold = CreateFont( 10, ETrue, EFalse );
	i12pxPlain = CreateFont( 12, EFalse, EFalse );
	i12pxBold = CreateFont( 12, ETrue, EFalse );
	i14pxPlain = CreateFont( 14, EFalse, EFalse );
	i14pxBold = CreateFont( 14, ETrue, EFalse );
	i17pxPlain = CreateFont( 17, EFalse, EFalse );
	i17pxBold = CreateFont( 17, ETrue, EFalse );
}


/**
 * Get drawable rectangle for freestyle control.  
 */
TRect CFuiEnv::DrawableRect()
{
	CAknAppUi* appUi = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
	TRect appRect = TRect( TPoint( 0,0 ), appUi->ClientRect().Size() );
	return appRect;
}

/**
 * Get window rect.  
 */
TRect CFuiEnv::WindowRect()
{
	CAknAppUi* appUi = static_cast<CAknAppUi*>( CCoeEnv::Static()->AppUi() );
	TRect appRect = appUi->ClientRect();
	return appRect;
}

/**
 * Size changed.
 */
void CFuiEnv::HandleSizeChangedEventL()
{
	CCoeEnv* coeEnv = CCoeEnv::Static();
	
	if( iScreenBitmap )
	{
		delete iScreenBitmap;
		iScreenBitmap = NULL;
	}
	
	iScreenBitmap = new (ELeave)CWsBitmap(coeEnv->WsSession());
	User::LeaveIfError( iScreenBitmap->Create( WindowRect().Size(), coeEnv->ScreenDevice()->DisplayMode() ) );
	
	if( iGc )
	{
		delete iGc;
		iGc = NULL;
	}
	
	iGc = CFbsBitGc::NewL();
	
	if( iDevice )
	{
		delete iDevice;
		iDevice = NULL;
	}
	
	iDevice = CFbsBitmapDevice::NewL(iScreenBitmap);
	
	iGc->Activate( iDevice );
	iGc->SetBrushColor( KRgbWhite );
	iGc->Clear();
}

/**
 * Set current theme.
 */
EXPORT_C void CFuiEnv::SetCurrentTheme( const TDesC& aThemeName )
{
	if( iTheme )
	{
		delete iTheme;
		iTheme = NULL;
	}
	
	TRAPD( err, 
	{
		iTheme = CFuiTheme::NewL( aThemeName );
	} );
	
	__ASSERT_ALWAYS( !err, Panic( KFsPanicThemeInitFailed ) );
}

CFont* CFuiEnv::CreateFont( TInt aSizeInPixels, TBool aBold, TBool aItalic )
{
	CFont* font = NULL;
	
    TFontSpec fontSpec = CCoeEnv::Static()->NormalFont()->FontSpecInTwips();
    fontSpec.iHeight = aSizeInPixels;
    fontSpec.iFontStyle.SetBitmapType( EAntiAliasedGlyphBitmap );
    fontSpec.iFontStyle.SetStrokeWeight( EStrokeWeightNormal );
    
    if( aBold )
    {
        fontSpec.iFontStyle.SetStrokeWeight( EStrokeWeightBold );
    }
    
    if( aItalic )
    {
        fontSpec.iFontStyle.SetPosture( EPostureItalic );
    }
    
    if( CCoeEnv::Static()->ScreenDevice()->GetNearestFontInPixels( font, fontSpec ) == KErrNone )
    {
    	return font;
    }
    else
    {
    	TFontSpec fontSpec = CCoeEnv::Static()->NormalFont()->FontSpecInTwips();
    	fontSpec.iHeight = aSizeInPixels;
    	CCoeEnv::Static()->ScreenDevice()->GetNearestFontInPixels( font, fontSpec );
    	return font;
    }
}

/**
 * Get path to resource directory
 */
void CFuiEnv::GetResourcePath( TDes& aFileName, const TDesC& aResourceName )
{
	aFileName.Copy( KResourcePath );
	aFileName[0] = RProcess().FileName()[0];
	aFileName.Append( aResourceName );
}



