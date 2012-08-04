/*
 ============================================================================
 Name		: ToggleElement.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiChoiceElement declaration
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
 *  CFuiChoiceElement
 * 
 */
class CFuiChoiceElement: 
	public CFuiElementBase, 
	public MTimerEvent
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiChoiceElement();

	/**
	 * Two-phased constructor.
	 */
	IMPORT_C static CFuiChoiceElement* NewL();

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
	inline TBool SelectedIndex();

	/**
	 * Set choices
	 */
	void SetChoices( CDesCArray* aChoices );
	
protected: // from CCoeControl
	void SizeChanged();
	
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiChoiceElement();

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
	CDesCArray* iChoices;
	TInt iSelectedIndex;
	mutable TRect iCurrentRect;
};
	
inline TInt CFuiChoiceElement::SelectedIndex()
{
	return iSelectedIndex;
}

#endif // TOGGLEELEMENT_H
