/**
* @file   Define.h
* @brief  共通して使う定数を管理
* @author Syota Tachikawa
*/

#ifndef ___DEFINE_H
#define ___DEFINE_H

// プレイヤー番号の定義（配列でややこしくなるのを防止）
// プレイヤー１
#define PLAYER1 0
// プレイヤー２
#define PLAYER2 1

// ジョイスティックの最大数
#define JOY_MAX 2

// アルファ最大値
#define ALPHA_MAX 255
// アルファ最小値
#define ALPHA_MIN 0

/// キャラクターの種類
#define CHARA_KIND_NUM 2

/// フェードフレーム
#define FADE_FRAME 170

/// ウィンドウの横幅
#define WINDOW_WIDTH 1280

/// ウィンドウの縦幅
#define WINDOW_HEIGHT 720

#endif