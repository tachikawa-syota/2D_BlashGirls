/**
* @file GraphicsLib.h
* @brief �O���t�B�b�N�Ɋւ���S�ʂ��Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___GRAPHICSLIB_H
#define ___GRAPHICSLIB_H

#include "..\Common\StdAfx.h"

/// �摜�i�[�ő吔
#define MAX_TEXTURE		270

/// �O���t�B�b�N�}�l�[�W���[�̃C���X�^���X�擾
#define GetGraphicsManager GraphicsManager::GetInstance()

/**
* @brief �e�N�X�`���ɕK�v�ȍ\����
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
* @brief 2D�e�N�X�`���p�\����
*/
typedef struct{
	float					x, y, z;
	float					rhw;
	DWORD					uDiffuse;
	float					tu, tv;
}D2D_TEXTURE;

/**
* @brief 3D�e�N�X�`���p�\����
*/
typedef struct{
	float					x, y, z;
	DWORD					uDiffuse;
	float					tu, tv;
}D3D_TEXTURE;

/**
* @brief �A���t�@�E�ԁE�΁E��
*/
typedef struct{
	DWORD					alpha;
	DWORD					red;
	DWORD					green;
	DWORD					blue;
}ARGB;


/**
* @brief 2D�e�N�X�`��������
*/
class Graphics2DTexture
{
private:
	/// �u���b�N�ǂݍ��ݎ��Ɏg�p
	int numx, numy;

	/// �f�o�C�X	
	LPDIRECT3DDEVICE9	m_pDevice;
	
	/// �e�N�X�`���f�[�^
	TEXTURE m_tex[MAX_TEXTURE];

	/**
	* @brief �󂫔z�񌟍�
	* @return �z��ԍ�
	*/
	int FindEmptyArray();

public:
	/**
	* @brief �R���X�g���N�^
	*/
	Graphics2DTexture();
	/**
	* @brief �f�X�g���N�^
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
* @brief �O���t�B�b�N�S�̂��Ǘ�����
*/
class GraphicsManager
{
private:
	/**
	* @brief �R���X�g���N�^
	*/
	GraphicsManager(){
		m_p2Dtex = nullptr;
	};

	/// 2D�e�N�X�`��
	Graphics2DTexture* m_p2Dtex;

	/// �f�o�C�X
	LPDIRECT3DDEVICE9 m_device;

public:
	/**
	* @brief �Q�b�g�C���X�^���X
	*/
	static GraphicsManager* GetInstance(){
		static GraphicsManager singleton;
		return &singleton;
	}
	/**
	* @brief �f�X�g���N�^
	*/
	~GraphicsManager(){};

	/**
	* @brief ������
	*/
	HRESULT Initialize();

	/**
	* �f�o�C�X�ȊO�����(��{�I�ɂ��ׂĉ�����Ă��܂�)
	*/
	void ReleaseAll();

	/**
	* @brief �e�N�X�`���𒆐S�ɕ`�悷��
	* @param index - �e�N�X�`���f�[�^
	* @param posX - X���W�̎w��
	* @param posY - Y���W�̎w��
	* @param angle - �p�x
	* @param scale - �傫��
	* @param alpha - �A���t�@�l
	* @param add - ���Z�����̗L��
	* @param reverse - ���]���ĕ`�悷�邩
	*
	* @note �g�����F"index"��"LoadTexture"�œǂݍ��񂾃f�[�^���w�肵�Ă�������
	*				�e�N�X�`������]���ĕ`�悵�����ꍇ��"angle"�Ɋp�x���w�肵�Ă�������
	*				�p�x�E�傫���E���Z�E���]�Ɋւ��Ă̓f�t�H���g�ň������w�肵�Ă��܂�
	*/
	HRESULT DrawTexture(int index, float posX, float posY, float angle = 0.0f, float scale = 1.0f, int alpha = 255, bool add = false, bool reverse = false){
		return m_p2Dtex->DrawTexture(index, posX, posY, angle, scale, alpha, add, reverse);
	}

	/**
	* @brief �e�N�X�`���𒆐S�ɕ`�悷��
	* @param x1 - ���[X���W
	* @param y1 - ���[Y���W
	* @param x2 - �E�[X���W
	* @param y2 - �E�[Y���W
	* @param pTex - �e�N�X�`���f�[�^�iD3DLoadTexture�œǂݍ��񂾂�j
	* @param z	- z��
	* @param add - ���Z�����̗L��
	*
	* @note �g�����F"pTex"��"D3DLoadTexture"�œǂݍ��񂾃f�[�^���w�肵�Ă�������
	*/
	HRESULT DrawTextureEx(float x1, float y1, float x2, float y2, LPDIRECT3DBASETEXTURE9 pTex, float z = 0.0f, bool add = false){
		return m_p2Dtex->DrawTextureEx(x1, y1, x2, y2, pTex, z, add);
	}

	/**
	* @brief �e�N�X�`�����r���{�[�h�ŕ`�悷��
	* @param index - �e�N�X�`���f�[�^
	* @param pos - �`��ʒu
	* @param angle - �p�x
	* @param scale - �傫��
	* @param alpha - �A���t�@�l
	* @param mBillboard - �r���{�[�h
	* @param billFlag - �r���{�[�h���邩�ǂ���
	*/
	HRESULT Draw3DTexture(int index, D3DXVECTOR3 pos, D3DXVECTOR3 angle, D3DXVECTOR3 scale, int alpha, D3DXMATRIX mBillboard, int billFlg){
		return m_p2Dtex->Draw3DTex(index, pos, angle, scale, alpha, mBillboard, billFlg);
	}

	/**
	* @brief �e�N�X�`����`�悷��i�J���[�̕ύX���\�j
	* @param index - �e�N�X�`���f�[�^
	* @param posX - X���W�̎w��
	* @param posY - Y���W�̎w��
	* @param argb - �J���[�f�[�^�̎w��
	* @param add - ���Z�����̗L��
	* @param angle - �p�x
	* @param scale - �傫��
	* @param reverse - ���]���ĕ`�悷�邩
	*/
	HRESULT DrawTexARGB(int index, float posX, float posY, ARGB argb, bool add = true, float angle = 0.0f, float scale = 1.0f, bool reverse = false){
		return m_p2Dtex->DrawTexARGB(index, posX, posY, argb, add, angle, scale, reverse);
	}

	/**
	* @brief �l�p�`��`�悷��
	*/
	HRESULT DrawBox(float nMinX, float nMinY, float nMaxX, float nMaxY, DWORD color){
		return m_p2Dtex->DrawBox(nMinX, nMinY, nMaxX, nMaxY, color);
	}

	/**
	* @brief �e�N�X�`���̓ǂݍ���
	* @param szFileName - �e�N�X�`���t�@�C���̖��O
	* @return �e�N�X�`���̔ԍ�
	*/
	int LoadTexture(const char* szFileName){
		return m_p2Dtex->LoadTexture(szFileName);
	}

	/**
	* @brief D3D�^�̃e�N�X�`���̓ǂݍ���
	*/
	LPDIRECT3DTEXTURE9 D3LoadTexture(char *szFileName){
		return m_p2Dtex->LoadTexture(szFileName);
	}

	/**
	* @brief �u���b�N�^�̃e�N�X�`���̓ǂݍ���
	* @param szFileName - �e�N�X�`���t�@�C���̖��O
	* @param sizeX - ������������1�����̃e�N�X�`���̉���
	* @param sizeY - ������������1�����̃e�N�X�`���̏c��
	* @param numX - ���ɕ��ׂ��Ă���e�N�X�`���̖���
	* @param numY - �c�ɕ��ׂ��Ă���e�N�X�`���̖���
	* @param numMax - �e�N�X�`���̑�����
	* @param *data - �ǂݍ��񂾃e�N�X�`�����i�[����z��|�C���^
	* @return �e�N�X�`���̔ԍ�
	*
	* @note �g�����F"sizeX,sizeY"��1�����̃e�N�X�`���̕����w�肵�Ă�������
	*				�e�N�X�`���̃T�C�Y���S�ē����T�C�Y�̃��m�łȂ��Ɠǂݍ��݂���肭�����܂���i�o���o���ł��ǂݍ��߂�悤�ɂ�����Ή����������j
	*				"numMax"��"numX�ɓ��ꂽ�l * numY�ɓ��ꂽ�l"�ɂ��Ă�������
	*				*data�̔z��T�C�Y�ƃe�N�X�`���̖������قȂ�ƃo�O�̗v���ɂȂ�̂ł����ӂ�
	*/
	int LoadBlkTexture(const char* szFileName, int sizeX, int sizeY, int numX, int numY, int numMax, int *data){
		return m_p2Dtex->LoadBlkTexture(szFileName, sizeX, sizeY, numX, numY, numMax, data);
	}
};

#endif