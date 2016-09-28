#include "StarParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
* @param scale - �傫��
* @param alpha - �A���t�@�l
*/
StarParticle::StarParticle(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_STAR);

	// �e��p�����[�^�̐ݒ�
	m_obj.scale = 1.2f;
	m_obj.pos = pos;
	m_obj.rot = 0.0f;
	m_v.x = Utility::Random(-4.0f, -1.0f);
	m_v.y = Utility::Random(2.0f, 6.0f);

	// �d�͗p
	m_add = { 0.0f, 0.03f };
	m_obj.alpha = ALPHA_MAX;

}

/**
* @brief �X�V
*/
bool StarParticle::Update()
{
	// ��]������
	m_obj.rot += 20.0f;

	// �A���t�@�l�𔲂�
	m_obj.alpha -= 4;

	// ���W�X�V
	m_obj.pos += m_v;

	// ���x�X�V
	m_v += m_add;

	return (m_obj.alpha < ALPHA_MIN) ? true : false;
}

/**
* @brief �`��
*/
void StarParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true);
}