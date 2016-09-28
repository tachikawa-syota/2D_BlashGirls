#include "SpecialHitParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
*/
SpecialHitParticle::SpecialHitParticle(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_GUARD_EFFECT); // ﾃｸｽﾁｬ使い回し

	// パラメータ設定
	m_obj.scale = Utility::Random(0.2f, 0.6f);
	// 乱数で生成位置にズレを発生させる
	m_obj.pos.x = pos.x + Utility::Random(-20.0f, 20.0f);
	m_obj.pos.y = pos.y + Utility::Random(-20.0f, 20.0f);
	
	// アルファ値の設定
	m_obj.alpha = ALPHA_MAX;

	// 速度の設定
	m_v.x = Utility::Random(-5.0f, 5.0f);
	m_v.y = Utility::Random(-5.0f, 5.0f);
}

/**
* @brief 更新
*/
bool SpecialHitParticle::Update()
{
	m_obj.scale -= 0.008f;

	// 座標更新
	m_obj.pos += m_v;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief 描画
*/
void SpecialHitParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha);
}