/*
 ============================================================================
 Name		: FuiChoiceElement.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiToggleElement implementation
 ============================================================================
 */

#include "FuiChoiceElement.h"

#include "theme.mbg"


CFuiChoiceElement::CFuiChoiceElement()
{
	// No implementation required
}

CFuiChoiceElement::~CFuiChoiceElement()
{
	delete iTimer;
}

EXPORT_C CFuiChoiceElement* CFuiChoiceElement::NewL()
{
	CFuiChoiceElement* self = new (ELeave) CFuiChoiceElement();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiChoiceElement::ConstructL()
{
	// Get pointer to environment. Faster access. 
	iFsEnv = CFuiEnv::Static();
	
	// Create timer for animations. 
	iTimer = CFuiTimer::NewL( this );

	// Set default position and size for this element. 
	TRect drawableRect = iFsEnv->DrawableRect();
	SetRect( TRect( drawableRect.iTl, TSize( drawableRect.Size().iWidth, 40 ) ) );

	// Init graphics for this element. 
	InitGraphicsL();
	
}

/**
 * Init graphics.
 */
void CFuiChoiceElement::InitGraphicsL()
{
	CFuiTheme* theme = iFsEnv->Theme();
	
	iLineBackground = theme->SvgIconL( EMbmThemeLinebackground, Rect().Size() );
}

/**
 * Draw object to given rectangle. 
 */
void CFuiChoiceElement::DrawElement( const TRect& aRect ) const
{
	RDebug::Print( _L("[log] Element DRAW") );
	
	CFbsBitGc& gc = iFsEnv->Gc();
	
	CGulIcon* background = iLineBackground;
	
	TRect elementRect = Rect();
	TSize elementSize = elementRect.Size();
	
	// Draw background first.
	if( background )
	{
		gc.BitBltMasked( aRect.iTl, 
				background->Bitmap(), 
				elementSize, 
				background->Mask(), 
				EFalse );
	}

	// Create draw area so that elements have small
	// gap to borders. 
	TRect drawArea( aRect.iTl, elementSize );
	drawArea.Shrink( 3, 3 );
	
}

void CFuiChoiceElement::SizeChanged()
{
	
}

/**
 * Handle key event. 
 * 
 * @return ETrue if key was handled. 
 */
TKeyResponse CFuiChoiceElement::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
{
	RDebug::Print( _L("[FUI] offerkeyevent") );
	
	DrawNow();
	
	if( aKeyEvent.iScanCode == EStdKeyDevice3 )
	{
		iTimer->Start( 4000 );
		
		return EKeyWasConsumed;
	}
	
	return EKeyWasNotConsumed;
}

void CFuiChoiceElement::HandlePointerEventL( const TPointerEvent& aPointerEvent )
{
	
}
/**
 * Set choices
 */
void CFuiChoiceElement::SetChoices( CDesCArray* aChoices )
{
	iChoices = aChoices;
}

TBool CFuiChoiceElement::Tick()
{
	TBool ret = EFalse;
	
	
	Redraw();
	
	return ret;
}
