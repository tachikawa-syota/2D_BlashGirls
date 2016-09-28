/**
* @file   RingEffect.h
* @brief  �ւ����G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___RINGEFFECT_H
#define ___RINGEFFECT_H

#include "..\IObject.h"

/**
* @brief �ւ����G�t�F�N�g�N���X
*/
class RingEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	RingEffect(const Vector2& pos, const ARGB& color, const float addScale);

	/**
	* @brief �f�X�g���N�^
	*/
	~RingEffect(){};

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

	/// �J���[�f�[�^
	ARGB m_color;

	/// �g�呬�x
	float m_addScale;

	/// �����t���[��
	int m_liveFrame;
};

#endif