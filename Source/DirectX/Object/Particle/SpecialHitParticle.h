/**
* @file   SpecialHitParticle.h
* @brief  必殺技ヒットパーティクルを管理する
* @author Syota Tachikawa
*/

#ifndef ___SPECIALHITPARTICLE_H
#define ___SPECIALHITPARTICLE_H

#include "..\IObject.h"

/**
* @brief 必殺技ヒットパーティクル
*/
class SpecialHitParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	SpecialHitParticle(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~SpecialHitParticle(){};

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