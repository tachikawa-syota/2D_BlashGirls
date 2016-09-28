/**
* @file   UIManager.h
* @brief  UIを管理する
* @author Syota Tachikawa
*/

#ifndef ___UIMANAGER_H
#define ___UIMANAGER_H

#include "..\..\Common\StdAfx.h"
#include "SpecialGauge.h"
#include "HpGauge.h"

/**
* @brief UIを管理するクラス
*/
class UIManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	UIManager();
	
	/**
	* @brief デストラクタ
	*/
	~UIManager();

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void Update(int breakState[], HpGauge hp);

	/**
	* @brief 描画
	*/
	void Render(int winCount[], float swingAdd[], const SpGaugePtr& sp, HpGauge hp);

	/**
	* @brief 衣服が破れた
	*/
	bool IsClothesBreak(int index);

	/**
	* @brief ゲージデータを設定
	*/
	bool SetGaugeData(int index);

private:

	const float GAUGE_SIZE_X = 289.0f;

	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;

	/// HPゲージテクスチャ
	LPDIRECT3DTEXTURE9 m_tex;
	LPDIRECT3DTEXTURE9 m_oldTex;

	/// リリアの立ち絵テクスチャ
	int m_standLiliaTex[6];

	/// ルナの立ち絵テクスチャ
	int m_standRunaTex[6];

	/// 左右に表示するキャラクターの立ち絵番号
	int m_displayNumber[JOY_MAX];

	/// 左右に表示するキャラクターの立ち絵状態
	int m_standCharaState[JOY_MAX];

	/// 左右に表示するキャラクターの立ち絵の背景
	int m_standCharaBack[3];

	/// 立ち絵の衣服状態
	int m_breakClothesCount[JOY_MAX];

	/// 選択したキャラクター
	const int* m_selectChara;

	/// 数字テクスチャ
	int m_numberTex[NUMBER_MAX];

	/// 衣服が破れた
	bool m_isClothesBreak[JOY_MAX];

	/// 必殺技ゲージの数字を表示する座標
	float m_spGaugeNumberX[JOY_MAX];

};

#endif