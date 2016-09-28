#include "SpecialSlashEffect.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\SpecialHitParticle.h"
#include "..\..\DirectX\SoundPlayer.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\GameSystem\Collide.h"

/**
* @brief コンストラクタ
* @param id - エフェクトのID(攻撃使用プレイヤーの持つIDが渡される)
* @param pos - 位置
* @param dir - 向き
* @param vel - 速度
* @param rot - 角度(デフォルトで0.0f)
*/
SpecialSlashEffect::SpecialSlashEffect(
	const unsigned int id, 
	const Vector2& pos, 
	const Dir& dir, 
	const Vector2& vel,
	const float rot)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_SLASH3);

	// 位置を設定
	m_obj.pos = pos;
	m_obj.rot = rot;
	m_obj.scale = 0.8f;

	// 向きによって速度と向きと角度を設定
	if (dir == Dir::Right){
		m_v.x = vel.x;
		m_obj.isReverse = false;
	}
	else{
		// 符号を反転させる
		m_obj.rot *= -1;
		m_v.x -= vel.x;
		m_obj.isReverse = true;
	}
	m_v.y = vel.y;

	// 当たり範囲を設定
	m_hitRect = { 0.0f, 0.0f, 300.0f, 300.0f };
	m_liveFrame = 10;
	m_id = id;

	m_isHit = false;
}

/**
* @brief 更新
*/
bool SpecialSlashEffect::Update()
{
	// 拡大する
	m_obj.scale += 0.4f;

	// スケール固定
	if (m_obj.scale >= 1.5f){
		m_obj.scale = 1.5f;
	}

	// 位置に速度を加算する
	m_obj.pos += m_v;

	// 生存フレームを減算
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void SpecialSlashEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, ALPHA_MAX, false);
}

/**
* @brief プレイヤーとの当たり判定
*/
void SpecialSlashEffect::CollisionCheckPlayer(IPlPtr obj)
{
	// エフェクトを出した自分自身には当たらない
	if (m_id == obj->GetID()) return;

	// ヒットしていたら処理を終了する
	if (m_isHit) return;

	// 当たっていなかったら処理を終了する
	if (!Collide::CheckRectAndRect(m_obj.pos, obj->GetPos(), m_hitRect, obj->GetHitRect())) return;

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
	// ヒットしたら少し浮かす
	obj->SetSpeed(0.0f, -0.3f);

	// パーティクルの追加
	for (int i = 0; i < 5; i++){
		ParticleManager::GetInstance()->Add(make_shared<SpecialHitParticle>(obj->GetPos()));
	}

	static int seFrame = 0;
	// 効果音の再生
	if (seFrame % 3 == 0){
		SoundPlayer::GetInstance()->Play(BLADE_SE);
	}
	seFrame++;

	// ヒット
	m_isHit = true;
}