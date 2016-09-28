/**
* @file CharacterParam.h
* @brief キャラクターのパラメータデータを纏めた
* @author Syota Tachikawa
* @since 2016/03/17
*/

// ---------------------------------------------------------------------------
//
// 移動関係
//
// ---------------------------------------------------------------------------

/// ガード速度
const float GUARD_VX = -2.0f;

/// 移動速度
const float WALK_VX = 5.3f;

/// ダッシュ速度
const float DASH_VX = 15.0f;

/// バックステップ速度
const float BACK_STEP_VX = -10.0f;

/// 必殺技追撃速度
const float ATTACK_SPECIAL_PURSUIT_VX = 30.0f;

/// 奇襲攻撃の速度
const float ATTACK_RAID_VX = 70.0f;

/// 相殺時の速度
const float OFFSET_VX = 30.0f;

/// 受身の速度
const float PASSIVE_VX = 4.0f;
const float PASSIVE_VY = 10.0f;

/// 勝利ポーズの速度
const float WIN_VY = 10.0f;

/// ＫＯになった瞬間の速度
const float KO_VX = 4.0f;
const float KO_VY = 20.0f;

// ジャンプ速度
const float JUMP_VY = -17.0f;

/// しゃがみガード中ノックバック速度
const float CHARACTER_GUARD_VX = 3.0f;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// 攻撃力関係
//
// ---------------------------------------------------------------------------

/// 弱攻撃の攻撃力
const float ATTACK_WEAK_POWER = 20.0f;

/// 弱下攻撃の攻撃力
const float ATTACK_WEAK_UNDER_POWER = 20.0f;

/// 弱攻撃追撃の攻撃力
const float ATTACK_WEAK_DERIVATION_POWER = 40.0f;

/// 中攻撃の攻撃力
const float ATTACK_MEDIUM_POWER = 75.0f;

/// 中攻撃追撃の攻撃力
const float ATTACK_MEDIUM_DERIVATION_POWER = 50.0f;

/// 強攻撃の攻撃力（多段ヒットの為、1ヒットの威力を落としている）
const float ATTACK_STRONG_POWER = 8.05f;

/// 必殺技の攻撃力（多段ヒットの為、1ヒットの威力を落としている）
const float ATTACK_SPECIAL_POWER = 9.0f;

/// 必殺技追撃の攻撃力
const float ATTACK_SPECIAL_PURSUIT_POWER = 20.0f;

/// ダッシュ攻撃の攻撃力
const float ATTACK_DASH_POWER = 10.0f;

/// しゃがみ攻撃の攻撃力
const float ATTACK_SQUAT_POWER = 7.0f;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// フレーム関係
//
// ---------------------------------------------------------------------------

/// しゃがみ攻撃仰け反りフレーム
const int BENDBACKWARDFRAME_SQUAT = 15;

/// 弱攻撃仰け反りフレーム
const int BENDBACKWARDFRAME_WEAK = 22;

/// 弱派生攻撃仰け反りフレーム
const int BENDBACKWARDFRAME_WEAK_DERIVATION = 30;

/// 中攻撃仰け反りフレーム
const int BENDBACKWARDFRAME_MEDIUM = 30;

/// 強攻撃仰け反りフレーム
const int BENDBACKWARDFRAME_STRONG = 90;

/// 必殺技仰け反りフレーム
const int BENDBACKWARDFRAME_SPECIAL_PURSUIT = 110;

///	ジャンプ攻撃仰け反りフレーム
const int BENDBACKWARDFRAME_JUMP = 5;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// 座標関係
//
// ---------------------------------------------------------------------------

/// Player1の初期位置
const float INIT_PLAYER1_X = 350.0f;

/// Player2の初期位置
const float INIT_PLAYER2_X = 930.0f;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// その他
//
// ---------------------------------------------------------------------------

/// 立ち絵キャラクターの横幅
const float STAND_CHARACTER_WIDTH = 200.0f;

/// キャラクターの余白
const float CHARACTER_MARGIN = 40.0f;

/// 炎上中のアルファ加算値
const int BURNING_ADD_ALPHA = 8;

/// 吹き飛び状態の角度加算
const float BLOWOFF_ADD_ANGLE = 6.0f;

const float HITPARTICLESIZE = 0.9f;

/// ジャンプ最大数
const int JUMP_MAX = 1;

// ---------------------------------------------------------------------------