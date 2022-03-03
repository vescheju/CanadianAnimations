/**
 * \file Actor.h
 *
 * \author Justin Vesche
 *
 * Class for actors in our drawings.
 */


#pragma once

#include<string>
#include<memory>
#include<vector>
#include "AnimChannelPoint.h"

class CDrawable;
#include "Picture.h"

/**
* Class for actors in our drawings.
*
* An actor is some graphical object that consists of
* one or more parts. Actors can be animated.
*/
class CActor
{
public:
	virtual ~CActor();

    /** Default constructor disabled */
    CActor() = delete;
    /** Copy constructor disabled */
    CActor(const CActor&) = delete;
    /** Assignment operator disabled */
    void operator=(const CActor&) = delete;

    CActor(const std::wstring& name);

    void SetRoot(std::shared_ptr<CDrawable> root);

    void Draw(Gdiplus::Graphics *graphics);

    std::shared_ptr<CDrawable> HitTest(Gdiplus::Point point);

    void AddDrawable(std::shared_ptr<CDrawable> drawable);


    /** Get the actor name
    * \returns Actor name */
    std::wstring GetName() const { return mName; }

    /** Get actor enabled
    * \returns Actor enabled */
    bool IsEnabled() const { return mEnabled; }

    /** Set Actor enabled
    * \param enabled New enabled status */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /** Get actor position
    * \returns Actor position */
    Gdiplus::Point GetPosition() const { return mPosition; }

    /** Set actor position
    * \param point the point mPosition is being changed to */
    void SetPosition(Gdiplus::Point point) { mPosition = point; }

    /** Get if the actor is clickable
    * \returns Actor clickable */
    bool IsClickable() const { return mClickable; }

    /** Set Actor clickable
    * \param clickable New clickable status */
    void SetClickable(bool clickable) { mClickable = clickable; }

    /** Get the actor picture
    * \returns Picture associated with actor */
    CPicture* GetPicture() const { return mPicture; }

    
    void SetPicture(CPicture* picture);


    void SetKeyframe();

    void GetKeyframe();

    /** The point animation channel
     * \returns Pointer to animation channel */
    CAnimChannelPoint* GetPositionChannel() { return &mChannel; }

    void SetTimeline(CTimeline* timeline);

private:
    /// Name of actor
    std::wstring mName;
    /// If actor is enabled check
    bool mEnabled = true;
    /// if the actor is clickable
    bool mClickable = true;
    /// position of the actor
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);

    /// The root drawable
    std::shared_ptr<CDrawable> mRoot;
    /// The drawables in drawing order
    std::vector<std::shared_ptr<CDrawable>> mDrawablesInOrder;
    /// The picture that represents actor
    CPicture *mPicture = nullptr;
    /// The animation channel for animating the angle of this drawable
    CAnimChannelPoint mChannel;
};

