#include "..\IObject.h"
#include "EffectManager.h"

/**
* @brief �G�t�F�N�g��ǉ�����
*/
void EffectManager::Add(IEffectPtr p)
{
	effects.emplace_back(p);
}

/**
* @brief ������
*/
void EffectManager::Initialize()
{
	// �S�v�f�폜
	effects.clear();
}

/**
* @brief �G�t�F�N�g���X�V����
*/
void EffectManager::Update()
{
	// �C�e���[�^���擾
	auto it = effects.begin();

	while (it != effects.end())
	{
		if ((*it)->Update()){
			// �폜
			it = effects.erase(it);
		}
		else{
			// �X�V
			++it;
		}
	}
}

/**
* @brief �G�t�F�N�g��`�悷��
*/
void EffectManager::Render()
{
	// ���X�g���S�`��
	for (auto& e : effects)
	{
		e->Render();
	}
}