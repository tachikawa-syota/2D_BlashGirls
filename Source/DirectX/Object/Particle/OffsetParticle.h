/**
* @file   OffsetParticle.h
* @brief  相殺パーティクルを管理する
* @author Syota Tachikawa
*/

#ifndef ___OFFSETPARTICLE_H
#define ___OFFSETPARTICLE_H

#include "..\IObject.h"

/**
* @brief 相殺パーティクルクラス
*/
class OffsetParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	OffsetParticle(const Vector2& pos);
	/**
	* @brief デストラクタ
	*/
	~OffsetParticle(){};

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

	/// 生存フレーム
	int m_liveFrame;
};

#endif