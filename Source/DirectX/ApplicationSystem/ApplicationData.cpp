#include "ApplicationData.h"

/**
* @brief ウィンドウハンドルの設定
* @param ウィンドウハンドル
*/
VOID ApplicationData::SetWindowHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

/**
* @brief ウィンドウのサイズを設定する
* @param width  ： 横幅
* @param height ： 縦幅
*/
VOID ApplicationData::SetWindowSize(const DWORD width, const DWORD height)
{
	m_Width = width;
	m_Height = height;
}

/**
* @brief ウィンドウモードを設定する
* @param ウィンドウモードの有無
*/
VOID ApplicationData::SetWindowed(bool windowed)
{
	m_windowed = windowed;
}

/**
* @brief ウィンドウハンドルの取得
* @return ウィンドウハンドル
*/
HWND ApplicationData::GetWindowHandle()
{
	return m_hWnd;
}

/**
* @brief ウィンドウの横幅を取得する
* @return 横幅(unsigned long型)
*/
DWORD ApplicationData::GetWindowWidth()
{
	return m_Width;
}

/**
* @brief ウィンドウの縦幅を取得する
* @return 縦幅(unsigned long型)
*/
DWORD ApplicationData::GetWindowHeight()
{
	return m_Height;
}

/**
* @brief ウィンドウモードを取得する
* @return true - ウィンドウ : false - フルスクリーン
*/
bool ApplicationData::GetWindowed()
{
	return m_windowed;
}