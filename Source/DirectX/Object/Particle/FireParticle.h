/**
* @file   FireParticle.h
* @brief  �΃p�[�e�B�N���V�X�e�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___FIREPARTICLE_H
#define ___FIREPARTICLE_H

#include "..\IObject.h"

/**
* @brief �΃p�[�e�B�N���N���X
*/
class FireParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	FireParticle(const Vector2& pos,
		const float scale);
	/**
	* @brief �f�X�g���N�^
	*/
	~FireParticle(){};

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

	/// �����x
	Vector2 m_add;
};

#endif