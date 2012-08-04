/*
 ============================================================================
 Name		: FuiElementBase.h
 Author	  : Petteri Muilu
 Version	 : 1.0
 Copyright   : (C) Copyright 2008 Petteri Muilu
 Description : CFuiElementBase declaration
 ============================================================================
 */

#ifndef FUIELEMENTBASE_H
#define FUIELEMENTBASE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
// CLASS DECLARATION

class CEikRichTextEditor;

/**
 *  CFuiElementBase
 * 
 */
class CFuiElementBase: public CCoeControl
		
{
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
	~CFuiElementBase();

	/**
	 * Called when element is added to surface and really used. 
	 */
	virtual void ElementConstructL();
	
	/**
	 * Draw the element.
	 */
	virtual void DrawElement(const TRect& aRect) const;

	/**
	 * Return editor if there is such. 
	 */
	virtual CEikRichTextEditor* Editor();
	
	/**
	 * Draw this element to surface. 
	 */
	void Redraw();
	
	
protected:

	/**
	 * Constructor for performing 1st stage construction
	 */
	CFuiElementBase();

};

#endif // FUIELEMENTBASE_H
