/**
 * \file TimelineDlg.h
 *
 * \author Justin Vesche
 *
 * This class implements a timeline dialog
 */

#pragma once
class CTimeline;

/** Timeline dialog implementation */
class CTimelineDlg : public CDialog
{
	/** Timeline dialog implementation
	*
	*/
	DECLARE_DYNAMIC(CTimelineDlg)

public:
	CTimelineDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTimelineDlg();

	void SetTimeline(CTimeline* timeline);

	void Take();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMELINEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	/// obtained from dialog box num frames
	int mNumFrames;

	/// The timeline we are editing
	CTimeline* mTimeline = nullptr;

	/// obtained from dialog box frame rate
	int mFrameRate;
};
