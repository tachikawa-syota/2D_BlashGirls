#include "Command.h"
#include "..\DirectX\InputMask.h"

/**
* @brief �R���X�g���N�^
*/
Command::Command()
{
	Initialize();
}

/**
* @brief �f�X�g���N�^
*/
Command::~Command()
{

}

/**
* @brief ������
*/
void Command::Initialize()
{
	m_inputNum = 0;

	for (int i = 0; i < COMMAND_INPUT_MAX; i++){
		m_inputBuffer[i] = {};
	}

	m_inputFrame = 0;
	m_inputData = NULL;
	m_oldInputData = NULL;
	m_skill = -1;
}

/**
* @brief �X�L���f�[�^
*/
const int Command::SkillCommand[COMMAND_MAX][COMMAND_INPUT_MAX] = 
{
	// �Ă��ƂŁ[��
	{ INPUT_DOWN, INPUT_RIGHT, INPUT_01, -1 },
	
	// �Z�f�[�^�I�[
	{ -1 },
};


/**
* @brief �f�o�C�X�̓��͏����擾����
*/
void Command::InputCommand(unsigned int flag)
{
	m_inputData = flag;

	if (m_inputData == 0) return;

	if (m_inputData != m_oldInputData)
	{
		// �t���[����������
		m_inputFrame = 0;

		// �o�b�t�@�ɓ��̓f�[�^��ۑ�
		m_inputBuffer[m_inputNum] = m_inputData;

		// ���̃R�}���h�ɐi�߂�
		m_inputNum++;

		// �X�L���̃`�F�b�N
		m_skill = SkillCheck();
	}

	// �P�\�t���[���𒴂���Ə����������i���s�j
	if (m_inputFrame > INPUT_VALID_FRAME){
		Initialize();
	}

	// �R�}���h���͐����ő�l�𒴂���Ə�����
	if (m_inputNum >= COMMAND_INPUT_MAX){
		Initialize();
	}

	// ���͏���ۑ�����
	m_oldInputData = m_inputData;

	// �t���[�������Z����
	m_inputFrame++;
}


/**
* @brief �R�}���h��񂩂�X�L���f�[�^���擾����
*/
const int Command::SkillCheck()
{
	int skill = -1;
	int maxConbo = NULL;

	// �o���Z��T��
	maxConbo = 0;

	for (int i = 0; SkillCommand[i][0] != -1; i++)
	{
		// �R�}���h�f�[�^�Ɠ��͂����f�[�^�����������𒲂ׂ�
		int j = 0;
		while (SkillCommand[i][j] == m_inputBuffer[j]) j++;

		// �R�}���h�f�[�^�̏I�[�܂œ����������ꍇ��
		// ���̋Z�̃R�}���h���ƋZ�i���o�[��ۑ�����
		// �Ȃ��ȑO�ɂ����Ƒ����̃R�}���h��v���Z�ƓK�����Ă�����L�����Ȃ�
		if (SkillCommand[i][j] == -1)
		{
			maxConbo = j;
			skill = i;
		}
	}

	// �X�L���s��v
	if (maxConbo == 0) {
		return -1;
	}

	// �I�΂ꂽ�X�L���ԍ���Ԃ�
	return skill;
}

/**
* @brief �X�L���ԍ����擾����
* @return -1 �̓R�}���h�s����(�������Ȃ�)
*/
const int Command::GetSkillNumber()
{
	return m_skill;
}