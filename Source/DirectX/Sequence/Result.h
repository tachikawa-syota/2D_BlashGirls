/**
* @file   Result.h
* @brief  ���U���g��ʂ̏������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___RESULT_H
#define ___RESULT_H

#include "ISequence.h"
#include "..\DirectX\InputMask.h"
#include "..\Common\StdAfx.h"

/**
* @brief ���U���g���
*/
class Result : public ISequence
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
	
	// �e�N�X�`���f�[�^
	TextureData* m_texData;
	
	// ���̓f�o�C�X
	vector<InputRef> m_dev;
	
	/// �t���[��
	int m_frame;

	/// �T�u���[�N
	int m_subWork;

	/// �I�������L�����N�^�[
	const int* m_select;

	/// �s�k�����v���C���[�ԍ�
	int m_losePl;

	/// �J�[�\���𑀍�ł���v���C���[
	int m_controlPlayer;

	/// �s�҃v���C���[�ԍ��̃e�N�X�`��
	int m_loserPlayerTex[2];

	/// �s�k�����L�����N�^�[�̃e�N�X�`��
	int m_loserCharaTex_[2];

	/// �A���t�@�l
	int m_alpha;

	/// �J�[�\�����[�N
	int m_cursolWork;

	/// �J�[�\���̈ʒu
	float m_cursolY;

	/**
	* @brief �J�[�\���̓���
	*/
	void CursolMove();
};

#endif