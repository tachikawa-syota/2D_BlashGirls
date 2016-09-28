#include "ComboCounter.h"
#include "..\Common\ParamLoader.h"

/**
* @brief ������
*/
void ComboCounter::Initialize()
{
	// �C���X�^���X�̎擾
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// ���W�̐ݒ�
	hitTexX[PLAYER1] = GetPrm->HitFontPlayer1X;
	hitTexX[PLAYER2] = GetPrm->HitFontPlayer2X;
	numberTexX[PLAYER1] = GetPrm->NumberFontPlayer1X;
	numberTexX[PLAYER2] = GetPrm->NumberFontPlayer2X;

	// �����e�N�X�`���̃R�s�[
	for (int i = 0; i < NUMBER_MAX; i++){
		numberTex[i] = m_texData->GetNumberTexture(i);
	}

	// �p�����[�^�̏�����
	for (int i = 0; i < JOY_MAX; i++)
	{
		comboFrame[i] = 0;
		comboCount[i] = 0;
		comboCountOld[i] = 0;
		comboOnesPlace[i] = 0;
		comboTensPlace[i] = 0;
		comboHundredsPlace[i] = 0;
		correctionCoefficient[i] = 1.0f;
	}
}

/**
* @brief �X�V
*/
void ComboCounter::Update()
{		
	for (int i = 0; i < JOY_MAX; i++)
	{
		// �O�t���[���ƌ��݂̃t���[���ŃR���{���������Ȃ�
		if (comboCountOld[i] == comboCount[i]){
			// �R���{�t���[�������Z
			comboFrame[i]++;
		}
		else{
			// ����ȊO�Ȃ�0������
			comboFrame[i] = 0;
		}

		// �R���{�t���[����60�t���[�����z�����u�ԏ���������
		if (comboFrame[i] >= GetPrm->ComboFrameLimit)
		{
			comboCount[i] = 0;
			comboOnesPlace[i] = 0;
			comboTensPlace[i] = 0;
			comboHundredsPlace[i] = 0;
			correctionCoefficient[i] = 1.0f;
		}

		// 1�̈ʂ�9�𒴂�����10�̈ʂ𑫂�
		if (comboOnesPlace[i] > 9)
		{
			comboOnesPlace[i] = 0;
			comboTensPlace[i]++;
		}
		// 10�̈ʂ�9�𒴂�����100�̈ʂ𑫂�
		if (comboTensPlace[i] > 9)
		{
			comboTensPlace[i] = 0;
			comboHundredsPlace[i]++;
		}

		// �R���{�ő吔��999
		if (comboOnesPlace[i] == 9 && comboTensPlace[i] == 9 && comboHundredsPlace[i] == 9)
		{
			comboOnesPlace[i] = 9;
			comboTensPlace[i] = 9;
			comboHundredsPlace[i] = 9;
		}

		// �R���{����5�𒴂�����
		if (comboCount[i] > 5)
		{
			// �_���[�W�␳��������
			correctionCoefficient[i] -= GetPrm->ComboCorrectionCoefficient;
		}

		// �␳�l�͔�����艺����Ȃ�
		if (correctionCoefficient[i] < GetPrm->ComboCorrectionCoefficientLimit)
			correctionCoefficient[i] = GetPrm->ComboCorrectionCoefficientLimit;
	
		// ���݂̃R���{�����L�^����
		comboCountOld[i] = comboCount[i];
	}
}

/**
* @brief �R���{����`�悷��
*/
void ComboCounter::Render()
{
	for (int i = 0; i < JOY_MAX; i++)
	{
		// �R���{�����P�ȏゾ������
		if (comboCount[i] > 0)
		{
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_HITS_FONT), hitTexX[i], 200.0f, 0.0f, 1.1f);
			m_2dTex->DrawTexture(numberTex[comboOnesPlace[i]], numberTexX[i], 200.0f);
			
			// 10�̈ʂ�0�ȏ�܂���100�̈ʂ�0�ȏ�Ȃ�\������
			if (comboTensPlace[i] > 0 || comboHundredsPlace[i] > 0)
				m_2dTex->DrawTexture(numberTex[comboTensPlace[i]], numberTexX[i] - 60.0f, 200.0f);

			// 100�̈ʂɐ�������������
			if (comboHundredsPlace[i] > 0)
				m_2dTex->DrawTexture(numberTex[comboHundredsPlace[i]], numberTexX[i] - 120, 200.0f);
		}
	}
}

/**
* @brief �R���{�������Z
* @param plNum - �v���C���[�ԍ�
*/
void ComboCounter::Add(int plNum)
{
	comboCount[plNum]++;
	comboOnesPlace[plNum]++;
}

/**
* @brief �R���{���ɂ��_���[�W�␳���ꂽ�l��Ԃ�
* @param damage - �ʏ펞�̃_���[�W���擾
* @param plNum - �v���C���[�ԍ�
*/
float ComboCounter::ComboDamageCorrection(float damage, int plNum)
{
	float value;

	value = damage * correctionCoefficient[plNum];

	return value;
}

/**
* @brief Player1�̃R���{�����擾
* @param index - �v���C���[�ԍ�
*/
int ComboCounter::GetComboCount(int index)
{
	return 	comboCount[index];
}