/**
* @file   Title.h
* @brief  �^�C�g���������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___TITLE_H
#define ___TITLE_H

#include "..\DirectX\InputMask.h"
#include "..\Common\StdAfx.h"
#include "ISequence.h"

class Title : public ISequence
{
private:
	// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	// �e�N�X�`���f�[�^
	TextureData* m_texData;

	// ���̓f�[�^���Ǘ�
	vector<InputRef> m_dev;

	/// �T�u���[�N
	int m_subWork;

	/// �^�C�g�����[�N
	int titleWork;

	/// �J�[�\���̈ʒu
	float cursolY;

	/// ���G�t�F�N�g�̃A���t�@�l
	int m_lightAlpha;

	/// ���G�t�F�N�g�̊p�x
	float m_lightAngle;

	/// �A���t�@�l
	int m_alpha;

	/// �t���[��
	int m_frame;

	/// �A���t�@�l�����Z
	bool m_isAlphaPlus;

	/// �I�����ꂽ�L�����N�^�[�i�f���ɓ���O�Ɏg���j
	int m_select[JOY_MAX];

	/// ���u�t���[��
	int m_waitFrame;

	/**
	* @brief �^�C�g���Z���N�g�̍X�V
	*/
	GameMode TitleWork();

	void UpdateLight();

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
};

#endif