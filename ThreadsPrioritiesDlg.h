
// ThreadsPrioritiesDlg.h : header file
//

#pragma once
#include <vector>


// CThreadsPrioritiesDlg dialog
class CThreadsPrioritiesDlg : public CDialogEx
{
// Construction
public:
	CThreadsPrioritiesDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREADSPRIORITIES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRunstop();
	afx_msg void OnBnClickedPriority2();
	afx_msg void OnBnClickedSleep2();
	afx_msg void OnBnClickedSleep1();
	afx_msg void OnBnClickedPriority1();

	// Переменные элементов окна:

	CSpinButtonCtrl cSpin1;
	CSpinButtonCtrl cSpin2;
	CProgressCtrl progress1;
	CProgressCtrl progress2;
	CString power1;
	CString power2;
	int isSlept1;
	int isSlept2;
	int priority1;
	int priority2;


	// Переменные внутренних задач:
	bool isThRuns;
	std::vector<HANDLE> hThreads;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnNMThemeChangedSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMOutofmemorySpin2(NMHDR* pNMHDR, LRESULT* pResult);
};
