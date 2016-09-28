/**
* @file   LightEffect.h
* @brief  ���G�t�F�N�g���Ǘ�
* @author Syota Tachikawa
*/

#ifndef ___LIGHTEFFECT_H
#define ___LIGHTEFFECT_H

#include "..\IObject.h"

/**
* @brief ���G�t�F�N�g
*/
class LightEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param �`��ʒu
	*/
	LightEffect(const Vector2& pos);

	/**
	* @brief �f�X�g���N�^
	*/
	~LightEffect(){};

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

	/// �A�j���[�V�����p
	int m_animation;

	/// �e�N�X�`���f�[�^
	int hTex[LIGHT_MAX];

	/// �A�j���[�V�����t���[��
	int m_animFrame;
};

#endif