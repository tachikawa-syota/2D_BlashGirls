/**
* @file   ParticleManager.h
* @brief  全パーティクルを管理をする
* @author Syota Tachikawa
*/

#ifndef ___PARTICLEMANAGER_H
#define ___PARTICLEMANAGER_H

#include "..\IObject.h"

/**
* @brief パーティクルを管理するクラス
*/
class ParticleManager
{
public:
	/**
	* @brief インスタンスを取得する（シングルトン）
	*/
	static ParticleManager* GetInstance(){
		static ParticleManager singleton;
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
	* @brief パーティクルを追加する
	*/
	void Add(IParticlePtr p);

private:
	/// パーティクルリスト
	list<IParticlePtr> particles;
};

#endif