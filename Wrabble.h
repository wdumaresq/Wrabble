// Wrabble.h : main header file for the WRABBLE application
//

#if !defined(AFX_WRABBLE_H__DD93C3E5_6457_11D7_8E77_E06F55C10000__INCLUDED_)
#define AFX_WRABBLE_H__DD93C3E5_6457_11D7_8E77_E06F55C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWrabbleApp:
// See Wrabble.cpp for the implementation of this class
//

class CWrabbleApp : public CWinApp
{
public:
	CWrabbleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrabbleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWrabbleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRABBLE_H__DD93C3E5_6457_11D7_8E77_E06F55C10000__INCLUDED_)
