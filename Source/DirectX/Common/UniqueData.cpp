#include "UniqueData.h"

/**
* @brief �I�������L�����N�^�[�̎�ނ�ݒ�
* @param �L�����N�^�[�f�[�^�̔z����|�C���^�Ŏ󂯎��
*/
void UniqueData::SetSelectCharacter(const int* select)
{
	m_selectChara = select;
}

/**
* @brief �I�������L�����N�^�[���擾
* @return �L�����N�^�[�f�[�^�̃|�C���^
*/
const int* UniqueData::GetSelectCharacter() const
{
	return m_selectChara;
}

/**
* @brief �v���C���[�̐l����ݒ肷��
* @param playerCount - �v���C���[�̐�
* @param computerCount - �R���s���[�^�[�̐�
*/
void UniqueData::SetPlayerCount(int playerCount, int computerCount)
{
	m_playerCount = playerCount;
	m_computerCount = computerCount;
}

/**
* @brief �v���C���[�̐l�����擾
*/
int UniqueData::GetPlayerCount()
{
	return m_playerCount;
}

/**
* @brief �R���s���[�^�[�̐l�����擾
*/
int UniqueData::GetComputerCount()
{
	return m_computerCount;
}

/**
* @brief �s�k�����v���C���[��ݒ�
* @param �s�k�����v���C���[�̔ԍ�
*/
void UniqueData::SetLosePlayer(const int index)
{
	m_losePl = index;
}

/**
* @brief �s�k�����v���C���[���擾
*/
int UniqueData::GetLosePlayer() const
{
	return m_losePl;
}

/**
* @brief �Q�[�����[�h��ݒ�
*/
void UniqueData::SetGameMode(const GameMode mode)
{
	m_gameMode = mode;
}

/**
* @brief �Q�[�����[�h���擾
*/
const GameMode UniqueData::GetGameMode() const
{
	return m_gameMode;
}
