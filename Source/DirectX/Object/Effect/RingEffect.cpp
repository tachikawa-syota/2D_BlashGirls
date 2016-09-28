#include "RingEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
*/
RingEffect::RingEffect(const Vector2& pos, const ARGB& color, const float addScale)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_RING);

	// パラメータの設定
	m_obj.scale = 0.0f;
	m_obj.pos = pos;
	m_liveFrame = 20;
	m_color = color;

	// 拡大速度
	m_addScale = addScale;

	m_obj.alpha = ALPHA_MAX;
}

/**
* @brief 更新
*/
bool RingEffect::Update()
{
	if (m_obj.scale >= 1.0f){
		m_color.red -= 25;
		m_color.blue -= 30;
	}
	if (m_color.alpha <= 0){
		m_color.alpha = 0;
	}

	// スケールを加算
	m_obj.scale += m_addScale;

	// 生存フレームを減算
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void RingEffect::Render()
{
	m_2dTex->DrawTexARGB(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_color, true, m_obj.rot, m_obj.scale);
}