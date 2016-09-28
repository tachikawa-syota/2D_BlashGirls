#include "BurstRingEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
*/
BurstRingEffect::BurstRingEffect(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_BURST_RING);

	// �p�����[�^�̐ݒ�
	m_obj.scale = 0.0f;
	m_obj.pos = pos;

	m_liveFrame = 120;
	m_obj.scale = 0.0f;

	m_obj.alpha = ALPHA_MAX;
}

/**
* @brief �X�V
*/
bool BurstRingEffect::Update()
{
	m_obj.scale += 0.2f;
	m_obj.alpha -= 5;

	// �����t���[�������Z
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void BurstRingEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}