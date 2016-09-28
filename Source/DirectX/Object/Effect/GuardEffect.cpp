#include "GuardEffect.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �`��ʒu
* @param dir - �`�����
*/
GuardEffect::GuardEffect(const Vector2& pos, const Dir& dir)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_GUARD);

	// �ʒu��ݒ�
	m_obj.pos = pos;

	if (dir == Dir::Left){
		m_obj.pos.x -= 50.0f;
		m_obj.isReverse = true;
	}else{
		m_obj.pos.x += 50.0f;
		m_obj.isReverse = false;
	}
	m_obj.scale = 0.0f;
	m_v = {};
	m_liveFrame = 10;
}

/**
* @brief �X�V
*/
bool GuardEffect::Update()
{
	// �g�債�Ă���
	m_obj.scale += GetPrm->GuardEffectAddScale;

	if (m_obj.scale > GetPrm->GuardEffectMaxScale){
		m_obj.scale = GetPrm->GuardEffectMaxScale;
	}

	// �����t���[�������Y
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief �`��
*/
void GuardEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, 200, false, m_obj.isReverse);
}