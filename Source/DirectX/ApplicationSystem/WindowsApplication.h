/**
* @file WindowsApplication.h
* @brief アプリケーションシステムの管理
* @author Syota Tachikawa
* @date 11/27
*/

#ifndef ___WINDOWSAPPLICATION_H
#define ___WINDOWSAPPLICATION_H

#include "..\Common\StdAfx.h"
#include <crtdbg.h>

/// アプリケーションネーム
#define APPLICATION_NAME "Blush Girls"

/**
* @brief ウィンドウズアプリケーションクラス
*/
class WindowsApplication
{
public:
	/**
	* @brief コンストラクタ
	*/
	WindowsApplication();
	
	/**
	* @brief デストラクタ
	*/
	~WindowsApplication();

	/**
	* @brief 作成
	*/
	HRESULT Create(HINSTANCE hInst);

	/**
	* @brief ウィンドウからのメッセージ処理
	*/
	BOOL ProcessEvent();

	/**
	* @brief ウィンドウの初期化（ 作成 ）
	*/
	BOOL WindowInitialize(HINSTANCE hInst);

	/**
	* @brief 解放
	*/
	VOID Release();

private:
	/// メッセージ
	MSG m_msg;

	/// ウィンドウハンドル
	HWND m_hWnd;

	/**
	* @brief ウィンドウクラスへ登録
	* @param hInst   ： インスタンス
	* @param WndProc ： ウィンドウプロシージャ
	*/
	ATOM RegisterWindowClass(HINSTANCE hInst, WNDPROC WndProc);

	/**
	* @brief ウィンドウプロシージャ
	* @param 規定のパラメータ
	* @return メッセージ処理の結果
	*/
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	/**
	* @brief デバッグ用ウィンドウを開く
	*/
	static void OpenDebugWindow();

	/**
	* @brief デバッグ用ウィンドウを閉じる
	*/
	void CloseDebugWindow();
};

#endif