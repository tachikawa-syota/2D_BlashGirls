#include "SmokeEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param 描画位置
*/
SmokeEffect::SmokeEffect(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_SMOKE);

	// 位置を設定
	m_obj.pos = pos;
	m_obj.scale = 0.0f;
	// 生存フレームを設定
	m_liveFrame = 30;
}

/**
* @brief 更新
*/
bool SmokeEffect::Update()
{
	m_obj.scale += 0.03f;

	if (m_obj.scale > 0.5f){
		m_obj.scale = 0.5f;
	}
	// 生存フレームを減算
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void SmokeEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale);
}