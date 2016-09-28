/**
* @file   CutIn.h
* @brief  カットイン処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___CUTIN_H
#define ___CUTIN_H

#include "..\Common\StdAfx.h"

/**
* @brief カットインクラス
*/
class CutIn
{
public:
	/**
	* @brief コンストラクタ
	* @param name - キャラクターの名前
	* @param index - キャラクターの番号
	*/
	CutIn(int name, int index);

	/**
	* @brief デストラクタ
	*/
	~CutIn();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;

	/// オブジェクト
	Object2DPacket m_obj;

	/// 速度
	Vector2 m_v;

	/// 番号
	int m_index;

	/// 背景
	int m_backTex;

	/// 慣性
	float m_inertia;
};

#endif