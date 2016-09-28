#include "FlushEffect.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param �`��ʒu
*/
FlushEffect::FlushEffect(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_FLUSH);

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_obj.scale = 0.0f;
	m_liveFrame = 30;
}

/**
* @brief �X�V
*/
bool FlushEffect::Update()
{
	// �X�P�[�����g��
	m_obj.scale += GetPrm->FlushEffectAddScale;
	
	if (m_obj.scale > GetPrm->FlushEffectMaxScale){
		m_obj.scale = GetPrm->FlushEffectMaxScale;
	}

	// �����t���[�������Z
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void FlushEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale);
}