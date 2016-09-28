/**
* @file   Title.h
* @brief  タイトル処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___TITLE_H
#define ___TITLE_H

#include "..\DirectX\InputMask.h"
#include "..\Common\StdAfx.h"
#include "ISequence.h"

class Title : public ISequence
{
private:
	// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	// テクスチャデータ
	TextureData* m_texData;

	// 入力データを管理
	vector<InputRef> m_dev;

	/// サブワーク
	int m_subWork;

	/// タイトルワーク
	int titleWork;

	/// カーソルの位置
	float cursolY;

	/// 光エフェクトのアルファ値
	int m_lightAlpha;

	/// 光エフェクトの角度
	float m_lightAngle;

	/// アルファ値
	int m_alpha;

	/// フレーム
	int m_frame;

	/// アルファ値を加算
	bool m_isAlphaPlus;

	/// 選択されたキャラクター（デモに入る前に使う）
	int m_select[JOY_MAX];

	/// 放置フレーム
	int m_waitFrame;

	/**
	* @brief タイトルセレクトの更新
	*/
	GameMode TitleWork();

	void UpdateLight();

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
};

#endif