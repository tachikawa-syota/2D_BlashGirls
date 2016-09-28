#include "HitParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �`��ʒu
* @param scale - �`��J�n���̑傫��
*/
HitParticle::HitParticle(const Vector2& pos, const float scale)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	m_liveFrame = 30;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_HIT_EFFECT);

	// �p�����[�^�̐ݒ�
	m_obj.pos = pos;
	m_obj.scale = scale;
	m_obj.alpha = ALPHA_MAX;
	m_v.x = static_cast<float>((rand() % 255 - 128) / 16);
	m_v.y = static_cast<float>((rand() % 255 - 128) / 16);
}

/**
* @brief �X�V
*/
bool HitParticle::Update()
{
	// �k��
	m_obj.scale -= 0.006f;

	// �A���t�@�l������
	m_obj.alpha -= 7;

	// ���W�X�V
	m_obj.pos += m_v * 0.65f;

	// �����t���[���X�V
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void HitParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}