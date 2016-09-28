#include "PowerUpParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
* @param scale - 大きさ
* @param alpha - アルファ値
*/
PowerupParticle::PowerupParticle(const Vector2& pos, const float scale, const float alpha)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_RED_LIGHT);
	// 生存フレームの設定
	m_liveFrame = 120;
	m_obj.scale = scale;
	m_obj.pos = pos;
	m_v.x = static_cast<float>(rand() % 100 * 0.01 - 0.5);
	m_v.y = static_cast<float>(rand() % 100 * 0.01 + 0.7);
	m_obj.alpha = alpha;
}

/**
* @brief 更新
*/
bool PowerupParticle::Update()
{
	// 速度加算
	m_v.x = (float)(rand() % 255 - 128) / 32;
	m_v.y = -1.4f;

	// 縮小
	m_obj.scale -= 0.012f;

	// 座標更新
	m_obj.pos += m_v;

	// 生存フレーム更新
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void PowerupParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}