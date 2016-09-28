#include "SlashEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
* @param dir - ����
* @param vel - ���x
* @param rot - �g�呬�x(�f�t�H���g�� 0.0f)
* @param rot - �p�x(�f�t�H���g�� 0.0f)
*/
SlashEffect::SlashEffect(const Vector2& pos, const Dir& dir, const Vector2& vel, const float scale, const float addScale, const float rot)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_SLASH);

	// �p�����[�^�̐ݒ�
	m_obj.scale = scale;
	m_obj.pos = pos;
	m_obj.rot = rot;
	m_v.y = vel.y;
	m_obj.alpha = ALPHA_MAX;
	m_addScale = addScale;
	m_liveFrame = 20;

	// �v���C���[�̌����ɉ����Ĕ��]������
	if (dir == Dir::Right){
		m_v.x = vel.x;
		m_obj.isReverse = true;
	}
	else{
		m_obj.rot *= -1;
		m_v.x = -vel.x;
		m_obj.isReverse = false;
	}
}

/**
* @brief �X�V
*/
bool SlashEffect::Update()
{
	//�@�X�P�[�������Z
	m_obj.scale += m_addScale;

	// ���x���ʒu�ɉ��Z����
	m_obj.pos += m_v;

	// �����t���[�������Z����
	m_liveFrame--;

	if (m_obj.scale < 0.0f || m_liveFrame < 0){
		// �폜����
		return true;
	}

	return false;
}

/**
* @brief �`��
*/
void SlashEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true, m_obj.isReverse);
}