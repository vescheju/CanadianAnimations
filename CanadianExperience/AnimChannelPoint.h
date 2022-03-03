/**
 * \file AnimChannelPoint.h
 *
 * \author Justin Vesche
 *
 * Animation channel for points
 */

#pragma once
#include "AnimChannel.h"

/**
* Animation channel for points.
*/
class CAnimChannelPoint : public CAnimChannel
{
public:
    virtual ~CAnimChannelPoint();
    /** \brief Copy constructor disabled */
    CAnimChannelPoint(const CAnimChannelPoint&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CAnimChannelPoint&) = delete;

    CAnimChannelPoint();

    /** Get the point
    * \returns the point */
    Gdiplus::Point GetPoint() const { return mPoint; }

    void SetKeyframe(Gdiplus::Point point);

    /** Class that represents a keyframe */
    class KeyframePoint : public Keyframe
    {
    public:
        /** Get the point
        * \returns the point */
        Gdiplus::Point GetPoint() const { return mPoint; }

        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

        /** Use this keyframe as keyfraem 2 */
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

        /** Use this keyframe as the point */
        virtual void UseOnly() override { mChannel->mPoint = mPoint; }

        /** Constructor
        * \param channel The channel we are for
        * \param point The point for the keyframe */
        KeyframePoint(CAnimChannelPoint* channel, Gdiplus::Point point) :
            Keyframe(channel), mChannel(channel), mPoint(point) {}

        /** \brief Default constructor disabled */
        KeyframePoint() = delete;
        /** \brief Copy constructor disabled */
        KeyframePoint(const KeyframePoint&) = delete;
        /** \brief Assignment operator disabled */
        void operator=(const KeyframePoint&) = delete;

    private:
        /// The point
        Gdiplus::Point mPoint;
        /// The channel this keyframe is associated with
        CAnimChannelPoint* mChannel;
    };
protected:
    virtual void Tween(double t) override;

private:
    /// the point
    Gdiplus::Point mPoint;

    /// The first angle keyframe
    KeyframePoint* mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframePoint* mKeyframe2 = nullptr;

};

