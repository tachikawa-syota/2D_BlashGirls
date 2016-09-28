/**
* @file IObject.h
* @brief �I�u�W�F�N�g�̃C���^�[�t�F�C�X
* @author Syota Tachikawa
*/

#ifndef ___IOBJECT_H
#define ___IOBJECT_H

// �h����Ŏg�p����w�b�_��\�߃C���N���[�h���Ă���
#include "..\DirectX\GraphicsLib.h"
#include "..\Common\FileData.h"
#include "..\Common\Struct.h"
#include "IPlayer.h"

/**
* @brief �I�u�W�F�N�g�C���^�[�t�F�C�X
*/
__interface IObject
{
	/**
	* @brief �X�V
	*/
	bool Update();

	/**
	* @brief �`��
	*/
	void Render();
};

/**
* @brief �p�[�e�B�N���C���^�[�t�F�C�X
*/
__interface IParticle : public IObject
{
};

/**
* @brief �G�t�F�N�g�C���^�[�t�F�C�X
*/
__interface IEffect : public IObject
{
};

/**
* @brief �X�e�[�W�C���^�[�t�F�C�X
*/
__interface IStage : public IObject
{
	/**
	* @brief �X�e�[�W�S�̂̃A���t�@�l��ύX����
	*/
	void ChangeAlpha(int alpha);
};

/**
* @brief �����蔻������G�t�F�N�g�C���^�[�t�F�C�X
*/
__interface ICollisionEffect : public IObject
{
	/**
	* @brief �v���C���[�Ƃ̓����蔻��
	*/
	void CollisionCheckPlayer(IPlPtr obj);
};

/// �G�t�F�N�g�C���^�[�t�F�C�X�̃X�}�[�g�|�C���^���`
using IEffectPtr = shared_ptr<IEffect>;

/// �p�[�e�B�N���̃X�}�[�g�|�C���^���`
using IParticlePtr = shared_ptr<IParticle>;

/// �����蔻��t���G�t�F�N�g�C���^�[�t�F�C�X�̃X�}�[�g�|�C���^���`
using IColEffectPtr = shared_ptr<ICollisionEffect>;

/// �X�e�[�W�C���^�[�t�F�C�X�̃X�}�[�g�|�C���^���`(���j�[�N�|�C���^)
using IStagePtr = unique_ptr<IStage>;

#endif