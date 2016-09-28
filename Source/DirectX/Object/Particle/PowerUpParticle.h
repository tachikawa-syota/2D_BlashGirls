/**
* @file   PowerUpParticle.h
* @brief  能力上昇中のパーティクルシステムを管理する
* @author Syota Tachikawa
*/

#ifndef ___POWERUPPARTICLE_H
#define ___POWERUPPARTICLE_H

#include "..\IObject.h"

/**
* @brief パワーアップパーティクルクラス
*/
class PowerupParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	PowerupParticle(const Vector2& pos,
		const float scale,
		const float alpha);
	/**
	* @brief デストラクタ
	*/
	~PowerupParticle(){};

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