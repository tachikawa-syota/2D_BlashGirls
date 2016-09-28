#include "UIManager.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\Common\UniqueData.h"

UIManager::UIManager()
{
	// インスタンスを取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// 選択キャラクターのデータを取得
	m_selectChara = UniqueData::GetInstance()->GetSelectCharacter();

	// 数字テクスチャ座標
	m_spGaugeNumberX[PLAYER1] = 258.0f;
	m_spGaugeNumberX[PLAYER2] = 1018.0f;


	// テクスチャのコピー
	m_standCharaBack[0] = m_texData->GetTexture(TEX_STAND_BACK_G);
	m_standCharaBack[1] = m_texData->GetTexture(TEX_STAND_BACK_R);
	m_standCharaBack[2] = m_texData->GetTexture(TEX_STAND_BACK_P);

	m_tex = m_texData->GetD3dTexture(TEX_SHAME_GAUGE);
	m_oldTex = m_texData->GetD3dTexture(TEX_SHAME_GAUGE_OLD);

	for (int i = 0; i < 6; i++){
		m_standLiliaTex[i] = m_texData->GetTexture(TEX_LILIA_STAND_00 + i);
		m_standRunaTex[i] = m_texData->GetTexture(TEX_RUNA_STAND_00 + i);
	}

	// 数字テクスチャ
	for (int i = 0; i < NUMBER_MAX; i++){
		m_numberTex[i] = m_texData->GetRedNumberTexture(i);
	}
}

UIManager::~UIManager()
{

}

void UIManager::Initialize()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		m_displayNumber[i] = NO_BREAK;
		m_breakClothesCount[i] = 0;
		m_isClothesBreak[i] = 0;
		m_standCharaState[i] = 0;
		
	}
}

/**
* @brief 更新
*/
void UIManager::Update(int breakState[], HpGauge hp)
{
	int old[2];
	for (int i = 0; i < JOY_MAX; i++)
	{
		old[i] = m_breakClothesCount[i];

		// 衣服が破れたら
		if (hp.GetHP(i) < GetPrm->HpMax - 200.0f)
		{
			m_displayNumber[i] = BREAK_TORSO;
			m_breakClothesCount[i] = 1;
		}
		// 衣服が破れたら
		if (hp.GetHP(i) < GetPrm->HpMax - 1000.0f)
		{
			m_displayNumber[i] = BREAK_TORSO_AND_OUTERWEAR;
			m_breakClothesCount[i] = 2;
		}
		// 衣服が破れたら
		if (hp.GetHP(i) < GetPrm->HpMax - 1990.0f)
		{
			m_displayNumber[i] = BREAK_TORSO_AND_SKIRT;
			m_breakClothesCount[i] = 3;
		}
		// 衣服が破れたら
		if (hp.GetHP(i) < 100)
		{
			m_displayNumber[i] = ALL_BREAK;
			m_breakClothesCount[i] = 4;
		}

		// 前フレームと破れたカウントが違ったら
		// 破れフラグを立てる
		if (m_breakClothesCount[i] > old[i])
			m_isClothesBreak[i] = true;
		else{
			m_isClothesBreak[i] = false;
		}
	}
}

/**
* @brief 描画
* @param winCount[] - 勝利数
* @param swingAdd[] - 揺らす値
* @param sp - 必殺技ゲージクラス
* @param hp - HPゲージクラス
*/
void UIManager::Render(int winCount[], float swingAdd[], const SpGaugePtr& sp, HpGauge hp)
{
	// HPゲージ -------------------------------------------------------------------------

	// ダメージ被弾用
	m_2dTex->DrawTextureEx(534.0f, 25.0f, 532.0f + (-hp.GetOldHP(PLAYER1) * GAUGE_SIZE_X / hp.GetMaxHp()), 52.0f, m_oldTex);
	m_2dTex->DrawTextureEx(750.0f + (hp.GetOldHP(PLAYER2) * GAUGE_SIZE_X / hp.GetMaxHp()), 25.0f, 750.0f, 52.0f, m_oldTex);

	m_2dTex->DrawTextureEx(534.0f, 25.0f, 532.0f + (-hp.GetHP(PLAYER1) * GAUGE_SIZE_X / hp.GetMaxHp()), 52.0f, m_tex);
	m_2dTex->DrawTextureEx(750.0f + (hp.GetHP(PLAYER2) * GAUGE_SIZE_X / hp.GetMaxHp()), 25.0f, 750.0f, 52.0f, m_tex);

	// ----------------------------------------------------------------------------------

	// 勝利アイコン枠
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_HPFRAME), 640.0f, 78.0f, 0.0f, 0.85f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_WINFLAG), 480.0f, 73.0f, 0.0f, 0.5f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_WINFLAG), 510.0f, 73.0f, 0.0f, 0.5f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_WINFLAG), 770.0f, 73.0f, 0.0f, 0.5f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_WINFLAG), 800.0f, 73.0f, 0.0f, 0.5f);
	m_2dTex->DrawTexture(m_numberTex[8], 640.0f, 50.0f, -90.0f);

	if (winCount[PLAYER1] == 1){
		m_2dTex->DrawTexture((m_texData->GetTexture(TEX_WINICON)), 510.0f, 73.0f, 0.0f, 0.1f);
	}
	else if (winCount[PLAYER1] == 2){
		m_2dTex->DrawTexture((m_texData->GetTexture(TEX_WINICON)), 480.0f, 73.0f, 0.0f, 0.1f);
	}
	if (winCount[PLAYER2] == 1){
		m_2dTex->DrawTexture((m_texData->GetTexture(TEX_WINICON)), 770.0f, 73.0f, 0.0f, 0.1f);
	}
	else if (winCount[PLAYER2] == 2){
		m_2dTex->DrawTexture((m_texData->GetTexture(TEX_WINICON)), 800.0f, 73.0f, 0.0f, 0.1f);
	}

	// 左右立ち絵の背景
	m_2dTex->DrawTexture(m_standCharaBack[m_standCharaState[PLAYER1]], 100.0f + swingAdd[PLAYER1], 360.0f - swingAdd[PLAYER1], 0.0f, 1.0f, 255);
	m_2dTex->DrawTexture(m_standCharaBack[m_standCharaState[PLAYER2]], 1180.0f + swingAdd[PLAYER2], 360.0f - swingAdd[PLAYER2], 0.0f, 1.0f, 255);

	for (int i = 0; i < JOY_MAX; i++)
	{
		switch (m_selectChara[i])
		{
		case LILIA:
			if (i == PLAYER1)
				m_2dTex->DrawTexture(m_standLiliaTex[m_displayNumber[PLAYER1]], 100.0f + swingAdd[PLAYER1], 360.0f - swingAdd[PLAYER1]);
			if (i == PLAYER2)
				m_2dTex->DrawTexture(m_standLiliaTex[m_displayNumber[PLAYER2]], 1180.0f + swingAdd[PLAYER2], 360.0f - swingAdd[PLAYER2]);
			break;

		case RUNA:
			if (i == PLAYER1)
				m_2dTex->DrawTexture(m_standRunaTex[m_displayNumber[PLAYER1]], 100.0f + swingAdd[PLAYER1], 360.0f - swingAdd[PLAYER1]);
			if (i == PLAYER2)
				m_2dTex->DrawTexture(m_standRunaTex[m_displayNumber[PLAYER2]], 1180.0f + swingAdd[PLAYER2], 360.0f - swingAdd[PLAYER2]);
			break;
		}

	}

	// 必殺技ゲージ --------------------------------------------------------------------------------------------

	if (sp->GetGaugeCount(PLAYER1) == 5)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_SPECIAL_GAUGE_BER), 397.0f, 680.0f, 0.0f, 0.85f);
	else if (sp->GetGaugeCount(PLAYER1) > 0)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_SPECIAL_GAUGE_BER), 397.0f, 680.0f, 0.0f, 0.85f, 140);

	if (sp->GetGaugeCount(PLAYER2) == 5)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_SPECIAL_GAUGE_BER), 878.0f, 680.0f, 0.0f, 0.85f);
	else if (sp->GetGaugeCount(PLAYER2) > 0)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_SPECIAL_GAUGE_BER), 878.0f, 680.0f, 0.0f, 0.85f, 140);


	// 1P側
	m_2dTex->DrawTextureEx(280.0f, 670.0f, 280.0f + (sp->GetGauge(PLAYER1) * GetPrm->SpecialGaugeSizeX / GetPrm->MaxSpecialGauge), 670.0f + 40.0f, m_texData->GetD3dTexture(TEX_SPECIAL_GAUGE));

	// 2P側
	m_2dTex->DrawTextureEx(990.0f, 670.0f, 990.0f + (-sp->GetGauge(PLAYER2) * GetPrm->SpecialGaugeSizeX / GetPrm->MaxSpecialGauge), 670.0f + 40.0f, m_texData->GetD3dTexture(TEX_SPECIAL_GAUGE));

	// 枠の表示
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_SPECIAL_GAUGE_FRAME), 640.0f, 470.0f, 0.0f, 0.45f);

	for (int i = 0; i < JOY_MAX; i++){
		m_2dTex->DrawTexture(m_numberTex[sp->GetGaugeCount(i)], m_spGaugeNumberX[i], 665.0f, 0.0f, 0.55f);
	}
	// --------------------------------------------------------------------------------------------------------------
}

/**
* @brief 衣服が破れた
*/
bool UIManager::IsClothesBreak(int index)
{
	return m_isClothesBreak[index];
}