#include "SwordTrajectoryEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param texid - �e�N�X�`���̔ԍ�
* @param pos   - �ʒu
* @param dir   - ����
* @param rot   - �p�x(�O�Ղ̊p�x��M�肽�����͐��l������B�f�t�H���g��0.0f)
*/
SwordTrajectoryEffect::SwordTrajectoryEffect(const int texid, const Vector2& pos, const Dir& dir, const float rot)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	for (int i = 0; i < SLASH_MAX; i++){
		hTex[i] = m_texData->GetSlashTexture(i);
	}

	// �ʒu��ݒ�
	m_obj.pos = pos;
	m_obj.alpha = ALPHA_MAX;
	m_obj.rot = rot;
	m_obj.scale = 0.0f;

	m_id = texid;

	if (dir == Dir::Left){
		m_obj.pos.x -= 50.0f;
		m_obj.isReverse = true;
	}
	else{
		m_obj.pos.x += 50.0f;
		m_obj.isReverse = false;
	}
}

/**
* @brief �X�V
*/
bool SwordTrajectoryEffect::Update()
{
	// �g�債�Ă���
	m_obj.scale += 0.07f;
	//�@�A���t�@�l�𔲂�
	m_obj.alpha -= 10;

	if (m_obj.scale > 1.15f){
		m_obj.scale = 1.15f;
	}

	return (m_obj.alpha < 0) ? true : false;
}

/**
* @brief �`��
*/
void SwordTrajectoryEffect::Render()
{
	m_2dTex->DrawTexture(hTex[m_id], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true, m_obj.isReverse);
}