// --------------------------------------------------------
//
//	恥辱システムに関係する処理の記述
//
// --------------------------------------------------------

#include "HpGauge.h"
#include "..\..\Common\ParamLoader.h"

/**
* @brief 初期化
*/
void HpGauge::Initialize()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		m_damage[i] = 0.0f;
		m_Maxhp = GetPrm->HpMax;
		m_hpGauge[i] = GetPrm->HpMax;
		m_hpGaugeOld[i] = GetPrm->HpMax;
		m_isDead[i] = false;
		m_isDelete[i] = false;
	}
}

/**
* @brief 更新
*/
void HpGauge::Update()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		if (m_isDelete[i])
		{
			m_hpGaugeOld[i] -= 20.0f;
			if (m_hpGaugeOld[i] <= m_hpGauge[i]){
				m_hpGaugeOld[i] = m_hpGauge[i];
				m_isDelete[i] = false;
			}
		}

		if (m_hpGauge[i] < 0)
		{
			m_hpGauge[i] = 0;
			m_isDead[i] = true;
		}

		// ダメージ処理
		m_hpGauge[i] -= m_damage[i];
		m_damage[i] = 0;
	}
}

/**
* @brief KO状態か否か
* @return 0,1 - KOしたプレイヤー番号 , -1 - KOしていない
*/
int HpGauge::isDead()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		if (m_isDead[i])
		{
			return i;
		}
	}
	return -1;
}


/**
* @brief HP残量を取得
*/
float HpGauge::GetHP(const int plNum)
{
	return m_hpGauge[plNum];
}

/**
* @brief ヒット前のHP量を取得
*/
float HpGauge::GetOldHP(const int plNum)
{
	return m_hpGaugeOld[plNum];
}

/**
* @brief 最大HP量を取得
*/
float HpGauge::GetMaxHp()
{
	return m_Maxhp;
}

/**
* @brief ダメージ加算
*/
void HpGauge::DamageAdd(const float damage, const int plNum)
{
	m_damage[plNum] = damage;
}

/**
* @brief ヒット前のHP情報を削除
*/
void HpGauge::SetOldGaugeDelete(const int plNum, const bool bFlag)
{
	m_isDelete[plNum] = bFlag;
}