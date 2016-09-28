#include "Result.h"
#include "GameMain.h"
#include "Title.h"
#include "SequenceChanger.h"
#include "..\Common\UniqueData.h"
#include "..\DirectX\SoundPlayer.h"

/**
* @brief �쐬
*/
void Result::Create()
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �I���L�����N�^�[�f�[�^���擾
	m_select = UniqueData::GetInstance()->GetSelectCharacter();
	// �s�k�����v���C���[�ԍ����擾
	m_losePl = UniqueData::GetInstance()->GetLosePlayer();

	// 2P�ΐ탂�[�h
	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Vs2P){
		// �f�o�C�X��ڑ�����Ă��鐔�����擾����
		for (int i = 0; i < JOY_MAX; i++){
			m_dev.emplace_back(new InputMask(i));
		}
		// �J�[�\���𑀍�ł���v���C���[�ԍ���ݒ肷��
		m_controlPlayer = m_losePl;
	}

	// CPU�ΐ탂�[�h
	else if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU){
		m_dev.emplace_back(new InputMask(PLAYER1));
		// CPU�ΐ�̏ꍇ1P���K���J�[�\���𑀍�ł���
		m_controlPlayer = PLAYER1;
	}

	// �e�N�X�`�����R�s�[
	m_loserPlayerTex[PLAYER1] = m_texData->GetTexture(TEX_PLAYER1_FONT);
	m_loserPlayerTex[PLAYER2] = m_texData->GetTexture(TEX_PLAYER2_FONT);

	m_loserCharaTex_[LILIA] = m_texData->GetTexture(TEX_LILIA_CUTIN_01);
	m_loserCharaTex_[RUNA] = m_texData->GetTexture(TEX_RUNA_CUTIN_01);
}

/**
* @brief ������
*/
void Result::Initialize()
{
	m_alpha = ALPHA_MAX;
	m_frame = 0;
	m_subWork = 0;
	m_cursolWork = 0;
	m_cursolY = 355.0f;

	// BGM���Đ�����
	SoundPlayer::GetInstance()->LoopPlay(RESULT_BGM);
	// �{�C�X���Đ�����
	switch (m_select[m_losePl])
	{
	case LILIA:
		SoundPlayer::GetInstance()->Play(LILIA_GASP_VOICE2);
		break;

	case RUNA:
		SoundPlayer::GetInstance()->Play(RUNA_GASP_VOICE2);
		break;
	}
}

/**
* @brief �X�V
*/
void Result::Update()
{
	// ���̓f�o�C�X�̍X�V
	m_dev[m_controlPlayer]->GetInput();

	switch (m_subWork)
	{
	case 0:
		// �t�F�[�h���|�����Ă��Ȃ�������
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			m_subWork++;
		}
		break;

	case 1:
		// ���t���[���𒴂����玟�̋����Ɉڂ�
		if (m_frame >= 60)
		{
			m_subWork++;
			m_alpha = 170;
		}
		// �t���[�������Z����
		m_frame++;
		break;

	case 2:
		// �J�[�\���̓���
		CursolMove();
		break;
	}	
}

/**
* @brief �`��
*/
void Result::Render()
{
	// �w�i
	// �L�����N�^�[�I����ʂƓ����w�i���g��(�g���܂킵)
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CHARASELECT_BG), 640.0f, 360.0f, 0.0f, 1.0f, m_alpha);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LOSE_FONT), 800.0f, 200.0f, 0.0f, 1.5f, m_alpha);
	m_2dTex->DrawTexture(m_loserCharaTex_[m_select[m_losePl]], 200.0f, 640.0f, 0.0f, 1.0f, m_alpha);
	m_2dTex->DrawTexture(m_loserPlayerTex[m_losePl], 900.0f, 400.0f, 0.0f, 0.3f, m_alpha);

	if(m_subWork == 2){
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CONTINUE_FRAME), 640.0f, 500.0f);	// �g
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CONTINUE_CURSOL), 640.0f, m_cursolY);	// �J�[�\��
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CONTINUE_FONT), 640.0f, 500.0f);	// ����

	}
}

/**
* @brief �J�[�\���̈ړ�
*/
void Result::CursolMove()
{
	if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_DOWN))
	{
		m_cursolWork++;
		SoundPlayer::GetInstance()->Play(CURSOL_SE);
		if (m_cursolWork > 1)
			m_cursolWork = 0;
	}
	if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_UP))
	{
		m_cursolWork--;
		SoundPlayer::GetInstance()->Play(CURSOL_SE);
		if (m_cursolWork < 0)
			m_cursolWork = 1;
	}

	switch (m_cursolWork)
	{
	case 0:
		// �X�e�B�b�N���|���ꂽ��J�[�\���𓮂���
		m_cursolY = 355.0f;
		// �L�[���͂��m�F������
		if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_01))
		{
			SoundPlayer::GetInstance()->Play(DECISION_SE);
			SequenceChanger::GetInstance()->ChangeScene(new GameMain());
		}
		break;

	case 1:
		// �X�e�B�b�N���|���ꂽ��J�[�\���𓮂���
		m_cursolY = 500.0f;
		// �L�[���͂��m�F������
		if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_01))
		{
			SoundPlayer::GetInstance()->Play(DECISION_SE);
			SequenceChanger::GetInstance()->ChangeScene(new Title());
		}
		break;
	}
}

/**
* @brief �I��
*/
void Result::Finalize()
{
	// �T�E���h�̒�~
	SoundPlayer::GetInstance()->Stop(RESULT_BGM);
}