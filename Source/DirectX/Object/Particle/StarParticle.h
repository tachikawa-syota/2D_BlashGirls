/**
* @file   StarParticle.h
* @brief  星パーティクルを管理する
* @author Syota Tachikawa
*/

#ifndef ___STARARTICLE_H
#define ___STARPARTICLE_H

#include "..\IObject.h"

/**
* @brief 星パーティクルクラス
*/
class StarParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	StarParticle(const Vector2& pos);
	/**
	* @brief デストラクタ
	*/
	~StarParticle(){};

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