#include "GuardEffect.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 描画位置
* @param dir - 描画向き
*/
GuardEffect::GuardEffect(const Vector2& pos, const Dir& dir)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_GUARD);

	// 位置を設定
	m_obj.pos = pos;

	if (dir == Dir::Left){
		m_obj.pos.x -= 50.0f;
		m_obj.isReverse = true;
	}else{
		m_obj.pos.x += 50.0f;
		m_obj.isReverse = false;
	}
	m_obj.scale = 0.0f;
	m_v = {};
	m_liveFrame = 10;
}

/**
* @brief 更新
*/
bool GuardEffect::Update()
{
	// 拡大していく
	m_obj.scale += GetPrm->GuardEffectAddScale;

	if (m_obj.scale > GetPrm->GuardEffectMaxScale){
		m_obj.scale = GetPrm->GuardEffectMaxScale;
	}

	// 生存フレームを減産
	m_liveFrame--;

	return (m_liveFrame < 0) ? true : false;
}

/**
* @brief 描画
*/
void GuardEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, 200, false, m_obj.isReverse);
}