/**
* @file   OffsetParticle.h
* @brief  ���E�p�[�e�B�N�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___OFFSETPARTICLE_H
#define ___OFFSETPARTICLE_H

#include "..\IObject.h"

/**
* @brief ���E�p�[�e�B�N���N���X
*/
class OffsetParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	OffsetParticle(const Vector2& pos);
	/**
	* @brief �f�X�g���N�^
	*/
	~OffsetParticle(){};

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

	/// �����t���[��
	int m_liveFrame;
};

#endif