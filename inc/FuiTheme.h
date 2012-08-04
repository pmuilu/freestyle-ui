/*
 ============================================================================
 Name		: Theme.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiTheme declaration
 ============================================================================
 */

#ifndef THEME_H
#define THEME_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <gulicon.h>
#include <fbs.h>
// CLASS DECLARATION

/**
 *  CFuiTheme
 * 
 */
class CFuiTheme: public CBase
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiTheme();

	/**
	 * Two-phased constructor.
	 */
	static CFuiTheme* NewL( const TDesC& aTheme );

public:
	/**
	 * Current name of the theme
	 */
	inline TPtrC Name();
	
	/**
	 * Load svg element.
	 */
	CFbsBitmap* SvgElementL( TInt aElementId );
	
	/**
	 * Load svg element and scale it to given size. 
	 */
	CFbsBitmap* SvgElementL( TInt aElementId, const TSize& aSize );
	
	/**
	 * Load svg element.
	 */
	CGulIcon* SvgIconL( TInt aElementId );
	
	/**
	 * Load svg element and scale it to given size. 
	 */
	CGulIcon* SvgIconL( TInt aElementId, const TSize& aSize );
		
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiTheme();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL( const TDesC& aTheme );
	
	/**
	 * Load theme 
	 */
	void LoadThemeL( const TDesC& aTheme );

private:
	/**
	 * Return SVG filename. 
	 */
	void SvgFile( TDes& aFileName );

private:
	TBuf<255> iName;
	RPointerArray<CBase> iElements;
};

inline TPtrC CFuiTheme::Name()
{
	return iName;
}

#endif // THEME_H
