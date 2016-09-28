#include "GraphicsLib.h"

/**
* 2D�摜�N���X
* @brief �e�N�X�`��������
*/
Graphics2DTexture::Graphics2DTexture()
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		m_tex[i].used = false;
	}
}

/**
* @brief �f�X�g���N�^
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
* @brief �󂫔z�񌟍�
* @return �z��ԍ�
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
* @brief �e�N�X�`���̓ǂݍ���
*/
int Graphics2DTexture::LoadTexture(const char* szFileName)
{
	// ���g�p�̗v�f������
	int idx = FindEmptyArray();
	// �󂫔z�񂪂Ȃ�
	if (idx == -1) return -1;

	D3DXIMAGE_INFO iiImageInfo;
	//�u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
	if (FAILED(D3DXCreateTextureFromFileEx(D3DIns->GetDevice(), szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff00ff00, &iiImageInfo, NULL, &m_tex[idx].pDxTex)))
	{
		MessageBox(0, szFileName, "�e�N�X�`���ǂݍ��ݎ��s", MB_OK);
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
* @brief �e�N�X�`���̓ǂݍ���
* @param szFileName	- �ǂݍ��މ摜�t�@�C��
*/
LPDIRECT3DTEXTURE9 Graphics2DTexture::LoadTexture(char *szFileName)
{
	HRESULT hr;

	// ���������Ă���
	LPDIRECT3DTEXTURE9 pTex = nullptr;
	D3DXIMAGE_INFO iiImageInfo;

	// �e�N�X�`�����t�@�C������쐬
	hr = D3DXCreateTextureFromFileEx(D3DIns->GetDevice(), szFileName, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0, &iiImageInfo, NULL, &pTex);

	if (FAILED(hr)){
		MessageBox(NULL, szFileName, "�e�N�X�`���ǂݍ��ݎ��s", MB_OK);
		return NULL;
	}
	return pTex;
}

/**
* @brief �e�N�X�`���̓ǂݍ���
* @param szFileName     �F    �ǂݍ��ރt�@�C����
* @param sizeX          �F    �����v�Z�����e�N�X�`���̉���
* @param sizeY          �F    �����v�Z�����e�N�X�`���̏c��
* @param numX           �F    �����v�Z�����e�N�X�`���̉��ɕ��ׂ�ꂽ��
* @param numY           �F    �����v�Z�����e�N�X�`���̏c�ɕ��ׂ�ꂽ��
* @param numMax         �F    �����v�Z�����e�N�X�`���̍ő吔
* @param *data          �F    �o�b�t�@
*/
bool Graphics2DTexture::LoadBlkTexture(const char* szFileName, int sizeX, int sizeY, int numX, int numY, int numMax, int *data)
{
	// �e�N�X�`���v�f���̃f�[�^�m��
	numx = numX;
	numy = numY;

	// ���g�p�̗v�f������
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
	// �ǂݍ���
	TEXTURE bufTex;
	if (FAILED(D3DXCreateTextureFromFileEx(D3DIns->GetDevice(), szFileName, D3DX_DEFAULT, D3DX_DEFAULT, 1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff00ff00, &iiImageInfo, NULL, &bufTex.pDxTex))){
		MessageBox(0, szFileName, "�e�N�X�`���ǂݍ��ݎ��s", MB_OK);
		return false;
	}
	// �e�N�X�`���T�C�Y�擾
	bufTex.nWidth = iiImageInfo.Width;
	bufTex.nHeight = iiImageInfo.Height;
	// �e�N�X�`���␳
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
			// �����ԍ������Ɏ擾
			int j = y * numX + x;
			// �����e�N�X�`���ő吔�ɒB�����Break
			if (j >= numMax) break;
			// �f�[�^����
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
* @brief 2D�e�N�X�`���̕`��i���S�Ɂj
* @param index �e�N�X�`���̔z��ԍ�
* @param posX �`��ʒu
* @param posY �`��ʒu
* @param angle �p�x
* @param scale �g�嗦
* @param add ���Z
* @param reverse ���]
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

//�ˉe�ϊ��ς݂Ƃ��Ĉ����钸�_���
typedef struct _CUSTOM_VERTEX_TEXTURE{
	D3DXVECTOR3 pos;                //�ʒu
	float                rhw;                //1.0f������        ���Z���H
	float                u, v;                //uv���W
}CUSTOM_VERTEX_TEXTURE;

/**
* @brief 2D�e�N�X�`���̕`��i(�g��k���\)
* @param x1 ����
* @param y1 ����
* @param x2 �E��
* @param y2 �E��
* @param pTex �e�N�X�`��
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

	//�E��
	vPnt[0].x = x2;
	vPnt[0].y = y1;
	vPnt[0].z = z;

	//�E��
	vPnt[1] = vPnt[0];
	vPnt[1].y = y2;

	//����
	vPnt[2] = vPnt[0];
	vPnt[2].x = x1;

	//����
	vPnt[3] = vPnt[1];
	vPnt[3].x = x1;

	CUSTOM_VERTEX_TEXTURE vertex[4];        //���_

	for (int i = 0; i < 4; i++){
		vertex[i].pos = vPnt[i];                //���W�R�s�[
		vertex[i].rhw = 1.0f;                   //�ˉe�ϊ��ς݂Ƃ���
	}

	//�E��
	vertex[0].u = 1.0f;
	vertex[0].v = 0.0f;

	//�E��
	vertex[1].u = 1.0f;
	vertex[1].v = 1.0f;

	//����
	vertex[2].u = 0.0f;
	vertex[2].v = 0.0f;

	//����
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

	//�����_�����O
	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	//�e�N�X�`���ݒ�
	D3DIns->GetDevice()->SetTexture(0, pTex);
	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(CUSTOM_VERTEX_TEXTURE));

	// ����
	return S_OK;
}


/**
* 2D�e�N�X�`����3D�`��
*
* @param index	�e�N�X�`���̔z��ԍ�
* @param Pos	���W
* @param Angle	�p�x
* @param Scale	�g�嗦
* @param mBillboard �r���{�[�h
* @param BillFlg �r���{�[�h���邩�ǂ���
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


	//�錾
	D3DXMATRIX mWorld, mRotation, mPosition, mScale;

	//�v�Z
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

	//�`��
	D3DIns->GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	D3DIns->GetDevice()->SetTexture(0, m_tex[index].pDxTex);
	D3DIns->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vPoint, sizeof(D3D_TEXTURE));

	// ����
	return S_OK;
}


/**
* @brief 2D�e�N�X�`���̕`��i�J���[��M���j
* @param index �e�N�X�`���̔z��ԍ�
* @param posX �`��ʒu
* @param posY �`��ʒu
* @param argb �J���[
* @param add ���Z
* @param angle �p�x
* @param scale �g�嗦
* @param reverse ���]
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

	// ����
	return S_OK;
}

/**
* �l�p�`�̕`��(�X�N���[�����W)
*
* @param nMinX	�l�p�`����X���W
* @param nMinY	�l�p�`����Y���W
* @param nMaxX	�l�p�`�E��X���W
* @param nMaxY	�l�p�`�E��Y���W
* @param color	�F
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

	// ����
	return S_OK;
}

/**
* @brief ������
*/
HRESULT GraphicsManager::Initialize()
{
	// �C���X�^���X�擾
	m_p2Dtex = new Graphics2DTexture();

	// ����
	return S_OK;
}