#include "SwordTrajectoryEffect.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param texid - テクスチャの番号
* @param pos   - 位置
* @param dir   - 向き
* @param rot   - 角度(軌跡の角度を弄りたい時は数値を入れる。デフォルトは0.0f)
*/
SwordTrajectoryEffect::SwordTrajectoryEffect(const int texid, const Vector2& pos, const Dir& dir, const float rot)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	// テクスチャコピー
	for (int i = 0; i < SLASH_MAX; i++){
		hTex[i] = m_texData->GetSlashTexture(i);
	}

	// 位置を設定
	m_obj.pos = pos;
	m_obj.alpha = ALPHA_MAX;
	m_obj.rot = rot;
	m_obj.scale = 0.0f;

	m_id = texid;

	if (dir == Dir::Left){
		m_obj.pos.x -= 50.0f;
		m_obj.isReverse = true;
	}
	else{
		m_obj.pos.x += 50.0f;
		m_obj.isReverse = false;
	}
}

/**
* @brief 更新
*/
bool SwordTrajectoryEffect::Update()
{
	// 拡大していく
	m_obj.scale += 0.07f;
	//　アルファ値を抜く
	m_obj.alpha -= 10;

	if (m_obj.scale > 1.15f){
		m_obj.scale = 1.15f;
	}

	return (m_obj.alpha < 0) ? true : false;
}

/**
* @brief 描画
*/
void SwordTrajectoryEffect::Render()
{
	m_2dTex->DrawTexture(hTex[m_id], m_obj.pos.x - GetCameraPos, m_obj.pos.y, m_obj.rot, m_obj.scale, m_obj.alpha, true, m_obj.isReverse);
}