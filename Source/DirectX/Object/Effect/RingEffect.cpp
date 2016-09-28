#include "RingEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
*/
RingEffect::RingEffect(const Vector2& pos, const ARGB& color, const float addScale)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_RING);

	// �p�����[�^�̐ݒ�
	m_obj.scale = 0.0f;
	m_obj.pos = pos;
	m_liveFrame = 20;
	m_color = color;

	// �g�呬�x
	m_addScale = addScale;

	m_obj.alpha = ALPHA_MAX;
}

/**
* @brief �X�V
*/
bool RingEffect::Update()
{
	if (m_obj.scale >= 1.0f){
		m_color.red -= 25;
		m_color.blue -= 30;
	}
	if (m_color.alpha <= 0){
		m_color.alpha = 0;
	}

	// �X�P�[�������Z
	m_obj.scale += m_addScale;

	// �����t���[�������Z
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void RingEffect::Render()
{
	m_2dTex->DrawTexARGB(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_color, true, m_obj.rot, m_obj.scale);
}