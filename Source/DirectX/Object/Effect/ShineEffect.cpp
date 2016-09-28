#include "ShineEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
* @param �`��ʒu
*/
ShineEffect::ShineEffect(const Vector2& pos)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// �e�N�X�`���R�s�[
	m_obj[0].handle = m_texData->GetTexture(TEX_SHINE2);
	m_obj[1].handle = m_texData->GetTexture(TEX_SHINE2);

	// �ʒu��ݒ�
	for (int i = 0; i != m_obj.size(); i++){
		m_obj[i].pos = pos;
		m_obj[i].scale = 0.5f;
	}
	m_subWork = 0;
}

/**
* @brief �X�V
*/
bool ShineEffect::Update()
{
	for (int i = 0; i != m_obj.size(); i++)
	{
		switch (m_subWork)
		{
		case 0:
			m_obj[i].scale += 0.4f;
			if (m_obj[i].scale > 2.0f){
				m_subWork++;
			}
			break;

		case 1:
			m_obj[i].scale -= 0.4f;
			if (m_obj[i].scale < 0.0f){
				m_subWork++;
			}
			break;
		}
	}

	return (m_obj[1].scale < 0.0f) ? true : false;
}

/**
* @brief �`��
*/
void ShineEffect::Render()
{
	for (auto& obj : m_obj){
		m_2dTex->DrawTexture(obj.handle, obj.pos.x - GetCameraPos, obj.pos.y, 0.0f, obj.scale);
	}
}