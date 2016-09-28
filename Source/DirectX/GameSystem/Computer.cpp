#include "Computer.h"
#include "..\DirectX\InputMask.h"
#include "..\Object\UI\SpecialGauge.h"
#include "..\Common\Utility.h"

/**
* @brief 初期化
*/
void Computer::Initialize()
{
	m_actionFrame = 0;
	m_nextActionFrame = 60;
}

/**
* @brief 思考の更新
* @param コンピューターの数を取得
*/
void Computer::ThinkUpdate(std::vector<IPlPtr> pPlayer, int index, int computerCount, SpGaugePtr sp)
{
	// コンピューターが存在しなかったら終了
	if (computerCount == 0) return;
	// １Ｐはコンピューターにならない
	if (computerCount == 1 && index == 0) return;

	// ターゲットを設定（1Pは必ずプレイヤーが入る）
	target = pPlayer[PLAYER1];

	if (!pPlayer[index]->CanControll() || !pPlayer[index]->isControll()) return;

	// 行動フレームを加算する
	m_actionFrame++;

	// 一定フレームを超えない限り
	if (m_actionFrame > m_nextActionFrame){
		m_nextActionFrame = 60 + m_actionFrame;

		// ゲージ量を確認する
		CheckGauge(pPlayer, index, sp);

		// 前回の行動を継続する
		pPlayer[index]->SetState(m_oldState);
		return;
	}

	// 思考開始
	ThinkAction(pPlayer, index);

	// ゲージ量を確認する
	CheckGauge(pPlayer, index, sp);

	// コンピュータを更新する
	pPlayer[index]->SetState(m_state);
}

/**
* @brief 行動を考える
*/
void Computer::ThinkAction(vector<IPlPtr> pPlayer, int index)
{
	// 状態を保存する
	m_oldState = m_state;

	// プレイヤー同士の距離を計算
	float dist = Utility::GetDistance(pPlayer[PLAYER1]->GetPos().x, pPlayer[PLAYER2]->GetPos().x);

	// 対象と距離が離れている
	if (dist > 400.0f)
	{
		LongDistanceAction();
	}
	// 対象とそこそこ距離が離れている
	else if (dist > 230.0f)
	{
		MiddleDistanceAction();
	}
	// 対象と距離が近い
	else{
		ShortDistanceAction();
	}
}

/**
* @brief ターゲットと近距離時の行動
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
		// ガード崩しを仕掛ける
		m_state = State::SquatAttack;
		break;

		// 各種攻撃
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

		// しゃがみ攻撃
	case State::SquatAttack:
		if (rand2 > 3){
			m_state = State::SquatGuard;
		}
		break;

	}

	// ジャンプしていたら
	if (m_state == State::Jump || m_state == State::JumpFront)
	{
		// ジャンプ攻撃
		m_state = State::JumpAttack;
	}
}

/**
* @brief ターゲットと中距離時の行動
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
* @brief ターゲットと遠距離時の行動
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
* @brief ゲージ量を確認する
*/
void Computer::CheckGauge(std::vector<IPlPtr> pPlayer, int index, SpGaugePtr sp)
{
	if (m_state == State::SpecialAttack){
		// ゲージ量の確認（不足してたら処理しない）
		if (!sp->IsUseGauge(State::SpecialAttack, pPlayer[index]->GetID())) {
			m_state = State::Neutral;
			return;
		}
		else{
			// ゲージの使用
			sp->Use(pPlayer[index]->GetID());
		}
	}
	else if (m_state == State::StrongAttack){
		// ゲージ量の確認（不足してたら処理しない）
		if (!sp->IsUseGauge(State::StrongAttack, pPlayer[index]->GetID())) {
			m_state = State::Neutral;
			return;
		}
		else{
			// ゲージの使用
			sp->Use(pPlayer[index]->GetID());
		}
	}
}