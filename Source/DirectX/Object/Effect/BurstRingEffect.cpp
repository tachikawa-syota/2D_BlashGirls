#include "BurstRingEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
*/
BurstRingEffect::BurstRingEffect(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_BURST_RING);

	// パラメータの設定
	m_obj.scale = 0.0f;
	m_obj.pos = pos;

	m_liveFrame = 120;
	m_obj.scale = 0.0f;

	m_obj.alpha = ALPHA_MAX;
}

/**
* @brief 更新
*/
bool BurstRingEffect::Update()
{
	m_obj.scale += 0.2f;
	m_obj.alpha -= 5;

	// 生存フレームを減算
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void BurstRingEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}