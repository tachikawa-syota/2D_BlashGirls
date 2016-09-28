#ifndef ___UNIQUEDATA_H
#define ___UNIQUEDATA_H

#include "Enum.h"

/**
* @brief ��ӂȃf�[�^�Ǘ��N���X
*/
class UniqueData
{
public:
	/**
	* @brief �C���X�^���X�擾(�V���O���g��)
	*/
	static UniqueData* GetInstance(){
		static UniqueData singleton;
		return &singleton;
	}

	/**
	* @brief �I�������L�����N�^�[�̎�ނ�ݒ�
	* @param �L�����N�^�[�f�[�^�̔z����|�C���^�Ŏ󂯎��
	*/
	void SetSelectCharacter(const int* select);

	/**
	* @brief �I�������L�����N�^�[���擾
	* @return �L�����N�^�[�f�[�^�̃|�C���^
	*/
	const int* GetSelectCharacter() const;

	/**
	* @brief �v���C���[�̐l����ݒ肷��
	* @param playerCount - �v���C���[�̐�
	* @param computerCount - �R���s���[�^�[�̐�
	*/
	void SetPlayerCount(int playerCount, int computerCount);

	/**
	* @brief �v���C���[�̐l�����擾
	*/
	int GetPlayerCount();

	/**
	* @brief �R���s���[�^�[�̐l�����擾
	*/
	int GetComputerCount();

	/**
	* @brief �s�k�����v���C���[��ݒ�
	*/
	void SetLosePlayer(const int index);

	/**
	* @brief �s�k�����v���C���[���擾
	*/
	int GetLosePlayer() const;

	/**
	* @brief �Q�[�����[�h��ݒ�
	*/
	void SetGameMode(const GameMode mode);

	/**
	* @brief �Q�[�����[�h���擾
	*/
	const GameMode GetGameMode() const;

private:
	/// �I�������L�����N�^�[
	const int* m_selectChara;

	/// �v���C���[�̐l��
	int m_playerCount;

	/// �R���s���[�^�[�̐l��
	int m_computerCount;

	/// �s�k�����L�����N�^�[�ԍ�
	int m_losePl;

	/// �Q�[�����[�h
	GameMode m_gameMode;
};

#endif