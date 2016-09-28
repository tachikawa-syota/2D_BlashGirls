/**
* @file   CharacterFactory.h
* @brief  キャラクターのインスタンスを生成する
* @author Syota Tachikawa
*/

#ifndef ___CHARACTERFACTORY_H
#define ___CHARACTERFACTORY_H

#include "..\IPlayer.h"
#include "Lilia.h"
#include "Runa.h"

/**
* @brief キャラクター生成クラス
*/
class CharacterFactory
{
public:
	/**
	* @brief キャラクターインスタンス生成
	* @param name - キャラクターの名前(Enumで定義している物を使用)
	* @param index - プレイヤーの番号
	*/
	IPlPtr CreateCharacter(const int name, const int index);
};

/**
* @brief キャラクターインスタンス生成
* @param name - キャラクターの名前(Enumで定義している物を使用)
* @param index - プレイヤーの番号
*/
IPlPtr CharacterFactory::CreateCharacter(const int name, const int index)
{
	switch (name)
	{
		// リリア
	case CharaName::LILIA:
		return make_shared<Lilia>(index);
		break;
		// ルナ
	case CharaName::RUNA:
		return make_shared<Runa>(index);
		break;
		// エラー（あり得ない）
	default:
		return nullptr;
		break;
	}
}

#endif
