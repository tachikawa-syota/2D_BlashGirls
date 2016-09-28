/**
* @file Collide.h
* @brief 当たり判定処理を管理
* @author Syota Tachikawa
* @date 12/13
*/

#ifndef ___COLLIDE_H
#define ___COLLIDE_H

#include "..\Common\StdAfx.h"
#include "..\Common\Struct.h"

/**
* @brief 当たり判定クラス
*/
class Collide
{
public:
	/**
	* @brief 矩形と矩形の当たり判定をチェックする
	* @param obj - オブジェクトの位置
	* @param rec - オブジェクトの当たり範囲
	* @return true - 当たった、false - 当たっていない
	*
	* @note 使い方：obj1とrec1には同じオブジェクトのパラメータを入れる（obj2とrec2も然り）
	*				オブジェクトの順番は逆にしても結果は変わらない
	*/
	static bool CheckRectAndRect(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2);

	/**
	* @brief 重なった分だけ左右にズラす
	* @param obj - オブジェクトの位置
	* @param rec - オブジェクトの当たり範囲
	* @param dir - オブジェクトの向き
	*/
	static float PlayerDisplace(Vector2 obj1, Vector2 obj2, Rect rec1, Rect rec2, Dir& dir);
};

#endif