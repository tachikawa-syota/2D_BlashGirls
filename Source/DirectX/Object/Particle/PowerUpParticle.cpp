#include "PowerUpParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
* @param scale - �傫��
* @param alpha - �A���t�@�l
*/
PowerupParticle::PowerupParticle(const Vector2& pos, const float scale, const float alpha)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_RED_LIGHT);
	// �����t���[���̐ݒ�
	m_liveFrame = 120;
	m_obj.scale = scale;
	m_obj.pos = pos;
	m_v.x = static_cast<float>(rand() % 100 * 0.01 - 0.5);
	m_v.y = static_cast<float>(rand() % 100 * 0.01 + 0.7);
	m_obj.alpha = alpha;
}

/**
* @brief �X�V
*/
bool PowerupParticle::Update()
{
	// ���x���Z
	m_v.x = (float)(rand() % 255 - 128) / 32;
	m_v.y = -1.4f;

	// �k��
	m_obj.scale -= 0.012f;

	// ���W�X�V
	m_obj.pos += m_v;

	// �����t���[���X�V
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void PowerupParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}