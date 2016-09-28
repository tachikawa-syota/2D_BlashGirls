/**
* @file   ParticleManager.h
* @brief  �S�p�[�e�B�N�����Ǘ�������
* @author Syota Tachikawa
*/

#ifndef ___PARTICLEMANAGER_H
#define ___PARTICLEMANAGER_H

#include "..\IObject.h"

/**
* @brief �p�[�e�B�N�����Ǘ�����N���X
*/
class ParticleManager
{
public:
	/**
	* @brief �C���X�^���X���擾����i�V���O���g���j
	*/
	static ParticleManager* GetInstance(){
		static ParticleManager singleton;
		return &singleton;
	}
	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �p�[�e�B�N����ǉ�����
	*/
	void Add(IParticlePtr p);

private:
	/// �p�[�e�B�N�����X�g
	list<IParticlePtr> particles;
};

#endif