/**
* @file   ScreanEffect.h
* @brief  スクリーンエフェクト処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___SCREANEFFECT_H
#define ___SCREANEFFECT_H

#include "StdAfx.h"
#include "..\DirectX\GraphicsLib.h"

/**
* @brief スクリーンエフェクトクラス
*/
class ScreenEffect
{
public:
	// インスタンス取得
	static ScreenEffect* GetInstance(){
		static ScreenEffect singleton;
		return &singleton;
	}

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief フェードの設定
	*/
	bool SetFade(Fade type, FadeColor color, int frame);

	/**
	* @brief フェード実行中かをチェック
	*/
	bool isPlayFade();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Draw();

private:
	/// 加算値
	int m_add;

	/// 色
	FadeColor m_color;

	/// フレーム
	int m_frame;

	/// カウント
	int m_fade_cnt;

	/// 状態
	Fade m_state;

};

#endif