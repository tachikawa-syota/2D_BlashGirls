#include "WaveEffect.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\Common\ParamLoader.h"

/**
* @brief �R���X�g���N�^
*/
WaveEffect::WaveEffect(const Vector2& pos, const Dir& dir)
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �e�N�X�`���R�s�[
	for (int i = 0; i < WAVE_MAX; i++){
		m_hTex[i] = m_texData->GetWaveTexture(i);
	}

	// �ʒu��ݒ�
	m_obj.pos = pos;
	
	// �L�����N�^�[���������Ȃ�e�N�X�`���𔽓]������
	if (dir == Dir::Right){
		m_obj.pos.x -= 80.0f;
		m_obj.isReverse = false;
	}
	else{
		m_obj.pos.x += 80.0f;
		m_obj.isReverse = true;
	}
	// ���W��␳����
	m_obj.pos.y += 80.0f;

	// �e��J�E���^�[�̏�����
	loopCount = 0;
	m_animFrame = 0;
	m_animation = 0;
}

/**
* @brief �X�V
*/
bool WaveEffect::Update()
{
	if (m_animFrame % 5 == 0)
	{
		m_animation++;
		if (m_animation >= GetPrm->WaveEffectMaxAnimation){
			m_animation = 0;
			loopCount++;
		}
	}

	// �A�j���[�V�����t���[�������Z
	m_animFrame++;

	return (loopCount > 2) ? true : false;
}

/**
* @brief �`��
*/
void WaveEffect::Render()
{
	m_2dTex->DrawTexture(m_hTex[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, 1.0f, ALPHA_MAX, false, m_obj.isReverse);
}