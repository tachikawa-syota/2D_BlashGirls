/**
* @file HpGauge.h
* @brief HPゲージに関係する処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___HPGAUGE_H
#define ___HPGAUGE_H

#include "..\..\Common\StdAfx.h"

/**
* @brief HPゲージに関係する処理を管理するクラス
*/
class HpGauge
{
public:
	/**
	* @brief 初期化
	*/
	void Initialize();
	
	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 初期化
	*/
	int isDead();

	/**
	* @brief HP残量を取得
	* @param プレイヤーの番号
	*/
	float GetHP(const int plNum);

	/**
	* @brief ヒット前のHP量を取得
	* @param プレイヤーの番号
	*/
	float GetOldHP(const int plNum);

	/**
	* @brief 最大HP量を取得
	*/
	float GetMaxHp();

	/**
	* @brief ダメージ加算
	* @param damage - 加算するダメージの量
	* @param plNum - プレイヤーの番号
	*/
	void DamageAdd(const float damage, const int plNum);

	/**
	* @brief ヒット前のHP情報を削除
	* @param プレイヤーの番号
	*/
	void SetOldGaugeDelete(const int plNum, const bool bFlag = false);

private:
	const float GAUGE_SIZE_X = 289.0f;

	/// ダメージ量
	float m_damage[JOY_MAX];

	/// HP残量
	float m_hpGauge[JOY_MAX];

	/// ヒット前のHP残量
	float m_hpGaugeOld[JOY_MAX];

	/// 最大HP
	float m_Maxhp;

	/// 死亡
	bool m_isDead[JOY_MAX];		/// trueで戦闘不能
	bool m_isDelete[JOY_MAX];

};

#endif