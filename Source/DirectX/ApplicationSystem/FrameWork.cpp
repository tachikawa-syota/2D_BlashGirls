#include "Framework.h"
#include "..\Sequence\Title.h"
#include "..\Sequence\SequenceChanger.h"


/**
* @brief �R���X�g���N�^
*/
FrameWork::FrameWork()
{
	// ���P�[���̐ݒ�
	setlocale(LC_ALL, "Japanese_Japan.932");

	// srand�֐��ŁA�����p�^�[��������������
	srand((unsigned)time(NULL));

	// �������[���[�N���o
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

/**
* @brief �f�X�g���N�^
*/
FrameWork::~FrameWork()
{
	m_nowScene = nullptr;
}

/**
* @brief �쐬
* @param �C���X�^���X
* @return true - �����Ffalse - ���s
*/
bool FrameWork::Create(HINSTANCE hInst)
{
	// 2�d�N���h�~
	HANDLE hMutex = CreateMutex(NULL, TRUE, APPLICATION_NAME);
	if (hMutex == NULL) {
		return false;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		MessageBox(NULL, "���ɋN������Ă��܂��B", "error", MB_OK | MB_ICONERROR);
		return false;
	}

	// �C���X�^���X�𐶐�
	pSys = make_unique<WindowsApplication>();
	pD3d = make_unique<Direct3DSystem>();

	// �A�v���P�[�V�������쐬�i���s�����"0"���Ԃ�j
	if FAILED(pSys->Create(hInst)) return false;
	// Direct3D���쐬�i���s�����"0"���Ԃ�j
	if FAILED(pD3d->Create(ApplicationData::GetInstance()->GetWindowHandle())) return false;

	// ���������s��
	Initialize();

	return true;
}

/**
* @brief ������
*/
void FrameWork::Initialize()
{
	m_nowScene = nullptr;

	// �V���O���g�����܂Ƃ߂ď���������
	m_singletonOwner = make_unique<SingletonOwner>();
	m_singletonOwner->Initialize();

	// FPS
	m_fpsCounter = make_unique<FPSCounter>(FPSMode::FPS_60);

	// �t�H���g
	m_font = make_unique<Font>();

	// �T�E���h�f�[�^�𐶐�
	m_soundData = make_unique<SoundData>();

	// �����V�[���̐ݒ�
	SequenceChanger::GetInstance()->ChangeScene(new Title());
}

/**
* @brief �X�V
*/
void FrameWork::Update()
{
	// FPS�̍X�V
	m_fpsCounter->Update();

	// �t�F�[�h�̍X�V
	ScreenEffect::GetInstance()->Update();

	// �V�[���̍X�V
	if (m_nowScene != nullptr) m_nowScene->Update();

	SequenceChanger* seqChanger = SequenceChanger::GetInstance();
	// �V�[�����؂�ւ������
	if (m_nowScene != seqChanger->GetNowScene()){
		m_nowScene = seqChanger->GetNowScene();
	}
}

/**
* @brief �`��
*/
void FrameWork::Render()
{
	// �`��t���O
	if (!m_fpsCounter->IsRender()) return;

	// �V�[���J�n
	HCls();

	// �V�[���`��
	if (m_nowScene != nullptr) m_nowScene->Render();

	// �t�F�[�h�̕`��
	ScreenEffect::GetInstance()->Draw();

	// FPS�̕\��
	RenderFPS();

	// �V�[���I��
	Flip();
}

/**
* @brief �X�V�ƕ`��
*/
void FrameWork::Run()
{
	while (!pSys->ProcessEvent())
	{
		// �X�V
		Update();

		// �`��
		Render();
	}
}

/**
* @brief ��ʃN���A
*/
BOOL FrameWork::HCls()
{
	D3DIns->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	// �����_�����O�J�n
	if (SUCCEEDED(D3DIns->GetDevice()->BeginScene()))
	{
		return TRUE;
	}
	return FALSE;
}

/**
* @brief �t���b�s���O
*/
BOOL FrameWork::Flip()
{
	// �����_�����O�I��
	D3DIns->GetDevice()->EndScene();
	D3DIns->GetDevice()->Present(NULL, NULL, NULL, NULL);

	return TRUE;
}

/**
* @brief FPS�̕\��
*/
VOID FrameWork::RenderFPS()
{
	//	�t���[�����[�g�̕\��
#ifdef _DEBUG
	char	str[64];
	wsprintf(str, "FPS %03d / %03d\n", m_fpsCounter->GetFPS(), m_fpsCounter->GetRenderFPS());
	m_font->DrawFont(str, 10, 10, 200, 20, FONTCOLOR_BLACK);
#endif
}