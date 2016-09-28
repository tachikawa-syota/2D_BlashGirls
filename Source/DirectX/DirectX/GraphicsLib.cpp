#include "GraphicsLib.h"

/**
* 2D画像クラス
* @brief テクスチャを扱う
*/
Graphics2DTexture::Graphics2DTexture()
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		m_tex[i].used = false;
	}
}

/**
* @brief デストラクタ
*/
Graphics2DTexture::~Graphics2DTexture()
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (m_tex[i].used){
			m_tex[i].pDxTex->Release();
		}
	}
}

/**
* @brief 空き配列検索
* @return 配列番号
*/
int Graphics2DTexture::FindEmptyArray()
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (!m_tex[i].used){
			return i;
		}
	}
	return -1;
}

/**
* @brief テクスチャの読み込み
*/
int Graphics2DTexture::LoadTexture(const char* szFileName)
{
	// 未使用の要素を検索
	int idx = FindEmptyArray();
	// 空き配列がない
	if (idx == -1) return -1;

	D3DXIMAGE_INFO iiImageInfo;
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(D3DIns->GetDevice(), szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff00ff00, &iiImageInfo, NULL, &m_tex[idx].pDxTex)))
	{
		MessageBox(0, szFileName, "テクスチャ読み込み失敗", MB_OK);
		return -1;
	}

	m_tex[idx].nWidth = iiImageInfo.Width;
	m_tex[idx].nHeight = iiImageInfo.Height;

	DWORD x = 1;
	while ((x = x * 2) < m_tex[idx].nWidth);
	m_tex[idx].uv1[0] = 0;
	m_tex[idx].uv1[1] = (float)m_tex[idx].nWidth / (float)x;
	DWORD y = 1;
	while ((y = y * 2) < m_tex[idx].nHeight);
	m_tex[idx].uv2[0] = 0;
	m_tex[idx].uv2[1] = (float)m_tex[idx].nHeight / (float)y;


	m_tex[idx].used = true;

	return idx;
}

/**
* @brief テクスチャの読み込み
* @param szFileName	- 読み込む画像ファイル
*/
LPDIRECT3DTEXTURE9 Graphics2DTexture::LoadTexture(char *szFileName)
{
	HRESULT hr;

	// 初期化しておく
	LPDIRECT3DTEXTURE9 pTex = nullptr;
	D3DXIMAGE_INFO iiImageInfo;

	// テクスチャをファイルから作成
	hr = D3DXCreateTextureFromFileEx(D3DIns->GetDevice(), szFileName, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &iiImageInfo, NULL, &pTex);

	if (FAILED(hr)){
		MessageBox(NULL, szFileName, "テクスチャ読み込み失敗", MB_OK);
		return NULL;
	}
	return pTex;
}

/**
* @brief テクスチャの読み込み
* @param szFileName     ：    読み込むファイル名
* @param sizeX          ：    分割計算したテクスチャの横幅
* @param sizeY          ：    分割計算したテクスチャの縦幅
* @param numX           ：    分割計算したテクスチャの横に並べられた数
* @param numY           ：    分割計算したテクスチャの縦に並べられた数
* @param numMax         ：    分割計算したテクスチャの最大数
* @param *data          ：    バッファ
*/
bool Graphics2DTexture::LoadBlkTexture(const char* szFileName, int sizeX, int sizeY, int numX, int numY, int numMax, int *data)
{
	// テクスチャ要素数のデータ確保
	numx = numX;
	numy = numY;

	// 未使用の要素を検索
	int i;
	for (i = 0; i < numMax; ++i){
		data[i] = FindEmptyArray();
		if (data[i] == -1) break;
		m_tex[data[i]].used = true;
	}
	if (i != numMax){
		for (int j = 0; j<i; ++j){ m_tex[data[j]].used = false; }
		return false;
	}
	D3DXIMAGE_INFO iiImageInfo;
	// 読み込み
	TEXTURE bufTex;
	if (FAILED(D3DXCreateTextureFromFileEx(D3DIns->GetDevice(), szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff00ff00, &iiImageInfo, NULL, &bufTex.pDxTex))){
		MessageBox(0, szFileName, "テクスチャ読み込み失敗", MB_OK);
		return false;
	}
	// テクスチャサイズ取得
	bufTex.nWidth = iiImageInfo.Width;
	bufTex.nHeight = iiImageInfo.Height;
	// テクスチャ補正
	DWORD x = 1;
	while ((x = x * 2) < bufTex.nWidth);
	bufTex.uv1[0] = 0;
	bufTex.uv1[1] = (float)bufTex.nWidth / (float)x;
	DWORD y = 1;
	while ((y = y * 2) < bufTex.nHeight);
	bufTex.uv2[0] = 0;
	bufTex.uv2[1] = (float)bufTex.nHeight / (float)y;

	float addx = ((float)sizeX / bufTex.nWidth) * bufTex.uv1[1];
	float addy = ((float)sizeY / bufTex.nHeight) * bufTex.uv2[1];

	for (int y = 0; y < numY; ++y)
	{
		for (int x = 0; x < numX; ++x)
		{
			// 分割番号を順に取得
			int j = y * numX + x;
			// 分割テクスチャ最大数に達するとBreak
			if (j >= numMax) break;
			// データを代入
			m_tex[data[j]].pDxTex = bufTex.pDxTex;
			m_tex[data[j]].nWidth = bufTex.nWidth / numX;
			m_tex[data[j]].nHeight = bufTex.nHeight / numY;

			m_tex[data[j]].uv1[0] = x*addx;
			m_tex[data[j]].uv1[1] = (x + 1)*addx;
			m_tex[data[j]].uv2[0] = y*addy;
			m_tex[data[j]].uv2[1] = (y + 1)*addy;
		}
	}
	return true;
}

/**
* @brief 2Dテクスチャの描画（中心に）
* @param index テクスチャの配列番号
* @param posX 描画位置
* @param posY 描画位置
* @param angle 角度
* @param scale 拡大率
* @param add 加算
* @param reverse 反転
*/
HRESULT Graphics2DTexture::DrawTexture(int index, float posX, float posY, float angle, float scale, int alpha, bool add, bool reverse)
{
	if (!m_tex[index].used){
		return E_FAIL;
	}
	if (alpha < ALPHA_MIN)
		alpha = ALPHA_MIN;
	else if (alpha > ALPHA_MAX)
		alpha = ALPHA_MAX;

	float x = m_tex[index].nWidth * 0.5f * scale;
	float y = m_tex[index].nHeight * 0.5f * scale;

	DWORD vColor = D3DCOLOR_ARGB(alpha, alpha, alpha, alpha);


	float uv10, uv11;
	if (reverse){
		uv10 = m_tex[index].uv1[1];
		uv11 = m_tex[index].uv1[0];
	}
	else {
		uv10 = m_tex[index].uv1[0];
		uv11 = m_tex[index].uv1[1];
	}
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, uv10, m_tex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, uv11, m_tex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, uv10, m_tex[index].uv2[1] }
		, { x, y, 0, 1, vColor, uv11, m_tex[index].uv2[1] }
	};
	float RotX = sinf(angle * D3DX_PI / 180.0f);
	float RotY = cosf(angle * D3DX_PI / 180.0f);
	for (int i = 0; i<4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = (fX*RotY) - (fY*RotX) + posX;
		pv->y = (fX*RotX) + (fY*RotY) + posY;
	}

	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	D3DIns->GetDevice()->SetTexture(0, m_tex[index].pDxTex);

	if (!add){
		D3DIns->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		D3DIns->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DIns->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else{
		D3DIns->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);
		D3DIns->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DIns->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		D3DIns->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);
	}

	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

	return S_OK;
}

//射影変換済みとして扱われる頂点情報
typedef struct _CUSTOM_VERTEX_TEXTURE{
	D3DXVECTOR3 pos;                //位置
	float                rhw;                //1.0fを入れる        除算数？
	float                u, v;                //uv座標
}CUSTOM_VERTEX_TEXTURE;

/**
* @brief 2Dテクスチャの描画（(拡大縮小可能)
* @param x1 左上
* @param y1 左上
* @param x2 右下
* @param y2 右下
* @param pTex テクスチャ
*/
HRESULT Graphics2DTexture::DrawTextureEx(float x1, float y1, float x2, float y2, LPDIRECT3DBASETEXTURE9 pTex, float z, bool add)
{
	float tmp;
	if (x1 > x2){
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	if (y1 > y2){
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	D3DXVECTOR3 vPnt[4];

	//右上
	vPnt[0].x = x2;
	vPnt[0].y = y1;
	vPnt[0].z = z;

	//右下
	vPnt[1] = vPnt[0];
	vPnt[1].y = y2;

	//左上
	vPnt[2] = vPnt[0];
	vPnt[2].x = x1;

	//左下
	vPnt[3] = vPnt[1];
	vPnt[3].x = x1;

	CUSTOM_VERTEX_TEXTURE vertex[4];        //頂点

	for (int i = 0; i < 4; i++){
		vertex[i].pos = vPnt[i];                //座標コピー
		vertex[i].rhw = 1.0f;                   //射影変換済みとする
	}

	//右上
	vertex[0].u = 1.0f;
	vertex[0].v = 0.0f;

	//右下
	vertex[1].u = 1.0f;
	vertex[1].v = 1.0f;

	//左上
	vertex[2].u = 0.0f;
	vertex[2].v = 0.0f;

	//左下
	vertex[3].u = 0.0f;
	vertex[3].v = 1.0f;
	
	if (!add){
		D3DIns->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		D3DIns->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DIns->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else{
		D3DIns->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);
		D3DIns->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DIns->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		D3DIns->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);
	}

	//レンダリング
	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	//テクスチャ設定
	D3DIns->GetDevice()->SetTexture(0, pTex);
	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(CUSTOM_VERTEX_TEXTURE));

	// 成功
	return S_OK;
}


/**
* 2Dテクスチャを3D描画
*
* @param index	テクスチャの配列番号
* @param Pos	座標
* @param Angle	角度
* @param Scale	拡大率
* @param mBillboard ビルボード
* @param BillFlg ビルボードするかどうか
*/
HRESULT Graphics2DTexture::Draw3DTex(int index, D3DXVECTOR3 pos, D3DXVECTOR3 angle, D3DXVECTOR3 scale, int alpha, D3DXMATRIX mBillboard, int billFlg)
{
	if (!m_tex[index].used){
		return E_FAIL;
	}

	float x = m_tex[index].nWidth / 100.0f;
	float y = m_tex[index].nHeight / 100.0f;

	DWORD vColor = D3DCOLOR_ARGB(alpha, alpha, alpha, alpha);
	D3D_TEXTURE vPoint[4] = {
		{ -x, y, 0, vColor, m_tex[index].uv1[0], m_tex[index].uv2[0] }
		, { x, y, 0, vColor, m_tex[index].uv1[1], m_tex[index].uv2[0] }
		, { -x, -y, 0, vColor, m_tex[index].uv1[0], m_tex[index].uv2[1] }
		, { x, -y, 0, vColor, m_tex[index].uv1[1], m_tex[index].uv2[1] }
	};


	//宣言
	D3DXMATRIX mWorld, mRotation, mPosition, mScale;

	//計算
	D3DXMatrixTranslation(&mPosition, pos.x, pos.y, pos.z);
	float RadX = D3DX_PI * angle.x / 180.0f;
	float RadY = D3DX_PI * angle.y / 180.0f;
	float RadZ = D3DX_PI * angle.z / 180.0f;
	D3DXMatrixRotationYawPitchRoll(&mRotation, RadY, RadX, RadZ);
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	mWorld = mScale * mRotation * mPosition;
	if (billFlg == 1){
		mWorld = mScale * mRotation * mBillboard * mPosition;
	}
	else
		if (billFlg == 2){
			mWorld = mScale * mRotation * mPosition * mBillboard;
		}

	D3DIns->GetDevice()->SetTransform(D3DTS_WORLD, &mWorld);

	//描画
	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	D3DIns->GetDevice()->SetTexture(0, m_tex[index].pDxTex);
	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D3D_TEXTURE));

	// 成功
	return S_OK;
}


/**
* @brief 2Dテクスチャの描画（カラーを弄れる）
* @param index テクスチャの配列番号
* @param posX 描画位置
* @param posY 描画位置
* @param argb カラー
* @param add 加算
* @param angle 角度
* @param scale 拡大率
* @param reverse 反転
*/
HRESULT Graphics2DTexture::DrawTexARGB(int index, float posX, float posY, ARGB argb, bool add, float angle, float scale, bool reverse)
{
	if (!m_tex[index].used){
		return E_FAIL;
	}
	if (argb.alpha < 0)
		argb.alpha = 0;
	else if (argb.alpha > 255)
		argb.alpha = 255;

	float x = m_tex[index].nWidth * 0.5f * scale;
	float y = m_tex[index].nHeight * 0.5f * scale;

	DWORD vColor = D3DCOLOR_ARGB(argb.alpha, argb.red, argb.green, argb.blue);

	float uv10, uv11;
	if (reverse){
		uv10 = m_tex[index].uv1[1];
		uv11 = m_tex[index].uv1[0];
	}
	else {
		uv10 = m_tex[index].uv1[0];
		uv11 = m_tex[index].uv1[1];
	}
	D2D_TEXTURE vPoint[] = {
		{ -x, -y, 0, 1, vColor, uv10, m_tex[index].uv2[0] }
		, { x, -y, 0, 1, vColor, uv11, m_tex[index].uv2[0] }
		, { -x, y, 0, 1, vColor, uv10, m_tex[index].uv2[1] }
		, { x, y, 0, 1, vColor, uv11, m_tex[index].uv2[1] }
	};
	float RotX = sinf(angle * D3DX_PI / 180.0f);
	float RotY = cosf(angle * D3DX_PI / 180.0f);
	for (int i = 0; i<4; i++){
		D2D_TEXTURE *pv = &vPoint[i];
		float fX = pv->x;
		float fY = pv->y;
		pv->x = (fX*RotY) - (fY*RotX) + posX;
		pv->y = (fX*RotX) + (fY*RotY) + posY;
	}

	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	D3DIns->GetDevice()->SetTexture(0, m_tex[index].pDxTex);

	if (!add){
		D3DIns->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		D3DIns->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DIns->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else{
		D3DIns->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, true);
		D3DIns->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		D3DIns->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		D3DIns->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, false);
	}

	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D2D_TEXTURE));

	// 成功
	return S_OK;
}

/**
* 四角形の描画(スクリーン座標)
*
* @param nMinX	四角形左上X座標
* @param nMinY	四角形左上Y座標
* @param nMaxX	四角形右下X座標
* @param nMaxY	四角形右下Y座標
* @param color	色
*/
HRESULT Graphics2DTexture::DrawBox(float nMinX, float nMinY, float nMaxX, float nMaxY, DWORD color)
{
	COLOR_POINT vPoint[] = {
		{ nMinX, nMinY, 0.0f, 1.0f, color }
		, { nMaxX, nMinY, 0.0f, 1.0f, color }
		, { nMinX, nMaxY, 0.0f, 1.0f, color }
		, { nMaxX, nMaxY, 0.0f, 1.0f, color }
	};

	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	D3DIns->GetDevice()->SetTexture(0, NULL);
	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(COLOR_POINT));

	// 成功
	return S_OK;
}

/**
* @brief 初期化
*/
HRESULT GraphicsManager::Initialize()
{
	// インスタンス取得
	m_p2Dtex = new Graphics2DTexture();

	// 成功
	return S_OK;
}