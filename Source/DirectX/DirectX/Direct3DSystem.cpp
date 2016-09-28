#include "Direct3DSystem.h"

/**
* @brief コンストラクタ
*/
Direct3DSystem::Direct3DSystem()
{
	m_pD3d = nullptr;
	m_pDevice = nullptr;
}

/**
* @brief デストラクタ
*/
Direct3DSystem::~Direct3DSystem()
{
	Release();
}

/**
* @brief 作成
* @param ウィンドウハンドル
*/
HRESULT Direct3DSystem::Create(HWND hWnd)
{
	// 「Direct3D」オブジェクトの作成
	if (nullptr == (m_pD3d = Direct3DCreate9(D3D_SDK_VERSION))){
		MessageBox(0, "Direct3Dの作成に失敗しました", "", MB_OK);
		return E_FAIL;
	}

	// デバイスパラメータを作成
	if (!CreateParam()) return E_FAIL;

	// デバイスの作成
	if (!CreateDevice(hWnd)) return E_FAIL;

	// デバイスをセット
	D3DIns->SetDevice(m_pDevice);

	// 成功
	return S_OK;
}

/**
* @brief デバイスパラメータの作成
*/
BOOL Direct3DSystem::CreateParam()
{
	D3DDISPLAYMODE d3dmode;
	// 現在のディスプレイモードを得る（DEFAULT指定でプライマリアダプタを選択）
	if (FAILED(m_pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmode))) {
		return FALSE;
	}

	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	if (AppIns->GetWindowed()) {
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファフォーマット指定 D3DFMT_UNKNOWNで現在のディスプレイモード指定
		m_d3dpp.BackBufferCount = 1;								// バックバッファ数
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// バックバッファ切り替え動作の指定
		m_d3dpp.Windowed = TRUE;									// ウィンドウモードか否か
		m_d3dpp.EnableAutoDepthStencil = TRUE;						// Z(深度)バッファ、ステンシルバッファの有効化
#ifdef 平面投影法
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// Zバッファ、ステンシルバッファのフォーマット指定
#else
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// Zバッファ、ステンシルバッファのフォーマット指定
		m_d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// ダブルステンシル
#endif
	}
	else {
		m_d3dpp.BackBufferWidth = 1280;								// 解像度セット
		m_d3dpp.BackBufferHeight = 720;
		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;					// ピクセルフォーマットを指定
		m_d3dpp.Windowed = FALSE;									// フルスクリーン
		m_d3dpp.BackBufferCount = 1;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_d3dpp.EnableAutoDepthStencil = TRUE;						// Z(深度)バッファ、ステンシルバッファの有効化
#ifdef 平面投影法
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				//Zバッファ、ステンシルバッファのフォーマット指定
#else
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// Zバッファ、ステンシルバッファのフォーマット指定
		m_d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// ダブルステンシル
#endif
	}

	return TRUE;
}

/**
* @brief デバイスの作成
*/
BOOL Direct3DSystem::CreateDevice(HWND hWnd)
{
	if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_d3dpp, &m_pDevice)))
	{
		if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp, &m_pDevice)))
		{
			MessageBox(0, "HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します", NULL, MB_OK);
			if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&m_d3dpp, &m_pDevice)))
			{
				if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&m_d3dpp, &m_pDevice)))
				{
					MessageBox(0, "DIRECT3Dデバイスの作成に失敗しました", NULL, MB_OK);
					// 失敗
					return FALSE;
				}
			}
		}
	}

	// 成功
	return TRUE;
}

/**
* @brief 解放
*/
VOID Direct3DSystem::Release()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pD3d);
}