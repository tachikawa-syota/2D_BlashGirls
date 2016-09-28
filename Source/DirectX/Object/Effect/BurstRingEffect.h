/**
* @file   BurstRingEffect.h
* @brief  �Ռ��g�G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___BURSTRINGEFFECT_H
#define ___BURSTRINGEFFECT_H

#include "..\IObject.h"

/**
* @brief �Ռ��g�G�t�F�N�g
*/
class BurstRingEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	BurstRingEffect(const Vector2& pos);

	/**
	* @brief �f�X�g���N�^
	*/
	~BurstRingEffect(){};

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

	/// �����t���[��
	int m_liveFrame;
};

#endif