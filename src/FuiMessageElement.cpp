/*
 ============================================================================
 Name		: ToggleElement.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiMessageElement implementation
 ============================================================================
 */
#include <aknutils.h> 
#include "FuiMessageElement.h"
#include "theme.mbg"


CFuiMessageElement::CFuiMessageElement()
{
	// No implementation required
}

CFuiMessageElement::~CFuiMessageElement()
{
	delete iText;
	delete iTimer;
	delete iWrappedText;
}

EXPORT_C CFuiMessageElement* CFuiMessageElement::NewL()
{
	CFuiMessageElement* self = new (ELeave) CFuiMessageElement();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiMessageElement::ConstructL()
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
void CFuiMessageElement::InitGraphicsL()
{
	CFuiTheme* theme = iFsEnv->Theme();
	
	if(iLineBackground)
	{
		delete iLineBackground;
		iLineBackground = NULL;
	}
	
	iLineBackground = theme->SvgIconL( EMbmThemeLinebackground, Rect().Size() );
}

/**
 * Draw object to given rectangle. 
 */
void CFuiMessageElement::DrawElement( const TRect& aRect ) const
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
	
	TRect textArea( aRect.iTl, TSize( elementSize.iWidth, elementSize.iHeight ) );

	if( !iWrappedText )
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
		CFont* titleFont = iFsEnv->Font14Bold();
		CFont* textFont = iFsEnv->Font12Plain();
					
		TRect textArea1( textArea.iTl, TSize( textArea.Width(), titleFont->HeightInPixels() ) );
		TRect textArea2( textArea.iTl + TPoint( 0, textArea1.Height() ), TSize( textArea1.Width(), textArea1.Height() ) );
		
		if( iText )
		{
			// TODO: color from theme?
			gc.SetPenColor( KRgbBlack );
			gc.SetPenStyle( CWindowGc::ESolidPen );
			gc.SetBrushStyle( CWindowGc::ENullBrush );
									
				gc.UseFont( titleFont );
			gc.DrawText( iText->Des(), textArea1, titleFont->HeightInPixels(), CWindowGc::ECenter );
			gc.DiscardFont();
			
			gc.UseFont( textFont );
				
			TInt y = 0;
			for( TInt i=0;i<iWrappedText->Count();i++ )
			{
				gc.DrawText( (*iWrappedText)[i], textArea2, textFont->HeightInPixels(), CWindowGc::ECenter );
				textArea2.Move( 0, textFont->HeightInPixels() );
			}
			gc.DiscardFont();
		}
	}
}

void CFuiMessageElement::SizeChanged()
{
	
}

/**
 * Handle key event. 
 * 
 * @return ETrue if key was handled. 
 */
TKeyResponse CFuiMessageElement::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
{
	return EKeyWasNotConsumed;
}

/**
 * Handle pointer event.
 * 
 * @return ETrue if pointer event was handled. 
 */
void CFuiMessageElement::HandlePointerEventL( const TPointerEvent& aPointerEvent )
{
}

/**
 * Set text
 */
EXPORT_C void CFuiMessageElement::SetText( const TDesC& aText )
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
EXPORT_C void CFuiMessageElement::SetSecondaryText( const TDesC& aText )
{
	if( iWrappedText )
	{
		delete iWrappedText;
		iWrappedText = NULL;
	}
	
	iWrappedText = new(ELeave)CDesCArrayFlat(5);
	
	CArrayFixFlat<TPtrC>* wrappedArray = new(ELeave)CArrayFixFlat<TPtrC>(5);
	CleanupStack::PushL(wrappedArray);
	
	CFont* textFont = iFsEnv->Font12Plain();
	AknTextUtils::WrapToArrayL( aText, Rect().Width(), *textFont, *wrappedArray );
	
	for(TInt i=0;i<wrappedArray->Count();i++)
	{
		iWrappedText->AppendL((*wrappedArray)[i]);
	}
	
	// Set default position and size for this element. 
	TRect drawableRect = iFsEnv->DrawableRect();
	SetRect(TRect(drawableRect.iTl, 
			TSize(drawableRect.Size().iWidth, 40 + (wrappedArray->Count()-1)*textFont->HeightInPixels())));

	InitGraphicsL();
	
	CleanupStack::PopAndDestroy(); //wrappedArray
}


TBool CFuiMessageElement::Tick()
{
	TBool ret = EFalse;
	
	Redraw();
	
	return ret;
}
