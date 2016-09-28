/**
* @file   WaveEffect.h
* @brief  波エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___WAVEEFFECT_H
#define ___WAVEEFFECT_H

#include "..\IObject.h"

class WaveEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	WaveEffect(const Vector2& pos, const Dir& dir);

	/**
	* @brief デストラクタ
	*/
	~WaveEffect(){};

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

	/// 波エフェクトアニメーション
	int m_hTex[WAVE_MAX];

	/// アニメーション
	int m_animation;

	/// アニメーションフレーム
	int m_animFrame;

	/// ループカウント
	unsigned int loopCount;
};

#endif