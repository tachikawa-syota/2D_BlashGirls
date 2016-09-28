/**
* @file   CommandManager.h
* @brief  コマンドを管理する
* @author Syota Tachikawa
*/

#ifndef ___COMMANDMANAGER_H
#define ___COMMANDMANAGER_H

#include "..\Common\StdAfx.h"

// 猶予フレーム
const int INPUT_VALID_FRAME = 60;
/// コマンド最大数
const int COMMAND_MAX = 1 + 1;
/// コマンド入力最大数
const int COMMAND_INPUT_MAX = 4;

// 前方宣言
class InputMask;

class Command
{
public:
	/**
	* @brief コンストラクタ
	*/
	Command();
	
	/**
	* @brief デストラクタ
	*/
	~Command();
	
	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief スキルデータ
	*/
	static const int SkillCommand[COMMAND_MAX][COMMAND_INPUT_MAX];

	/**
	* @brief デバイスの入力情報を取得する
	*/
	void InputCommand(unsigned int flag);

	/**
	* @brief スキル番号を取得する
	* @return -1 はコマンド不成立(何もしない)
	*/
	const int GetSkillNumber();

private:
	// 入力フレーム
	unsigned int m_inputFrame;

	// 入力情報を保存
	unsigned int m_inputData;

	// １フレーム前の入力情報
	unsigned int m_oldInputData;

	// 入力されたコマンドの数
	int m_inputNum;

	// 入力データ
	int m_inputBuffer[COMMAND_INPUT_MAX];

	/// スキルデータ
	int m_skill;

	/**
	* @brief コマンド情報からスキルデータを取得する
	*/
	const int SkillCheck();
};

#endif