/**
 * \file Timeline.cpp
 *
 * \author Justin Vesche
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
* Constructor
*/
CTimeline::CTimeline()
{
}

/** 
* Adding the channel to timeline
* \param channel the the channel to be added
*/
void CTimeline::AddChannel(CAnimChannel* channel)
{
	mChannels.push_back(channel);
	channel->SetTimeline(this);
}


/** 
*
* removing the channel from the timeline
*
*/
void CTimeline::RemoveChannel()
{
    for (auto curChannel : mChannels)
    {
        curChannel->RemoveKeyFrame(GetCurrentFrame());
    }

}

/** Sets the current time
*
* Ensures all of the channels are
* valid for that point in time.
* 
* \param t Time
*/
void CTimeline::SetCurrentTime(double t)
{
    // Set the time
    mCurrentTime = t;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}