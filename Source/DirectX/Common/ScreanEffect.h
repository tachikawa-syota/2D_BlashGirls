/**
* @file   ScreanEffect.h
* @brief  �X�N���[���G�t�F�N�g�������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SCREANEFFECT_H
#define ___SCREANEFFECT_H

#include "StdAfx.h"
#include "..\DirectX\GraphicsLib.h"

/**
* @brief �X�N���[���G�t�F�N�g�N���X
*/
class ScreenEffect
{
public:
	// �C���X�^���X�擾
	static ScreenEffect* GetInstance(){
		static ScreenEffect singleton;
		return &singleton;
	}

	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �t�F�[�h�̐ݒ�
	*/
	bool SetFade(Fade type, FadeColor color, int frame);

	/**
	* @brief �t�F�[�h���s�������`�F�b�N
	*/
	bool isPlayFade();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Draw();

private:
	/// ���Z�l
	int m_add;

	/// �F
	FadeColor m_color;

	/// �t���[��
	int m_frame;

	/// �J�E���g
	int m_fade_cnt;

	/// ���
	Fade m_state;

};

#endif