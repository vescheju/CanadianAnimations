/**
 * \file AnimChannelPoint.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "AnimChannelPoint.h"
#include <memory>

using namespace std;
using namespace Gdiplus;

CAnimChannelPoint::~CAnimChannelPoint()
{
}

/** Constructor */
CAnimChannelPoint::CAnimChannelPoint() : CAnimChannel()
{
}

/**
 * Set the keyframe at the current frame
 *
 * \param point The point that the current keyframe will hold.
 */
void CAnimChannelPoint::SetKeyframe(Gdiplus::Point point)
{
	// Create a keyframe of the appropriate type
	// Telling it this channel and the point
	shared_ptr<KeyframePoint> keyframe =
		make_shared<KeyframePoint>(this, point);

	// Insert it into the collection
	InsertKeyframe(keyframe);
}

/**
 * Compute an angle that is an interpolation between two keyframes
 *
 * This function is called after Use1 and Use2, so we have pointers to
 * to valid keyframes of the type KeyframeAngle. This function does the
 * tweening.
 * \param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
 * interpolate between.
 */
void CAnimChannelPoint::Tween(double t)
{
	Point a = mKeyframe1->GetPoint();
	Point b = mKeyframe2->GetPoint();

	Point c(int(a.X + t * (b.X - a.X)), int(a.Y + t * (b.Y - a.Y)));
	
	mPoint = c;
}
