/**
* @file   HitParticle.h
* @brief  ヒットパーティクルを管理する
* @author Syota Tachikawa
*/

#ifndef ___HITPARTICLE_H
#define ___HITPARTICLE_H

#include "..\IObject.h"

/**
* @brief ヒットパーティクルクラス
*/
class HitParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	HitParticle(const Vector2& pos,
		const float scale);
	/**
	* @brief デストラクタ
	*/
	~HitParticle(){};

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