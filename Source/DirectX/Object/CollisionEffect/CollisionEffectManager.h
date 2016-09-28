/**
* @file   CollisionEffectManager.h
* @brief  当たり判定付きエフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___COLLISIONEFFECTMANAGER_H
#define ___COLLISIONEFFECTMANAGER_H

#include "..\IObject.h"

/**
* @brief 当たり判定付きエフェクト管理者
*/
class CollisionEffectManager
{
public:
	/**
	* @brief インスタンスを取得する（シングルトン）
	*/
	static CollisionEffectManager* GetInstance(){
		static CollisionEffectManager singleton;
		return &singleton;
	}

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief 追加
	*/
	void Add(IColEffectPtr p);

	/**
	* @brief プレイヤーとの当たり判定
	*/
	void CollisionCheckPlayer(IPlPtr obj);

private:
	/// 当たり判定付き
	list<IColEffectPtr> m_colEffects;
};

#endif