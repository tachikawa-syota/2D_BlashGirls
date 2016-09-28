#ifndef ___UNIQUEDATA_H
#define ___UNIQUEDATA_H

#include "Enum.h"

/**
* @brief 一意なデータ管理クラス
*/
class UniqueData
{
public:
	/**
	* @brief インスタンス取得(シングルトン)
	*/
	static UniqueData* GetInstance(){
		static UniqueData singleton;
		return &singleton;
	}

	/**
	* @brief 選択したキャラクターの種類を設定
	* @param キャラクターデータの配列をポインタで受け取る
	*/
	void SetSelectCharacter(const int* select);

	/**
	* @brief 選択したキャラクターを取得
	* @return キャラクターデータのポインタ
	*/
	const int* GetSelectCharacter() const;

	/**
	* @brief プレイヤーの人数を設定する
	* @param playerCount - プレイヤーの数
	* @param computerCount - コンピューターの数
	*/
	void SetPlayerCount(int playerCount, int computerCount);

	/**
	* @brief プレイヤーの人数を取得
	*/
	int GetPlayerCount();

	/**
	* @brief コンピューターの人数を取得
	*/
	int GetComputerCount();

	/**
	* @brief 敗北したプレイヤーを設定
	*/
	void SetLosePlayer(const int index);

	/**
	* @brief 敗北したプレイヤーを取得
	*/
	int GetLosePlayer() const;

	/**
	* @brief ゲームモードを設定
	*/
	void SetGameMode(const GameMode mode);

	/**
	* @brief ゲームモードを取得
	*/
	const GameMode GetGameMode() const;

private:
	/// 選択したキャラクター
	const int* m_selectChara;

	/// プレイヤーの人数
	int m_playerCount;

	/// コンピューターの人数
	int m_computerCount;

	/// 敗北したキャラクター番号
	int m_losePl;

	/// ゲームモード
	GameMode m_gameMode;
};

#endif