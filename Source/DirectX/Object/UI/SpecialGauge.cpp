#include "SpecialGauge.h"
#include "..\..\Common\ParamLoader.h"

/**
* @brief ������
*/
void SpecialGauge::Initialize()
{
	// �Q�[�W�e�N�X�`��
	m_gaugeX[PLAYER1] = 280.0f;
	m_gaugeX[PLAYER2] = 990.0f;

	// �����e�N�X�`�����W
	m_texX[PLAYER1] = 258.0f;
	m_texX[PLAYER2] = 1018.0f;

	for (int i = 0; i < JOY_MAX; i++)
	{
		m_gaugeNum[i] = 0;
		m_gauge[i] = 0.0f;
		m_addValue[i] = 0.0f;
		m_gaugeState[i] = SpecialGaugeState::None;
	}
}

/**
* @brief �X�V
*/
void SpecialGauge::Update()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		switch (m_gaugeState[i])
		{
		case SpecialGaugeState::None:
		case SpecialGaugeState::Empty:
			// �������Ȃ�
			break;

		case SpecialGaugeState::Add:

			// �Q�[�W�����Z����
			m_gauge[i] += m_addValue[i];

			// �Q�[�W������萔�𒴂�����Q�[�W�{�������Z����
			if (m_gauge[i] > GetPrm->MaxSpecialGauge)
			{
				m_gauge[i] = 0.0f;
				m_gaugeNum[i]++;
			}

			// 5�ȏ�ɂ͂Ȃ�Ȃ�
			if (m_gaugeNum[i] >= 5){
				m_gaugeNum[i] = 5;
				m_gauge[i] = 0.0f;
				m_gaugeState[i] = SpecialGaugeState::Full;
			}

			// ���Z���I������珉��������
			m_addValue[i] = 0.0f;
			break;

			// ���^��
		case SpecialGaugeState::Full:

			break;

		case SpecialGaugeState::Use:

			switch (m_useKind[i])
			{
			case State::StrongAttack:
				m_gaugeNum[i] -= 1;
				break;

			case State::SpecialAttack:
				m_gaugeNum[i]-= 2;
				break;

			default:
			// �o�^����Ă����ԈȊO�ł͉������Ȃ�
				break;
			}

			// �g���I��������Ԃ�None�ɂ���
			m_gaugeState[i] = SpecialGaugeState::None;
			break;
		}
	}
}

/**
* @brief �Q�[�W�ʂ̑���
* @param addValue - ������
* @param plNum - �v���C���[�ԍ�
*/
void SpecialGauge::Add(float addValue, int plNum)
{
	// �Q�[�W���g�p���������牽�����Ȃ�
	if (m_gaugeState[plNum] == SpecialGaugeState::Use) return;

	m_gaugeState[plNum] = SpecialGaugeState::Add;
	m_addValue[plNum] += addValue;
}

/**
* @brief �Q�[�W���g�p��Ԃɂ���
* @param plNum - �v���C���[�ԍ�
*/
void SpecialGauge::Use(int plNum)
{
	m_gaugeState[plNum] = SpecialGaugeState::Use;
}

/**
* @brief �Q�[�W���g�p�ł��邩�ۂ�
* @param useKind - �Q�[�W���g�p����Z�̎��
* @param plNum - �v���C���[�ԍ�
* @return true�Ŕ���
*/
bool SpecialGauge::IsUseGauge(const State& useKind, int plNum)
{
	// ��Ԃ�ۑ�
	m_useKind[plNum] = useKind;

	switch (m_useKind[plNum])
	{
	case State::StrongAttack:
		// �Q�[�W�P�{�ȏ�
		if (m_gaugeNum[plNum] >= 1)
			return true;
		break;

	case State::SpecialAttack:
		// �Q�[�W�Q�{�ȏ�
		if (m_gaugeNum[plNum] >= 2)
			return true;
		break;
	}
	
	return false;
}

float SpecialGauge::GetGauge(int index)
{
	return m_gauge[index];
}

int SpecialGauge::GetGaugeCount(int index)
{
	return m_gaugeNum[index];
}