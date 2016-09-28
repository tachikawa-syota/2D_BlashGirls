#include "..\IObject.h"
#include "EffectManager.h"

/**
* @brief エフェクトを追加する
*/
void EffectManager::Add(IEffectPtr p)
{
	effects.emplace_back(p);
}

/**
* @brief 初期化
*/
void EffectManager::Initialize()
{
	// 全要素削除
	effects.clear();
}

/**
* @brief エフェクトを更新する
*/
void EffectManager::Update()
{
	// イテレータを取得
	auto it = effects.begin();

	while (it != effects.end())
	{
		if ((*it)->Update()){
			// 削除
			it = effects.erase(it);
		}
		else{
			// 更新
			++it;
		}
	}
}

/**
* @brief エフェクトを描画する
*/
void EffectManager::Render()
{
	// リスト内全描画
	for (auto& e : effects)
	{
		e->Render();
	}
}