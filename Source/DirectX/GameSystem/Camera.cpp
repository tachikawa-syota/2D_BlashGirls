// ----------------------------------------------------------------
//
//	ステージ上に存在する全てのオブジェクトにカメラ座標を加える
//
// ----------------------------------------------------------------


#include "Camera.h"

const float CAMERA_END_X = 553.0f;

/**
* @brief 初期化
*/
void Camera::Initialize()
{
	vx = 0;
}

/**
* @brief 更新
*/
void Camera::Update()
{
	if (-CAMERA_END_X >= x || CAMERA_END_X <= x){ 
		x = oldX; 
	}

	Move();

	oldX = x;
}

/**
* @brief 移動
*/
void Camera::Move()
{
	x += vx;
}

/**
* @brief 中心点を設定する
*/
void Camera::SetCenterPoint(float pointX)
{
	x = pointX;
}
