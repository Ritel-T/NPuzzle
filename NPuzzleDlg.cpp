
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
	ON_BN_CLICKED(IDC_BUTTON1, &CNPuzzleDlg::OnBnClickedButtonST)
	ON_WM_TIMER()
	ON_COMMAND(IDM_OPEN, &CNPuzzleDlg::OnOpen)
	ON_COMMAND(IDM_RESETBRD, &CNPuzzleDlg::OnResetBrd)
	ON_COMMAND(IDM_RESETIMG, &CNPuzzleDlg::OnResetImg)
	ON_COMMAND(IDM_ABOUTBOX, &CNPuzzleDlg::OnAboutBox)
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
	// 随机数种子
	srand(time(NULL));

	// 获取方块位置
	for (int i = 1; i < 16; ++i)
	{
		m_Blk[i].GetWindowRect(&rctBlk[i]);
		ScreenToClient(&rctBlk[i]);
	}
	rctBlk[16] = { rctBlk[15].right, rctBlk[12].bottom,
		rctBlk[15].right + rctBlk[1].Width(),
		rctBlk[12].bottom + rctBlk[1].Height() };

	// 初始盘面
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

// 设置盘面
void CNPuzzleDlg::Reset(bool bTime, bool bRand, bool bImage)
{
	KillTimer(1);
	nSec = 0; nMin = 0;
	SetDlgItemText(IDC_TIME, L"00 : 00");

	if (bRand) // 随机生成盘面
	{
		int nNumRd, nDif = 0;
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
				m_Blk[nNumRd].MoveWindow(&rctBlk[i], FALSE);
			}
			nNumInPos[i] = nNumRd;
			nPosOfNum[nNumRd] = i;
		}
		// 检查无解
		for (int i = 2; i <= 16; ++i)
		{
			for (int j = 1; j < i; ++j)
				if (nNumInPos[j] > nNumInPos[i]) ++nDif;
		}
		nDif += (nPosOfNum[0] - 1) % 4 + (nPosOfNum[0] - 1) / 4;

		if (nDif % 2 == 0) // 无解情况
		{
			if (nNumInPos[15]) m_Blk[nNumInPos[15]].MoveWindow(&rctBlk[16], FALSE);
			if (nNumInPos[16]) m_Blk[nNumInPos[16]].MoveWindow(&rctBlk[15], FALSE);
			int t = nNumInPos[15];
			nNumInPos[15] = nNumInPos[16];
			nNumInPos[16] = t;
			nPosOfNum[nNumInPos[15]] = 15;
			nPosOfNum[nNumInPos[16]] = 16;
		}
	}
	else // 恢复盘面
	{
		nPosOfNum[0] = 16;
		for (int i = 1; i < 16; ++i)
		{
			m_Blk[i].MoveWindow(&rctBlk[i], FALSE);
			nNumInPos[i] = i;
			nPosOfNum[i] = i;
		}
		nNumInPos[16] = 0;
	}

	// 恢复数字图像
	if (bImage)
	{
		int nBlkW = rctBlk[1].Width(), nBlkH = rctBlk[1].Height();
		RECT rctImage = { 0, 0, nBlkW, nBlkH };

		// 创建白底图像
		CImage imgBlkBg;
		imgBlkBg.Create(nBlkW, nBlkH, 24);
		for (int j = 0; j < nBlkH; ++j)
			for (int k = 0; k < nBlkW; ++k)
				imgBlkBg.SetPixelRGB(k, j, 255, 255, 255);

		for (int i = 1; i < 16; ++i) // 绘制数字
		{
			CImage imgBlk;
			imgBlk.Create(nBlkW, nBlkH, 24);

			HDC hDC = imgBlk.GetDC();
			imgBlkBg.BitBlt(hDC, 0, 0, nBlkW, nBlkH, 0, 0);

			int nWidth = nBlkW / 2 - 16, nHeight = 2.3 * nWidth;
			CFont font;
			font.CreateFont(nHeight, nWidth, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"等线");
			SelectObject(hDC, font);

			CString wszNum;
			_itow_s(i, wszNum.GetBuffer(4), 4, 10);
			wszNum.ReleaseBuffer();

			DrawText(hDC, wszNum, wszNum.GetLength(), &rctImage, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			imgBlk.BitBlt(hDC, 0, 0, nBlkW, nBlkH, 0, 0);

			imgBlk.ReleaseDC();
			m_Blk[i].SetBitmap(imgBlk.Detach());
		}
	}
	// 开始计时
	if (bTime) SetTimer(1, 1000, NULL);

	Invalidate();
}

// 移动方块
void CNPuzzleDlg::MoveBlk(int nNumClk)
{
	int nPosClk = nPosOfNum[nNumClk],
		nPosLine = (nPosClk - 1) / 4 * 4 + 1, nPosCol = (nPosClk - 1) % 4 + 1;
	if (nPosOfNum[0] >= nPosLine && nPosOfNum[0] <= nPosLine + 3) // 空位同行
	{
		if (nPosOfNum[0] < nPosClk) // 空位在左边
		{

			for (int iPos = nPosOfNum[0] + 1, i = 0; iPos <= nPosClk; ++iPos, ++i)
			{
				int nNumMv = nNumInPos[iPos];

				SLIDEBLKSTRUCT* sbs = new SLIDEBLKSTRUCT;
				*sbs = { this, nNumMv, iPos, iPos - 1, 50 * i };

				CloseHandle(CreateThread(NULL, NULL, ThreadSlideBlk, sbs, NULL, NULL));

				nPosOfNum[nNumMv] = iPos - 1;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos - 1] = nNumMv;
				nNumInPos[iPos] = 0;
			}
		}
		else // 空位在右边
		{
			for (int iPos = nPosOfNum[0] - 1, i = 0; iPos >= nPosClk; --iPos, ++i)
			{
				int nNumMv = nNumInPos[iPos];

				SLIDEBLKSTRUCT* sbs = new SLIDEBLKSTRUCT;
				*sbs = { this, nNumMv, iPos, iPos + 1, 50 * i };
				CloseHandle(CreateThread(NULL, NULL, ThreadSlideBlk, sbs, NULL, NULL));

				nPosOfNum[nNumMv] = iPos + 1;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos + 1] = nNumMv;
				nNumInPos[iPos] = 0;
			}
		}
	}
	else if ((nPosOfNum[0] - 1) % 4 + 1 == nPosCol) // 空位同列
	{
		if (nPosOfNum[0] < nPosClk) // 空位在上方
		{
			for (int iPos = nPosOfNum[0] + 4, i = 0; iPos <= nPosClk; iPos += 4, ++i)
			{
				int nNumMv = nNumInPos[iPos];

				SLIDEBLKSTRUCT* sbs = new SLIDEBLKSTRUCT;
				*sbs = { this, nNumMv,  iPos, iPos - 4, 50 * i };
				CloseHandle(CreateThread(NULL, NULL, ThreadSlideBlk, sbs, NULL, NULL));

				nPosOfNum[nNumMv] = iPos - 4;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos - 4] = nNumMv;
				nNumInPos[iPos] = 0;
			}
		}
		else // 空位在下方
		{
			for (int iPos = nPosOfNum[0] - 4, i = 0; iPos >= nPosClk; iPos -= 4, ++i)
			{
				int nNumMv = nNumInPos[iPos];

				SLIDEBLKSTRUCT* sbs = new SLIDEBLKSTRUCT;
				*sbs = { this, nNumMv, iPos, iPos + 4, 50 * i };
				CloseHandle(CreateThread(NULL, NULL, ThreadSlideBlk, sbs, NULL, NULL));

				nPosOfNum[nNumMv] = iPos + 4;
				nPosOfNum[0] = iPos;
				nNumInPos[iPos + 4] = nNumMv;
				nNumInPos[iPos] = 0;
			}
		}
	}
	CheckCpl();
}

// 滑动方块
void CNPuzzleDlg::SlideBlk(int nNum, int nPosSrc, int nPosDest)
{
	CRect rctMove = rctBlk[nPosSrc], rctDest = rctBlk[nPosDest];
	int nXSrc = rctMove.left, nYSrc = rctMove.top;

	int nMoveX = rctDest.left - rctMove.left;
	int nMoveY = rctDest.top - rctMove.top;

	const int T = 240, dT = 10;
	int t1 = dT;
	// Acceleration
	double ax = 4.0 * nMoveX / T / T, ay = 4.0 * nMoveY / T / T;
	// Displacement
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	double vx0 = ax * dT * 2, vy0 = ay * dT * 2;
	for (; t1 <= 0.3125 * T; t1 += dT) // 加速运动
	{
		x1 = vx0 * t1 + 0.5 * ax * t1 * t1;
		y1 = vy0 * t1 + 0.5 * ay * t1 * t1;
		rctMove.MoveToXY(nXSrc + x1, nYSrc + y1);
		m_Blk[nNum].MoveWindow(&rctMove);
		Sleep(dT);
	}

	vx0 = ax * t1, vy0 = ay * t1;
	for (; t1 <= 0.5375 * T; t1 += dT) // 较快的匀速运动
	{
		x1 += 2.0 * nMoveX / T * dT;
		y1 += 2.0 * nMoveY / T * dT;
		rctMove.MoveToXY(nXSrc + x1, nYSrc + y1);
		m_Blk[nNum].MoveWindow(&rctMove);
		Sleep(dT);
	}
	InvalidateRect(&rctMove);

	for (int t2 = dT; t1 <= 0.75 * T; t1 += dT, t2 += dT) // 减速运动
	{
		// 相对于 x1, y1 的位移
		x2 = vx0 * t2 - 0.5 * ax * t2 * t2;
		y2 = vy0 * t2 - 0.5 * ay * t2 * t2;
		rctMove.MoveToXY(nXSrc + x1 + x2, nYSrc + y1 + y2);
		m_Blk[nNum].MoveWindow(&rctMove);
		Sleep(dT);
	}

	while (TRUE) // 较慢的匀速运动
	{
		x2 += ax * dT * dT;
		y2 += ay * dT * dT;
		rctMove.MoveToXY(nXSrc + x1 + x2, nYSrc + y1 + y2);
		if (abs(rctMove.left - rctDest.left) <= 1 &&
			abs(rctMove.top - rctDest.top) <= 1) break;
		m_Blk[nNum].MoveWindow(&rctMove);
		Sleep(dT);
	}

	m_Blk[nNum].MoveWindow(&rctDest, FALSE);

	rctDest.left -= 5; rctDest.right += 5;
	rctDest.top -= 5; rctDest.bottom += 5;
	InvalidateRect(&rctDest);
}

// 检查完成
void CNPuzzleDlg::CheckCpl()
{
	for (int i = 1; i < 16; ++i)
	{
		if (nPosOfNum[i] != i) return;
	}
	KillTimer(1);

	::SetForegroundWindow(GetDesktopWindow()->m_hWnd);
	SetForegroundWindow();
}

// 加载图片
void CNPuzzleDlg::LoadImg()
{
	CRect RectBrd(0, 0, rctBlk[16].right, rctBlk[16].bottom);

	int nBlkW = rctBlk[1].Width(), nBlkH = rctBlk[1].Height(),
		nBrdW = RectBrd.Width(), nBrdH = RectBrd.Height();
	if (imgSel.GetWidth() != nBrdW || imgSel.GetHeight() != nBrdH)
	{
		// 等比缩放到 imgTemp
		int nSrcW = imgSel.GetWidth(), nSrcH = imgSel.GetHeight();
		double fScale = max((double)nBrdW / nSrcW, (double)nBrdH / nSrcH);
		int nDestW = nSrcW * fScale, nDestH = nSrcH * fScale;

		CImage imgTemp;
		imgTemp.Create(nDestW, nDestH, 24);
		HDC hDCNew = imgTemp.GetDC();
		SetStretchBltMode(hDCNew, HALFTONE);
		imgSel.StretchBlt(hDCNew, 0, 0, nDestW, nDestH);

		imgTemp.ReleaseDC();
		imgSel.Destroy();

		// 裁剪中心部分到 imgSel
		imgSel.Create(nBrdW, nBrdH, 24);
		imgTemp.BitBlt(imgSel.GetDC(), 0, 0, nBrdW, nBrdH, (nDestW - nBrdW) / 2, (nDestH - nBrdH) / 2);
		imgSel.ReleaseDC();
	}
	for (int i = 1; i < 16; ++i)
	{
		CImage imgBlk;
		imgBlk.Create(nBlkW, nBlkH, 24);
		imgSel.BitBlt(imgBlk.GetDC(), 0, 0, nBlkW, nBlkH, rctBlk[i].left, rctBlk[i].top);
		imgBlk.ReleaseDC();
		m_Blk[i].SetBitmap(imgBlk.Detach());
	}
	imgSel.Destroy();

	Invalidate();
}

// 按下开始按钮
void CNPuzzleDlg::OnBnClickedButtonST()
{
	// TODO: 在此添加控件通知处理程序代码
	Reset();
	SetDlgItemText(IDC_BUTTON1, L"もう一回");
}

// 按下 OK
void CNPuzzleDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButtonST();
}

// 计时事件
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

// 打开文件
void CNPuzzleDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlgFile(
		TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		L"imgSel Files (*.bmp;*.jpg;*.jpeg;*.png)|*.jpg; *.jpeg; *.png||");
	dlgFile.m_ofn.lpstrTitle = L"画像ファイルを選択";
	if (dlgFile.DoModal() == IDOK)
	{
		CString wszFile = dlgFile.GetPathName();
		if (FAILED(imgSel.Load(wszFile)))
			MessageBox(L"画像ファイルのロードに失敗しました", L"エラー");
		else LoadImg();
	}
	::SetForegroundWindow(GetDesktopWindow()->m_hWnd);
	SetForegroundWindow();
}

// 重置盘面
void CNPuzzleDlg::OnResetBrd()
{
	// TODO: 在此添加命令处理程序代码
	Reset(FALSE, FALSE);
	SetDlgItemText(IDC_BUTTON1, L"ミッションスタートだ！");
}

// 重置图像
void CNPuzzleDlg::OnResetImg()
{
	// TODO: 在此添加命令处理程序代码
	Reset(FALSE, FALSE, TRUE);
	SetDlgItemText(IDC_BUTTON1, L"ミッションスタートだ！");
}

void CNPuzzleDlg::OnAboutBox()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
