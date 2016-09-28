/**
* @file HpGauge.h
* @brief HP�Q�[�W�Ɋ֌W���鏈�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___HPGAUGE_H
#define ___HPGAUGE_H

#include "..\..\Common\StdAfx.h"

/**
* @brief HP�Q�[�W�Ɋ֌W���鏈�����Ǘ�����N���X
*/
class HpGauge
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
	* @brief ������
	*/
	int isDead();

	/**
	* @brief HP�c�ʂ��擾
	* @param �v���C���[�̔ԍ�
	*/
	float GetHP(const int plNum);

	/**
	* @brief �q�b�g�O��HP�ʂ��擾
	* @param �v���C���[�̔ԍ�
	*/
	float GetOldHP(const int plNum);

	/**
	* @brief �ő�HP�ʂ��擾
	*/
	float GetMaxHp();

	/**
	* @brief �_���[�W���Z
	* @param damage - ���Z����_���[�W�̗�
	* @param plNum - �v���C���[�̔ԍ�
	*/
	void DamageAdd(const float damage, const int plNum);

	/**
	* @brief �q�b�g�O��HP�����폜
	* @param �v���C���[�̔ԍ�
	*/
	void SetOldGaugeDelete(const int plNum, const bool bFlag = false);

private:
	const float GAUGE_SIZE_X = 289.0f;

	/// �_���[�W��
	float m_damage[JOY_MAX];

	/// HP�c��
	float m_hpGauge[JOY_MAX];

	/// �q�b�g�O��HP�c��
	float m_hpGaugeOld[JOY_MAX];

	/// �ő�HP
	float m_Maxhp;

	/// ���S
	bool m_isDead[JOY_MAX];		/// true�Ő퓬�s�\
	bool m_isDelete[JOY_MAX];

};

#endif