/**
* @file   SlashEffect.h
* @brief  �a���G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SLASHEFFECT_H
#define ___SLASHEFFECT_H

#include "..\IObject.h"

/**
* @brief �a���G�t�F�N�g�N���X
*/
class SlashEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SlashEffect(const Vector2& pos, const Dir& dir,
		const Vector2& vel, const float scale, const float addScale = 0.0f, const float rot = 0.0f);
	/**
	* @brief �f�X�g���N�^
	*/
	~SlashEffect(){};

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

	/// ���x
	Vector2 m_v;

	/// �p�x���x
	float m_addScale;

	/// �����t���[��
	int m_liveFrame;
};

#endif