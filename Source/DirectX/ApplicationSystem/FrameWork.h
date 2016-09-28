/**
* @file   FrameWork.h
* @brief  フレームワーク
* @author Syota Tachikawa
*/

#ifndef ___FRAMEWORK_H
#define ___FRAMEWORK_H

#include "..\Common\StdAfx.h"
#include "..\Common\SingletonOwner.h"

/**
* @brief フレームワーククラス
*/
class FrameWork
{
public:
	/**
	* @brief コンストラクタ
	*/
	FrameWork();
	
	/**
	* @brief デストラクタ
	*/
	~FrameWork();

	/**
	* @brief 作成
	* @param インスタンス
	* @return true - 成功：false - 失敗
	*/
	bool Create(HINSTANCE hInst);

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief 更新と描画
	*/
	void Run();

private:
	/// アプリケーションシステム
	unique_ptr<WindowsApplication> pSys;

	/// D3Dシステム
	unique_ptr<Direct3DSystem> pD3d;

	/// シーン
	ISequence* m_nowScene;

	/// シングルトンオーナー
	unique_ptr<SingletonOwner> m_singletonOwner;

	/// フォント
	unique_ptr<Font> m_font;

	/// サウンドデータ
	unique_ptr<SoundData> m_soundData;

	/// FPSカウンター
	unique_ptr<FPSCounter> m_fpsCounter;

	/**
	* @brief 画面クリア
	*/
	BOOL HCls();

	/**
	* @brief フリッピング
	*/
	BOOL Flip();

	/**
	* @brief FPSの表示
	*/
	VOID RenderFPS();
};



#endif