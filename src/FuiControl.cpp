/*
 ============================================================================
 Name		: SurfaceControl.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiControl implementation
 ============================================================================
 */
#include <eikrted.h> 
#include <eikseced.h> 
#include "FuiControl.h"
#include "FuiEnv.h"
#include "FuiElementBase.h"
#include "theme.mbg"


CFuiControl::CFuiControl()
{
	// No implementation required
}

CFuiControl::~CFuiControl()
{
	delete iTimer;
	
	iUIObjects.ResetAndDestroy();
	iUIObjects.Close();
}

EXPORT_C CFuiControl* CFuiControl::NewL()
{
	CFuiControl* self = new (ELeave) CFuiControl();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiControl::ConstructL()
{
	// Get pointer to freestyle environment.
	iFsEnv = CFuiEnv::Static();
	
	// Create a window for this application view
	CreateWindowL();
	
	// Set size for this window. 
	SetRect(iFsEnv->WindowRect());
	
	// Initialise timer, this is used for animations. 
	iTimer = CPeriodic::NewL( CActive::EPriorityIdle );

	// Init graphics 
	InitGraphicsL();
	
	// Pre-calculate UI variables.
	CalculateVariablesL();
	
	// Activate window.
	ActivateL();
}

void CFuiControl::InitGraphicsL()
{
	CFuiTheme* theme = iFsEnv->Theme();
	iBackground = theme->SvgElementL( EMbmThemeBackground, Rect().Size() ); 
}

void CFuiControl::CalculateVariablesL()
{
	iGap = TPoint( 0, 0 );
	
	iSurfacePos.SetSpeed( 10, 4000 );
}

void CFuiControl::Draw(const TRect& /*aRect*/) const
{
	RDebug::Print( _L("[log] Control DRAW") );
	CFbsBitGc& gc = iFsEnv->Gc();
	
	gc.SetBrushColor( KRgbWhite );
	
	if( iBackground )
	{
		gc.BitBlt( TPoint( 0,0 ), iBackground );
	}
	
	TPoint pos;
	
	for( TInt i=0;i<iUIObjects.Count();i++ )
	{
		TRect objectRect = iUIObjects[i]->Rect();
		TSize objectSize = objectRect.Size();
		TPoint objectPos = pos + iSurfacePos.Now() + objectRect.iTl;
		
		iUIObjects[i]->DrawElement( TRect( objectPos, objectSize ) );
		
		pos.iY+=objectSize.iHeight + iGap.iY;
	}
	
	gc.SetBrushStyle( CWindowGc::ENullBrush );
	gc.SetPenStyle( CWindowGc::ESolidPen );
	gc.SetPenColor( KRgbWhite );
	gc.SetPenSize( TSize( 2, 2 ) );
	
	if( iSelectedIndex < iUIObjects.Count() )
	{
		TRect objectRect = iUIObjects[iSelectedIndex]->Rect();
	
		gc.DrawRect( TRect( iHighlightPos.Now(), 
				objectRect.Size() ) );
	}
	
	SystemGc().BitBlt( TPoint( 0,0 ), 
			iFsEnv->Screen() );

}
    
EXPORT_C TKeyResponse CFuiControl::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
{
	// Handle surface control keys first. 
	switch( aKeyEvent.iScanCode )
	{
	case EStdKeyUpArrow:
		if( aType == EEventKey )
		{
			if( iSelectedIndex > 0 && iSelectedIndex < iUIObjects.Count() )
			{
				TInt objHeight = iUIObjects[iSelectedIndex-1]->Rect().Height() + iGap.iY;
				
				if( iHighlightPos.Now().iY - objHeight >= 0 )
				{
					iHighlightPos.SetPosition( iHighlightPos.Target() - TPoint( 0, objHeight ) );
					Animate();
				}
				else
				{
					TInt fixPos = 0;
					if( iHighlightPos.Now().iY - objHeight < 0 )
					{
						fixPos = iHighlightPos.Now().iY;
						iHighlightPos.SetPosition( iHighlightPos.Target() - TPoint( 0, fixPos ) );
					}
					
					iSurfacePos.SetTarget( iSurfacePos.Target() + TPoint( 0, objHeight - fixPos ) );
					Animate();
				}
				
				iUIObjects[iSelectedIndex]->SetFocus( EFalse );
				iSelectedIndex--;
				iUIObjects[iSelectedIndex]->SetFocus( ETrue );
				
				return EKeyWasConsumed;
			}
		}
		break;
	case EStdKeyDownArrow:
		if( aType == EEventKey )
		{
			if( iSelectedIndex < iUIObjects.Count() - 1 )
			{
				TInt nextHeight = iUIObjects[iSelectedIndex+1]->Rect().Height() + iGap.iY;
				
				if( iHighlightPos.Now().iY + nextHeight + nextHeight < Rect().Height() )
				{
					TInt objHeight = iUIObjects[iSelectedIndex]->Rect().Height();
					iHighlightPos.SetPosition( iHighlightPos.Target() + TPoint( 0, objHeight + iGap.iY ) );
					Animate();
				}
				else
				{
					TInt objHeight = iUIObjects[iSelectedIndex]->Rect().Height();
					iSurfacePos.SetTarget( iSurfacePos.Target() - TPoint( 0, objHeight + iGap.iY ) );
					Animate();
				}
				
				iUIObjects[iSelectedIndex]->SetFocus( EFalse );
				iSelectedIndex++;
				iUIObjects[iSelectedIndex]->SetFocus( ETrue );
				
				return EKeyWasConsumed;
			}
		}
		break;
	}
	
	// It seems that this was not surface control key event, 
	// pass it to currently focused control. 
	CCoeControl* control = GetFocusedControl();
	
	if( control )
	{
		return control->OfferKeyEventL( aKeyEvent, aType );
	}
	
	return EKeyWasNotConsumed;
}
    
void CFuiControl::HandlePointerEventL( const TPointerEvent& aPointerEvent )
{
	for( TInt i=0;i<iUIObjects.Count();i++ )
	{
		iUIObjects[i]->HandlePointerEventL( aPointerEvent );
	}
}

void CFuiControl::SizeChanged()
{
	iFsEnv->HandleSizeChangedEventL();
}

CCoeControl* CFuiControl::GetFocusedControl()
{
	if( iSelectedIndex < iUIObjects.Count() )
	{
		return iUIObjects[iSelectedIndex];
	}
	else
	{
		return NULL;
	}
}
   
void CFuiControl::Animate()
{
	if( !iTimer->IsActive() )
	{
		iTimer->Start( 4000,4000,TCallBack(Tick, this) );
	}
}

TInt CFuiControl::Tick(TAny* aObject)
{
    return ((CFuiControl*)aObject)->DoTick();
}

TInt CFuiControl::DoTick()
{
	TBool finished = EFalse;
	iSurfacePos.Run( finished );
	
	if( finished )
	{
		finished = EFalse;
		iHighlightPos.Run( finished );
		
		if( finished )
		{
			iTimer->Cancel();
		}
	}

	DrawDeferred();

	return KErrNone;
}

/**
 * Append MUIObject to Surface. 
 */
EXPORT_C void CFuiControl::Append( CFuiElementBase* aObject )
{
	if( aObject )
	{
		aObject->SetParent( this );
		aObject->ElementConstructL();
		iUIObjects.Append( aObject );
	}
}

/**
 * Append MUIObject to Surface. 
 */
EXPORT_C void CFuiControl::Insert( CFuiElementBase* aObject, TInt aIndex )
{
	if( aObject )
	{
		aObject->SetParent( this );
		aObject->ElementConstructL();
		
		if( iUIObjects.Count() >= aIndex )
		{
			iUIObjects.Insert(aObject,aIndex);
		}
		else
		{
			iUIObjects.Append( aObject );
		}
	}
}

/**
 * Remove MUIObject from Surface.
 */
EXPORT_C void CFuiControl::Remove( CFuiElementBase* /*aObject*/ )
{
	
}

TInt CFuiControl::CountComponentControls() const
{
	if( iSelectedIndex < iUIObjects.Count() )
	{
		if( iUIObjects[iSelectedIndex]->Editor() )
		{
			return 1;
		}
	}
	
	return 0;
}

CCoeControl* CFuiControl::ComponentControl(TInt aIndex) const
{
	return iUIObjects[iSelectedIndex]->Editor();
}

