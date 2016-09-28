#include "CollisionEffectManager.h"
#include "FireEffect.h"
#include "..\..\DirectX\SoundPlayer.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\FireParticle.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\GameSystem\Collide.h"

/**
* @brief コンストラクタ
* @param id - 番号
* @param pos - 描画位置
* @param dir - 描画向き
*/
FireEffect::FireEffect(const unsigned int id, const Vector2& pos, const Dir& dir)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_HINOKO);

	// 位置を設定
	m_obj.pos = pos;
	m_obj.scale = 1.0f;

	// 向きによって速度と向きを設定
	if (dir == Dir::Right){
		m_v.x = 20.0f;
		m_obj.isReverse = false;
	}
	else{
		m_v.x -= 20.0f;
		m_obj.isReverse = true;
	}

	// ヒット範囲
	m_hitRect = { 0.0f, 0.0f, 180.0f, 180.0f };
	
	// 生存フレームは60フレーム
	m_liveFrame = 60;
	// プレイヤーの番号を入れる
	m_id = id;
	// 死んでいない
	m_isDead = false;
}

/**
* @brief 更新
*/
bool FireEffect::Update()
{
	// 位置に速度を加算する
	m_obj.pos += m_v;

	// 生存フレームが０で消す
	if (m_liveFrame < 0){
		m_isDead = true;
	}

	// 生存フレームを減算
	m_liveFrame--;

	// trueで削除
	return m_isDead;
}

/**
* @brief 描画
*/
void FireEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, ALPHA_MAX, false, m_obj.isReverse);
}

/**
* @brief プレイヤーとの当たり判定
*/
void FireEffect::CollisionCheckPlayer(IPlPtr obj)
{
	// エフェクトを出した自分自身には当たらない
	if (m_id == obj->GetID()) return;

	// 当たっていなかったら処理を終了する
	if (!Collide::CheckRectAndRect(m_obj.pos, obj->GetPos(), m_hitRect, obj->GetHitRect())) return;

	// 当たったらエフェクトを消す
	m_isDead = true;

	// ガード状態だったら
	if (obj->GetState() == State::Guard || 
		obj->GetState() == State::JumpGuard ||
		obj->GetState() == State::GuardNow)
	{
		// ガード中
		obj->SetState(State::GuardNow);
		// 終了
		return;
	}

	// 被弾状態に設定
	obj->SetState(State::DamageEffect);
	// 炎上させる
	obj->SetBurning();
	// 停止させる
	obj->SetSpeed();

	// 効果音を再生
	SoundPlayer::GetInstance()->Play(FLAMECOLLIDE_SE);

	// プレイヤーの座標にヒットパーティクルを生成する
	for (int i = 0; i < 35; i++)
	{
		ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(obj->GetPos().x, obj->GetPos().y + 70.f), 1.3f));
		ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(obj->GetPos().x + 8.0f, obj->GetPos().y + 70.f), 1.3f));
		ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(obj->GetPos().x - 8.0f, obj->GetPos().y + 70.f), 1.3f));
	}
}