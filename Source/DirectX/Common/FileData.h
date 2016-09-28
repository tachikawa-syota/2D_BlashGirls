/**
* @file   FileData.h
* @brief  ファイルデータを管理する
* @author Syota Tachikawa
*/

#ifndef ___FILEDATA_H
#define ___FILEDATA_H

#include "StdAfx.h"

/// TextureDataのインスタンス取得
#define GetTextureData TextureData::GetInstance()
/// テクスチャの最大数
#define TEXTURE_MAX 270 
/// D3D型テクスチャの最大数
#define D3DTEXTURE_MAX 3
/// リリアアニメーション最大数
#define LILIA_ANIM_MAX 26
/// ルナアニメーション最大数
#define RUNA_ANIM_MAX 22
/// 巨大魔方陣テクスチャ最大数
#define MAGICCIRCLE_MAX 2
/// 数字テクスチャ最大数
#define NUMBER_MAX 10
/// タイトルメニューテクスチャ最大数
#define TITLE_MENU_MAX 12
/// 斬撃用テクスチャ最大数
#define SLASH_MAX 64
/// 光テクスチャ最大数
#define LIGHT_MAX 8
/// 波テクスチャ最大数
#define WAVE_MAX 14

/// テクスチャネーム
enum _TEXTURE_TYPE_{
	/// タイトル
	TEX_TITLE_BG,
	TEX_TITLE_LOGO,
	TEX_TITLE_ICON,

	/// キャラクター選択画面
	TEX_CHARASELECT_BG,
	TEX_CHARASELECT_BG2,
	TEX_CHARASELECT_FONT,
	TEX_LILIA_FONT,
	TEX_RUNA_FONT,
	TEX_LILIA_TEXT,
	TEX_RUNA_TEXT,
	TEX_LILIA_ICON,
	TEX_RUNA_ICON,
	TEX_CURSOL_1P,
	TEX_CURSOL_2P,
	TEX_DESCRIOTION_FRAME,
	TEX_DESCRIOTION_FONT,
	TEX_VSPREPARATION_BG,
	TEX_VSPREPARATION_BG2,
	TEX_PLAYER1_FONT,
	TEX_PLAYER2_FONT,
	TEX_VS_FONT,
	// バトル中
	TEX_BATTLE_BG,
	TEX_BATTLE_BG_SPHERE,
	TEX_BATTLE_BG_FLOOR,
	TEX_BATTLE_BG_SPECIAL,
	TEX_BER,
	TEX_STAND_BACK_G,
	TEX_STAND_BACK_R,
	TEX_STAND_BACK_P,
	TEX_PUSH_FONT,
	TEX_PUSH_FONT2,
	TEX_HPFRAME,
	TEX_WINICON,
	TEX_WINFLAG,
	TEX_KO_FONT,
	TEX_HITS_FONT,
	TEX_ROUND1_FONT,
	TEX_ROUND2_FONT,
	TEX_FINALROUND_FONT,
	TEX_FIGHT_FONT,
	TEX_SPECIAL_GAUGE_FRAME,
	TEX_SPECIAL_GAUGE_BER,

	// リザルト
	TEX_LOSE_FONT,
	TEX_CONTINUE_FONT,
	TEX_CONTINUE_FRAME,
	TEX_CONTINUE_CURSOL,
	// リリア
	TEX_LILIA_CUTIN_00,
	TEX_LILIA_CUTIN_01,
	TEX_LILIA_STAND_00,
	TEX_LILIA_STAND_01,
	TEX_LILIA_STAND_02,
	TEX_LILIA_STAND_03,
	TEX_LILIA_STAND_04,
	TEX_LILIA_STAND_05,
	TEX_LILIA_STAND_06,
	TEX_LILIA_SPECIAL,
	TEX_LILIA_SPECIAL_SMALL,
	// ルナ
	TEX_RUNA_CUTIN_00,
	TEX_RUNA_CUTIN_01,
	TEX_RUNA_STAND_00,
	TEX_RUNA_STAND_01,
	TEX_RUNA_STAND_02,
	TEX_RUNA_STAND_03,
	TEX_RUNA_STAND_04,
	TEX_RUNA_STAND_05,
	TEX_RUNA_STAND_06,
	TEX_RUNA_SPECIAL,
	TEX_RUNA_SPECIAL_SMALL,
	// 魔方陣
	TEX_MAGICCIRCLE_G,
	TEX_MAGICCIRCLE_P,
	TEX_MAGIC_FONT_R,
	TEX_MAGIC_FONT_B,
	// 火エフェクト
	TEX_HINOKO,
	// 斬撃エフェクト
	TEX_SLASH,
	TEX_SLASH2,
	TEX_SLASH3,
	TEX_SLASH4,
	// 煙エフェクト
	TEX_SMOKE,
	// 輪エフェクト
	TEX_RING,
	TEX_RED_RING,
	TEX_BLUE_RING,
	TEX_BURST_RING,
	// ブラー
	TEX_BLUR,
	// ライン
	TEX_LINE,
	// 光エフェクト
	TEX_LIGHT,
	TEX_LIGHT2,
	TEX_LIGHT3,
	TEX_LIGHT4,
	TEX_RED_LIGHT,
	TEX_BLUE_LIGHT,
	TEX_FLUSH,
	// 輝きエフェクト
	TEX_SHINE,
	TEX_SHINE2,
	// ガードエフェクト
	TEX_GUARD,
	// ヒットエフェクトパーティクル
	TEX_HIT_EFFECT,
	// ガードエフェクトパーティクル
	TEX_GUARD_EFFECT,
	// 火パーティクル用
	TEX_FIRE_LIGHT,
	// 星パーティクル用
	TEX_STAR,
	// 氷エフェクト
	TEX_FROST,
	// 泡エフェクト
	TEX_FORM,
	// 相殺エフェクト
	TEX_OFFSET,

	TEXTURE_TYPE_MAX,
};

enum _D3DTEXTURE_{
	TEX_SHAME_GAUGE,
	TEX_SHAME_GAUGE_OLD,
	TEX_SPECIAL_GAUGE,
};

// 前方宣言
class GraphicsManager;

/**
* @brief テクスチャデータを管理するクラス
*/
class TextureData
{
public:
	// コンストラクタ・デストラクタ
	TextureData(){};
	~TextureData(){};
	
	/**
	* @brief ゲットインスタンス
	*/
	static TextureData* GetInstance(){
		static TextureData singleton;
		return &singleton;
	}

	/**
	* @brief テクスチャデータの読み込み
	*/
	HRESULT LoadTexture();

	/**
	* @brief テクスチャデータの取得
	*/
	int GetTexture(int num) { return tex[num]; }
	
	/**
	* @brief D3D型テクスチャデータの取得
	*/
	LPDIRECT3DTEXTURE9 GetD3dTexture(int num) { return d3dTex[num]; }

	/// リリアアニメーションの取得
	int GetLiliaAnim(int num) { return liliaAnim[num]; }
	/// ルナアニメーションの取得
	int GetRunaAnim(int num) { return runaAnim[num]; }
	/// 魔方陣テクスチャの取得
	int GetMagicCircleTexture(int num) { return magicCircle[num]; }
	/// 赤色数字テクスチャの取得
	int GetRedNumberTexture(int num) { return redNumberFont[num]; }
	/// 数字テクスチャの取得
	int GetNumberTexture(int num) { return numberFont[num]; }
	/// タイトルメニューテクスチャの取得
	int GetTitleMenuTexture(int num) { return titleMenu[num]; }
	/// 斬撃テクスチャの取得
	int GetSlashTexture(int num) { return slash[num]; }
	/// 光テクスチャの取得
	int GetLightTexture(int num) { return light[num]; }
	/// 波テクスチャの取得
	int GetWaveTexture(int num) { return wave[num]; }

private:
	/// 基本テクスチャ
	int tex[TEXTURE_MAX];
	/// D3D型テクスチャ
	LPDIRECT3DTEXTURE9 d3dTex[D3DTEXTURE_MAX];

	/// リリアアニメーションテクスチャ
	int liliaAnim[LILIA_ANIM_MAX];

	/// ルナアニメーションテクスチャ
	int runaAnim[RUNA_ANIM_MAX];

	/// ブロック型魔方陣テクスチャ
	int magicCircle[MAGICCIRCLE_MAX];

	/// ブロック型赤色数字テクスチャ
	int redNumberFont[NUMBER_MAX];

	/// ブロック型数字テクスチャ
	int numberFont[NUMBER_MAX];

	/// ブロック型タイトルメニューテクスチャ
	int titleMenu[TITLE_MENU_MAX];
	
	/// ブロック型斬撃用テクスチャ
	int slash[SLASH_MAX];

	/// ブロック型光テクスチャ
	int light[LIGHT_MAX];

	/// ブロック型波テクスチャ
	int wave[WAVE_MAX];

	// グラフィックスマネージャ
	GraphicsManager* m_2dTex;
};


/**
* @brief サウンドデータを管理する
*/
class SoundData
{
public:
	/**
	* @brief コンストラクタ
	*/
	SoundData();
	/**
	* @brief デストラクタ
	*/
	~SoundData();
};

#endif