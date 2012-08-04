/*
 ============================================================================
 Name		: ToggleElement.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiToggleElement implementation
 ============================================================================
 */

#include <barsread.h>
#include <txtrich.h>
#include <freestyle.rsg>
#include "FuiEditorElement.h"
#include "theme.mbg"


CFuiEditorElement::CFuiEditorElement()
{
	// No implementation required
}

CFuiEditorElement::~CFuiEditorElement()
{
	delete iText;
}

EXPORT_C CFuiEditorElement* CFuiEditorElement::NewL()
{
	CFuiEditorElement* self = new (ELeave) CFuiEditorElement();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiEditorElement::ConstructL()
{
	// Get pointer to environment. Faster access. 
	iFsEnv = CFuiEnv::Static();
}

/**
 * Element constructor, called when element is added to surface. 
 */
void CFuiEditorElement::ElementConstructL()
{
	// Set default position and size for this element. 
	TRect drawableRect = iFsEnv->DrawableRect();
	SetRect( TRect( drawableRect.iTl, TSize( drawableRect.Size().iWidth, 50 ) ) );

	// Init graphics for this element. 
	InitGraphicsL();
	
	// Create text field. 
	iEditor = CreateTextFieldL( Parent(), KRgbBlack );
	
	iEditorBaseRect = Rect();
	iEditorBaseRect.Shrink( 5, 0 );
	iEditorBaseRect.SetHeight( 20 );
}


/**
 * Init graphics.
 */
void CFuiEditorElement::InitGraphicsL()
{
	CFuiTheme* theme = iFsEnv->Theme();
	
	iLineBackground = theme->SvgIconL( EMbmThemeLinebackground, Rect().Size() );
}

/**
 * Draw object to given rectangle. 
 */
void CFuiEditorElement::DrawElement( const TRect& aRect ) const
{
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
	TRect textArea1( textArea.iTl, TSize( textArea.Width(), textArea.Height() / 2 ) );
	TRect textArea2( textArea.iTl + TPoint( 0, textArea1.Height() ), TSize( textArea1.Width(), textArea1.Height() ) );
	
	iEditor->SetRect( TRect( iEditorBaseRect.iTl + textArea2.iTl,
				iEditorBaseRect.Size() ) );
	
	gc.SetPenColor( KRgbBlack );
	gc.SetBrushColor( KRgbWhite );
	gc.SetPenSize( TSize( 1, 1 ) );
	gc.SetPenStyle( CWindowGc::ESolidPen );
	gc.SetBrushStyle( CWindowGc::ESolidBrush );
	
	TRect editorBorder( iEditor->Rect() );
	editorBorder.Grow( 1, 1 );
	gc.DrawRect( editorBorder );
	
	if( iEditor )
	{
		HBufC* text = iEditor->GetTextInHBufL();
	
		TRect editorTextArea( iEditor->Rect() );
		editorTextArea.Shrink( 2, 1 );
			
		if( text )
		{
			gc.UseFont( iEditorFont );
			gc.DrawText( text->Des(), editorTextArea, iEditorFont->HeightInPixels() );
			gc.DiscardFont();
		}
	}
		
	
	if( iText )
	{
		// TODO: color from theme?
		gc.SetPenColor( KRgbBlack );
		gc.SetPenStyle( CWindowGc::ESolidPen );
		gc.SetBrushStyle( CWindowGc::ENullBrush );
		
		CFont* font = iFsEnv->Font14Bold();
		
		TInt baseLine = textArea1.Height() / 2 + font->HeightInPixels() / 2 - 3;
					
		gc.UseFont( font );
		gc.DrawText( iText->Des(), textArea1, baseLine, CWindowGc::ECenter );
		gc.DiscardFont();
	}
}

void CFuiEditorElement::SizeChanged()
{
	
}

void CFuiEditorElement::FocusChanged(TDrawNow aDrawNow)
{
	iEditor->SetFocus( IsFocused(), EDrawNow );
	Redraw();
}
	
/**
 * Handle key event. 
 * 
 * @return ETrue if key was handled. 
 */
TKeyResponse CFuiEditorElement::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
{
	if( iEditor )
	{
		return iEditor->OfferKeyEventL( aKeyEvent, aType );
	}

	return EKeyWasNotConsumed;
}

/**
 * Handle pointer event.
 * 
 * @return ETrue if pointer event was handled. 
 */
void CFuiEditorElement::HandlePointerEventL( const TPointerEvent& aPointerEvent )
{
	if( aPointerEvent.iType == TPointerEvent::EButton1Up )
	{
		if( iCurrentRect.Contains( aPointerEvent.iPosition) )
		{
		}
	}
}

/**
 * Set text
 */
EXPORT_C void CFuiEditorElement::SetText( const TDesC& aText )
{
	if( iText )
	{
		delete iText;
		iText = NULL;
	}
	
	iText = aText.Alloc();
}

CEikRichTextEditor* CFuiEditorElement::CreateTextFieldL( CCoeControl* aParent, TRgb aFontColor )
{
	CEikRichTextEditor* editor = new (ELeave) CEikRichTextEditor;
	editor->SetContainerWindowL( *aParent );
	
	TResourceReader reader;
	CCoeEnv::Static()->CreateResourceReaderLC (reader, R_RICH_TEXT_EDITOR );
	editor->ConstructFromResourceL (reader);
	CleanupStack::PopAndDestroy (); // reader
	
	editor->SetFocus (ETrue);
	editor->EnableCcpuSupportL (ETrue);
	editor->SetBorder(TGulBorder::ESingleBlack);
	
	iEditorFont = iFsEnv->Font14Plain();
	
	TCharFormat charFormat;
	charFormat.iFontSpec = iEditorFont->FontSpecInTwips(); 
	
	TCharFormatMask charFormatMask;
	charFormat.iFontPresentation.iTextColor = aFontColor;
	charFormatMask.SetAttrib (EAttColor);
	charFormatMask.SetAttrib (EAttFontTypeface);
	charFormatMask.SetAttrib (EAttFontHeight);
	
	CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
	charFormatLayer->Sense(charFormat, charFormatMask);
	charFormatLayer->SetL(charFormat, charFormatMask);
	editor->SetCharFormatLayer (charFormatLayer);

	return editor;
}

TInt CFuiEditorElement::CountComponentControls() const
{
	return 1;
}

CCoeControl* CFuiEditorElement::ComponentControl(TInt aIndex) const
{
	return iEditor;
}

CEikRichTextEditor* CFuiEditorElement::Editor()
{
	return iEditor;
}
