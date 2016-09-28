#include "SubSpaceStage.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\StarParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief �R���X�g���N�^
*/
SubSpaceStage::SubSpaceStage()
{
	// �C���X�^���X���擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	m_lightAlpha = ALPHA_MIN;
	m_stageAlpha = ALPHA_MAX;
	m_isEffectScale = false;
	m_effectScale = 0.0f;
}

/**
* @brief �f�X�g���N�^
*/
SubSpaceStage::~SubSpaceStage()
{
	SafeDelete(m_2dTex);
	SafeDelete(m_texData);
}

/**
* @brief �X�V
*/
bool SubSpaceStage::Update()
{
	// ��ʃT�C�Y���甼��������
	float starPosX = static_cast<float>(rand() % 1280);

	// �w�i�ɐ��p�[�e�B�N���𐶐�����
	if (m_frame % 80 == 0){
		ParticleManager::GetInstance()->Add(make_shared<StarParticle>(Vector2(starPosX, -1.0f)));
	}

	// �A���t�@�l��������i���Z�����p�j
	static float add;
	add += 0.02f;
	m_lightAlpha = static_cast<int>(sin(add) * ALPHA_MAX);

	// �o�߃t���[���ɉ����Ĕw�i�ɃG�t�F�N�g����������
	if (m_frame % 350 == 0){
		m_isEffectScale = true;
	}
	// �g��
	if (m_isEffectScale){
		m_effectScale += 0.2f;
	}
	// �傫������
	if (m_effectScale >= 10.0f){
		m_isEffectScale = false;
		m_effectScale = 0.0f;
	}

	// �t���[�������Z����
	m_frame++;

	// �폜���Ȃ�(�Œ�ŕԂ�)
	return false;
}

/**
* @brief �`��
*/
void SubSpaceStage::Render()
{
	// �w�i
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG), 640.0f - GetCameraPos, 360.0f, 0.0f, 1.0f, m_stageAlpha);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_FROST), 630.0f - GetCameraPos, 280.0f, 0.0f, 1.5f, m_stageAlpha, true);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BLUE_RING), 640.0f - GetCameraPos, 360.0f, 0.0f, m_effectScale, m_stageAlpha, true);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG_SPHERE), 640.0f - GetCameraPos, 280.0f, 0.0f, 0.5f, m_stageAlpha);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT2), 640.0f - GetCameraPos, 280.0f, 0.0f, 2.5f, m_lightAlpha, true);
	// ��
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG_FLOOR), 640.0f - GetCameraPos, 656.0f, 0.0f, 1.0f, m_stageAlpha);
}

/**
* @brief �A���t�@�l�̕ύX(����X�L�����g�������ɔw�i���Â�����p�Ŏg��)
*/
void SubSpaceStage::ChangeAlpha(int alpha)
{
	m_stageAlpha = alpha;
}