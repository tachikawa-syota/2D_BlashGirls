/**
* @file   GuardParticle.h
* @brief  ガードパーティクルを管理する
* @author Syota Tachikawa
*/

#ifndef ___GUARDPARTICLE_H
#define ___GUARDPARTICLE_H

#include "..\IObject.h"

/**
* @brief ガードパーティクルクラス
*/
class GuardParticle : public IParticle
{
public:
	/**
	* @brief コンストラクタ
	*/
	GuardParticle(const Vector2& pos,
		const float scale);
	/**
	* @brief デストラクタ
	*/
	~GuardParticle(){};

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