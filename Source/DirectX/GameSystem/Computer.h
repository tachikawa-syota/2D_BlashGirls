/**
* @file   Computer.h
* @brief  敵のAIシステムを管理する
* @author Syota Tachikawa
*/

#ifndef ___COMPUTER_H
#define ___COMPUTER_H

#include "..\Common\StdAfx.h"
#include "..\Common\Enum.h"
#include "..\Object\IPlayer.h"
#include "..\Object\UI\SpecialGauge.h"

/**
* @brief コンピューター（人工知能）クラス
*/
class Computer
{
public:
	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void ThinkUpdate(vector<IPlPtr> pPlayer, int index, int computerCount, SpGaugePtr sp);

	/**
	* @brief 行動を考える
	*/
	void ThinkAction(vector<IPlPtr> pPlayer, int index);

	/**
	* @brief 近距離時の行動
	*/
	void ShortDistanceAction();

	/**
	* @brief 中距離時の行動
	*/
	void MiddleDistanceAction();

	/**
	* @brief 長距離時の行動
	*/
	void LongDistanceAction();

	/**
	* @brief ゲージ量を確認する
	*/
	void CheckGauge(vector<IPlPtr> pPlayer, int index, SpGaugePtr sp);

private:
	/// 相手プレイヤー（人間）
	IPlPtr target;

	/// 次の行動に移るまでのフレーム
	unsigned int m_nextActionFrame;

	/// 行動フレーム
	unsigned int m_actionFrame;

	/// 状態
	State m_state;

	/// 前回の状態を保存
	State m_oldState;
};

#endif