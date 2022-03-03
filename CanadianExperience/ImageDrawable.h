/**
 * \file ImageDrawable.h
 *
 * \author Justin Vesche
 *
 * Class to draw images
 */

#pragma once
#include "Drawable.h"
#include <string>
#include <memory>

/**
* Class to draw images
*
* A drawable image is one part of an actor. Drawable images parts can be moved
* independently.
*/
class CImageDrawable : public CDrawable
{
public:
    /** \brief Default constructor disabled */
    CImageDrawable() = delete;
    /** \brief Copy constructor disabled */
    CImageDrawable(const CImageDrawable&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CImageDrawable&) = delete;

    CImageDrawable(const std::wstring& name, const std::wstring& filename);

    virtual void Draw(Gdiplus::Graphics* graphics);

    bool HitTest(Gdiplus::Point pos); 

    /** Set the center position
     * \param pos The new center*/
    void SetCenter(Gdiplus::Point pos) { mCenter = pos; }

    /** Get the center position
     * \returns The center position*/
    Gdiplus::Point GetCenter() const { return mCenter; }

protected:
    /// Our current image
    std::unique_ptr<Gdiplus::Bitmap> mImage;
private:
    /// The current location of the center image
    Gdiplus::Point mCenter = Gdiplus::Point(0, 0);
};

