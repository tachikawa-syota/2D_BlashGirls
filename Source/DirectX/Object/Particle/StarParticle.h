/**
* @file   StarParticle.h
* @brief  ���p�[�e�B�N�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___STARARTICLE_H
#define ___STARPARTICLE_H

#include "..\IObject.h"

/**
* @brief ���p�[�e�B�N���N���X
*/
class StarParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	StarParticle(const Vector2& pos);
	/**
	* @brief �f�X�g���N�^
	*/
	~StarParticle(){};

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