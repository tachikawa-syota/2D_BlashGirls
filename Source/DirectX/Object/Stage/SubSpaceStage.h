/**
* @file   SubSpaceStage.h
* @brief  亜空間ステージを管理する
* @author Syota Tachikawa
*/

#ifndef ___SUBSPACESTAGE_H
#define ___SUBSPACESTAGE_H

#include "..\IObject.h"
#include "..\..\Common\StdAfx.h"

/**
* @brief 亜空間ステージクラス
*/
class SubSpaceStage : public IStage
{
public:
	/**
	* @brief コンストラクタ
	*/
	SubSpaceStage();

	/**
	* @brief デストラクタ
	*/
	~SubSpaceStage();

	/**
	* @brief 更新
	*/
	bool Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief アルファ値の変更（特殊スキルを使った時に背景を暗くする用で使う）
	*/
	void ChangeAlpha(int alpha);

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;
	
	/// フレーム
	unsigned int m_frame;
	
	/// ステージ全体のアルファ値
	int m_stageAlpha;
	
	/// 光アルファ値
	int m_lightAlpha;
	
	/// エフェクト拡大率
	float m_effectScale;
	
	/// エフェクト拡大フラグ
	bool m_isEffectScale;
};

#endif