#include "SingletonOwner.h"

SingletonOwner::SingletonOwner()
{
}

SingletonOwner::~SingletonOwner()
{
}

/**
* @brief ������
*/
bool SingletonOwner::Initialize()
{
	// ���̓f�o�C�X�̏������ƍ쐬�Ɛݒ�
	m_deviceManager = DeviceManager::GetInstance();
	if (FAILED(m_deviceManager->Initialize())){
		return false;
	}
	if (FAILED(m_deviceManager->SetUp())){
		return false;
	}
	
	// �O���t�B�b�N�X�̏�����
	m_graphicsManager = GraphicsManager::GetInstance();
	if (FAILED(m_graphicsManager->Initialize())){
		return false;
	}

	// �T�E���h�̏�����
	m_soundPlayer = SoundPlayer::GetInstance();
	if (FAILED(m_soundPlayer->Initialize())){
		return false;
	}

	// �e�N�X�`���̓ǂݍ��݂��ꊇ�ōs��
	m_textureData = TextureData::GetInstance();
	if (FAILED(m_textureData->LoadTexture())){
		return false;
	}

	// �V�[���؂�ւ��̏�����
	m_sequenceChanger = SequenceChanger::GetInstance();
	m_sequenceChanger->Initialize();

	// �X�N���[���G�t�F�N�g�̏�����
	m_screenEffect = ScreenEffect::GetInstance();
	m_screenEffect->Initialize();

	return true;
}