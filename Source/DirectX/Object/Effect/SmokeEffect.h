/**
* @file   SmokeEffect.h
* @brief  ���G�t�F�N�g���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___SMOKEEFFECT_H
#define ___SMOKEEFFECT_H

#include "..\IObject.h"

/**
* @brief ���G�t�F�N�g���Ǘ�����N���X
*/
class SmokeEffect : public IEffect
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param �`��ʒu
	*/
	SmokeEffect(const Vector2& pos);

	/**
	* @brief �f�X�g���N�^
	*/
	~SmokeEffect(){};

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