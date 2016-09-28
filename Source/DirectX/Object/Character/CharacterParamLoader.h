#ifndef ___CHARACTERPARAMLOADER_H
#define ___CHARACTERPARAMLOADER_H

#include "..\..\iniFileLoader\iniFileLoaderBase.h"

// インスタンス取得
#define GetChrPrm CharacterParamLoader::GetInstance()

/**
* @brief iniファイルで管理しているキャラクターパラメーターを読み込むクラス
*/
class CharacterParamLoader : public iniFileLoaderBase
{
public:
	static CharacterParamLoader* GetInstance(){
		static CharacterParamLoader singleton;
		return &singleton;
	}

	// 全キャラクター共通のパラメータ-----------------------
	float PlayerGuardNowSpeed;

	// リリア(攻撃力を高め・スピードを遅めに設定)-----------------------------------------------

	/// 前進速度
	float LiliaAdvanceSpeed;

	/// ガード速度
	float LiliaGuardSpeed;

	/// ダッシュ速度
	float LiliaDashSpeed;

	/// バックステップ速度
	float LiliaBackStepSpeed;

	/// 強攻撃使用時の速度
	float LiliaAttackStrongSpeed;

	/// 必殺技追撃の速度
	float LiliaAttackSpecialPursuitSpeed;

	/// 弱攻撃の攻撃力
	float LiliaAttackWeakPower;

	/// ジャンプ攻撃の攻撃力
	float LiliaAttackJumpPower;

	/// 遠距離攻撃の攻撃力
	float LiliaAttackLongPower;

	/// 弱攻撃追撃の攻撃力
	float LiliaAttackWeakDerivationPower;

	/// 中攻撃の攻撃力
	float LiliaAttackMediumPower;

	/// 中攻撃追撃の攻撃力
	float LiliaAttackMediumDerivationPower;

	/// 強攻撃の攻撃力（多段ヒットの為、1ヒットの威力を落としている）
	float LiliaAttackStrongPower;

	/// 必殺技の攻撃力（多段ヒットの為、1ヒットの威力を落としている）
	float LiliaAttackSpecialPower;

	/// 必殺技追撃の攻撃力
	float LiliaAttackSpecialPursuitPower;

	/// ダッシュ攻撃の攻撃力
	float LiliaAttackDashPower;

	/// 奇襲攻撃の攻撃力
	float LiliaAttackRaidPower;

	/// しゃがみ攻撃の攻撃力
	float LiliaAttackSquatPower;

	/// リリア斬撃回数の最大値
	int LiliaSlashingCountMax;


	// ルナ (攻撃力を低め・スピードを早めに設定)--------------------------------------------------------

	/// 前進速度
	float RunaAdvanceSpeed;

	/// ガード速度
	float RunaGuardSpeed;

	/// ダッシュ速度
	float RunaDashSpeed;

	/// バックステップ速度
	float RunaBackStepSpeed;

	/// 強攻撃使用時の速度
	float RunaAttackStrongSpeed;

	/// 必殺技追撃の速度
	float RunaAttackSpecialPursuitSpeed;

	/// 弱攻撃の攻撃力
	float RunaAttackWeakPower;

	/// ジャンプ攻撃の攻撃力
	float RunaAttackJumpPower;

	/// 遠距離攻撃の攻撃力
	float RunaAttackLongPower;

	/// 弱攻撃追撃の攻撃力
	float RunaAttackWeakDerivationPower;

	/// 中攻撃の攻撃力
	float RunaAttackMediumPower;

	/// 中攻撃追撃の攻撃力
	float RunaAttackMediumDerivationPower;

	/// 強攻撃の攻撃力（多段ヒットの為、1ヒットの威力を落としている）
	float RunaAttackStrongPower;

	/// 必殺技の攻撃力（多段ヒットの為、1ヒットの威力を落としている）
	float RunaAttackSpecialPower;

	/// 必殺技追撃の攻撃力
	float RunaAttackSpecialPursuitPower;

	/// ダッシュ攻撃の攻撃力
	float RunaAttackDashPower;

	/// 奇襲攻撃の攻撃力
	float RunaAttackRaidPower;

	/// しゃがみ攻撃の攻撃力
	float RunaAttackSquatPower;

	/// ルナ斬撃回数の最大値
	int RunaSlashingCountMax;


private:
	/**
	* @brief コンストラクタ
	*/
	CharacterParamLoader() :iniFileLoaderBase("CharacterParam.ini")
	{
		// 共通
		PlayerGuardNowSpeed = GetNextParameterFloat();

		// リリア
		LiliaAdvanceSpeed = GetNextParameterFloat();
		LiliaGuardSpeed = GetNextParameterFloat();
		LiliaDashSpeed = GetNextParameterFloat();
		LiliaBackStepSpeed = GetNextParameterFloat();
		LiliaAttackStrongSpeed = GetNextParameterFloat();
		LiliaAttackSpecialPursuitSpeed = GetNextParameterFloat();
		LiliaAttackWeakPower = GetNextParameterFloat();
		LiliaAttackJumpPower = GetNextParameterFloat();
		LiliaAttackLongPower = GetNextParameterFloat();
		LiliaAttackWeakDerivationPower = GetNextParameterFloat();
		LiliaAttackMediumPower = GetNextParameterFloat();
		LiliaAttackMediumDerivationPower = GetNextParameterFloat();
		LiliaAttackStrongPower = GetNextParameterFloat();
		LiliaAttackSpecialPower = GetNextParameterFloat();
		LiliaAttackSpecialPursuitPower = GetNextParameterFloat();
		LiliaAttackDashPower = GetNextParameterFloat();
		LiliaAttackRaidPower = GetNextParameterFloat();
		LiliaAttackSquatPower = GetNextParameterFloat();
		LiliaSlashingCountMax = GetNextParameterInt();

		// ルナ
		RunaAdvanceSpeed = GetNextParameterFloat();
		RunaGuardSpeed = GetNextParameterFloat();
		RunaDashSpeed = GetNextParameterFloat();
		RunaBackStepSpeed = GetNextParameterFloat();
		RunaAttackStrongSpeed = GetNextParameterFloat();
		RunaAttackSpecialPursuitSpeed = GetNextParameterFloat();
		RunaAttackWeakPower = GetNextParameterFloat();
		RunaAttackJumpPower = GetNextParameterFloat();
		RunaAttackLongPower = GetNextParameterFloat();
		RunaAttackWeakDerivationPower = GetNextParameterFloat();
		RunaAttackMediumPower = GetNextParameterFloat();
		RunaAttackMediumDerivationPower = GetNextParameterFloat();
		RunaAttackStrongPower = GetNextParameterFloat();
		RunaAttackSpecialPower = GetNextParameterFloat();
		RunaAttackSpecialPursuitPower = GetNextParameterFloat();
		RunaAttackDashPower = GetNextParameterFloat();
		RunaAttackRaidPower = GetNextParameterFloat();
		RunaAttackSquatPower = GetNextParameterFloat();
		RunaSlashingCountMax = GetNextParameterInt();
	}
};

#endif