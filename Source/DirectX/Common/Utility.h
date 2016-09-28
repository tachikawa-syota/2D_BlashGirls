/**
* @file   Utility.h
* @brief  �L�p���̂��鏈�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___UTILITY_H
#define ___UTILITY_H

#include "StdAfx.h"
#include <random>

/// ���[�e�B���e�B�N���X
class Utility
{
public:
	/// �����񁨐��l
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
			wcout << "��O StringToNumber(" << inStr << ")" << endl;
			return 0;
		}
	}

	/// ���l��������
	template<class T>
	static string NumberToString(T inputNum)
	{
		try {
			std::stringstream ss;
			ss << inputNum;
			return ss.str();
		}
		catch (...) {
			wcout << "��O NumberToString(" << inputNum << ")" << endl;
			return "";
		}
	}

	/// wchar���琔��
	template<class T>
	static T CharToNumber(const wchar_t& inChar)
	{
		stringstream ss;
		ss << inChar;
		T n = 0;
		ss >> n;
		return n;
	}

	/// wchar���當����
	static string CharToString(const wchar_t* s)
	{
		std::stringstream ss;
		ss << s;
		return ss.str();
	}

	/// char*����wchar_t*�ɕϊ�
	static void convertCharPtrToWchar_tPtr(const char* message, wchar_t* wcharMsg)
	{
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcharMsg, strlen(message) + 1, message, _TRUNCATE);
	}

	/**
	* @brief ���C��Ԃ�
	* @param vx - �����x
	* @param coefficient - �W��
	*/
	static float Friction(float vx, float coefficient)
	{
		float friction = vx * coefficient;

		return friction;
	}

	/**
	* @brief 2�_�̋����𑪂�i��Βl���Ԃ��Ă���j
	* @param �v���ΏۃI�u�W�F�N�g�̍��W
	*/
	static float GetDistance(float posX1, float posX2)
	{
		float dist = posX1 - posX2;
		return abs(dist);
	}

	/**
	* @brief �����^������Ԃ�
	* @param min - �ŏ��l
	* @param max - �ő�l
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
	* @brief ���������_������Ԃ�
	* @param min - �ŏ��l
	* @param max - �ő�l
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
	* @brief ���˕Ԃ�
	* @param spd - ���x
	* @param IA - �Ռ��z���l�iImpact absorption�̗��j
	*/
	static float Rebound(float spd, float IA)
	{
		float result;
		result = spd * (-1) * IA;

		return result;
	}

	/// �_�C�A���O�{�b�N�X��\�����A�v�����I������
	static void abortWithMsg(char* msg)
	{
		MessageBox(NULL, msg, "�Ӑ}���Ȃ��I��", MB_OK | MB_ICONERROR);
		exit(0);
	}
};

#endif