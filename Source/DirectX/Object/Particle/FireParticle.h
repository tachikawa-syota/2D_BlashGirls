/**
* @file   FireParticle.h
* @brief  火パーティクルシステムを管理する
* @author Syota Tachikawa
*/

#ifndef ___FIREPARTICLE_H
#define ___FIREPARTICLE_H

#include "..\IObject.h"

/**
* @brief 火パーティクルクラス
*/
class FireParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	FireParticle(const Vector2& pos,
		const float scale);
	/**
	* @brief デストラクタ
	*/
	~FireParticle(){};

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

	/// 加速度
	Vector2 m_add;
};

#endif