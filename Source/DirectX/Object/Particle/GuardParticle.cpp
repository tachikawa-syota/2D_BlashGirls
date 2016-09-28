#include "GuardParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param pos - �ʒu
* @param scale - �傫��
*/
GuardParticle::GuardParticle(const Vector2& pos,
	const float scale
	)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	m_obj.handle = m_texData->GetTexture(TEX_GUARD_EFFECT);
	// �����t���[���̐ݒ�
	m_liveFrame = 240;
	m_obj.scale = scale;
	m_obj.pos = pos;

	m_v.x = Utility::Random(-4.0f, 4.0f);
	m_v.y = Utility::Random(-4.0f, 4.0f);
	m_obj.alpha = 255;
}

/**
* @brief �X�V
*/
bool GuardParticle::Update()
{
	// ���x���Z
	m_obj.scale -= 0.02f;

	// ���W�X�V
	m_obj.pos += m_v;

	if (m_obj.scale < 0.0f)
		return true;

	if (m_liveFrame < 0)
		return true;

	if (m_obj.pos.y < 0.0f || m_obj.pos.y > 720.0f)
		return true;

	return false;
}

/**
* @brief �`��
*/
void GuardParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}