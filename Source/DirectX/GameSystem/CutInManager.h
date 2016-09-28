/**
* @file   CutInManager.h
* @brief  カットインの作成や描画などを管理する
* @author Syota Tachikawa
*/

#ifndef ___CUTINMANAGER_H
#define ___CUTINMANAGER_H

#include "CutIn.h"

/**
* @brief カットインの作成や描画等を管理するクラス
*/
class CutInManager
{
public:
	/**
	* @brief インスタンスを取得する(シングルトン)
	*/
	static CutInManager* GetInstance(){
		static CutInManager singlton;
		return &singlton;
	}

	/**
	* @brief 作成
	* @param name - キャラクターの名前(Enum定義したものを使用する)
	* @param index - キャラクターの番号
	* @param pos - 描画する位置
	*/
	void Create(int name, int index, const Vector2& pos);

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief 表示中かどうかの確認
	*/
	bool IsPlayCutIn();

private:
	/// カットイン
	CutIn* m_cutin;

	/// フレーム
	int m_frame;

	/// 表示フラグ
	bool m_isDisp;
};

#endif