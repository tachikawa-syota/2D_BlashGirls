#ifndef ___IPLAYER_H
#define ___IPLAYER_H

#include "..\Common\StdAfx.h"
#include "..\Common\Struct.h"
#include "..\Common\Enum.h"

/**
* @brief プレイヤーインターフェイス
*/
__interface IPlayer
{
	/**
	* @brief 初期化
	* @param キャラクターの番号
	*/
	void Initialize(int index);

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief ジャンプ出来るかの判定
	*/
	bool IsJump();

	/**
	* @brief 受身を取れるか
	*/
	bool CanPassive();

	/**
	* @brief 追撃(派生技)が可能か
	*/
	bool CanDerivation();

	/**
	* @brief 制御
	* @return true - 制御可：false - 制御不可
	*/
	bool isControll();

	/**
	* @brief 炎上
	*/
	void SetBurning();

	/**
	* @brief 上段攻撃が当たったか
	*/
	bool isUpperAttackHit(const IPlayer& enemy);

	/**
	* @brief 下段攻撃が当たったか
	*/
	bool isLowerAttackHit(const IPlayer& enemy);

	/**
	* @brief 被弾
	*/
	void Damage(const IPlayer& attacker, AttackPoint hitType);

	/**
	* @brief 操作可能か
	*/
	bool CanControll();	

	/**
	* @brief 位置を設定
	*/
	void SetPos(const Vector2& pos);

	/**
	* @brief 状態を設定
	*/
	void SetState(const State state);

	/**
	* @brief 向きを設定
	*/
	void SetDirection(const Dir& dir);

	/**
	* @brief 速度を設定する
	*/
	void SetSpeed(const float spx = 0.0f, const float spy = 0.0f);

	/**
	* @brief プレイヤー番号を取得
	*/
	const unsigned int GetID() const;

	/**
	* @brief 攻撃力を取得
	*/
	const float GetPower() const;

	/**
	* @brief 位置を取得
	*/
	const Vector2& GetPos() const;

	/**
	* @brief 状態を取得
	*/
	const State GetState() const;

	/**
	* @brief 攻撃範囲を取得
	*/
	const Rect GetAttackRect() const;

	/**
	* @brief ヒット範囲を取得
	*/
	const Rect GetHitRect() const;

	/**
	* @brief 向きを取得
	*/
	const Dir GetDirection() const;

	/**
	* @brief 攻撃判定発生中か否か
	*/
	bool isAttackJudge();
};

// shared_ptrのIPlayer
using IPlPtr = shared_ptr<IPlayer>;

#endif