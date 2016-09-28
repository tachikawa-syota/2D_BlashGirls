/**
* @file   CutIn.h
* @brief  �J�b�g�C���������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___CUTIN_H
#define ___CUTIN_H

#include "..\Common\StdAfx.h"

/**
* @brief �J�b�g�C���N���X
*/
class CutIn
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param name - �L�����N�^�[�̖��O
	* @param index - �L�����N�^�[�̔ԍ�
	*/
	CutIn(int name, int index);

	/**
	* @brief �f�X�g���N�^
	*/
	~CutIn();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;

	/// �I�u�W�F�N�g
	Object2DPacket m_obj;

	/// ���x
	Vector2 m_v;

	/// �ԍ�
	int m_index;

	/// �w�i
	int m_backTex;

	/// ����
	float m_inertia;
};

#endif