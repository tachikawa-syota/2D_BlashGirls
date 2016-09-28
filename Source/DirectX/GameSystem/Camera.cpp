// ----------------------------------------------------------------
//
//	�X�e�[�W��ɑ��݂���S�ẴI�u�W�F�N�g�ɃJ�������W��������
//
// ----------------------------------------------------------------


#include "Camera.h"

const float CAMERA_END_X = 553.0f;

/**
* @brief ������
*/
void Camera::Initialize()
{
	vx = 0;
}

/**
* @brief �X�V
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
* @brief �ړ�
*/
void Camera::Move()
{
	x += vx;
}

/**
* @brief ���S�_��ݒ肷��
*/
void Camera::SetCenterPoint(float pointX)
{
	x = pointX;
}
