/**
 * \file HeadTop.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "HeadTop.h"
#include "Timeline.h"


using namespace Gdiplus;

/** Constructor
* \param name The drawable name
* \param filename The filename for the image */
CHeadTop::CHeadTop(const std::wstring& name, const std::wstring& filename) : CImageDrawable(name, filename)
{

}

/// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/**
 * Draw the image drawable
 * \param graphics Graphics context to draw on
 */
void CHeadTop::Draw(Gdiplus::Graphics* graphics)
{
    CImageDrawable::Draw(graphics);

    DrawEye(graphics, mEye1);

    DrawEye(graphics, mEye2);

    DrawEyebrow(graphics, mEyebrowStart1 - mOffsetEyebrow, mEyebrowEnd1 - mOffsetEyebrow);

    DrawEyebrow(graphics, mEyebrowStart2 - mOffsetEyebrow, mEyebrowEnd2 - mOffsetEyebrow);
    
}

/**
 * Draw the image drawable
 * \param graphics Graphics context to draw on
 * \param point Point we will draw at
 */
void CHeadTop::DrawEye(Gdiplus::Graphics* graphics, Gdiplus::Point point)
{
    float wid = 15.0f;
    float hit = 20.0f;

    auto state = graphics->Save();
    Point p = TransformPoint(point);
    graphics->TranslateTransform(p.X, p.Y);
    graphics->RotateTransform((float)(-mPlacedR * RtoD));
    SolidBrush brush(Color::Black);
    graphics->FillEllipse(&brush, -wid / 2, -hit / 2, wid, hit);
    graphics->Restore(state);

}

/**
 * Draw the image drawable
 * \param graphics Graphics context to draw on
 * \param point1 Point1 we will draw at
 * \param point2 Point2 we will end at
 */
void CHeadTop::DrawEyebrow(Gdiplus::Graphics* graphics, Gdiplus::Point point1, Gdiplus::Point point2)
{

    
    Pen eyebrowPen(Color::Black, 2);
    graphics->DrawLine(&eyebrowPen, TransformPoint(point1), TransformPoint(point2));
 
}




/** Transform a point from a location on the bitmap to
*  a location on the screen.
* \param  p Point to transform
* \returns Transformed point
*/
Gdiplus::Point CHeadTop::TransformPoint(Gdiplus::Point p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}



/** Set the keyframe based on the current status.
*/
void CHeadTop::SetKeyframe()
{
    CDrawable::SetKeyframe();
    mChannelPoint.SetKeyframe(GetPosition());
}

/** Get the current channel from the animation system.
*/
void CHeadTop::GetKeyframe()
{
    CDrawable::GetKeyframe();
    if (mChannelPoint.IsValid())
        SetPosition(mChannelPoint.GetPoint());
}

/** Add the channels for this drawable to a timeline
 * \param timeline The timeline class.
 */
void CHeadTop::SetTimeline(CTimeline* timeline)
{
    CDrawable::SetTimeline(timeline);
    timeline->AddChannel(&mChannelPoint);
    
}
