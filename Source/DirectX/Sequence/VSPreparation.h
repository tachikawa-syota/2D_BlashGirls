#pragma once

#include "ISequence.h"
#include "..\Common\StdAfx.h"

class VSPreparation : public ISequence
{
public:
	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 作成
	*/
	void Create();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief 終了
	*/
	void Finalize();

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;

	/// キャラクターオブジェクト
	Object2DPacket m_obj[JOY_MAX];

	/// Playerフォントオブジェクト
	Object2DPacket m_plFontObj[JOY_MAX];

	/// キャラクターオブジェクトの速度
	float m_v[JOY_MAX];

	/// Playerフォントオブジェクトの速度
	float m_plFontvx[JOY_MAX];

	/// キャラクターの名前フォントオブジェクト
	Object2DPacket m_nameObj[JOY_MAX];

	/// キャラクターの名前フォントの速度
	float m_namevx[JOY_MAX];
	float m_namevy[JOY_MAX];

	/// キャラクターオブジェクトのアルファ値（アルファ値は共通した値が入るから一つだけ）
	int m_alpha;

	/// フレーム
	int m_frame;

	/// サブワーク
	int m_subWork;

	/// 背景フォントの位置
	float fontY;

	/// VSフォントの大きさ
	float vsScale_;

	/**
	* @brief 背景文字の更新
	*/
	void UpdateBackgroundFont();

};