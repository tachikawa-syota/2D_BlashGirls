/**
* @file   CharaSelect.h
* @brief  �L�����N�^�[�I���������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___CHARASELECT_H
#define ___CHARASELECT_H

#include "ISequence.h"
#include "..\Common\StdAfx.h"
#include "..\Common\Struct.h"
#include "..\DirectX\InputMask.h"

/**
* @brief �L�����N�^�[�I�����
*/
class CharaSelect : public ISequence
{
public:
	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �쐬
	*/
	void Create();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �I��
	*/
	void Finalize();

	int FindEmptyArray();

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;
	
	/// ���̓f�o�C�X
	vector<InputRef> m_dev;

	/// ���쌠���̂���R���g���[���[
	unsigned int controlJoy;

	/// �I�����ꂽ�L�����N�^�[
	int m_selectChara[JOY_MAX];

	/// �T�u���[�N
	int subWork;

	/// �t���[��
	int frame;

	/// �J�[�\���ԍ�
	int m_cursolNum;

	// �L�����N�^�[�����e�N�X�`��
	int charaFont[2];

	/// �L�����N�^�[�������e�N�X�`��
	int charaText[2];

	/// �w�i��]�p
	float bgRot;

	/// �L�����N�^�[�A�j���[�V����
	int animation;

	/// �A�j���[�V�����ő吔
	int animMax;

	/// �A�j���[�V�����t���[��
	int animFrame;
	int adjustAnimFrame;

	/**
	* @brief �L�����N�^�[�I���̍X�V
	*/
	bool UpdateSelect();

	/**
	* @brief �J�[�\���̈ړ��̍X�V
	*/
	void CursolMove();

	/**
	* @brief �L�����N�^�[�̓����̍X�V
	*/
	void CharaMove();

	/**
	* @brief �L�����N�^�A�j���[�V����
	*/
	void Animation();

	/**
	* @brief �A�j���[�V������ݒ肷��
	*/
	void SetAnimation(const int aniMax, const int adjustAniFrame);

	/**
	* @brief �����w�쐬
	*/
	void MagicalCreate();

	/**
	* @brief �����w�̈ړ�
	*/
	void MagicalMove();
};

/**
* @brief �L�����N�^�[�̃A�C�R���\����
*/
typedef struct
{
	float x, y;
	int kind;
	int tex;
}CHARAICON;

/**
* @brief �w�i�ɕ`�悷��L�����N�^�[�\����
*/
typedef struct
{
	float x, y;
	float vx;
	float initX;
	bool flag;	// �؂�ւ��t���O
	bool isSet;	// �Z�b�g�t���O
	bool isDisp;// �\���t���O
	int frame;
	int tex;
	int alpha;
}BACKCHARA;

/**
* @brief �I�����ɕ`�悷��L�����N�^�[�\����
*/
typedef struct
{
	float x, y;
	bool isDisp;	// �\���t���O
	bool isFlash;	// ���点��t���O
	int girl1[3];
	int girl2[3];
	int alpha;
}SELECTCHARA;

/**
* @brief �J�[�\���\����
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
* @brief �����w�\����
*/
typedef struct
{
	Vector2 pos;
	float v;
	int tex[2];
	int kind;
	bool flag;	// �����t���O
}MAGICAL;

#endif