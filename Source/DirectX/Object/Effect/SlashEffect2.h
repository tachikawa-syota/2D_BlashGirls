/**
* @file   SlashEffect2.h
* @brief  �a���G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SLASHEFFECT2_H
#define ___SLASHEFFECT2_H

#include "..\IObject.h"

/**
* @brief �a���G�t�F�N�g�N���X
*/
class SlashEffect2 : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SlashEffect2(const Vector2& pos, const Dir& dir,
		const Vector2& vel, const float rot);

	/**
	* @brief �f�X�g���N�^
	*/
	~SlashEffect2(){};

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
};

#endif