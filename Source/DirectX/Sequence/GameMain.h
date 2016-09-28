/**
* @file   GameMain.h
* @brief  メインゲームの処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___GAMEMAIN_H
#define ___GAMEMAIN_H

#include "ISequence.h"
#include "..\Common\StdAfx.h"
#include "..\Object\IPlayer.h"
#include "..\Object\IObject.h"
#include "..\DirectX\InputMask.h"
#include "..\GameSystem\Computer.h"
#include "..\GameSystem\Command.h"
#include "..\Object\UI\SpecialGauge.h"
#include "..\GameSystem\ComboCounter.h"
#include "..\Object\UI\HpGauge.h"
#include "..\Object\UI\UIManager.h"

/// ラウンドの最大数
const BYTE ROUND_MAX = 3;

class GameMain : public ISequence
{
protected:
	// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	// テクスチャデータ
	TextureData* m_texData;

	// ステージオブジェクト
	IStagePtr pStage;

	// プレイヤーオブジェクト
	vector<IPlPtr> pPlayer;

	// 入力デバイス
	vector<InputRef> m_dev;

	// コマンドデータ
	vector<Command*> cmd;

	// CPU
	Computer m_com;

	/// HPゲージ
	HpGauge hpGauge;

	/// コンボ数
	ComboCounter combo;

	/// UIマネージャ
	unique_ptr<UIManager> uiMgr;

	/// 必殺技ゲージ
	SpGaugePtr spGauge;

	// テクスチャ関連 ---------------------------------------------

	/// 左右立ち絵用
	std::vector<int> UI_stand01;
	std::vector<int> UI_stand02;

	/// キャラクターの種類
	int m_charaType[JOY_MAX];
	
	/// キャラクターの隠しシーン用
	int spcialTex[2];
	/// 描画位置
	float specialTexY;
	/// 大きさ
	float specialTexScale[2];

	/// 魔方陣テクスチャコピー用
	int mCircleTex[2];
	
	// ------------------------------------------------------------

	/// 表示する立ち絵番号
	std::array<int, JOY_MAX>displayNumber;

	/// ヒットポイント

	/// ステージのアルファ値
	int stageAlpha;

	// 一時的に使用するフレームの定義
	
	/// 停止フレーム
	int stopFrame;
	int stopCount;
	int workFrame;
	int adjustworkFrame;
	/// サブワーク
	GameState subWork;

	/// 選択されたキャラクタ
	const int* selectChara;

	/// バトル開始前内でのワーク
	int m_beforBattleWork;

	/// バトルセット内でのワーク
	int m_setBattleWork;

	/// ゲームセット内でのワーク
	int m_gameSetWork;


	/// 特殊演出ワーク
	int spWork;
	
	/// 必殺技ワーク
	int spAttackWork;

	/// 特殊エフェクトワーク
	int spEffectWork;

	/// ゲームワーク
	int gameWork;

	/// リリアパワーアップ値
	float powerUPLilia[JOY_MAX];

	/// ルナパワーアップ値
	float powerUPRuna[JOY_MAX];

	/// 立ち絵背景の描画する番号
	int standBack[JOY_MAX];

	/// ゲームフレーム
	int gameFrame;

	/// 調整用フレーム
	int adjustFrame;

	/// ＫＯ判定用
	int isKO;

	/// 特殊演出フラグ
	bool isSpecial;

	/// ゲーム停止フラグ
	bool m_isGameStop;

	/// 揺らす値
	float swingVal[JOY_MAX];
	// 揺らすか否かのフラグ
	bool isSwing[JOY_MAX];
	/// エクストラスキル発動フラグ
	bool isUseExSkill[JOY_MAX];

	/// 衣服が破れた回数
	int clothesBreakCount[JOY_MAX];
	
	/// 衣服破れフラグ
	bool isClothesBreak[JOY_MAX];

	/// 光用アルファ値
	float light2Angle;		

	/// 破れ状態
	int breakState[JOY_MAX];

	/// パワーアップパーティクルアルファ値
	float pwUpAlpha[JOY_MAX];
	/// 1Pパワーアップ値
	float P1pwUpValue[2];
	/// 2Pパワーアップ値
	float P2pwUpValue[2];

	/// 必殺技用の魔方陣の角度
	float mCircleAngle;
	/// 必殺技用の魔方陣の大きさ
	float mCircleScale;
	/// 必殺技用の魔方陣のアルファ値
	int mCircleAlpha;

	/// 泡座標
	float formX[5], formY[5];
	/// 泡発生フラグ
	bool formFlag;

	/// 開始前の魔方陣角度
	float magicAngle;
	
	/// Fightフォント座標
	float fightX;
	/// Fightフォント速度
	float fightVX;

	// 勝利数保存
	int winNum[JOY_MAX];
	// 現在のラウンド
	int roundNow;
	// 負けたプレイヤー番号
	int losePlNum;
	
	/**
	* @brief メインゲーム更新
	*/
	void UpdateGame();

	/**
	* @brief KO部分の更新
	*/
	bool UpdateGameKO();
	
	/**
	* @brief バトル前の演出更新
	*/
	void UpdateBeforBattle();
	
	/**
	* @brief バトル前のフォント部分の更新
	*/
	void UpdateSetBattle();

	/**
	* @brief バトル決着の更新
	*/
	void UpdateGameSet();

	/**
	* @brief バトルKOの更新
	*/
	void UpdateKO();

	/**
	* @brief バトル特殊シーンの更新
	*/
	void UpdateSpecial();

	/**
	* @brief バトル終了の更新
	*/
	void UpdateEnd();

	/**
	* @brief バトル終了の更新
	*/
	void UpdateExit();

	/**
	* @brief 破れエフェクトの更新
	*/
	void UpdateBreakClothes();

	/**
	* @brief パワーアップエフェクトの更新
	*/
	void UpdatePowerUp();
	
	/**
	* @brief キャラクターの更新
	*/
	void UpdateCharacter(int index);

	/**
	* @brief エクストラスキルの更新
	*/
	void UpdateExSkill();

	/**
	* @brief 背景に描画する魔方陣の更新
	*/
	void UpdateBackGroundMagicCircle();

	/**
	* @brief 背景に描画する
	*/
	void RenderBackGround();

	/**
	* @brief 魔方陣とReadyフォント描画
	*/
	void RenderSetBattle();

	/**
	* @brief 特殊演出の描画
	*/
	void RenderSpecialProduction();

	/**
	* @brief ＫＯしたかを判定する
	*/
	void GetCheckKO();
	
	/**
	* @brief プレイヤー同士の当たり判定
	*/
	void CheckPlayerCollide(int index);

	/**
	* @brief プレイヤーと上段攻撃の当たり判定
	*/
	void CheckUpperAttackCollide(int index);

	/**
	* @brief プレイヤーと下段攻撃の当たり判定
	*/
	void CheckLowerAttackCollide(int index);
	
	/**
	* @brief 相殺判定
	*/
	void CheckOffsetCollide(int index);

	/**
	* @brief プレイヤーとエフェクトの当たり判定
	*/
	void CheckEffectCollide(int index);

	/**
	* @brief プレイヤーの向きを調整する
	*/
	void SetPlayerDirection(int index);

	/**
	* @brief 攻撃ダメージを加算する
	*/
	void UpdateAttackDamage(int index);

	/**
	* @brief ステージ端から出ないようにする
	*/
	void StageEnd();

	/**
	* @brief 壁ハメを出来ないようにステージ端で攻撃を喰らったら補正する
	*/
	void StageEndShift(int index);

	/**
	* @brief 画面を揺らす
	*/
	void ScreenSwing();

	/**
	* @brief 隠しコマンドによる特殊演出
	*/
	bool SpecialProduction();

	/**
	* @brief ゲームの更新を停止する
	* @param frame - 停止するフレーム数
	* @param flag  - trueで停止させる
	*/
	void SetGameStop(int frame , bool flag = false);

public:

	/**
	* @brief 初期化
	*/
	void Initialize();
	
	/**
	* @brief 作成
	*/
	void Create();
	
	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief 終了
	*/
	void Finalize();
};

#endif