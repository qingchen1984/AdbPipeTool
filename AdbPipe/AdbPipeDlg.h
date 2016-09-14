/************************************************************
Copyright (C), CMCC, ZYHY. Co., Ltd.
FileName: AdbPipeDlg.cpp
Author: QingChen  Date:2016-9-13
Description:AdbPipe Dialog class definition
Version: 1.0.0
History:
<author>  <time>     <version >    <desc>
QingChen    2016-9-13     1.0.0     build this moudle
***********************************************************/


// AdbPipeDlg.h : header file
//

#if !defined(AFX_AdbPipeDLG_H__264E7AF0_5CBF_4AC3_AD45_5BE0F1D57269__INCLUDED_)
#define AFX_AdbPipeDLG_H__264E7AF0_5CBF_4AC3_AD45_5BE0F1D57269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAdbPipeDlg dialog

class CAdbPipeDlg : public CDialog
{
// Construction
public:
	CAdbPipeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdbPipeDlg)
	enum { IDD = IDD_ADBPIPE_DIALOG };
	CEdit	m_ctrlRECEIVE;
	CEdit	m_ctrlPING;
	CString	m_PING;
	CString	m_RECEIVE;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdbPipeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAdbPipeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AdbPipeDLG_H__264E7AF0_5CBF_4AC3_AD45_5BE0F1D57269__INCLUDED_)
