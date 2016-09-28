/**
* @file   Enum.h
* @brief  Enum定義を纏めた
* @author Syota Tachikawa
*/

#ifndef ___ENUM_H
#define ___ENUM_H

/// 向き
enum class Dir
{
	Right,
	Left
};

/// キャラクター状態
enum class State
{
	Neutral,
	Advance,					// 前進
	Dash,						// フロントステップ(ダッシュ)
	BackStep,					// バックステップ
	Squat,						// しゃがみ
	SquatAttack,				// しゃがみ攻撃
	Jump,
	JumpFront,					// 前方ジャンプ
	JumpBack,					// 後方ジャンプ
	JumpAttack,					// 空中攻撃
	DashAttack,					// ダッシュ攻撃
	WeakAttack,					// 弱攻撃
	UnderAttack,				// 弱下攻撃
	WeakDerivationAttack,		// 弱攻撃派生技
	MediumAttack,				// 中攻撃
	StrongAttack,				// 強攻撃
	StrongDerivationAttack,		// 強攻撃派生技
	SpecialAttack,				// 必殺技
	AttackSpecialPursuit,		// 必殺技追撃
	RaidAttack,					// 奇襲攻撃
	Guard,						// 通常ガード
	SquatGuard,					// しゃがみガード
	SquatGuardNow,				// しゃがみガード中
	JumpGuard,					// ジャンプガード
	GuardNow,					// 通常ガード中
	Down,						// ダウン状態
	AIRHIT,						// 空中被弾
	Blowoff,					// 吹き飛び
	Damage,						// 被弾
	DamageEffect,				// エフェクト被弾
	Offset,						// 相殺
	Passive,					// 受身
	BeforBattle,				// バトル開始前
	Win,						// 勝利
	Ko,
	SpecialProduction,			// 特殊演出
	STATE_MAX
};

// フェード
enum class Fade
{
	None,
	In,
	Out
};

// フェードカラー
enum class FadeColor
{
	Black,
	White
};

// ゲームモード
enum class GameMode
{
	Default = 0,
	VsCPU,
	Vs2P,
	Demo,		// デモプレイ
	Exit
};

// キャラクターネーム
enum CharaName
{
	LILIA,
	RUNA
};

// 衣服の状態
enum ClotheState
{
	NO_BREAK = 0,
	BREAK_TORSO,
	BREAK_TORSO_AND_OUTERWEAR,
	BREAK_TORSO_AND_SKIRT,
	ALL_BREAK,
	NUDE
};

// ゲームの状態
enum class GameState
{
	BattleBefore = 0,
	Set,
	Play,
	GameSet,
	KO,
	Special,
	End,
	Exit
};

// エフェクトの種類
enum EffectKind
{
	Hinoko,        // 火の粉
	Slash,         // 斬撃
	Slash2,        // 斬撃
	Light,         // 光
	Smoke,         // 煙
	Slash3,        // 斬撃
	Ring,          // 輪っか
	Blur,          // ブラー
	Trajectory,    // 剣の軌跡
	Slash4 = 9,    // 斬撃
	RedRing,       // 赤い輪
	BurstRing,     // 衝撃波
};

// 必殺技ゲージの状態
enum class SpecialGaugeState
{
	None,  // なし
	Empty, // 空
	Add,   // 増加
	Full,  // 満タン
	Use,   // 使用
};

// ステージの種類
enum class StageType
{
	SubSpace, // 亜空間
};

// 攻撃ポイント
enum class AttackPoint
{
	// データ無し
	None,
	// 上段
	Upper,
	// 下段
	Lower
};

#endif