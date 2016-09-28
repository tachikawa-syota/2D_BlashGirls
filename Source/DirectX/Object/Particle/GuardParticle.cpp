#include "GuardParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
* @param scale - 大きさ
*/
GuardParticle::GuardParticle(const Vector2& pos,
	const float scale
	)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_GUARD_EFFECT);
	// 生存フレームの設定
	m_liveFrame = 240;
	m_obj.scale = scale;
	m_obj.pos = pos;

	m_v.x = Utility::Random(-4.0f, 4.0f);
	m_v.y = Utility::Random(-4.0f, 4.0f);
	m_obj.alpha = 255;
}

/**
* @brief 更新
*/
bool GuardParticle::Update()
{
	// 速度加算
	m_obj.scale -= 0.02f;

	// 座標更新
	m_obj.pos += m_v;

	if (m_obj.scale < 0.0f)
		return true;

	if (m_liveFrame < 0)
		return true;

	if (m_obj.pos.y < 0.0f || m_obj.pos.y > 720.0f)
		return true;

	return false;
}

/**
* @brief 描画
*/
void GuardParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}