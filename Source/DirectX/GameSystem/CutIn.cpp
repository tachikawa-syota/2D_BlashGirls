#include "CutIn.h"
#include "Camera.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\ParamLoader.h"
#include "..\Common\Utility.h"

/**
* @brief �R���X�g���N�^
* @param name - �L�����N�^�[�̖��O
* @param index - �L�����N�^�[�̔ԍ�
*/
CutIn::CutIn(int name, int index)
{
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	m_index = index;

	switch (name)
	{
		// �����A
	case CharaName::LILIA:
		m_obj.handle = m_texData->GetTexture(TEX_LILIA_CUTIN_00);
		break;
		// ���i
	case CharaName::RUNA:
		m_obj.handle = m_texData->GetTexture(TEX_RUNA_CUTIN_00);
		break;
		// ���蓾�Ȃ�(�G���[)
	default:
		Utility::abortWithMsg("�J�b�g�C���̍쐬�Ɏ��s���܂���");
		break;
	}
	// �w�i
	m_backTex = m_texData->GetTexture(TEX_VSPREPARATION_BG);

	// ���x������
	m_v = Vector2(GetPrm->InitCutinV, GetPrm->InitCutinV);


	if (m_index == PLAYER1){
		m_obj.pos.x = GetPrm->InitCutinPlayer1X;
		m_obj.pos.y = GetPrm->InitCutinY;
	}
	else if (m_index == PLAYER2){
		m_obj.pos.x = GetPrm->InitCutinPlayer2X;
		m_obj.pos.y = GetPrm->InitCutinY;
	}

	SoundPlayer::GetInstance()->Play(CUTIN_SE);

	m_inertia = 0.0f;
}

/**
* @brief �f�X�g���N�^
*/
CutIn::~CutIn()
{

}

/**
* @brief �X�V
*/
void CutIn::Update()
{
	if (m_index == PLAYER1)
	{
		if (m_obj.pos.x >= GetPrm->CutinPlayer1X)
		{
			m_obj.pos.x = GetPrm->InitCutinPlayer1X;
		}
	}
	else if (m_index == PLAYER2)
	{
		if (m_obj.pos.x <= GetPrm->CutinPlayer2X)
		{
			m_obj.pos.x = GetPrm->InitCutinPlayer2X;
		}
	}

	if (m_obj.pos.y <= GetPrm->CutinY)
	{
		m_obj.pos.y = GetPrm->InitCutinY;
	}

	m_v -= Vector2(m_inertia, m_inertia);

	if (m_v.x <= 0.01f)
	{
		m_v.x = 0.01f;
	}
	if (m_v.y <= 0.01f)
	{
		m_v.y = 0.01f;
	}
	if (m_index == PLAYER1) m_obj.pos.x += m_v.x;
	if (m_index == PLAYER2) m_obj.pos.x -= m_v.x;

	m_obj.pos.y -= m_v.y;
}

/**
* @brief �`��
*/
void CutIn::Render()
{
	m_2dTex->DrawTexture(m_backTex, 640.0f, 360.0f);
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x, m_obj.pos.y, 0.0f, 0.9f);
}
