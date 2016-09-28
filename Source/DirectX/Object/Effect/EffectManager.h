/**
* @file   EffectManager.h
* @brief  全エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___EFFECTMANAGER_H
#define ___EFFECTMANAGER_H

#include "..\IObject.h"

/**
* @brief エフェクトを管理するクラス
*/
class EffectManager
{
public:
	/**
	* @brief インスタンスを取得する（シングルトン）
	*/
	static EffectManager* GetInstance(){
		static EffectManager singleton;
		return &singleton;
	}

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
	* @brief 追加
	*/
	void Add(IEffectPtr p);

private:
	/// エフェクトリスト
	list<IEffectPtr> effects;
};

#endif