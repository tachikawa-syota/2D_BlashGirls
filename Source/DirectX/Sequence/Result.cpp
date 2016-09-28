#include "Result.h"
#include "GameMain.h"
#include "Title.h"
#include "SequenceChanger.h"
#include "..\Common\UniqueData.h"
#include "..\DirectX\SoundPlayer.h"

/**
* @brief 作成
*/
void Result::Create()
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// 選択キャラクターデータを取得
	m_select = UniqueData::GetInstance()->GetSelectCharacter();
	// 敗北したプレイヤー番号を取得
	m_losePl = UniqueData::GetInstance()->GetLosePlayer();

	// 2P対戦モード
	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Vs2P){
		// デバイスを接続されている数だけ取得する
		for (int i = 0; i < JOY_MAX; i++){
			m_dev.emplace_back(new InputMask(i));
		}
		// カーソルを操作できるプレイヤー番号を設定する
		m_controlPlayer = m_losePl;
	}

	// CPU対戦モード
	else if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU){
		m_dev.emplace_back(new InputMask(PLAYER1));
		// CPU対戦の場合1Pが必ずカーソルを操作できる
		m_controlPlayer = PLAYER1;
	}

	// テクスチャをコピー
	m_loserPlayerTex[PLAYER1] = m_texData->GetTexture(TEX_PLAYER1_FONT);
	m_loserPlayerTex[PLAYER2] = m_texData->GetTexture(TEX_PLAYER2_FONT);

	m_loserCharaTex_[LILIA] = m_texData->GetTexture(TEX_LILIA_CUTIN_01);
	m_loserCharaTex_[RUNA] = m_texData->GetTexture(TEX_RUNA_CUTIN_01);
}

/**
* @brief 初期化
*/
void Result::Initialize()
{
	m_alpha = ALPHA_MAX;
	m_frame = 0;
	m_subWork = 0;
	m_cursolWork = 0;
	m_cursolY = 355.0f;

	// BGMを再生する
	SoundPlayer::GetInstance()->LoopPlay(RESULT_BGM);
	// ボイスを再生する
	switch (m_select[m_losePl])
	{
	case LILIA:
		SoundPlayer::GetInstance()->Play(LILIA_GASP_VOICE2);
		break;

	case RUNA:
		SoundPlayer::GetInstance()->Play(RUNA_GASP_VOICE2);
		break;
	}
}

/**
* @brief 更新
*/
void Result::Update()
{
	// 入力デバイスの更新
	m_dev[m_controlPlayer]->GetInput();

	switch (m_subWork)
	{
	case 0:
		// フェードが掛かっていなかったら
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			m_subWork++;
		}
		break;

	case 1:
		// 一定フレームを超えたら次の挙動に移る
		if (m_frame >= 60)
		{
			m_subWork++;
			m_alpha = 170;
		}
		// フレームを加算する
		m_frame++;
		break;

	case 2:
		// カーソルの動作
		CursolMove();
		break;
	}	
}

/**
* @brief 描画
*/
void Result::Render()
{
	// 背景
	// キャラクター選択画面と同じ背景を使う(使いまわし)
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CHARASELECT_BG), 640.0f, 360.0f, 0.0f, 1.0f, m_alpha);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LOSE_FONT), 800.0f, 200.0f, 0.0f, 1.5f, m_alpha);
	m_2dTex->DrawTexture(m_loserCharaTex_[m_select[m_losePl]], 200.0f, 640.0f, 0.0f, 1.0f, m_alpha);
	m_2dTex->DrawTexture(m_loserPlayerTex[m_losePl], 900.0f, 400.0f, 0.0f, 0.3f, m_alpha);

	if(m_subWork == 2){
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CONTINUE_FRAME), 640.0f, 500.0f);	// 枠
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CONTINUE_CURSOL), 640.0f, m_cursolY);	// カーソル
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CONTINUE_FONT), 640.0f, 500.0f);	// 文字

	}
}

/**
* @brief カーソルの移動
*/
void Result::CursolMove()
{
	if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_DOWN))
	{
		m_cursolWork++;
		SoundPlayer::GetInstance()->Play(CURSOL_SE);
		if (m_cursolWork > 1)
			m_cursolWork = 0;
	}
	if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_UP))
	{
		m_cursolWork--;
		SoundPlayer::GetInstance()->Play(CURSOL_SE);
		if (m_cursolWork < 0)
			m_cursolWork = 1;
	}

	switch (m_cursolWork)
	{
	case 0:
		// スティックが倒されたらカーソルを動かす
		m_cursolY = 355.0f;
		// キー入力を確認したら
		if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_01))
		{
			SoundPlayer::GetInstance()->Play(DECISION_SE);
			SequenceChanger::GetInstance()->ChangeScene(new GameMain());
		}
		break;

	case 1:
		// スティックが倒されたらカーソルを動かす
		m_cursolY = 500.0f;
		// キー入力を確認したら
		if (m_dev[m_controlPlayer]->CheckInputMask(INPUT_01))
		{
			SoundPlayer::GetInstance()->Play(DECISION_SE);
			SequenceChanger::GetInstance()->ChangeScene(new Title());
		}
		break;
	}
}

/**
* @brief 終了
*/
void Result::Finalize()
{
	// サウンドの停止
	SoundPlayer::GetInstance()->Stop(RESULT_BGM);
}