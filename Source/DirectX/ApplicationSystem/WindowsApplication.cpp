#include "WindowsApplication.h"


/**
* @brief コンストラクタ
*/
WindowsApplication::WindowsApplication()
{
	m_hWnd = NULL;
	ZeroMemory(&m_msg, sizeof(m_msg));
}

/**
* @brief デストラクタ
*/
WindowsApplication::~WindowsApplication()
{

}

/**
* @brief 作成
*/
HRESULT WindowsApplication::Create(HINSTANCE hInst)
{
	// ウィンドウクラスの登録
	if (!RegisterWindowClass(hInst, WndProc)) return E_FAIL;

	// ウィンドウの初期化
	if (!WindowInitialize(hInst)) return E_FAIL;

	// 成功
	return S_OK;
}

/**
* @brief ウィンドウの初期化（ 作成 ）
*/
BOOL WindowsApplication::WindowInitialize(HINSTANCE hInst)
{
	// フルスクリーンモードかウィンドウモードかを選択
	bool isWindowed = true;
	if (MessageBox(0, "フルスクリーンモードで起動しますか？", "確認", MB_YESNO) == IDYES) {
		isWindowed = false;
	}
	// ウィンドウモードをセット
	AppIns->SetWindowed(isWindowed);

	RECT rcWindow;
	rcWindow.left = 0;
	rcWindow.top = 0;
	rcWindow.right = WINDOW_WIDTH;
	rcWindow.bottom = WINDOW_HEIGHT;

	// クライアント領域からウィンドウ領域を計算
	AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, FALSE);

	// ウィンドウを作成する（中央に）
	m_hWnd = CreateWindow(APPLICATION_NAME, 
		APPLICATION_NAME, 
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (rcWindow.right - rcWindow.left) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - (rcWindow.bottom - rcWindow.top) / 2,
		rcWindow.right - rcWindow.left, 
		rcWindow.bottom - rcWindow.top, NULL, NULL, hInst, NULL);
	if (!m_hWnd){
		MessageBox(0, "CreateWindowに失敗しました。", "WindowInitializeError!", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// ウィンドウの表示状態を設定
	ShowWindow(m_hWnd, SW_SHOW);

	// ウィンドウの更新
	UpdateWindow(m_hWnd);

	// ウィンドウハンドルをセット
	AppIns->SetWindowHandle(m_hWnd);

	return TRUE;
}

/**
* @brief ウィンドウクラスへ登録
* @param hInst   ： インスタンス
* @param WndProc ： ウィンドウプロシージャ
*/
ATOM WindowsApplication::RegisterWindowClass(HINSTANCE hInst, WNDPROC WndProc)
{
	WNDCLASSEX  wndclass;

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = APPLICATION_NAME;
	wndclass.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	
	return RegisterClassEx(&wndclass);
}

/**
* @brief ウィンドウプロシージャ
* @param 規定のパラメータ
* @return メッセージ処理の結果
*/
LRESULT CALLBACK WindowsApplication::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	// 破棄
	case WM_DESTROY:
		PostQuitMessage(0);
		DestroyWindow(hWnd);
		break;

	//強制終了
	case  WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(hWnd);
		break;

	case WM_KEYDOWN:
		switch (wParam){
		case VK_ESCAPE: 
			PostQuitMessage(0);
			DestroyWindow(hWnd);
			break;

		case VK_F1: 
			OpenDebugWindow();
			break;
		}
		break;

		// マウスカーソルセット
	case WM_SETCURSOR:
		if (!AppIns->GetWindowed()){
			SetCursor(NULL);
		}
		return 1;
		break;

	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

	return 0;
}

/**
* @brief ウィンドウからのメッセージ処理
*/
BOOL WindowsApplication::ProcessEvent()
{
	if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		// ウィンドウプロシージャへメッセージを送出
		DispatchMessage(&m_msg);
	}
	if (m_msg.message != WM_QUIT){
		return FALSE;
	}
	return TRUE;
}

/**
* @brief 解放
*/
VOID WindowsApplication::Release()
{
	CloseDebugWindow();
}


// デバッグウィンドウ用
static FILE* DebugFP = NULL;

/**
* @brief デバッグ用ウィンドウを開く
*/
void WindowsApplication::OpenDebugWindow()
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s(&DebugFP, "CONOUT$", "w", stdout);
	freopen_s(&DebugFP, "CONIN$", "r", stdin);
#endif
}

/**
* @brief デバッグ用ウィンドウを閉じる
*/
void WindowsApplication::CloseDebugWindow()
{
#ifdef _DEBUG
	if (DebugFP)
	{
		fclose(DebugFP);
		FreeConsole();
	}
#endif
}