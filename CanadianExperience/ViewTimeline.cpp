/**
 * \file ViewTimeline.cpp
 *
 * \author Justin Vesche
 */


#include "pch.h"
#include <cassert>
#include <sstream>
#include "CanadianExperience.h"
#include "ViewTimeline.h"
#include "DoubleBufferDC.h"
#include "Timeline.h"
#include "Picture.h"
#include "MainFrm.h"
#include "Actor.h"


/// The window height in pixels
const int WindowHeight = 60;

/// The spacing from the top of the 
/// window to the top of the tick marks in pixels
const int BorderTop = 20;

/// Space to the left of the scale in pixels
const int BorderLeft = 10;

/// Space to the right of the scale in pixels
const int BorderRight = 10;

/// The spacing between ticks on the timeline in pixels
const int TickSpacing = 3;

/// The length of a short tick mark in pixels
const int TickShort = 10;

/// The length of a long tick mark in pixels
const int TickLong = 20;

using namespace std;
using namespace Gdiplus;


IMPLEMENT_DYNCREATE(CViewTimeline, CScrollView)

/**
 * Force an update of this window when the picture changes.
 */
void CViewTimeline::UpdateObserver()
{
    Invalidate();
    UpdateWindow();
}

/** Constructor */
CViewTimeline::CViewTimeline()
{
    mPointer = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/pointer-down.png"));
    assert(mPointer->GetLastStatus() == Ok);
}

/** Destructor */
CViewTimeline::~CViewTimeline()
{
}




/** Handle the initial update for this window */
void CViewTimeline::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

    int sbHeight = GetSystemMetrics(SM_CXHSCROLL);
    CSize sizeTotal(200, Height - sbHeight - 20);
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/** Draw this window 
 * \param pDC Device context */
void CViewTimeline::OnDraw(CDC* pDC)
{

    // Get the timeline
    CTimeline* timeline = GetPicture()->GetTimeline();

    // Set the scroll system correctly
    CSize sizeTotal(timeline->GetNumFrames() * TickSpacing + BorderLeft + BorderRight, WindowHeight);
    SetScrollSizes(MM_TEXT, sizeTotal);

    CDoubleBufferDC dbDC(pDC);

    Graphics graphics(dbDC.m_hDC);    // Create GDI+ graphics context

    CRect rect;
    GetClientRect(&rect);
    int hit = rect.Height();
    int wid = rect.Width();
    Pen tickpen(Color(0, 0, 0), 1);
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 10);
    SolidBrush brush(Color(0, 0, 0));



    int currentTick = timeline->GetCurrentFrame() * TickSpacing + BorderLeft - 2;
    graphics.DrawImage(mPointer.get(),
        currentTick, BorderTop,
        mPointer->GetWidth(), mPointer->GetHeight());


    for (int tickNum = 0; tickNum <= timeline->GetNumFrames(); ++tickNum)
    {
        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;
        int drawAt = ((tickNum + 1) * TickSpacing) + BorderLeft;
        if (onSecond)
        {
           
            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << tickNum / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            RectF size;
            PointF origin(0.0f, 0.0f);
            graphics.MeasureString(wstr.c_str(), wstr.size(),
                &font, origin, &size);

            graphics.DrawLine(&tickpen, drawAt, BorderTop, drawAt, BorderTop + TickLong);
           
            graphics.DrawString(wstr.c_str(), -1, &font, PointF(drawAt - (float)(size.Width) / 2, float(BorderTop + TickLong)), &brush);
        }
        else
        {
            graphics.DrawLine(&tickpen, drawAt, BorderTop, drawAt, BorderTop + TickShort);
        }

    }
    
}


/** Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context 
 * \return FALSE */
BOOL CViewTimeline::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

/** Handle the Edit>Set Keyframe menu option */
 void CViewTimeline::OnEditSetkeyframe()
 {
     for (auto actor : *GetPicture())
     {
         actor->SetKeyframe();
     }
 }


 /** Handle the Edit>Delete Keyframe menu option */
 void CViewTimeline::OnEditDeletekeyframe()
 {
     auto timeline = GetPicture()->GetTimeline();
     timeline->RemoveChannel();
     
 }


 // Doxygen sometimes gets confused by these message 
 // maps, since they look like functions. I've found
 // it helps to move them to the end of the file.
 BEGIN_MESSAGE_MAP(CViewTimeline, CScrollView)
	 ON_WM_CREATE()
	 ON_WM_ERASEBKGND()
	 ON_COMMAND(ID_EDIT_SETKEYFRAME, &CViewTimeline::OnEditSetkeyframe)
	 ON_COMMAND(ID_EDIT_DELETEKEYFRAME, &CViewTimeline::OnEditDeletekeyframe)
//     ON_WM_MBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
 END_MESSAGE_MAP()



// void CViewTimeline::OnMButtonDown(UINT nFlags, CPoint point)
// {
//
//     __super::OnMButtonDown(nFlags, point);
// }


/** Handle a left button mouse press event
* \param nFlags flags associated with the mouse press
* \param point The location of the mouse press
*/
 void CViewTimeline::OnLButtonDown(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);

     int x = point.x;

     // Get the timeline
     CTimeline* timeline = GetPicture()->GetTimeline();
     int pointerX = (int)(timeline->GetCurrentTime() *
         timeline->GetFrameRate() * TickSpacing + BorderLeft);

     mMovingPointer = x >= pointerX - (int)mPointer->GetWidth() / 2 &&
         x <= pointerX + (int)mPointer->GetWidth() / 2;


     __super::OnLButtonDown(nFlags, point);
 }

 /** Handle a mouse movement
* \param nFlags flags associated with the mouse press
* \param point The location of the mouse press
*/
 void CViewTimeline::OnMouseMove(UINT nFlags, CPoint point)
 {
     // Convert mouse coordinates to logical coordinates
     CClientDC dc(this);
     OnPrepareDC(&dc);
     dc.DPtoLP(&point);
     
     // Get the timeline
     CTimeline* timeline = GetPicture()->GetTimeline();

     int x = point.x;
     if (mMovingPointer && nFlags && MK_LBUTTON)
     { 
        if (x < BorderLeft)
        {
             GetPicture()->SetAnimationTime(0.0);
        }
        else if (x < BorderLeft + timeline->GetNumFrames() * TickSpacing)
        {
            double timer = double((x - BorderLeft)) /
            ((timeline->GetFrameRate()) * TickSpacing);

            GetPicture()->SetAnimationTime(timer);
        }
        else
        {
            GetPicture()->SetAnimationTime(timeline->GetDuration());
        }
     }

     __super::OnMouseMove(nFlags, point);
 }
