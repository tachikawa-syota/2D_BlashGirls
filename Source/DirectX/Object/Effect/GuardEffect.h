/**
* @file   GuardEffect.h
* @brief  ガードエフェクトを管理
* @author Syota Tachikawa
*/

#ifndef ___GUARDEFFECT_H
#define ___GUARDEFFECT_H

#include "..\..\Common\Struct.h"
#include "..\IObject.h"

/**
* @brief ガードエフェクト
*/
class GuardEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	* @param pos - 描画位置
	* @param dir - 描画向き
	*/
	GuardEffect(const Vector2& pos, const Dir& dir);

	/**
	* @brief デストラクタ
	*/
	~GuardEffect(){};

	/**
	* @brief 更新
	*/
	bool Update();

	/**
	* @brief 描画
	*/
	void Render();

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;

	/// 2Dオブジェクト用
	Object2DPacket m_obj;

	/// 速度
	Vector2 m_v;

	/// 生存フレーム
	int m_liveFrame;
};

#endif