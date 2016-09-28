/**
* @file   FlushEffect.h
* @brief  光エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___FLUSHEFFECT_H
#define ___FLUSHEFFECT_H

#include "..\IObject.h"

/**
* @brief 光エフェクト
*/
class FlushEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	FlushEffect(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~FlushEffect(){};

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