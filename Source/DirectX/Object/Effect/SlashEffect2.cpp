#include "SlashEffect2.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
* @param dir - 向き
* @param vel - 速度
* @param rot - 拡大速度(デフォルトは 0.0f)
* @param rot - 角度(デフォルトは 0.0f)
*/
SlashEffect2::SlashEffect2(const Vector2& pos, const Dir& dir, const Vector2& vel, const float rot)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_SLASH4);

	// パラメータの設定
	m_obj.scale = 0.9f;
	m_obj.pos = pos;
	m_obj.rot = rot;
	m_v.y = vel.y;
	m_obj.alpha = ALPHA_MAX;
}

/**
* @brief 更新
*/
bool SlashEffect2::Update()
{
	// アルファ値を減算する
	m_obj.alpha -= 30;

	// 速度を位置に加算する
	m_obj.pos += m_v;

	// アルファ値が０以下で消去
	if (m_obj.alpha < 0){
		return true;
	}

	return false;
}

/**
* @brief 描画
*/
void SlashEffect2::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true, m_obj.isReverse);
}