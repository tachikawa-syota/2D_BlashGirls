/**
* @file   ShineEffect.h
* @brief  ����G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SHINEEFFECT_H
#define ___SHINEEFFECT_H

#include "..\IObject.h"

class ShineEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ShineEffect(const Vector2& pos);

	/**
	* @brief �f�X�g���N�^
	*/
	~ShineEffect(){};

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
	array<Object2DPacket ,2> m_obj;

	/// �T�u���[�N
	int m_subWork;
};

#endif