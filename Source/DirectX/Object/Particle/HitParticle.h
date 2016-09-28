/**
* @file   HitParticle.h
* @brief  �q�b�g�p�[�e�B�N�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___HITPARTICLE_H
#define ___HITPARTICLE_H

#include "..\IObject.h"

/**
* @brief �q�b�g�p�[�e�B�N���N���X
*/
class HitParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	HitParticle(const Vector2& pos,
		const float scale);
	/**
	* @brief �f�X�g���N�^
	*/
	~HitParticle(){};

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