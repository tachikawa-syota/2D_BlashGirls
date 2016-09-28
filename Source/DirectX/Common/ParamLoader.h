#ifndef ___PARAMLOADER_H
#define ___PARAMLOADER_H

#include "..\iniFileLoader\iniFileLoaderBase.h"

// インスタンス取得
#define GetPrm ParamLoader::GetInstance()

/**
* @brief iniファイルで管理しているパラメーターを読み込むクラス
*/
class ParamLoader : public iniFileLoaderBase
{
public:
	static ParamLoader* GetInstance(){
		static ParamLoader singleton;
		return &singleton;
	}

	/// プレイヤー１の初期座標
	float Player1InitPosX;

	/// プレイヤー２の初期座標
	float Player2InitPosX;

	/// プレイヤーの初期座標（Y座標は両者共通なので定数は一つだけ）
	float PlayerInitPosY;

	/// 床の座標
	float Ground;

	/// 重力
	float Gravity;

	/// 輝エフェクトの拡大値
	float FlushEffectAddScale;

	/// 輝エフェクトの大きさの最大値
	float FlushEffectMaxScale;

	/// ガードエフェクトの大きさの最大値
	float GuardEffectMaxScale;

	/// ガードエフェクトの拡大値
	float GuardEffectAddScale;

	/// 光エフェクトの大きさの最大値
	float LightEffectMaxScale;

	/// 光ラインエフェクトの速度
	float LightlineEffectVX;

	/// 波エフェクトのアニメーション最大数
	int WaveEffectMaxAnimation;

	/// Player1側のヒットフォントの位置
	float HitFontPlayer1X;

	/// Player2側のヒットフォントの位置
	float HitFontPlayer2X;

	/// Player1側の数字フォントの位置
	float NumberFontPlayer1X;

	/// Player2側の数字フォントの位置
	float NumberFontPlayer2X;

	/// コンボ持続フレームのリミット
	int ComboFrameLimit;

	/// コンボダメージによる補正係数
	float ComboCorrectionCoefficient;

	/// 補正値のリミット
	float ComboCorrectionCoefficientLimit;

	/// Player1側のカットインの初期位置Ｘ
	float InitCutinPlayer1X;

	/// カットインの初期位置Ｙ
	float InitCutinY;

	/// Player2側のカットインの初期位置Ｘ
	float InitCutinPlayer2X;

	/// 初期カットイン速度
	float InitCutinV;

	/// Player1のカットイン位置
	float CutinPlayer1X;

	/// カットイン位置
	float CutinY;

	/// Player2のカットイン位置
	float CutinPlayer2X;

	/// 恥辱ゲージの最大値（ＨＰゲージ）
	float HpMax;

	/// 上着耐久の最大値
	float OuterWearEnduranceMax;

	/// スカート耐久の最大値
	float SkirtEnduranceMax;

	/// 胴耐久の最大値
	float TorsoEnduranceMax;

	/// 背景キャラクターの位置
	float BackPlayer1X;
	float BackPlayer2X;

	/// 背景キャラクターの速度
	float BackCharacterVX;

	/// 背景キャラクターのアルファ加算値
	int BackCharacterAddAlpha;

	/// キャラクター選択画面魔法フォントの速度
	float MagicFontVX;

	/// キャラクター選択画面魔法フォント位置のリミット
	float MagicFontY1Limit;
	float MagicFontY2Limit;

	/// キャラクター選択画面魔法フォントの初期位置
	float MagicFontInitY1;
	float MagicFontInitY2;

	/// Fightフォントの初期位置
	float FightFontInitX;

	/// Fightフォントの初期速度
	float FightFontInitVX;

	/// Fightフォントの位置
	float FightFontX;

	/// Fightフォントの速度
	float FightFontVX;

	// バトル開始前の魔方陣を回転速度
	float MagicCircleAddAngle;

	/// ガードによるダメージ軽減率
	float GuardDamageMitiGation;

	/// 補正が入るステージの右端位置
	float StageLeftShiftLimit;

	/// 補正が入るステージの右端位置
	float StageRightShiftLimit;

	/// 必殺技ゲージ量の最大値
	float MaxSpecialGauge;

	/// 必殺技ゲージの大きさ
	float SpecialGaugeSizeX;

private:
	/**
	* @brief コンストラクタ
	*/
	ParamLoader() :iniFileLoaderBase("Param.ini")
	{
		Player1InitPosX = GetNextParameterFloat();
		Player2InitPosX = GetNextParameterFloat();
		PlayerInitPosY = GetNextParameterFloat();
		Ground = GetNextParameterFloat();
		Gravity = GetNextParameterFloat();
		FlushEffectAddScale = GetNextParameterFloat();
		FlushEffectMaxScale = GetNextParameterFloat();
		GuardEffectMaxScale = GetNextParameterFloat();
		GuardEffectAddScale = GetNextParameterFloat();
		LightEffectMaxScale = GetNextParameterFloat();
		LightlineEffectVX = GetNextParameterFloat();
		WaveEffectMaxAnimation = GetNextParameterInt();
		HitFontPlayer1X = GetNextParameterFloat();
		HitFontPlayer2X = GetNextParameterFloat();
		NumberFontPlayer1X = GetNextParameterFloat();
		NumberFontPlayer2X = GetNextParameterFloat();
		ComboFrameLimit = GetNextParameterInt();
		ComboCorrectionCoefficient = GetNextParameterFloat();
		ComboCorrectionCoefficientLimit = GetNextParameterFloat();
		InitCutinPlayer1X = GetNextParameterFloat();
		InitCutinY = GetNextParameterFloat();
		InitCutinPlayer2X = GetNextParameterFloat();
		InitCutinV = GetNextParameterFloat();
		CutinPlayer1X = GetNextParameterFloat();
		CutinY = GetNextParameterFloat();
		CutinPlayer2X = GetNextParameterFloat();
		HpMax = GetNextParameterFloat();
		OuterWearEnduranceMax = GetNextParameterFloat();
		SkirtEnduranceMax = GetNextParameterFloat();
		TorsoEnduranceMax = GetNextParameterFloat();
		BackPlayer1X = GetNextParameterFloat();
		BackPlayer2X = GetNextParameterFloat();
		BackCharacterVX = GetNextParameterFloat();
		BackCharacterAddAlpha = GetNextParameterInt();
		MagicFontVX = GetNextParameterFloat();
		MagicFontY1Limit = GetNextParameterFloat();
		MagicFontY2Limit = GetNextParameterFloat();
		MagicFontInitY1 = GetNextParameterFloat();
		MagicFontInitY2 = GetNextParameterFloat();
		FightFontInitX = GetNextParameterFloat();
		FightFontInitVX = GetNextParameterFloat();
		FightFontX = GetNextParameterFloat();
		FightFontVX = GetNextParameterFloat();
		MagicCircleAddAngle = GetNextParameterFloat();
		GuardDamageMitiGation = GetNextParameterFloat();
		StageLeftShiftLimit = GetNextParameterFloat();
		StageRightShiftLimit = GetNextParameterFloat();
		MaxSpecialGauge = GetNextParameterFloat();
		SpecialGaugeSizeX = GetNextParameterFloat();
	}
};

#endif