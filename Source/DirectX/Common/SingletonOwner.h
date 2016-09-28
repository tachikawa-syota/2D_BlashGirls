/**
* @file   SingletonOwner.h
* @brief  シングルトンをまとめて管理する
* @author Syota Tachikawa
*/

#ifndef ___SINGLETONOWNER_H
#define ___SINGLETONOWNER_H

#include "..\DirectX\DeviceManager.h"
#include "..\DirectX\GraphicsLib.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\FileData.h"
#include "..\Sequence\SequenceChanger.h"

/**
* @brief シングルトンをまとめて管理するクラス
*/
class SingletonOwner
{
public:
	/**
	* @brief コンストラクタ
	*/
	SingletonOwner();
	
	/**
	* @brief デストラクタ
	*/
	~SingletonOwner();

	/**
	* @brief 初期化
	*/
	bool Initialize();

private:
	/// デバイス
	DeviceManager* m_deviceManager;

	/// グラフィックス
	GraphicsManager* m_graphicsManager;

	/// サウンド
	SoundPlayer* m_soundPlayer;
	
	/// テクスチャデータ
	TextureData* m_textureData;

	/// シーンチェンジャー
	SequenceChanger* m_sequenceChanger;

	/// スクリーンエフェクト
	ScreenEffect* m_screenEffect;
};

#endif