/**
* @file Collide.h
* @brief �����蔻�菈�����Ǘ�
* @author Syota Tachikawa
* @date 12/13
*/

#ifndef ___COLLIDE_H
#define ___COLLIDE_H

#include "..\Common\StdAfx.h"
#include "..\Common\Struct.h"

/**
* @brief �����蔻��N���X
*/
class Collide
{
public:
	/**
	* @brief ��`�Ƌ�`�̓����蔻����`�F�b�N����
	* @param obj - �I�u�W�F�N�g�̈ʒu
	* @param rec - �I�u�W�F�N�g�̓�����͈�
	* @return true - ���������Afalse - �������Ă��Ȃ�
	*
	* @note �g�����Fobj1��rec1�ɂ͓����I�u�W�F�N�g�̃p�����[�^������iobj2��rec2���R��j
	*				�I�u�W�F�N�g�̏��Ԃ͋t�ɂ��Ă����ʂ͕ς��Ȃ�
	*/
	static bool CheckRectAndRect(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2);

	/**
	* @brief �d�Ȃ������������E�ɃY����
	* @param obj - �I�u�W�F�N�g�̈ʒu
	* @param rec - �I�u�W�F�N�g�̓�����͈�
	* @param dir - �I�u�W�F�N�g�̌���
	*/
	static float PlayerDisplace(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2, Dir& dir);
};

#endif