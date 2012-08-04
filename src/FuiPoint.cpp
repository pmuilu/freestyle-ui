/*
 ============================================================================
 Name		: FuiPoint.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiPoint implementation
 ============================================================================
 */

#include <e32math.h>
#include <e32svr.h>
#include "FuiPoint.h"


TFuiPoint::TFuiPoint()
{
	SetPosition( TPoint( 0,0 ) );
}

TFuiPoint::TFuiPoint(const TPoint& aPosition,const TPoint& aTarget ) : 
	iPosition( aPosition ), iTarget( aTarget )
{
	
}

void TFuiPoint::SetPosition( const TPoint& aPosition )
{
	iPosition = aPosition;
	iTarget = iPosition;
}

void TFuiPoint::SetTarget( const TPoint& aTarget )
{
	iTarget.Set( aTarget );
	
	TReal xLength = Abs( iTarget.iX - iPosition.iX );
	TReal yLength = Abs( iTarget.iY - iPosition.iY );

	TReal xSpeed;
	Math::Sqrt( xSpeed, xLength );
	
	TReal ySpeed;
	Math::Sqrt( ySpeed, yLength );
	
	iXStep = xSpeed * 100.f;
	iYStep = ySpeed * 100.f;
}

void TFuiPoint::SetSpeed( TInt aUnitsPerSecond, const TTimeIntervalMicroSeconds& aInterval )
{
	TInt unitsPerSecond = aUnitsPerSecond << 16;
	TInt frames = 1000000 / aInterval.Int64();
	
	
}

TPoint TFuiPoint::Now() const
{
	return iPosition.Point();
}

TPoint TFuiPoint::Target() const
{
	return iTarget.Point();
}

void TFuiPoint::Run( TBool& aFinished )
{
	/*if( iPosition.iX < iTarget.iX )
	{
		iPosition.iX+=iXStep;
	}
	else if( iPosition.iX > iTarget.iX )
	{
		iPosition.iX-=iXStep;
	}*/
	
	/*if( iPosition.iY < iTarget.iY + 32768 )
	{
		iPosition.iY+=iYStep;
		return;
	}
	else*/
	
	if( iPosition.iY - iYStep > iTarget.iY )
	{
		iPosition.iY-=iYStep;
	}	
	else if( iPosition.iY + iYStep < iTarget.iY )
	{
		iPosition.iY+=iYStep;
	}	
	else
	{
		iPosition.iY = iTarget.iY;
		aFinished = ETrue;	
	}
	
	
}

TFuiFixPoint::TFuiFixPoint() : iX( 0 ), iY( 0 )
{
	
}

TFuiFixPoint::TFuiFixPoint( const TPoint& aPoint )
{
	Set( aPoint );
}

TPoint TFuiFixPoint::Point() const
{
	return TPoint( iX >> 16, iY >> 16 );
}
	
void TFuiFixPoint::Set( const TPoint& aPoint )
{
	iX = aPoint.iX << 16;
	iY = aPoint.iY << 16;
}
	
