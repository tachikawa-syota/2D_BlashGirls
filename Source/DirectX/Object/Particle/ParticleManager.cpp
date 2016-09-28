#include "ParticleManager.h"
#include "..\IObject.h"

/**
* @brief �p�[�e�B�N����ǉ�����
*/
void ParticleManager::Add(IParticlePtr p)
{
	particles.emplace_back(p);
}

/**
* @brief ������
*/
void ParticleManager::Initialize()
{
	// �S�v�f�폜
	particles.clear();
}

/**
* @brief �p�[�e�B�N�����X�V����
*/
void ParticleManager::Update()
{
	// �C�e���[�^���擾
	auto it = particles.begin();

	while (it != particles.end())
	{
		if ((*it)->Update()){
			// �폜
			it = particles.erase(it);
		}
		else{
			// �X�V
			++it;
		}
	}
}

/**
* @brief �p�[�e�B�N����`�悷��
*/
void ParticleManager::Render()
{
	// ���X�g���S�`��
	for (auto& p : particles)
	{
		p->Render();
	}
}