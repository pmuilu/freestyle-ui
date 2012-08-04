/*
 ============================================================================
 Name		: freestyle.h
 Author	  : Petteri Muilu
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : freestyle.h - Cfreestyle class header
 ============================================================================
 */

#ifndef __FREESTYLE_H__
#define __FREESTYLE_H__

#include <e32base.h>
#include <e32std.h>
#include "fuisurface.h"
#include "fuicontrol.h"
#include "fuienv.h"
#include "fuitoggleelement.h"
#include "fuieditorelement.h"
#include "fuimessageelement.h"
#include "fuitheme.h"

inline void InitFreestyle(const TDesC& aThemeName)
{
	CFuiEnv::Static();
	CFuiEnv::Static()->SetCurrentTheme(aThemeName);
}

inline void DestroyFreestyle()
{
	delete CFuiEnv::Static();
}

#endif  // __FREESTYLE_H__

