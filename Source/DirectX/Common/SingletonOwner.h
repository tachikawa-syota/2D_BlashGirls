/**
* @file   SingletonOwner.h
* @brief  �V���O���g�����܂Ƃ߂ĊǗ�����
* @author Syota Tachikawa
*/

#ifndef ___SINGLETONOWNER_H
#define ___SINGLETONOWNER_H

#include "..\DirectX\DeviceManager.h"
#include "..\DirectX\GraphicsLib.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\FileData.h"
#include "..\Sequence\SequenceChanger.h"

/**
* @brief �V���O���g�����܂Ƃ߂ĊǗ�����N���X
*/
class SingletonOwner
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	SingletonOwner();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~SingletonOwner();

	/**
	* @brief ������
	*/
	bool Initialize();

private:
	/// �f�o�C�X
	DeviceManager* m_deviceManager;

	/// �O���t�B�b�N�X
	GraphicsManager* m_graphicsManager;

	/// �T�E���h
	SoundPlayer* m_soundPlayer;
	
	/// �e�N�X�`���f�[�^
	TextureData* m_textureData;

	/// �V�[���`�F���W���[
	SequenceChanger* m_sequenceChanger;

	/// �X�N���[���G�t�F�N�g
	ScreenEffect* m_screenEffect;
};

#endif