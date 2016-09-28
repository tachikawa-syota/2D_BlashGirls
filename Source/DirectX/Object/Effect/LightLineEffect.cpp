#include "LightLineEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param 描画位置
*/
LightLineEffect::LightLineEffect(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_LINE);

	// 位置を設定
	m_obj.pos = pos;
	m_v = {};
	m_liveFrame = 4;
}

/**
* @brief 更新
*/
bool LightLineEffect::Update()
{
	m_v.y -= 10.0f;

	// 位置に速度を加算する
	m_obj.pos += m_v;

	// 生存フレームを減算
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void LightLineEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, 0.5f, ALPHA_MAX, true);
}