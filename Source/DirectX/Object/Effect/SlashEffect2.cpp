#include "SlashEffect2.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
* @param dir - ����
* @param vel - ���x
* @param rot - �g�呬�x(�f�t�H���g�� 0.0f)
* @param rot - �p�x(�f�t�H���g�� 0.0f)
*/
SlashEffect2::SlashEffect2(const Vector2& pos, const Dir& dir, const Vector2& vel, const float rot)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_SLASH4);

	// �p�����[�^�̐ݒ�
	m_obj.scale = 0.9f;
	m_obj.pos = pos;
	m_obj.rot = rot;
	m_v.y = vel.y;
	m_obj.alpha = ALPHA_MAX;
}

/**
* @brief �X�V
*/
bool SlashEffect2::Update()
{
	// �A���t�@�l�����Z����
	m_obj.alpha -= 30;

	// ���x���ʒu�ɉ��Z����
	m_obj.pos += m_v;

	// �A���t�@�l���O�ȉ��ŏ���
	if (m_obj.alpha < 0){
		return true;
	}

	return false;
}

/**
* @brief �`��
*/
void SlashEffect2::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true, m_obj.isReverse);
}