/**
* @file   ConboCounter.h
* @brief  �R���{�����Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___COMBOCOUNTER_H
#define ___COMBOCOUNTER_H

#include "..\Common\StdAfx.h"

/**
* @brief �R���{�����Ǘ�����N���X
*/
class ComboCounter
{
public:
	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �R���{����`�悷��
	*/
	void Render();

	/**
	* @brief �R���{�����Z
	*/
	void Add(int plNum);

	/**
	* @brief �␳���ꂽ�_���[�W��Ԃ�
	*/
	float ComboDamageCorrection(float damage, int plNum);

	/**
	* @brief �w��v���C���[�̃R���{�����擾
	* @param index - �v���C���[�ԍ�
	*/
	int GetComboCount(int index);

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;

	/// �R���{��
	int comboCount[JOY_MAX];

	/// �P�t���[���O�̃R���{��
	int comboCountOld[JOY_MAX];

	/// �R���{�����t���[��
	int comboFrame[JOY_MAX];

	/// �R���{���P�̈�
	int comboOnesPlace[JOY_MAX];
	
	/// �R���{���P�O�̈�
	int comboTensPlace[JOY_MAX];

	/// �R���{���P�O�O�̈�
	int comboHundredsPlace[JOY_MAX];

	/// �����e�N�X�`���p
	int numberTex[NUMBER_MAX];

	/// �q�b�g�摜�`��ʒu
	float hitTexX[JOY_MAX];
	
	/// �����摜�`��ʒu
	float numberTexX[JOY_MAX];

	// �R���{���ɂ��_���[�W�␳�W��
	float correctionCoefficient[JOY_MAX];
};

#endif