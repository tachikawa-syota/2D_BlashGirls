/**
* @file   Utility.h
* @brief  有用性のある処理を管理する
* @author Syota Tachikawa
*/

#ifndef ___UTILITY_H
#define ___UTILITY_H

#include "StdAfx.h"
#include <random>

/// ユーティリティクラス
class Utility
{
public:
	/// 文字列→数値
	template<class T>
	static T StringToNumber(const string& inStr)
	{
		try {
			stringstream ss(inStr);
			T n = 0;
			ss >> n;
			return n;
		}
		catch (...) {
			wcout << "例外 StringToNumber(" << inStr << ")" << endl;
			return 0;
		}
	}

	/// 数値→文字列
	template<class T>
	static string NumberToString(T inputNum)
	{
		try {
			std::stringstream ss;
			ss << inputNum;
			return ss.str();
		}
		catch (...) {
			wcout << "例外 NumberToString(" << inputNum << ")" << endl;
			return "";
		}
	}

	/// wcharから数字
	template<class T>
	static T CharToNumber(const wchar_t& inChar)
	{
		stringstream ss;
		ss << inChar;
		T n = 0;
		ss >> n;
		return n;
	}

	/// wcharから文字列
	static string CharToString(const wchar_t* s)
	{
		std::stringstream ss;
		ss << s;
		return ss.str();
	}

	/// char*からwchar_t*に変換
	static void convertCharPtrToWchar_tPtr(const char* message, wchar_t* wcharMsg)
	{
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcharMsg, strlen(message) + 1, message, _TRUNCATE);
	}

	/**
	* @brief 摩擦を返す
	* @param vx - ｘ速度
	* @param coefficient - 係数
	*/
	static float Friction(float vx, float coefficient)
	{
		float friction = vx * coefficient;

		return friction;
	}

	/**
	* @brief 2点の距離を測る（絶対値が返ってくる）
	* @param 計測対象オブジェクトの座標
	*/
	static float GetDistance(float posX1, float posX2)
	{
		float dist = posX1 - posX2;
		return abs(dist);
	}

	/**
	* @brief 整数型乱数を返す
	* @param min - 最小値
	* @param max - 最大値
	*/
	static int Random(int min, int max)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int> rad(min, max);
		int result = rad(mt);

		return result;
	}

	/**
	* @brief 浮動小数点乱数を返す
	* @param min - 最小値
	* @param max - 最大値
	*/
	static float Random(float min, float max)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<float> rad(min, max);
		float result = rad(mt);

		return result;
	}

	/**
	* @brief 跳ね返り
	* @param spd - 速度
	* @param IA - 衝撃吸収値（Impact absorptionの略）
	*/
	static float Rebound(float spd, float IA)
	{
		float result;
		result = spd * (-1) * IA;

		return result;
	}

	/// ダイアログボックスを表示しつつアプリを終了する
	static void abortWithMsg(char* msg)
	{
		MessageBox(NULL, msg, "意図しない終了", MB_OK | MB_ICONERROR);
		exit(0);
	}
};

#endif