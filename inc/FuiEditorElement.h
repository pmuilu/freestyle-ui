/*
 ============================================================================
 Name		: ToggleElement.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiToggleElement declaration
 ============================================================================
 */

#ifndef EDITORELEMENT_H
#define EDITORELEMENT_H

// INCLUDES
#include <w32std.h>
#include <e32std.h>
#include <e32base.h>
#include <eikenv.h>
#include <eikrted.h> 
#include <eikseced.h> 
#include "freestyle.h"
#include "fuitimer.h"
#include "fuielementbase.h"

// CLASS DECLARATION

/**
 *  CFuiEditorElement
 * 
 */
class CFuiEditorElement: 
	public CFuiElementBase	
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiEditorElement();

	/**
	 * Two-phased constructor.
	 */
	IMPORT_C static CFuiEditorElement* NewL();

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
	 * Set text
	 */
	IMPORT_C void SetText( const TDesC& aText );
	
	
protected: // from CCoeControl
	void SizeChanged();
	
	void FocusChanged(TDrawNow aDrawNow);
	
private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiEditorElement();

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();
	
	/**
	 * Element constructor, called when element is added to surface. 
	 */
	void ElementConstructL();
	
	/**
	 * Init graphics.
	 */
	void InitGraphicsL();
	
	/**
	 * Draw object to given rectangle. 
	 */
	virtual void DrawElement(const TRect& aRect) const;

	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	CEikRichTextEditor* CreateTextFieldL( CCoeControl* aParent, TRgb aFontColor );
	
	CEikRichTextEditor* Editor();
	
private:
	CFuiEnv* iFsEnv; // Not owned
	CGulIcon* iLineBackground; // Not owned.
	mutable CEikRichTextEditor* iEditor;
	mutable TRect iCurrentRect;
	TRect iEditorBaseRect;
	HBufC* iText;
	CFont *iEditorFont;
};

#endif // TOGGLEELEMENT_H


