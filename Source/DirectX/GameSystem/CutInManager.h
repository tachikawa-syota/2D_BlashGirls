/**
* @file   CutInManager.h
* @brief  �J�b�g�C���̍쐬��`��Ȃǂ��Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___CUTINMANAGER_H
#define ___CUTINMANAGER_H

#include "CutIn.h"

/**
* @brief �J�b�g�C���̍쐬��`�擙���Ǘ�����N���X
*/
class CutInManager
{
public:
	/**
	* @brief �C���X�^���X���擾����(�V���O���g��)
	*/
	static CutInManager* GetInstance(){
		static CutInManager singlton;
		return &singlton;
	}

	/**
	* @brief �쐬
	* @param name - �L�����N�^�[�̖��O(Enum��`�������̂��g�p����)
	* @param index - �L�����N�^�[�̔ԍ�
	* @param pos - �`�悷��ʒu
	*/
	void Create(int name, int index, const Vector2& pos);

	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �\�������ǂ����̊m�F
	*/
	bool IsPlayCutIn();

private:
	/// �J�b�g�C��
	CutIn* m_cutin;

	/// �t���[��
	int m_frame;

	/// �\���t���O
	bool m_isDisp;
};

#endif