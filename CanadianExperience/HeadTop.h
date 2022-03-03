/**
 * \file ImageDrawable.h
 *
 * \author Justin Vesche
 *
 * Class to draw the head top
 */

#pragma once
#include "ImageDrawable.h"
#include "AnimChannelPoint.h"

/**
* Abstract base class for head elements of our picture.
*
* The head is one part of an actor. Drawable head parts can be adjusted
* independently.
*/
class CHeadTop : public CImageDrawable
{
public:
    /** \brief Default constructor disabled */
    CHeadTop() = delete;
    /** \brief Copy constructor disabled */
    CHeadTop(const CHeadTop&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CHeadTop&) = delete;

    CHeadTop(const std::wstring& name, const std::wstring& filename);
   
    virtual void Draw(Gdiplus::Graphics* graphics);

    Gdiplus::Point TransformPoint(Gdiplus::Point p);

    /** Get if is moveable
    * \returns true unless overwritten*/
    virtual bool IsMovable() { return true; };

    void CHeadTop::DrawEye(Gdiplus::Graphics* graphics, Gdiplus::Point point);

    void CHeadTop::DrawEyebrow(Gdiplus::Graphics* graphics, Gdiplus::Point point1, Gdiplus::Point point2);

    /** Set the eye location of eye1
     * \param pos The new eye1 location*/
    void SetEye1(Gdiplus::Point pos) { mEye1 = pos; }

    /** Get the location of eye1
     * \returns eye1 pos*/
    Gdiplus::Point GetEye1() const { return mEye1; }

    /** Set the eye location of eye2
    * \param pos The new eye2 location*/
    void SetEye2(Gdiplus::Point pos) { mEye2 = pos; }

    /** Get the location of eye2
     * \returns eye2 pos*/
    Gdiplus::Point GetEye2() const { return mEye2; }

    /** Set the eye location of Eyebrowstart1
    * \param pos The new Eyebrowstart1 location*/
    void SetEyebrowStart1(Gdiplus::Point pos) { mEyebrowStart1 = pos; }
    /** Set the eye location of EyebrowStart2
    * \param pos The new eye2 location*/
    void SetEyebrowStart2(Gdiplus::Point pos) { mEyebrowStart2 = pos; }
    /** Set the eye location of EyebrowEnd1
    * \param pos The new EyebrowEnd1 location*/
    void SetEyebrowEnd1(Gdiplus::Point pos) { mEyebrowEnd1 = pos; }
    /** Set the eye location of EyebrowEnd2
    * \param pos The new EyebrowEnd2 location*/
    void SetEyebrowEnd2(Gdiplus::Point pos) { mEyebrowEnd2 = pos; }

    /** Set the eyebrow offset if needed
    * \param pos The new Eyebrow offset*/
    void SetEyebrowOffset(Gdiplus::Point pos) { mOffsetEyebrow = pos; }

    virtual void SetKeyframe();

    virtual void GetKeyframe();

    virtual void SetTimeline(CTimeline* timeline);

private:
    /// Location of eye 1
    Gdiplus::Point mEye1 = Gdiplus::Point(40.0f, 80.0f);
    /// Location of eye 2
    Gdiplus::Point mEye2 = Gdiplus::Point(70.0f, 80.0f);

    /// Location of eyebrow part 1 start
    Gdiplus::Point mEyebrowStart1 = Gdiplus::Point(65.0f, 60.0f);
    /// Location of eyebrow part 1 end
    Gdiplus::Point mEyebrowEnd1 = Gdiplus::Point(80.0f, 63.0f);

    /// Location of eyebrow part 2 start
    Gdiplus::Point mEyebrowStart2 = Gdiplus::Point(30.0f, 63.0f);
    /// Location of eyebrow part 2 end
    Gdiplus::Point mEyebrowEnd2 = Gdiplus::Point(45.0f, 60.0f);
    
    /// Eyebrow offset
    Gdiplus::Point mOffsetEyebrow = Gdiplus::Point(0.0f, 0.0f);
    
    /// The animation channel for animating the angle of this drawable
    CAnimChannelPoint mChannelPoint;

};

