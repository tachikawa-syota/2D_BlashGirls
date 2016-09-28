/**
* @file   FireEffect.h
* @brief  �΂̋ʃG�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___FIREEFFECT_H
#define ___FIREEFFECT_H

#include "..\IObject.h"

/**
* @brief �΂̋ʃG�t�F�N�g
*/
class FireEffect : public ICollisionEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param id - �ԍ�
	* @param pos - �`��ʒu
	* @param dir - �`�����
	*/
	FireEffect(const unsigned int id, const Vector2& pos, const Dir& dir);

	/**
	* @brief �f�X�g���N�^
	*/
	~FireEffect(){};

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
	
	/// ��������
	bool m_isDead;
};

#endif