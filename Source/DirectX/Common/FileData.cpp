#include "FileData.h"
#include "..\DirectX\SoundPlayer.h"

/**
* @brief テクスチャデータの読み込み
*/
HRESULT TextureData::LoadTexture()
{
	// インスタンス取得
	m_2dTex = GraphicsManager::GetInstance();

	// タイトル
	tex[TEX_TITLE_BG] = m_2dTex->LoadTexture("Data/Graph/Scene/Title/titlebg.png");
	tex[TEX_TITLE_LOGO] = m_2dTex->LoadTexture("Data/Graph/Scene/Title/logo.png");
	tex[TEX_TITLE_ICON] = m_2dTex->LoadTexture("Data/Graph/Scene/Title/icon.png");

	// キャラクターセレクト
	tex[TEX_CHARASELECT_BG] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/charaselectBG.png");
	tex[TEX_CHARASELECT_BG2] = m_2dTex->LoadTexture("Data/Graph/a.png");
	tex[TEX_CHARASELECT_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/cs.png");
	tex[TEX_LILIA_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/liliafont.png");
	tex[TEX_RUNA_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/runafont.png");
	tex[TEX_LILIA_TEXT] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/liliatext.png");
	tex[TEX_RUNA_TEXT] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/runatext.png");
	tex[TEX_LILIA_ICON] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/iconlilia.png");
	tex[TEX_RUNA_ICON] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/iconruna.png");
	tex[TEX_CURSOL_1P] = m_2dTex->LoadTexture("Data/Graph/cursol.png");
	tex[TEX_CURSOL_2P] = m_2dTex->LoadTexture("Data/Graph/cursol2p.png");
	tex[TEX_DESCRIOTION_FRAME] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/desframe.png");
	tex[TEX_DESCRIOTION_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/CharaSelect/destext.png");
	// バトル開始前
	tex[TEX_VSPREPARATION_BG] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/cutinback03.jpg");
	tex[TEX_VSPREPARATION_BG2] = m_2dTex->LoadTexture("Data/Graph/Scene/VS/font.png");
	tex[TEX_PLAYER1_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Result/player1.png");
	tex[TEX_PLAYER2_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Result/player2.png");
	tex[TEX_VS_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Title/vs.png");
	// バトル中
	tex[TEX_BATTLE_BG] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/bgmain2.png");
	tex[TEX_BATTLE_BG_SPHERE] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/bgsphere.png");
	tex[TEX_BATTLE_BG_FLOOR] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/bgmainfloor.png");
	tex[TEX_BATTLE_BG_SPECIAL] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/bgspecial.png");
	tex[TEX_FROST] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/frost.png");
	tex[TEX_BER] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/ber.png");
	tex[TEX_STAND_BACK_G] = m_2dTex->LoadTexture("Data/Graph/stand_back00.png");
	tex[TEX_STAND_BACK_R] = m_2dTex->LoadTexture("Data/Graph/stand_back01.png");
	tex[TEX_STAND_BACK_P] = m_2dTex->LoadTexture("Data/Graph/stand_back02.png");
	tex[TEX_PUSH_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/push1.png");
	tex[TEX_PUSH_FONT2] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/push2.png");
	tex[TEX_HPFRAME] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/hpframe.png");
	tex[TEX_WINICON] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/win.png");
	tex[TEX_WINFLAG] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/winflag.png");
	tex[TEX_KO_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/KO.png");
	tex[TEX_HITS_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/hits.png");
	tex[TEX_ROUND1_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/round1.png");
	tex[TEX_ROUND2_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/round2.png");
	tex[TEX_FINALROUND_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/finalround.png");
	tex[TEX_FIGHT_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/fight.png");
	tex[TEX_SPECIAL_GAUGE_FRAME] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/spGaugeFrame.png");
	tex[TEX_SPECIAL_GAUGE_BER] = m_2dTex->LoadTexture("Data/Graph/Scene/Game/UI/specialgaugeBer.png");

	// リザルト
	tex[TEX_LOSE_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Result/lose.png");
	tex[TEX_CONTINUE_FONT] = m_2dTex->LoadTexture("Data/Graph/Scene/Result/continueFont.png");
	tex[TEX_CONTINUE_FRAME] = m_2dTex->LoadTexture("Data/Graph/Scene/Result/continueframe.png");
	tex[TEX_CONTINUE_CURSOL] = m_2dTex->LoadTexture("Data/Graph/Scene/Result/continuecursol.png");
	
	// リリア
	tex[TEX_LILIA_CUTIN_00] = m_2dTex->LoadTexture("Data/Graph/Girl1/normal.png");
	tex[TEX_LILIA_CUTIN_01] = m_2dTex->LoadTexture("Data/Graph/Girl1/CutIn06.png");
	tex[TEX_LILIA_STAND_00] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand00.png");
	tex[TEX_LILIA_STAND_01] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand01.png");
	tex[TEX_LILIA_STAND_02] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand02.png");
	tex[TEX_LILIA_STAND_03] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand03.png");
	tex[TEX_LILIA_STAND_04] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand04.png");
	tex[TEX_LILIA_STAND_05] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand05.png");
	tex[TEX_LILIA_STAND_06] = m_2dTex->LoadTexture("Data/Graph/Girl1/stand06.png");
	tex[TEX_LILIA_SPECIAL] = m_2dTex->LoadTexture("Data/Graph/Girl1/special.png");
	tex[TEX_LILIA_SPECIAL_SMALL] = m_2dTex->LoadTexture("Data/Graph/Girl1/specialsmall.png");

	// ルナ
	tex[TEX_RUNA_CUTIN_00] = m_2dTex->LoadTexture("Data/Graph/Girl2/CutIn00.png");
	tex[TEX_RUNA_CUTIN_01] = m_2dTex->LoadTexture("Data/Graph/Girl2/CutIn05.png");
	tex[TEX_RUNA_STAND_00] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand00.png");
	tex[TEX_RUNA_STAND_01] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand01.png");
	tex[TEX_RUNA_STAND_02] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand02.png");
	tex[TEX_RUNA_STAND_03] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand03.png");
	tex[TEX_RUNA_STAND_04] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand04.png");
	tex[TEX_RUNA_STAND_05] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand05.png");
	tex[TEX_RUNA_STAND_06] = m_2dTex->LoadTexture("Data/Graph/Girl2/stand06.png");
	tex[TEX_RUNA_SPECIAL] = m_2dTex->LoadTexture("Data/Graph/Girl2/CutIn06.png");
	tex[TEX_RUNA_SPECIAL_SMALL] = m_2dTex->LoadTexture("Data/Graph/Girl2/CutIn06-small.png");
	
	// 魔方陣
	tex[TEX_MAGICCIRCLE_G] = m_2dTex->LoadTexture("Data/Graph/Effect/magiccircle00.png");
	tex[TEX_MAGICCIRCLE_P] = m_2dTex->LoadTexture("Data/Graph/Effect/magiccircle01.png");
	tex[TEX_MAGIC_FONT_R] = m_2dTex->LoadTexture("Data/Graph/Effect/magiccircleR.png");
	tex[TEX_MAGIC_FONT_B] = m_2dTex->LoadTexture("Data/Graph/Effect/magiccircleB.png");

	// 火エフェクト
	tex[TEX_HINOKO] = m_2dTex->LoadTexture("Data/Graph/Effect/hinoko.png");
	// 斬撃エフェクト
	tex[TEX_SLASH] = m_2dTex->LoadTexture("Data/Graph/Effect/Slash.png");
	tex[TEX_SLASH2] = m_2dTex->LoadTexture("Data/Graph/Effect/Slash2.png");
	tex[TEX_SLASH3] = m_2dTex->LoadTexture("Data/Graph/Effect/Slash3.png");
	tex[TEX_SLASH4] = m_2dTex->LoadTexture("Data/Graph/Effect/0005.png");
	// 煙エフェクト
	tex[TEX_SMOKE] = m_2dTex->LoadTexture("Data/Graph/Effect/smoke02.png");
	// 輪エフェクト
	tex[TEX_RING] = m_2dTex->LoadTexture("Data/Graph/Effect/ring02.png");
	tex[TEX_RED_RING] = m_2dTex->LoadTexture("Data/Graph/Effect/redring.png");
	tex[TEX_BLUE_RING] = m_2dTex->LoadTexture("Data/Graph/Effect/001.png");
	tex[TEX_BURST_RING] = m_2dTex->LoadTexture("Data/Graph/Effect/burstRing1.bmp");
	// ブラー
	tex[TEX_BLUR] = m_2dTex->LoadTexture("Data/Graph/Effect/Blur.png");
	// ライン
	tex[TEX_LINE] = m_2dTex->LoadTexture("Data/Graph/Effect/line.png");
	// 光エフェクト
	tex[TEX_LIGHT] = m_2dTex->LoadTexture("Data/Graph/Scene/Title/light.png");
	tex[TEX_LIGHT2] = m_2dTex->LoadTexture("Data/Graph/Effect/0.png");
	tex[TEX_LIGHT3] = m_2dTex->LoadTexture("Data/Graph/Effect/003.png");
	tex[TEX_LIGHT4] = m_2dTex->LoadTexture("Data/Graph/Effect/light2.png");
	tex[TEX_RED_LIGHT] = m_2dTex->LoadTexture("Data/Graph/Effect/light03.png");
	tex[TEX_BLUE_LIGHT] = m_2dTex->LoadTexture("Data/Graph/Effect/light02.png");
	tex[TEX_FLUSH] = m_2dTex->LoadTexture("Data/Graph/Effect/flush.png");
	// 輝きエフェクト
	tex[TEX_SHINE] = m_2dTex->LoadTexture("Data/Graph/Effect/shine00.png");
	tex[TEX_SHINE2] = m_2dTex->LoadTexture("Data/Graph/Effect/shine01.png");
	tex[TEX_GUARD] = m_2dTex->LoadTexture("Data/Graph/Effect/guard2.png");
	// ヒットパーティクル
	tex[TEX_HIT_EFFECT] = m_2dTex->LoadTexture("Data/Graph/Effect/hiteffect.png");
	// ガードパーティクル
	tex[TEX_GUARD_EFFECT] = m_2dTex->LoadTexture("Data/Graph/Effect/guardeffect.png");
	// 火パーティクル用
	tex[TEX_FIRE_LIGHT] = m_2dTex->LoadTexture("Data/Graph/Effect/fire.png");
	// 星パーティクル用
	tex[TEX_STAR] = m_2dTex->LoadTexture("Data/Graph/Effect/star.png");
	// 泡エフェクト
	tex[TEX_FORM] = m_2dTex->LoadTexture("Data/Graph/Effect/002.png");
	// 相殺エフェクト
	tex[TEX_OFFSET] = m_2dTex->LoadTexture("Data/Graph/Effect/offset.png");

	d3dTex[TEX_SHAME_GAUGE] = m_2dTex->D3LoadTexture("Data/Graph/ShameGauge.png");
	d3dTex[TEX_SHAME_GAUGE_OLD] = m_2dTex->D3LoadTexture("Data/Graph/ShameGaugeHit.png");
	d3dTex[TEX_SPECIAL_GAUGE] = m_2dTex->D3LoadTexture("Data/Graph/Scene/Game/UI/specialgaugeBer.png");

	// リリアアニメーション
	m_2dTex->LoadBlkTexture("Data/Graph/Girl1/block1.png", 300, 300, 6, 5, LILIA_ANIM_MAX, liliaAnim);
	// ルナアニメーション
	m_2dTex->LoadBlkTexture("Data/Graph/Girl2/block1.png", 300, 300, 6, 4, RUNA_ANIM_MAX, runaAnim);
	// 魔方陣
	m_2dTex->LoadBlkTexture("Data/Graph/Scene/Game/magiccircle.png", 960, 960, 1, 2, MAGICCIRCLE_MAX, magicCircle);
	// 数字
	m_2dTex->LoadBlkTexture("Data/Graph/Scene/Game/UI/number.png", 64, 96, 10, 1, NUMBER_MAX, redNumberFont);
	m_2dTex->LoadBlkTexture("Data/Graph/Scene/Game/UI/number2.png", 64, 96, 10, 1, NUMBER_MAX, numberFont);
	// メニュー
	m_2dTex->LoadBlkTexture("Data/Graph/Scene/Title/font.png", 512, 96, 1, 12, TITLE_MENU_MAX, titleMenu);
	// 斬撃
	m_2dTex->LoadBlkTexture("Data/Graph/effect/0007.png", 256, 128, 4, 16, 64, slash);
	// 光
	m_2dTex->LoadBlkTexture("Data/Graph/Effect/light.png", 100, 100, 8, 1, 8, light);
	// 波
	m_2dTex->LoadBlkTexture("Data/Graph/Effect/wave00.png", 222, 111, 7, 2, 14, wave);

	// 成功
	return S_OK;
}

SoundData::SoundData()
{
	// インスタンスの取得
	SoundPlayer* m_sound = SoundPlayer::GetInstance();

	// 効果音-----------------------------------------
	
	m_sound->Load(DECISION_SE);
	m_sound->Load(CURSOL_SE);
	m_sound->Load(CUTIN_SE);
	m_sound->Load(FLAME_HIT_SE);
	m_sound->Load(BLADE_SE);
	m_sound->Load(FLAME_SE);
	m_sound->Load(FLAMECOLLIDE_SE);
	m_sound->Load(SWORDSWING_SE);
	m_sound->Load(SWORDBLOW_SE);
	m_sound->Load(EXTRASKILL_SE);
	m_sound->Load(BOMB_SE);
	m_sound->Load(DOWN_SE);
	m_sound->Load(SETUPMOTION_SE);
	m_sound->Load(OFFSET_SE);
	m_sound->Load(GUARD_SE);
	m_sound->Load(CHEER_SE);
	m_sound->Load(CHEER2_SE);
	m_sound->Load(LAUGH_SE);
	m_sound->Load(VSSWITCH_SE);
	m_sound->Load(VERSUS_SE);
	m_sound->Load(KO_SE);
	
	// -----------------------------------------------


	// 音楽-------------------------------------------
	
	m_sound->Load(TITLE_BGM);
	m_sound->Load(BATTLE_BGM);
	m_sound->Load(CHARACTERSELECT_BGM);
	m_sound->Load(RESULT_BGM);

	// -----------------------------------------------


	// 声--------------------------------------------
	// リリア
	m_sound->Load(LILIA_TITLE_VOICE);
	m_sound->Load(LILIA_CHARASELECT_VOICE);
	m_sound->Load(LILIA_CHARASELECTWAIT_VOICE);
	m_sound->Load(LILIA_BEFOREBATTLE_VOICE);
	m_sound->Load(LILIA_SQUATATTACK_VOICE);
	m_sound->Load(LILIA_DASHATTACK_VOICE);
	m_sound->Load(LILIA_JUMPATTACK_VOICE);
	m_sound->Load(LILIA_ATTACKWEAK_VOICE);
	m_sound->Load(LILIA_ATTACKWEAK_DER_VOICE);
	m_sound->Load(LILIA_ATTACKMEDIUM_VOICE);
	m_sound->Load(LILIA_ATTACKSTRONG_VOICE);
	m_sound->Load(LILIA_ATTACKSTRONG_VOICE2);
	m_sound->Load(LILIA_ATTACKSPECIAL_VOICE);
	m_sound->Load(LILIA_ATTACKSPECIAL_VOICE2);
	m_sound->Load(LILIA_ATTACKSPECIAL_VOICE3);
	m_sound->Load(LILIA_ATTACKSPECIAL_SUCCESS);
	m_sound->Load(LILIA_ATTACKSPECIAL_PUR_VOICE);
	m_sound->Load(LILIA_GUARDPRAISE_VOICE);
	m_sound->Load(LILIA_SCREAM_VOICE);
	m_sound->Load(LILIA_GASP_VOICE);
	m_sound->Load(LILIA_GASP_VOICE2);
	m_sound->Load(LILIA_WIN_VOICE);
	m_sound->Load(LILIA_LOSE_VOICE);
	m_sound->Load(LILIA_PASSIVE_VOICE);

	// ルナ
	m_sound->Load(RUNA_CHARASELECT_VOICE);
	m_sound->Load(RUNA_CHARASELECTWAIT_VOICE);
	m_sound->Load(RUNA_BEFOREBATTLE_VOICE);
	m_sound->Load(RUNA_SQUATATTACK_VOICE);
	m_sound->Load(RUNA_DASHATTACK_VOICE);
	m_sound->Load(RUNA_JUMPATTACK_VOICE);
	m_sound->Load(RUNA_ATTACKWEAK_VOICE);
	m_sound->Load(RUNA_ATTACKWEAK_DER_VOICE);
	m_sound->Load(RUNA_ATTACKMEDIUM_VOICE);
	m_sound->Load(RUNA_ATTACKSTRONG_VOICE);
	m_sound->Load(RUNA_ATTACKSTRONG_VOICE2);
	m_sound->Load(RUNA_ATTACKSPECIAL_VOICE);
	m_sound->Load(RUNA_ATTACKSPECIAL_VOICE2);
	m_sound->Load(RUNA_ATTACKSPECIAL_VOICE3);
	m_sound->Load(RUNA_ATTACKSPECIAL_SUCCESS);
	m_sound->Load(RUNA_ATTACKSPECIAL_PUR_VOICE);
	m_sound->Load(RUNA_GUARDPRAISE_VOICE);
	m_sound->Load(RUNA_SCREAM_VOICE);
	m_sound->Load(RUNA_GASP_VOICE);
	m_sound->Load(RUNA_GASP_VOICE2);
	m_sound->Load(RUNA_WIN_VOICE);
	m_sound->Load(RUNA_LOSE_VOICE);
	m_sound->Load(RUNA_PASSIVE_VOICE);

	// -----------------------------------------------
}

SoundData::~SoundData()
{

}