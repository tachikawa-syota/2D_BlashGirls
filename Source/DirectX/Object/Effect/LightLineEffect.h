/**
* @file   LightLineEffect.h
* @brief  ���̐��G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___LIGHTLINEEFFECT_H
#define ___LIGHTLINEEFFECT_H

#include "..\IObject.h"

/**
* @brief ���̐��G�t�F�N�g�N���X
*/
class LightLineEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	LightLineEffect(const Vector2& pos);

	/**
	* @brief �f�X�g���N�^
	*/
	~LightLineEffect(){};

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