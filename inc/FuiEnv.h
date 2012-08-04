/*
 ============================================================================
 Name		: FreestyleEnv.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiEnv declaration
 ============================================================================
 */

#ifndef FREESTYLEENV_H
#define FREESTYLEENV_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coemain.h>

class CFuiTheme;
class CFuiControl;

// CLASS DECLARATION
const TUid KUidFreestyleEnv = {0x20026D02};

_LIT( KResourcePath, "!:\\resource\\apps\\" );
_LIT( KFreestyleRsc, "freestyle.rsc" );

/**
 *  CFuiEnv
 * 
 */
class CFuiEnv: public CCoeStatic
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	virtual ~CFuiEnv();

public: // Exported functions
	/**
	 * Two-phased constructor.
	 */
	IMPORT_C static CFuiEnv* Static();
	
	/**
	 * Set current theme.
	 */
	IMPORT_C void SetCurrentTheme( const TDesC& aThemeName );

	/**
	 * Add control to control stack. 
	 */
	IMPORT_C void AddControl( CFuiControl* aControl );
	
	/**
	 * Switch to another control.
	 */
	IMPORT_C void SwitchToControl( CFuiControl* aControl );
	
	/**
	 * Remove control from control stack.
	 */
	IMPORT_C void RemoveControl( CFuiControl* aControl );
	
public: // Others
	/**
	 * Get drawable rectangle for freestyle control.  
	 */
	TRect DrawableRect();
	
	/**
	 * Get window rect
	 */
	TRect WindowRect();
	
	/**
	 * Size changed.
	 */
	void HandleSizeChangedEventL();
	
	/**
	 * Return graphics context
	 */
	inline CFbsBitGc& Gc();
	
	/**
	 * Return screen bitmap
	 */
	inline CWsBitmap* Screen();

	/**
	 * Get current theme.
	 */
	inline CFuiTheme* Theme();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font10Plain();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font10Bold();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font12Plain();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font12Bold();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font14Plain();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font14Bold();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font17Plain();
	
	/**
	 * Get font 12px, plain.
	 */
	inline CFont* Font17Bold();
	
	/**
	 * Get path to resource directory
	 */
	void GetResourcePath( TDes& aFileName, const TDesC& aResourceName );

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiEnv();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	/**
	 * Create fonts;
	 */
	void CreateFontsL();
	
	/**
	 * Create font. 
	 */
	CFont* CreateFont( TInt aSizeInPixels, TBool aBold, TBool aItalic );
	
private:
    CFbsBitGc* iGc;
    CWsBitmap* iScreenBitmap;
    CFbsBitmapDevice* iDevice;
    CFuiTheme* iTheme;
    
    CFont* i10pxPlain;
    CFont* i10pxBold;
    CFont* i12pxPlain;
    CFont* i12pxBold;
    CFont* i14pxPlain;
    CFont* i14pxBold;
    CFont* i17pxPlain;
    CFont* i17pxBold;
    
    RPointerArray<CFuiControl> iControlStack;
    CFuiControl* iCurrentControl;
};

// Inline functions

inline CFbsBitGc& CFuiEnv::Gc()
{
	return *iGc;
}

inline CWsBitmap* CFuiEnv::Screen()
{
	return iScreenBitmap;
}

/**
 * Get theme.
 */
inline CFuiTheme* CFuiEnv::Theme()
{
	return iTheme;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font10Plain()
{
	return i10pxPlain;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font10Bold()
{
	return i10pxBold;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font12Plain()
{
	return i12pxPlain;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font12Bold()
{
	return i12pxBold;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font14Plain()
{
	return i14pxPlain;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font14Bold()
{
	return i14pxBold;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font17Plain()
{
	return i17pxPlain;
}

/**
 * Get font 12px, plain.
 */
inline CFont* CFuiEnv::Font17Bold()
{
	return i17pxBold;
}

#endif // FREESTYLEENV_H
