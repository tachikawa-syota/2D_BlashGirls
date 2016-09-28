/**
* @file   SequenceChanger.h
* @brief  シーンの切り替えを管理する
* @author Syota Tachikawa
*/

#ifndef ___SEQUENCECHANGER_H
#define ___SEQUENCECHANGER_H

#include "ISequence.h"

/**
* @brief シーンの切り替えを管理するクラス
*/
class SequenceChanger
{
private:
	/// 現在のシーン
	ISequence* m_nowScene;

public:
	/**
	* @brief コンストラクタ
	*/
	static SequenceChanger* GetInstance() {
		static SequenceChanger singleton;
		return &singleton;
	}

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief シーンの切り替え
	* @param 切り替えたいシーンを入れる
	*/
	void ChangeScene(ISequence* seq);
	
	/**
	* @brief 現在のシーンを取得する
	*/
	ISequence* GetNowScene();
};

#endif