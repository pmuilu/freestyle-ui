/*
 ============================================================================
 Name		: FuiTimer.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiTimer implementation
 ============================================================================
 */

#include "FuiTimer.h"

CFuiTimer::CFuiTimer( MTimerEvent* aEvent ) : iEvent( aEvent )
{
	// No implementation required
}

CFuiTimer::~CFuiTimer()
{
	delete iTimer;
}

CFuiTimer* CFuiTimer::NewL( MTimerEvent* aEvent )
{
	CFuiTimer* self = new (ELeave) CFuiTimer( aEvent );
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(); // self;
	return self;
}

void CFuiTimer::ConstructL()
{
	// Initialise timer, this is used for animations. 
	iTimer = CPeriodic::NewL( CActive::EPriorityIdle );
}
/**
 * Start timing
 */
void CFuiTimer::Start( TTimeIntervalMicroSeconds32 aInterval )
{
	if( !iTimer->IsActive() )
	{
		iTimer->Start( 0, aInterval, TCallBack(Tick, this) );
	}
}

TInt CFuiTimer::Tick(TAny* aObject)
{
    return ((CFuiTimer*)aObject)->DoTick();
}

TInt CFuiTimer::DoTick()
{
	if( !iEvent->Tick() )
	{
		iTimer->Cancel();
	}
}

