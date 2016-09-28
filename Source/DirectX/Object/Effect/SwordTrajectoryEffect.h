/**
* @file   SwordTrajectoryEffect.h
* @brief  ���̋O�ՃG�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SWORDTRAJECTORYEFFECT_H
#define ___SWORDTRAJECTORYEFFECT_H

#include "..\IObject.h"

/**
* @brief ���̋O�ՃG�t�F�N�g�N���X
*/
class SwordTrajectoryEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SwordTrajectoryEffect(const int texid, const Vector2& pos, const Dir& dir, const float rot = 0.0f);

	/**
	* @brief �f�X�g���N�^
	*/
	~SwordTrajectoryEffect(){};

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

	///�ԍ�
	int m_id;

	/// �e�N�X�`���f�[�^
	int hTex[SLASH_MAX];
};

#endif