/**
* @file Direct3DData.h
* @brief Direct3Dシステムデータの管理
* @author Syota Tachikawa
*/

#ifndef ___DIRECT3DDATA_H
#define ___DIRECT3DDATA_H

#include "..\Common\StdAfx.h"

/// インスタンスを取得
#define D3DIns Direct3DData::GetInstance()

/**
* @brief Direct3Dのデータを管理するクラス
*/
class Direct3DData
{
public:
	/**
	* @brief ゲットインスタンス
	*/
	static Direct3DData* GetInstance()
	{
		static Direct3DData singlton;
		return &singlton;
	}

	/**
	* @brief D3DDeviceの設定
	*/
	VOID SetDevice(LPDIRECT3DDEVICE9 pDevice);

	/**
	* @brief D3DDeviceを取得する
	*/
	LPDIRECT3DDEVICE9 GetDevice();

	/**
	* @brief デバイスオブジェクトを取得する
	*/
	D3DPRESENT_PARAMETERS& GetD3dpp();

private:
	/// D3DDeviceオブジェクト
	LPDIRECT3DDEVICE9 m_pDevice;

};

#endif