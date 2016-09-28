#include "Title.h"
#include "CharaSelect.h"
#include "SequenceChanger.h"
#include "..\Common\ParamLoader.h"
#include "..\Common\UniqueData.h"
#include "..\DirectX\SoundPlayer.h"

/**
* @brief �쐬
*/
void Title::Create()
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// 1P�R���g���[���[�̂ݐ�������
	m_dev.emplace_back(new InputMask(0));
}

/**
* @brief ������
*/
void Title::Initialize()
{	
	cursolY = 510.0f;
	// �Q�[�����[�h�����������Ă���
	UniqueData::GetInstance()->SetGameMode(GameMode::Default);
	titleWork = 0;
	m_subWork = 0;
	m_lightAlpha = ALPHA_MAX;
	m_lightAngle = 0.0f;
	m_alpha = ALPHA_MAX;
	m_isAlphaPlus = false;
	m_waitFrame = 0;

	// BGM�̍Đ�
	SoundPlayer::GetInstance()->LoopPlay(TITLE_BGM);
}

/**
* @brief �X�V
*/
void Title::Update()
{
	// ���G�t�F�N�g�̍X�V
	UpdateLight();

	switch (m_subWork)
	{
	case 0: // �t�F�[�h�I���܂ő҂�
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			m_subWork++;
		}
		break;

	case 1: // �A���t�@�l�ύX
		m_alpha = 130;
		m_subWork++;
		break;

	case 2:
	{
		GameMode ret = TitleWork();

		if (ret == GameMode::Vs2P)
			m_subWork = 4;
		else if (ret == GameMode::VsCPU)
			m_subWork = 5;
		else if (ret == GameMode::Exit)
			m_subWork = 6;
		break;
	}

	case 4:
		// �ΐl���[�h
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// �v���C���[ VS �v���C���[
			UniqueData::GetInstance()->SetGameMode(GameMode::Vs2P);
			UniqueData::GetInstance()->SetPlayerCount(2, 0);
			SequenceChanger::GetInstance()->ChangeScene(new CharaSelect());
		}
		break;

	case 5:
		// �΂b�o�t���[�h
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// �v���C���[ VS �R���s���[�^�[
			UniqueData::GetInstance()->SetGameMode(GameMode::VsCPU);
			UniqueData::GetInstance()->SetPlayerCount(1, 1);
			SequenceChanger::GetInstance()->ChangeScene(new CharaSelect());
		}
		break;

	case 6: // �t�F�[�h�I���܂ő҂�
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// �A�v���P�[�V�����I��
			exit(1);
		}
		break;
	}

	// �t���[�����Z
	m_frame++;
}


/**
* @brief �^�C�g���X�V
*/
GameMode Title::TitleWork()
{
	// �L�[�����擾
	m_dev[0]->GetInput();

	// ���ړ�
	if (m_dev[0]->CheckInputMask(INPUT_DOWN)){
		titleWork++;
	}
	// ��ړ�
	if (m_dev[0]->CheckInputMask(INPUT_UP)){
		titleWork--;
	}

	if (titleWork == 0)
	{
		cursolY = 410.0f;
	}
	else if (titleWork == 1)
	{
		cursolY = 510.0f;
	}
	else if (titleWork == 2)
	{
		cursolY = 610.0f;
	}


	if (titleWork < 0)
	{		
		titleWork = 0;
	}
	if (titleWork > 2)
	{
		titleWork = 2;
	}

	m_waitFrame++;

	// �L�[�����͂��ꂽ��
	if (m_dev[0]->CheckInputMask(INPUT_01))
	{
		// �t�F�[�h��������
		ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);
		// ���ʉ��̍Đ�
		SoundPlayer::GetInstance()->Play(DECISION_SE);
		
		switch (titleWork)
		{
		case 0:
			return GameMode::Vs2P;

		case 1:
			return GameMode::VsCPU;

		case 2:
			return GameMode::Exit;
		}
	}

	return GameMode::Default;
}

void Title::UpdateLight()
{
	if (m_lightAlpha > ALPHA_MAX)
		m_isAlphaPlus = false;
	else if (m_lightAlpha < 0)
		m_isAlphaPlus = true;

	if (m_isAlphaPlus)
		m_lightAlpha += 10;
	else m_lightAlpha -= 10;

	m_lightAngle += 2.0f;
}

/**
* @brief �`��
*/
void Title::Render()
{
	// �w�i
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_TITLE_BG), 640.0f, 360.0f, 0.0f, 1.0f, m_alpha);
	// ���S
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_TITLE_LOGO), 640.0f, 400.0f, 0.0f, 0.5f, m_alpha);

	// ���G�t�F�N�g
	if (m_subWork > 0){
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT), 300.0f, 370.0f, m_lightAngle, 0.5f, m_lightAlpha, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT), 800.0f, 370.0f, m_lightAngle + 30.0f, 0.5f, m_lightAlpha, true);
	}

	if (m_subWork == 2)
	{
		// ���j���[�t�H���g
		m_2dTex->DrawTexture(m_texData->GetTitleMenuTexture(1), 640.0f, 400.0f, 0.0f, 1.0f, ALPHA_MAX, true);
		m_2dTex->DrawTexture(m_texData->GetTitleMenuTexture(2), 640.0f, 500.0f, 0.0f, 1.0f, ALPHA_MAX, true);
		m_2dTex->DrawTexture(m_texData->GetTitleMenuTexture(11), 640.0f, 600.0f, 0.0f, 1.0f, ALPHA_MAX, true);
		// �J�[�\���A�C�R��
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_TITLE_ICON), 430.0f, cursolY);
	}
}

/**
* @brief �I��
*/
void Title::Finalize()
{
	// �T�E���h�̒�~
	SoundPlayer::GetInstance()->Stop(TITLE_BGM);
}