/**
* @file IObject.h
* @brief オブジェクトのインターフェイス
* @author Syota Tachikawa
*/

#ifndef ___IOBJECT_H
#define ___IOBJECT_H

// 派生先で使用するヘッダを予めインクルードしておく
#include "..\DirectX\GraphicsLib.h"
#include "..\Common\FileData.h"
#include "..\Common\Struct.h"
#include "IPlayer.h"

/**
* @brief オブジェクトインターフェイス
*/
__interface IObject
{
	/**
	* @brief 更新
	*/
	bool Update();

	/**
	* @brief 描画
	*/
	void Render();
};

/**
* @brief パーティクルインターフェイス
*/
__interface IParticle : public IObject
{
};

/**
* @brief エフェクトインターフェイス
*/
__interface IEffect : public IObject
{
};

/**
* @brief ステージインターフェイス
*/
__interface IStage : public IObject
{
	/**
	* @brief ステージ全体のアルファ値を変更する
	*/
	void ChangeAlpha(int alpha);
};

/**
* @brief 当たり判定を持つエフェクトインターフェイス
*/
__interface ICollisionEffect : public IObject
{
	/**
	* @brief プレイヤーとの当たり判定
	*/
	void CollisionCheckPlayer(IPlPtr obj);
};

/// エフェクトインターフェイスのスマートポインタを定義
using IEffectPtr = shared_ptr<IEffect>;

/// パーティクルのスマートポインタを定義
using IParticlePtr = shared_ptr<IParticle>;

/// 当たり判定付きエフェクトインターフェイスのスマートポインタを定義
using IColEffectPtr = shared_ptr<ICollisionEffect>;

/// ステージインターフェイスのスマートポインタを定義(ユニークポインタ)
using IStagePtr = unique_ptr<IStage>;

#endif