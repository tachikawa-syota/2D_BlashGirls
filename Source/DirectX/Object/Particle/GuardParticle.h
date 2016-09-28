/**
* @file   GuardParticle.h
* @brief  �K�[�h�p�[�e�B�N�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___GUARDPARTICLE_H
#define ___GUARDPARTICLE_H

#include "..\IObject.h"

/**
* @brief �K�[�h�p�[�e�B�N���N���X
*/
class GuardParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	GuardParticle(const Vector2& pos,
		const float scale);
	/**
	* @brief �f�X�g���N�^
	*/
	~GuardParticle(){};

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

	/// �����t���[��
	int m_liveFrame;
};

#endif