#include "StarParticle.h"
#include "..\..\Common\Utility.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
* @param scale - 大きさ
* @param alpha - アルファ値
*/
StarParticle::StarParticle(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_STAR);

	// 各種パラメータの設定
	m_obj.scale = 1.2f;
	m_obj.pos = pos;
	m_obj.rot = 0.0f;
	m_v.x = Utility::Random(-4.0f, -1.0f);
	m_v.y = Utility::Random(2.0f, 6.0f);

	// 重力用
	m_add = { 0.0f, 0.03f };
	m_obj.alpha = ALPHA_MAX;

}

/**
* @brief 更新
*/
bool StarParticle::Update()
{
	// 回転させる
	m_obj.rot += 20.0f;

	// アルファ値を抜く
	m_obj.alpha -= 4;

	// 座標更新
	m_obj.pos += m_v;

	// 速度更新
	m_v += m_add;

	return (m_obj.alpha < ALPHA_MIN) ? true : false;
}

/**
* @brief 描画
*/
void StarParticle::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true);
}