/*
 ============================================================================
 Name		: FuiPoint.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiPoint declaration
 ============================================================================
 */

#ifndef FUIPOINT_H
#define FUIPOINT_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

class TFuiFixPoint
{
public:
	TFuiFixPoint();
	TFuiFixPoint( const TPoint& aPoint );
	
	TPoint Point() const;
	void Set( const TPoint& aPoint );
	
public:
	TInt64 iX;
	TInt64 iY;
};

/**
 *  CFuiPoint
 * 
 */
class TFuiPoint
{
public:
	// Constructors and destructor
	TFuiPoint();	
	TFuiPoint(const TPoint& aPosition,const TPoint& aTarget );
	
	void SetPosition( const TPoint& aPosition );
	void SetTarget( const TPoint& aTarget );
	void SetSpeed( TInt aUnitsPerSecond, const TTimeIntervalMicroSeconds& aInterval );
	
	TPoint Now() const;
	TPoint Target() const;
	
	void Run( TBool& aFinished );
	
private:
	TFuiFixPoint iPosition;
	TFuiFixPoint iTarget;
	
	TInt64 iXStep;
	TInt64 iYStep;
};

#endif // FUIPOINT_H
