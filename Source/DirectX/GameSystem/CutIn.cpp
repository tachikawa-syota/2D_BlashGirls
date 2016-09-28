#include "CutIn.h"
#include "Camera.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\ParamLoader.h"
#include "..\Common\Utility.h"

/**
* @brief コンストラクタ
* @param name - キャラクターの名前
* @param index - キャラクターの番号
*/
CutIn::CutIn(int name, int index)
{
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	m_index = index;

	switch (name)
	{
		// リリア
	case CharaName::LILIA:
		m_obj.handle = m_texData->GetTexture(TEX_LILIA_CUTIN_00);
		break;
		// ルナ
	case CharaName::RUNA:
		m_obj.handle = m_texData->GetTexture(TEX_RUNA_CUTIN_00);
		break;
		// あり得ない(エラー)
	default:
		Utility::abortWithMsg("カットインの作成に失敗しました");
		break;
	}
	// 背景
	m_backTex = m_texData->GetTexture(TEX_VSPREPARATION_BG);

	// 速度初期化
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
* @brief デストラクタ
*/
CutIn::~CutIn()
{

}

/**
* @brief 更新
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
* @brief 描画
*/
void CutIn::Render()
{
	m_2dTex->DrawTexture(m_backTex, 640.0f, 360.0f);
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x, m_obj.pos.y, 0.0f, 0.9f);
}
