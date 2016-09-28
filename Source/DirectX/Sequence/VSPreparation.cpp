// ----------------------------------------------------------------
//
//	�o�g���J�n�O�̉��o���
//
// ----------------------------------------------------------------

#include "VSPreparation.h"
#include "GameMain.h"
#include "SequenceChanger.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\UniqueData.h"

/**
* @brief �쐬
*/
void VSPreparation::Create()
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �I���L�����N�^�[�̏����擾
	const int* select = UniqueData::GetInstance()->GetSelectCharacter();

	for (int i = 0; i < JOY_MAX; i++)
	{
		switch (select[i])
		{
		case LILIA:
			m_obj[i].handle = m_texData->GetTexture(TEX_LILIA_CUTIN_00);
			m_nameObj[i].handle = m_texData->GetTexture(TEX_LILIA_FONT);
			break;

		case RUNA:
			m_obj[i].handle = m_texData->GetTexture(TEX_RUNA_CUTIN_00);
			m_nameObj[i].handle = m_texData->GetTexture(TEX_RUNA_FONT);
			break;
		}
	}
}

/**
* @brief ������
*/
void VSPreparation::Initialize()
{
	vsScale_ = 0.0f;
	
	m_obj[PLAYER1].pos.x = -600.0f;
	m_obj[PLAYER2].pos.x = 1880.0f;
	m_plFontObj[PLAYER1].pos.x = -300.0f;
	m_plFontObj[PLAYER2].pos.x = 1580.0f;
	m_nameObj[PLAYER1].pos.x = -300.0f;
	m_nameObj[PLAYER2].pos.x = 1580.0f;
	m_nameObj[PLAYER1].rot = -20.0f;
	m_nameObj[PLAYER2].rot = 20.0f;

	for (int i = 0; i < JOY_MAX; i++){
		m_obj[i].scale = 1.4f;
		m_v[i] = 0.0f;
		
		m_plFontObj[i].pos.y = 650.0f;
		m_plFontvx[i] = 0.0f;

		m_nameObj[i].pos.y = 700.0f;
		m_namevx[i] = 0.0f;
		m_namevy[i] = 0.0f;
	}
	m_alpha = ALPHA_MIN;

	fontY = 760.0f;

	m_frame = 0;
	m_subWork = 0;
}

/**
* @brief �X�V
*/
void VSPreparation::Update()
{
	switch (m_subWork)
	{
	case 0: // 1P���E�ɓ�����
		m_v[PLAYER1] = 30.0f;
		SoundPlayer::GetInstance()->Play(CHEER2_SE);
		m_subWork++;

		break;

	case 1: 
		if (m_frame >= 100)
		{
			SoundPlayer::GetInstance()->Play(CHEER2_SE);
			m_v[PLAYER1] = 0.0f;
			m_obj[PLAYER1].pos = -600.0f;
			m_frame = 0;
			m_subWork++;
		}
		break;

	case 2: // 2P�����ɓ�����
		m_v[PLAYER2] = -30.0f;

		if (m_frame >= 100)
		{
			m_v[PLAYER1] = -10.0f;
			m_obj[PLAYER1].pos.x = 600.0f;

			m_v[PLAYER2] = 10.0f;
			m_obj[PLAYER2].pos.x = 680.0f;

			m_obj[PLAYER1].scale = 0.9f;
			m_obj[PLAYER2].scale = 0.9f;

			m_plFontvx[PLAYER1] = 14.0f;
			m_plFontvx[PLAYER2] = -14.0f;

			m_namevx[PLAYER1] = 17.0f;
			m_namevx[PLAYER2] = -17.0f;

			m_namevy[PLAYER1] = -7.0f;
			m_namevy[PLAYER2] = -7.0f;

			m_subWork++;
		}
		break;

	case 3: // �������獶�E�ɓ�����
		m_alpha += 7;
		if (m_alpha >= 200)
		{
			for (int i = 0; i < JOY_MAX; i++){
				m_namevx[i] = m_namevx[i] * 0.65f;
				m_namevy[i] = m_namevy[i] * 0.65f;
			}
		}

		if (m_alpha > ALPHA_MAX)
		{
			for (int i = 0; i < JOY_MAX; i++){
				m_v[i] = 0.0f;
				m_plFontvx[i] = 0.0f;
				m_namevx[i] = 0.0f;
				m_namevy[i] = 0.0f;
			}

			vsScale_ = 4.0f;
			SoundPlayer::GetInstance()->Play(VERSUS_SE);
			m_frame = 0;
			m_subWork++;
		}
		break;

	case 4:
		vsScale_ -= 0.06f;
		if (vsScale_ <= 0.8f){
			SoundPlayer::GetInstance()->Play(VSSWITCH_SE);
			m_frame = 0;
			m_subWork++;
		}
		break;

	case 5:
		if (m_frame >= 240)
		{
			// �t�F�[�h�̐ݒ�
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);
			m_subWork++;
		}
		break;

	case 6:
		// �t�F�[�h�I���҂�
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			// ���C���Q�[���ɐ؂�ւ���
			SequenceChanger::GetInstance()->ChangeScene(new GameMain());
			m_subWork = 0;
		}
		break;
	
	}

	// �w�i�t�H���g�̍X�V
	UpdateBackgroundFont();

	for (int i = 0; i < JOY_MAX; i++){
		m_obj[i].pos.x += m_v[i];
		m_plFontObj[i].pos.x += m_plFontvx[i];
		m_nameObj[i].pos.x += m_namevx[i];
		m_nameObj[i].pos.y += m_namevy[i];
	}

	// �t���[���X�V
	m_frame++;
}

/**
* @brief �`��
*/
void VSPreparation::Render()
{
	// �I�����ꂽ�L�����N�^�[�f�[�^���擾����
	const int* select = UniqueData::GetInstance()->GetSelectCharacter();

	// �w�i
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VSPREPARATION_BG), 640, 360);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VSPREPARATION_BG2), 640, fontY);
	
	// �L�����\��
	for (int i = 0; i < JOY_MAX; i++){
		m_2dTex->DrawTexture(m_obj[select[i]].handle, m_obj[i].pos.x, 600.0f, 0.0f, m_obj[i].scale, m_alpha);
		m_2dTex->DrawTexture(m_nameObj[select[i]].handle, m_nameObj[i].pos.x, m_nameObj[i].pos.y, m_nameObj[i].rot);

		if (i == PLAYER1){
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PLAYER1_FONT), m_plFontObj[i].pos.x, m_plFontObj[i].pos.y, 0.0f, 0.3f);
		}
		else{
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PLAYER2_FONT), m_plFontObj[i].pos.x, m_plFontObj[i].pos.y, 0.0f, 0.3f);
		}
	}

	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VS_FONT), 640, 360, 0.0f, vsScale_);
}

/**
* @brief �w�i�����̍X�V
*/
void VSPreparation::UpdateBackgroundFont()
{
	fontY -= 1.7f;
	if (fontY <= -400.0f){
		fontY = 760.0f;
	}
}


/**
* @brief �I��
*/
void VSPreparation::Finalize()
{
	// �������Ȃ�
}
