/**
* @file   LightLineEffect.h
* @brief  光の線エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___LIGHTLINEEFFECT_H
#define ___LIGHTLINEEFFECT_H

#include "..\IObject.h"

/**
* @brief 光の線エフェクトクラス
*/
class LightLineEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	LightLineEffect(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~LightLineEffect(){};

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