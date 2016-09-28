/**
* @file GraphicsLib.h
* @brief グラフィックに関する全般を管理する
* @author Syota Tachikawa
*/

#ifndef ___GRAPHICSLIB_H
#define ___GRAPHICSLIB_H

#include "..\Common\StdAfx.h"

/// 画像格納最大数
#define MAX_TEXTURE		270

/// グラフィックマネージャーのインスタンス取得
#define GetGraphicsManager GraphicsManager::GetInstance()

/**
* @brief テクスチャに必要な構造体
*/
typedef struct{
	LPDIRECT3DTEXTURE9		pDxTex;
	DWORD					nWidth;
	DWORD					nHeight;
	float					uv1[2], uv2[2];
	bool					used;
}TEXTURE;

typedef struct{
	float					x, y, z;
	float					rhw;
	DWORD					dwColor;
}COLOR_POINT;

/**
* @brief 2Dテクスチャ用構造体
*/
typedef struct{
	float					x, y, z;
	float					rhw;
	DWORD					uDiffuse;
	float					tu, tv;
}D2D_TEXTURE;

/**
* @brief 3Dテクスチャ用構造体
*/
typedef struct{
	float					x, y, z;
	DWORD					uDiffuse;
	float					tu, tv;
}D3D_TEXTURE;

/**
* @brief アルファ・赤・緑・青
*/
typedef struct{
	DWORD					alpha;
	DWORD					red;
	DWORD					green;
	DWORD					blue;
}ARGB;


/**
* @brief 2Dテクスチャを扱う
*/
class Graphics2DTexture
{
private:
	/// ブロック読み込み時に使用
	int numx, numy;

	/// デバイス	
	LPDIRECT3DDEVICE9	m_pDevice;
	
	/// テクスチャデータ
	TEXTURE m_tex[MAX_TEXTURE];

	/**
	* @brief 空き配列検索
	* @return 配列番号
	*/
	int FindEmptyArray();

public:
	/**
	* @brief コンストラクタ
	*/
	Graphics2DTexture();
	/**
	* @brief デストラクタ
	*/
	~Graphics2DTexture();

	int LoadTexture(const char* szFileName);
	LPDIRECT3DTEXTURE9 LoadTexture(char *szFileName);
	bool LoadBlkTexture(const char* szFileName, int sizeX, int sizeY, int numX, int numY, int num, int *data);
	HRESULT DrawTexture(int index, float posX, float posY, float angle = 0.0f, float scale = 1.0f, int alpha = 255, bool add = false, bool reverse = false);
	HRESULT DrawTextureEx(float x1, float y1, float x2, float y2, LPDIRECT3DBASETEXTURE9 pTex, float z = 0.0f, bool add = false);
	HRESULT Draw3DTex(int index, D3DXVECTOR3 pos, D3DXVECTOR3 angle, D3DXVECTOR3 scale, int alpha, D3DXMATRIX mBillboard, int billFlg);
	HRESULT DrawTexARGB(int index, float posX, float posY, ARGB argb, bool add = true, float angle = 0.0f, float scale = 1.0f, bool reverse = false);
	HRESULT DrawBox(float nMinX, float nMinY, float nMaxX, float nMaxY, DWORD color);
};

/**
* @brief グラフィック全体を管理する
*/
class GraphicsManager
{
private:
	/**
	* @brief コンストラクタ
	*/
	GraphicsManager(){
		m_p2Dtex = nullptr;
	};

	/// 2Dテクスチャ
	Graphics2DTexture* m_p2Dtex;

	/// デバイス
	LPDIRECT3DDEVICE9 m_device;

public:
	/**
	* @brief ゲットインスタンス
	*/
	static GraphicsManager* GetInstance(){
		static GraphicsManager singleton;
		return &singleton;
	}
	/**
	* @brief デストラクタ
	*/
	~GraphicsManager(){};

	/**
	* @brief 初期化
	*/
	HRESULT Initialize();

	/**
	* デバイス以外を解放(基本的にすべて解放してしまう)
	*/
	void ReleaseAll();

	/**
	* @brief テクスチャを中心に描画する
	* @param index - テクスチャデータ
	* @param posX - X座標の指定
	* @param posY - Y座標の指定
	* @param angle - 角度
	* @param scale - 大きさ
	* @param alpha - アルファ値
	* @param add - 加算合成の有無
	* @param reverse - 反転して描画するか
	*
	* @note 使い方："index"に"LoadTexture"で読み込んだデータを指定してください
	*				テクスチャを回転して描画したい場合は"angle"に角度を指定してください
	*				角度・大きさ・加算・反転に関してはデフォルトで引数を指定しています
	*/
	HRESULT DrawTexture(int index, float posX, float posY, float angle = 0.0f, float scale = 1.0f, int alpha = 255, bool add = false, bool reverse = false){
		return m_p2Dtex->DrawTexture(index, posX, posY, angle, scale, alpha, add, reverse);
	}

	/**
	* @brief テクスチャを中心に描画する
	* @param x1 - 左端X座標
	* @param y1 - 左端Y座標
	* @param x2 - 右端X座標
	* @param y2 - 右端Y座標
	* @param pTex - テクスチャデータ（D3DLoadTextureで読み込んだやつ）
	* @param z	- z軸
	* @param add - 加算合成の有無
	*
	* @note 使い方："pTex"に"D3DLoadTexture"で読み込んだデータを指定してください
	*/
	HRESULT DrawTextureEx(float x1, float y1, float x2, float y2, LPDIRECT3DBASETEXTURE9 pTex, float z = 0.0f, bool add = false){
		return m_p2Dtex->DrawTextureEx(x1, y1, x2, y2, pTex, z, add);
	}

	/**
	* @brief テクスチャをビルボードで描画する
	* @param index - テクスチャデータ
	* @param pos - 描画位置
	* @param angle - 角度
	* @param scale - 大きさ
	* @param alpha - アルファ値
	* @param mBillboard - ビルボード
	* @param billFlag - ビルボードするかどうか
	*/
	HRESULT Draw3DTexture(int index, D3DXVECTOR3 pos, D3DXVECTOR3 angle, D3DXVECTOR3 scale, int alpha, D3DXMATRIX mBillboard, int billFlg){
		return m_p2Dtex->Draw3DTex(index, pos, angle, scale, alpha, mBillboard, billFlg);
	}

	/**
	* @brief テクスチャを描画する（カラーの変更が可能）
	* @param index - テクスチャデータ
	* @param posX - X座標の指定
	* @param posY - Y座標の指定
	* @param argb - カラーデータの指定
	* @param add - 加算合成の有無
	* @param angle - 角度
	* @param scale - 大きさ
	* @param reverse - 反転して描画するか
	*/
	HRESULT DrawTexARGB(int index, float posX, float posY, ARGB argb, bool add = true, float angle = 0.0f, float scale = 1.0f, bool reverse = false){
		return m_p2Dtex->DrawTexARGB(index, posX, posY, argb, add, angle, scale, reverse);
	}

	/**
	* @brief 四角形を描画する
	*/
	HRESULT DrawBox(float nMinX, float nMinY, float nMaxX, float nMaxY, DWORD color){
		return m_p2Dtex->DrawBox(nMinX, nMinY, nMaxX, nMaxY, color);
	}

	/**
	* @brief テクスチャの読み込み
	* @param szFileName - テクスチャファイルの名前
	* @return テクスチャの番号
	*/
	int LoadTexture(const char* szFileName){
		return m_p2Dtex->LoadTexture(szFileName);
	}

	/**
	* @brief D3D型のテクスチャの読み込み
	*/
	LPDIRECT3DTEXTURE9 D3LoadTexture(char *szFileName){
		return m_p2Dtex->LoadTexture(szFileName);
	}

	/**
	* @brief ブロック型のテクスチャの読み込み
	* @param szFileName - テクスチャファイルの名前
	* @param sizeX - 分割した時の1枚分のテクスチャの横幅
	* @param sizeY - 分割した時の1枚分のテクスチャの縦幅
	* @param numX - 横に並べられているテクスチャの枚数
	* @param numY - 縦に並べられているテクスチャの枚数
	* @param numMax - テクスチャの総枚数
	* @param *data - 読み込んだテクスチャを格納する配列ポインタ
	* @return テクスチャの番号
	*
	* @note 使い方："sizeX,sizeY"に1枚分のテクスチャの幅を指定してください
	*				テクスチャのサイズが全て同じサイズのモノでないと読み込みが上手くいきません（バラバラでも読み込めるようにいずれ対応させたい）
	*				"numMax"は"numXに入れた値 * numYに入れた値"にしてください
	*				*dataの配列サイズとテクスチャの枚数が異なるとバグの要因になるのでご注意を
	*/
	int LoadBlkTexture(const char* szFileName, int sizeX, int sizeY, int numX, int numY, int numMax, int *data){
		return m_p2Dtex->LoadBlkTexture(szFileName, sizeX, sizeY, numX, numY, numMax, data);
	}
};

#endif