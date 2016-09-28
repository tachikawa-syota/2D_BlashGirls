/**
* @file   BurstRingEffect.h
* @brief  衝撃波エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___BURSTRINGEFFECT_H
#define ___BURSTRINGEFFECT_H

#include "..\IObject.h"

/**
* @brief 衝撃波エフェクト
*/
class BurstRingEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	BurstRingEffect(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~BurstRingEffect(){};

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

	/// 生存フレーム
	int m_liveFrame;
};

#endif