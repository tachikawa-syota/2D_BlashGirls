/**
* @file   ISequence.h
* @brief  シークエンスインターフェイス
* @author Syota Tachikawa
*/

#ifndef ___ISEQUENCE_H
#define ___ISEQUENCE_H

using namespace std;
#include <memory>

/**
* @brief シークエンスインターフェイスクラス
*/
__interface ISequence
{
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