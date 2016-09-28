/**
* @file   Computer.h
* @brief  �G��AI�V�X�e�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___COMPUTER_H
#define ___COMPUTER_H

#include "..\Common\StdAfx.h"
#include "..\Common\Enum.h"
#include "..\Object\IPlayer.h"
#include "..\Object\UI\SpecialGauge.h"

/**
* @brief �R���s���[�^�[�i�l�H�m�\�j�N���X
*/
class Computer
{
public:
	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void ThinkUpdate(vector<IPlPtr> pPlayer, int index, int computerCount, SpGaugePtr sp);

	/**
	* @brief �s�����l����
	*/
	void ThinkAction(vector<IPlPtr> pPlayer, int index);

	/**
	* @brief �ߋ������̍s��
	*/
	void ShortDistanceAction();

	/**
	* @brief ���������̍s��
	*/
	void MiddleDistanceAction();

	/**
	* @brief ���������̍s��
	*/
	void LongDistanceAction();

	/**
	* @brief �Q�[�W�ʂ��m�F����
	*/
	void CheckGauge(vector<IPlPtr> pPlayer, int index, SpGaugePtr sp);

private:
	/// ����v���C���[�i�l�ԁj
	IPlPtr target;

	/// ���̍s���Ɉڂ�܂ł̃t���[��
	unsigned int m_nextActionFrame;

	/// �s���t���[��
	unsigned int m_actionFrame;

	/// ���
	State m_state;

	/// �O��̏�Ԃ�ۑ�
	State m_oldState;
};

#endif