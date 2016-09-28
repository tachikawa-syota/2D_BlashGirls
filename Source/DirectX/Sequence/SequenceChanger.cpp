#include "SequenceChanger.h"
#include "..\Common\ScreanEffect.h"

/**
* @brief ������
*/
void SequenceChanger::Initialize()
{
	m_nowScene = nullptr;
}

/**
* @brief �V�[���̐؂�ւ�
* @param �؂�ւ������V�[��������
*/
void SequenceChanger::ChangeScene(ISequence* next)
{
	// ���݂̃V�[���̏I������
	if (m_nowScene != nullptr){
		m_nowScene->Finalize();
	}

	// �V�[���̐؂�ւ�
	m_nowScene = next;
	
	// �t�F�[�h�Z�b�g
	ScreenEffect::GetInstance()->SetFade(Fade::In, FadeColor::Black, FADE_FRAME);

	// �V�[���̍쐬
	m_nowScene->Create();

	// �V�[���̏�����
	m_nowScene->Initialize();
}

/**
* @brief ���݂̃V�[���̎擾
*/
ISequence* SequenceChanger::GetNowScene()
{
	return m_nowScene;
}