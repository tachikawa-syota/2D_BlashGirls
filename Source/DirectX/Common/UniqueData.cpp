#include "UniqueData.h"

/**
* @brief 選択したキャラクターの種類を設定
* @param キャラクターデータの配列をポインタで受け取る
*/
void UniqueData::SetSelectCharacter(const int* select)
{
	m_selectChara = select;
}

/**
* @brief 選択したキャラクターを取得
* @return キャラクターデータのポインタ
*/
const int* UniqueData::GetSelectCharacter() const
{
	return m_selectChara;
}

/**
* @brief プレイヤーの人数を設定する
* @param playerCount - プレイヤーの数
* @param computerCount - コンピューターの数
*/
void UniqueData::SetPlayerCount(int playerCount, int computerCount)
{
	m_playerCount = playerCount;
	m_computerCount = computerCount;
}

/**
* @brief プレイヤーの人数を取得
*/
int UniqueData::GetPlayerCount()
{
	return m_playerCount;
}

/**
* @brief コンピューターの人数を取得
*/
int UniqueData::GetComputerCount()
{
	return m_computerCount;
}

/**
* @brief 敗北したプレイヤーを設定
* @param 敗北したプレイヤーの番号
*/
void UniqueData::SetLosePlayer(const int index)
{
	m_losePl = index;
}

/**
* @brief 敗北したプレイヤーを取得
*/
int UniqueData::GetLosePlayer() const
{
	return m_losePl;
}

/**
* @brief ゲームモードを設定
*/
void UniqueData::SetGameMode(const GameMode mode)
{
	m_gameMode = mode;
}

/**
* @brief ゲームモードを取得
*/
const GameMode UniqueData::GetGameMode() const
{
	return m_gameMode;
}
