#include "Direct3DData.h"

/**
* @brief D3DDevice‚Ìİ’è
*/
VOID Direct3DData::SetDevice(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
}

/**
* @brief D3DDevice‚ğæ“¾‚·‚é
*/
LPDIRECT3DDEVICE9 Direct3DData::GetDevice()
{
	return m_pDevice;
}