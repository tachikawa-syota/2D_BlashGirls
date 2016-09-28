/**
* @file   CollisionEffectManager.h
* @brief  �����蔻��t���G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___COLLISIONEFFECTMANAGER_H
#define ___COLLISIONEFFECTMANAGER_H

#include "..\IObject.h"

/**
* @brief �����蔻��t���G�t�F�N�g�Ǘ���
*/
class CollisionEffectManager
{
public:
	/**
	* @brief �C���X�^���X���擾����i�V���O���g���j
	*/
	static CollisionEffectManager* GetInstance(){
		static CollisionEffectManager singleton;
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
	void Add(IColEffectPtr p);

	/**
	* @brief �v���C���[�Ƃ̓����蔻��
	*/
	void CollisionCheckPlayer(IPlPtr obj);

private:
	/// �����蔻��t��
	list<IColEffectPtr> m_colEffects;
};

#endif