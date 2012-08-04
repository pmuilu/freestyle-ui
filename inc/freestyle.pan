/*
 ============================================================================
 Name		: freestyle.pan
 Author	  : Petteri Muilu
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : Panic codes
 ============================================================================
 */

#ifndef __FREESTYLE_PAN__
#define __FREESTYLE_PAN__

//  Data Types

enum TfreestylePanic
{
	EfreestyleNullPointer,
	KFsPanicEnvInitFailed,
	KFsPanicThemeInitFailed
};

//  Function Prototypes

GLREF_C void Panic(TfreestylePanic aPanic);

#endif  // __FREESTYLE_PAN__

