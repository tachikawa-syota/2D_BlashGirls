/**
* @file   ISequence.h
* @brief  �V�[�N�G���X�C���^�[�t�F�C�X
* @author Syota Tachikawa
*/

#ifndef ___ISEQUENCE_H
#define ___ISEQUENCE_H

using namespace std;
#include <memory>

/**
* @brief �V�[�N�G���X�C���^�[�t�F�C�X�N���X
*/
__interface ISequence
{
	/**
	* @brief ������
	*/
	void Initialize();
	
	/**
	* @brief �쐬
	*/
	void Create();
	
	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �I��
	*/
	void Finalize();
};

#endif