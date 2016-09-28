#include "WindowsApplication.h"


/**
* @brief �R���X�g���N�^
*/
WindowsApplication::WindowsApplication()
{
	m_hWnd = NULL;
	ZeroMemory(&m_msg, sizeof(m_msg));
}

/**
* @brief �f�X�g���N�^
*/
WindowsApplication::~WindowsApplication()
{

}

/**
* @brief �쐬
*/
HRESULT WindowsApplication::Create(HINSTANCE hInst)
{
	// �E�B���h�E�N���X�̓o�^
	if (!RegisterWindowClass(hInst, WndProc)) return E_FAIL;

	// �E�B���h�E�̏�����
	if (!WindowInitialize(hInst)) return E_FAIL;

	// ����
	return S_OK;
}

/**
* @brief �E�B���h�E�̏������i �쐬 �j
*/
BOOL WindowsApplication::WindowInitialize(HINSTANCE hInst)
{
	// �t���X�N���[�����[�h���E�B���h�E���[�h����I��
	bool isWindowed = true;
	if (MessageBox(0, "�t���X�N���[�����[�h�ŋN�����܂����H", "�m�F", MB_YESNO) == IDYES) {
		isWindowed = false;
	}
	// �E�B���h�E���[�h���Z�b�g
	AppIns->SetWindowed(isWindowed);

	RECT rcWindow;
	rcWindow.left = 0;
	rcWindow.top = 0;
	rcWindow.right = WINDOW_WIDTH;
	rcWindow.bottom = WINDOW_HEIGHT;

	// �N���C�A���g�̈悩��E�B���h�E�̈���v�Z
	AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, FALSE);

	// �E�B���h�E���쐬����i�����Ɂj
	m_hWnd = CreateWindow(APPLICATION_NAME, 
		APPLICATION_NAME, 
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (rcWindow.right - rcWindow.left) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - (rcWindow.bottom - rcWindow.top) / 2,
		rcWindow.right - rcWindow.left, 
		rcWindow.bottom - rcWindow.top, NULL, NULL, hInst, NULL);
	if (!m_hWnd){
		MessageBox(0, "CreateWindow�Ɏ��s���܂����B", "WindowInitializeError!", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// �E�B���h�E�̕\����Ԃ�ݒ�
	ShowWindow(m_hWnd, SW_SHOW);

	// �E�B���h�E�̍X�V
	UpdateWindow(m_hWnd);

	// �E�B���h�E�n���h�����Z�b�g
	AppIns->SetWindowHandle(m_hWnd);

	return TRUE;
}

/**
* @brief �E�B���h�E�N���X�֓o�^
* @param hInst   �F �C���X�^���X
* @param WndProc �F �E�B���h�E�v���V�[�W��
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
* @brief �E�B���h�E�v���V�[�W��
* @param �K��̃p�����[�^
* @return ���b�Z�[�W�����̌���
*/
LRESULT CALLBACK WindowsApplication::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	// �j��
	case WM_DESTROY:
		PostQuitMessage(0);
		DestroyWindow(hWnd);
		break;

	//�����I��
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

		// �}�E�X�J�[�\���Z�b�g
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
* @brief �E�B���h�E����̃��b�Z�[�W����
*/
BOOL WindowsApplication::ProcessEvent()
{
	if (PeekMessage(&m_msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
		DispatchMessage(&m_msg);
	}
	if (m_msg.message != WM_QUIT){
		return FALSE;
	}
	return TRUE;
}

/**
* @brief ���
*/
VOID WindowsApplication::Release()
{
	CloseDebugWindow();
}


// �f�o�b�O�E�B���h�E�p
static FILE* DebugFP = NULL;

/**
* @brief �f�o�b�O�p�E�B���h�E���J��
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
* @brief �f�o�b�O�p�E�B���h�E�����
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