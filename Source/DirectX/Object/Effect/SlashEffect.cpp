#include "SlashEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param pos - 位置
* @param dir - 向き
* @param vel - 速度
* @param rot - 拡大速度(デフォルトは 0.0f)
* @param rot - 角度(デフォルトは 0.0f)
*/
SlashEffect::SlashEffect(const Vector2& pos, const Dir& dir, const Vector2& vel, const float scale, const float addScale, const float rot)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	m_obj.handle = m_texData->GetTexture(TEX_SLASH);

	// パラメータの設定
	m_obj.scale = scale;
	m_obj.pos = pos;
	m_obj.rot = rot;
	m_v.y = vel.y;
	m_obj.alpha = ALPHA_MAX;
	m_addScale = addScale;
	m_liveFrame = 20;

	// プレイヤーの向きに応じて反転させる
	if (dir == Dir::Right){
		m_v.x = vel.x;
		m_obj.isReverse = true;
	}
	else{
		m_obj.rot *= -1;
		m_v.x = -vel.x;
		m_obj.isReverse = false;
	}
}

/**
* @brief 更新
*/
bool SlashEffect::Update()
{
	//　スケールを加算
	m_obj.scale += m_addScale;

	// 速度を位置に加算する
	m_obj.pos += m_v;

	// 生存フレームを減算する
	m_liveFrame--;

	if (m_obj.scale < 0.0f || m_liveFrame < 0){
		// 削除する
		return true;
	}

	return false;
}

/**
* @brief 描画
*/
void SlashEffect::Render()
{
	m_2dTex->DrawTexture(m_obj.handle, m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true, m_obj.isReverse);
}