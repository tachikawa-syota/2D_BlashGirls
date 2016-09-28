/**
* @file   CommandManager.h
* @brief  �R�}���h���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___COMMANDMANAGER_H
#define ___COMMANDMANAGER_H

#include "..\Common\StdAfx.h"

// �P�\�t���[��
const int INPUT_VALID_FRAME = 60;
/// �R�}���h�ő吔
const int COMMAND_MAX = 1 + 1;
/// �R�}���h���͍ő吔
const int COMMAND_INPUT_MAX = 4;

// �O���錾
class InputMask;

class Command
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Command();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~Command();
	
	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�L���f�[�^
	*/
	static const int SkillCommand[COMMAND_MAX][COMMAND_INPUT_MAX];

	/**
	* @brief �f�o�C�X�̓��͏����擾����
	*/
	void InputCommand(unsigned int flag);

	/**
	* @brief �X�L���ԍ����擾����
	* @return -1 �̓R�}���h�s����(�������Ȃ�)
	*/
	const int GetSkillNumber();

private:
	// ���̓t���[��
	unsigned int m_inputFrame;

	// ���͏���ۑ�
	unsigned int m_inputData;

	// �P�t���[���O�̓��͏��
	unsigned int m_oldInputData;

	// ���͂��ꂽ�R�}���h�̐�
	int m_inputNum;

	// ���̓f�[�^
	int m_inputBuffer[COMMAND_INPUT_MAX];

	/// �X�L���f�[�^
	int m_skill;

	/**
	* @brief �R�}���h��񂩂�X�L���f�[�^���擾����
	*/
	const int SkillCheck();
};

#endif