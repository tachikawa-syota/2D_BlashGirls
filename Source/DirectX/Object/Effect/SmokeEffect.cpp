#include "SmokeEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param �`��ʒu
*/
SmokeEffect::SmokeEffect(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_SMOKE);

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_obj.scale = 0.0f;
	// �����t���[����ݒ�
	m_liveFrame = 30;
}

/**
* @brief �X�V
*/
bool SmokeEffect::Update()
{
	m_obj.scale += 0.03f;

	if (m_obj.scale > 0.5f){
		m_obj.scale = 0.5f;
	}
	// �����t���[�������Z
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void SmokeEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale);
}