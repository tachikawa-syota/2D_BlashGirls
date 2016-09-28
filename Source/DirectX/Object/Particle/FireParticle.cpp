#include "FireParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
* @param scale - 大きさ
*/
FireParticle::FireParticle(const Vector2& pos, const float scale)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_FIRE_LIGHT);

	// パラメータの設定
	m_obj.scale = scale;
	m_obj.pos = pos;
	m_v.x = 0.0f;
	m_v.y = static_cast<float>((rand() % 100 * 0.04f - 0.5f));
	// 加速度は0
	m_add = {};
	m_obj.alpha = 255;
}

/**
* @brief 更新
*/
bool FireParticle::Update()
{
	m_obj.scale -= 0.018f;
	
	m_add.x = (float)(rand() % 256 - 128) / 256;
	m_add.y = -(float)(rand() % 128) / 256;

	// 座標更新
	m_obj.pos += m_v;

	// 速度更新
	m_v += m_add;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief 描画
*/
void FireParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}