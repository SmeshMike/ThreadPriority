
// ThreadsPrioritiesDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ThreadsPriorities.h"
#include "ThreadsPrioritiesDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_TIMER 5000
#define NUM_OF_THRS 2
int __stdcall ThreadFunc(int number);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreadsPrioritiesDlg dialog



CThreadsPrioritiesDlg::CThreadsPrioritiesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREADSPRIORITIES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadsPrioritiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, progress1);
	DDX_Control(pDX, IDC_PROGRESS2, progress2);
	DDX_Text(pDX, IDC_POWER1, power1);
	DDX_Text(pDX, IDC_POWER2, power2);
	DDX_Text(pDX, IDC_EDIT1, priority1);
	DDX_Text(pDX, IDC_EDIT2, priority2);
	DDX_Check(pDX, IDC_SLEEP1, isSlept1);
	DDX_Check(pDX, IDC_SLEEP2, isSlept2);
	DDX_Control(pDX, IDC_SPIN1, cSpin1);
	DDX_Control(pDX, IDC_SPIN2, cSpin2);

}

BEGIN_MESSAGE_MAP(CThreadsPrioritiesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUNSTOP, &CThreadsPrioritiesDlg::OnBnClickedRunstop)
	ON_BN_CLICKED(IDC_SLEEP2, &CThreadsPrioritiesDlg::OnBnClickedSleep2)
	ON_BN_CLICKED(IDC_SLEEP1, &CThreadsPrioritiesDlg::OnBnClickedSleep1)
	ON_WM_TIMER()
//	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CThreadsPrioritiesDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CThreadsPrioritiesDlg::OnDeltaposSpin2)
//	ON_NOTIFY(NM_THEMECHANGED, IDC_SPIN1, &CThreadsPrioritiesDlg::OnNMThemeChangedSpin1)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CThreadsPrioritiesDlg::OnDeltaposSpin1)
ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPIN2, &CThreadsPrioritiesDlg::OnNMOutofmemorySpin2)
END_MESSAGE_MAP()


// CThreadsPrioritiesDlg message handlers

BOOL CThreadsPrioritiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here
	HANDLE there = GetCurrentProcess();
	SetProcessAffinityMask(there, 0x1);

	progress1.SetRange(0, 100);
	progress1.SetPos(0);
	progress2.SetRange(0, 100);
	progress2.SetPos(0);
	cSpin1.SetRange(0, 4);	    // диапазон
	cSpin1.SetPos(0);
	priority1 = cSpin1.GetPos();
	//cSpin1.SetBuddy(priority1);
	cSpin2.SetRange(0, 4);		    // диапазон
	cSpin2.SetPos(0);
	priority2 = cSpin2.GetPos();
	SetTimer(IDC_TIMER, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThreadsPrioritiesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CThreadsPrioritiesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CThreadsPrioritiesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadsPrioritiesDlg::OnBnClickedRunstop()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (isThRuns)
	{
		isThRuns = false;

		for (int i = 0; i < NUM_OF_THRS; i++)
		{
			// Остановка вторичных потоков:
			TerminateThread(hThreads[i], 0);

			WaitForSingleObject(hThreads[i], INFINITE);
			CloseHandle(hThreads[i]);
			hThreads[i] = 0;
		}

		theApp.ThreadVar.clear();
		theApp.ThreadSleeps.clear();
		hThreads.clear();
	}
	else
	{
		for (int i = 0; i < NUM_OF_THRS; i++)
		{
			// Установка начальных значений:
			theApp.ThreadVar.push_back(0);
			switch (i)
			{
			case 0: theApp.ThreadSleeps.push_back(isSlept1 == 1); break;
			case 1: theApp.ThreadSleeps.push_back(isSlept2 == 1); break;
			default: theApp.ThreadSleeps.push_back(false); break;
			}

			// Создание вторичных потоков:
			DWORD dwThrIDs;
			HANDLE hThread = CreateThread(
				NULL, 0,
				(LPTHREAD_START_ROUTINE)ThreadFunc,
				(LPVOID)i,
				CREATE_SUSPENDED,
				&dwThrIDs
			);
			hThreads.push_back(hThread);
		}

		// Запуск вторичных потоков:
		for (int i = 0; i < NUM_OF_THRS; i++) { ResumeThread(hThreads[i]); }
		isThRuns = true;
	}
	UpdateData(false);
}

void CThreadsPrioritiesDlg::OnBnClickedSleep1()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (isThRuns)
	{
		// Приоритет первого процесса:
		//DWORD ThPr = THREAD_PRIORITY_NORMAL;
		//switch (mSlider_T1.GetPos())
		//{
		//case 0: ThPr = THREAD_PRIORITY_HIGHEST;			break;
		//case 1: ThPr = THREAD_PRIORITY_ABOVE_NORMAL;	break;
		//case 3: ThPr = THREAD_PRIORITY_BELOW_NORMAL;	break;
		//case 4: ThPr = THREAD_PRIORITY_LOWEST;			break;
		//}
		//SetThreadPriority(hThreads[0], ThPr);

		//// Приоритет второго процесса:
		//ThPr = THREAD_PRIORITY_NORMAL;
		//switch (mSlider_T2.GetPos())
		//{
		//case 0: ThPr = THREAD_PRIORITY_HIGHEST;			break;
		//case 1: ThPr = THREAD_PRIORITY_ABOVE_NORMAL;	break;
		//case 3: ThPr = THREAD_PRIORITY_BELOW_NORMAL;	break;
		//case 4: ThPr = THREAD_PRIORITY_LOWEST;			break;
		//}
		//SetThreadPriority(hThreads[1], ThPr);
	}
	UpdateData(false);
}

void CThreadsPrioritiesDlg::OnBnClickedSleep2()
{
	// TODO: Add your control notification handler code here
}


void CThreadsPrioritiesDlg::OnBnClickedPriority1()
{
	// TODO: Add your control notification handler code here
}

void CThreadsPrioritiesDlg::OnBnClickedPriority2()
{
	// TODO: Add your control notification handler code here
}


void CThreadsPrioritiesDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(true);
	if (isThRuns)
	{
		// Обмен информацией с вторичными потоками:
		double ThreadResult1 = (double)InterlockedExchange(&(theApp.ThreadVar[0]), 0);
		double ThreadResult2 = (double)InterlockedExchange(&(theApp.ThreadVar[1]), 0);

		// Вывод информации о производительности в окно:
		ThreadResult1 = 100.0 * ThreadResult1 / (ThreadResult1 + ThreadResult2);
		ThreadResult2 = 100.0 - ThreadResult1;

		power1.Format(_T("%2.2f"), ThreadResult1);
		power2.Format(_T("%2.2f"), ThreadResult2);
		power1 += '%';
		power2 += '%';

		progress1.SetPos((int)trunc(ThreadResult1));
		progress2.SetPos((int)trunc(ThreadResult2));
	}
	UpdateData(false);

	CDialogEx::OnTimer(nIDEvent);
}


//void CThreadsPrioritiesDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	UpdateData(true);
//	priority1 = cSpin1.GetPos();
//	UpdateData(false);
//	*pResult = 1;
//}


void CThreadsPrioritiesDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	priority2 = cSpin2.GetPos() - 65536;
	if (isThRuns)
	{

		//// Приоритет второго процесса:
		DWORD ThPr = THREAD_PRIORITY_NORMAL;
		switch (cSpin2.GetPos())
		{
		case 0: ThPr = THREAD_PRIORITY_HIGHEST;			break;
		case 1: ThPr = THREAD_PRIORITY_ABOVE_NORMAL;	break;
		case 3: ThPr = THREAD_PRIORITY_BELOW_NORMAL;	break;
		case 4: ThPr = THREAD_PRIORITY_LOWEST;			break;
		}
		SetThreadPriority(hThreads[1], ThPr);
	}
	UpdateData(false);
	*pResult = 0;
}


void CThreadsPrioritiesDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	priority1 = cSpin1.GetPos() - 65536;
	if (isThRuns)
	{
		 //Приоритет первого процесса:
		DWORD ThPr = THREAD_PRIORITY_NORMAL;
		switch (priority1)
		{
		case 0: ThPr = THREAD_PRIORITY_HIGHEST;			break;
		case 1: ThPr = THREAD_PRIORITY_ABOVE_NORMAL;	break;
		case 3: ThPr = THREAD_PRIORITY_BELOW_NORMAL;	break;
		case 4: ThPr = THREAD_PRIORITY_LOWEST;			break;
		}
		SetThreadPriority(hThreads[0], ThPr);
	}
	UpdateData(false);
	*pResult = 0;
}


void CThreadsPrioritiesDlg::OnNMOutofmemorySpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	priority1 = cSpin2.GetPos();
	UpdateData(FALSE);

	*pResult = 0;
}
