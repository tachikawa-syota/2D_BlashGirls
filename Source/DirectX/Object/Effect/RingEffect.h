/**
* @file   RingEffect.h
* @brief  輪っかエフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___RINGEFFECT_H
#define ___RINGEFFECT_H

#include "..\IObject.h"

/**
* @brief 輪っかエフェクトクラス
*/
class RingEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	RingEffect(const Vector2& pos, const ARGB& color, const float addScale);

	/**
	* @brief デストラクタ
	*/
	~RingEffect(){};

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

	/// カラーデータ
	ARGB m_color;

	/// 拡大速度
	float m_addScale;

	/// 生存フレーム
	int m_liveFrame;
};

#endif