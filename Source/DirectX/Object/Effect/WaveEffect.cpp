#include "WaveEffect.h"
#include "..\..\GameSystem\Camera.h"
#include "..\..\Common\ParamLoader.h"

/**
* @brief コンストラクタ
*/
WaveEffect::WaveEffect(const Vector2& pos, const Dir& dir)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	for (int i = 0; i < WAVE_MAX; i++){
		m_hTex[i] = m_texData->GetWaveTexture(i);
	}

	// 位置を設定
	m_obj.pos = pos;
	
	// キャラクターが左向きならテクスチャを反転させる
	if (dir == Dir::Right){
		m_obj.pos.x -= 80.0f;
		m_obj.isReverse = false;
	}
	else{
		m_obj.pos.x += 80.0f;
		m_obj.isReverse = true;
	}
	// 座標を補正する
	m_obj.pos.y += 80.0f;

	// 各種カウンターの初期化
	loopCount = 0;
	m_animFrame = 0;
	m_animation = 0;
}

/**
* @brief 更新
*/
bool WaveEffect::Update()
{
	if (m_animFrame % 5 == 0)
	{
		m_animation++;
		if (m_animation >= GetPrm->WaveEffectMaxAnimation){
			m_animation = 0;
			loopCount++;
		}
	}

	// アニメーションフレームを加算
	m_animFrame++;

	return (loopCount > 2) ? true : false;
}

/**
* @brief 描画
*/
void WaveEffect::Render()
{
	m_2dTex->DrawTexture(m_hTex[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, 1.0f, ALPHA_MAX, false, m_obj.isReverse);
}