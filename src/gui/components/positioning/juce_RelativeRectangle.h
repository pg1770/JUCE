/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-10 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_RELATIVERECTANGLE_JUCEHEADER__
#define __JUCE_RELATIVERECTANGLE_JUCEHEADER__

#include "juce_RelativeCoordinate.h"
class Component;

//==============================================================================
/**
    An rectangle stored as a set of RelativeCoordinate values.

    The rectangle's top, left, bottom and right edge positions are each stored as a RelativeCoordinate.

    @see RelativeCoordinate, RelativePoint
*/
class JUCE_API  RelativeRectangle
{
public:
    //==============================================================================
    /** Creates a zero-size rectangle at the origin. */
    RelativeRectangle();

    /** Creates an absolute rectangle, relative to the origin. */
    explicit RelativeRectangle (const Rectangle<float>& rect, const String& componentName);

    /** Creates a rectangle from four coordinates. */
    RelativeRectangle (const RelativeCoordinate& left, const RelativeCoordinate& right,
                       const RelativeCoordinate& top, const RelativeCoordinate& bottom);

    /** Creates a rectangle from a stringified representation.
        The string must contain a sequence of 4 coordinates, separated by commas, in the order
        left, top, right, bottom. The syntax for the coordinate strings is explained in the
        RelativeCoordinate class.
        @see toString
    */
    explicit RelativeRectangle (const String& stringVersion);

    bool operator== (const RelativeRectangle& other) const throw();
    bool operator!= (const RelativeRectangle& other) const throw();

    //==============================================================================
    /** Calculates the absolute position of this rectangle.

        You'll need to provide a suitable Expression::EvaluationContext for looking up any coordinates that may
        be needed to calculate the result.
    */
    const Rectangle<float> resolve (const Expression::EvaluationContext* evaluationContext) const;

    /** Changes the values of this rectangle's coordinates to make it resolve to the specified position.

        Calling this will leave any anchor points unchanged, but will set any absolute
        or relative positions to whatever values are necessary to make the resultant position
        match the position that is provided.
    */
    void moveToAbsolute (const Rectangle<float>& newPos, const Expression::EvaluationContext* evaluationContext);

    /** Returns true if this rectangle depends on any other coordinates for its position. */
    bool isDynamic() const;

    /** Returns a string which represents this point.
        This returns a comma-separated list of coordinates, in the order left, top, right, bottom. For details of
        the string syntax used by the coordinates, see the RelativeCoordinate constructor notes.
        The string that is returned can be passed to the RelativeRectangle constructor to recreate the rectangle.
    */
    const String toString() const;

    /** Renames a symbol if it is used by any of the coordinates.
        This calls RelativeCoordinate::renameSymbolIfUsed() on the rectangle's coordinates.
    */
    void renameSymbolIfUsed (const String& oldName, const String& newName);

    /** Creates and sets an appropriate Component::Positioner object for the given component, which will
        keep it positioned with this rectangle.
    */
    void applyToComponent (Component& component) const;

    //==============================================================================
    // The actual rectangle coords...
    RelativeCoordinate left, right, top, bottom;
};


#endif   // __JUCE_RELATIVERECTANGLE_JUCEHEADER__