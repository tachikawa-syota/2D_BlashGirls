
#include "Collide.h"

/**
* @brief ��`�Ƌ�`�̓����蔻����`�F�b�N����
* @param obj - �I�u�W�F�N�g�̈ʒu
* @param rec - �I�u�W�F�N�g�̓�����͈�
* @return true - ���������Afalse - �������Ă��Ȃ�
*
* @note �g�����Fobj1��rec1�ɂ͓����I�u�W�F�N�g�̃p�����[�^������iobj2��rec2���R��j
*				�I�u�W�F�N�g�̏��Ԃ͋t�ɂ��Ă����ʂ͕ς��Ȃ�
*/
bool Collide::CheckRectAndRect(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2)
{
	float obj1left = rec1.right / 2.0f;
	float obj2left = rec2.right / 2.0f;
	float obj1top = rec1.bottom / 2.0f;
	float obj2top = rec2.bottom / 2.0f;

	if (obj2.x - obj2left + rec2.right >= obj1.x - obj1left && obj2.x - obj2left <= obj1.x - obj1left + rec1.right)
	{
		if ((obj2.y - obj2top) + rec2.bottom >= (obj1.y - obj1top) && (obj2.y - obj2top) <= (obj1.y - obj1top) + rec1.bottom)
		{
			return true;
		}
	}
	return false;
}

/**
* @brief �d�Ȃ������������E�ɃY����
* @param obj - �I�u�W�F�N�g�̈ʒu
* @param rec - �I�u�W�F�N�g�̓�����͈�
* @param dir - �I�u�W�F�N�g�̌���
*/
float Collide::PlayerDisplace(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2, Dir& dir)
{
	float ret;
	float obj1left = rec1.right / 2.0f;
	float obj2left = rec2.right / 2.0f;

	// 1P�̉E�[��2P�̍��[
	if (obj1.x - obj1left + rec1.right < obj2.x - obj2left + 5.0f)
	{
		ret = -15.0f;
	}
	// 2P�̉E�[��1P�̍��[
	if (obj2.x - obj2left + rec2.right < obj1.x - obj1left + 5.0f)
	{
		ret = 15.0f;
	}
	// �d�Ȃ�����
	if (obj1.x == obj2.x)
	{
		ret = 15.0f;
	}
	// ��O����
	else{
		// �E
		if (dir == Dir::Right)
			ret = -15.0f;
		// ��
		else
			ret = 15.0f;
	}

	return ret;
}