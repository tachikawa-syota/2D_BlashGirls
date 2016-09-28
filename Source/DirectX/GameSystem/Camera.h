/**
* @file   Camera.h
* @brief  メインゲームで使用するカメラ処理
* @author Syota Tachikawa
*/

#ifndef ___CAMERA_H
#define ___CAMERA_H

#include "..\Common\StdAfx.h"

/// インスタンスの取得を定義
#define GetCameraPos Camera::GetInstance()->GetPos()

#define CAMERA_END_RIGHT 1080
#define CAMERA_END_LEFT 200

/**
* @brief メインゲームで使用するカメラクラス
*/
class Camera
{
public:
	/**
	* @brief インスタンスの取得(シングルトン)
	*/
	static Camera* GetInstance(){
		static Camera singleton;
		return &singleton;
	}

	/**
	* @brief 初期化
	*/
	void Initialize();

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 中心点を設定する
	*/
	void SetCenterPoint(float pointX);

	/**
	* @brief 座標取得
	*/
	float GetPos(){ return x; }

private:
	/// 座標
	float x, oldX;
	float vx;

	/**
	* @brief 移動
	*/
	void Move();

};

#endif