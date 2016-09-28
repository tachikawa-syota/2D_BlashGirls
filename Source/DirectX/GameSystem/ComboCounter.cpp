#include "ComboCounter.h"
#include "..\Common\ParamLoader.h"

/**
* @brief 初期化
*/
void ComboCounter::Initialize()
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// 座標の設定
	hitTexX[PLAYER1] = GetPrm->HitFontPlayer1X;
	hitTexX[PLAYER2] = GetPrm->HitFontPlayer2X;
	numberTexX[PLAYER1] = GetPrm->NumberFontPlayer1X;
	numberTexX[PLAYER2] = GetPrm->NumberFontPlayer2X;

	// 数字テクスチャのコピー
	for (int i = 0; i < NUMBER_MAX; i++){
		numberTex[i] = m_texData->GetNumberTexture(i);
	}

	// パラメータの初期化
	for (int i = 0; i < JOY_MAX; i++)
	{
		comboFrame[i] = 0;
		comboCount[i] = 0;
		comboCountOld[i] = 0;
		comboOnesPlace[i] = 0;
		comboTensPlace[i] = 0;
		comboHundredsPlace[i] = 0;
		correctionCoefficient[i] = 1.0f;
	}
}

/**
* @brief 更新
*/
void ComboCounter::Update()
{		
	for (int i = 0; i < JOY_MAX; i++)
	{
		// 前フレームと現在のフレームでコンボ数が同じなら
		if (comboCountOld[i] == comboCount[i]){
			// コンボフレームを加算
			comboFrame[i]++;
		}
		else{
			// それ以外なら0初期化
			comboFrame[i] = 0;
		}

		// コンボフレームが60フレームを越えた瞬間初期化する
		if (comboFrame[i] >= GetPrm->ComboFrameLimit)
		{
			comboCount[i] = 0;
			comboOnesPlace[i] = 0;
			comboTensPlace[i] = 0;
			comboHundredsPlace[i] = 0;
			correctionCoefficient[i] = 1.0f;
		}

		// 1の位が9を超えたら10の位を足す
		if (comboOnesPlace[i] > 9)
		{
			comboOnesPlace[i] = 0;
			comboTensPlace[i]++;
		}
		// 10の位が9を超えたら100の位を足す
		if (comboTensPlace[i] > 9)
		{
			comboTensPlace[i] = 0;
			comboHundredsPlace[i]++;
		}

		// コンボ最大数は999
		if (comboOnesPlace[i] == 9 && comboTensPlace[i] == 9 && comboHundredsPlace[i] == 9)
		{
			comboOnesPlace[i] = 9;
			comboTensPlace[i] = 9;
			comboHundredsPlace[i] = 9;
		}

		// コンボ数が5を超えたら
		if (comboCount[i] > 5)
		{
			// ダメージ補正がかかる
			correctionCoefficient[i] -= GetPrm->ComboCorrectionCoefficient;
		}

		// 補正値は半分より下がらない
		if (correctionCoefficient[i] < GetPrm->ComboCorrectionCoefficientLimit)
			correctionCoefficient[i] = GetPrm->ComboCorrectionCoefficientLimit;
	
		// 現在のコンボ数を記録する
		comboCountOld[i] = comboCount[i];
	}
}

/**
* @brief コンボ数を描画する
*/
void ComboCounter::Render()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		// コンボ数が１以上だったら
		if (comboCount[i] > 0)
		{
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_HITS_FONT), hitTexX[i], 200.0f, 0.0f, 1.1f);
			m_2dTex->DrawTexture(numberTex[comboOnesPlace[i]], numberTexX[i], 200.0f);
			
			// 10の位が0以上または100の位が0以上なら表示する
			if (comboTensPlace[i] > 0 || comboHundredsPlace[i] > 0)
				m_2dTex->DrawTexture(numberTex[comboTensPlace[i]], numberTexX[i] - 60.0f, 200.0f);

			// 100の位に数字が入ったら
			if (comboHundredsPlace[i] > 0)
				m_2dTex->DrawTexture(numberTex[comboHundredsPlace[i]], numberTexX[i] - 120, 200.0f);
		}
	}
}

/**
* @brief コンボ数を加算
* @param plNum - プレイヤー番号
*/
void ComboCounter::Add(int plNum)
{
	comboCount[plNum]++;
	comboOnesPlace[plNum]++;
}

/**
* @brief コンボ数によるダメージ補正された値を返す
* @param damage - 通常時のダメージを取得
* @param plNum - プレイヤー番号
*/
float ComboCounter::ComboDamageCorrection(float damage, int plNum)
{
	float value;

	value = damage * correctionCoefficient[plNum];

	return value;
}

/**
* @brief Player1のコンボ数を取得
* @param index - プレイヤー番号
*/
int ComboCounter::GetComboCount(int index)
{
	return 	comboCount[index];
}