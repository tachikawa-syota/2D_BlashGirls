#include "HitParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 描画位置
* @param scale - 描画開始時の大きさ
*/
HitParticle::HitParticle(const Vector2& pos, const float scale)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	m_liveFrame = 30;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_HIT_EFFECT);

	// パラメータの設定
	m_obj.pos = pos;
	m_obj.scale = scale;
	m_obj.alpha = ALPHA_MAX;
	m_v.x = static_cast<float>((rand() % 255 - 128) / 16);
	m_v.y = static_cast<float>((rand() % 255 - 128) / 16);
}

/**
* @brief 更新
*/
bool HitParticle::Update()
{
	// 縮小
	m_obj.scale -= 0.006f;

	// アルファ値を引く
	m_obj.alpha -= 7;

	// 座標更新
	m_obj.pos += m_v * 0.65f;

	// 生存フレーム更新
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void HitParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}