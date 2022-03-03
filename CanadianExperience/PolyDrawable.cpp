/**
 * \file PolyDrawable.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include<vector>
#include "PolyDrawable.h"

using namespace Gdiplus;
using namespace std; 

/** Destructor */
CPolyDrawable::~CPolyDrawable()
{
}

/**
 * Constructor
 * \param name The drawable name
 */
CPolyDrawable::CPolyDrawable(const std::wstring& name) : CDrawable(name)
{
}

/** Draw this poly
* \param graphics The Graphics object we are drawing on */
void CPolyDrawable::Draw(Gdiplus::Graphics* graphics)
{
    SolidBrush brush(mColor);

    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    graphics->FillPolygon(&brush, &points[0], (int)points.size());
}

/** Hit test for polly, determine if hit
* \param pos The position to test if clicked
* \returns a boolean that depends if the poly is clicked
*/
bool CPolyDrawable::HitTest(Gdiplus::Point pos)
{
    // Transform the points
    vector<Point> points;
    for (auto point : mPoints)
    {
        points.push_back(RotatePoint(point, mPlacedR) + mPlacedPosition);
    }

    GraphicsPath path;
    path.AddPolygon(&points[0], (int)points.size());
    return path.IsVisible(pos) ? true : false;
}

/** Add a point to the current polly
* \param point The point we are adding to the vector*/
void CPolyDrawable::AddPoint(Gdiplus::Point point)
{
	mPoints.push_back(point);
}
