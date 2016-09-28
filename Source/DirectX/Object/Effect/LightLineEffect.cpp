#include "LightLineEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param �`��ʒu
*/
LightLineEffect::LightLineEffect(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_LINE);

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_v = {};
	m_liveFrame = 4;
}

/**
* @brief �X�V
*/
bool LightLineEffect::Update()
{
	m_v.y -= 10.0f;

	// �ʒu�ɑ��x�����Z����
	m_obj.pos += m_v;

	// �����t���[�������Z
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void LightLineEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, 0.5f, ALPHA_MAX, true);
}