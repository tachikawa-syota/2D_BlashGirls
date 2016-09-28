/**
* @file   ConboCounter.h
* @brief  コンボ数を管理する
* @author Syota Tachikawa
*/

#ifndef ___COMBOCOUNTER_H
#define ___COMBOCOUNTER_H

#include "..\Common\StdAfx.h"

/**
* @brief コンボ数を管理するクラス
*/
class ComboCounter
{
public:
	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief コンボ数を描画する
	*/
	void Render();

	/**
	* @brief コンボ数加算
	*/
	void Add(int plNum);

	/**
	* @brief 補正されたダメージを返す
	*/
	float ComboDamageCorrection(float damage, int plNum);

	/**
	* @brief 指定プレイヤーのコンボ数を取得
	* @param index - プレイヤー番号
	*/
	int GetComboCount(int index);

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;

	/// コンボ数
	int comboCount[JOY_MAX];

	/// １フレーム前のコンボ数
	int comboCountOld[JOY_MAX];

	/// コンボ持続フレーム
	int comboFrame[JOY_MAX];

	/// コンボ数１の位
	int comboOnesPlace[JOY_MAX];
	
	/// コンボ数１０の位
	int comboTensPlace[JOY_MAX];

	/// コンボ数１００の位
	int comboHundredsPlace[JOY_MAX];

	/// 数字テクスチャ用
	int numberTex[NUMBER_MAX];

	/// ヒット画像描画位置
	float hitTexX[JOY_MAX];
	
	/// 数字画像描画位置
	float numberTexX[JOY_MAX];

	// コンボ数によるダメージ補正係数
	float correctionCoefficient[JOY_MAX];
};

#endif