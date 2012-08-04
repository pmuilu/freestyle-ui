/*
 ============================================================================
 Name		: Surface.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CSurface declaration
 ============================================================================
 */

#ifndef SURFACE_H
#define SURFACE_H

// INCLUDES
#include <w32std.h>
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>

class CFuiElementBase;

// CLASS DECLARATION
class MUISurface
{
public:
	/**
	 * Append MUIObject to Surface. 
	 */
	virtual void Append( CFuiElementBase* aObject ) = 0;
	
	/**
	 * Remove MUIObject from Surface.
	 */
	virtual void Remove( CFuiElementBase* aObject ) = 0;
};

#endif // SURFACE_H
