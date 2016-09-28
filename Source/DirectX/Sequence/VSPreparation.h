#pragma once

#include "ISequence.h"
#include "..\Common\StdAfx.h"

class VSPreparation : public ISequence
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

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;

	/// �L�����N�^�[�I�u�W�F�N�g
	Object2DPacket m_obj[JOY_MAX];

	/// Player�t�H���g�I�u�W�F�N�g
	Object2DPacket m_plFontObj[JOY_MAX];

	/// �L�����N�^�[�I�u�W�F�N�g�̑��x
	float m_v[JOY_MAX];

	/// Player�t�H���g�I�u�W�F�N�g�̑��x
	float m_plFontvx[JOY_MAX];

	/// �L�����N�^�[�̖��O�t�H���g�I�u�W�F�N�g
	Object2DPacket m_nameObj[JOY_MAX];

	/// �L�����N�^�[�̖��O�t�H���g�̑��x
	float m_namevx[JOY_MAX];
	float m_namevy[JOY_MAX];

	/// �L�����N�^�[�I�u�W�F�N�g�̃A���t�@�l�i�A���t�@�l�͋��ʂ����l�����邩�������j
	int m_alpha;

	/// �t���[��
	int m_frame;

	/// �T�u���[�N
	int m_subWork;

	/// �w�i�t�H���g�̈ʒu
	float fontY;

	/// VS�t�H���g�̑傫��
	float vsScale_;

	/**
	* @brief �w�i�����̍X�V
	*/
	void UpdateBackgroundFont();

};