/*
 ============================================================================
 Name		: ToggleElement.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiToggleElement implementation
 ============================================================================
 */

#include "FuiToggleElement.h"

#include "theme.mbg"


CFuiToggleElement::CFuiToggleElement()
{
	// No implementation required
}

CFuiToggleElement::~CFuiToggleElement()
{
	delete iText;
	delete iSecondaryText;
	delete iTimer;
}

EXPORT_C CFuiToggleElement* CFuiToggleElement::NewL()
{
	CFuiToggleElement* self = new (ELeave) CFuiToggleElement();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiToggleElement::ConstructL()
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
void CFuiToggleElement::InitGraphicsL()
{
	CFuiTheme* theme = iFsEnv->Theme();
	
	iLineBackground = theme->SvgIconL( EMbmThemeLinebackground, Rect().Size() );
	iToggleSwitch = theme->SvgIconL( EMbmThemeToggle_switch );
	iToggleOptions = theme->SvgIconL( EMbmThemeToggle_options );
	
	if( iToggleSwitch )
	{
		iSwitchHeight = iToggleSwitch->Bitmap()->SizeInPixels().iHeight;
	}
}

/**
 * Draw object to given rectangle. 
 */
void CFuiToggleElement::DrawElement( const TRect& aRect ) const
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
	
	// Draw toggle options (On/Off) 
	TSize toggleSize;
	TPoint togglePos;
	
	CGulIcon* toggleOptions = iToggleOptions;
	
	if( toggleOptions )
	{
		toggleSize = toggleOptions->Bitmap()->SizeInPixels();
		togglePos = TPoint( drawArea.Width() - toggleSize.iWidth + drawArea.iTl.iX, 
				    		drawArea.iTl.iY );
		
		iCurrentRect = TRect( togglePos, toggleSize );
		
		gc.BitBltMasked( togglePos, 
				toggleOptions->Bitmap(), 
				toggleSize, 
				toggleOptions->Mask(), 
				EFalse );
	}

	// Draw toggle switch, it is drawn over toggle options
	// so that one option is always hidden. 
	CGulIcon* toggleSwitch = iToggleSwitch;
	
	if( toggleSwitch )
	{
		TSize switchSize = toggleSwitch->Bitmap()->SizeInPixels();
		TPoint switchPos = togglePos + TPoint( 0, iSwitchX );
		
		gc.BitBltMasked( switchPos, 
				toggleSwitch->Bitmap(), 
				switchSize, 
				toggleSwitch->Mask(), 
				EFalse );
	}
	
	TRect textArea( aRect.iTl, TSize( elementSize.iWidth - toggleSize.iWidth, elementSize.iHeight ) );

	if( !iSecondaryText )
	{
		if( iText )
		{
			// TODO: color from theme?
			gc.SetPenColor( KRgbBlack );
			gc.SetPenStyle( CWindowGc::ESolidPen );
			gc.SetBrushStyle( CWindowGc::ENullBrush );
			
			CFont* font = iFsEnv->Font17Bold();
			
			TInt baseLine = textArea.Height() / 2 + font->HeightInPixels() / 2 - 3;
						
			gc.UseFont( font );
			gc.DrawText( iText->Des(), textArea, baseLine, CWindowGc::ECenter );
			gc.DiscardFont();
		}
	}
	else
	{
		TRect textArea1( textArea.iTl, TSize( textArea.Width(), textArea.Height() / 2 ) );
		TRect textArea2( textArea.iTl + TPoint( 0, textArea1.Height() ), TSize( textArea1.Width(), textArea1.Height() ) );
		
		if( iText )
		{
			// TODO: color from theme?
			gc.SetPenColor( KRgbBlack );
			gc.SetPenStyle( CWindowGc::ESolidPen );
			gc.SetBrushStyle( CWindowGc::ENullBrush );
									
			CFont* titleFont = iFsEnv->Font14Bold();
			CFont* textFont = iFsEnv->Font12Plain();
			
			gc.UseFont( titleFont );
			gc.DrawText( iText->Des(), textArea1, titleFont->HeightInPixels(), CWindowGc::ECenter );
			gc.DiscardFont();
			
			gc.UseFont( textFont );
			gc.DrawText( iText->Des(), textArea2, textFont->HeightInPixels(), CWindowGc::ECenter );
			gc.DiscardFont();
		}
	}
		
}

void CFuiToggleElement::SizeChanged()
{
	
}

/**
 * Handle key event. 
 * 
 * @return ETrue if key was handled. 
 */
TKeyResponse CFuiToggleElement::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
{
	RDebug::Print( _L("[FUI] offerkeyevent") );
	
	DrawNow();
	
	if( aKeyEvent.iScanCode == EStdKeyDevice3 )
	{
		iOn = !iOn;
		
		iTimer->Start( 4000 );
		
		return EKeyWasConsumed;
	}
	
	return EKeyWasNotConsumed;
}

/**
 * Handle pointer event.
 * 
 * @return ETrue if pointer event was handled. 
 */
void CFuiToggleElement::HandlePointerEventL( const TPointerEvent& aPointerEvent )
{
	if( aPointerEvent.iType == TPointerEvent::EButton1Up )
	{
		if( iCurrentRect.Contains( aPointerEvent.iPosition) )
		{
			iOn = !iOn;
			iTimer->Start( 4000 );
		}
	}
}

/**
 * Set text
 */
EXPORT_C void CFuiToggleElement::SetText( const TDesC& aText )
{
	if( iText )
	{
		delete iText;
		iText = NULL;
	}
	
	iText = aText.Alloc();
}

/**
 * Set secondary text
 */
EXPORT_C void CFuiToggleElement::SetSecondaryText( const TDesC& aText )
{
	if( iSecondaryText )
	{
		delete iSecondaryText;
		iSecondaryText = NULL;
	}
	
	iSecondaryText = aText.Alloc();
}


TBool CFuiToggleElement::Tick()
{
	TBool ret = EFalse;
	
	if( iOn )
	{
		if( iSwitchX < iSwitchHeight )
		{
			iSwitchX += 1;
			ret = ETrue;
		}
	}
	else
	{
		if( iSwitchX > 0 )
		{
			iSwitchX -= 1;
			ret = ETrue;
		}
	}
	
	Redraw();
	
	return ret;
}
