#include "LightEffect.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param �`��ʒu
*/
LightEffect::LightEffect(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	for (int i = 0; i < LIGHT_MAX; i++){
		hTex[i] = m_texData->GetLightTexture(i);
	}

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_obj.scale = 0.0f;
	// �e��p�����[�^�̏�����
	m_animFrame = 0;
	m_animation = 0;
}

/**
* @brief �X�V
*/
bool LightEffect::Update()
{
	// �g�傷��
	m_obj.scale++;
	// ���~�b�g
	if (m_obj.scale >= GetPrm->LightEffectMaxScale){
		m_obj.scale = 0.0f;
	}

	if (m_animFrame % 4 == 0){
		m_animation++;
	}

	// �A�j���[�V�����t���[�������Z
	m_animFrame++;

	return (m_animation >= LIGHT_MAX - 1) ? true : false;
}

/**
* @brief �`��
*/
void LightEffect::Render()
{
	m_2dTex->DrawTexture(hTex[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale);
}