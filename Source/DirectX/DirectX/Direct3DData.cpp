#include "Direct3DData.h"

/**
* @brief D3DDevice�̐ݒ�
*/
VOID Direct3DData::SetDevice(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
}

/**
* @brief D3DDevice���擾����
*/
LPDIRECT3DDEVICE9 Direct3DData::GetDevice()
{
	return m_pDevice;
}