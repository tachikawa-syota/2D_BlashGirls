#include "FormParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
*/
FormParticle::FormParticle(const Vector2& pos, const float scale)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_FORM);

	// �p�����[�^�ݒ�
	m_obj.scale = scale;
	// �����Ő����ʒu�ɃY���𔭐�������
	m_obj.pos.x = pos.x + Utility::Random(-20.0f, 20.0f);
	m_obj.pos.y = pos.y + Utility::Random(-20.0f, 20.0f);

	m_obj.alpha = ALPHA_MAX;

	// ���x�̐ݒ�
	m_v.x = Utility::Random(-4.0f, 4.0f);
	m_v.y = Utility::Random(-4.0f, 4.0f);
}

/**
* @brief �X�V
*/
bool FormParticle::Update()
{
	// �k��
	m_obj.scale -= 0.008f;

	// �A���t�@�l������
	m_obj.alpha -= 1;

	// ���W�X�V
	m_obj.pos += m_v;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief �`��
*/
void FormParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}