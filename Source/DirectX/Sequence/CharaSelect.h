/**
* @file   CharaSelect.h
* @brief  キャラクター選択処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___CHARASELECT_H
#define ___CHARASELECT_H

#include "ISequence.h"
#include "..\Common\StdAfx.h"
#include "..\Common\Struct.h"
#include "..\DirectX\InputMask.h"

/**
* @brief キャラクター選択画面
*/
class CharaSelect : public ISequence
{
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

	int FindEmptyArray();

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;
	
	/// 入力デバイス
	vector<InputRef> m_dev;

	/// 操作権限のあるコントローラー
	unsigned int controlJoy;

	/// 選択されたキャラクター
	int m_selectChara[JOY_MAX];

	/// サブワーク
	int subWork;

	/// フレーム
	int frame;

	/// カーソル番号
	int m_cursolNum;

	// キャラクター文字テクスチャ
	int charaFont[2];

	/// キャラクター説明文テクスチャ
	int charaText[2];

	/// 背景回転用
	float bgRot;

	/// キャラクターアニメーション
	int animation;

	/// アニメーション最大数
	int animMax;

	/// アニメーションフレーム
	int animFrame;
	int adjustAnimFrame;

	/**
	* @brief キャラクター選択の更新
	*/
	bool UpdateSelect();

	/**
	* @brief カーソルの移動の更新
	*/
	void CursolMove();

	/**
	* @brief キャラクターの動きの更新
	*/
	void CharaMove();

	/**
	* @brief キャラクタアニメーション
	*/
	void Animation();

	/**
	* @brief アニメーションを設定する
	*/
	void SetAnimation(const int aniMax, const int adjustAniFrame);

	/**
	* @brief 魔方陣作成
	*/
	void MagicalCreate();

	/**
	* @brief 魔方陣の移動
	*/
	void MagicalMove();
};

/**
* @brief キャラクターのアイコン構造体
*/
typedef struct
{
	float x, y;
	int kind;
	int tex;
}CHARAICON;

/**
* @brief 背景に描画するキャラクター構造体
*/
typedef struct
{
	float x, y;
	float vx;
	float initX;
	bool flag;	// 切り替えフラグ
	bool isSet;	// セットフラグ
	bool isDisp;// 表示フラグ
	int frame;
	int tex;
	int alpha;
}BACKCHARA;

/**
* @brief 選択時に描画するキャラクター構造体
*/
typedef struct
{
	float x, y;
	bool isDisp;	// 表示フラグ
	bool isFlash;	// 光らせるフラグ
	int girl1[3];
	int girl2[3];
	int alpha;
}SELECTCHARA;

/**
* @brief カーソル構造体
*/
typedef struct
{
	float x, y;
	int num;
	int tex;
	int frame;
	bool isSelect;
}CURSOL;

/**
* @brief 魔方陣構造体
*/
typedef struct
{
	Vector2 pos;
	float v;
	int tex[2];
	int kind;
	bool flag;	// 生存フラグ
}MAGICAL;

#endif