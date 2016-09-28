/**
* @file   StdAfx.h
* @brief  プリコンパイル済みヘッダ
* @author Syota Tachikawa
*/

#ifndef ___STDAFX_H
#define ___STDAFX_H

// ------------------------------------------------------------------------
// std記述を省略する
using namespace std;
// ------------------------------------------------------------------------
#define STRICT               // 型チェックを厳密に行う
#define WIN32_LEAN_AND_MEAN  // ヘッダーからあまり使われない関数を除く
// new によるメモリリーク検出でCPPファイル名と行数出力指定
//メモリリーク発生時にデバッガに出力する内容をわかりやすくする
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC                            // mallocによるメモリリーク検出でCPPファイル名と行数出力指定
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)  // new によるメモリリーク検出でCPPファイル名と行数出力指定
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

// DirectXLibを管理
#include "..\DirectX\myD3dlib.h"
// アプリケーションシステム
#include "..\ApplicationSystem\ApplicationData.h"
#include "..\ApplicationSystem\WindowsApplication.h"
#include "..\ApplicationSystem\FPSCounter.h"
#include "..\DirectX\Direct3DData.h"
#include "..\DirectX\Direct3DSystem.h"
// グラフィックス関係
#include "..\DirectX\GraphicsLib.h"
// インプット
#include "..\DirectX\InputLib.h"
#include "..\DirectX\Font.h"
// サウンド
#include "..\DirectX\DirectSound.h"
// 定数
#include "Define.h"
#include "StringDefine.h"
#include "Enum.h"
// 構造体
#include "Struct.h"
// スクリーンエフェクト
#include "..\Common\ScreanEffect.h"
// データ管理
#include "FileData.h"

template<typename _T, typename T_>
T_ New(_T p)
{
	return make_unique<p>;
}

#endif