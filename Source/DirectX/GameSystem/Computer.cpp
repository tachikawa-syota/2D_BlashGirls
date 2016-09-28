#include "Computer.h"
#include "..\DirectX\InputMask.h"
#include "..\Object\UI\SpecialGauge.h"
#include "..\Common\Utility.h"

/**
* @brief ������
*/
void Computer::Initialize()
{
	m_actionFrame = 0;
	m_nextActionFrame = 60;
}

/**
* @brief �v�l�̍X�V
* @param �R���s���[�^�[�̐����擾
*/
void Computer::ThinkUpdate(std::vector<IPlPtr> pPlayer, int index, int computerCount, SpGaugePtr sp)
{
	// �R���s���[�^�[�����݂��Ȃ�������I��
	if (computerCount == 0) return;
	// �P�o�̓R���s���[�^�[�ɂȂ�Ȃ�
	if (computerCount == 1 && index == 0) return;

	// �^�[�Q�b�g��ݒ�i1P�͕K���v���C���[������j
	target = pPlayer[PLAYER1];

	if (!pPlayer[index]->CanControll() || !pPlayer[index]->isControll()) return;

	// �s���t���[�������Z����
	m_actionFrame++;

	// ���t���[���𒴂��Ȃ�����
	if (m_actionFrame > m_nextActionFrame){
		m_nextActionFrame = 60 + m_actionFrame;

		// �Q�[�W�ʂ��m�F����
		CheckGauge(pPlayer, index, sp);

		// �O��̍s�����p������
		pPlayer[index]->SetState(m_oldState);
		return;
	}

	// �v�l�J�n
	ThinkAction(pPlayer, index);

	// �Q�[�W�ʂ��m�F����
	CheckGauge(pPlayer, index, sp);

	// �R���s���[�^���X�V����
	pPlayer[index]->SetState(m_state);
}

/**
* @brief �s�����l����
*/
void Computer::ThinkAction(vector<IPlPtr> pPlayer, int index)
{
	// ��Ԃ�ۑ�����
	m_oldState = m_state;

	// �v���C���[���m�̋������v�Z
	float dist = Utility::GetDistance(pPlayer[PLAYER1]->GetPos().x, pPlayer[PLAYER2]->GetPos().x);

	// �ΏۂƋ���������Ă���
	if (dist > 400.0f)
	{
		LongDistanceAction();
	}
	// �ΏۂƂ�����������������Ă���
	else if (dist > 230.0f)
	{
		MiddleDistanceAction();
	}
	// �ΏۂƋ������߂�
	else{
		ShortDistanceAction();
	}
}

/**
* @brief �^�[�Q�b�g�Ƌߋ������̍s��
*/
void Computer::ShortDistanceAction()
{
	int rand = Utility::Random(0, 5);
	switch (rand)
	{
	case 0:
		m_state = State::MediumAttack;
		break;

	case 1:
		m_state = State::Advance;
		break;

	case 2:
		m_state = State::BackStep;
		break;

	case 3:
		m_state = State::Neutral;
		break;

	case 4:
		m_state = State::SpecialAttack;
		break;

	case 5:
		m_state = State::StrongAttack;
		break;
	}

	int rand2 = Utility::Random(0, 10);

	switch (target->GetState())
	{
	case State::Guard:
		// �K�[�h�������d�|����
		m_state = State::SquatAttack;
		break;

		// �e��U��
	case State::DashAttack:
	case State::MediumAttack:
	case State::RaidAttack:
	case State::StrongAttack:
	case State::WeakAttack:
	case State::SpecialAttack:
	case State::AttackSpecialPursuit:
		if (rand2 > 3){
			m_state = State::Guard;
		}
		break;

		// ���Ⴊ�ݍU��
	case State::SquatAttack:
		if (rand2 > 3){
			m_state = State::SquatGuard;
		}
		break;

	}

	// �W�����v���Ă�����
	if (m_state == State::Jump || m_state == State::JumpFront)
	{
		// �W�����v�U��
		m_state = State::JumpAttack;
	}
}

/**
* @brief �^�[�Q�b�g�ƒ��������̍s��
*/
void Computer::MiddleDistanceAction()
{
	int rand = Utility::Random(0, 3);
	switch (rand)
	{
	case 0:
		m_state = State::Guard;
		break;
	case 1:
	{
			  int rand2 = Utility::Random(0, 100);
			  if (rand2 > 90){
				  m_state = State::RaidAttack;
			  }
			  else{
				  m_state = State::Dash;
			  }
			  break;
	}
	case 2:
	case 3:
		m_state = State::Dash;
		break;
	}
}

/**
* @brief �^�[�Q�b�g�Ɖ��������̍s��
*/
void Computer::LongDistanceAction()
{
	int rand = Utility::Random(0, 6);
	switch (rand)
	{
	case 0:
	case 1:
	case 2:
		m_state = State::Dash;
		break;

	case 3:
		m_state = State::SpecialAttack;
		break;

	case 4:
		m_state = State::RaidAttack;
		break;

	case 5:
		m_state = State::Advance;
		break;

	case 6:
		m_state = State::UnderAttack;
		break;
	}
}

/**
* @brief �Q�[�W�ʂ��m�F����
*/
void Computer::CheckGauge(std::vector<IPlPtr> pPlayer, int index, SpGaugePtr sp)
{
	if (m_state == State::SpecialAttack){
		// �Q�[�W�ʂ̊m�F�i�s�����Ă��珈�����Ȃ��j
		if (!sp->IsUseGauge(State::SpecialAttack, pPlayer[index]->GetID())) {
			m_state = State::Neutral;
			return;
		}
		else{
			// �Q�[�W�̎g�p
			sp->Use(pPlayer[index]->GetID());
		}
	}
	else if (m_state == State::StrongAttack){
		// �Q�[�W�ʂ̊m�F�i�s�����Ă��珈�����Ȃ��j
		if (!sp->IsUseGauge(State::StrongAttack, pPlayer[index]->GetID())) {
			m_state = State::Neutral;
			return;
		}
		else{
			// �Q�[�W�̎g�p
			sp->Use(pPlayer[index]->GetID());
		}
	}
}