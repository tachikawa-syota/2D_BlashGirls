/**
* @file   SpecialSlashEffect.h
* @brief  �K�E�Z�p�a���G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SPECIALSLASHEFFECT_H
#define ___SPECIALSLASHEFFECT_H

#include "..\IObject.h"

class SpecialSlashEffect : public ICollisionEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SpecialSlashEffect(const unsigned int id, const Vector2& pos, const Dir& dir, const Vector2& vel, const float rot = 0.0f);

	/**
	* @brief �f�X�g���N�^
	*/
	~SpecialSlashEffect(){};

	/**
	* @brief �X�V
	*/
	bool Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �v���C���[�Ƃ̓����蔻��
	*/
	void CollisionCheckPlayer(IPlPtr obj);

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;
	
	/// 2D�I�u�W�F�N�g�p
	Object2DPacket m_obj;
	
	/// ���x
	Vector2 m_v;

	/// �q�b�g�͈�
	Rect m_hitRect;
	
	/// �ԍ�
	unsigned int m_id;
	
	/// �����t���[��
	int m_liveFrame;
	
	/// �q�b�g�t���O
	bool m_isHit;
};

#endif