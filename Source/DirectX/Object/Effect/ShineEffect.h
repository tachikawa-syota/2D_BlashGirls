/**
* @file   ShineEffect.h
* @brief  光るエフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___SHINEEFFECT_H
#define ___SHINEEFFECT_H

#include "..\IObject.h"

class ShineEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	ShineEffect(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~ShineEffect(){};

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
	array<Object2DPacket ,2> m_obj;

	/// サブワーク
	int m_subWork;
};

#endif