#include "CutInManager.h"
#include "..\Object\Effect\EffectManager.h"
#include "..\Object\Effect\ShineEffect.h"

/**
* @brief 作成
* @param name - キャラクターの名前(Enum定義したものを使用する)
* @param index - キャラクターの番号
* @param pos - 描画する位置
*/
void CutInManager::Create(int name, int index, const Vector2& pos)
{
	// 表示フラグON
	m_isDisp = true;
	// フレーム初期化
	m_frame = NULL;
	// 光のエフェクトを生成
	EffectManager::GetInstance()->Add(make_shared<ShineEffect>(pos));
	// カットインの生成
	m_cutin = new CutIn(name, index);
}

/**
* @brief 初期化
*/
void CutInManager::Initialize()
{
	m_cutin = nullptr;
	m_isDisp = false;
	m_frame = NULL;
}

/**
* @brief 更新
*/
void CutInManager::Update()
{
	if (!m_isDisp) return;

	// 更新
	m_cutin->Update();

	// 一定フレーム経過で削除
	if (m_frame >= 45){
		delete m_cutin;
		m_isDisp = false;
	}

	// フレームを加算する
	m_frame++;
}

/**
* @brief 描画
*/
void CutInManager::Render()
{
	if (m_isDisp) m_cutin->Render();
}

/**
* @brief 表示中かどうかの確認
*/
bool CutInManager::IsPlayCutIn()
{
	return m_isDisp;
}