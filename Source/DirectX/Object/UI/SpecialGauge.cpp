#include "SpecialGauge.h"
#include "..\..\Common\ParamLoader.h"

/**
* @brief 初期化
*/
void SpecialGauge::Initialize()
{
	// ゲージテクスチャ
	m_gaugeX[PLAYER1] = 280.0f;
	m_gaugeX[PLAYER2] = 990.0f;

	// 数字テクスチャ座標
	m_texX[PLAYER1] = 258.0f;
	m_texX[PLAYER2] = 1018.0f;

	for (int i = 0; i < JOY_MAX; i++)
	{
		m_gaugeNum[i] = 0;
		m_gauge[i] = 0.0f;
		m_addValue[i] = 0.0f;
		m_gaugeState[i] = SpecialGaugeState::None;
	}
}

/**
* @brief 更新
*/
void SpecialGauge::Update()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		switch (m_gaugeState[i])
		{
		case SpecialGaugeState::None:
		case SpecialGaugeState::Empty:
			// 何もしない
			break;

		case SpecialGaugeState::Add:

			// ゲージを加算する
			m_gauge[i] += m_addValue[i];

			// ゲージ数が一定数を超えたらゲージ本数を加算する
			if (m_gauge[i] > GetPrm->MaxSpecialGauge)
			{
				m_gauge[i] = 0.0f;
				m_gaugeNum[i]++;
			}

			// 5以上にはならない
			if (m_gaugeNum[i] >= 5){
				m_gaugeNum[i] = 5;
				m_gauge[i] = 0.0f;
				m_gaugeState[i] = SpecialGaugeState::Full;
			}

			// 加算し終わったら初期化する
			m_addValue[i] = 0.0f;
			break;

			// 満タン
		case SpecialGaugeState::Full:

			break;

		case SpecialGaugeState::Use:

			switch (m_useKind[i])
			{
			case State::StrongAttack:
				m_gaugeNum[i] -= 1;
				break;

			case State::SpecialAttack:
				m_gaugeNum[i]-= 2;
				break;

			default:
			// 登録されている状態以外では何もしない
				break;
			}

			// 使い終わったら状態をNoneにする
			m_gaugeState[i] = SpecialGaugeState::None;
			break;
		}
	}
}

/**
* @brief ゲージ量の増加
* @param addValue - 増加量
* @param plNum - プレイヤー番号
*/
void SpecialGauge::Add(float addValue, int plNum)
{
	// ゲージを使用中だったら何もしない
	if (m_gaugeState[plNum] == SpecialGaugeState::Use) return;

	m_gaugeState[plNum] = SpecialGaugeState::Add;
	m_addValue[plNum] += addValue;
}

/**
* @brief ゲージを使用状態にする
* @param plNum - プレイヤー番号
*/
void SpecialGauge::Use(int plNum)
{
	m_gaugeState[plNum] = SpecialGaugeState::Use;
}

/**
* @brief ゲージを使用できるか否か
* @param useKind - ゲージを使用する技の種類
* @param plNum - プレイヤー番号
* @return trueで発動
*/
bool SpecialGauge::IsUseGauge(const State& useKind, int plNum)
{
	// 状態を保存
	m_useKind[plNum] = useKind;

	switch (m_useKind[plNum])
	{
	case State::StrongAttack:
		// ゲージ１本以上
		if (m_gaugeNum[plNum] >= 1)
			return true;
		break;

	case State::SpecialAttack:
		// ゲージ２本以上
		if (m_gaugeNum[plNum] >= 2)
			return true;
		break;
	}
	
	return false;
}

float SpecialGauge::GetGauge(int index)
{
	return m_gauge[index];
}

int SpecialGauge::GetGaugeCount(int index)
{
	return m_gaugeNum[index];
}