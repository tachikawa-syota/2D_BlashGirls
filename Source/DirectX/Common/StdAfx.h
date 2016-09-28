/**
* @file   StdAfx.h
* @brief  �v���R���p�C���ς݃w�b�_
* @author Syota Tachikawa
*/

#ifndef ___STDAFX_H
#define ___STDAFX_H

// ------------------------------------------------------------------------
// std�L�q���ȗ�����
using namespace std;
// ------------------------------------------------------------------------
#define STRICT               // �^�`�F�b�N�������ɍs��
#define WIN32_LEAN_AND_MEAN  // �w�b�_�[���炠�܂�g���Ȃ��֐�������
// new �ɂ�郁�������[�N���o��CPP�t�@�C�����ƍs���o�͎w��
//���������[�N�������Ƀf�o�b�K�ɏo�͂�����e���킩��₷������
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC                            // malloc�ɂ�郁�������[�N���o��CPP�t�@�C�����ƍs���o�͎w��
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)  // new �ɂ�郁�������[�N���o��CPP�t�@�C�����ƍs���o�͎w��
#else
#define NEW  new
#endif
// ------------------------------------------------------------------------

#include <stdio.h>
#include <time.h>
#include <crtdbg.h>
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <cstdint>
#include <string>
#include <sstream>
#include <list>
#include <memory>
#include <map>
#include <array>
#include <random>

// DirectXLib���Ǘ�
#include "..\DirectX\myD3dlib.h"
// �A�v���P�[�V�����V�X�e��
#include "..\ApplicationSystem\ApplicationData.h"
#include "..\ApplicationSystem\WindowsApplication.h"
#include "..\ApplicationSystem\FPSCounter.h"
#include "..\DirectX\Direct3DData.h"
#include "..\DirectX\Direct3DSystem.h"
// �O���t�B�b�N�X�֌W
#include "..\DirectX\GraphicsLib.h"
// �C���v�b�g
#include "..\DirectX\InputLib.h"
#include "..\DirectX\Font.h"
// �T�E���h
#include "..\DirectX\DirectSound.h"
// �萔
#include "Define.h"
#include "StringDefine.h"
#include "Enum.h"
// �\����
#include "Struct.h"
// �X�N���[���G�t�F�N�g
#include "..\Common\ScreanEffect.h"
// �f�[�^�Ǘ�
#include "FileData.h"

template<typename _T, typename T_>
T_ New(_T p)
{
	return make_unique<p>;
}

#endif