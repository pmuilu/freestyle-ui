/*
 ============================================================================
 Name		: FuiTimer.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : Easy to use wrapper for CPeriodic timer. 
 ============================================================================
 */

#ifndef FUITIMER_H
#define FUITIMER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>

// CLASS DECLARATION

class MTimerEvent
{
public:
	virtual TBool Tick() = 0;
};

/**
 *  CFuiTimer
 * 
 */
class CFuiTimer: public CBase
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiTimer();

	/**
	 * Two-phased constructor.
	 */
	static CFuiTimer* NewL( MTimerEvent* aEvent );

	/**
	 * Start timing
	 */
	void Start( TTimeIntervalMicroSeconds32 aInterval );
	
	/**
	 * Tick
	 */
	static TInt Tick(TAny* aObject);
	
	/**
	 * Do the tick.
	 */
	TInt DoTick();

private:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiTimer( MTimerEvent* aEvent );

	/**
	 * EPOC default constructor for performing 2nd stage construction
	 */
	void ConstructL();

private:
	CPeriodic* iTimer;
	MTimerEvent* iEvent;
};

#endif // FUITIMER_H
