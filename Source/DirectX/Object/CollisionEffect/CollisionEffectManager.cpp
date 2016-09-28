#include "CollisionEffectManager.h"
#include "..\IObject.h"

/**
* @brief �����蔻��t���̃G�t�F�N�g��ǉ�����
*/
void CollisionEffectManager::Add(IColEffectPtr p)
{
	m_colEffects.emplace_back(p);
}

/**
* @brief ������
*/
void CollisionEffectManager::Initialize()
{
	// �S�v�f�폜
	m_colEffects.clear();
}

/**
* @brief �����蔻��t���̃G�t�F�N�g���X�V����
*/
void CollisionEffectManager::Update()
{
	// �C�e���[�^���擾
	auto it = m_colEffects.begin();

	while (it != m_colEffects.end())
	{
		if ((*it)->Update()){
			// �폜
			it = m_colEffects.erase(it);
		}
		else{
			// �X�V
			++it;
		}
	}
}

/**
* @brief �����蔻��t���̃G�t�F�N�g��`�悷��
*/
void CollisionEffectManager::Render()
{
	// ���X�g���S�`��
	for (auto& c : m_colEffects)
	{
		c->Render();
	}
}

/**
* @brief �v���C���[�Ƃ̓����蔻��
*/
void CollisionEffectManager::CollisionCheckPlayer(IPlPtr obj)
{
	// �C�e���[�^���擾
	auto it = m_colEffects.begin();

	while (it != m_colEffects.end()){
		// �������Ă��邩�ۂ��̃`�F�b�N
		(*it)->CollisionCheckPlayer(obj);
		++it;
	}
}