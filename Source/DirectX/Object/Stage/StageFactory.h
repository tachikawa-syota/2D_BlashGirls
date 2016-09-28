/**
* @file   StageFactory.h
* @brief  ステージのインスタンスを生成する
* @author Syota Tachikawa
*/

#ifndef ___STAGEFACTORY_H
#define ___STAGEFACTORY_H

#include "..\IObject.h"
#include "SubSpaceStage.h"
#include "..\..\Common\Enum.h"

/**
* @brief ステージのインスタンスを作成 (ファクトリメソッド)
*/
class StageFactory
{
public:
	/**
	* @brief ステージの作成
	* @param ステージの種類
	*/
	IStagePtr CreateStage(StageType type);
};

/**
* @brief ステージのインスタンス作成(ファクトリメソッド)
* @param ステージの種類
*/
IStagePtr StageFactory::CreateStage(StageType type)
{
	// 今はステージが一つしかない
	switch (type)
	{
		// 亜空間ステージ
	case StageType::SubSpace:
		return make_unique<SubSpaceStage>();
		break;

		// あり得ない
	default:
		return nullptr;
		break;
	}
}

#endif