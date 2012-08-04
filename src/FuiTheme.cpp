/*
 ============================================================================
 Name		: Theme.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiTheme implementation
 ============================================================================
 */

#include <akniconutils.h>
#include <bautils.h>
#include <coemain.h>
#include "FuiTheme.h"
#include "FuiEnv.h"

_LIT( KMifExt, ".mif");

CFuiTheme::CFuiTheme()
{
	// No implementation required
}

CFuiTheme::~CFuiTheme()
{
	iElements.ResetAndDestroy();
}

CFuiTheme* CFuiTheme::NewL( const TDesC& aTheme )
{
	CFuiTheme* self = new (ELeave) CFuiTheme();
	CleanupStack::PushL(self);
	self->ConstructL(aTheme);
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiTheme::ConstructL( const TDesC& aTheme )
{
	LoadThemeL( aTheme );
}

/**
 * Load theme 
 */
void CFuiTheme::LoadThemeL( const TDesC& aTheme )
{
	iName.Copy( aTheme );
	
	TFileName svgFile;
	SvgFile( svgFile );
	RDebug::Print( _L("[FUI] Setting up SVG: %S"), &svgFile );
	
	if( !BaflUtils::FileExists( CCoeEnv::Static()->FsSession(), svgFile ) )
	{
		User::Leave( KErrNotFound );
	}
}


/**
 * Load svg element.
 */
CFbsBitmap* CFuiTheme::SvgElementL( TInt aElementId )
{
	TFileName svgFile;
	SvgFile( svgFile );
	
    CFbsBitmap* a = new (ELeave)CFbsBitmap();
    User::LeaveIfError( a->Load( svgFile, aElementId ) );
    
    TSize contentSize;
    AknIconUtils::PreserveIconData( a );
    AknIconUtils::GetContentDimensions( a, contentSize );
    AknIconUtils::SetSize( a, contentSize );
    AknIconUtils::DestroyIconData( a );
    	
    iElements.Append( a );
    
    return a;
}

/**
 * Load svg element and scale it to given size. 
 */
CFbsBitmap* CFuiTheme::SvgElementL( TInt aElementId, const TSize& aSize )
{
	RDebug::Print(_L("[log] CFuiTheme: %d"),__LINE__);
	TFileName svgFile;
	SvgFile( svgFile );
	RDebug::Print(_L("[log] CFuiTheme: %d"),__LINE__);
	
	CFbsBitmap* a = AknIconUtils::CreateIconL( svgFile, aElementId );
	AknIconUtils::SetSize( a, aSize, EAspectRatioNotPreserved );
	iElements.Append( a );

	RDebug::Print(_L("[log] CFuiTheme: %d"),__LINE__);
	
    return a;
}

/**
 * Load svg element.
 */
CGulIcon* CFuiTheme::SvgIconL( TInt aElementId )
{
	CFbsBitmap* a = NULL;
	CFbsBitmap* b = NULL;
	
	TFileName svgFile;
	SvgFile( svgFile );
		
	AknIconUtils::CreateIconL( a, b, svgFile, aElementId, aElementId );
		
	CGulIcon* c = CGulIcon::NewL( a, b );
	
	AknIconUtils::PreserveIconData( c->Bitmap() );
	AknIconUtils::PreserveIconData( c->Mask() );
	
	TSize contentSize;
	AknIconUtils::GetContentDimensions( c->Bitmap(), contentSize );
	
	AknIconUtils::SetSize( c->Bitmap(), contentSize );
	AknIconUtils::SetSize( c->Mask(), contentSize );
	
	AknIconUtils::DestroyIconData( c->Bitmap() );
	AknIconUtils::DestroyIconData( c->Mask() );
	
	iElements.Append( c );
	
	return c;
}

/**
 * Load svg element and scale it to given size. 
 */
 CGulIcon* CFuiTheme::SvgIconL( TInt aElementId, const TSize& aSize )
{
	CFbsBitmap* a = NULL;
	CFbsBitmap* b = NULL;
	
	TFileName svgFile;
	SvgFile( svgFile );
		
	AknIconUtils::CreateIconL( a, b, svgFile, aElementId, aElementId );
	
	CGulIcon* c = CGulIcon::NewL( a, b );
	
	AknIconUtils::SetSize( c->Bitmap(), aSize, EAspectRatioNotPreserved );
	AknIconUtils::SetSize( c->Mask(), aSize, EAspectRatioNotPreserved );
	
	iElements.Append( c );
	
	return c;
}

/**
 * Return SVG filename. 
 */
void CFuiTheme::SvgFile( TDes& aFileName )
{
		
	aFileName.Append( KResourcePath );
	aFileName.Append( iName );
	aFileName.Append( KMifExt );
	
	aFileName[0] = RProcess().FileName()[0];
}



