/**
* @file ApplicationData.h
* @brief �A�v���P�[�V�����V�X�e���f�[�^�̊Ǘ�
* @author Syota Tachikawa
*/

#ifndef ___APPLICATIONSYSTEMDATA_H
#define ___APPLICATIONSYSTEMDATA_H

#include "..\Common\StdAfx.h"

// �V�X�e���f�[�^�̃C���X�^���X
#define AppIns ApplicationData::GetInstance()

/**
* @brief �A�v���P�[�V�����̃V�X�e���f�[�^���Ǘ�����N���X
*/
class ApplicationData
{
public:
	/**
	* @brief �Q�b�g�C���X�^���X
	*/
	static ApplicationData* GetInstance()
	{
		static ApplicationData singlton;
		return &singlton;
	}

	/**
	* @brief �E�B���h�E�n���h���̐ݒ�
	* @param �E�B���h�E�n���h��
	*/
	VOID SetWindowHandle(HWND hWnd);


	/**
	* @brief �E�B���h�E�̃T�C�Y��ݒ肷��
	* @param width  �F ����
	* @param height �F �c��
	*/
	VOID SetWindowSize(const DWORD width, const DWORD height);

	/**
	* @brief �E�B���h�E���[�h��ݒ肷��
	* @param �E�B���h�E���[�h�̗L��
	*/
	VOID SetWindowed(bool windowed);

	/**
	* @brief �E�B���h�E�n���h���̎擾
	* @return �E�B���h�E�n���h��
	*/
	HWND GetWindowHandle();

	/**
	* @brief �E�B���h�E�̉������擾����
	* @return ����(unsigned long�^)
	*/
	DWORD GetWindowWidth();

	/**
	* @brief �E�B���h�E�̏c�����擾����
	* @return �c��(unsigned long�^)
	*/
	DWORD GetWindowHeight();

	/**
	* @brief �E�B���h�E���[�h���擾����
	* @return true - �E�B���h�E : false - �t���X�N���[��
	*/
	bool GetWindowed();

private:
	/// �E�B���h�E�n���h��
	HWND m_hWnd;

	/// �E�B���h�E�̉���
	DWORD m_Width;

	/// �E�B���h�E�̏c��
	DWORD m_Height;

	/// �E�B���h�E���[�h
	bool m_windowed;
};

#endif