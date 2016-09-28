/**
* @file   myD3dlib.h
* @brief  DirectX�֌W��悭�g���}�N���Ȃǂ��Ǘ�
* @author Syota Tachikawa
* @date   11/27
*/

#ifndef ___MYD3DLIB_H
#define ___MYD3DLIB_H

// �x���}��
#pragma warning(disable:4819)

//�K�v�ȃ��C�u�����t�@�C���̃��[�h
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
// Input�֌W
#include <dinput.h>
// Sound�֌W
#include <mmsystem.h>
#include <process.h>
#include <ddraw.h>
#include <dsound.h>
#include <mmeapi.h>
#include <string.h>


template<typename _T>
/**
* @brief �|�C���^���S���
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
* @brief �f�o�C�X���S���
*/
void SafeRelease(_T*& p)
{
	if (p != nullptr){
		p->Release();
		p = nullptr;
	}
}

#endif