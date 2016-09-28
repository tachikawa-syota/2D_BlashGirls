/**
* @file   Camera.h
* @brief  ���C���Q�[���Ŏg�p����J��������
* @author Syota Tachikawa
*/

#ifndef ___CAMERA_H
#define ___CAMERA_H

#include "..\Common\StdAfx.h"

/// �C���X�^���X�̎擾���`
#define GetCameraPos Camera::GetInstance()->GetPos()

#define CAMERA_END_RIGHT 1080
#define CAMERA_END_LEFT 200

/**
* @brief ���C���Q�[���Ŏg�p����J�����N���X
*/
class Camera
{
public:
	/**
	* @brief �C���X�^���X�̎擾(�V���O���g��)
	*/
	static Camera* GetInstance(){
		static Camera singleton;
		return &singleton;
	}

	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief ���S�_��ݒ肷��
	*/
	void SetCenterPoint(float pointX);

	/**
	* @brief ���W�擾
	*/
	float GetPos(){ return x; }

private:
	/// ���W
	float x, oldX;
	float vx;

	/**
	* @brief �ړ�
	*/
	void Move();

};

#endif