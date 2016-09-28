#include "Command.h"
#include "..\DirectX\InputMask.h"

/**
* @brief コンストラクタ
*/
Command::Command()
{
	Initialize();
}

/**
* @brief デストラクタ
*/
Command::~Command()
{

}

/**
* @brief 初期化
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
* @brief スキルデータ
*/
const int Command::SkillCommand[COMMAND_MAX][COMMAND_INPUT_MAX] = 
{
	// てすとでーた
	{ INPUT_DOWN, INPUT_RIGHT, INPUT_01, -1 },
	
	// 技データ終端
	{ -1 },
};


/**
* @brief デバイスの入力情報を取得する
*/
void Command::InputCommand(unsigned int flag)
{
	m_inputData = flag;

	if (m_inputData == 0) return;

	if (m_inputData != m_oldInputData)
	{
		// フレームを初期化
		m_inputFrame = 0;

		// バッファに入力データを保存
		m_inputBuffer[m_inputNum] = m_inputData;

		// 次のコマンドに進める
		m_inputNum++;

		// スキルのチェック
		m_skill = SkillCheck();
	}

	// 猶予フレームを超えると初期化される（失敗）
	if (m_inputFrame > INPUT_VALID_FRAME){
		Initialize();
	}

	// コマンド入力数が最大値を超えると初期化
	if (m_inputNum >= COMMAND_INPUT_MAX){
		Initialize();
	}

	// 入力情報を保存する
	m_oldInputData = m_inputData;

	// フレームを加算する
	m_inputFrame++;
}


/**
* @brief コマンド情報からスキルデータを取得する
*/
const int Command::SkillCheck()
{
	int skill = -1;
	int maxConbo = NULL;

	// 出す技を探す
	maxConbo = 0;

	for (int i = 0; SkillCommand[i][0] != -1; i++)
	{
		// コマンドデータと入力したデータが等しい数を調べる
		int j = 0;
		while (SkillCommand[i][j] == m_inputBuffer[j]) j++;

		// コマンドデータの終端まで同じだった場合は
		// その技のコマンド数と技ナンバーを保存する
		// なお以前にもっと多くのコマンドを要す技と適合していたら記憶しない
		if (SkillCommand[i][j] == -1)
		{
			maxConbo = j;
			skill = i;
		}
	}

	// スキル不一致
	if (maxConbo == 0) {
		return -1;
	}

	// 選ばれたスキル番号を返す
	return skill;
}

/**
* @brief スキル番号を取得する
* @return -1 はコマンド不成立(何もしない)
*/
const int Command::GetSkillNumber()
{
	return m_skill;
}