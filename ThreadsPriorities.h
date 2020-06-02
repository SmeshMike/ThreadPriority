
// ThreadsPriorities.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <vector>

// CThreadsPrioritiesApp:
// See ThreadsPriorities.cpp for the implementation of this class
//

class CThreadsPrioritiesApp : public CWinApp
{
public:
	CThreadsPrioritiesApp();
	std::vector<unsigned int> ThreadVar;
	std::vector<short> ThreadSleeps;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CThreadsPrioritiesApp theApp;
