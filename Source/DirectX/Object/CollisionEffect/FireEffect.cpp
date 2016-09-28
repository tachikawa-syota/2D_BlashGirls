#include "CollisionEffectManager.h"
#include "FireEffect.h"
#include "..\..\DirectX\SoundPlayer.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\FireParticle.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\GameSystem\Collide.h"

/**
* @brief �R���X�g���N�^
* @param id - �ԍ�
* @param pos - �`��ʒu
* @param dir - �`�����
*/
FireEffect::FireEffect(const unsigned int id, const Vector2& pos, const Dir& dir)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_HINOKO);

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_obj.scale = 1.0f;

	// �����ɂ���đ��x�ƌ�����ݒ�
	if (dir == Dir::Right){
		m_v.x = 20.0f;
		m_obj.isReverse = false;
	}
	else{
		m_v.x -= 20.0f;
		m_obj.isReverse = true;
	}

	// �q�b�g�͈�
	m_hitRect = { 0.0f, 0.0f, 180.0f, 180.0f };
	
	// �����t���[����60�t���[��
	m_liveFrame = 60;
	// �v���C���[�̔ԍ�������
	m_id = id;
	// ����ł��Ȃ�
	m_isDead = false;
}

/**
* @brief �X�V
*/
bool FireEffect::Update()
{
	// �ʒu�ɑ��x�����Z����
	m_obj.pos += m_v;

	// �����t���[�����O�ŏ���
	if (m_liveFrame < 0){
		m_isDead = true;
	}

	// �����t���[�������Z
	m_liveFrame--;

	// true�ō폜
	return m_isDead;
}

/**
* @brief �`��
*/
void FireEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, ALPHA_MAX, false, m_obj.isReverse);
}

/**
* @brief �v���C���[�Ƃ̓����蔻��
*/
void FireEffect::CollisionCheckPlayer(IPlPtr obj)
{
	// �G�t�F�N�g���o�����������g�ɂ͓�����Ȃ�
	if (m_id == obj->GetID()) return;

	// �������Ă��Ȃ������珈�����I������
	if (!Collide::CheckRectAndRect(m_obj.pos, obj->GetPos(), m_hitRect, obj->GetHitRect())) return;

	// ����������G�t�F�N�g������
	m_isDead = true;

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
	// ���コ����
	obj->SetBurning();
	// ��~������
	obj->SetSpeed();

	// ���ʉ����Đ�
	SoundPlayer::GetInstance()->Play(FLAMECOLLIDE_SE);

	// �v���C���[�̍��W�Ƀq�b�g�p�[�e�B�N���𐶐�����
	for (int i = 0; i < 35; i++)
	{
		ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(obj->GetPos().x, obj->GetPos().y + 70.f), 1.3f));
		ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(obj->GetPos().x + 8.0f, obj->GetPos().y + 70.f), 1.3f));
		ParticleManager::GetInstance()->Add(make_shared<FireParticle>(Vector2(obj->GetPos().x - 8.0f, obj->GetPos().y + 70.f), 1.3f));
	}
}