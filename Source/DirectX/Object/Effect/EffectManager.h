/**
* @file   EffectManager.h
* @brief  �S�G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___EFFECTMANAGER_H
#define ___EFFECTMANAGER_H

#include "..\IObject.h"

/**
* @brief �G�t�F�N�g���Ǘ�����N���X
*/
class EffectManager
{
public:
	/**
	* @brief �C���X�^���X���擾����i�V���O���g���j
	*/
	static EffectManager* GetInstance(){
		static EffectManager singleton;
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
	* @brief �ǉ�
	*/
	void Add(IEffectPtr p);

private:
	/// �G�t�F�N�g���X�g
	list<IEffectPtr> effects;
};

#endif