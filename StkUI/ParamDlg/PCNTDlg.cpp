// PCNTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCNTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCNTDlg dialog


CPCNTDlg::CPCNTDlg(CWnd* pParent, CPCNT * pPCNT )
{
	CParamDlg::CParamDlg(CPCNTDlg::IDD, pParent);

	//{{AFX_DATA_INIT(CPCNTDlg)
	m_nMADays = 0;
	//}}AFX_DATA_INIT

	m_pPCNT	=	pPCNT;
}


void CPCNTDlg::DoDataExchange(CDataExchange* pDX)
{
	CParamDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPCNTDlg)
	DDX_Control(pDX, IDC_DEADFORK, m_cmbDeadFork);
	DDX_Control(pDX, IDC_GOLDENFORK, m_cmbGoldenFork);
	DDX_Control(pDX, IDC_STATIC_NAME, m_staticName);
	DDX_Text(pDX, IDC_MADAYS, m_nMADays);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPCNTDlg, CParamDlg)
	//{{AFX_MSG_MAP(CPCNTDlg)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_PARAMHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCNTDlg message handlers

BOOL CPCNTDlg::OnInitDialog() 
{
	CParamDlg::OnInitDialog();
	
	ASSERT( m_pPCNT );

	// TODO: Add extra initialization here
	RefreshData( FALSE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPCNTDlg::OnCancel() 
{
}

void CPCNTDlg::OnOK() 
{
	// TODO: Add extra validation here
	if( !RefreshData( TRUE ) )
		m_pPCNT->SetDefaultParameters( );

	CParamDlg::OnOK();
}

void CPCNTDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	m_pPCNT->SetDefaultParameters( );
	RefreshData( FALSE );
}

void CPCNTDlg::OnHelp() 
{
	ParamHelp( STT_PCNT );
}

BOOL CPCNTDlg::RefreshData( BOOL bSaveAndValidate )
{
	if( !m_pPCNT->IsValidParameters() )
		m_pPCNT->SetDefaultParameters();

	if( bSaveAndValidate )
	{
		UpdateData( TRUE );
		
		m_pPCNT->m_nMADays	=	m_nMADays;

		m_pPCNT->m_itsGoldenFork		=	m_cmbGoldenFork.GetSelect();
		m_pPCNT->m_itsDeadFork		=	m_cmbDeadFork.GetSelect();
		return m_pPCNT->IsValidParameters();
	}
	else
	{
		m_staticName.SetWindowText( AfxGetSTTFullName(STT_PCNT) );

		m_nMADays		=	m_pPCNT->m_nMADays;
		
		m_cmbGoldenFork.ResetAndSelect( m_pPCNT->m_itsGoldenFork );
		m_cmbDeadFork.ResetAndSelect( m_pPCNT->m_itsDeadFork );
		UpdateData( FALSE );
	}

	return TRUE;
}

