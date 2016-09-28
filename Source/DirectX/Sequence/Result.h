/**
* @file   Result.h
* @brief  リザルト画面の処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___RESULT_H
#define ___RESULT_H

#include "ISequence.h"
#include "..\DirectX\InputMask.h"
#include "..\Common\StdAfx.h"

/**
* @brief リザルト画面
*/
class Result : public ISequence
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
	
	// テクスチャデータ
	TextureData* m_texData;
	
	// 入力デバイス
	vector<InputRef> m_dev;
	
	/// フレーム
	int m_frame;

	/// サブワーク
	int m_subWork;

	/// 選択したキャラクター
	const int* m_select;

	/// 敗北したプレイヤー番号
	int m_losePl;

	/// カーソルを操作できるプレイヤー
	int m_controlPlayer;

	/// 敗者プレイヤー番号のテクスチャ
	int m_loserPlayerTex[2];

	/// 敗北したキャラクターのテクスチャ
	int m_loserCharaTex_[2];

	/// アルファ値
	int m_alpha;

	/// カーソルワーク
	int m_cursolWork;

	/// カーソルの位置
	float m_cursolY;

	/**
	* @brief カーソルの動き
	*/
	void CursolMove();
};

#endif