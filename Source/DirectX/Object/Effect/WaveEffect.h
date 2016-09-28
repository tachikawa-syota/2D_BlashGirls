/**
* @file   WaveEffect.h
* @brief  �g�G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___WAVEEFFECT_H
#define ___WAVEEFFECT_H

#include "..\IObject.h"

class WaveEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	WaveEffect(const Vector2& pos, const Dir& dir);

	/**
	* @brief �f�X�g���N�^
	*/
	~WaveEffect(){};

	/**
	* @brief �X�V
	*/
	bool Update();

	/**
	* @brief �`��
	*/
	void Render();

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;

	/// 2D�I�u�W�F�N�g�p
	Object2DPacket m_obj;

	/// �g�G�t�F�N�g�A�j���[�V����
	int m_hTex[WAVE_MAX];

	/// �A�j���[�V����
	int m_animation;

	/// �A�j���[�V�����t���[��
	int m_animFrame;

	/// ���[�v�J�E���g
	unsigned int loopCount;
};

#endif