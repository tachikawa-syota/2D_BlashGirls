/**
* @file   FrameWork.h
* @brief  �t���[�����[�N
* @author Syota Tachikawa
*/

#ifndef ___FRAMEWORK_H
#define ___FRAMEWORK_H

#include "..\Common\StdAfx.h"
#include "..\Common\SingletonOwner.h"

/**
* @brief �t���[�����[�N�N���X
*/
class FrameWork
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	FrameWork();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~FrameWork();

	/**
	* @brief �쐬
	* @param �C���X�^���X
	* @return true - �����Ffalse - ���s
	*/
	bool Create(HINSTANCE hInst);

	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �X�V�ƕ`��
	*/
	void Run();

private:
	/// �A�v���P�[�V�����V�X�e��
	unique_ptr<WindowsApplication> pSys;

	/// D3D�V�X�e��
	unique_ptr<Direct3DSystem> pD3d;

	/// �V�[��
	ISequence* m_nowScene;

	/// �V���O���g���I�[�i�[
	unique_ptr<SingletonOwner> m_singletonOwner;

	/// �t�H���g
	unique_ptr<Font> m_font;

	/// �T�E���h�f�[�^
	unique_ptr<SoundData> m_soundData;

	/// FPS�J�E���^�[
	unique_ptr<FPSCounter> m_fpsCounter;

	/**
	* @brief ��ʃN���A
	*/
	BOOL HCls();

	/**
	* @brief �t���b�s���O
	*/
	BOOL Flip();

	/**
	* @brief FPS�̕\��
	*/
	VOID RenderFPS();
};



#endif