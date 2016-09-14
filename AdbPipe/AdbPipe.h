/************************************************************
Copyright (C), CMCC, ZYHY. Co., Ltd.
FileName: AdbPipe.h
Author: QingChen  Date:2016-9-13
Description:AdbPipe APP class
Version: 1.0.0
History:
<author>  <time>     <version >    <desc>
QingChen    2016-9-13     1.0.0     build this moudle
***********************************************************/

#if !defined(AFX_ADBPIPE_H__DB18E05E_91F7_4179_9C10_1C92110ADB53__INCLUDED_)
#define AFX_ADBPIPE_H__DB18E05E_91F7_4179_9C10_1C92110ADB53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGuandao01App:
// See Guandao01.cpp for the implementation of this class
//

class CAdbPipeApp : public CWinApp
{
public:
	CAdbPipeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdbPipeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAdbPipeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AdbPipe_H__DB18E05E_91F7_4179_9C10_1C92110ADB53__INCLUDED_)
