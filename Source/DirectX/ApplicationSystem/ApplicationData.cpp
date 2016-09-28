#include "ApplicationData.h"

/**
* @brief �E�B���h�E�n���h���̐ݒ�
* @param �E�B���h�E�n���h��
*/
VOID ApplicationData::SetWindowHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

/**
* @brief �E�B���h�E�̃T�C�Y��ݒ肷��
* @param width  �F ����
* @param height �F �c��
*/
VOID ApplicationData::SetWindowSize(const DWORD width, const DWORD height)
{
	m_Width = width;
	m_Height = height;
}

/**
* @brief �E�B���h�E���[�h��ݒ肷��
* @param �E�B���h�E���[�h�̗L��
*/
VOID ApplicationData::SetWindowed(bool windowed)
{
	m_windowed = windowed;
}

/**
* @brief �E�B���h�E�n���h���̎擾
* @return �E�B���h�E�n���h��
*/
HWND ApplicationData::GetWindowHandle()
{
	return m_hWnd;
}

/**
* @brief �E�B���h�E�̉������擾����
* @return ����(unsigned long�^)
*/
DWORD ApplicationData::GetWindowWidth()
{
	return m_Width;
}

/**
* @brief �E�B���h�E�̏c�����擾����
* @return �c��(unsigned long�^)
*/
DWORD ApplicationData::GetWindowHeight()
{
	return m_Height;
}

/**
* @brief �E�B���h�E���[�h���擾����
* @return true - �E�B���h�E : false - �t���X�N���[��
*/
bool ApplicationData::GetWindowed()
{
	return m_windowed;
}