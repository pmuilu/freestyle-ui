/*
 ============================================================================
 Name		: ToggleElement.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiToggleElement declaration
 ============================================================================
 */

#ifndef TOGGLEELEMENT_H
#define TOGGLEELEMENT_H

// INCLUDES
#include <w32std.h>
#include <e32std.h>
#include <e32base.h>
#include "freestyle.h"
#include "fuitimer.h"
#include "fuielementbase.h"

// CLASS DECLARATION

/**
 *  CFuiToggleElement
 * 
 */
class CFuiToggleElement: 
	public CFuiElementBase, 
	public MTimerEvent
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiToggleElement();

	/**
	 * Two-phased constructor.
	 */
	IMPORT_C static CFuiToggleElement* NewL();

public:
	/**
	 * Handle key event. 
	 * 
	 * @return ETrue if key was handled. 
	 */
	TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
	
	/**
	 * Handle pointer event.
	 * 
	 * @return ETrue if pointer event was handled. 
	 */
	void HandlePointerEventL( const TPointerEvent& aPointerEvent );

	/**
	 * Return current state. 
	 */
	inline TBool On();
	
	/**
	 * Set text
	 */
	IMPORT_C void SetText( const TDesC& aText );
	
	/**
	 * Set secondary text
	 */
	IMPORT_C void SetSecondaryText( const TDesC& aText );

protected: // from CCoeControl
	void SizeChanged();
	
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiToggleElement();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	/**
	 * Init graphics.
	 */
	void InitGraphicsL();
	
	/**
	 * Draw object to given rectangle. 
	 */
	virtual void DrawElement(const TRect& aRect) const;

private: // from MTimerEvent
	TBool Tick();
	
private:
	CFuiEnv* iFsEnv; // Not owned
	CFuiTimer* iTimer;
	CGulIcon* iLineBackground; // Not owned.
	CGulIcon* iToggleOptions; // Not owned
	CGulIcon* iToggleSwitch; // Not owned
	mutable TRect iCurrentRect;
	TInt iSwitchX;
	TInt iSwitchHeight;
	TBool iOn;
	HBufC* iText;
	HBufC* iSecondaryText;
};
	
inline TBool CFuiToggleElement::On()
{
	return iOn;
}

#endif // TOGGLEELEMENT_H
