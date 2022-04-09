
// NPuzzleDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NPuzzle.h"
#include "NPuzzleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CNPuzzleDlg 对话框



CNPuzzleDlg::CNPuzzleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NPUZZLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 1; i < 16; ++i)
		DDX_Control(pDX, IDC_BLK + i, m_Blk[i]);
	DDX_Control(pDX, IDC_BUTTON1, m_Btn);
}

BEGIN_MESSAGE_MAP(CNPuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_BLK1, &CNPuzzleDlg::OnStnClickedBlk1)
	ON_STN_CLICKED(IDC_BLK2, &CNPuzzleDlg::OnStnClickedBlk2)
	ON_STN_CLICKED(IDC_BLK3, &CNPuzzleDlg::OnStnClickedBlk3)
	ON_STN_CLICKED(IDC_BLK4, &CNPuzzleDlg::OnStnClickedBlk4)
	ON_STN_CLICKED(IDC_BLK5, &CNPuzzleDlg::OnStnClickedBlk5)
	ON_STN_CLICKED(IDC_BLK6, &CNPuzzleDlg::OnStnClickedBlk6)
	ON_STN_CLICKED(IDC_BLK7, &CNPuzzleDlg::OnStnClickedBlk7)
	ON_STN_CLICKED(IDC_BLK8, &CNPuzzleDlg::OnStnClickedBlk8)
	ON_STN_CLICKED(IDC_BLK9, &CNPuzzleDlg::OnStnClickedBlk9)
	ON_STN_CLICKED(IDC_BLK10, &CNPuzzleDlg::OnStnClickedBlk10)
	ON_STN_CLICKED(IDC_BLK11, &CNPuzzleDlg::OnStnClickedBlk11)
	ON_STN_CLICKED(IDC_BLK12, &CNPuzzleDlg::OnStnClickedBlk12)
	ON_STN_CLICKED(IDC_BLK13, &CNPuzzleDlg::OnStnClickedBlk13)
	ON_STN_CLICKED(IDC_BLK14, &CNPuzzleDlg::OnStnClickedBlk14)
	ON_STN_CLICKED(IDC_BLK15, &CNPuzzleDlg::OnStnClickedBlk15)
	ON_BN_CLICKED(IDC_BUTTON1, &CNPuzzleDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_COMMAND(IDM_OPEN, &CNPuzzleDlg::OnOpen)
	ON_COMMAND(IDM_ABOUTBOX, &CNPuzzleDlg::OnAboutbox)
	ON_COMMAND(IDM_RESETBRD, &CNPuzzleDlg::OnResetbrd)
	ON_COMMAND(IDM_RESETIMG, &CNPuzzleDlg::OnResetimg)
END_MESSAGE_MAP()


// CNPuzzleDlg 消息处理程序

BOOL CNPuzzleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	srand(time(NULL));

	for (int i = 1; i < 16; ++i)
	{
		m_Blk[i].GetWindowRect(&Rect[i]);
		ScreenToClient(&Rect[i]);
	}
	Rect[16] = { Rect[15].right, Rect[12].bottom,
		Rect[15].right + Rect[1].Width(),
		Rect[12].bottom + Rect[1].Height() };

	Reset(FALSE, FALSE, TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNPuzzleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNPuzzleDlg::OnStnClickedBlk1() { MoveBlk(1); }
void CNPuzzleDlg::OnStnClickedBlk2() { MoveBlk(2); }
void CNPuzzleDlg::OnStnClickedBlk3() { MoveBlk(3); }
void CNPuzzleDlg::OnStnClickedBlk4() { MoveBlk(4); }
void CNPuzzleDlg::OnStnClickedBlk5() { MoveBlk(5); }
void CNPuzzleDlg::OnStnClickedBlk6() { MoveBlk(6); }
void CNPuzzleDlg::OnStnClickedBlk7() { MoveBlk(7); }
void CNPuzzleDlg::OnStnClickedBlk8() { MoveBlk(8); }
void CNPuzzleDlg::OnStnClickedBlk9() { MoveBlk(9); }
void CNPuzzleDlg::OnStnClickedBlk10() { MoveBlk(10); }
void CNPuzzleDlg::OnStnClickedBlk11() { MoveBlk(11); }
void CNPuzzleDlg::OnStnClickedBlk12() { MoveBlk(12); }
void CNPuzzleDlg::OnStnClickedBlk13() { MoveBlk(13); }
void CNPuzzleDlg::OnStnClickedBlk14() { MoveBlk(14); }
void CNPuzzleDlg::OnStnClickedBlk15() { MoveBlk(15); }

void CNPuzzleDlg::MoveBlk(int nNumClk)
{
	int nPosClk = nPosOfNum[nNumClk],
		nPosLine = (nPosClk - 1) / 4 * 4 + 1, nPosCol = (nPosClk - 1) % 4 + 1;
	if (nPosOfNum[0] >= nPosLine && nPosOfNum[0] <= nPosLine + 3) // 空位同行
	{
		if (nPosOfNum[0] < nPosClk) // 空位在左边
		{
			for (int iPos = nPosOfNum[0] + 1; iPos <= nPosClk; ++iPos)
			{
				int nNumMov = nNumInPos[iPos];

				m_Blk[nNumMov].MoveWindow(&Rect[iPos - 1]);
				nPosOfNum[nNumMov] = iPos - 1;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos - 1] = nNumMov;
				nNumInPos[iPos] = 0;
			}
		}
		else // 空位在右边
		{
			for (int iPos = nPosOfNum[0] - 1; iPos >= nPosClk; --iPos)
			{
				int nNumMov = nNumInPos[iPos];
				m_Blk[nNumMov].MoveWindow(&Rect[iPos + 1]);
				nPosOfNum[nNumMov] = iPos + 1;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos + 1] = nNumMov;
				nNumInPos[iPos] = 0;
			}
		}
	}
	else if ((nPosOfNum[0] - 1) % 4 + 1 == nPosCol) // 空位同列
	{
		if (nPosOfNum[0] < nPosClk) // 空位在上方
		{
			for (int iPos = nPosOfNum[0] + 4; iPos <= nPosClk; iPos += 4)
			{
				int nNumMov = nNumInPos[iPos];
				m_Blk[nNumMov].MoveWindow(&Rect[iPos - 4]);
				nPosOfNum[nNumMov] = iPos - 4;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos - 4] = nNumMov;
				nNumInPos[iPos] = 0;
			}
		}
		else // 空位在下方
		{
			for (int iPos = nPosOfNum[0] - 4; iPos >= nPosClk; iPos -= 4)
			{
				int nNumMov = nNumInPos[iPos];
				m_Blk[nNumMov].MoveWindow(&Rect[iPos + 4]);
				nPosOfNum[nNumMov] = iPos + 4;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos + 4] = nNumMov;
				nNumInPos[iPos] = 0;
			}
		}
	}
	CheckCpl();
}

void CNPuzzleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Reset();
	SetDlgItemText(IDC_BUTTON1, L"もう一回");
}

void CNPuzzleDlg::OnResetbrd()
{
	// TODO: 在此添加命令处理程序代码
	Reset(FALSE, FALSE);
	SetDlgItemText(IDC_BUTTON1, L"ミッションスタートだ！");
}

void CNPuzzleDlg::OnResetimg()
{
	// TODO: 在此添加命令处理程序代码
	Reset(FALSE, FALSE, TRUE);
	SetDlgItemText(IDC_BUTTON1, L"ミッションスタートだ！");
}

void CNPuzzleDlg::Reset(bool bTime, bool bRand, bool bImage)
{
	KillTimer(1);
	nSec = 0;
	SetDlgItemText(IDC_TIME, L"00 : 00");

	if (bRand)
	{
		int nNumRd, nDif = 0;
		do {
			bool bNum[16]{ 0 };
			nDif = 0;
			for (int i = 1; i <= 16; ++i)
			{
				if (i == 16)
				{
					for (int j = 0; j < 16; ++j)
						if (!bNum[j]) { nNumRd = j; break; }
				}
				else while (bNum[nNumRd = rand() % 16]);
				bNum[nNumRd] = 1;
				if (nNumRd)
				{
					m_Blk[nNumRd].MoveWindow(&Rect[i], FALSE);
				}
				nNumInPos[i] = nNumRd;
				nPosOfNum[nNumRd] = i;
			}
			for (int i = 2; i <= 16; ++i)
			{
				for (int j = 1; j < i; ++j)
					if (nNumInPos[j] > nNumInPos[i]) ++nDif;
			}
			nDif += (nPosOfNum[0] - 1) % 4 + (nPosOfNum[0] - 1) / 4;
		} while (nDif % 2 == 0);
	}
	else
	{
		nPosOfNum[0] = 16;
		for (int i = 1; i < 16; ++i)
		{
			m_Blk[i].MoveWindow(&Rect[i], FALSE);
			nNumInPos[i] = i;
			nPosOfNum[i] = i;
		}
		nNumInPos[16] = 0;
	}
	if (bImage)
	{
		int nBlkW = Rect[1].Width(), nBlkH = Rect[1].Height();
		RECT RectImg = { 0, 0, nBlkW, nBlkH };

		CImage ImgBlkBg;
		ImgBlkBg.Create(nBlkW, nBlkH, 24);
		for (int j = 0; j < nBlkH; ++j)
			for (int k = 0; k < nBlkW; ++k)
				ImgBlkBg.SetPixelRGB(k, j, 255, 255, 255);
		for (int i = 1; i < 16; ++i)
		{
			CImage ImgBlk;
			ImgBlk.Create(nBlkW, nBlkH, 24);

			HDC hDC = ImgBlk.GetDC();
			ImgBlkBg.BitBlt(hDC, 0, 0, nBlkW, nBlkH, 0, 0);

			int nWidth = nBlkW / 2 - 16, nHeight = 2.3 * nWidth;
			CFont Font;
			Font.CreateFont(nHeight, nWidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"等线");
			SelectObject(hDC, Font);

			CString wszNum;
			_itow_s(i, wszNum.GetBuffer(4), 4, 10);
			wszNum.ReleaseBuffer();

			DrawText(hDC, wszNum, wszNum.GetLength(), &RectImg, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ImgBlk.BitBlt(hDC, 0, 0, nBlkW, nBlkH, 0, 0);

			ImgBlk.ReleaseDC();
			m_Blk[i].SetBitmap(ImgBlk.Detach());
		}
	}
	if (bTime) SetTimer(1, 1000, NULL);
	Invalidate();
}

void CNPuzzleDlg::CheckCpl()
{
	for (int i = 1; i < 16; ++i)
	{
		if (nPosOfNum[i] != i) return;
	}
	KillTimer(1);
}

void CNPuzzleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	++nSec;
	if (nSec >= 60) { ++nMin; nSec %= 60; }
	CString wszTime, wszSec, wszMin;
	_itow_s(nSec, wszSec.GetBuffer(4), 4, 10);
	_itow_s(nMin, wszMin.GetBuffer(4), 4, 10);
	wszSec.ReleaseBuffer();
	wszMin.ReleaseBuffer();
	if (nSec < 10) wszSec.Insert(0, L"0");
	if (nMin < 10) wszMin.Insert(0, L"0");
	wszTime = wszMin + L" : " + wszSec;
	SetDlgItemText(IDC_TIME, wszTime);
	CDialogEx::OnTimer(nIDEvent);
}

void CNPuzzleDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButton1();
}

void CNPuzzleDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		L"Image Files (*.bmp;*.jpg;*.jpeg;*.png)|*.jpg; *.jpeg; *.png||");
	dlgFile.m_ofn.lpstrTitle = L"画像ファイルを選択";
	if (dlgFile.DoModal() == IDOK)
	{
		CString wszFile = dlgFile.GetPathName();
		if (FAILED(Image.Load(wszFile))) MessageBox(L"画像ファイルのロードに失敗しました", L"エラー");
		LoadImg();
	}
	::SetForegroundWindow(GetDesktopWindow()->m_hWnd);
	SetForegroundWindow();
}

void CNPuzzleDlg::LoadImg()
{
	CRect RectBrd(0, 0, Rect[16].right, Rect[16].bottom);

	int nBlkW = Rect[1].Width(), nBlkH = Rect[1].Height(),
		nBrdW = RectBrd.Width(), nBrdH = RectBrd.Height();
	if (Image.GetWidth() != nBrdW || Image.GetHeight() != nBrdH)
	{
		// 等比缩放到 imgTemp
		int nSrcW = Image.GetWidth(), nSrcH = Image.GetHeight();
		double fScale = max((double)nBrdW / nSrcW, (double)nBrdH / nSrcH);
		int nDestW = nSrcW * fScale, nDestH = nSrcH * fScale;
		CImage imgTemp;
		imgTemp.Create(nDestW, nDestH, 24);
		HDC hDCNew = imgTemp.GetDC();
		SetStretchBltMode(hDCNew, HALFTONE);
		Image.StretchBlt(hDCNew, 0, 0, nDestW, nDestH);
		imgTemp.ReleaseDC();
		Image.Destroy();
		// 裁剪中心部分到 Image
		Image.Create(nBrdW, nBrdH, 24);
		imgTemp.BitBlt(Image.GetDC(), 0, 0, nBrdW, nBrdH, (nDestW - nBrdW) / 2, (nDestH - nBrdH) / 2);
		Image.ReleaseDC();
	}
	for (int i = 1; i < 16; ++i)
	{
		CImage imgBlk;
		imgBlk.Create(nBlkW, nBlkH, 24);
		Image.BitBlt(imgBlk.GetDC(), 0, 0, nBlkW, nBlkH, Rect[i].left, Rect[i].top);
		imgBlk.ReleaseDC();
		m_Blk[i].SetBitmap(imgBlk.Detach());
	}
	Image.Destroy();
	Invalidate();
}

void CNPuzzleDlg::OnAboutbox()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
