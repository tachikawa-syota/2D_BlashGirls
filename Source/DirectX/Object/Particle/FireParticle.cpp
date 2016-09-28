#include "FireParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
* @param scale - �傫��
*/
FireParticle::FireParticle(const Vector2& pos, const float scale)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_FIRE_LIGHT);

	// �p�����[�^�̐ݒ�
	m_obj.scale = scale;
	m_obj.pos = pos;
	m_v.x = 0.0f;
	m_v.y = static_cast<float>((rand() % 100 * 0.04f - 0.5f));
	// �����x��0
	m_add = {};
	m_obj.alpha = 255;
}

/**
* @brief �X�V
*/
bool FireParticle::Update()
{
	m_obj.scale -= 0.018f;
	
	m_add.x = (float)(rand() % 256 - 128) / 256;
	m_add.y = -(float)(rand() % 128) / 256;

	// ���W�X�V
	m_obj.pos += m_v;

	// ���x�X�V
	m_v += m_add;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief �`��
*/
void FireParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}