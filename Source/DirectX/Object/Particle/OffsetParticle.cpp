#include "OffsetParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
*/
OffsetParticle::OffsetParticle(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_OFFSET);

	// パラメータ設定
	m_obj.scale = 0.4f;
	// 乱数で生成位置にズレを発生させる
	m_obj.pos.x = pos.x + Utility::Random(-20.0f, 20.0f);
	m_obj.pos.y = pos.y + Utility::Random(-20.0f, 20.0f);

	m_obj.alpha = ALPHA_MAX;

	// 速度の設定
	m_v.x = Utility::Random(-5.0f, 5.0f);
	m_v.y = Utility::Random(-5.0f, 5.0f);
	// ０初期化
	m_add = {};
}

/**
* @brief 更新
*/
bool OffsetParticle::Update()
{
	// 加速度設定
	m_add.y = 0.3f;

	// 縮小
	m_obj.scale -= 0.008f;

	// 座標更新
	m_obj.pos += m_v;
	// 速度更新
	m_v += m_add;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief 描画
*/
void OffsetParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}