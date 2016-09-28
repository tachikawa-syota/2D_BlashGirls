/**
* @file   myD3dlib.h
* @brief  DirectX関係やよく使うマクロなどを管理
* @author Syota Tachikawa
* @date   11/27
*/

#ifndef ___MYD3DLIB_H
#define ___MYD3DLIB_H

// 警告抑制
#pragma warning(disable:4819)

//必要なライブラリファイルのロード
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

// DirectX
#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9math.h>

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <math.h>
// Input関係
#include <dinput.h>
// Sound関係
#include <mmsystem.h>
#include <process.h>
#include <ddraw.h>
#include <dsound.h>
#include <mmeapi.h>
#include <string.h>


template<typename _T>
/**
* @brief ポインタ安全解放
*/
void SafeDelete(_T*& p)
{
	if (p != nullptr){
		delete(p);
		(p) = nullptr;
	}
}

template<typename _T>
/**
* @brief デバイス安全解放
*/
void SafeRelease(_T*& p)
{
	if (p != nullptr){
		p->Release();
		p = nullptr;
	}
}

#endif