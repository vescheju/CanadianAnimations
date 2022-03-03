/**
 * \file Drawable.h
 *
 * \author Justin Vesche
 *
 * Abstract base class for drawable elements of our picture.
 */

#pragma once
#include<string>
#include<vector>
#include<memory>
#include "AnimChannelAngle.h"

class CTimeline;
class CActor;
/**
* Abstract base class for drawable elements of our picture.
*
* A drawable is one part of an actor. Drawable parts can be moved
* independently.
*/
class CDrawable
{
public:
	virtual ~CDrawable();

    /** \brief Default constructor disabled */
    CDrawable() = delete;
    /** \brief Copy constructor disabled */
    CDrawable(const CDrawable&) = delete;
    /** \brief Assignment operator disabled */
    void operator=(const CDrawable&) = delete;

    void SetActor(CActor* actor);
    /** Draw 
    * \param graphics The Graphics object we are drawing on */
    virtual void Draw(Gdiplus::Graphics* graphics) = 0;

    void Place(Gdiplus::Point offset, double rotate);

    void AddChild(std::shared_ptr<CDrawable> child);
    
    /** Hit test determine if hit
    * \param pos The position to test if clicked
    * \returns a boolean that depends if the item is clicked
    */
    virtual bool HitTest(Gdiplus::Point pos) = 0;

    /** Get if is moveable
    * \returns false unless overwritten*/
    virtual bool IsMovable() { return false; }

    void Move(Gdiplus::Point delta);
    

    /** Get the drawable name
    * \returns The drawable name */
    std::wstring GetName() const { return mName; }

    /** Set the drawable position
     * \param pos The new drawable position*/
    void SetPosition(Gdiplus::Point pos) { mPosition = pos; }

    /** Get the drawable position
     * \returns The drawable position*/
    Gdiplus::Point GetPosition() const { return mPosition; }

    /** Set the rotation angle in radians
    * \param r The new rotation angle in radians*/
    void SetRotation(double r) { mRotation = r; }

    /** Get the rotation angle in radians
    * \returns The rotation angle in radians*/
    double GetRotation() const { return mRotation; }

    /** Set the parent of the drawable object
    * \param parent the parent to be set of the drawable*/
    void SetParent(CDrawable* parent) { mParent = parent; }

    /** Get the parent of the drawable object
    * \returns The parent*/
    CDrawable* GetParent() const { return mParent; }

    virtual void SetTimeline(CTimeline* timeline);

    /** The angle animation channel
     * \returns Pointer to animation channel */
    CAnimChannelAngle* GetAngleChannel() { return &mChannel; }

    virtual void SetKeyframe();

    virtual void GetKeyframe();

protected:
    CDrawable(const std::wstring &name);
    
    Gdiplus::Point RotatePoint(Gdiplus::Point point, double angle);



    /// The actual postion in the drawing
    Gdiplus::Point mPlacedPosition = Gdiplus::Point(0, 0);
    /// The actual rotation in the drawing
    double mPlacedR = 0;

private:
    /// The position of this drawable relative to its parent
    Gdiplus::Point mPosition = Gdiplus::Point(0, 0);
    /// The drawable name
    std::wstring mName;
    /// The rotation of this drawable relative to its parent
    double mRotation = 0;

    /// The actor using this drawable
    CActor* mActor = nullptr;
    /// The parent of the current drawable
    CDrawable* mParent = nullptr;
    /// Children stored in a vector
    std::vector<std::shared_ptr<CDrawable>> mChildren;
    /// The animation channel for animating the angle of this drawable
    CAnimChannelAngle mChannel;

};

