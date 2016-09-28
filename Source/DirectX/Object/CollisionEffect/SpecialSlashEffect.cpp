#include "SpecialSlashEffect.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\SpecialHitParticle.h"
#include "..\..\DirectX\SoundPlayer.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\GameSystem\Collide.h"

/**
* @brief �R���X�g���N�^
* @param id - �G�t�F�N�g��ID(�U���g�p�v���C���[�̎���ID���n�����)
* @param pos - �ʒu
* @param dir - ����
* @param vel - ���x
* @param rot - �p�x(�f�t�H���g��0.0f)
*/
SpecialSlashEffect::SpecialSlashEffect(
	const unsigned int id, 
	const Vector2& pos, 
	const Dir& dir, 
	const Vector2& vel,
	const float rot)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_SLASH3);

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_obj.rot = rot;
	m_obj.scale = 0.8f;

	// �����ɂ���đ��x�ƌ����Ɗp�x��ݒ�
	if (dir == Dir::Right){
		m_v.x = vel.x;
		m_obj.isReverse = false;
	}
	else{
		// �����𔽓]������
		m_obj.rot *= -1;
		m_v.x -= vel.x;
		m_obj.isReverse = true;
	}
	m_v.y = vel.y;

	// ������͈͂�ݒ�
	m_hitRect = { 0.0f, 0.0f, 300.0f, 300.0f };
	m_liveFrame = 10;
	m_id = id;

	m_isHit = false;
}

/**
* @brief �X�V
*/
bool SpecialSlashEffect::Update()
{
	// �g�傷��
	m_obj.scale += 0.4f;

	// �X�P�[���Œ�
	if (m_obj.scale >= 1.5f){
		m_obj.scale = 1.5f;
	}

	// �ʒu�ɑ��x�����Z����
	m_obj.pos += m_v;

	// �����t���[�������Z
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void SpecialSlashEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, ALPHA_MAX, false);
}

/**
* @brief �v���C���[�Ƃ̓����蔻��
*/
void SpecialSlashEffect::CollisionCheckPlayer(IPlPtr obj)
{
	// �G�t�F�N�g���o�����������g�ɂ͓�����Ȃ�
	if (m_id == obj->GetID()) return;

	// �q�b�g���Ă����珈�����I������
	if (m_isHit) return;

	// �������Ă��Ȃ������珈�����I������
	if (!Collide::CheckRectAndRect(m_obj.pos, obj->GetPos(), m_hitRect, obj->GetHitRect())) return;

	// �K�[�h��Ԃ�������
	if (obj->GetState() == State::Guard ||
		obj->GetState() == State::JumpGuard ||
		obj->GetState() == State::GuardNow)
	{
		// �K�[�h��
		obj->SetState(State::GuardNow);
		// �I��
		return;
	}

	// ��e��Ԃɐݒ�
	obj->SetState(State::DamageEffect);
	// �q�b�g�����班��������
	obj->SetSpeed(0.0f, -0.3f);

	// �p�[�e�B�N���̒ǉ�
	for (int i = 0; i < 5; i++){
		ParticleManager::GetInstance()->Add(make_shared<SpecialHitParticle>(obj->GetPos()));
	}

	static int seFrame = 0;
	// ���ʉ��̍Đ�
	if (seFrame % 3 == 0){
		SoundPlayer::GetInstance()->Play(BLADE_SE);
	}
	seFrame++;

	// �q�b�g
	m_isHit = true;
}