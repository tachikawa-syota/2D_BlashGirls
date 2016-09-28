/**
* @file   PowerUpParticle.h
* @brief  �\�͏㏸���̃p�[�e�B�N���V�X�e�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___POWERUPPARTICLE_H
#define ___POWERUPPARTICLE_H

#include "..\IObject.h"

/**
* @brief �p���[�A�b�v�p�[�e�B�N���N���X
*/
class PowerupParticle : public IParticle
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	PowerupParticle(const Vector2& pos,
		const float scale,
		const float alpha);
	/**
	* @brief �f�X�g���N�^
	*/
	~PowerupParticle(){};

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