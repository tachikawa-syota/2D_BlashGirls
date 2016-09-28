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
* @brief �R���X�g���N�^
*/
Lilia::Lilia(int index)
{
	// �C���X�^���X�擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���̃R�s�[
	m_hDown = m_texData->GetLiliaAnim(9);
	m_hHit = m_texData->GetLiliaAnim(10);
	m_hJump = m_texData->GetLiliaAnim(11);
	m_hSquat = m_texData->GetLiliaAnim(18);
	m_hWalk = m_texData->GetLiliaAnim(22);
	m_hWin[0] = m_texData->GetLiliaAnim(23);
	m_hWin[1] = m_texData->GetLiliaAnim(24);

	// �R���A�j���[�V�������ꊇ�ŃR�s�[
	for (int i = 0; i < 3; i++){
		m_hJumpAttack[i] = m_texData->GetLiliaAnim(i + 12);
		m_hNeutral[i] = m_texData->GetLiliaAnim(i + 15);
		m_hSquatAttack[i] = m_texData->GetLiliaAnim(i + 19);
	}
	for (int i = 0; i < 9; i++){
		m_hAttack[i] = m_texData->GetLiliaAnim(i);
	}

	// �p�����[�^�̏�����������
	Initialize(index);
}

/**
* @brief �f�X�g���N�^
*/
Lilia::~Lilia()
{
}

#pragma region IPlayer

/**
* @brief ������
* @param index - �L�����N�^�̔ԍ�
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

	// �L�����N�^�̔ԍ�
	m_id = index;

	// �e��J�E���g�̏�����
	m_jumpCount = 0;
	m_slashingCount = 0;
	m_downFrame = 0;
	m_damageFrame = 0;
	m_knockbackFrame = 0;
	m_subFrame = 0;
	m_subWork = 0;

	m_attackPoint = AttackPoint::None;
	// �U���͂̏�����
	m_power = 0.0f;
	// �����
	m_isControll = true;
	// ���G�ł͂Ȃ�
	m_isInvincible = false;
	// ��g
	m_isPassive = false;
	// �U�����蔭�����ĂȂ�
	m_isAttackJudge = false;
	m_isAttackSuccess = false;
	m_isDerivation = false;

	m_isBurning = false;

	/// �j���[�g�������
	m_state = State::Neutral;
	m_oldState = State::Neutral;

	// �A�j���[�V�����ԍ���0�ɐݒ�
	m_animation = 0;
}


/**
* @brief �X�V
*/
void Lilia::Update()
{
	// ��Ԃ��؂�ւ�����烊�Z�b�g����
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

	// ��Ԃ�ۑ�
	m_oldState = m_state;
	// ���x��ۑ�
	m_oldSpd = m_spd;
	// �d�͂����Z
	m_spd.y += GetPrm->Gravity;
	// �ʒu�ɑ��x�����Z
	m_obj.pos += m_spd;
	
	// �������Ȃ�L�����N�^�[�𔽓]���ĕ`��
	if (m_obj.direction == Dir::Left){
		m_obj.isReverse = true;
	}
	else{
		m_obj.isReverse = false;
	}

	// �ڒn���Ă�����
	if (m_obj.pos.y > GetPrm->Ground)
	{
		// �ڒn�t���O�𗧂Ă�
		m_isFloor = true;
		// �W�����v�񐔂�������
		m_jumpCount = JUMP_MAX;
		// �߂荞�܂Ȃ��悤�ɕ␳����
		m_obj.pos.y = GetPrm->Ground;
	}
	else{
		// �W�����v�ł��Ȃ�
		m_jumpCount = 0;
		// �n�ʂɕt���Ă��Ȃ�
		m_isFloor = false;
	}

	// �R���Ă�����
	if (m_isBurning)
	{
		// ���̃A���t�@�l��255�Ȃ�
		if (m_obj.alpha == ALPHA_MAX){
			m_obj.alpha = ALPHA_MIN;	// ��������
		}
		// ���Ƃ̓A���t�@�𑫂��Ă�������
		m_obj.alpha += BURNING_ADD_ALPHA;

		if (m_obj.alpha > ALPHA_MAX)
		{
			m_obj.alpha = ALPHA_MAX;
			m_isBurning = false;
		}
	}
}

/**
* @brief �`��
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

		// �f�ނ����Ȃ�����U���p�A�j���[�V�����̎g���܂킷
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
* @brief �O�i
*/
void Lilia::Advance()
{
	SetSpeed(GetChrPrm->LiliaAdvanceSpeed);
}

/**
* @brief �K�[�h
*/
void Lilia::Guard()
{
	SetSpeed(GetChrPrm->PlayerGuardNowSpeed);
}

/**
* @brief �K�[�h��
*/
void Lilia::GuardNow()
{
	switch (m_subWork)
	{
	case 0:
		// ���ʉ��̍Đ�
		SoundPlayer::GetInstance()->Play(GUARD_SE);
		// �K�[�h�G�t�F�N�g�̐���
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
* @brief ���Ⴊ�݃K�[�h��
*/
void Lilia::SquatGuardNow()
{
	switch (m_subWork)
	{
	case 0: // ������
		SoundPlayer::GetInstance()->Play(GUARD_SE);
		// �K�[�h�G�t�F�N�g�̐���
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
* @brief �W�����v
*/
void Lilia::Jump()
{
	// �W�����v�o����񐔂��O�Ȃ瑬�x��ݒ肵�Ȃ�
	if (m_jumpCount == 0) {
		m_subWork = 1;
	}

	switch (m_subWork)
	{
	case 0: // �p�����[�^�ݒ�
		switch (m_state)
		{
		case State::Jump:
			SetSpeed(0.0f, JUMP_VY);
			break;

		case State::JumpFront:
			// �E����
			if (m_obj.direction == Dir::Right)
				SetSpeed(m_oldSpd.x, JUMP_VY);
			// ������
			else
				SetSpeed(-m_oldSpd.x, JUMP_VY);
			break;

		case State::JumpBack:
			// ���E�̕␳�͂���Ȃ�
			SetSpeed(-4.0f, JUMP_VY);
			break;
		}
		// �i�߂�
		m_subWork++;
		break;

	case 1: // �A�N�V����

		// �n�ʂɐڂ��Ă�����
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
* @brief ����\���ۂ�
* @return true - ����\
*         false - ����s�\
*/
bool Lilia::isControll()
{
	return m_isControll;
}

/**
* @brief ����
*/
void Lilia::SetBurning()
{
	m_isBurning = true;
}

/**
* @brief ��i�U��������������
*/
bool Lilia::isUpperAttackHit(const IPlayer& enemy)
{
	ARGB red = { 255, 255, 0, 0 };
	ARGB blue = { 255, 0, 0, 255 };

	// ��i�U������Ȃ������牽�����Ȃ�
	if (m_attackPoint != AttackPoint::Upper) return false;

	// �U�����肪�������Ă��Ȃ������牽�����Ȃ�
	if (!m_isAttackJudge) return false;

	// ������t���O
	bool isHit = false;

	// ����������
	if (Collide::CheckRectAndRect(m_obj.pos, enemy.GetPos(), m_attackRect, enemy.GetHitRect()))
	{
		// ��ɍU�������؂�
		m_isAttackJudge = false;

		// ���肪�K�[�h��Ԃ܂��̓K�[�h���Ȃ�
		if (enemy.GetState() == State::Guard || enemy.GetState() == State::GuardNow){
			// ���������t���O��Ԃ��ď������I������
			return true;
		}
		
		// �q�b�g���ʉ��Đ������p
		static unsigned int hitSECount = 0;
		hitSECount++;

		// �U������
		m_isAttackSuccess = true;
		// ��������
		isHit = true;

		switch (m_state)
		{
		case State::WeakAttack:
		case State::MediumAttack:
		case State::SpecialProduction:
			// �q�b�g��
			SoundPlayer::GetInstance()->Play(BLADE_SE);
			// �G�t�F�N�g�𐶐�����
			EffectManager::GetInstance()->Add(make_shared<SlashEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), m_obj.direction, Vector2(20.0f), 3.5f, -0.25f));
			EffectManager::GetInstance()->Add(make_shared<SlashEffect2>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 170.0f), m_obj.direction, Vector2(0.0f, -20.0f), 90.0f));
			EffectManager::GetInstance()->Add(make_shared<SlashEffect2>(Vector2(enemy.GetPos().x + 300.0f, enemy.GetPos().y + 30.0f), m_obj.direction, Vector2(20.0f, 0.0f), 0.0f));
			EffectManager::GetInstance()->Add(make_shared<SlashEffect2>(Vector2(enemy.GetPos().x - 300.0f, enemy.GetPos().y + 30.0f), m_obj.direction, Vector2(-20.0f, 0.0f), 0.0f));
			// 10�d�˂�
			for (int i = 0; i < 10; i++){
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), red, 0.1f));
				EffectManager::GetInstance()->Add(make_shared<RingEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), blue, 0.07f));
			}
			break;

		case State::StrongAttack:
			// ���Z�b�g��������
			//			ActionReset();
			// ���x��������
			SetSpeed();
			// ����s�ɂ���
			m_isControll = false;
			// �q�b�g��
			SoundPlayer::GetInstance()->Play(SWORDBLOW_SE);
			// ��e�t���[�������Z����
			m_damageFrame++;

			// �q�b�g��
			if (hitSECount % 7 == 0){
				SoundPlayer::GetInstance()->Play(FLAME_SE);
			}
			// �΃p�[�e�B�N��
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
			// ���i�q�b�g������悤�Ƀt���O�������I�ɂn�m�ɂ���
			m_isAttackJudge = true;
			break;

		case State::WeakDerivationAttack:
			SoundPlayer::GetInstance()->Play(BLADE_SE);
			EffectManager::GetInstance()->Add(make_shared<SlashEffect>(Vector2(enemy.GetPos().x, enemy.GetPos().y - 50.0f), m_obj.direction, Vector2(20.0f, 0.0f), 1.0f, 0.0f, -45.0f));
			// 10�d�˂�
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
			// 10�d�˂�
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
* @brief ���i�U��������������
*/
bool Lilia::isLowerAttackHit(const IPlayer& enemy)
{
	// ���i�U������Ȃ������牽�����Ȃ�
	if (m_attackPoint != AttackPoint::Lower) return false;

	// �U�����肪�������Ă��Ȃ������牽�����Ȃ�
	if (!m_isAttackJudge) return false;

	// ������t���O
	bool isHit = false;

	// ����������
	if (Collide::CheckRectAndRect(m_obj.pos, enemy.GetPos(), m_attackRect, enemy.GetHitRect()))
	{
		// ��ɍU�������؂�
		m_isAttackJudge = false;

		// ���肪�K�[�h��Ԃ܂��̓K�[�h���Ȃ�
		if (enemy.GetState() == State::SquatGuard || enemy.GetState() == State::SquatGuardNow){
			// ���������t���O��Ԃ��ď������I������
			return true;
		}

		// �U������
		m_isAttackSuccess = true;
		// ��������
		isHit = true;

		switch (m_state)
		{
		case State::SquatAttack:
			SoundPlayer::GetInstance()->Play(SWORDBLOW_SE);
			// �p�[�e�B�N������
			for (int i = 0; i < 10; i++)
				ParticleManager::GetInstance()->Add(make_shared<HitParticle>(enemy.GetPos(), 0.3f));
			break;
		}
	}

	return isHit;
}

/**
* @brief ��e
*/
void Lilia::Damage(const IPlayer& attacker, AttackPoint hitType)
{
	switch (hitType)
	{
	case AttackPoint::Upper:
		// �K�[�h��Ԃ܂��̓K�[�h���Ȃ�
		if (m_state == State::Guard || m_state == State::GuardNow)
		{
			SetState(State::GuardNow);
			// �p�[�e�B�N���𐶐�����
			for (int i = 0; i < 7; i++){
				ParticleManager::GetInstance()->Add(make_shared<GuardParticle>(m_obj.pos, 0.3f));
			}
			// �ȍ~�̏����͂��Ȃ�
			return;
		}
		break;

	case AttackPoint::Lower:
		if (m_state == State::SquatGuard || m_state == State::SquatGuardNow)
		{
			SetState(State::SquatGuardNow);
			// �p�[�e�B�N���𐶐�����
			for (int i = 0; i < 7; i++){
				ParticleManager::GetInstance()->Add(make_shared<GuardParticle>(m_obj.pos, 0.3f));
			}
			// �ȍ~�̏����͂��Ȃ�
			return;
		}
		break;

	default:
		Utility::abortWithMsg("��e�^�C�v�����݂��܂���B");
		break;
	}
	
	// ���G��Ԃł��ȍ~�̏����͂��Ȃ�
	if (m_isInvincible){
		return;
	}

	// �_�E����ԂȂ�_�E���̂܂܂ɂ��Ă���
	if (m_state == State::Down) {
		SetState(State::Down);
	}

	// �U���҂̏��
	switch (attacker.GetState())
	{
	case State::WeakAttack:
	case State::MediumAttack:
		SetState(State::Damage);
		// ������
		SetSpeed(-0.4f);
		m_knockbackFrame = 30;
		// �󒆂ɂ����班��������
		if (m_obj.pos.y < GetPrm->Ground){
			SetSpeed(0.0f, -3.0f);
		}
		break;

	case State::StrongAttack: 
		m_knockbackFrame = 60;
		SetSpeed();
		SetState(State::Damage);
		// ����s�\
		m_isControll = false;
		// �A���t�@�l�𔲂�
		m_obj.alpha = ALPHA_MIN;
		// �R�₷
		m_isBurning = true;
		break;

	case State::StrongDerivationAttack:
		// �̂�����t���[��
		m_knockbackFrame = 90;
		m_downFrame = 90;
		// �A���t�@�l�𔲂�
		m_obj.alpha = ALPHA_MIN;
		// ������я�Ԃɂ���
		SetState(State::Blowoff);
		SetSpeed(-3.0f, -23.0f);
		break;

	case State::WeakDerivationAttack:
		SetSpeed(-20.0f, -7.0f);
		// �̂�����t���[��
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
		// �������
		SetSpeed(-14.0f, -17.0f);
		// KO��Ԃ̂܂�
		SetState(State::Ko);
	}
}

/**
* @brief �_�E����Ԃ��ۂ�
*/
bool Lilia::isDown()
{
	return false;
}

/**
* @brief �W�����v�o���邩�ۂ��̔���
*/
bool Lilia::IsJump()
{
	return(m_isFloor && m_jumpCount > 0 ? true : false);
}

/**
* @brief ��g�����邩�̔���
*/
bool Lilia::CanPassive()
{
	return m_isPassive;
}

/**
* @brief �ǌ�(�h���Z)���\��
*/
bool Lilia::CanDerivation()
{
	return m_isDerivation;
}

/**
* @brief �ʒu��ݒ�
*/
void Lilia::SetPos(const Vector2& pos)
{
	m_obj.pos = pos;
}

/**
* @brief ��Ԃ�ݒ�
*/
void Lilia::SetState(const State state)
{
	m_state = state;
}

/**
* @brief ������ݒ�
*/
void Lilia::SetDirection(const Dir& dir)
{
	m_obj.direction = dir;
}

/**
* @brief �v���C���[�ԍ����擾
*/
const unsigned int Lilia::GetID() const
{
	return m_id;
}

/**
* @brief �U���͂��擾
*/
const float Lilia::GetPower() const
{
	return m_power;
}

/**
* @brief �ʒu���擾
*/
const Vector2& Lilia::GetPos() const
{
	return m_obj.pos;
}

/**
* @brief ��Ԃ��擾
*/
const State Lilia::GetState() const
{
	return m_state;
}

/**
* @brief �U���͈͂��擾
*/
const Rect Lilia::GetAttackRect() const
{
	return m_attackRect;
}

/**
* @brief �q�b�g�͈͂��擾
*/
const Rect Lilia::GetHitRect() const
{
	return m_hitRect;
}

/**
* @brief �������擾
*/
const Dir Lilia::GetDirection() const
{
	return m_obj.direction;
}

/**
* @brief �U�����蔭�������ۂ�
*/
bool Lilia::isAttackJudge()
{
	return m_isAttackJudge;
}


#pragma endregion



/**
* @brief �ҋ@�X�V
*/
void Lilia::Neutral()
{
	// ���x0 ������
	SetSpeed();

	// �q�b�g����
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
* @brief �_�b�V���X�V
*/
void Lilia::Dash()
{
	SetSpeed(GetChrPrm->LiliaDashSpeed);
}

/**
* @brief ��ލX�V
*/
void Lilia::BackStep()
{
	if (m_subFrame == 0){
		// ����s�\
		m_isControll = false;
		
		SetSpeed(GetChrPrm->LiliaBackStepSpeed);
	}

	if (m_subFrame > 12){
		// ����\
		m_isControll = true;

		// �X�e�C�g��߂�
		SetState(State::Guard);
	}

	// �t���[���𑝂₷
	m_subFrame++;
}


/**
* @brief ���Ⴊ��
*/
void Lilia::Squat()
{
	// ���x�O
	SetSpeed();
	// �����蔻��Z�b�g
	m_hitRect = { 0, 70, 140, 140 };
	m_animation = 0;
}

/**
* @brief ���Ⴊ�ݍU��
*/
void Lilia::SquatAttack()
{
	switch (m_subWork)
	{
	case 0: // ������
		// ��i�U��
		m_attackPoint = AttackPoint::Lower;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackSquatPower;
		// �{�C�X�̍Đ�
		SoundPlayer::GetInstance()->Play(LILIA_SQUATATTACK_VOICE);

		float x;
		if (m_obj.direction == Dir::Right){
			x = 9.0f;
		} else {
			x = -9.0f;
		}
		// ���[�v�ŏd�˂ăG�t�F�N�g�𐶐�����
		for (int i = 0; i < 5; i++){
			EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>
				(29, Vector2(m_obj.pos.x + x + i, m_obj.pos.y + 80.0f), m_obj.direction));
										// ��[��]�ō��W���Y������[��]�Ń��[�v�̒l�����Y�����Ă�
		}
		// ����s�\
		m_isControll = false;
		// ���x�O������
		SetSpeed();
		
		m_subWork++;
		break;

	case 1:
		if (m_subFrame > 3){
			// �A�j���[�V��������
			m_animation = 0;
			// �����蔻��̐���
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
		// �����蔻����ɏ��ł����Ă���
		m_isAttackJudge = false;
		// �A�j���[�V�����ԍ�
		m_animation = 2;

		if (m_subFrame > 12){
			// ���Z�b�g
			ActionReset();
		}
		break;
	default:
		Utility::abortWithMsg("���݂��Ȃ��U����ԂɂȂ�܂����B�I�����܂��B");
		break;
	}

	// �t���[�����Z
	m_subFrame++;
}

/**
* @brief �_�b�V���U��
*/
void Lilia::DashAttack()
{
	switch (m_subWork)
	{
	case 0:
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackDashPower;
		// �{�C�X���Đ�
		SoundPlayer::GetInstance()->Play(LILIA_DASHATTACK_VOICE);
		// ����s��
		m_isControll = false;
		// �A�j���[�V�����Z�b�g
		m_animation = 1;
		// �����蔻��̐���
		m_attackRect = { 0, 0, 200, 200 };
		m_isAttackJudge = true;
		m_subWork++;
		break;

	case 1:
		// ������������
		m_spd.x = Utility::Friction(m_spd.x, 0.95f);

		if (m_subFrame > 30){
			// �����蔻��̏���
			m_isAttackJudge = false;
			m_subWork++;
		}
		break;

	case 2:
		// ������������
		m_spd.x = Utility::Friction(m_spd.x, 0.95f);

		// �d��
		if (m_subFrame > 60){
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	default:
		Utility::abortWithMsg("���݂��Ȃ��U����ԂɂȂ�܂����B�I�����܂��B");
		break;
	}
	// �t���[���̉��Z
	m_subFrame++;
}

/**
* @brief �W�����v�U��
*/
void Lilia::JumpAttack()
{
	switch (m_subWork)
	{
	case 0:
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackJumpPower;
		// �A�j���[�V�����̐ݒ�
		m_animation = 0;
		// ���ʉ��ƃ{�C�X�̍Đ�
		SoundPlayer::GetInstance()->Play(SWORDSWING_SE);
		SoundPlayer::GetInstance()->Play(LILIA_JUMPATTACK_VOICE);
		// �G�t�F�N�g���d�˂ĕ`�悷��
		EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>(31, Vector2(m_obj.pos.x, m_obj.pos.y + 60.0f), m_obj.direction));
		EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>(31, Vector2(m_obj.pos.x, m_obj.pos.y + 60.0f), m_obj.direction));
		m_subWork++;
		break;

	case 1:
		if (m_subFrame > 5){
			// �A�j���[�V�����̐ݒ�
			m_animation = 1;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame > 9){
			// �����蔻��̐���
			m_attackRect = { 0.0f, 0.0f, 250.0f, 150.0f };
			m_isAttackJudge = true;
			// �A�j���[�V�����̐ݒ�
			m_animation = 2;
			m_subWork++;
		}
		break;

	case 3:
		if (m_subFrame > 24){
			// �T�u���[�N�ƃt���[���̂ݏ�����
			m_subWork = 0;
			m_subFrame = 0;
			m_isAttackJudge = false;
			// ��Ԃ��W�����v�ɖ߂�
			SetState(State::Jump);
		}
		break;
	default:
		Utility::abortWithMsg("���݂��Ȃ��U����ԂɂȂ�܂����B�I�����܂��B");
		break;
	}

	// �U�����ɒn�ʂɕt�����ꍇ�͏�����
	if (m_obj.pos.y >= GetPrm->Ground){
		SetState(State::Neutral);
		ActionReset();
	}

	m_subFrame++;
}

/**
* @brief �_�E�����
*/
void Lilia::Down()
{
	switch (m_subWork)
	{
	case 0:
		// ���ʉ����Đ�
		SoundPlayer::GetInstance()->Play(DOWN_SE);
		EffectManager::GetInstance()->Add(make_shared<SmokeEffect>(Vector2(m_obj.pos.x, m_obj.pos.y + 120.0f)));
		m_isControll = false;
		m_subWork++;
		break;
	case 1:
		if (m_downFrame < 25)
			m_isInvincible = true;

		// �_�E���t���[�����O���L�����N�^�[���n�ʂɕt���Ă����烊�Z�b�g
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
* @brief ������
*/
void Lilia::Knockback()
{
	switch (m_subWork)
	{
	case 0: // ������
		if (m_state == State::DamageEffect){
			m_state = State::Damage;
			m_knockbackFrame = 25;
		}
		m_subWork++;
		break;

	case 1:
		if (m_knockbackFrame < 0){
			// ���Z�b�g���Ă���
			ActionReset();

			// �n��ɂ�����
			if (m_obj.pos.y >= GetPrm->Ground)
				SetState(State::Neutral);
			// �󒆂ɂ�����
			else
				SetState(State::Jump);
		}
		break;
	}

	// �t���[�������Z
	m_knockbackFrame--;
}

/**
* @brief ��U��
*/
void Lilia::WeakAttack()
{
	// �W�����v���Ȃ�ʏ��U���ɂ͓���Ȃ�
	if (!IsJump()) return;

	switch (m_subWork)
	{
	case 0:
	{
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackWeakPower;

		// �����̍Đ�
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKWEAK_VOICE);
		SoundPlayer::GetInstance()->Play(SWORDSWING_SE);

		// �L�����N�^�[�̌����ɂ���ăY�����l�Ɗp�x��ς���
		float x = 0.0f, rot = 0.0f;
		// �E����
		if (m_obj.direction == Dir::Right){
			rot = 15.0f;
			x = 9.0f;
		} // ������
		else{
			rot -= 15.0f;
			x -= 9.0f;
		}
		// ���[�v�ŏd�˂ăG�t�F�N�g�𐶐�����
		for (int i = 0; i < 5; i++){
			EffectManager::GetInstance()->Add(make_shared<SwordTrajectoryEffect>
				(29, Vector2(m_obj.pos.x + x + i, m_obj.pos.y + 35.0f), m_obj.direction, rot));
										// ��[��]�ō��W���Y������[��]�Ń��[�v�̒l�����Y�����Ă�
		}

		// ����s�\
		m_isControll = false;
		// ���x���O�ɂ���
		SetSpeed();
		// �A�j���[�V�����ݒ�
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
			// �����蔻��𐶐�
			m_attackRect = { 0, 0, 250, 150 };
			m_isAttackJudge = true;
			// �A�j���[�V�����ԍ�
			m_animation = 2;
			m_subWork++;
		}
		break;

	case 3:
		// �����蔻����ɏ��ł�����
		m_isAttackJudge = false;
		// �d��
		if (m_subFrame > 24){
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	default:
		Utility::abortWithMsg("���݂��Ȃ��U����ԂɂȂ�܂����B�I�����܂��B");
		break;
	}

	// �U�����q�b�g������
	if (m_isAttackSuccess){
		// �h���Z�Ɉڂ��
		m_isDerivation = true;
	}

	// �t���[�����܂킷
	m_subFrame++;
}

/**
* @brief ��U���h���Z
*/
void Lilia::WeakAttackDerivation()
{
	switch (m_subWork)
	{
	case 0:
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �U���͂�ݒ�
		m_power = GetChrPrm->LiliaAttackWeakDerivationPower;
		// �����蔻��𐶐�
		m_isAttackJudge = true;
		m_attackRect = { 0, 0, 200, 200 };
		// ���x�̐ݒ�
		SetSpeed(10.0f);
		// �A�j���[�V�����̐ݒ�
		m_animation = 1;
		// �{�C�X���Đ�����
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKWEAK_DER_VOICE);
		// ����s��
		m_isControll = false;

		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 35)
		{
			// ���Z�b�g
			ActionReset();
			SetState(State::Neutral);
		}
		m_subFrame++;
		break;
	}
}

/**
* @brief ���U��
*/
void Lilia::MediumAttack()
{
	switch (m_subWork)
	{
	case 0: // ������
		// ���Z�b�g���Ă���
		ActionReset();
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackMediumPower;
		SoundPlayer::GetInstance()->Play(LILIA_JUMPATTACK_VOICE); // �W�����v�p�{�C�X���p
		// ����s�\
		m_isControll = false;
		// �A�j���[�V�����̐ݒ�
		m_animation = 5;
		SetSpeed();
		m_subWork++;
		break;

	case 1:
		if (m_subFrame > 4){
			// �A�j���[�V�����̐ݒ�
			m_animation = 4;
			// �����蔻��̐���
			m_attackRect = { 0, 0, 200, 200 };
			m_isAttackJudge = true;
			m_subWork++;
		}
		break;

	case 2:
		if (m_subFrame > 10){
			// �A�j���[�V�����̐ݒ�
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
		Utility::abortWithMsg("���݂��Ȃ��U����ԂɂȂ�܂����B�I�����܂��B");
		break;
	}
	m_subFrame++;
}

/**
* @brief ���U��
*/
void Lilia::StrongAttack()
{
	// �{�C�X�Đ������p
	static int r;

	switch (m_subWork)
	{
	case 0: // ������
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// ����s��
		m_isControll = false;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackStrongPower;
		// �����蔻��̐���
		m_isAttackJudge = true;
		m_attackRect = { 0, 0, 200, 200 };
		// �A�j���[�V�����̐ݒ�
		m_animation = 1;
		// ��������
		r = Utility::Random(0, 1);
		// �����ōĐ�����{�C�X��ύX����
		if (r == 0) SoundPlayer::GetInstance()->Play(LILIA_ATTACKSTRONG_VOICE);
		if (r == 1) SoundPlayer::GetInstance()->Play(LILIA_ATTACKSTRONG_VOICE2);
		// ���x�̐ݒ�
		SetSpeed(GetChrPrm->LiliaAttackStrongSpeed);

		m_subWork++;
		break;

	case 1: // �U����
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
		// ���i�q�b�g������悤�Ƀt���O�������I�ɂn�m�ɂ���
		m_isAttackJudge = true;
		SetSpeed();
		break;
	}
	m_subFrame++;
}

/**
* @brief ���U���h���Z
*/
void Lilia::StrongAttackDerivation()
{
	switch (m_subWork)
	{
	case 0:
		// ����s��
		m_isControll = false;
		m_attackRect = { 0, 0, 200, 200 };
		// �A�j���[�V�����̐ݒ�
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

	// �t���[�������Z����
	m_subFrame++;
}

/**
* @brief �������U��
*/
void Lilia::LongAttack()
{
	if (!IsJump()) return;

	switch (m_subWork)
	{
	case 0:
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackLongPower;
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKWEAK_VOICE);
		m_isControll = false;
		m_animation = 5;
		// ���x��������
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
		// �d��
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
* @brief �K�E�Z
*/
void Lilia::SpecialAttack()
{
	// �A�j���[�V���������p�t���[��
	static int adjustFrame;

	switch (m_subWork)
	{
	case 0: // ������
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// ���x���O�ɂ���
		SetSpeed();
		// ����s��Ԃɂ���
		m_isControll = false;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackSpecialPower;
		// �J�b�g�C����ݒ肷��
		CutInManager::GetInstance()->Create(LILIA, m_id, m_obj.pos);

		// �{�C�X�̍Đ�
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_VOICE);

		m_subWork++;
		break;

	case 1:
		// �J�b�g�C����������̂�҂�
		if (!CutInManager::GetInstance()->IsPlayCutIn()){
			m_subWork++;
		}
		break;

	case 2: 
		// ���G�t���O���Z�b�g
		m_isInvincible = true;
		// �{�C�X�̍Đ�
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_VOICE3);
		m_subWork++;
		adjustFrame = 10;
		EffectManager::GetInstance()->Add(make_shared<WaveEffect>(m_obj.pos, m_obj.direction));
		break;

	case 3:
		// �U���p�G�t�F�N�g�𐶐�����
		SpecialAttackCreateEffect();

		// �t���[�����o�߂��閈�ɃA�j���[�V���������������Ă�������
		if (m_subFrame % adjustFrame == 0)
		{
			// �G�t�F�N�g�𐶐�����
			EffectManager::GetInstance()->Add(make_shared<LightLineEffect>(m_obj.pos));
			m_animation++;
			if (m_animation >= 3){
				adjustFrame--;
				m_animation = 0;
			}
		}
		// 0�ȉ��ɂȂ�����
		if (adjustFrame <= 0)
		{
			// �����t���[����1�ŌŒ�
			adjustFrame = 1;
			// �a���J�E���g�����Z����
			m_slashingCount++;
			// 16��ȉ��Ȃ珈���𑱂���
			if (m_slashingCount > GetChrPrm->LiliaSlashingCountMax){
				m_subWork++;
			}
		}
		break;

	case 4: // �K�E�Z�ǌ���Ԃɓ���O�Ƀp�����[�^�����Z�b�g���Ă���
		// ���G�t���O��܂�
		m_isInvincible = false;
		m_slashingCount = 0;
		adjustFrame = 10;
		// ��x���Z�b�g��������
		ActionReset();
		// ����s�\
		m_isControll = false;
		SetState(State::AttackSpecialPursuit);
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_PUR_VOICE);
		break;
	}
	// �t���[�������Z
	m_subFrame++;
}

/**
* @brief �K�E�Z�ǌ�
* @note  �K�E�Z���I���Ǝ����I�ɂ��̃A�N�V�����ɓ���
*/
void Lilia::SpecialPursuitAttack()
{
	switch (m_subWork)
	{
	case 0:
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// �����蔻��̐���
		m_attackRect = { 0, 0, 250, 250 };
		m_isAttackJudge = true;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackSpecialPursuitPower;
		// �A�j���[�V�����̐ݒ�
		m_animation = 1;
		// ���x�̐ݒ�
		SetSpeed(GetChrPrm->LiliaAttackSpecialPursuitSpeed);
		m_subWork++;
		break;

	case 1:
		// �U�����蔭������
		if (m_subFrame > 40){

			// �U��������
			if (m_isAttackSuccess){
				SoundPlayer::GetInstance()->Play(LILIA_ATTACKSPECIAL_SUCCESS);
			}
			else {
				ActionReset();
				SetState(State::Neutral);
			}
			// �����蔻��̍폜
			m_isAttackJudge = false;
			// ���x������
			SetSpeed();
			m_subWork++;
		}
		break;
		
	case 2:
		if (m_subFrame > 150){
			// �����蔻��̍폜
			m_isAttackJudge = false;
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
	// �t���[�������Z
	m_subFrame++;
}

/**
* @brief ��P�U��
*/
void Lilia::RaidAttack()
{
	switch (m_subWork)
	{
	case 0:
		// ��i�U��
		m_attackPoint = AttackPoint::Upper;
		// ����s�\
		m_isControll = false;	
		// �{�C�X�̍쐬
		SoundPlayer::GetInstance()->Play(LILIA_ATTACKMEDIUM_VOICE);
		SoundPlayer::GetInstance()->Play(SETUPMOTION_SE);
		// �G�t�F�N�g�쐬
		EffectManager::GetInstance()->Add(make_shared<LightEffect>(m_obj.pos));
		// �A�j���[�V�����̐ݒ�
		m_animation = 0;
		// �U���͂̐ݒ�
		m_power = GetChrPrm->LiliaAttackRaidPower;
		m_subWork++;
		break;

	case 1:
		// �����܂�15�t���[��
		if (m_subFrame >= 15){
			m_subWork++;
			m_subFrame = 0;
		}
		break;

	case 2:
		// �����蔻��̐���
		m_attackRect = { 0, 0, 200, 200 };
		m_isAttackJudge = true;

		// �A�j���[�V�����̐ݒ�
		m_animation = 1;
		// ���x�̐ݒ�
		SetSpeed(ATTACK_RAID_VX);
		m_subWork++;
		break;

	case 3:
		// ������
		m_spd.x = Utility::Friction(m_spd.x, 0.9f);

		if (m_subFrame >= 35){
			// �A�j���[�V�����ݒ�
			m_animation = 0;
			m_subWork++;
		}
		break;

	case 4:
		// ������
		m_spd.x = Utility::Friction(m_spd.x, 0.9f);

		// �d��
		if (m_subFrame >= 75){
			m_isAttackJudge = false;
			SetState(State::Neutral);
			ActionReset();
		}
		break;
	}
	// �t���[���X�V
	m_subFrame++;
}

/**
* @brief �������
*/
void Lilia::BlowOff()
{
	switch (m_subWork)
	{
	case 0:
		// ����s��
		m_isControll = false;
		m_subWork++;
		break;

	case 1:
		// �p�x���Z
		AddAngle(BLOWOFF_ADD_ANGLE);

		// �[�ɓ��������璵�˕Ԃ�
		if (m_obj.pos.x >= CAMERA_END_RIGHT - CHARACTER_MARGIN + GetCameraPos ||
			m_obj.pos.x <= CAMERA_END_LEFT + CHARACTER_MARGIN + GetCameraPos)
		{
			m_spd.x = Utility::Rebound(m_spd.x, 0.2f);
		}

		// ����������Ȃ��Ƌ󒆏�ԂŐ�����Ԃƃo�O��̂ŋ~�Ϗ��u�p�Ƃ��ċL�q
		if (m_obj.pos.y > GetPrm->Ground) m_obj.pos.y = GetPrm->Ground;

		if (m_obj.pos.y == GetPrm->Ground){
			// �n�ʂɕt�����u�Ԃ�����g������
			m_isPassive = true;
			m_subWork++;
		}
		break;

	case 2:
		// ��g�t���O����
		m_isPassive = false;
		// ���Z�b�g
		ActionReset();
		// �_�E�����
		SetState(State::Down);

		// ���C
		m_spd.x = Utility::Friction(m_spd.x, 0.55f);
		// �o�E���h
		m_spd.y = Utility::Rebound(m_spd.y, 0.2f);

		break;
	}

	// �t���[�����܂킷
	m_subFrame++;
}

/**
* @brief ���E
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
		// ���C�W��
		m_spd.x = Utility::Friction(m_spd.x, 0.85f);

		if (m_subFrame >= 30)
		{
			// �p�����[�^������
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
	// �t���[�����Z
	m_subFrame++;
}

/**
* @brief ��g
*/
void Lilia::Passive()
{
	switch (m_subWork)
	{
	case 0: // �p�����[�^������������
		// ��g�t���O����
		m_isPassive = false;
		ActionReset();
		m_subWork++;
		break;

	case 1: // ���x�ƃ{�C�X��ݒ肷��
		SetSpeed(-PASSIVE_VX, -PASSIVE_VY);
		SoundPlayer::GetInstance()->Play(LILIA_PASSIVE_VOICE);
		m_subWork++;
		break;

	case 2:
		// �n�ʂɒ�������
		if (m_obj.pos.y >= GetPrm->Ground){
			// �p�����[�^��������
			ActionReset();
			SetState(State::Neutral);
		}
		break;
	}
}

/**
* @brief �o�g���J�n�O
*/
void Lilia::BeforeBattle()
{
	switch (m_subWork)
	{
	case 0:
		m_animation = 0;

		// ����s�\�ɂ���
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
		// ���Z�b�g
		ActionReset();
		SetState(State::Neutral);
		break;
	}

	// �s���t���[�������Z
	m_subFrame++;
}

/**
* @brief �m�b�N�A�E�g
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
		// �n�ʂɒ����Ă�����
		if (m_obj.pos.y >= GetPrm->Ground)
		{
			SetSpeed(-KO_VX, -KO_VY);
		}
		// �󒆂ɂ�����
		else
		{
			SetSpeed(-KO_VX, m_spd.y);
		}

		m_subWork++;
		break;

	case 2:
		// �n�ʂɒ�������
		if (m_obj.pos.y >= GetPrm->Ground)
		{
			// ���x������
			SetSpeed();
			m_subWork++;
		}
		break;

	case 3:
		// �������Ȃ�
		break;
	}
}

/**
* @brief ����
*/
void Lilia::Win()
{
	switch (m_subWork)
	{
	case 0:
		// �����s�\�ɂ���
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
	// �t���[�����Z
	m_subFrame++;
}

/**
* @brief ���ꉉ�o
*/
void Lilia::SpecialProduction()
{
	switch (m_subWork)
	{
	case 0:
		// �p�����[�^�����Z�b�g���Ă���
		ActionReset();
		// ��i
		m_attackPoint = AttackPoint::Upper;
		// ����s�\
		m_isControll = false;
		// �A�j���[�V�����ݒ�1
		m_animation = 0;

		m_subWork++;
		break;

	case 1:
		if (m_subFrame >= 30){
			// �S�͈�
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

	case 3: // ����������
		m_isAttackJudge = false;
		ActionReset();
		SetState(State::Neutral);
		break;
	}
	// �s���t���[�������Z����
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
* @brief �p�����[�^���Z�b�g
*        �L�����N�^�[�̏�Ԃ��؂�ւ�鎞�ɂ��̊֐����Ă�
*/
void Lilia::ActionReset()
{
	// �A�j���[�V�������Z�b�g
	m_animation = 0;
	// �����蔻��̏���
	m_attackRect = {};
	// ����\��Ԃ�
	m_isControll = true;
	// ���G�t���O������
	m_isInvincible = false;
	// �����蔻�����
	m_isAttackJudge = false;
	// �U�������t���O������
	m_isAttackSuccess = false;
	// �ǌ��t���O������
	m_isDerivation = false;
	// �U���͂�������
	m_power = 0.0f;
	// �T�u���[�N�𓪂ɖ߂�
	m_subWork = 0;
	// �e�X�̃t���[�����O�ɂ���
	m_subFrame = 0;
	// �p�x���O��
	m_obj.rot = 0.0f;
}

/**
* @brief ���x�̐ݒ�(�Z�ʂ������悤��x��y��ʁX�ɐݒ�ł���悤�ɂ��Ă���)
*        �L�����N�^�[���E�����̎��͐��A�������̎��͕��̒l���ݒ肳���
* @param spx - �����̑��x(�f�t�H���g��0.0f)
* @param spy - �c���̑��x(�f�t�H���g��0.0f)
*/
void Lilia::SetSpeed(const float spx, const float spy)
{
	if (m_obj.direction == Dir::Right){
		m_spd.x = spx;
	}
	else if(m_obj.direction == Dir::Left){
		m_spd.x = -spx;
	}

	// y���͌����Ɋ֌W�Ȃ��ꗥ
	m_spd.y = spy;
}

void Lilia::AddAngle(float speed)
{
	static const float LIMIT_ANGLE = 140.0f;
	// ������
	if (m_obj.direction == Dir::Left){
		m_obj.rot += speed;
		if (m_obj.rot > LIMIT_ANGLE){
			m_obj.rot = LIMIT_ANGLE;
		}
	}
	// �E����
	else{
		if (m_obj.rot < -LIMIT_ANGLE){
			m_obj.rot = -LIMIT_ANGLE;
		}
		m_obj.rot -= speed;
	}
}

void Lilia::SpecialAttackCreateEffect()
{
	// �ꎞ�ϐ�
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

	// �O�ȉ��ɂ͂Ȃ�Ȃ�
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