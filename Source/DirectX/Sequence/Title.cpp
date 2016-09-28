#include "Title.h"
#include "CharaSelect.h"
#include "SequenceChanger.h"
#include "..\Common\ParamLoader.h"
#include "..\Common\UniqueData.h"
#include "..\DirectX\SoundPlayer.h"

/**
* @brief 作成
*/
void Title::Create()
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// 1Pコントローラーのみ生成する
	m_dev.emplace_back(new InputMask(0));
}

/**
* @brief 初期化
*/
void Title::Initialize()
{	
	cursolY = 510.0f;
	// ゲームモードを初期化しておく
	UniqueData::GetInstance()->SetGameMode(GameMode::Default);
	titleWork = 0;
	m_subWork = 0;
	m_lightAlpha = ALPHA_MAX;
	m_lightAngle = 0.0f;
	m_alpha = ALPHA_MAX;
	m_isAlphaPlus = false;
	m_waitFrame = 0;

	// BGMの再生
	SoundPlayer::GetInstance()->LoopPlay(TITLE_BGM);
}

/**
* @brief 更新
*/
void Title::Update()
{
	// 光エフェクトの更新
	UpdateLight();

	switch (m_subWork)
	{
	case 0: // フェード終了まで待つ
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			m_subWork++;
		}
		break;

	case 1: // アルファ値変更
		m_alpha = 130;
		m_subWork++;
		break;

	case 2:
	{
		GameMode ret = TitleWork();

		if (ret == GameMode::Vs2P)
			m_subWork = 4;
		else if (ret == GameMode::VsCPU)
			m_subWork = 5;
		else if (ret == GameMode::Exit)
			m_subWork = 6;
		break;
	}

	case 4:
		// 対人モード
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// プレイヤー VS プレイヤー
			UniqueData::GetInstance()->SetGameMode(GameMode::Vs2P);
			UniqueData::GetInstance()->SetPlayerCount(2, 0);
			SequenceChanger::GetInstance()->ChangeScene(new CharaSelect());
		}
		break;

	case 5:
		// 対ＣＰＵモード
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// プレイヤー VS コンピューター
			UniqueData::GetInstance()->SetGameMode(GameMode::VsCPU);
			UniqueData::GetInstance()->SetPlayerCount(1, 1);
			SequenceChanger::GetInstance()->ChangeScene(new CharaSelect());
		}
		break;

	case 6: // フェード終了まで待つ
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// アプリケーション終了
			exit(1);
		}
		break;
	}

	// フレーム加算
	m_frame++;
}


/**
* @brief タイトル更新
*/
GameMode Title::TitleWork()
{
	// キー情報を取得
	m_dev[0]->GetInput();

	// 下移動
	if (m_dev[0]->CheckInputMask(INPUT_DOWN)){
		titleWork++;
	}
	// 上移動
	if (m_dev[0]->CheckInputMask(INPUT_UP)){
		titleWork--;
	}

	if (titleWork == 0)
	{
		cursolY = 410.0f;
	}
	else if (titleWork == 1)
	{
		cursolY = 510.0f;
	}
	else if (titleWork == 2)
	{
		cursolY = 610.0f;
	}


	if (titleWork < 0)
	{		
		titleWork = 0;
	}
	if (titleWork > 2)
	{
		titleWork = 2;
	}

	m_waitFrame++;

	// キーが入力されたら
	if (m_dev[0]->CheckInputMask(INPUT_01))
	{
		// フェードをかける
		ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);
		// 効果音の再生
		SoundPlayer::GetInstance()->Play(DECISION_SE);
		
		switch (titleWork)
		{
		case 0:
			return GameMode::Vs2P;

		case 1:
			return GameMode::VsCPU;

		case 2:
			return GameMode::Exit;
		}
	}

	return GameMode::Default;
}

void Title::UpdateLight()
{
	if (m_lightAlpha > ALPHA_MAX)
		m_isAlphaPlus = false;
	else if (m_lightAlpha < 0)
		m_isAlphaPlus = true;

	if (m_isAlphaPlus)
		m_lightAlpha += 10;
	else m_lightAlpha -= 10;

	m_lightAngle += 2.0f;
}

/**
* @brief 描画
*/
void Title::Render()
{
	// 背景
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_TITLE_BG), 640.0f, 360.0f, 0.0f, 1.0f, m_alpha);
	// ロゴ
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_TITLE_LOGO), 640.0f, 400.0f, 0.0f, 0.5f, m_alpha);

	// 光エフェクト
	if (m_subWork > 0){
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT), 300.0f, 370.0f, m_lightAngle, 0.5f, m_lightAlpha, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT), 800.0f, 370.0f, m_lightAngle + 30.0f, 0.5f, m_lightAlpha, true);
	}

	if (m_subWork == 2)
	{
		// メニューフォント
		m_2dTex->DrawTexture(m_texData->GetTitleMenuTexture(1), 640.0f, 400.0f, 0.0f, 1.0f, ALPHA_MAX, true);
		m_2dTex->DrawTexture(m_texData->GetTitleMenuTexture(2), 640.0f, 500.0f, 0.0f, 1.0f, ALPHA_MAX, true);
		m_2dTex->DrawTexture(m_texData->GetTitleMenuTexture(11), 640.0f, 600.0f, 0.0f, 1.0f, ALPHA_MAX, true);
		// カーソルアイコン
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_TITLE_ICON), 430.0f, cursolY);
	}
}

/**
* @brief 終了
*/
void Title::Finalize()
{
	// サウンドの停止
	SoundPlayer::GetInstance()->Stop(TITLE_BGM);
}