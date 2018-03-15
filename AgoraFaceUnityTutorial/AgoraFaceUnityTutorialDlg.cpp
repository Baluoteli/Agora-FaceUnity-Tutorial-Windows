
// AgoraFaceUnityTutorialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgoraFaceUnityTutorial.h"
#include "AgoraFaceUnityTutorialDlg.h"
#include "afxdialogex.h"
#include "commonfun.h"
#include "FrameFrequencyCtrl.h"
using namespace plusFCL_BTL;
#include "YUVTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAgoraFaceUnityTutorialDlg 对话框



CAgoraFaceUnityTutorialDlg::CAgoraFaceUnityTutorialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgoraFaceUnityTutorialDlg::IDD, pParent),
	is_need_draw_landmarks(FALSE)
	, m_ThreadData(NULL)
	, m_bTerminated(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgoraFaceUnityTutorialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CameraDS, m_ComCamera);
	DDX_Control(pDX, IDC_EDIT_MediaUID, m_AgEditMediaUid);
	DDX_Control(pDX, IDC_EDIT_ChannelID, m_AgEditChannelName);
	DDX_Control(pDX, IDC_BUTTON_JoinChannel, m_AgBtnJoinChannel);
	DDX_Control(pDX, IDC_STATIC_Local, m_PicCtlLocal);
	DDX_Control(pDX, IDC_STATIC_Remote, m_PicCtlRemote);
	DDX_Control(pDX, IDC_BUTTON_Sticker_0, m_AgBtnSticker_0);
	DDX_Control(pDX, IDC_BUTTON_Sticker_1, m_AgBtnSticker_1);
	DDX_Control(pDX, IDC_BUTTON_Sticker_2, m_AgBtnSticker_2);
	DDX_Control(pDX, IDC_BUTTON_Sticker_3, m_AgBtnSticker_3);
	DDX_Control(pDX, IDC_BUTTON_Sticker_4, m_AgBtnSticker_4);
	DDX_Control(pDX, IDC_BUTTON_Sticker_5, m_AgBtnSticker_5);
	DDX_Control(pDX, IDC_BUTTON_Sticker_6, m_AgBtnSticker_6);
	DDX_Control(pDX, IDC_BUTTON_Sticker_7, m_AgBtnSticker_7);
	DDX_Control(pDX, IDC_BUTTON_Sticker_8, m_AgBtnSticker_8);
	DDX_Control(pDX, IDC_BUTTON_Filter_0, m_AgBtnFilter_0);
	DDX_Control(pDX, IDC_BUTTON_Filter_1, m_AgBtnFilter_1);
	DDX_Control(pDX, IDC_BUTTON_Filter_2, m_AgBtnFilter_2);
	DDX_Control(pDX, IDC_BUTTON_Filter_3, m_AgBtnFilter_3);
	DDX_Control(pDX, IDC_BUTTON_Filter_4, m_AgBtnFilter_4);
	DDX_Control(pDX, IDC_BUTTON_Filter_5, m_AgBtnFilter_5);
	DDX_Control(pDX, IDC_Check_Sticker, m_BtnCheckSticker);
	DDX_Control(pDX, IDC_Check_Beauty, m_BtnCheckBeauty);
}

BEGIN_MESSAGE_MAP(CAgoraFaceUnityTutorialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_CameraDS, &CAgoraFaceUnityTutorialDlg::OnCbnSelchangeComboCamerads)
	ON_BN_CLICKED(IDC_BUTTON_JoinChannel, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonJoinchannel)
	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS), onJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_WARNING), onWarning)
	ON_MESSAGE(WM_MSGID(EID_ERROR), onError)
	ON_MESSAGE(WM_MSGID(EID_LEAVE_CHANNEL), onLeaveChannel)
	ON_MESSAGE(WM_MSGID(EID_REQUEST_CHANNELKEY), onRequestChannelKey)
	ON_MESSAGE(WM_MSGID(EID_LASTMILE_QUALITY), onLastMileQuality)
	ON_MESSAGE(WM_MSGID(EID_FIRST_LOCAL_VIDEO_FRAME), onFirstLocalVideoFrame)
	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_DECODED), onFirstRemoteVideoDecoded)
	ON_MESSAGE(WM_MSGID(EID_FIRST_REMOTE_VIDEO_FRAME), onFirstRmoteVideoFrame)
	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), onUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), onUserOff)
	ON_MESSAGE(WM_MSGID(EID_USER_MUTE_VIDEO), onUserMuteVideo)
	ON_MESSAGE(WM_MSGID(EID_CONNECTION_LOST), onConnectionLost)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_0, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker0)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_1, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker1)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_2, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker2)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_3, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker3)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_4, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker4)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_5, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker5)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_6, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker6)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_7, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker7)
	ON_BN_CLICKED(IDC_BUTTON_Sticker_8, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker8)
	ON_BN_CLICKED(IDC_BUTTON_Filter_0, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter0)
	ON_BN_CLICKED(IDC_BUTTON_Filter_1, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter1)
	ON_BN_CLICKED(IDC_BUTTON_Filter_2, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter2)
	ON_BN_CLICKED(IDC_BUTTON_Filter_3, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter3)
	ON_BN_CLICKED(IDC_BUTTON_Filter_4, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter4)
	ON_BN_CLICKED(IDC_BUTTON_Filter_5, &CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter5)
	ON_BN_CLICKED(IDC_Check_Sticker, &CAgoraFaceUnityTutorialDlg::OnBnClickedCheckSticker)
	ON_BN_CLICKED(IDC_Check_Beauty, &CAgoraFaceUnityTutorialDlg::OnBnClickedCheckBeauty)
END_MESSAGE_MAP()


// CAgoraFaceUnityTutorialDlg 消息处理程序

BOOL CAgoraFaceUnityTutorialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	SetBackgroundColor(RGB(0xff, 0xff, 0xff), TRUE);

	m_strAppId = s2cs(gAgoraFaceUnityConfig.getAppId());
	if (_T("") == m_strAppId){
		AfxMessageBox(_T("APPID is empty .please input again."));
		std::string iniFilePath = gAgoraFaceUnityConfig.getFilePah();
		gAgoraFaceUnityConfig.setAppId("");
		ShellExecute(NULL, _T("open"), s2cs(iniFilePath), NULL, NULL, SW_SHOW);
		::PostQuitMessage(0);
		return FALSE;
	}

	initCtrl();
	initAgoraMedia();
	initFaceUnity();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAgoraFaceUnityTutorialDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAgoraFaceUnityTutorialDlg::OnPaint()
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
HCURSOR CAgoraFaceUnityTutorialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAgoraFaceUnityTutorialDlg::OnCbnSelchangeComboCamerads()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonJoinchannel()
{
	// TODO:  在此添加控件通知处理程序代码

	CString strParam;
	m_AgBtnJoinChannel.GetWindowTextW(strParam);
	if (_T("JoinChannel") == strParam){

		m_lpAgoraObject->EnableLastmileTest(FALSE);
		m_lpAgoraObject->SetClientRole(CLIENT_ROLE_TYPE::CLIENT_ROLE_BROADCASTER);
		m_lpAgoraObject->SetChannelProfile(TRUE);

		m_uMediaUid = str2int(gAgoraFaceUnityConfig.getLoginUid());
		std::string strAppcertificatId = gAgoraFaceUnityConfig.getAppCertificateId();
		m_lpAgoraObject->SetSelfUID(m_uMediaUid);
		m_lpAgoraObject->SetAppCert(s2cs(strAppcertificatId));

		VideoCanvas vc;
		vc.renderMode = RENDER_MODE_FIT;
		vc.uid = m_uMediaUid;
		vc.view = m_PicCtlLocal;
		m_lpRtcEngine->setupLocalVideo(vc);

		int nVideoIndex = str2int(gAgoraFaceUnityConfig.getVideoSolutinIndex());
		m_lpAgoraObject->SetVideoProfile(nVideoIndex, FALSE);//640*480 15 500

		m_lpRtcEngine->startPreview();

		bool bAppCertEnalbe = str2int(gAgoraFaceUnityConfig.getAppCertEnable());
		if (bAppCertEnalbe){

			CStringA strMediaChannelKey = m_lpAgoraObject->getDynamicMediaChannelKey(m_ChannelName);
			m_lpAgoraObject->JoinChannel(m_ChannelName, m_uMediaUid, strMediaChannelKey);
		}
		else{

			m_lpAgoraObject->JoinChannel(m_ChannelName, m_uMediaUid);
		}
	}
	else if (_T("LeaveChannel") == strParam){

		m_lpAgoraObject->LeaveCahnnel();
		m_lpRtcEngine->stopPreview();
	}
}

inline void CAgoraFaceUnityTutorialDlg::initCtrl()
{
	int nCameraCount = m_FaceName.CameraCount();
	for (int nCameraIndex = 0; nCameraCount > nCameraIndex; nCameraIndex++){

		char szbuf[PATH_LEN] = { '\0' };
		int nRes = m_FaceName.CameraName(nCameraIndex, szbuf, PATH_LEN);
		if (nRes){

			m_ComCamera.AddString(s2cs(szbuf));
		}
	}

	m_ComCamera.SetCurSel(0);

	m_AgEditMediaUid.SetTip(_T("MediaUID"));
	m_AgEditChannelName.SetTip(_T("ChannelName"));

	CString csParam = s2cs(gAgoraFaceUnityConfig.getLoginUid());
	m_ChannelName = s2cs(gAgoraFaceUnityConfig.getChannelName());
	m_AgEditMediaUid.SetWindowTextW(csParam);
	m_AgEditChannelName.SetWindowTextW(m_ChannelName);
	m_AgBtnSticker_0.SetBackImage(IDB_BITMAP_Stride_0);
	m_AgBtnSticker_0.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_1.SetBackImage(IDB_BITMAP_Stride_1);
	m_AgBtnSticker_1.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_2.SetBackImage(IDB_BITMAP_Stride_2);
	m_AgBtnSticker_2.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_3.SetBackImage(IDB_BITMAP_Stride_3);
	m_AgBtnSticker_3.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_4.SetBackImage(IDB_BITMAP_Stride_4);
	m_AgBtnSticker_4.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_5.SetBackImage(IDB_BITMAP_Stride_5);
	m_AgBtnSticker_5.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_6.SetBackImage(IDB_BITMAP_Stride_6);
	m_AgBtnSticker_6.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_7.SetBackImage(IDB_BITMAP_Stride_7);
	m_AgBtnSticker_7.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnSticker_8.SetBackImage(IDB_BITMAP_Stride_8);
	m_AgBtnSticker_8.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));

	m_AgBtnFilter_0.SetBackImage(IDB_BITMAP_Filter_0);
	m_AgBtnFilter_0.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnFilter_1.SetBackImage(IDB_BITMAP_Filter_1);
	m_AgBtnFilter_1.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnFilter_2.SetBackImage(IDB_BITMAP_Filter_2);
	m_AgBtnFilter_2.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnFilter_3.SetBackImage(IDB_BITMAP_Filter_3);
	m_AgBtnFilter_3.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnFilter_4.SetBackImage(IDB_BITMAP_Filter_4);
	m_AgBtnFilter_4.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
	m_AgBtnFilter_5.SetBackImage(IDB_BITMAP_Filter_5);
	m_AgBtnFilter_5.SetBackColor(RGB(0, 160, 239), RGB(255, 255, 0), RGB(255, 128, 128), RGB(0, 160, 239));
}

inline void CAgoraFaceUnityTutorialDlg::uninitCtrl()
{
	m_ComCamera.Clear();

	m_strAppId = _T("");
	m_uMediaUid = 0;
	m_ChannelName = _T("");
}

inline void CAgoraFaceUnityTutorialDlg::initAgoraMedia()
{
	if ("" == m_strAppId)
		return;

	m_lpAgoraObject = CAgoraObject::GetAgoraObject(m_strAppId);
	ASSERT(m_lpAgoraObject);
	m_lpAgoraObject->SetMsgHandlerWnd(m_hWnd);

	m_lpRtcEngine = CAgoraObject::GetEngine();
	ASSERT(m_lpRtcEngine);

	CString strSdkLogFilePath = s2cs(getMediaSdkLogPath());
	m_lpAgoraObject->SetLogFilePath(strSdkLogFilePath);
	m_lpAgoraObject->EnableLastmileTest(TRUE);
	m_lpAgoraObject->EnableLocalMirrorImage(FALSE);
	m_lpAgoraObject->EnableLoopBack(FALSE);

	m_lpAgoraObject->EnableVideo(TRUE);
}

inline void CAgoraFaceUnityTutorialDlg::uninitAgoraMedia()
{
	if (nullptr == m_lpAgoraObject)
		return;

	m_lpAgoraObject->EnableVideo(FALSE);
	m_lpAgoraObject->EnableLastmileTest(FALSE);
	if (m_lpAgoraObject){
		CAgoraObject::CloseAgoraObject();
		m_lpAgoraObject = nullptr;
		m_lpRtcEngine = nullptr;
	}
}

inline void CAgoraFaceUnityTutorialDlg::initFaceUnity()
{
#if 0
	std::string strVersiono = m_FaceName.getVersion();
	m_openGl.SetupPixelFormat(::GetDC(m_PicCtlLocal));
	CRect rect;
	GetClientRect(&rect);
	m_openGl.Init(rect.right, rect.bottom);
	SetTimer(1, 40, 0);
#endif

	m_FaceName.Init(m_nWidth,m_nHeight);

	if (nullptr == m_ThreadData){

		m_bTerminated = FALSE;
		DWORD threadID = 0;
		m_ThreadData = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFaceUntiyDataProc, this, 0, &threadID);
	}
}

inline void CAgoraFaceUnityTutorialDlg::uninitFaceUnity()
{
	if (!m_bTerminated)
		m_bTerminated = true;

	DWORD dExitCode = 0;
	TerminateThread(m_ThreadData,dExitCode);
	CloseHandle(m_ThreadData);
	m_ThreadData = nullptr;
}

LRESULT CAgoraFaceUnityTutorialDlg::onJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onWarning(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onError(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onRequestChannelKey(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onLastMileQuality(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onFirstLocalVideoFrame(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onFirstRemoteVideoDecoded(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onFirstRmoteVideoFrame(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onUserJoined(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onUserOff(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onUserMuteVideo(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

LRESULT CAgoraFaceUnityTutorialDlg::onConnectionLost(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker0()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(0);
	is_need_draw_landmarks = false;
}

void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(1);
	is_need_draw_landmarks = false;
}

void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker2()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(2);
	is_need_draw_landmarks = false;
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(3);
	is_need_draw_landmarks = false;
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker5()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(4);
	is_need_draw_landmarks = false;
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker6()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(5);
	is_need_draw_landmarks = false;
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker7()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(6);
	is_need_draw_landmarks = false;
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonSticker8()
{
	// TODO:  在此添加控件通知处理程序代码
	m_FaceName.SetCurrentBundle(7);
	is_need_draw_landmarks = false;
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter0()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter1()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter2()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter3()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter4()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CAgoraFaceUnityTutorialDlg::OnBnClickedButtonFilter5()
{
	// TODO:  在此添加控件通知处理程序代码
}


DWORD CAgoraFaceUnityTutorialDlg::ThreadFaceUntiyDataProc(LPVOID lpParameter)
{
	CAgoraFaceUnityTutorialDlg *pObj = (CAgoraFaceUnityTutorialDlg*)lpParameter;
	CYUVTrans yuvTrans;
	LPBYTE yuvBuffer = new BYTE[0x800000];
	SIZE_T yuvBufferLen = pObj->m_nWidth * pObj->m_nHeight * 3 / 2;
	CFileIO fileMedia;
#ifdef _DEBUG
	fileMedia.openMedia("D:\\Agora_programe\\baluoteli\\Agora-FaceUnity-Tutorial-Windows\\Debug\\cameraYuv.yuv");
#else
	fileMedia.openMedia("D:\\Agora_programe\\baluoteli\\Agora-FaceUnity-Tutorial-Windows\\Release\\cameraYuv.yuv");
#endif

	if (pObj){

		CHighResoluteFrameCtrl framectrl;
		framectrl.setInterval(40);

		while (!pObj->m_bTerminated){
			framectrl.wait();

			std::tr1::shared_ptr<unsigned char> frame = pObj->m_FaceName.QueryFrame();
#if 0
			if (!frame)
				OutputDebugStringA("QueryFrame failed..\n");

			if ( !yuvTrans.RGB24ToI420((LPBYTE)frame.get(), yuvBuffer, yuvBufferLen, pObj->m_nWidth, pObj->m_nHeight))
				OutputDebugStringA("RGB24ToI420 failed..\n");

			std::tr1::shared_ptr<unsigned char> frameYUV = (std::tr1::shared_ptr<unsigned char>)yuvBuffer;
			pObj->m_FaceName.RenderItems(frameYUV);

			fileMedia.write((char*)frameYUV.get(), yuvBufferLen);
			fileMedia.close();
#else
			//pObj->m_FaceName.RenderItems(frame);
			int rgbaLen = pObj->m_nWidth * pObj->m_nHeight * 4;
			//pObj->m_openGl.Render(frame);

			std::tr1::shared_ptr<unsigned char> frameYUV1 = pObj->m_FaceName.ConvertBetweenBGRAandRGBA(frame);
			fileMedia.write((char*)frameYUV1.get(), rgbaLen);

			//pObj->Invalidate(FALSE);
#endif
		}
	}

	fileMedia.close();
	if (yuvBuffer)
		delete[] yuvBuffer;
	yuvBufferLen = 0;

	return TRUE;
}

void CAgoraFaceUnityTutorialDlg::OnClose()
{
	//TO DO
	if (m_lpAgoraObject)
		m_lpAgoraObject->LeaveCahnnel();

	if (m_lpRtcEngine)
		m_lpRtcEngine->stopPreview();

	uninitFaceUnity();
	uninitAgoraMedia();
	uninitCtrl();

	CDialogEx::OnClose();
}

void CAgoraFaceUnityTutorialDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1){

		std::tr1::shared_ptr<unsigned char>frame;
	//	m_openGl.Render(frame);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CAgoraFaceUnityTutorialDlg::OnBnClickedCheckSticker()
{
	// TODO:  在此添加控件通知处理程序代码

}


void CAgoraFaceUnityTutorialDlg::OnBnClickedCheckBeauty()
{
	// TODO:  在此添加控件通知处理程序代码
}
