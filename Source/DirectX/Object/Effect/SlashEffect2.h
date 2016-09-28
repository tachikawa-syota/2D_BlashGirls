/**
* @file   SlashEffect2.h
* @brief  斬撃エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___SLASHEFFECT2_H
#define ___SLASHEFFECT2_H

#include "..\IObject.h"

/**
* @brief 斬撃エフェクトクラス
*/
class SlashEffect2 : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	SlashEffect2(const Vector2& pos, const Dir& dir,
		const Vector2& vel, const float rot);

	/**
	* @brief デストラクタ
	*/
	~SlashEffect2(){};

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
};

#endif