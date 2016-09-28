// --------------------------------------------------------
//
//	�p�J�V�X�e���Ɋ֌W���鏈���̋L�q
//
// --------------------------------------------------------

#include "HpGauge.h"
#include "..\..\Common\ParamLoader.h"

/**
* @brief ������
*/
void HpGauge::Initialize()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		m_damage[i] = 0.0f;
		m_Maxhp = GetPrm->HpMax;
		m_hpGauge[i] = GetPrm->HpMax;
		m_hpGaugeOld[i] = GetPrm->HpMax;
		m_isDead[i] = false;
		m_isDelete[i] = false;
	}
}

/**
* @brief �X�V
*/
void HpGauge::Update()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		if (m_isDelete[i])
		{
			m_hpGaugeOld[i] -= 20.0f;
			if (m_hpGaugeOld[i] <= m_hpGauge[i]){
				m_hpGaugeOld[i] = m_hpGauge[i];
				m_isDelete[i] = false;
			}
		}

		if (m_hpGauge[i] < 0)
		{
			m_hpGauge[i] = 0;
			m_isDead[i] = true;
		}

		// �_���[�W����
		m_hpGauge[i] -= m_damage[i];
		m_damage[i] = 0;
	}
}

/**
* @brief KO��Ԃ��ۂ�
* @return 0,1 - KO�����v���C���[�ԍ� , -1 - KO���Ă��Ȃ�
*/
int HpGauge::isDead()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		if (m_isDead[i])
		{
			return i;
		}
	}
	return -1;
}


/**
* @brief HP�c�ʂ��擾
*/
float HpGauge::GetHP(const int plNum)
{
	return m_hpGauge[plNum];
}

/**
* @brief �q�b�g�O��HP�ʂ��擾
*/
float HpGauge::GetOldHP(const int plNum)
{
	return m_hpGaugeOld[plNum];
}

/**
* @brief �ő�HP�ʂ��擾
*/
float HpGauge::GetMaxHp()
{
	return m_Maxhp;
}

/**
* @brief �_���[�W���Z
*/
void HpGauge::DamageAdd(const float damage, const int plNum)
{
	m_damage[plNum] = damage;
}

/**
* @brief �q�b�g�O��HP�����폜
*/
void HpGauge::SetOldGaugeDelete(const int plNum, const bool bFlag)
{
	m_isDelete[plNum] = bFlag;
}