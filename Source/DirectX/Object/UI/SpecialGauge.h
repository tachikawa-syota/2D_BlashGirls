/**
* @file SpecialGauge.h
* @brief �K�E�Z�Q�[�W�Ɋ֌W���鏈�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SPECIALGAUGE_H
#define ___SPECIALGAUGE_H

#include "..\..\Common\StdAfx.h"

/**
* @brief �K�E�Z�Q�[�W�Ɋ֌W���鏈�����Ǘ�����N���X
*/
class SpecialGauge
{
public:
	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �Q�[�W�𑝉�����
	*/
	void Add(float addValue, int plNum);

	/**
	* @brief �Q�[�W���g�p��Ԃɂ���
	*/
	void Use(int plNum);

	/**
	* @brief �Q�[�W���g�p�ł��邩�ۂ�
	*/
	bool IsUseGauge(const State& useKind, int plNum);

	/**
	* @brief �Q�[�W�ʂ��擾
	*/
	float GetGauge(int index);

	/**
	* @brief �Q�[�W�{�����擾
	*/
	int GetGaugeCount(int index);

private:
	/// �Q�[�W�ʂ̕`��ʒu
	float m_gaugeX[JOY_MAX];

	/// �Q�[�W��
	float m_gauge[JOY_MAX];

	/// �Q�[�W�{��
	int m_gaugeNum[JOY_MAX];

	/// �Q�[�W������
	float m_addValue[JOY_MAX];

	/// �Q�[�W�̏��
	SpecialGaugeState m_gaugeState[JOY_MAX];

	/// �Q�[�W�̎g�p���
	State m_useKind[JOY_MAX];
	
	/// �����e�N�X�`���̈ʒu
	float m_texX[4];
};

/// �K�E�Z�Q�[�W�N���X�̃X�}�[�g�|�C���^���`
using SpGaugePtr = shared_ptr<SpecialGauge>;

#endif