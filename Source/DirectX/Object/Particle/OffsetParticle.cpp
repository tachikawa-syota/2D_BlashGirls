#include "OffsetParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
*/
OffsetParticle::OffsetParticle(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_OFFSET);

	// �p�����[�^�ݒ�
	m_obj.scale = 0.4f;
	// �����Ő����ʒu�ɃY���𔭐�������
	m_obj.pos.x = pos.x + Utility::Random(-20.0f, 20.0f);
	m_obj.pos.y = pos.y + Utility::Random(-20.0f, 20.0f);

	m_obj.alpha = ALPHA_MAX;

	// ���x�̐ݒ�
	m_v.x = Utility::Random(-5.0f, 5.0f);
	m_v.y = Utility::Random(-5.0f, 5.0f);
	// �O������
	m_add = {};
}

/**
* @brief �X�V
*/
bool OffsetParticle::Update()
{
	// �����x�ݒ�
	m_add.y = 0.3f;

	// �k��
	m_obj.scale -= 0.008f;

	// ���W�X�V
	m_obj.pos += m_v;
	// ���x�X�V
	m_v += m_add;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief �`��
*/
void OffsetParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}