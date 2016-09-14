/************************************************************
Copyright (C), CMCC, ZYHY. Co., Ltd.
FileName: AdbPipeDlg.cpp
Author: QingChen  Date:2016-9-13
Description:AdbPipe Dialog class
Version: 1.0.0
History:
<author>  <time>     <version >    <desc>
QingChen    2016-9-13     1.0.0     build this moudle
***********************************************************/


// AdbPipeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdbPipe.h"
#include "AdbPipeDlg.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdbPipeDlg dialog
CAdbPipeDlg *g_dlg=NULL;
CAdbPipeDlg::CAdbPipeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdbPipeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdbPipeDlg)
	m_PING = _T("");
	m_RECEIVE = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdbPipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdbPipeDlg)
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_ctrlRECEIVE);
	DDX_Control(pDX, IDC_EDIT_PING, m_ctrlPING);
	DDX_Text(pDX, IDC_EDIT_PING, m_PING);
	DDX_Text(pDX, IDC_EDIT_RECEIVE, m_RECEIVE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdbPipeDlg, CDialog)
	//{{AFX_MSG_MAP(CAdbPipeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdbPipeDlg message handlers

BOOL CAdbPipeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	g_dlg=this;
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdbPipeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAdbPipeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAdbPipeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

unsigned __stdcall CmdThread(void *pParam)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	CString strCmd;
	g_dlg->m_ctrlPING.GetWindowText(strCmd);//从控件获得cmd命令串
	strCmd="cmd /k"+strCmd;//加上"cmd /k"是为了能执行类似dir的命令

	if(strCmd.IsEmpty())
	{
		return TRUE;
	}
	//创建命名管道
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) {
		//MessageBox("Error On CreatePipe()");
		return FALSE;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;//数据输出用的文件句柄
	si.hStdOutput = hWrite;//数据输出用的文件句柄
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	OutputDebugString("1");

	if (!CreateProcess(NULL,strCmd.GetBuffer(strCmd.GetLength())//执行cmd命令,并在命名中管道中写入cmd命令返回的串
		,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi)) {
		//MessageBox("Error on CreateProcess()");
		return FALSE;
	}
	/*if(WaitForSingleObject(pi.hProcess, INFINITE)==WAIT_FAILED)//这里决定是否要等整个命令执行完,如ping等耗时较多的命令.
	{
		//MessageBox("Failed!");
		return FALSE;
	}*/
	CloseHandle(hWrite);
	OutputDebugString("2");
	
	char buffer[4096] ={0} ;
	DWORD bytesRead;
	CString strResult="";
	
	while(1)
	{
		memset(buffer,0,4096);
		if(ReadFile(hRead,buffer,4096,&bytesRead,NULL) != NULL)//从命名管道中读取数据
		{
			strResult += buffer;
			g_dlg->m_ctrlRECEIVE.SetWindowText(strResult);//显示到界面上去
			OutputDebugString(buffer);
			
		}
		else
		{
			break;
		}
	}
	CloseHandle(hRead);
	return TRUE;
}

void CAdbPipeDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	_beginthreadex(NULL,0,CmdThread,NULL,0,NULL);
}
