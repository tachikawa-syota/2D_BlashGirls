#include "SingletonOwner.h"

SingletonOwner::SingletonOwner()
{
}

SingletonOwner::~SingletonOwner()
{
}

/**
* @brief 初期化
*/
bool SingletonOwner::Initialize()
{
	// 入力デバイスの初期化と作成と設定
	m_deviceManager = DeviceManager::GetInstance();
	if (FAILED(m_deviceManager->Initialize())){
		return false;
	}
	if (FAILED(m_deviceManager->SetUp())){
		return false;
	}
	
	// グラフィックスの初期化
	m_graphicsManager = GraphicsManager::GetInstance();
	if (FAILED(m_graphicsManager->Initialize())){
		return false;
	}

	// サウンドの初期化
	m_soundPlayer = SoundPlayer::GetInstance();
	if (FAILED(m_soundPlayer->Initialize())){
		return false;
	}

	// テクスチャの読み込みを一括で行う
	m_textureData = TextureData::GetInstance();
	if (FAILED(m_textureData->LoadTexture())){
		return false;
	}

	// シーン切り替えの初期化
	m_sequenceChanger = SequenceChanger::GetInstance();
	m_sequenceChanger->Initialize();

	// スクリーンエフェクトの初期化
	m_screenEffect = ScreenEffect::GetInstance();
	m_screenEffect->Initialize();

	return true;
}