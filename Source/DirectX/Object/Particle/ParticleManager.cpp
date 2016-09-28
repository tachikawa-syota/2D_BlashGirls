#include "ParticleManager.h"
#include "..\IObject.h"

/**
* @brief パーティクルを追加する
*/
void ParticleManager::Add(IParticlePtr p)
{
	particles.emplace_back(p);
}

/**
* @brief 初期化
*/
void ParticleManager::Initialize()
{
	// 全要素削除
	particles.clear();
}

/**
* @brief パーティクルを更新する
*/
void ParticleManager::Update()
{
	// イテレータを取得
	auto it = particles.begin();

	while (it != particles.end())
	{
		if ((*it)->Update()){
			// 削除
			it = particles.erase(it);
		}
		else{
			// 更新
			++it;
		}
	}
}

/**
* @brief パーティクルを描画する
*/
void ParticleManager::Render()
{
	// リスト内全描画
	for (auto& p : particles)
	{
		p->Render();
	}
}