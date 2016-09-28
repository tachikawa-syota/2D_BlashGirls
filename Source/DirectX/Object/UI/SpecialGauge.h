/**
* @file SpecialGauge.h
* @brief 必殺技ゲージに関係する処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___SPECIALGAUGE_H
#define ___SPECIALGAUGE_H

#include "..\..\Common\StdAfx.h"

/**
* @brief 必殺技ゲージに関係する処理を管理するクラス
*/
class SpecialGauge
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
	* @brief ゲージを増加する
	*/
	void Add(float addValue, int plNum);

	/**
	* @brief ゲージを使用状態にする
	*/
	void Use(int plNum);

	/**
	* @brief ゲージを使用できるか否か
	*/
	bool IsUseGauge(const State& useKind, int plNum);

	/**
	* @brief ゲージ量を取得
	*/
	float GetGauge(int index);

	/**
	* @brief ゲージ本数を取得
	*/
	int GetGaugeCount(int index);

private:
	/// ゲージ量の描画位置
	float m_gaugeX[JOY_MAX];

	/// ゲージ量
	float m_gauge[JOY_MAX];

	/// ゲージ本数
	int m_gaugeNum[JOY_MAX];

	/// ゲージ増加量
	float m_addValue[JOY_MAX];

	/// ゲージの状態
	SpecialGaugeState m_gaugeState[JOY_MAX];

	/// ゲージの使用種類
	State m_useKind[JOY_MAX];
	
	/// 数字テクスチャの位置
	float m_texX[4];
};

/// 必殺技ゲージクラスのスマートポインタを定義
using SpGaugePtr = shared_ptr<SpecialGauge>;

#endif