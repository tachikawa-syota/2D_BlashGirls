/**
* @file ApplicationData.h
* @brief アプリケーションシステムデータの管理
* @author Syota Tachikawa
*/

#ifndef ___APPLICATIONSYSTEMDATA_H
#define ___APPLICATIONSYSTEMDATA_H

#include "..\Common\StdAfx.h"

// システムデータのインスタンス
#define AppIns ApplicationData::GetInstance()

/**
* @brief アプリケーションのシステムデータを管理するクラス
*/
class ApplicationData
{
public:
	/**
	* @brief ゲットインスタンス
	*/
	static ApplicationData* GetInstance()
	{
		static ApplicationData singlton;
		return &singlton;
	}

	/**
	* @brief ウィンドウハンドルの設定
	* @param ウィンドウハンドル
	*/
	VOID SetWindowHandle(HWND hWnd);


	/**
	* @brief ウィンドウのサイズを設定する
	* @param width  ： 横幅
	* @param height ： 縦幅
	*/
	VOID SetWindowSize(const DWORD width, const DWORD height);

	/**
	* @brief ウィンドウモードを設定する
	* @param ウィンドウモードの有無
	*/
	VOID SetWindowed(bool windowed);

	/**
	* @brief ウィンドウハンドルの取得
	* @return ウィンドウハンドル
	*/
	HWND GetWindowHandle();

	/**
	* @brief ウィンドウの横幅を取得する
	* @return 横幅(unsigned long型)
	*/
	DWORD GetWindowWidth();

	/**
	* @brief ウィンドウの縦幅を取得する
	* @return 縦幅(unsigned long型)
	*/
	DWORD GetWindowHeight();

	/**
	* @brief ウィンドウモードを取得する
	* @return true - ウィンドウ : false - フルスクリーン
	*/
	bool GetWindowed();

private:
	/// ウィンドウハンドル
	HWND m_hWnd;

	/// ウィンドウの横幅
	DWORD m_Width;

	/// ウィンドウの縦幅
	DWORD m_Height;

	/// ウィンドウモード
	bool m_windowed;
};

#endif