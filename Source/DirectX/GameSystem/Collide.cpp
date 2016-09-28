
#include "Collide.h"

/**
* @brief 矩形と矩形の当たり判定をチェックする
* @param obj - オブジェクトの位置
* @param rec - オブジェクトの当たり範囲
* @return true - 当たった、false - 当たっていない
*
* @note 使い方：obj1とrec1には同じオブジェクトのパラメータを入れる（obj2とrec2も然り）
*				オブジェクトの順番は逆にしても結果は変わらない
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
* @brief 重なった分だけ左右にズラす
* @param obj - オブジェクトの位置
* @param rec - オブジェクトの当たり範囲
* @param dir - オブジェクトの向き
*/
float Collide::PlayerDisplace(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2, Dir& dir)
{
	float ret;
	float obj1left = rec1.right / 2.0f;
	float obj2left = rec2.right / 2.0f;

	// 1Pの右端と2Pの左端
	if (obj1.x - obj1left + rec1.right < obj2.x - obj2left + 5.0f)
	{
		ret = -15.0f;
	}
	// 2Pの右端と1Pの左端
	if (obj2.x - obj2left + rec2.right < obj1.x - obj1left + 5.0f)
	{
		ret = 15.0f;
	}
	// 重なったら
	if (obj1.x == obj2.x)
	{
		ret = 15.0f;
	}
	// 例外処理
	else{
		// 右
		if (dir == Dir::Right)
			ret = -15.0f;
		// 左
		else
			ret = 15.0f;
	}

	return ret;
}