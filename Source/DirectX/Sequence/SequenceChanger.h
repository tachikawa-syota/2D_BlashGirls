/**
* @file   SequenceChanger.h
* @brief  �V�[���̐؂�ւ����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SEQUENCECHANGER_H
#define ___SEQUENCECHANGER_H

#include "ISequence.h"

/**
* @brief �V�[���̐؂�ւ����Ǘ�����N���X
*/
class SequenceChanger
{
private:
	/// ���݂̃V�[��
	ISequence* m_nowScene;

public:
	/**
	* @brief �R���X�g���N�^
	*/
	static SequenceChanger* GetInstance() {
		static SequenceChanger singleton;
		return &singleton;
	}

	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �V�[���̐؂�ւ�
	* @param �؂�ւ������V�[��������
	*/
	void ChangeScene(ISequence* seq);
	
	/**
	* @brief ���݂̃V�[�����擾����
	*/
	ISequence* GetNowScene();
};

#endif