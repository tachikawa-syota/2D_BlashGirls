/**
* @file   FileData.h
* @brief  �t�@�C���f�[�^���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___FILEDATA_H
#define ___FILEDATA_H

#include "StdAfx.h"

/// TextureData�̃C���X�^���X�擾
#define GetTextureData TextureData::GetInstance()
/// �e�N�X�`���̍ő吔
#define TEXTURE_MAX 270 
/// D3D�^�e�N�X�`���̍ő吔
#define D3DTEXTURE_MAX 3
/// �����A�A�j���[�V�����ő吔
#define LILIA_ANIM_MAX 26
/// ���i�A�j���[�V�����ő吔
#define RUNA_ANIM_MAX 22
/// ���喂���w�e�N�X�`���ő吔
#define MAGICCIRCLE_MAX 2
/// �����e�N�X�`���ő吔
#define NUMBER_MAX 10
/// �^�C�g�����j���[�e�N�X�`���ő吔
#define TITLE_MENU_MAX 12
/// �a���p�e�N�X�`���ő吔
#define SLASH_MAX 64
/// ���e�N�X�`���ő吔
#define LIGHT_MAX 8
/// �g�e�N�X�`���ő吔
#define WAVE_MAX 14

/// �e�N�X�`���l�[��
enum _TEXTURE_TYPE_{
	/// �^�C�g��
	TEX_TITLE_BG,
	TEX_TITLE_LOGO,
	TEX_TITLE_ICON,

	/// �L�����N�^�[�I�����
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
	// �o�g����
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

	// ���U���g
	TEX_LOSE_FONT,
	TEX_CONTINUE_FONT,
	TEX_CONTINUE_FRAME,
	TEX_CONTINUE_CURSOL,
	// �����A
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
	// ���i
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
	// �����w
	TEX_MAGICCIRCLE_G,
	TEX_MAGICCIRCLE_P,
	TEX_MAGIC_FONT_R,
	TEX_MAGIC_FONT_B,
	// �΃G�t�F�N�g
	TEX_HINOKO,
	// �a���G�t�F�N�g
	TEX_SLASH,
	TEX_SLASH2,
	TEX_SLASH3,
	TEX_SLASH4,
	// ���G�t�F�N�g
	TEX_SMOKE,
	// �փG�t�F�N�g
	TEX_RING,
	TEX_RED_RING,
	TEX_BLUE_RING,
	TEX_BURST_RING,
	// �u���[
	TEX_BLUR,
	// ���C��
	TEX_LINE,
	// ���G�t�F�N�g
	TEX_LIGHT,
	TEX_LIGHT2,
	TEX_LIGHT3,
	TEX_LIGHT4,
	TEX_RED_LIGHT,
	TEX_BLUE_LIGHT,
	TEX_FLUSH,
	// �P���G�t�F�N�g
	TEX_SHINE,
	TEX_SHINE2,
	// �K�[�h�G�t�F�N�g
	TEX_GUARD,
	// �q�b�g�G�t�F�N�g�p�[�e�B�N��
	TEX_HIT_EFFECT,
	// �K�[�h�G�t�F�N�g�p�[�e�B�N��
	TEX_GUARD_EFFECT,
	// �΃p�[�e�B�N���p
	TEX_FIRE_LIGHT,
	// ���p�[�e�B�N���p
	TEX_STAR,
	// �X�G�t�F�N�g
	TEX_FROST,
	// �A�G�t�F�N�g
	TEX_FORM,
	// ���E�G�t�F�N�g
	TEX_OFFSET,

	TEXTURE_TYPE_MAX,
};

enum _D3DTEXTURE_{
	TEX_SHAME_GAUGE,
	TEX_SHAME_GAUGE_OLD,
	TEX_SPECIAL_GAUGE,
};

// �O���錾
class GraphicsManager;

/**
* @brief �e�N�X�`���f�[�^���Ǘ�����N���X
*/
class TextureData
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	TextureData(){};
	~TextureData(){};
	
	/**
	* @brief �Q�b�g�C���X�^���X
	*/
	static TextureData* GetInstance(){
		static TextureData singleton;
		return &singleton;
	}

	/**
	* @brief �e�N�X�`���f�[�^�̓ǂݍ���
	*/
	HRESULT LoadTexture();

	/**
	* @brief �e�N�X�`���f�[�^�̎擾
	*/
	int GetTexture(int num) { return tex[num]; }
	
	/**
	* @brief D3D�^�e�N�X�`���f�[�^�̎擾
	*/
	LPDIRECT3DTEXTURE9 GetD3dTexture(int num) { return d3dTex[num]; }

	/// �����A�A�j���[�V�����̎擾
	int GetLiliaAnim(int num) { return liliaAnim[num]; }
	/// ���i�A�j���[�V�����̎擾
	int GetRunaAnim(int num) { return runaAnim[num]; }
	/// �����w�e�N�X�`���̎擾
	int GetMagicCircleTexture(int num) { return magicCircle[num]; }
	/// �ԐF�����e�N�X�`���̎擾
	int GetRedNumberTexture(int num) { return redNumberFont[num]; }
	/// �����e�N�X�`���̎擾
	int GetNumberTexture(int num) { return numberFont[num]; }
	/// �^�C�g�����j���[�e�N�X�`���̎擾
	int GetTitleMenuTexture(int num) { return titleMenu[num]; }
	/// �a���e�N�X�`���̎擾
	int GetSlashTexture(int num) { return slash[num]; }
	/// ���e�N�X�`���̎擾
	int GetLightTexture(int num) { return light[num]; }
	/// �g�e�N�X�`���̎擾
	int GetWaveTexture(int num) { return wave[num]; }

private:
	/// ��{�e�N�X�`��
	int tex[TEXTURE_MAX];
	/// D3D�^�e�N�X�`��
	LPDIRECT3DTEXTURE9 d3dTex[D3DTEXTURE_MAX];

	/// �����A�A�j���[�V�����e�N�X�`��
	int liliaAnim[LILIA_ANIM_MAX];

	/// ���i�A�j���[�V�����e�N�X�`��
	int runaAnim[RUNA_ANIM_MAX];

	/// �u���b�N�^�����w�e�N�X�`��
	int magicCircle[MAGICCIRCLE_MAX];

	/// �u���b�N�^�ԐF�����e�N�X�`��
	int redNumberFont[NUMBER_MAX];

	/// �u���b�N�^�����e�N�X�`��
	int numberFont[NUMBER_MAX];

	/// �u���b�N�^�^�C�g�����j���[�e�N�X�`��
	int titleMenu[TITLE_MENU_MAX];
	
	/// �u���b�N�^�a���p�e�N�X�`��
	int slash[SLASH_MAX];

	/// �u���b�N�^���e�N�X�`��
	int light[LIGHT_MAX];

	/// �u���b�N�^�g�e�N�X�`��
	int wave[WAVE_MAX];

	// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;
};


/**
* @brief �T�E���h�f�[�^���Ǘ�����
*/
class SoundData
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SoundData();
	/**
	* @brief �f�X�g���N�^
	*/
	~SoundData();
};

#endif