/*
 ============================================================================
 Name		: SurfaceControl.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiControl declaration
 ============================================================================
 */

#ifndef SURFACECONTROL_H
#define SURFACECONTROL_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include "FuiSurface.h"
#include "FuiTheme.h"
#include "FuiPoint.h"
class CFuiEnv;
class CFuiElementBase;

// CLASS DECLARATION

/**
 *  CFuiControl
 * 
 */
class CFuiControl: 
	public CCoeControl, 
	public MUISurface	
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiControl();

	/**
	 * Two-phased constructor.
	 */
	IMPORT_C static CFuiControl* NewL();

public: // from MUISurface
	
	/**
	 * Append element on the surface. 
	 */
	IMPORT_C void Append( CFuiElementBase* aObject );
	
	/**
	 * Insert element to specific position on the surface. 
	 */
	IMPORT_C void Insert( CFuiElementBase* aObject, TInt aIndex );
	
	/**
	 * Remove element from the surface.
	 */
	IMPORT_C void Remove( CFuiElementBase* aObject );

	/**
	 * Offer key event. 
	 */
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
	 
private: // from CCoeControl
    void Draw(const TRect& aRect) const;
    	
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    
    void InitGraphicsL();
    void CalculateVariablesL();
    
private:
	CCoeControl* GetFocusedControl();
	
	void Animate();
	static TInt Tick(TAny* aObject);
	TInt DoTick();
	
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiControl();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

private:
	RPointerArray<CFuiElementBase> iUIObjects;
	CFuiEnv* iFsEnv;
	
	TFuiPoint iSurfacePos;
	TFuiPoint iHighlightPos;
	TPoint iGap;
	mutable TPoint iAppendPos;
	TInt iSelectedIndex;
	CPeriodic* iTimer;
	
	// Not owned. 
	CFbsBitmap* iBackground;
};

#endif // SURFACECONTROL_H
