#include "LightEffect.h"
#include "..\..\Common\ParamLoader.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
* @param 描画位置
*/
LightEffect::LightEffect(const Vector2& pos)
{
	// インスタンスの取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// テクスチャコピー
	for (int i = 0; i < LIGHT_MAX; i++){
		hTex[i] = m_texData->GetLightTexture(i);
	}

	// 位置を設定
	m_obj.pos = pos;
	m_obj.scale = 0.0f;
	// 各種パラメータの初期化
	m_animFrame = 0;
	m_animation = 0;
}

/**
* @brief 更新
*/
bool LightEffect::Update()
{
	// 拡大する
	m_obj.scale++;
	// リミット
	if (m_obj.scale >= GetPrm->LightEffectMaxScale){
		m_obj.scale = 0.0f;
	}

	if (m_animFrame % 4 == 0){
		m_animation++;
	}

	// アニメーションフレームを加算
	m_animFrame++;

	return (m_animation >= LIGHT_MAX - 1) ? true : false;
}

/**
* @brief 描画
*/
void LightEffect::Render()
{
	m_2dTex->DrawTexture(hTex[m_animation], m_obj.pos.x - GetCameraPos, m_obj.pos.y, 0.0f, m_obj.scale);
}