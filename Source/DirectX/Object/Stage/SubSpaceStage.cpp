#include "SubSpaceStage.h"
#include "..\Particle\ParticleManager.h"
#include "..\Particle\StarParticle.h"
#include "..\..\GameSystem\Camera.h"

/**
* @brief コンストラクタ
*/
SubSpaceStage::SubSpaceStage()
{
	// インスタンスを取得
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	m_lightAlpha = ALPHA_MIN;
	m_stageAlpha = ALPHA_MAX;
	m_isEffectScale = false;
	m_effectScale = 0.0f;
}

/**
* @brief デストラクタ
*/
SubSpaceStage::~SubSpaceStage()
{
	SafeDelete(m_2dTex);
	SafeDelete(m_texData);
}

/**
* @brief 更新
*/
bool SubSpaceStage::Update()
{
	// 画面サイズから半分を引く
	float starPosX = static_cast<float>(rand() % 1280);

	// 背景に星パーティクルを生成する
	if (m_frame % 80 == 0){
		ParticleManager::GetInstance()->Add(make_shared<StarParticle>(Vector2(starPosX, -1.0f)));
	}

	// アルファ値をいじる（加算合成用）
	static float add;
	add += 0.02f;
	m_lightAlpha = static_cast<int>(sin(add) * ALPHA_MAX);

	// 経過フレームに応じて背景にエフェクト発生させる
	if (m_frame % 350 == 0){
		m_isEffectScale = true;
	}
	// 拡大
	if (m_isEffectScale){
		m_effectScale += 0.2f;
	}
	// 大きさ制御
	if (m_effectScale >= 10.0f){
		m_isEffectScale = false;
		m_effectScale = 0.0f;
	}

	// フレームを加算する
	m_frame++;

	// 削除しない(固定で返す)
	return false;
}

/**
* @brief 描画
*/
void SubSpaceStage::Render()
{
	// 背景
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG), 640.0f - GetCameraPos, 360.0f, 0.0f, 1.0f, m_stageAlpha);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_FROST), 630.0f - GetCameraPos, 280.0f, 0.0f, 1.5f, m_stageAlpha, true);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BLUE_RING), 640.0f - GetCameraPos, 360.0f, 0.0f, m_effectScale, m_stageAlpha, true);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG_SPHERE), 640.0f - GetCameraPos, 280.0f, 0.0f, 0.5f, m_stageAlpha);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT2), 640.0f - GetCameraPos, 280.0f, 0.0f, 2.5f, m_lightAlpha, true);
	// 床
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG_FLOOR), 640.0f - GetCameraPos, 656.0f, 0.0f, 1.0f, m_stageAlpha);
}

/**
* @brief アルファ値の変更(特殊スキルを使った時に背景を暗くする用で使う)
*/
void SubSpaceStage::ChangeAlpha(int alpha)
{
	m_stageAlpha = alpha;
}