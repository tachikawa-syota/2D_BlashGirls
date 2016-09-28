/**
* @file   GuardEffect.h
* @brief  �K�[�h�G�t�F�N�g���Ǘ�
* @author Syota Tachikawa
*/

#ifndef ___GUARDEFFECT_H
#define ___GUARDEFFECT_H

#include "..\..\Common\Struct.h"
#include "..\IObject.h"

/**
* @brief �K�[�h�G�t�F�N�g
*/
class GuardEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param pos - �`��ʒu
	* @param dir - �`�����
	*/
	GuardEffect(const Vector2& pos, const Dir& dir);

	/**
	* @brief �f�X�g���N�^
	*/
	~GuardEffect(){};

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