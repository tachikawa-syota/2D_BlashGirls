/**
* @file   FormParticle.h
* @brief  泡パーティクルを管理する
* @author Syota Tachikawa
*/

#ifndef ___STARARTICLE_H
#define ___STARPARTICLE_H

#include "..\IObject.h"

/**
* @brief 泡パーティクルクラス
*/
class FormParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	FormParticle(const Vector2& pos , const float scale);
	/**
	* @brief デストラクタ
	*/
	~FormParticle(){};

	/**
	* @brief 更新
	*/
	bool Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief 生死判定
	*/
	bool isDead();

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