#include "Lilia.h"
#include "CharacterParam.h"
#include "CharacterParamLoader.h"
#include "..\..\DirectX\SoundPlayer.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\GameSystem\CutInManager.h"
#include "..\..\GameSystem\Collide.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\Common\Utility.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\GuardParticle.h"
#include "..\Particle\HitParticle.h"
#include "..\Particle\FireParticle.h"
#include "..\Effect\LightEffect.h"
#include "..\Effect\EffectManager.h"
#include "..\Effect\SlashEffect.h"
#include "..\Effect\SlashEffect2.h"
#include "..\Effect\GuardEffect.h"
#include "..\Effect\RingEffect.h"
#include "..\Effect\BurstRingEffect.h"
#include "..\Effect\FlushEffect.h"
#include "..\Effect\LightLineEffect.h"
#include "..\Effect\WaveEffect.h"
#include "..\Effect\SwordTrajectoryEffect.h"
#include "..\Effect\SmokeEffect.h"
#include "..\Effect\LightEffect.h"
#include "..\CollisionEffect\CollisionEffectManager.h"
#include "..\CollisionEffect\FireEffect.h"
#include "..\CollisionEffect\SpecialSlashEffect.h"

/**
* @brief コンストラクタ
*/
Lilia::Lilia(int index)
{
	// インスタンス取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャのコピー
	m_hDown = m_texData->GetLiliaAnim(9);
	m_hHit = m_texData->GetLiliaAnim(10);
	m_hJump = m_texData->GetLiliaAnim(11);
	m_hSquat = m_texData->GetLiliaAnim(18);
	m_hWalk = m_texData->GetLiliaAnim(22);
	m_hWin[0] = m_texData->GetLiliaAnim(23);
	m_hWin[1] = m_texData->GetLiliaAnim(24);

	// ３枚アニメーションを一括でコピー
	for (int i = 0; i < 3; i++){
		m_hJumpAttack[i] = m_texData->GetLiliaAnim(i + 12);
		m_hNeutral[i] = m_texData->GetLiliaAnim(i + 15);
		m_hSquatAttack[i] = m_texData->GetLiliaAnim(i + 19);
	}
	for (int i = 0; i < 9; i++){
		m_hAttack[i] = m_texData->GetLiliaAnim(i);
	}

	// パラメータの初期化をする
	Initialize(index);
}

/**
* @brief デストラクタ
*/
Lilia::~Lilia()
{
}

#pragma region IPlayer

/**
* @brief 初期化
* @param index - キャラクタの番号
*/
void Lilia::Initialize(int index)
{
	switch (index)
	{
	case PLAYER1:
		m_obj.pos = Vector2(GetPrm->Player1InitPosX, GetPrm->PlayerInitPosY);
		m_obj.direction = Dir::Right;
		m_obj.isReverse = false;
		break;

	case PLAYER2:
		m_obj.pos = Vector2(GetPrm->Player2InitPosX, GetPrm->PlayerInitPosY);
		m_obj.direction = Dir::Left;
		m_obj.isReverse = true;
		break;
	}

	m_obj.scale = (1.0f);
	m_obj.rot = (0.0f);
	m_obj.alpha = ALPHA_MAX;
	m_spd = m_oldSpd = Vector2();

	// キャラクタの番号
	m_id = index;

	// 各種カウントの初期化
	m_jumpCount = 0;
	m_slashingCount = 0;
	m_downFrame = 0;
	m_damageFrame = 0;
	m_knockbackFrame = 0;
	m_subFrame = 0;
	m_subWork = 0;

	m_attackPoint = AttackPoint::None;
	// 攻撃力の初期化
	m_power = 0.0f;
	// 制御可
	m_isControll = true;
	// 無敵ではない
	m_isInvincible = false;
	// 受身
	m_isPassive = false;
	// 攻撃判定発生してない
	m_isAttackJudge = false;
	m_isAttackSuccess = false;
	m_isDerivation = false;

	m_isBurning = false;

	/// ニュートラル状態
	m_state = State::Neutral;
	m_oldState = State::Neutral;

	// アニメーション番号を0に設定
	m_animation = 0;
}


/**
* @brief 更新
*/
void Lilia::Update()
{
	// 状態が切り替わったらリセットする
	if (m_oldState != m_state)
		ActionReset();

	switch (m_state)
	{
	case State::Neutral:
		Neutral();
		break;

	case State::Advance:
		Advance();
		break;

	case State::Guard:
		Guard();
		break;

	case State::GuardNow:
		GuardNow();
		break;

	case State::Dash:
		Dash();
		break;

	case State::Damage:
	case State::DamageEffect:
		Knockback();
		break;

	case State::BackStep:
		BackStep();
		break;

	case State::Jump:
	case State::JumpFront:
	case State::JumpBack:
		Jump();
		break;

	case State::JumpGuard:
		Jump();
		break;

	case State::JumpAttack:
		JumpAttack();
		break;

	case State::DashAttack:
		DashAttack();
		break;

	case State::Squat:
		Squat();
		break;

	case State::SquatGuard:
		SetSpeed();
		break;

	case State::SquatGuardNow:
		SquatGuardNow();
		break;

	case State::SquatAttack:
		SquatAttack();
		break;

	case State::WeakAttack:
		WeakAttack();
		break;

	case State::WeakDerivationAttack:
		WeakAttackDerivation();
		break;

	case State::MediumAttack:
		MediumAttack();
		break;

	case State::SpecialAttack:
		SpecialAttack();
		break;

	case State::AttackSpecialPursuit:
		SpecialPursuitAttack();
		break;

	case State::Down:
		Down();
		break;

	case State::StrongAttack:
		StrongAttack();
		break;

	case State::StrongDerivationAttack:
		StrongAttackDerivation();
		break;

	case State::UnderAttack:
		LongAttack();
		break;

	case State::RaidAttack:
		RaidAttack();
		break;

	case State::Passive:
		Passive();
		break;

	case State::Offset:
		Offset();
		break;

	case State::Blowoff:
		BlowOff();
		break;

	case State::SpecialProduction:
		SpecialProduction();
		break;

	case State::BeforBattle:
		BeforeBattle();
		break;

	case State::Ko:
		KO();
		break;

	case State::Win:
		Win();
		break;
	}

	// 状態を保存
	m_oldState = m_state;
	// 速度を保存
	m_oldSpd = m_spd;
	// 重力を加算
	m_spd.y += GetPrm->Gravity;
	// 位置に速度を加算
	m_obj.pos += m_spd;
	
	// 左向きならキャラクターを反転して描画
	if (m_obj.direction == Dir::Left){
		m_obj.isReverse = true;
	}
	else{
		m_obj.isReverse = false;
	}

	// 接地していたら
	if (m_obj.pos.y > GetPrm->Ground)
	{
		// 接地フラグを立てる
		m_isFloor = true;
		// ジャンプ回数を初期化
		m_jumpCount = JUMP_MAX;
		// めり込まないように補正する
		m_obj.pos.y = GetPrm->Ground;
	}
	else{
		// ジャンプできない
		m_jumpCount = 0;
		// 地面に付いていない
		m_isFloor = false;
	}

	// 燃えていたら
	if (m_isBurning)
	{
		// 今のアルファ値が255なら
		if (m_obj.alpha == ALPHA_MAX){
			m_obj.alpha = ALPHA_MIN;	// 黒くする
		}
		// あとはアルファを足していくだけ
		m_obj.alpha += BURNING_ADD_ALPHA;

		if (m_obj.alpha > ALPHA_MAX)
		{
			m_obj.alpha = ALPHA_MAX;
			m_isBurning = false;
		}
	}
}

/**
* @brief 描画
*/
void Lilia::Render()
{
	ARGB red = { 255, 255, 0, 0 };

	switch (m_state)
	{
	case State::Neutral:
		m_2dTex->DrawTexture(m_hNeutral[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::Advance:
	case State::Guard:
	case State::Dash:
	case State::BackStep:
		m_2dTex->DrawTexture(m_hWalk, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::Jump:
	case State::JumpFront:
	case State::JumpBack:
	case State::JumpGuard:
	case State::Passive:
		m_2dTex->DrawTexture(m_hJump, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

		// 素材が少ないから攻撃用アニメーションの使いまわす
	case State::GuardNow:
	case State::Offset:
		m_2dTex->DrawTexture(m_hAttack[0], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::Squat:
	case State::SquatGuard:
	case State::SquatGuardNow:
		m_2dTex->DrawTexture(m_hSquat, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::SquatAttack:
		m_2dTex->DrawTexture(m_hSquatAttack[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::Damage:
	case State::DamageEffect:
	case State::Blowoff:
		m_2dTex->DrawTexture(m_hHit, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		if (m_isBurning)
			m_2dTex->DrawTexARGB(m_hHit, m_obj.pos.x - GetCameraPos, m_obj.pos.y, red, true, m_obj.rot, 1.0f, m_obj.isReverse);
		break;

	case State::DashAttack:
	case State::WeakAttack:
	case State::WeakDerivationAttack:
	case State::StrongAttack:
	case State::SpecialAttack:
	case State::AttackSpecialPursuit:
	case State::RaidAttack:
	case State::BeforBattle:
	case State::UnderAttack:
	case State::MediumAttack:
	case State::SpecialProduction:
		m_2dTex->DrawTexture(m_hAttack[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::JumpAttack:
	case State::StrongDerivationAttack:
		m_2dTex->DrawTexture(m_hJumpAttack[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;
		
	case State::Ko:
	case State::Down:
		m_2dTex->DrawTexture(m_hDown, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	case State::Win:
		m_2dTex->DrawTexture(m_hWin[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, false, m_obj.isReverse);
		break;

	default:
		break;
	}
}

/**
* @brief 前進
*/
void Lilia::Advance()
{
	SetSpeed(GetChrPrm->LiliaAdvanceSpeed);
}

/**
* @brief ガード
*/
void Lilia::Guard()
{
	SetSpeed(GetChrPrm->PlayerGuardNowSpeed);
}

/**
* @brief ガード中
*/
void Lilia::GuardNow()
{
	switch (m_subWork)
	{
	case 0:
		// 効果音の再生
		SoundPlayer::GetInstance()->Play(GUARD_SE);
		// ガードエフェクトの生成
		EffectManager::GetInstance()->Add(make_shared<GuardEffect>(m_obj.pos, m_obj.direction));
		SetSpeed(GetChrPrm->LiliaGuardSpeed);

		m_subWork++;
		break;

	case 1:
		SetSpeed();

		if (m_subFrame >= 5)
		{
			if (!IsJump())
				SetState(State::JumpGuard);
			else
				SetState(State::Guard);

			m_subWork = 0;
			m_subFrame = 0;
		}
		m_subFrame++;
		break;
	}
}

/**
* @brief しゃがみガード中
*/
void Lilia::SquatGuardNow()
{
	switch (m_subWork)
	{
	case 0: // 初期化
		SoundPlayer::GetInstance()->Play(GUARD_SE);
		// ガードエフェクトの生成
		EffectManager::GetInstance()->Add(make_shared<GuardEffect>(m_obj.pos, m_obj.direction));
		SetSpeed(-CHARACTER_GUARD_VX);

		m_subWork++;
		break;

	case 1:
		SetSpeed();
		if (m_subFrame >= 5)
		{
			SetState(State::Squat);
			m_subWork = 0;
			m_subFrame = 0;
		}
		m_subFrame++;
		break;
	}
}

/**
* @brief ジャンプ
*/
void Lilia::Jump()
{
	// ジャンプ出来る回数が０なら速度を設定しない
	if (m_jumpCount == 0) {
		m_subWork = 1;
	}

	switch (m_subWork)
	{
	case 0: // パラメータ設定
		switch (m_state)
		{
		case State::Jump:
			SetSpeed(0.0f, JUMP_VY);
			break;

		case State::JumpFront:
			// 右向き
			if (m_obj.direction == Dir::Right)
				SetSpeed(m_oldSpd.x, JUMP_VY);
			// 左向き
			else
				SetSpeed(-m_oldSpd.x, JUMP_VY);
			break;

		case State::JumpBack:
			// 左右の補正はいらない
			SetSpeed(-4.0f, JUMP_VY);
			break;
		}
		// 進める
		m_subWork++;
		break;

	case 1: // アクション

		// 地面に接していたら
		if (m_obj.pos.y >= GetPrm->Ground){
			SetState(State::Neutral);
		}

		if (m_jumpCount > 0){
			m_jumpCount--;
		}
		break;
	}
}

/**
* @brief 操作可能か否か
* @return true - 操作可能
*         false - 操作不能
*/
bool Lilia::isControll()
{
	return m_isControll;
}

/**
* @brief 炎上
*/
void Lilia::SetBurning()
{
	m_isBurning = true;
}

/**
* @brief 上段攻撃が当たったか
*/
bool Lilia::isUpperAttackHit(const IPlayer& enemy)
{
	ARGB red = { 255, 255, 0, 0 };
	ARGB blue = { 255, 0, 0, 255 };

	// 上段攻撃じゃなかったら何もしない
	if (m_attackPoint != AttackPoint::Upper) return false;

	// 攻撃判定が発生していなかったら何もしない
	if (!m_isAttackJudge) return false;

	// 当たりフラグ
	bool isHit = false;

	// 当たったら
	if (Collide::CheckRectAndRect(m_obj.pos, enemy.GetPos(), m_attackRect, enemy.GetHitRect()))
	{
		// 先に攻撃判定を切る
		m_isAttackJudge = false;

		// 相手がガード状態またはガード中なら
		if (enemy.GetState() == State::Guard || enemy.GetState() == State::GuardNow){
			// 当たったフラグを返して処理を終了する
			return true;
		}
		
		// ヒット効果音再生調整用
		static unsigned int hitSECount = 0;
		hitSECount++;

		// 攻撃成功
		m_isAttackSuccess = true;
		// 当たった
		isHit = true;

		switch (m_state)
		{
		case State::WeakAttack:
		case State::MediumAttack:
		case State::SpecialProduction:
			// ヒット音
			SoundPlayer::GetInstance()->Play(BLADE_SE);
			// エフェクトを生成する
			EffectManager::GetInstance()->Add(make_shared<SlashEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), m_obj.direction, Vector2(20.0f), 3.5f, -0.25f));
			EffectManager::GetInstance()->Add(make_shared<SlashEffect2>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 170.0f), m_obj.direction, Vector2(0.0f, -20.0f), 90.0f));
			EffectManager::GetInstance()->Add(make_shared<SlashEffect2>(Vector2(enemy.GetPos().x + 300.0f, enemy.GetPos().y + 30.0f), m_obj.direction, Vector2(20.0f, 0.0f), 0.0f));
			EffectManager::GetInstance()->Add(make_shared<SlashEffect2>(Vector2(enemy.GetPos().x - 300.0f, enemy.GetPos().y + 30.0f), m_obj.direction, Vector2(-20.0f, 0.0f), 0.0f));
			// 10個重ねる
			for (int i = 0; i < 10; i++){
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), red, 0.1f));
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), blue, 0.07f));
			}
			break;

		case State::StrongAttack:
			// リセットをかける
			//			ActionReset();
			// 速度を初期化
			SetSpeed();
			// 制御不可にする
			m_isControll = false;
			// ヒット音
			SoundPlayer::GetInstance()->Play(SWORDBLOW_SE);
			// 被弾フレームを加算する
			m_damageFrame++;

			// ヒット音
			if (hitSECount % 7 == 0){
				SoundPlayer::GetInstance()->Play(FLAME_SE);
			}
			// 火パーティクル
			for (int i = 0; i < 55; i++){
				ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(enemy.GetPos().x, enemy.GetPos().y + 100.0f), 1.3f));
				ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(enemy.GetPos().x - 10.0f, enemy.GetPos().y + 100.0f), 1.3f));
				ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(enemy.GetPos().x + 10.0f, enemy.GetPos().y + 100.0f), 1.3f));
			}

			if (m_damageFrame > 30){
				m_damageFrame = 0;
				EffectManager::GetInstance()->Add(make_shared<BurstRingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y + 100.0f)));
				SetState(State::StrongDerivationAttack);
			}
			break;

		case State::StrongDerivationAttack:
			// 多段ヒットさせるようにフラグを強制的にＯＮにする
			m_isAttackJudge = true;
			break;

		case State::WeakDerivationAttack:
			SoundPlayer::GetInstance()->Play(BLADE_SE);
			EffectManager::GetInstance()->Add(make_shared<SlashEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), m_obj.direction, Vector2(20.0f, 0.0f), 1.0f, 0.0f, -45.0f));
			// 10個重ねる
			for (int i = 0; i < 10; i++){
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50), red, 0.1f));
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50), blue, 0.07f));
			}
			break;
	
		case State::DashAttack:
		case State::RaidAttack:
			SoundPlayer::GetInstance()->Play(BLADE_SE);
			for (int p = 0; p < 10; p++)
				ParticleManager::GetInstance()->Add(make_shared<HitParticle>(enemy.GetPos(), 0.35f));
			break;

		case State::JumpAttack:
			SoundPlayer::GetInstance()->Play(BLADE_SE);
			EffectManager::GetInstance()->Add(make_shared<SlashEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), m_obj.direction, Vector2(20.0f), 3.5f, -0.25f));
			// 10個重ねる
			for (int i = 0; i < 10; i++){
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(enemy.GetPos(), red, 0.1f));
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(enemy.GetPos(), blue, 0.07f));
			}
			break;

		case State::AttackSpecialPursuit:
			SoundPlayer::GetInstance()->Play(BOMB_SE);
			EffectManager::GetInstance()->Add(make_shared<FlushEffect>(enemy.GetPos()));
			break;
		}
	}
	return isHit;
}

/**
* @brief 下段攻撃が当たったか
*/
bool Lilia::isLowerAttackHit(const IPlayer& enemy)
{
	// 下段攻撃じゃなかったら何もしない
	if (m_attackPoint != AttackPoint::Lower) return false;

	// 攻撃判定が発生していなかったら何もしない
	if (!m_isAttackJudge) return false;

	// 当たりフラグ
	bool isHit = false;

	// 当たったら
	if (Collide::CheckRectAndRect(m_obj.pos, enemy.GetPos(), m_attackRect, enemy.GetHitRect()))
	{
		// 先に攻撃判定を切る
		m_isAttackJudge = false;

		// 相手がガード状態またはガード中なら
		if (enemy.GetState() == State::SquatGuard || enemy.GetState() == State::SquatGuardNow){
			// 当たったフラグを返して処理を終了する
			return true;
		}

		// 攻撃成功
		m_isAttackSuccess = true;
		// 当たった
		isHit = true;

		switch (m_state)
		{
		case State::SquatAttack:
			SoundPlayer::GetInstance()->Play(SWORDBLOW_SE);
			// パーティクル生成
			for (int i = 0; i < 10; i++)
				ParticleManager::GetInstance()->Add(make_shared<HitParticle>(enemy.GetPos(), 0.3f));
			break;
		}
	}

	return isHit;
}

/**
* @brief 被弾
*/
void Lilia::Damage(const IPlayer& attacker, AttackPoint hitType)
{
	switch (hitType)
	{
	case AttackPoint::Upper:
		// ガード状態またはガード中なら
		if (m_state == State::Guard || m_state == State::GuardNow)
		{
			SetState(State::GuardNow);
			// パーティクルを生成する
			for (int i = 0; i < 7; i++){
				ParticleManager::GetInstance()->Add(make_shared<GuardParticle>(m_obj.pos, 0.3f));
			}
			// 以降の処理はしない
			return;
		}
		break;

	case AttackPoint::Lower:
		if (m_state == State::SquatGuard || m_state == State::SquatGuardNow)
		{
			SetState(State::SquatGuardNow);
			// パーティクルを生成する
			for (int i = 0; i < 7; i++){
				ParticleManager::GetInstance()->Add(make_shared<GuardParticle>(m_obj.pos, 0.3f));
			}
			// 以降の処理はしない
			return;
		}
		break;

	default:
		Utility::abortWithMsg("被弾タイプが存在しません。");
		break;
	}
	
	// 無敵状態でも以降の処理はしない
	if (m_isInvincible){
		return;
	}

	// ダウン状態ならダウンのままにしておく
	if (m_state == State::Down) {
		SetState(State::Down);
	}

	// 攻撃者の状態
	switch (attacker.GetState())
	{
	case State::WeakAttack:
	case State::MediumAttack:
		SetState(State::Damage);
		// 仰け反り
		SetSpeed(-0.4f);
		m_knockbackFrame = 30;
		// 空中にいたら少し浮かす
		if (m_obj.pos.y < GetPrm->Ground){
			SetSpeed(0.0f, -3.0f);
		}
		break;

	case State::StrongAttack: 
		m_knockbackFrame = 60;
		SetSpeed();
		SetState(State::Damage);
		// 操作不能
		m_isControll = false;
		// アルファ値を抜く
		m_obj.alpha = ALPHA_MIN;
		// 燃やす
		m_isBurning = true;
		break;

	case State::StrongDerivationAttack:
		// のけぞりフレーム
		m_knockbackFrame = 90;
		m_downFrame = 90;
		// アルファ値を抜く
		m_obj.alpha = ALPHA_MIN;
		// 吹き飛び状態にする
		SetState(State::Blowoff);
		SetSpeed(-3.0f, -23.0f);
		break;

	case State::WeakDerivationAttack:
		SetSpeed(-20.0f, -7.0f);
		// のけぞりフレーム
		m_knockbackFrame = 30;
		m_downFrame = 20;
		SetState(State::Blowoff);
		break;

	case State::DashAttack:
	case State::RaidAttack:
		m_downFrame = 30;
		if (attacker.GetState() == State::RaidAttack){
			SetSpeed(-6.0f, -13.0f);
		}
		else if (attacker.GetState() == State::DashAttack){
			SetSpeed(-6.0f, -10.0f);
		}
		SetState(State::Blowoff);
		break;

	case State::JumpAttack:
		m_knockbackFrame = 15;
		SetState(State::Damage);
		if (m_obj.pos.y < GetPrm->Ground){
			SetSpeed(0.0f, -3.0f);
		}
		break;

	case State::AttackSpecialPursuit:
		SetSpeed(0.0f, -20.0f);
		m_downFrame = 60;
		if (m_state == State::Down){
			m_state = State::Down;
		}
		else{
			m_state = State::Blowoff;
		}
		break;

	case State::SquatAttack:
		SoundPlayer::GetInstance()->Play(SWORDBLOW_SE);
		m_knockbackFrame = 15;
		SetState(State::Damage);
		SetSpeed(-0.4f);
		break;

	case State::SpecialProduction:
		// 吹き飛び
		SetSpeed(-14.0f, -17.0f);
		// KO状態のまま
		SetState(State::Ko);
	}
}

/**
* @brief ダウン状態か否か
*/
bool Lilia::isDown()
{
	return false;
}

/**
* @brief ジャンプ出来るか否かの判定
*/
bool Lilia::IsJump()
{
	return(m_isFloor && m_jumpCount > 0 ? true : false);
}

/**
* @brief 受身を取れるかの判定
*/
bool Lilia::CanPassive()
{
	return m_isPassive;
}

/**
* @brief 追撃(派生技)が可能か
*/
bool Lilia::CanDerivation()
{
	return m_isDerivation;
}

/**
* @brief 位置を設定
*/
void Lilia::SetPos(const Vector2& pos)
{
	m_obj.pos = pos;
}

/**
* @brief 状態を設定
*/
void Lilia::SetState(const State state)
{
	m_state = state;
}

/**
* @brief 向きを設定
*/
void Lilia::SetDirection(const Dir& dir)
{
	m_obj.direction = dir;
}

/**
* @brief プレイヤー番号を取得
*/
const unsigned int Lilia::GetID() const
{
	return m_id;
}

/**
* @brief 攻撃力を取得
*/
const float Lilia::GetPower() const
{
	return m_power;
}

/**
* @brief 位置を取得
*/
const Vector2& Lilia::GetPos() const
{
	return m_obj.pos;
}

/**
* @brief 状態を取得
*/
const State Lilia::GetState() const
{
	return m_state;
}

/**
* @brief 攻撃範囲を取得
*/
const Rect Lilia::GetAttackRect() const
{
	return m_attackRect;
}

/**
* @brief ヒット範囲を取得
*/
const Rect Lilia::GetHitRect() const
{
	return m_hitRect;
}

/**
* @brief 向きを取得
*/
const Dir Lilia::GetDirection() const
{
	return m_obj.direction;
}

/**
* @brief 攻撃判定発生中か否か
*/
bool Lilia::isAttackJudge()
{
	return m_isAttackJudge;
}


#pragma endregion



/**
* @brief 待機更新
*/
void Lilia::Neutral()
{
	// 速度0 初期化
	SetSpeed();

	// ヒット判定
	m_hitRect = { 0, 0, 140, 140 };

	if (m_subFrame % 10 == 0)
	{
		m_animation++;
		if (m_animation >= 3)
			m_animation = 0;
	}

	m_subFrame++;
}


/**
* @brief ダッシュ更新
*/
void Lilia::Dash()
{
	SetSpeed(GetChrPrm->LiliaDashSpeed);
}

/**
* @brief 後退更新
*/
void Lilia::BackStep()
{
	if (m_subFrame == 0){
		// 制御不能
		m_isControll = false;
		
		SetSpeed(GetChrPrm->LiliaBackStepSpeed);
	}

	if (m_subFrame > 12){
		// 制御可能
		m_isControll = true;

		// ステイトを戻す
		SetState(State::Guard);
	}

	// フレームを増やす
	m_subFrame++;
}


/**
* @brief しゃがみ
*/
void Lilia::Squat()
{
	// 速度０
	SetSpeed();
	// 当たり判定セット
	m_hitRect = { 0, 70, 140, 140 };
	m_animation = 0;
}

/**
* @brief しゃがみ攻撃
*/
void Lilia::SquatAttack()
{
	switch (m_subWork)
	{
	case 0: // 初期化
		// 上段攻撃
		m_attackPoint = AttackPoint::Lower;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackSquatPower;
		// ボイスの再生
		SoundPlayer::GetInstance()->Play(LILIA_SQUATATTACK_VOICE);

		float x;
		if (m_obj.direction == Dir::Right){
			x = 9.0f;
		} else {
			x = -9.0f;
		}
		// ループで重ねてエフェクトを生成する
		for (int i = 0; i < 5; i++){
			EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>
				(29, Vector2(m_obj.pos.x + x + i, m_obj.pos.y + 80.0f), m_obj.direction));
										// ↑[ｘ]で座標をズラして[ｉ]でループの値だけズラしてる
		}
		// 制御不能
		m_isControll = false;
		// 速度０初期化
		SetSpeed();
		
		m_subWork++;
		break;

	case 1:
		if (m_subFrame > 3){
			// アニメーションを回す
			m_animation = 0;
			// 当たり判定の生成
			m_attackRect = { 0, 0, 200, 150 };
			m_isAttackJudge = true;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame > 7){
			m_animation = 1;
			m_subWork++;
		}
		break;

	case 3:
		// 当たり判定を先に消滅させておく
		m_isAttackJudge = false;
		// アニメーション番号
		m_animation = 2;

		if (m_subFrame > 12){
			// リセット
			ActionReset();
		}
		break;
	default:
		Utility::abortWithMsg("存在しない攻撃状態になりました。終了します。");
		break;
	}

	// フレーム加算
	m_subFrame++;
}

/**
* @brief ダッシュ攻撃
*/
void Lilia::DashAttack()
{
	switch (m_subWork)
	{
	case 0:
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackDashPower;
		// ボイスを再生
		SoundPlayer::GetInstance()->Play(LILIA_DASHATTACK_VOICE);
		// 制御不可
		m_isControll = false;
		// アニメーションセット
		m_animation = 1;
		// 当たり判定の生成
		m_attackRect = { 0, 0, 200, 200 };
		m_isAttackJudge = true;
		m_subWork++;
		break;

	case 1:
		// 減速をさせる
		m_spd.x = Utility::Friction(m_spd.x, 0.95f);

		if (m_subFrame > 30){
			// 当たり判定の消滅
			m_isAttackJudge = false;
			m_subWork++;
		}
		break;

	case 2:
		// 減速をさせる
		m_spd.x = Utility::Friction(m_spd.x, 0.95f);

		// 硬直
		if (m_subFrame > 60){
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	default:
		Utility::abortWithMsg("存在しない攻撃状態になりました。終了します。");
		break;
	}
	// フレームの加算
	m_subFrame++;
}

/**
* @brief ジャンプ攻撃
*/
void Lilia::JumpAttack()
{
	switch (m_subWork)
	{
	case 0:
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackJumpPower;
		// アニメーションの設定
		m_animation = 0;
		// 効果音とボイスの再生
		SoundPlayer::GetInstance()->Play(SWORDSWING_SE);
		SoundPlayer::GetInstance()->Play(LILIA_JUMPATTACK_VOICE);
		// エフェクトを重ねて描画する
		EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>(31, Vector2(m_obj.pos.x, m_obj.pos.y + 60.0f), m_obj.direction));
		EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>(31, Vector2(m_obj.pos.x, m_obj.pos.y + 60.0f), m_obj.direction));
		m_subWork++;
		break;

	case 1:
		if (m_subFrame > 5){
			// アニメーションの設定
			m_animation = 1;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame > 9){
			// 当たり判定の生成
			m_attackRect = { 0.0f, 0.0f, 250.0f, 150.0f };
			m_isAttackJudge = true;
			// アニメーションの設定
			m_animation = 2;
			m_subWork++;
		}
		break;

	case 3:
		if (m_subFrame > 24){
			// サブワークとフレームのみ初期化
			m_subWork = 0;
			m_subFrame = 0;
			m_isAttackJudge = false;
			// 状態をジャンプに戻す
			SetState(State::Jump);
		}
		break;
	default:
		Utility::abortWithMsg("存在しない攻撃状態になりました。終了します。");
		break;
	}

	// 攻撃中に地面に付いた場合は初期化
	if (m_obj.pos.y >= GetPrm->Ground){
		SetState(State::Neutral);
		ActionReset();
	}

	m_subFrame++;
}

/**
* @brief ダウン状態
*/
void Lilia::Down()
{
	switch (m_subWork)
	{
	case 0:
		// 効果音を再生
		SoundPlayer::GetInstance()->Play(DOWN_SE);
		EffectManager::GetInstance()->Add(make_shared<SmokeEffect>(Vector2(m_obj.pos.x, m_obj.pos.y + 120.0f)));
		m_isControll = false;
		m_subWork++;
		break;
	case 1:
		if (m_downFrame < 25)
			m_isInvincible = true;

		// ダウンフレームが０且つキャラクターが地面に付いていたらリセット
		if (m_downFrame < 0 && m_obj.pos.y >= GetPrm->Ground)
		{
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	}

	m_downFrame--;
}

/**
* @brief 仰け反り
*/
void Lilia::Knockback()
{
	switch (m_subWork)
	{
	case 0: // 初期化
		if (m_state == State::DamageEffect){
			m_state = State::Damage;
			m_knockbackFrame = 25;
		}
		m_subWork++;
		break;

	case 1:
		if (m_knockbackFrame < 0){
			// リセットしておく
			ActionReset();

			// 地上にいたら
			if (m_obj.pos.y >= GetPrm->Ground)
				SetState(State::Neutral);
			// 空中にいたら
			else
				SetState(State::Jump);
		}
		break;
	}

	// フレームを減算
	m_knockbackFrame--;
}

/**
* @brief 弱攻撃
*/
void Lilia::WeakAttack()
{
	// ジャンプ中なら通常弱攻撃には入らない
	if (!IsJump()) return;

	switch (m_subWork)
	{
	case 0:
	{
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackWeakPower;

		// 音声の再生
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKWEAK_VOICE);
		SoundPlayer::GetInstance()->Play(SWORDSWING_SE);

		// キャラクターの向きによってズラす値と角度を変える
		float x = 0.0f, rot = 0.0f;
		// 右向き
		if (m_obj.direction == Dir::Right){
			rot = 15.0f;
			x = 9.0f;
		} // 左向き
		else{
			rot -= 15.0f;
			x -= 9.0f;
		}
		// ループで重ねてエフェクトを生成する
		for (int i = 0; i < 5; i++){
			EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>
				(29, Vector2(m_obj.pos.x + x + i, m_obj.pos.y + 35.0f), m_obj.direction, rot));
										// ↑[ｘ]で座標をズラして[ｉ]でループの値だけズラしてる
		}

		// 操作不能
		m_isControll = false;
		// 速度を０にする
		SetSpeed();
		// アニメーション設定
		m_animation = 0;
		m_subWork++;
		break;
	}

	case 1:
		if (m_subFrame > 5){
			m_animation = 1;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame > 9){
			// 当たり判定を生成
			m_attackRect = { 0, 0, 250, 150 };
			m_isAttackJudge = true;
			// アニメーション番号
			m_animation = 2;
			m_subWork++;
		}
		break;

	case 3:
		// 当たり判定を先に消滅させる
		m_isAttackJudge = false;
		// 硬直
		if (m_subFrame > 24){
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	default:
		Utility::abortWithMsg("存在しない攻撃状態になりました。終了します。");
		break;
	}

	// 攻撃がヒットしたら
	if (m_isAttackSuccess){
		// 派生技に移れる
		m_isDerivation = true;
	}

	// フレームをまわす
	m_subFrame++;
}

/**
* @brief 弱攻撃派生技
*/
void Lilia::WeakAttackDerivation()
{
	switch (m_subWork)
	{
	case 0:
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 攻撃力を設定
		m_power = GetChrPrm->LiliaAttackWeakDerivationPower;
		// 当たり判定を生成
		m_isAttackJudge = true;
		m_attackRect = { 0, 0, 200, 200 };
		// 速度の設定
		SetSpeed(10.0f);
		// アニメーションの設定
		m_animation = 1;
		// ボイスを再生する
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKWEAK_DER_VOICE);
		// 操作不可
		m_isControll = false;

		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 35)
		{
			// リセット
			ActionReset();
			SetState(State::Neutral);
		}
		m_subFrame++;
		break;
	}
}

/**
* @brief 中攻撃
*/
void Lilia::MediumAttack()
{
	switch (m_subWork)
	{
	case 0: // 初期化
		// リセットしておく
		ActionReset();
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackMediumPower;
		SoundPlayer::GetInstance()->Play(LILIA_JUMPATTACK_VOICE); // ジャンプ用ボイス流用
		// 制御不能
		m_isControll = false;
		// アニメーションの設定
		m_animation = 5;
		SetSpeed();
		m_subWork++;
		break;

	case 1:
		if (m_subFrame > 4){
			// アニメーションの設定
			m_animation = 4;
			// 当たり判定の生成
			m_attackRect = { 0, 0, 200, 200 };
			m_isAttackJudge = true;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame > 10){
			// アニメーションの設定
			m_animation = 3;
			m_subWork++;
		}
		break;

	case 3:
		m_isAttackJudge = false;
		if (m_subFrame > 30){
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	default:
		Utility::abortWithMsg("存在しない攻撃状態になりました。終了します。");
		break;
	}
	m_subFrame++;
}

/**
* @brief 強攻撃
*/
void Lilia::StrongAttack()
{
	// ボイス再生乱数用
	static int r;

	switch (m_subWork)
	{
	case 0: // 初期化
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 制御不可
		m_isControll = false;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackStrongPower;
		// 当たり判定の生成
		m_isAttackJudge = true;
		m_attackRect = { 0, 0, 200, 200 };
		// アニメーションの設定
		m_animation = 1;
		// 乱数生成
		r = Utility::Random(0, 1);
		// 乱数で再生するボイスを変更する
		if (r == 0) SoundPlayer::GetInstance()->Play(LILIA_ATTACKSTRONG_VOICE);
		if (r == 1) SoundPlayer::GetInstance()->Play(LILIA_ATTACKSTRONG_VOICE2);
		// 速度の設定
		SetSpeed(GetChrPrm->LiliaAttackStrongSpeed);

		m_subWork++;
		break;

	case 1: // 攻撃中
		if (m_subFrame > 30){
			m_isAttackJudge = false;
			SetState(State::Neutral);
			ActionReset();
		}

		if (m_isAttackSuccess){
			m_subWork++;
		}
		break;

	case 2:
		// 多段ヒットさせるようにフラグを強制的にＯＮにする
		m_isAttackJudge = true;
		SetSpeed();
		break;
	}
	m_subFrame++;
}

/**
* @brief 強攻撃派生技
*/
void Lilia::StrongAttackDerivation()
{
	switch (m_subWork)
	{
	case 0:
		// 制御不可
		m_isControll = false;
		m_attackRect = { 0, 0, 200, 200 };
		// アニメーションの設定
		m_animation = 1;
		m_subWork++;
		break;

	case 1:
		SetSpeed(2.0f, -15.0f);
		m_subWork++;
		break;

	case 2:
		ActionReset();
		SetState(State::Jump);
		break;
	}

	// フレームを加算する
	m_subFrame++;
}

/**
* @brief 遠距離攻撃
*/
void Lilia::LongAttack()
{
	if (!IsJump()) return;

	switch (m_subWork)
	{
	case 0:
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackLongPower;
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKWEAK_VOICE);
		m_isControll = false;
		m_animation = 5;
		// 速度を初期化
		SetSpeed();
		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 15){
			m_subWork++;
		}
		break;

	case 2:
		m_animation = 4;

		if (m_subFrame >= 18){
			CollisionEffectManager::GetInstance()->Add(make_shared<FireEffect>(m_id, m_obj.pos, m_obj.direction));
			m_subWork++;
		}
		break;

	case 3:
		m_animation = 3;
		m_subWork++;
		break;

	case 4:
		// 硬直
		if (m_subFrame >= 58)
		{
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	}

	m_subFrame++;
}

/**
* @brief 必殺技
*/
void Lilia::SpecialAttack()
{
	// アニメーション調整用フレーム
	static int adjustFrame;

	switch (m_subWork)
	{
	case 0: // 初期化
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 速度を０にする
		SetSpeed();
		// 操作不可状態にする
		m_isControll = false;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackSpecialPower;
		// カットインを設定する
		CutInManager::GetInstance()->Create(LILIA, m_id, m_obj.pos);

		// ボイスの再生
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_VOICE);

		m_subWork++;
		break;

	case 1:
		// カットインが消えるのを待つ
		if (!CutInManager::GetInstance()->IsPlayCutIn()){
			m_subWork++;
		}
		break;

	case 2: 
		// 無敵フラグをセット
		m_isInvincible = true;
		// ボイスの再生
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_VOICE3);
		m_subWork++;
		adjustFrame = 10;
		EffectManager::GetInstance()->Add(make_shared<WaveEffect>(m_obj.pos, m_obj.direction));
		break;

	case 3:
		// 攻撃用エフェクトを生成する
		SpecialAttackCreateEffect();

		// フレームが経過する毎にアニメーションを加速させていく処理
		if (m_subFrame % adjustFrame == 0)
		{
			// エフェクトを生成する
			EffectManager::GetInstance()->Add(make_shared<LightLineEffect>(m_obj.pos));
			m_animation++;
			if (m_animation >= 3){
				adjustFrame--;
				m_animation = 0;
			}
		}
		// 0以下になったら
		if (adjustFrame <= 0)
		{
			// 調整フレームを1で固定
			adjustFrame = 1;
			// 斬撃カウントを加算する
			m_slashingCount++;
			// 16回以下なら処理を続ける
			if (m_slashingCount > GetChrPrm->LiliaSlashingCountMax){
				m_subWork++;
			}
		}
		break;

	case 4: // 必殺技追撃状態に入る前にパラメータをリセットしておく
		// 無敵フラグを折る
		m_isInvincible = false;
		m_slashingCount = 0;
		adjustFrame = 10;
		// 一度リセットをかける
		ActionReset();
		// 制御不能
		m_isControll = false;
		SetState(State::AttackSpecialPursuit);
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_PUR_VOICE);
		break;
	}
	// フレームを加算
	m_subFrame++;
}

/**
* @brief 必殺技追撃
* @note  必殺技が終わると自動的にこのアクションに入る
*/
void Lilia::SpecialPursuitAttack()
{
	switch (m_subWork)
	{
	case 0:
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 当たり判定の生成
		m_attackRect = { 0, 0, 250, 250 };
		m_isAttackJudge = true;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackSpecialPursuitPower;
		// アニメーションの設定
		m_animation = 1;
		// 速度の設定
		SetSpeed(GetChrPrm->LiliaAttackSpecialPursuitSpeed);
		m_subWork++;
		break;

	case 1:
		// 攻撃判定発生時間
		if (m_subFrame > 40){

			// 攻撃が成功
			if (m_isAttackSuccess){
				SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_SUCCESS);
			}
			else {
				ActionReset();
				SetState(State::Neutral);
			}
			// 当たり判定の削除
			m_isAttackJudge = false;
			// 速度初期化
			SetSpeed();
			m_subWork++;
		}
		break;
		
	case 2:
		if (m_subFrame > 150){
			// 当たり判定の削除
			m_isAttackJudge = false;
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
	// フレームを加算
	m_subFrame++;
}

/**
* @brief 奇襲攻撃
*/
void Lilia::RaidAttack()
{
	switch (m_subWork)
	{
	case 0:
		// 上段攻撃
		m_attackPoint = AttackPoint::Upper;
		// 操作不能
		m_isControll = false;	
		// ボイスの作成
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKMEDIUM_VOICE);
		SoundPlayer::GetInstance()->Play(SETUPMOTION_SE);
		// エフェクト作成
		EffectManager::GetInstance()->Add(make_shared<LightEffect>(m_obj.pos));
		// アニメーションの設定
		m_animation = 0;
		// 攻撃力の設定
		m_power = GetChrPrm->LiliaAttackRaidPower;
		m_subWork++;
		break;

	case 1:
		// 発生まで15フレーム
		if (m_subFrame >= 15){
			m_subWork++;
			m_subFrame = 0;
		}
		break;

	case 2:
		// 当たり判定の生成
		m_attackRect = { 0, 0, 200, 200 };
		m_isAttackJudge = true;

		// アニメーションの設定
		m_animation = 1;
		// 速度の設定
		SetSpeed(ATTACK_RAID_VX);
		m_subWork++;
		break;

	case 3:
		// 減速率
		m_spd.x = Utility::Friction(m_spd.x, 0.9f);

		if (m_subFrame >= 35){
			// アニメーション設定
			m_animation = 0;
			m_subWork++;
		}
		break;

	case 4:
		// 減速率
		m_spd.x = Utility::Friction(m_spd.x, 0.9f);

		// 硬直
		if (m_subFrame >= 75){
			m_isAttackJudge = false;
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	}
	// フレーム更新
	m_subFrame++;
}

/**
* @brief 吹き飛び
*/
void Lilia::BlowOff()
{
	switch (m_subWork)
	{
	case 0:
		// 操作不可
		m_isControll = false;
		m_subWork++;
		break;

	case 1:
		// 角度加算
		AddAngle(BLOWOFF_ADD_ANGLE);

		// 端に当たったら跳ね返る
		if (m_obj.pos.x >= CAMERA_END_RIGHT - CHARACTER_MARGIN + GetCameraPos ||
			m_obj.pos.x <= CAMERA_END_LEFT + CHARACTER_MARGIN + GetCameraPos)
		{
			m_spd.x = Utility::Rebound(m_spd.x, 0.2f);
		}

		// これを書かないと空中状態で吹き飛ぶとバグるので救済処置用として記述
		if (m_obj.pos.y > GetPrm->Ground) m_obj.pos.y = GetPrm->Ground;

		if (m_obj.pos.y == GetPrm->Ground){
			// 地面に付いた瞬間だけ受身が取れる
			m_isPassive = true;
			m_subWork++;
		}
		break;

	case 2:
		// 受身フラグ消滅
		m_isPassive = false;
		// リセット
		ActionReset();
		// ダウン状態
		SetState(State::Down);

		// 摩擦
		m_spd.x = Utility::Friction(m_spd.x, 0.55f);
		// バウンド
		m_spd.y = Utility::Rebound(m_spd.y, 0.2f);

		break;
	}

	// フレームをまわす
	m_subFrame++;
}

/**
* @brief 相殺
*/
void Lilia::Offset()
{
	switch (m_subWork)
	{
	case 0:
		m_isControll = false;
		m_subWork++;
		break;

	case 1:
		SetSpeed(-OFFSET_VX);
		m_subWork++;
		break;

	case 2:
		// 摩擦係数
		m_spd.x = Utility::Friction(m_spd.x, 0.85f);

		if (m_subFrame >= 30)
		{
			// パラメータ初期化
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
	// フレーム加算
	m_subFrame++;
}

/**
* @brief 受身
*/
void Lilia::Passive()
{
	switch (m_subWork)
	{
	case 0: // パラメータを初期化する
		// 受身フラグ消滅
		m_isPassive = false;
		ActionReset();
		m_subWork++;
		break;

	case 1: // 速度とボイスを設定する
		SetSpeed(-PASSIVE_VX, -PASSIVE_VY);
		SoundPlayer::GetInstance()->Play(LILIA_PASSIVE_VOICE);
		m_subWork++;
		break;

	case 2:
		// 地面に着いたら
		if (m_obj.pos.y >= GetPrm->Ground){
			// パラメータを初期化
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
}

/**
* @brief バトル開始前
*/
void Lilia::BeforeBattle()
{
	switch (m_subWork)
	{
	case 0:
		m_animation = 0;

		// 操作不能にする
		m_isControll = false;
		SoundPlayer::GetInstance()->Play(LILIA_BEFOREBATTLE_VOICE);
		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 120){
			m_animation = 1;
			m_subWork++;
		}
		break;

	case 2:
		// リセット
		ActionReset();
		SetState(State::Neutral);
		break;
	}

	// 行動フレームを加算
	m_subFrame++;
}

/**
* @brief ノックアウト
*/
void Lilia::KO()
{
	switch (m_subWork)
	{
	case 0:
		m_isControll = false;
		m_subWork++;
		break;

	case 1:
		// 地面に着いていたら
		if (m_obj.pos.y >= GetPrm->Ground)
		{
			SetSpeed(-KO_VX, -KO_VY);
		}
		// 空中にいたら
		else
		{
			SetSpeed(-KO_VX, m_spd.y);
		}

		m_subWork++;
		break;

	case 2:
		// 地面に着いたら
		if (m_obj.pos.y >= GetPrm->Ground)
		{
			// 速度初期化
			SetSpeed();
			m_subWork++;
		}
		break;

	case 3:
		// 何もしない
		break;
	}
}

/**
* @brief 勝利
*/
void Lilia::Win()
{
	switch (m_subWork)
	{
	case 0:
		// 操作を不能にする
		m_isControll = false;
		m_animation = 0;
		SoundPlayer::GetInstance()->Play(LILIA_WIN_VOICE);
		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 30)
		{
			SetSpeed(0.0f, -WIN_VY);
			m_subWork++;
		}
		break;

	case 2:
		m_animation = 1;
		if (m_subFrame >= 120)
		{
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
	// フレーム加算
	m_subFrame++;
}

/**
* @brief 特殊演出
*/
void Lilia::SpecialProduction()
{
	switch (m_subWork)
	{
	case 0:
		// パラメータをリセットしておく
		ActionReset();
		// 上段
		m_attackPoint = AttackPoint::Upper;
		// 操作不能
		m_isControll = false;
		// アニメーション設定1
		m_animation = 0;

		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 30){
			// 全範囲
			m_attackRect = { 0, 0, 2000, 2000 };
			m_isAttackJudge = true;
			m_animation = 1;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame >= 65){
			m_animation = 2;
			m_subWork++;
		}
		break;

	case 3: // 初期化する
		m_isAttackJudge = false;
		ActionReset();
		SetState(State::Neutral);
		break;
	}
	// 行動フレームを加算する
	m_subFrame++;
}

bool Lilia::CanControll()
{
	if (!IsJump())
		return false;
	if (m_state == State::Damage)
		return false;
	if (m_state == State::DamageEffect)
		return false;
	if (m_state == State::Blowoff)
		return false;
	if (m_state == State::Down)
		return false;
	if (m_state == State::GuardNow)
		return false;
	if (m_state == State::SquatGuardNow)
		return false;
	if (m_state == State::BeforBattle)
		return false;
	if (m_state == State::Win)
		return false;
	if (m_state == State::Passive)
		return false;
	if (m_state == State::Ko)
		return false;

	return true;
}

/**
* @brief パラメータリセット
*        キャラクターの状態が切り替わる時にこの関数を呼ぶ
*/
void Lilia::ActionReset()
{
	// アニメーションリセット
	m_animation = 0;
	// 当たり判定の消滅
	m_attackRect = {};
	// 制御可能状態に
	m_isControll = true;
	// 無敵フラグを消す
	m_isInvincible = false;
	// 当たり判定消滅
	m_isAttackJudge = false;
	// 攻撃成功フラグを消す
	m_isAttackSuccess = false;
	// 追撃フラグを消す
	m_isDerivation = false;
	// 攻撃力を初期化
	m_power = 0.0f;
	// サブワークを頭に戻す
	m_subWork = 0;
	// 各々のフレームを０にする
	m_subFrame = 0;
	// 角度も０に
	m_obj.rot = 0.0f;
}

/**
* @brief 速度の設定(融通が利くようにxとyを別々に設定できるようにしておく)
*        キャラクターが右向きの時は正、左向きの時は負の値が設定される
* @param spx - 横軸の速度(デフォルトは0.0f)
* @param spy - 縦軸の速度(デフォルトは0.0f)
*/
void Lilia::SetSpeed(const float spx, const float spy)
{
	if (m_obj.direction == Dir::Right){
		m_spd.x = spx;
	}
	else if(m_obj.direction == Dir::Left){
		m_spd.x = -spx;
	}

	// y軸は向きに関係なく一律
	m_spd.y = spy;
}

void Lilia::AddAngle(float speed)
{
	static const float LIMIT_ANGLE = 140.0f;
	// 左向き
	if (m_obj.direction == Dir::Left){
		m_obj.rot += speed;
		if (m_obj.rot > LIMIT_ANGLE){
			m_obj.rot = LIMIT_ANGLE;
		}
	}
	// 右向き
	else{
		if (m_obj.rot < -LIMIT_ANGLE){
			m_obj.rot = -LIMIT_ANGLE;
		}
		m_obj.rot -= speed;
	}
}

void Lilia::SpecialAttackCreateEffect()
{
	// 一時変数
	float temp, temp2;

	if (m_obj.direction == Dir::Right) {
		temp = 50.0f;
		temp2 = 70.0f;
	}
	else{
		temp = -50.0f;
		temp2 = -70.0f;
	}
	
	static unsigned short subWork = 0;
	static unsigned int workFrame = 0;
	static unsigned int adjustWorkFrame = 10;

	// ０以下にはならない
	if (adjustWorkFrame < 1) adjustWorkFrame = 1;

	if (workFrame % adjustWorkFrame == 0)
	{
		switch (subWork)
		{
		case 0:
			CollisionEffectManager::GetInstance()->Add(make_shared<SpecialSlashEffect>
				(m_id, Vector2(m_obj.pos.x + temp, m_obj.pos.y - 400.0f), m_obj.direction, Vector2(80.0f), 70.0f));
			adjustWorkFrame--;
			subWork++;
			break;

		case 1:
			CollisionEffectManager::GetInstance()->Add(make_shared<SpecialSlashEffect>
				(m_id, Vector2(m_obj.pos.x + temp, m_obj.pos.y + 50.0f), m_obj.direction,Vector2(100.0f,0.0f)));
			subWork++;
			break;
	
		case 2:
			CollisionEffectManager::GetInstance()->Add(make_shared<SpecialSlashEffect>
				(m_id, Vector2(m_obj.pos.x + temp, m_obj.pos.y - 300.0f), m_obj.direction, Vector2(70.0f), 45.0f));
			CollisionEffectManager::GetInstance()->Add(make_shared<SpecialSlashEffect>
				(m_id, m_obj.pos, m_obj.direction ,Vector2(70.0f), 45.0f));
			subWork++;
			break;

		case 3:
			CollisionEffectManager::GetInstance()->Add(make_shared<SpecialSlashEffect>
				(m_id, Vector2(m_obj.pos.x + temp, m_obj.pos.y - 200.0f), m_obj.direction, Vector2(130.0f), 20.0f));
			adjustWorkFrame--;
			subWork++;
			break;

		case 4:
			CollisionEffectManager::GetInstance()->Add(make_shared<SpecialSlashEffect>
				(m_id, Vector2(m_obj.pos.x + temp, m_obj.pos.y - 300.0f), m_obj.direction, Vector2(55.0f), 45.0f));
			subWork++;
			break;

		case 5:
			subWork++;
			break;

		case 6:
			adjustWorkFrame--;
			subWork = 0;
			break;
		}
	}

	if (m_slashingCount > GetChrPrm->LiliaSlashingCountMax - 1){
		subWork = 0;
		workFrame = 0;
		adjustWorkFrame = 10;
	}

	workFrame++;
}