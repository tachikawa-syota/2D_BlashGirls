#include "Direct3DSystem.h"

/**
* @brief �R���X�g���N�^
*/
Direct3DSystem::Direct3DSystem()
{
	m_pD3d = nullptr;
	m_pDevice = nullptr;
}

/**
* @brief �f�X�g���N�^
*/
Direct3DSystem::~Direct3DSystem()
{
	Release();
}

/**
* @brief �쐬
* @param �E�B���h�E�n���h��
*/
HRESULT Direct3DSystem::Create(HWND hWnd)
{
	// �uDirect3D�v�I�u�W�F�N�g�̍쐬
	if (nullptr == (m_pD3d = Direct3DCreate9(D3D_SDK_VERSION))){
		MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
		return E_FAIL;
	}

	// �f�o�C�X�p�����[�^���쐬
	if (!CreateParam()) return E_FAIL;

	// �f�o�C�X�̍쐬
	if (!CreateDevice(hWnd)) return E_FAIL;

	// �f�o�C�X���Z�b�g
	D3DIns->SetDevice(m_pDevice);

	// ����
	return S_OK;
}

/**
* @brief �f�o�C�X�p�����[�^�̍쐬
*/
BOOL Direct3DSystem::CreateParam()
{
	D3DDISPLAYMODE d3dmode;
	// ���݂̃f�B�X�v���C���[�h�𓾂�iDEFAULT�w��Ńv���C�}���A�_�v�^��I���j
	if (FAILED(m_pD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmode))) {
		return FALSE;
	}

	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	if (AppIns->GetWindowed()) {
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@�t�H�[�}�b�g�w�� D3DFMT_UNKNOWN�Ō��݂̃f�B�X�v���C���[�h�w��
		m_d3dpp.BackBufferCount = 1;								// �o�b�N�o�b�t�@��
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �o�b�N�o�b�t�@�؂�ւ�����̎w��
		m_d3dpp.Windowed = TRUE;									// �E�B���h�E���[�h���ۂ�
		m_d3dpp.EnableAutoDepthStencil = TRUE;						// Z(�[�x)�o�b�t�@�A�X�e���V���o�b�t�@�̗L����
#ifdef ���ʓ��e�@
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				// Z�o�b�t�@�A�X�e���V���o�b�t�@�̃t�H�[�}�b�g�w��
#else
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// Z�o�b�t�@�A�X�e���V���o�b�t�@�̃t�H�[�}�b�g�w��
		m_d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// �_�u���X�e���V��
#endif
	}
	else {
		m_d3dpp.BackBufferWidth = 1280;								// �𑜓x�Z�b�g
		m_d3dpp.BackBufferHeight = 720;
		m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;					// �s�N�Z���t�H�[�}�b�g���w��
		m_d3dpp.Windowed = FALSE;									// �t���X�N���[��
		m_d3dpp.BackBufferCount = 1;
		m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_d3dpp.EnableAutoDepthStencil = TRUE;						// Z(�[�x)�o�b�t�@�A�X�e���V���o�b�t�@�̗L����
#ifdef ���ʓ��e�@
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				//Z�o�b�t�@�A�X�e���V���o�b�t�@�̃t�H�[�}�b�g�w��
#else
		m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// Z�o�b�t�@�A�X�e���V���o�b�t�@�̃t�H�[�}�b�g�w��
		m_d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// �_�u���X�e���V��
#endif
	}

	return TRUE;
}

/**
* @brief �f�o�C�X�̍쐬
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
			MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);
			if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&m_d3dpp, &m_pDevice)))
			{
				if (FAILED(m_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&m_d3dpp, &m_pDevice)))
				{
					MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
					// ���s
					return FALSE;
				}
			}
		}
	}

	// ����
	return TRUE;
}

/**
* @brief ���
*/
VOID Direct3DSystem::Release()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pD3d);
}