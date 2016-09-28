#include "FlushEffect.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param 描画位置
*/
FlushEffect::FlushEffect(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_FLUSH);

	// 位置を設定
	m_obj.pos = pos;
	m_obj.scale = 0.0f;
	m_liveFrame = 30;
}

/**
* @brief 更新
*/
bool FlushEffect::Update()
{
	// スケールを拡大
	m_obj.scale += GetPrm->FlushEffectAddScale;
	
	if (m_obj.scale > GetPrm->FlushEffectMaxScale){
		m_obj.scale = GetPrm->FlushEffectMaxScale;
	}

	// 生存フレームを減算
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void FlushEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale);
}