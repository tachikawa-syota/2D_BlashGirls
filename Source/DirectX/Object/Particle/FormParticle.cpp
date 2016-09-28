#include "FormParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
*/
FormParticle::FormParticle(const Vector2& pos, const float scale)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_FORM);

	// パラメータ設定
	m_obj.scale = scale;
	// 乱数で生成位置にズレを発生させる
	m_obj.pos.x = pos.x + Utility::Random(-20.0f, 20.0f);
	m_obj.pos.y = pos.y + Utility::Random(-20.0f, 20.0f);

	m_obj.alpha = ALPHA_MAX;

	// 速度の設定
	m_v.x = Utility::Random(-4.0f, 4.0f);
	m_v.y = Utility::Random(-4.0f, 4.0f);
}

/**
* @brief 更新
*/
bool FormParticle::Update()
{
	// 縮小
	m_obj.scale -= 0.008f;

	// アルファ値を引く
	m_obj.alpha -= 1;

	// 座標更新
	m_obj.pos += m_v;

	return (m_obj.scale < 0.0f) ? true : false;
}

/**
* @brief 描画
*/
void FormParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale, m_obj.alpha, true);
}