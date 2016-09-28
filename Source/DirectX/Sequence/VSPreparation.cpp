// ----------------------------------------------------------------
//
//	バトル開始前の演出画面
//
// ----------------------------------------------------------------

#include "VSPreparation.h"
#include "GameMain.h"
#include "SequenceChanger.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\UniqueData.h"

/**
* @brief 作成
*/
void VSPreparation::Create()
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// 選択キャラクターの情報を取得
	const int* select = UniqueData::GetInstance()->GetSelectCharacter();

	for (int i = 0; i < JOY_MAX; i++)
	{
		switch (select[i])
		{
		case LILIA:
			m_obj[i].handle = m_texData->GetTexture(TEX_LILIA_CUTIN_00);
			m_nameObj[i].handle = m_texData->GetTexture(TEX_LILIA_FONT);
			break;

		case RUNA:
			m_obj[i].handle = m_texData->GetTexture(TEX_RUNA_CUTIN_00);
			m_nameObj[i].handle = m_texData->GetTexture(TEX_RUNA_FONT);
			break;
		}
	}
}

/**
* @brief 初期化
*/
void VSPreparation::Initialize()
{
	vsScale_ = 0.0f;
	
	m_obj[PLAYER1].pos.x = -600.0f;
	m_obj[PLAYER2].pos.x = 1880.0f;
	m_plFontObj[PLAYER1].pos.x = -300.0f;
	m_plFontObj[PLAYER2].pos.x = 1580.0f;
	m_nameObj[PLAYER1].pos.x = -300.0f;
	m_nameObj[PLAYER2].pos.x = 1580.0f;
	m_nameObj[PLAYER1].rot = -20.0f;
	m_nameObj[PLAYER2].rot = 20.0f;

	for (int i = 0; i < JOY_MAX; i++){
		m_obj[i].scale = 1.4f;
		m_v[i] = 0.0f;
		
		m_plFontObj[i].pos.y = 650.0f;
		m_plFontvx[i] = 0.0f;

		m_nameObj[i].pos.y = 700.0f;
		m_namevx[i] = 0.0f;
		m_namevy[i] = 0.0f;
	}
	m_alpha = ALPHA_MIN;

	fontY = 760.0f;

	m_frame = 0;
	m_subWork = 0;
}

/**
* @brief 更新
*/
void VSPreparation::Update()
{
	switch (m_subWork)
	{
	case 0: // 1Pを右に動かす
		m_v[PLAYER1] = 30.0f;
		SoundPlayer::GetInstance()->Play(CHEER2_SE);
		m_subWork++;

		break;

	case 1: 
		if (m_frame >= 100)
		{
			SoundPlayer::GetInstance()->Play(CHEER2_SE);
			m_v[PLAYER1] = 0.0f;
			m_obj[PLAYER1].pos = -600.0f;
			m_frame = 0;
			m_subWork++;
		}
		break;

	case 2: // 2Pを左に動かす
		m_v[PLAYER2] = -30.0f;

		if (m_frame >= 100)
		{
			m_v[PLAYER1] = -10.0f;
			m_obj[PLAYER1].pos.x = 600.0f;

			m_v[PLAYER2] = 10.0f;
			m_obj[PLAYER2].pos.x = 680.0f;

			m_obj[PLAYER1].scale = 0.9f;
			m_obj[PLAYER2].scale = 0.9f;

			m_plFontvx[PLAYER1] = 14.0f;
			m_plFontvx[PLAYER2] = -14.0f;

			m_namevx[PLAYER1] = 17.0f;
			m_namevx[PLAYER2] = -17.0f;

			m_namevy[PLAYER1] = -7.0f;
			m_namevy[PLAYER2] = -7.0f;

			m_subWork++;
		}
		break;

	case 3: // 中央から左右に動かす
		m_alpha += 7;
		if (m_alpha >= 200)
		{
			for (int i = 0; i < JOY_MAX; i++){
				m_namevx[i] = m_namevx[i] * 0.65f;
				m_namevy[i] = m_namevy[i] * 0.65f;
			}
		}

		if (m_alpha > ALPHA_MAX)
		{
			for (int i = 0; i < JOY_MAX; i++){
				m_v[i] = 0.0f;
				m_plFontvx[i] = 0.0f;
				m_namevx[i] = 0.0f;
				m_namevy[i] = 0.0f;
			}

			vsScale_ = 4.0f;
			SoundPlayer::GetInstance()->Play(VERSUS_SE);
			m_frame = 0;
			m_subWork++;
		}
		break;

	case 4:
		vsScale_ -= 0.06f;
		if (vsScale_ <= 0.8f){
			SoundPlayer::GetInstance()->Play(VSSWITCH_SE);
			m_frame = 0;
			m_subWork++;
		}
		break;

	case 5:
		if (m_frame >= 240)
		{
			// フェードの設定
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);
			m_subWork++;
		}
		break;

	case 6:
		// フェード終了待ち
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			// メインゲームに切り替える
			SequenceChanger::GetInstance()->ChangeScene(new GameMain());
			m_subWork = 0;
		}
		break;
	
	}

	// 背景フォントの更新
	UpdateBackgroundFont();

	for (int i = 0; i < JOY_MAX; i++){
		m_obj[i].pos.x += m_v[i];
		m_plFontObj[i].pos.x += m_plFontvx[i];
		m_nameObj[i].pos.x += m_namevx[i];
		m_nameObj[i].pos.y += m_namevy[i];
	}

	// フレーム更新
	m_frame++;
}

/**
* @brief 描画
*/
void VSPreparation::Render()
{
	// 選択されたキャラクターデータを取得する
	const int* select = UniqueData::GetInstance()->GetSelectCharacter();

	// 背景
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VSPREPARATION_BG), 640, 360);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VSPREPARATION_BG2), 640, fontY);
	
	// キャラ表示
	for (int i = 0; i < JOY_MAX; i++){
		m_2dTex->DrawTexture(m_obj[select[i]].handle, m_obj[i].pos.x, 600.0f, 0.0f, m_obj[i].scale, m_alpha);
		m_2dTex->DrawTexture(m_nameObj[select[i]].handle, m_nameObj[i].pos.x, m_nameObj[i].pos.y, m_nameObj[i].rot);

		if (i == PLAYER1){
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PLAYER1_FONT), m_plFontObj[i].pos.x, m_plFontObj[i].pos.y, 0.0f, 0.3f);
		}
		else{
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PLAYER2_FONT), m_plFontObj[i].pos.x, m_plFontObj[i].pos.y, 0.0f, 0.3f);
		}
	}

	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VS_FONT), 640, 360, 0.0f, vsScale_);
}

/**
* @brief 背景文字の更新
*/
void VSPreparation::UpdateBackgroundFont()
{
	fontY -= 1.7f;
	if (fontY <= -400.0f){
		fontY = 760.0f;
	}
}


/**
* @brief 終了
*/
void VSPreparation::Finalize()
{
	// 何もしない
}
