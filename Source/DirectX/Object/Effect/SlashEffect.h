/**
* @file   SlashEffect.h
* @brief  斬撃エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___SLASHEFFECT_H
#define ___SLASHEFFECT_H

#include "..\IObject.h"

/**
* @brief 斬撃エフェクトクラス
*/
class SlashEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	SlashEffect(const Vector2& pos, const Dir& dir,
		const Vector2& vel, const float scale, const float addScale = 0.0f, const float rot = 0.0f);
	/**
	* @brief デストラクタ
	*/
	~SlashEffect(){};

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

	/// 角度速度
	float m_addScale;

	/// 生存フレーム
	int m_liveFrame;
};

#endif