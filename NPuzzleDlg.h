
// NPuzzleDlg.h: 头文件
//

#pragma once


// CNPuzzleDlg 对话框
class CNPuzzleDlg : public CDialogEx
{
	// 构造
public:
	CNPuzzleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NPUZZLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRect Rect[17];
	int nNumInPos[17]{ 0,
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10,11,12,
		13,14,15,0 };
	int nPosOfNum[16]{ 16,
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10,11,12,
		13,14,15 };
	CImage Image;
	UINT nSec = 0, nMin = 0;

	CStatic m_Blk[16];
	CButton m_Btn;

	void Reset(bool bTime = TRUE, bool bRand = TRUE, bool bImage = FALSE);
	void MoveBlk(int);
	void CheckCpl();
	void LoadImg();

	afx_msg void
		OnStnClickedBlk1(), OnStnClickedBlk2(), OnStnClickedBlk3(), OnStnClickedBlk4(),
		OnStnClickedBlk5(), OnStnClickedBlk6(), OnStnClickedBlk7(), OnStnClickedBlk8(),
		OnStnClickedBlk9(), OnStnClickedBlk10(), OnStnClickedBlk11(), OnStnClickedBlk12(),
		OnStnClickedBlk13(), OnStnClickedBlk14(), OnStnClickedBlk15();
	afx_msg void OnBnClickedButton1();
	virtual void OnOK();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnOpen();
	afx_msg void OnResetbrd();
	afx_msg void OnResetimg();
	afx_msg void OnAboutbox();
};
