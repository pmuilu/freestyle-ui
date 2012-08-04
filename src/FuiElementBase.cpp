/*
 ============================================================================
 Name		: FuiElementBase.cpp
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiElementBase implementation
 ============================================================================
 */
#include <eikrted.h> 
#include <eikseced.h> 
#include "FuiElementBase.h"

CFuiElementBase::CFuiElementBase()
{
	// No implementation required
}

CFuiElementBase::~CFuiElementBase()
{
}

/**
 * Draw the element.
 */
void CFuiElementBase::DrawElement(const TRect& /*aRect*/) const
{
}

/**
 * Called when element is added to surface and really used. 
 */
void CFuiElementBase::ElementConstructL()
{
}

/**
 * Return editor if there is such. 
 */
CEikRichTextEditor* CFuiElementBase::Editor()
{
	return NULL;
}

/**
 * Draw this element to surface. 
 */
void CFuiElementBase::Redraw()
{
	Parent()->DrawNow();
}



