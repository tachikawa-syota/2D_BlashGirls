// シーン
#include "Title.h"
#include "GameMain.h"
#include "Result.h"
#include "SequenceChanger.h"
// サウンド
#include "..\DirectX\SoundPlayer.h"
// オブジェクト
#include "..\Object\UI\UIManager.h"
// オブジェクト生成
#include "..\Object\Stage\StageFactory.h"
#include "..\Object\Character\CharacterFactory.h"
// エフェクト
#include "..\Object\Effect\EffectManager.h"
#include "..\Object\Effect\ShineEffect.h"
#include "..\Object\CollisionEffect\CollisionEffectManager.h"
// パーティクル
#include "..\Object\Particle\ParticleManager.h"
#include "..\Object\Particle\HitParticle.h"
#include "..\Object\Particle\PowerUpParticle.h"
#include "..\Object\Particle\FormParticle.h"
#include "..\Object\Particle\OffsetParticle.h"
// システム
#include "..\GameSystem\Camera.h"
#include "..\GameSystem\Collide.h"
#include "..\GameSystem\CutIn.h"
#include "..\GameSystem\CutInManager.h"
// パラメータ
#include "..\Common\ParamLoader.h"
#include "..\Object\Character\CharacterParam.h"
// 一意なデータ
#include "..\Common\UniqueData.h"
// 有益
#include "..\Common\Utility.h"

/// データなし
#define NONE -1

/**
* @brief 作成
*/
void GameMain::Create()
{
	// インスタンスを取得する
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// ステージを作成する
	//（現バージョンでは亜空間ステージしか無い）
	auto sf = make_unique<StageFactory>();
	pStage = sf->CreateStage(StageType::SubSpace);

	// 選択されたキャラクターの情報を取得する
	selectChara = UniqueData::GetInstance()->GetSelectCharacter();

	// キャラクターインスタンス生成クラス
	auto cf = make_unique<CharacterFactory>();
	for (int i = 0; i < JOY_MAX; i++){
		// 要素追加
		pPlayer.emplace_back((cf->CreateCharacter(selectChara[i], i)));
		// キャラクターの種類を保存
		m_charaType[i] = selectChara[i];
	}

	// プレイヤーの人数分デバイス作成
	int playerCount = UniqueData::GetInstance()->GetPlayerCount();
	for (int i = 0; i < playerCount; i++){
		m_dev.emplace_back(new InputMask(i));
		cmd.emplace_back(new Command());
	}

	uiMgr = make_unique<UIManager>();
	spGauge = make_unique<SpecialGauge>();

	// 左右に表示するキャラクターの立ち絵
	UI_stand01.resize(6);
	UI_stand02.resize(6);

	// テクスチャ一括コピー -------------------------------------------------

	// 立ち絵テクスチャコピー
	for (int i = 0; i < 6; i++){
		UI_stand01[i] = m_texData->GetTexture(TEX_LILIA_STAND_00 + i);
		UI_stand02[i] = m_texData->GetTexture(TEX_RUNA_STAND_00 + i);
	}
	// リリアの特殊シーンテクスチャ
	spcialTex[LILIA] = m_texData->GetTexture(TEX_LILIA_SPECIAL);
	// ルナの特殊シーンテクスチャ
	spcialTex[RUNA] = m_texData->GetTexture(TEX_RUNA_SPECIAL);
	for (int i = 0; i < MAGICCIRCLE_MAX; i++){
		mCircleTex[i] = m_texData->GetMagicCircleTexture(i);
	}

	// -----------------------------------------------------------------------
	
	// バトル開始前
	subWork = GameState::BattleBefore;

	// 勝利数の初期化
	winNum[PLAYER1] = 0;
	winNum[PLAYER2] = 0;

	// ラウンド番号を 1 に
	roundNow = 1;

	// プレイヤーが生成されたかをチェックする
	for (int i = 0; i != pPlayer.size(); i++)
	{
		if (pPlayer[i] == nullptr){
			// 強制終了
			Utility::abortWithMsg("プレイヤーの作成に失敗しました。");
		}
	}
}

/**
* @brief 初期化
*/
void GameMain::Initialize()
{
	gameWork = 0;
	spAttackWork = 0;
	spWork = 0;
	m_beforBattleWork = 0;
	m_setBattleWork = 0;
	m_gameSetWork = 0;
	gameFrame = 0;
	adjustworkFrame = 10;
	adjustFrame = 1;
	stageAlpha = ALPHA_MAX;
	stopCount = 0;
	stopFrame = 0;

	// 負けたプレイヤー番号初期化
	losePlNum = NONE;

	// Fight文字の座標と速度を設定
	fightX = GetPrm->FightFontInitX;
	fightVX = GetPrm->FightFontInitVX;
	
	// KOしていない
	isKO = NONE;

	// パワーアップ値の初期化
	for (int i = 0; i < 2; i++)
	{
		powerUPLilia[i] = {};
		powerUPRuna[i] = {};
	}

	isSwing[0] = isSwing[1] = false;
	isSpecial = false;
	isUseExSkill[0] = false;
	isUseExSkill[1] = false;

	magicAngle = 0.0f;
	
	workFrame = 0;
	
	specialTexY = 0.0f;
	specialTexScale[0] = 0.6f;
	mCircleScale = 0.0f;
	mCircleAngle = 0.0f;
	mCircleAlpha = 0;
	light2Angle = 0.0f;

	// プレイヤーの数だけ初期化をする
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 衣服の破れ状態を初期化
		clothesBreakCount[i] = 0;
		pwUpAlpha[i] = {};
		pwUpAlpha[i] = {};
		displayNumber[i] = NO_BREAK;
		standBack[i] = 0;
		breakState[i] = 0;
		swingVal[i] = 0.0f;
		// プレイヤーの初期化
		pPlayer[i]->Initialize(i);
	}

	// デバイスの数だけ初期化する
	for (int i = 0; i != m_dev.size(); i++){
		cmd[i]->Initialize();
	}

	// 初期化する
	EffectManager::GetInstance()->Initialize();
	CollisionEffectManager::GetInstance()->Initialize();
	ParticleManager::GetInstance()->Initialize();
	hpGauge.Initialize();
	spGauge->Initialize();
	combo.Initialize();
	uiMgr->Initialize();
	m_com.Initialize();

	// カメラも先に初期化しておく
	// プレイヤーの描画が中心点を軸にしてる関係で補正する
	float left = pPlayer[PLAYER1]->GetPos().x + (pPlayer[PLAYER2]->GetPos().x - pPlayer[PLAYER1]->GetPos().x) / 2.0f - 640.0f;
	Camera::GetInstance()->SetCenterPoint(left);
}


/**
* @brief 更新
*/
void GameMain::Update()
{
	// ステージの更新
	pStage->ChangeAlpha(stageAlpha);
	pStage->Update();

	switch (subWork)
	{
	// 開始前の掛け合い
	case GameState::BattleBefore:
		UpdateBeforBattle();
		break;

	// レディファイト
	case GameState::Set:
		UpdateSetBattle();
		break;

	// ゲームプレイ
	case GameState::Play:
		UpdateGame();
		break;

	// ゲームセット
	case GameState::GameSet:
		UpdateGameSet();
		break;

	// ノックアウト
	case GameState::KO:
		UpdateKO();
		break;

	// 特殊演出
	case GameState::Special:
		UpdateSpecial();
		break;
		
	case GameState::End:
		UpdateEnd();
		break;

	// バトルの終了
	case GameState::Exit:
		UpdateExit();
		break;

	// 例外処理
	default:
		Utility::abortWithMsg("ゲーム中に例外処理が発生しました");
		break;
	}
	
	// デモプレイ中で
	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Demo)
	{
		// キーの入力を確認したら
		if (m_dev[0]->CheckInputMask(INPUT_01))
		{
	//		SequenceManager::SequenceChange(Scene::Title);
			// 初期化
			Initialize();
		}
	}

	// フレーム更新
	gameFrame++;
}	

/**
* @brief 描画
*/
void GameMain::Render()
{
	// ステージの描画
	pStage->Render();

	// 背景に描画
	RenderBackGround();
	
	// カットインの描画
	CutInManager::GetInstance()->Render();
//	cutin->Render();

	// プレイヤーの描画
	for (int i = 0; i != pPlayer.size(); i++)
		pPlayer[i]->Render();

	// 当たり判定付きエフェクトの描画
	CollisionEffectManager::GetInstance()->Render();

	// エフェクトの描画
	EffectManager::GetInstance()->Render();
	
	// パーティクルの描画
	if (subWork != GameState::Special){
		ParticleManager::GetInstance()->Render();
	}

	// UIの描画
	uiMgr->Render(winNum, swingVal, spGauge, hpGauge);

	// コンボ数表示
	combo.Render();

	// KO文字の描画
	if (isKO != -1 && subWork == GameState::GameSet)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_KO_FONT), 640.0f, 290.0f, 0.0f, 0.5f);

	// Push文字の描画
	if (subWork == GameState::KO){
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PUSH_FONT), 640.0f, 200.0f);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PUSH_FONT2), 725.0f, 200.0f + 15.0f);
	}

	// ラウンド文字の描画
	if (subWork == GameState::Set)
	{
		RenderSetBattle();
	}
		
	// 特殊演出の描画
	RenderSpecialProduction();
}



/**
* @brief ゲーム部分の処理
*/
void GameMain::UpdateGame()
{
	// デバイスの更新
	for (int i = 0; i != m_dev.size(); i++){
		m_dev[i]->GetInput();
	}

	// プレイヤーの描画が中心点を軸にしてる関係で補正する
	float left = pPlayer[PLAYER1]->GetPos().x + (pPlayer[PLAYER2]->GetPos().x - pPlayer[PLAYER1]->GetPos().x) / 2.0f - 640.0f;
	Camera::GetInstance()->SetCenterPoint(left);
	// カメラの更新
	Camera::GetInstance()->Update();

	ScreenSwing();
	// 勝敗のチェック
	GetCheckKO();

	// ゲーム停止フラグ
	if (!m_isGameStop)
	{
		for (int i = 0; i != pPlayer.size(); ++i)
		{
			// キャラクター更新
			UpdateCharacter(i);
	//		cmd[i]->InputCommand(m_dev[i]->GetInputState());
			// 各種当たり判定をチェック
			CheckPlayerCollide(i);
			CheckUpperAttackCollide(i);
			CheckLowerAttackCollide(i);
			CheckOffsetCollide(i);
			CheckEffectCollide(i);

			SetPlayerDirection(i);

			pPlayer[i]->Update();

			// コンボ数の確認
			if (combo.GetComboCount(i) == 0){
				// 自分は除く
				if (i == PLAYER1)
					hpGauge.SetOldGaugeDelete(PLAYER2, true);
				else if (i == PLAYER2)
					hpGauge.SetOldGaugeDelete(PLAYER1, true);
			}
		}

		// 必殺技ゲージ更新
		spGauge->Update();

		uiMgr->Update(breakState, hpGauge);

		UpdateBreakClothes();

		// コンボ数更新
		combo.Update();

		// パーティクルの更新
		ParticleManager::GetInstance()->Update();

		// エフェクトの更新
		EffectManager::GetInstance()->Update();
	}


	// 恥辱ゲージ(HPゲージ)更新
	hpGauge.Update();

	// 当たり判定を持つエフェクトの更新
	CollisionEffectManager::GetInstance()->Update();

	// カットイン更新
	CutInManager::GetInstance()->Update();

	// ステージ端
	StageEnd();

	// 背景魔方陣更新
	UpdateBackGroundMagicCircle();

	// パワーアップ時のエフェクト更新
	UpdatePowerUp();

	// エクストラスキル更新
	UpdateExSkill();

	// キャラクターの種類によって必殺技ゲージの溜まり方が異なる
	for (int i = 0; i != pPlayer.size(); i++)
	{
		float spAdd = 0.0f;
		switch (m_charaType[i])
		{
		case CharaName::LILIA:
			spAdd = 0.65f;
			break;

		case CharaName::RUNA:
			spAdd = 0.65f + abs(powerUPRuna[i]);
			break;
		}

		// 毎フレーム必殺技ゲージを加算する
		spGauge->Add(spAdd, i);
	}

	// 停止処理
	if (m_isGameStop)
	{
		stopCount++;

		if (stopCount > stopFrame){
			m_isGameStop = false;
			stopCount = 0;
		}
	}

	// 特定の状態だとKO状態にしない ---------------------------------

	if (m_isGameStop || ScreenEffect::GetInstance()->isPlayFade()) return;

	for (int i = 0; i != pPlayer.size(); i++){
		if (pPlayer[i]->GetState() == State::StrongAttack || 
			pPlayer[i]->GetState() == State::SpecialAttack){
			return;
		}
	}

	// --------------------------------------------------------------

	// どちらかがKOしたら
	if (isKO != -1){
		subWork = GameState::GameSet;
		workFrame = 0;
		gameFrame = 0;
	}
}


/**
* @brief バトル開始前の処理
*/
void GameMain::UpdateBeforBattle()
{
	static unsigned short frame = 0;

	switch (m_beforBattleWork)
	{
	case 0:
		// フェードがかかっていなかったら
		if (ScreenEffect::GetInstance()->isPlayFade()) return;

		// 先にプレイヤー１を状態セットする
		pPlayer[PLAYER1]->SetState(State::BeforBattle);
		m_beforBattleWork++;
		break;

	case 1:
		if (frame >= 60){
			m_beforBattleWork++;
		}
		break;

	case 2:
		// 後にプレイヤー２を状態セットする
		pPlayer[PLAYER2]->SetState(State::BeforBattle);
		m_beforBattleWork++;
		break;

	case 3:
		// 一定フレーム経過で
		if (frame >= 120){
			m_beforBattleWork = 0;
			frame = 0;
			// 次のステイトへ
			subWork = GameState::Set;
		}
		break;
	}

	// プレイヤーを更新する
	for (int i = 0; i != pPlayer.size(); i++){
		pPlayer[i]->Update();
	}

	// ステージを更新する
	pStage->Update();

	// パーティクルの更新
	ParticleManager::GetInstance()->Update();

	// フレームを加算する
	frame++;
}


/**
*	@brief	セット部分の更新処理
*	@return trueで処理の終了
*	@author	Syota Tachikawa
*	@since	2015/02/19
*/
void GameMain::UpdateSetBattle()
{
	// 魔方陣回転
	magicAngle += GetPrm->MagicCircleAddAngle;

	switch (m_setBattleWork)
	{
	case 0:
		// プレイヤーの状態を待機に設定する
		for (int i = 0; i != pPlayer.size(); i++)
		{
			pPlayer[i]->SetState(State::Neutral);
		}

		// １ラウンド目だったら
		if (roundNow == 1){
			// BGMを再生する
			SoundPlayer::GetInstance()->LoopPlay(BATTLE_BGM);
		}
		m_setBattleWork++;
		break;

	case 1:
		if (workFrame >= 100){
			workFrame = 0;
			fightVX = GetPrm->FightFontVX;
			m_setBattleWork++;
		}
		break;

	case 2:
		// 速度を位置に加算
		fightX += fightVX;

		if (fightX >= 570.0f)
		{
			fightVX = fightVX * 0.59f;
		}

		if (fightX >= GetPrm->FightFontX){
			fightX = GetPrm->FightFontX;
			fightVX = GetPrm->FightFontInitVX;
			workFrame = 0;
			m_setBattleWork++;
		}
		break;

	case 3:
		if (workFrame >= 30)
			m_setBattleWork++;
		break;

	case 4:
		// ゲームプレイへ
		subWork = GameState::Play;
		break;
	}

	// プレイヤーを更新する
	for (int i = 0; i != pPlayer.size(); i++){
		pPlayer[i]->Update();
	}

	// ステージを更新する
	pStage->Update();

	// パーティクルの更新
	ParticleManager::GetInstance()->Update();

	// フレームの更新
	workFrame++;
}


/**
*	@brief	セット部分の描画処理
*	@author	Syota Tachikawa
*	@since	2015/02/19
*/
void GameMain::RenderSetBattle()
{
	// 赤成分
	ARGB a = { 255, 255, 0, 0 };

	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BER), 640.0f, 360.0f, 0.0f, 3.0f, 50);
	// 魔方陣描画
	m_2dTex->DrawTexture(mCircleTex[1], 1000.0f, 200.0f, magicAngle, 1.2f, ALPHA_MAX, true);
	// 魔方陣描画
	m_2dTex->DrawTexARGB(mCircleTex[0], 1000.0f, 200.0f, a, true, magicAngle, 1.2f);

	switch (m_setBattleWork)
	{
	case 1:
		if (roundNow == 1)
			m_2dTex->DrawTexture((m_texData->GetTexture(TEX_ROUND1_FONT)), 640.0f, 360.0f);
		else if (roundNow == 2)
			m_2dTex->DrawTexture((m_texData->GetTexture(TEX_ROUND2_FONT)), 640.0f, 360.0f);
		else if (roundNow == 3)
			m_2dTex->DrawTexture((m_texData->GetTexture(TEX_FINALROUND_FONT)), 640.0f, 360.0f);
		break;

	case 2:
	case 3:
		m_2dTex->DrawTexture((m_texData->GetTexture(TEX_FIGHT_FONT)), fightX, 360.0f);
		break;
	}
}

/**
* @brief バトル決着の更新
*/
void GameMain::UpdateGameSet()
{
	// キー入力初期化
	for (int i = 0; i != m_dev.size(); i++){
		m_dev[i]->DataClear();
	}

	if (gameFrame % adjustFrame == 0)
	{
		switch (m_gameSetWork)
		{
		case 0:
			if (UpdateGameKO()) {
				adjustFrame = 1;
				pPlayer[losePlNum]->SetState(State::Ko);
				m_gameSetWork++;
			}
			break;

		case 1:
			// 勝利カウントを増やす
			if (losePlNum == PLAYER1)
			{
				winNum[PLAYER2]++;
			}
			else if (losePlNum == PLAYER2)
			{
				winNum[PLAYER1]++;
			}
			// ラウンド数を増やす
			roundNow++;

			m_gameSetWork++;
			break;

		case 2:
			if (workFrame > 120){
				// 2ラウンド先取したら終了
				if (winNum[PLAYER1] >= 2 || winNum[PLAYER2] >= 2){
					subWork = GameState::KO;
				}
				else {
					subWork = GameState::Set;
					Initialize();
				}
			}
			break;
		}

		// プレイヤーを更新する
		for (int i = 0; i != pPlayer.size(); i++){
			pPlayer[i]->Update();
			// プレイヤーの向きを更新
			SetPlayerDirection(i);
		}

		// ステージ端
		StageEnd();

		// ステージを更新する
		pStage->Update();

		// パーティクルの更新
		ParticleManager::GetInstance()->Update();

		// エフェクトの更新
		EffectManager::GetInstance()->Update();

		// 当たり判定付きエフェクトの更新
		CollisionEffectManager::GetInstance()->Update();

		// エクストラスキルの更新
		UpdateExSkill();
	}
	workFrame++;
}

/**
* @brief バトルKOの更新
*/
void GameMain::UpdateKO()
{
	int winPl;

	// 勝利プレイヤーの設定
	if (losePlNum == PLAYER1)
		winPl = PLAYER2;
	else if (losePlNum == PLAYER2)
		winPl = PLAYER1;

	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Vs2P)
	{
		// ボタンの入力を確認したら特殊演出にフラグを立てる
		if (m_dev[winPl]->CheckInputMask(INPUT_01)){
			isSpecial = true;
		}
	}
	else if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU)
	{
		// ボタンの入力を確認したら特殊演出にフラグを立てる
		if (m_dev[0]->CheckInputMask(INPUT_01)){
			isSpecial = true;
		}
	}

	if (isSpecial)
	{
		// 勝利プレイヤーを特殊演出状態にする
		pPlayer[winPl]->SetState(State::SpecialProduction);

		// フレームが一定数を超えたら演出に移る
		if (workFrame > 120){
			workFrame = 0;
			// フェードの設定
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::White, FADE_FRAME);
			// ボイスの設定
			switch (selectChara[losePlNum])
			{
			case LILIA:
				SoundPlayer::GetInstance()->Play(LILIA_GASP_VOICE);
				break;

			case RUNA:
				SoundPlayer::GetInstance()->Play(RUNA_GASP_VOICE);
				break;
			}
			// サブワークを特殊演出に設定
			subWork = GameState::Special;
		}

		// フレームを加算する
		workFrame++;
	}
	// 特殊演出フラグが立っていなければフレームを回す
	else {
		workFrame++;
	}

	// ボタンが入力されずに一定フレーム過ぎたらバトルを終了させる
	if (workFrame >= 300)
	{
		subWork = GameState::End;
	}

	// パーティクルの更新
	ParticleManager::GetInstance()->Update();

	// エフェクトの更新
	EffectManager::GetInstance()->Update();

	// 入力デバイスの更新
	for (int i = 0; i != m_dev.size(); i++){
		m_dev[i]->GetInput();
	}
}

/**
* @brief KO部分の処理
*/
bool GameMain::UpdateGameKO()
{
	switch (gameWork)
	{
	case 0:
		// 敗北プレイヤー設定
		losePlNum = isKO;
		// フレーム初期化
		workFrame = 0;
		// 効果音を再生する
		SoundPlayer::GetInstance()->Play(KO_SE);
		// ボイスを再生する
		// ボイスの設定
		switch (selectChara[losePlNum])
		{
		case LILIA:
			SoundPlayer::GetInstance()->Play(LILIA_LOSE_VOICE);
			break;

		case RUNA:
			SoundPlayer::GetInstance()->Play(RUNA_LOSE_VOICE);
			break;
		}
		gameWork++;
		break;

	case 1:
		// フレーム調整
		adjustFrame = 13;
		// KOしたプレイヤーの状態を設定
		pPlayer[isKO]->SetState(State::Ko);
		gameWork++;
		break;

	case 2:
		if (workFrame >= 120){
			// 戻す
			adjustFrame = 1;
		}

		// 地面に付くまで
		if (pPlayer[isKO]->GetPos().y < GetPrm->Ground){
			return false;
		}

		// どちらかが待機状態に戻った時			
		if (workFrame > 240)
		{
			gameWork++;
			workFrame = 0;
		}
		break;

	case 3:
		if (isKO == PLAYER1){
			pPlayer[PLAYER2]->SetState(State::Win);
		}

		else if (isKO == PLAYER2){
			pPlayer[PLAYER1]->SetState(State::Win);
		}

		if (workFrame >= 120)
		{
			workFrame = 0;
			return true;
		}
		break;
	}
	return false;
}

/**
* @brief バトル特殊シーンの更新
*/
void GameMain::UpdateSpecial()
{
	int black[3] = { 0, 0, 0 };

	// 特殊演出が終わったら
	if (SpecialProduction())
	{
		// ヌード
		displayNumber[PLAYER2] = NUDE;
		// バトルの終了
		subWork = GameState::End;
		// フェードの設定
		ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);

		workFrame = 0;
	}

	// プレイヤーを更新する
	for (int i = 0; i != pPlayer.size(); i++){
		pPlayer[i]->Update();
	}

	// ステージ端
	StageEnd();

	// ステージを更新する
	pStage->Update();

	// エフェクトの更新
	EffectManager::GetInstance()->Update();

	// 当たり判定付きのエフェクトの更新
	CollisionEffectManager::GetInstance()->Update();

	// パーティクルの更新
	ParticleManager::GetInstance()->Update();

	// 当たり判定の更新
	for (int i = 0; i != pPlayer.size(); i++){
		CheckUpperAttackCollide(i);
	}
}

/**
* @brief バトル終了の更新
*/
void GameMain::UpdateEnd()
{
	if (!ScreenEffect::GetInstance()->isPlayFade())
		subWork = GameState::Exit;

	// フレームを回す
	workFrame++;
}

/**
* @brief バトル終了の更新
*/
void GameMain::UpdateExit()
{
	// 負けたプレイヤー番号を転送する
	UniqueData::GetInstance()->SetLosePlayer(losePlNum);

	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Demo)
		// デモプレイならタイトル画面に飛ばす
		SequenceChanger::GetInstance()->ChangeScene(new Title());
	else
		// 通常バトルならリザルト画面に飛ばす
		SequenceChanger::GetInstance()->ChangeScene(new Result());
}



/**
* @brief 背景に描画する
*/
void GameMain::RenderBackGround()
{
	// 必殺技時に背景に魔方陣を拡大と回転を加えて描画する
	for (int i = 0; i != pPlayer.size(); i++){
		if (pPlayer[i]->GetState() == State::SpecialAttack || pPlayer[i]->GetState() == State::AttackSpecialPursuit)
		{
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VSPREPARATION_BG), 640.0f, 360.0f);
			m_2dTex->DrawTexture(mCircleTex[0], 640.0f, 360.0f, mCircleAngle, mCircleScale, mCircleAlpha, true);
		}
	}

	if (pPlayer[PLAYER1]->GetState() == State::SpecialAttack)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_MAGICCIRCLE_P), pPlayer[PLAYER2]->GetPos().x - GetCameraPos, pPlayer[PLAYER2]->GetPos().y + 50.0f, 0.0f, 1.2f);
	if (pPlayer[PLAYER2]->GetState() == State::SpecialAttack)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_MAGICCIRCLE_P), pPlayer[PLAYER1]->GetPos().x - GetCameraPos, pPlayer[PLAYER1]->GetPos().y + 50.0f, 0.0f, 1.2f);

	// 特殊演出時
	if (pPlayer[PLAYER1]->GetState() == State::SpecialProduction || pPlayer[PLAYER2]->GetState() == State::SpecialProduction)
	{
		m_2dTex->DrawBox(0.0f - 100.0f + swingVal[0], 0.0f - 100.0f + swingVal[0], AppIns->GetWindowWidth() + 100.0f + swingVal[0], AppIns->GetWindowHeight() + 100.0f + swingVal[0], 0xffffffff);
	}
}

/**
* @brief プレイヤー同士の当たり判定
*/
void GameMain::CheckPlayerCollide(int index)
{
	// プレイヤーの数だけループ
	for(int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は除く
		if (i == index) {
			continue;
		}

		// 判定チェック
		if (Collide::CheckRectAndRect(pPlayer[index]->GetPos(), pPlayer[i]->GetPos(),
			pPlayer[index]->GetHitRect(), pPlayer[i]->GetHitRect()))
		{
			// 変数名が長いから定義しておく
			Vector2 pos1 = pPlayer[index]->GetPos();
			Vector2 pos2 = pPlayer[i]->GetPos();
			Dir dir1 = pPlayer[index]->GetDirection();
			Dir dir2 = pPlayer[i]->GetDirection();

			// ズラす値をプレイヤー座標に加算
			pos1.x += Collide::PlayerDisplace(pos1, pos2, pPlayer[index]->GetHitRect(), pPlayer[i]->GetHitRect(), dir1);
			// 座標セット
			pPlayer[index]->SetPos(pos1);

			// ズラす値をプレイヤー座標に加算
			pos2.x += Collide::PlayerDisplace(pos2, pos1, pPlayer[i]->GetHitRect(), pPlayer[index]->GetHitRect(), dir2);
			// 座標セット
			pPlayer[i]->SetPos(pos2);
		}
	}
}

/**
* @brief 上段攻撃の当たり判定
*/
void GameMain::CheckUpperAttackCollide(int index)
{
	// 攻撃判定が発生していなかったら処理を終了する
	if (!pPlayer[index]->isAttackJudge()){
		return;
	}
	
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は除く
		if (i == index) {
			continue;
		}

		// 当たっていなかったら処理を終了する
		if (!pPlayer[index]->isUpperAttackHit(*pPlayer[i])){
			return;
		}

		// 被弾時の処理
		pPlayer[i]->Damage(*pPlayer[index], AttackPoint::Upper);

		// ガード
		if (pPlayer[i]->GetState() == State::Guard || pPlayer[i]->GetState() == State::GuardNow)
		{
			// ダメージを加える
			UpdateAttackDamage(index);
			// 必殺技ゲージ加算
			spGauge->Add(2.0f, i);
			return;
		}

		// コンボ数を増やす
		combo.Add(index);
		// 必殺技ゲージチャージ
		spGauge->Add(7.0f, index);

		// パーティクル生成
		for (int p = 0; p < 10; p++){
			int scale = rand() % 3;
			ParticleManager::GetInstance()->Add(make_shared<HitParticle>(pPlayer[i]->GetPos(), 0.35f));
		}

		// ヒットストップを行う
		switch (pPlayer[index]->GetState())
		{
		case State::WeakAttack:
		case State::MediumAttack:
		case State::SpecialProduction:
			int stopF;
			if (pPlayer[index]->GetState() == State::WeakAttack ||
				pPlayer[index]->GetState() == State::MediumAttack)
			{
				stopF = 4;
			}
			else{
				isSwing[0] = true;
				isSwing[1] = true;
				stopF = 120;
			}
			// ゲームを止める
			SetGameStop(stopF, true);
			break;

		case State::WeakDerivationAttack:
			// ゲームを止める
			SetGameStop(8, true);
			break;

		case State::DashAttack:
		case State::RaidAttack:
			// ゲームを止める
			SetGameStop(6, true);
			break;

		case State::AttackSpecialPursuit:
		{
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::White, FADE_FRAME);
			// ゲームを止める
			SetGameStop(120, true);
			break;
		}


		case State::JumpAttack:
			// ゲームを止める
			SetGameStop(3, true);
			break;
		}

		// 端っこの位置修正
		StageEndShift(index);
		// ダメージを加算
		UpdateAttackDamage(index);
	}
}

/**
* @brief 下段攻撃の当たり判定
*/
void GameMain::CheckLowerAttackCollide(int index)
{
	// 攻撃判定が発生していなかったら処理を終了する
	if (!pPlayer[index]->isAttackJudge()){
		return;
	}

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は除く
		if (i == index) {
			continue;
		}

		// 当たっていなかったら処理を終了する
		if (!pPlayer[index]->isLowerAttackHit(*pPlayer[i])){
			return;
		}

		// 被弾時の処理
		pPlayer[i]->Damage(*pPlayer[index], AttackPoint::Lower);

		// ガード
		if (pPlayer[i]->GetState() == State::SquatGuard || pPlayer[i]->GetState() == State::SquatGuardNow)
		{
			// ダメージを加える
			UpdateAttackDamage(index);
			// 必殺技ゲージ加算
			spGauge->Add(2.0f, i);
			return;
		}

		// コンボ数を増やす
		combo.Add(index);
		// 必殺技ゲージチャージ
		spGauge->Add(7.0f, index);

		// パーティクル生成
		for (int p = 0; p < 10; p++){
			int scale = rand() % 3;
			ParticleManager::GetInstance()->Add(make_shared<HitParticle>(pPlayer[i]->GetPos(), 0.35f));
		}

		// 端っこの位置修正
		StageEndShift(index);
		// ダメージを加算
		UpdateAttackDamage(index);
	}
}

/**
* @brief 相殺判定
*/
void GameMain::CheckOffsetCollide(int index)
{
	// 攻撃判定が発生していなかったら処理を終了する
	if (!pPlayer[index]->isAttackJudge()){
		return;
	}

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は除く
		if (i == index){
			continue;
		}

		// 同じ攻撃状態でないと発生させない
		if (pPlayer[index]->GetState() != pPlayer[i]->GetState()){
			return;
		}

		if (Collide::CheckRectAndRect(pPlayer[index]->GetPos(), pPlayer[i]->GetPos(),
			pPlayer[index]->GetAttackRect(), pPlayer[i]->GetAttackRect()))
		{
			// 効果音の設定
			SoundPlayer::GetInstance()->Play(OFFSET_SE);
			pPlayer[index]->SetState(State::Offset);
			pPlayer[i]->SetState(State::Offset);

			// 中心を出す
			float centerPos = (pPlayer[index]->GetPos().x + pPlayer[i]->GetPos().x) / 2;

			// パーティクル生成
			for (int i = 0; i < 10; i++)
				ParticleManager::GetInstance()->Add(make_shared<OffsetParticle>(Vector2(centerPos, pPlayer[index]->GetPos().y)));
		}
	}
}

void GameMain::CheckEffectCollide(int index)
{
	// 当たっているかのチェック
	CollisionEffectManager::GetInstance()->CollisionCheckPlayer(pPlayer[index]);

	if (pPlayer[index]->GetState() != State::DamageEffect) return;

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は除く
		if (i == index) {
			continue;
		}

		// コンボ数を増やす
		combo.Add(i);
		// ダメージ
		UpdateAttackDamage(i);
	}

}

void GameMain::SetPlayerDirection(int index)
{
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は除く
		if (i == index){
			continue;
		}

		if (pPlayer[index]->GetPos().x < pPlayer[i]->GetPos().x){
			pPlayer[i]->SetDirection(Dir::Left);
			pPlayer[index]->SetDirection(Dir::Right);
		}
		else{
			pPlayer[i]->SetDirection(Dir::Right);
			pPlayer[index]->SetDirection(Dir::Left);
		}
	}
}

/**
* @brief キャラクターの更新
*/
void GameMain::UpdateCharacter(int index)
{
	// コンピューターの数を取得する
	int comCount = UniqueData::GetInstance()->GetComputerCount();

	// コンピューターの更新する
	m_com.ThinkUpdate(pPlayer, index, comCount, spGauge);
	
	// 入力デバイスの数を取得する
	int devCount = m_dev.size();

	if (index > devCount - 1) return;

	// 特定の条件を満たした場合は派生技を出せる
	if (pPlayer[index]->GetState() == State::WeakAttack && 
		pPlayer[index]->CanDerivation() && 
		m_dev[index]->CheckInputMask(INPUT_01))
	{
		// 派生攻撃
		pPlayer[index]->SetState(State::WeakDerivationAttack);
		return;
	}

	if (pPlayer[index]->GetState() == State::Jump || pPlayer[index]->GetState() == State::JumpFront || 
		pPlayer[index]->GetState() == State::JumpBack || pPlayer[index]->GetState() == State::JumpGuard)
	{
		// ジャンプガード
		if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right){
			pPlayer[index]->SetState(State::JumpGuard);
		}
		else if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left){
			pPlayer[index]->SetState(State::JumpGuard);
		}

		// ボタンが入力されたら
		if (m_dev[index]->CheckInputMask(INPUT_01)){
			pPlayer[index]->SetState(State::JumpAttack);
		}
	}

	if (m_dev[index]->CheckInput(INPUT_01) && pPlayer[index]->CanPassive()){
		pPlayer[index]->SetState(State::Passive);
	}

	// 操作不能なら処理終了
	if (!pPlayer[index]->CanControll()) return;

	// 操作不能状態なら処理をしない
	if (!pPlayer[index]->isControll()) return;

	// 強攻撃
	if (m_dev[index]->CheckInputMask(INPUT_04))
	{
		// ゲージ量の確認（不足してたら処理しない）
		if (!spGauge->IsUseGauge(State::StrongAttack, pPlayer[index]->GetID())) return;
		spGauge->Use(pPlayer[index]->GetID());
		isUseExSkill[index] = true;
		pPlayer[index]->SetState(State::StrongAttack);
		return;
	}
	// 必殺技
	else if (m_dev[index]->CheckInputMask(INPUT_02))
	{
		// ゲージ量の確認（不足してたら処理しない）
		if (!spGauge->IsUseGauge(State::SpecialAttack, pPlayer[index]->GetID())) return;
		spGauge->Use(pPlayer[index]->GetID());
		pPlayer[index]->SetState(State::SpecialAttack);
		return;
	}

	// 待機
	if (m_dev[index]->GetInputState() == NULL){
		pPlayer[index]->SetState(State::Neutral);
	}

	// 前進
	if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Left)
		pPlayer[index]->SetState(State::Advance);

	// ガード
	else if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right)
		pPlayer[index]->SetState(State::Guard);

	// 前進
	if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Right)
		pPlayer[index]->SetState(State::Advance);

	// ガード
	else if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left)
		pPlayer[index]->SetState(State::Guard);

	// しゃがみ
	if (m_dev[index]->CheckInput(INPUT_DOWN))
		pPlayer[index]->SetState(State::Squat);

	// しゃがみガード
	if (m_dev[index]->CheckInput(INPUT_DOWN) && m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right)
		pPlayer[index]->SetState(State::SquatGuard);

	// しゃがみガード
	else if (m_dev[index]->CheckInput(INPUT_DOWN) && m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left)
		pPlayer[index]->SetState(State::SquatGuard);

	// しゃがみ攻撃
	if (m_dev[index]->CheckInputMask(INPUT_01) && pPlayer[index]->GetState() == State::Squat){
		pPlayer[index]->SetState(State::SquatAttack);
		return;
	}
	// しゃがみガード
	else if (m_dev[index]->CheckInputMask(INPUT_01) && pPlayer[index]->GetState() == State::SquatGuard){
		pPlayer[index]->SetState(State::SquatAttack);
		return;
	}

	// 遠距離攻撃
	if (pPlayer[index]->GetState() == State::Squat && m_dev[index]->CheckInputMask(INPUT_03)){
//	if (cmd[index]->GetSkillNumber() == 0){
		pPlayer[index]->SetState(State::UnderAttack);
		return;
	}

	// 遠距離攻撃
	else if (pPlayer[index]->GetState() == State::SquatGuard && m_dev[index]->CheckInputMask(INPUT_03)){
		pPlayer[index]->SetState(State::UnderAttack);
		return;
	}

	// ダッシュ
	if (m_dev[index]->GetJoyStickRepel() && pPlayer[index]->GetState() == State::Advance)
		pPlayer[index]->SetState(State::Dash);

	// バックステップ
	else if (m_dev[index]->GetJoyStickRepel() && pPlayer[index]->GetState() == State::Guard)
		pPlayer[index]->SetState(State::BackStep);

	// ダッシュ攻撃
	if (pPlayer[index]->GetState() == State::Dash &&m_dev[index]->CheckInputMask(INPUT_01)){
		pPlayer[index]->SetState(State::DashAttack);
		return;
	}

	// スティック入力が上
	if (m_dev[index]->CheckInput(INPUT_UP))
	{
		// 前ジャンプ
		if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Right ||
			m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Left){
			pPlayer[index]->SetState(State::JumpFront);
		}
		// 後ジャンプ
		else if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right || 
			m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left){
			pPlayer[index]->SetState(State::JumpBack);
		}
		// ジャンプ
		else
			pPlayer[index]->SetState(State::Jump);
	}

	// 奇襲攻撃
	if (m_dev[index]->CheckInputMask(INPUT_01) && m_dev[index]->CheckInputMask(INPUT_03))
		pPlayer[index]->SetState(State::RaidAttack);

	// 弱攻撃
	else if (m_dev[index]->CheckInputMask(INPUT_01))
		pPlayer[index]->SetState(State::WeakAttack);

	// 中攻撃
	else if (m_dev[index]->CheckInputMask(INPUT_03))
		pPlayer[index]->SetState(State::MediumAttack);
}

/**
*	@brief	勝敗が付いたか否かを取得
*
*	@author	Syota Tachikawa
*	@since	2015/12/22
*/
void GameMain::GetCheckKO()
{
	isKO = hpGauge.isDead();
}

/**
* @brief 攻撃者の番号
*/
void GameMain::UpdateAttackDamage(int index)
{
	float damage = pPlayer[index]->GetPower();

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 自分は入らない
		if (index == i){
			continue;
		}

		// パワーアップ時のダメージ加算量(LILIA以外は0しか入らない)
		damage += abs(powerUPLilia[index]);

		// ガード中ならば
		if (pPlayer[i]->GetState() == State::Guard ||
			pPlayer[i]->GetState() == State::JumpGuard ||
			pPlayer[i]->GetState() == State::GuardNow)
		{
			damage = damage / GetPrm->GuardDamageMitiGation;
		}

		damage = combo.ComboDamageCorrection(damage, index);

		hpGauge.DamageAdd(damage, i);
	}
}


/**
* @brief エクストラスキルの更新
*/
void GameMain::UpdateExSkill()
{
	// フレーム
	static int frame = 0;

	// フレームを加算
	frame++;

	for (int i = 0; i < JOY_MAX; i++)
	{
		// エクストラスキル発動したら背景を暗くする
		if (isUseExSkill[i]){
			// エフェクトを生成する
			EffectManager::GetInstance()->Add(make_shared<ShineEffect>(pPlayer[i]->GetPos()));
			// 効果音を再生する
			SoundPlayer::GetInstance()->Play(EXTRASKILL_SE);
			// フラグを折る
			isUseExSkill[i] = false;
			// ゲームを止める
			SetGameStop(20, true);
			// アルファ値の変更
			stageAlpha = 150;
		}
		else {
			if (frame > 60){
				frame = 0;
				stageAlpha = ALPHA_MAX;
			}
		}

	}
	// コンピューターの数を取得する
	int comCount = UniqueData::GetInstance()->GetComputerCount();
	// コンピューターが存在したら
	if (comCount < 1) return;

	static bool flg = false;
	// 強攻撃時に一度だけ処理する
	if (pPlayer[PLAYER2]->GetState() == State::StrongAttack){
		// フラグが立ってたら終了
		if (flg) return;

		// エクストラスキルフラグON
		isUseExSkill[PLAYER2] = true;
		flg = true;
	}
	else{
		flg = false;
	}
}

/**
* @brief 背景に描画する魔方陣の更新
*/
void GameMain::UpdateBackGroundMagicCircle()
{
	// 必殺技背景魔方陣更新
	if (pPlayer[PLAYER1]->GetState() == State::SpecialAttack || pPlayer[PLAYER1]->GetState() == State::AttackSpecialPursuit ||
		pPlayer[PLAYER2]->GetState() == State::SpecialAttack || pPlayer[PLAYER2]->GetState() == State::AttackSpecialPursuit)
	{
		// カットインが表示されていなかったら
		if (!CutInManager::GetInstance()->IsPlayCutIn()){
			mCircleAngle += 10.0f;
			mCircleAlpha++;
			mCircleScale += 0.003f;
		}
	}
	else{
		mCircleScale = 0.0f;
	}
}


void GameMain::ScreenSwing()
{
	int swingFrame = 1;

	for (int i = 0; i != pPlayer.size(); i++)
	{
		if (pPlayer[i]->GetState() == State::Blowoff){
			swingFrame = 20;
			isSwing[i] = true;
		}

		if (pPlayer[i]->GetState() == State::SpecialProduction)
		{
			swingFrame = 120;
		}

		// スクリーンを揺らすフラグを切る
		if (gameFrame % swingFrame == 0)
		{
			isSwing[i] = false;
		}

		if (isSwing[i]){
			swingVal[i] = Utility::Random(-30.0f, 30.0f);
		}
		else{ swingVal[i] = 0; }
	}
}

/**
* @brief 破れエフェクトの更新
*/
void GameMain::UpdateBreakClothes()
{
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// 必殺技中は処理をしない
		if (pPlayer[i]->GetState() == State::SpecialAttack ||
			pPlayer[i]->GetState() == State::AttackSpecialPursuit)
			return;

		// ブレイクフラグが立っていなかったら処理をしない
		if (!uiMgr->IsClothesBreak(i)) continue;

		// ゲームを停止させる
		SetGameStop(30, true);

		// ボイスの設定
		switch (selectChara[i])
		{
		case LILIA:
			SoundPlayer::GetInstance()->Play(LILIA_SCREAM_VOICE);
			break;

		case RUNA:
			SoundPlayer::GetInstance()->Play(RUNA_SCREAM_VOICE);
			break;
		}

		// 泡パーティクルを発生させる
		for (int p = 0; p < 30; p++)
		{
			ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pPlayer[i]->GetPos(), Utility::Random(0.4f, 0.6f)));
		}

		// フェードをかける
		ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::White, 50);
	}
}

/**
*	@brief	特殊演出
*	@author	Syota Tachikawa
*	@since	2015/01/27
*/
bool GameMain::SpecialProduction()
{
	switch (spWork)
	{
	case 0: // 初期化する
		workFrame = 0;
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			for (int i = 0; i < 100; i++)
			{
				Vector2 pos = Vector2(Utility::Random(-20.0f, 1300.0f), Utility::Random(-20.0f, 800.0f));
				float scale = Utility::Random(1.5f, 3.0f);
				ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pos, scale));
				ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pos, scale));
				ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pos, scale));
			}
			for (int i = 0; i < 5; i++){
				formX[i] = 150.0f * i;
				formY[i] = Utility::Random(10.0f, 710.0f);
			}

			spWork++;
		}
		break;

	case 1: // 顔を映す
		specialTexY = 1200.0f;
		workFrame++;
		if (workFrame >= 150){
			spWork++;
			workFrame = 0;
		}
		break;

	case 2: // 体を映す
		specialTexY = 600.0f;
		workFrame++;
		if (workFrame >= 120){
			spWork++;
			workFrame = 0;
		}
		break;

	case 3: // 脚を映す
		specialTexY = -100.0f;
		workFrame++;
		if (workFrame >= 120){
			spWork++;
			workFrame = 0;
			specialTexY = -400.0f;
		}
		break;

	case 4:
		workFrame++;
		specialTexY += 2.0f;
		if (specialTexY >= 1220.0f) {
			spWork++;
			specialTexY = 360.0f;
			specialTexScale[0] = 0.0f;
			workFrame = 0;
		}
		break;

	case 5:
		specialTexScale[0] += 0.001f;
		if (specialTexScale[0] >= 0.2f) {
			SoundPlayer::GetInstance()->Play(CHEER_SE);
			SoundPlayer::GetInstance()->Play(LAUGH_SE);
			spWork++;
		}
		break;

	case 6:
		workFrame++;
		if (workFrame >= 120){
			workFrame = 0;
			spWork = 0;
			return true;
		}
		break;
	}

	if (workFrame % 60)
	{
		if (formFlag)
			formFlag = false;
		else
			formFlag = true;
	}
	for (int i = 0; i < 5; i++){
		formX[i] += 0.3f;
		if (formFlag)
			formY[i] += 0.3f;
		else 
			formY[i] -= 0.3f;
	}

	light2Angle += 4.0f;

	return false;
}

/**
*	@brief	ゲームの更新を止める
*	@param	frame - 止めるフレーム数
*	@author	Syota Tachikawa
*	@since	2015/02/15
*/
void GameMain::SetGameStop(int frame , bool flag)
{
	stopFrame = frame;
	m_isGameStop = flag;
}

/**
* @brief プレイヤーがステージの端で攻撃していたらハメれないように対象者と距離を離す
*/
void GameMain::StageEndShift(int index)
{
	for (int i = 0; i != pPlayer.size(); i++)
	{
		if (index == i) continue;

		if (pPlayer[i]->GetPos().x <= GetPrm->StageLeftShiftLimit || pPlayer[i]->GetPos().x >= GetPrm->StageRightShiftLimit)
		{
			pPlayer[index]->SetSpeed(-1.0f);
		}
	}
}

void GameMain::RenderSpecialProduction()
{
	// 特殊演出時の背景
	if (spWork != 0)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG_SPECIAL), 640.0f, 360.0f);

	// 特殊演出時のキャラクター
	if (subWork == GameState::Special && spWork != 0){
		m_2dTex->DrawTexture(spcialTex[selectChara[losePlNum]], 680.0f, specialTexY, -3.0f, specialTexScale[0]);
		// 泡の描画
		for (int i = 0; i < 5; i++)
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_FORM), formX[i], formY[i], 0.0f, 0.7f, 255, true);

		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 1100.0f, 200.0f, light2Angle, 0.4f, 255, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 100.0f, 500.0f, light2Angle, 0.4f, 255, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 600.0f, 300.0f, light2Angle, 0.4f, 255, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 900.0f, 600.0f, light2Angle, 0.4f, 255, true);
	}

	if (subWork == GameState::Special){
		ParticleManager::GetInstance()->Render();
	}
}

void GameMain::UpdatePowerUp()
{
	// どちらかのプレイヤーのHPが半分以上あったら処理をしない
	if (hpGauge.GetHP(PLAYER1) >= GetPrm->HpMax / 2 ||
		hpGauge.GetHP(PLAYER2) >= GetPrm->HpMax / 2){
		return;
	}

		// パワーアップパーティクル
		if (gameFrame % 10 == 0)
		{
			// 座標登録
			Vector2 plPos[2];
			Vector2 plLPos[2];
			Vector2 plRPos[2];

			for (int i = 0; i != pPlayer.size(); i++)
			{
				plPos[i] = Vector2(pPlayer[i]->GetPos().x, pPlayer[i]->GetPos().y + 130.0f);
				plPos[i] = Vector2(pPlayer[i]->GetPos().x - 10.0f, pPlayer[i]->GetPos().y + 120.0f);
				plPos[i] = Vector2(pPlayer[i]->GetPos().x + 10.0f, pPlayer[i]->GetPos().y + 120.0f);

				// 生成
				ParticleManager::GetInstance()->Add(make_shared<PowerupParticle>(plPos[i], 1.0f, pwUpAlpha[i]));
				ParticleManager::GetInstance()->Add(make_shared<PowerupParticle>(plLPos[i], 1.0f, pwUpAlpha[i]));
				ParticleManager::GetInstance()->Add(make_shared<PowerupParticle>(plRPos[i], 1.0f, pwUpAlpha[i]));
			}
		}

	for (int i = 0; i != pPlayer.size(); i++)
	{
		switch (m_charaType[i])
		{
			// キャラクターがリリアの時
		case LILIA:
			powerUPLilia[i] = hpGauge.GetHP(i) - GetPrm->HpMax / 2;
			pwUpAlpha[i] += 0.03f;
			// ここを弄るとパワーアップ時の攻撃力加算量を変更できる
			if (pPlayer[i]->GetState() == State::SpecialAttack){
				powerUPLilia[i] = powerUPLilia[i] * 0.003f;	// 必殺技時は加算量を極小にする
			}
			else if (pPlayer[i]->GetState() == State::StrongAttack){
				powerUPLilia[i] = powerUPLilia[i] * 0.01f;
			}
			else{
				powerUPLilia[i] = powerUPLilia[i] * 0.05f;
			}
			break;
	
			// キャラクターがルナの時
		case RUNA:
			powerUPRuna[i] = hpGauge.GetHP(i) - GetPrm->HpMax / 2;
			pwUpAlpha[i] += 0.03f;

			powerUPRuna[i] = powerUPRuna[i] * 0.002f;
			break;
		}
	}
}

/**
* @brief ステージ端から出ないようにする
*/
void GameMain::StageEnd()
{
	Vector2 end[2];
	
	for (int i = 0; i != pPlayer.size(); i++)
	{
		end[i].x = max(STAND_CHARACTER_WIDTH + CHARACTER_MARGIN + GetCameraPos, min(1080.0f - CHARACTER_MARGIN + GetCameraPos, pPlayer[i]->GetPos().x));
		end[i].y = pPlayer[i]->GetPos().y;
		// 座標を戻す
		pPlayer[i]->SetPos(end[i]);
	}
}

/**
* @brief 終了
*/
void GameMain::Finalize()
{
	// バトルBGMを停止する
	SoundPlayer::GetInstance()->Stop(BATTLE_BGM);

	// コンテナの要素削除
	m_dev.erase(m_dev.begin(), m_dev.end());
	// コンテナの要素削除
	pPlayer.erase(pPlayer.begin(), pPlayer.end());
}