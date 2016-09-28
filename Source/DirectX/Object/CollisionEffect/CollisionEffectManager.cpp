#include "CollisionEffectManager.h"
#include "..\IObject.h"

/**
* @brief 当たり判定付きのエフェクトを追加する
*/
void CollisionEffectManager::Add(IColEffectPtr p)
{
	m_colEffects.emplace_back(p);
}

/**
* @brief 初期化
*/
void CollisionEffectManager::Initialize()
{
	// 全要素削除
	m_colEffects.clear();
}

/**
* @brief 当たり判定付きのエフェクトを更新する
*/
void CollisionEffectManager::Update()
{
	// イテレータを取得
	auto it = m_colEffects.begin();

	while (it != m_colEffects.end())
	{
		if ((*it)->Update()){
			// 削除
			it = m_colEffects.erase(it);
		}
		else{
			// 更新
			++it;
		}
	}
}

/**
* @brief 当たり判定付きのエフェクトを描画する
*/
void CollisionEffectManager::Render()
{
	// リスト内全描画
	for (auto& c : m_colEffects)
	{
		c->Render();
	}
}

/**
* @brief プレイヤーとの当たり判定
*/
void CollisionEffectManager::CollisionCheckPlayer(IPlPtr obj)
{
	// イテレータを取得
	auto it = m_colEffects.begin();

	while (it != m_colEffects.end()){
		// 当たっているか否かのチェック
		(*it)->CollisionCheckPlayer(obj);
		++it;
	}
}