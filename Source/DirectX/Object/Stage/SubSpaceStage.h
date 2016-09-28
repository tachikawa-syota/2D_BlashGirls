/**
* @file   SubSpaceStage.h
* @brief  ����ԃX�e�[�W���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SUBSPACESTAGE_H
#define ___SUBSPACESTAGE_H

#include "..\IObject.h"
#include "..\..\Common\StdAfx.h"

/**
* @brief ����ԃX�e�[�W�N���X
*/
class SubSpaceStage : public IStage
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SubSpaceStage();

	/**
	* @brief �f�X�g���N�^
	*/
	~SubSpaceStage();

	/**
	* @brief �X�V
	*/
	bool Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �A���t�@�l�̕ύX�i����X�L�����g�������ɔw�i���Â�����p�Ŏg���j
	*/
	void ChangeAlpha(int alpha);

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;
	
	/// �t���[��
	unsigned int m_frame;
	
	/// �X�e�[�W�S�̂̃A���t�@�l
	int m_stageAlpha;
	
	/// ���A���t�@�l
	int m_lightAlpha;
	
	/// �G�t�F�N�g�g�嗦
	float m_effectScale;
	
	/// �G�t�F�N�g�g��t���O
	bool m_isEffectScale;
};

#endif