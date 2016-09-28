/**
* @file   FormParticle.h
* @brief  �A�p�[�e�B�N�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___STARARTICLE_H
#define ___STARPARTICLE_H

#include "..\IObject.h"

/**
* @brief �A�p�[�e�B�N���N���X
*/
class FormParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	FormParticle(const Vector2& pos , const float scale);
	/**
	* @brief �f�X�g���N�^
	*/
	~FormParticle(){};

	/**
	* @brief �X�V
	*/
	bool Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief ��������
	*/
	bool isDead();

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