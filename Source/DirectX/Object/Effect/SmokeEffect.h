/**
* @file   SmokeEffect.h
* @brief  煙エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___SMOKEEFFECT_H
#define ___SMOKEEFFECT_H

#include "..\IObject.h"

/**
* @brief 煙エフェクトを管理するクラス
*/
class SmokeEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	* @param 描画位置
	*/
	SmokeEffect(const Vector2& pos);

	/**
	* @brief デストラクタ
	*/
	~SmokeEffect(){};

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