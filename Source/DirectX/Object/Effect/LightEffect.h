/**
* @file   LightEffect.h
* @brief  光エフェクトを管理
* @author Syota Tachikawa
*/

#ifndef ___LIGHTEFFECT_H
#define ___LIGHTEFFECT_H

#include "..\IObject.h"

/**
* @brief 光エフェクト
*/
class LightEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	* @param 描画位置
	*/
	LightEffect(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~LightEffect(){};

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

	/// アニメーション用
	int m_animation;

	/// テクスチャデータ
	int hTex[LIGHT_MAX];

	/// アニメーションフレーム
	int m_animFrame;
};

#endif