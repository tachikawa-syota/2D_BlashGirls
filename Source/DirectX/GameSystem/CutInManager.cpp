#include "CutInManager.h"
#include "..\Object\Effect\EffectManager.h"
#include "..\Object\Effect\ShineEffect.h"

/**
* @brief �쐬
* @param name - �L�����N�^�[�̖��O(Enum��`�������̂��g�p����)
* @param index - �L�����N�^�[�̔ԍ�
* @param pos - �`�悷��ʒu
*/
void CutInManager::Create(int name, int index, const Vector2& pos)
{
	// �\���t���OON
	m_isDisp = true;
	// �t���[��������
	m_frame = NULL;
	// ���̃G�t�F�N�g�𐶐�
	EffectManager::GetInstance()->Add(make_shared<ShineEffect>(pos));
	// �J�b�g�C���̐���
	m_cutin = new CutIn(name, index);
}

/**
* @brief ������
*/
void CutInManager::Initialize()
{
	m_cutin = nullptr;
	m_isDisp = false;
	m_frame = NULL;
}

/**
* @brief �X�V
*/
void CutInManager::Update()
{
	if (!m_isDisp) return;

	// �X�V
	m_cutin->Update();

	// ���t���[���o�߂ō폜
	if (m_frame >= 45){
		delete m_cutin;
		m_isDisp = false;
	}

	// �t���[�������Z����
	m_frame++;
}

/**
* @brief �`��
*/
void CutInManager::Render()
{
	if (m_isDisp) m_cutin->Render();
}

/**
* @brief �\�������ǂ����̊m�F
*/
bool CutInManager::IsPlayCutIn()
{
	return m_isDisp;
}