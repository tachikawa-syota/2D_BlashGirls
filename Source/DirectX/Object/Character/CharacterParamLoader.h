#ifndef ___CHARACTERPARAMLOADER_H
#define ___CHARACTERPARAMLOADER_H

#include "..\..\iniFileLoader\iniFileLoaderBase.h"

// �C���X�^���X�擾
#define GetChrPrm CharacterParamLoader::GetInstance()

/**
* @brief ini�t�@�C���ŊǗ����Ă���L�����N�^�[�p�����[�^�[��ǂݍ��ރN���X
*/
class CharacterParamLoader : public iniFileLoaderBase
{
public:
	static CharacterParamLoader* GetInstance(){
		static CharacterParamLoader singleton;
		return &singleton;
	}

	// �S�L�����N�^�[���ʂ̃p�����[�^-----------------------
	float PlayerGuardNowSpeed;

	// �����A(�U���͂����߁E�X�s�[�h��x�߂ɐݒ�)-----------------------------------------------

	/// �O�i���x
	float LiliaAdvanceSpeed;

	/// �K�[�h���x
	float LiliaGuardSpeed;

	/// �_�b�V�����x
	float LiliaDashSpeed;

	/// �o�b�N�X�e�b�v���x
	float LiliaBackStepSpeed;

	/// ���U���g�p���̑��x
	float LiliaAttackStrongSpeed;

	/// �K�E�Z�ǌ��̑��x
	float LiliaAttackSpecialPursuitSpeed;

	/// ��U���̍U����
	float LiliaAttackWeakPower;

	/// �W�����v�U���̍U����
	float LiliaAttackJumpPower;

	/// �������U���̍U����
	float LiliaAttackLongPower;

	/// ��U���ǌ��̍U����
	float LiliaAttackWeakDerivationPower;

	/// ���U���̍U����
	float LiliaAttackMediumPower;

	/// ���U���ǌ��̍U����
	float LiliaAttackMediumDerivationPower;

	/// ���U���̍U���́i���i�q�b�g�ׁ̈A1�q�b�g�̈З͂𗎂Ƃ��Ă���j
	float LiliaAttackStrongPower;

	/// �K�E�Z�̍U���́i���i�q�b�g�ׁ̈A1�q�b�g�̈З͂𗎂Ƃ��Ă���j
	float LiliaAttackSpecialPower;

	/// �K�E�Z�ǌ��̍U����
	float LiliaAttackSpecialPursuitPower;

	/// �_�b�V���U���̍U����
	float LiliaAttackDashPower;

	/// ��P�U���̍U����
	float LiliaAttackRaidPower;

	/// ���Ⴊ�ݍU���̍U����
	float LiliaAttackSquatPower;

	/// �����A�a���񐔂̍ő�l
	int LiliaSlashingCountMax;


	// ���i (�U���͂��߁E�X�s�[�h�𑁂߂ɐݒ�)--------------------------------------------------------

	/// �O�i���x
	float RunaAdvanceSpeed;

	/// �K�[�h���x
	float RunaGuardSpeed;

	/// �_�b�V�����x
	float RunaDashSpeed;

	/// �o�b�N�X�e�b�v���x
	float RunaBackStepSpeed;

	/// ���U���g�p���̑��x
	float RunaAttackStrongSpeed;

	/// �K�E�Z�ǌ��̑��x
	float RunaAttackSpecialPursuitSpeed;

	/// ��U���̍U����
	float RunaAttackWeakPower;

	/// �W�����v�U���̍U����
	float RunaAttackJumpPower;

	/// �������U���̍U����
	float RunaAttackLongPower;

	/// ��U���ǌ��̍U����
	float RunaAttackWeakDerivationPower;

	/// ���U���̍U����
	float RunaAttackMediumPower;

	/// ���U���ǌ��̍U����
	float RunaAttackMediumDerivationPower;

	/// ���U���̍U���́i���i�q�b�g�ׁ̈A1�q�b�g�̈З͂𗎂Ƃ��Ă���j
	float RunaAttackStrongPower;

	/// �K�E�Z�̍U���́i���i�q�b�g�ׁ̈A1�q�b�g�̈З͂𗎂Ƃ��Ă���j
	float RunaAttackSpecialPower;

	/// �K�E�Z�ǌ��̍U����
	float RunaAttackSpecialPursuitPower;

	/// �_�b�V���U���̍U����
	float RunaAttackDashPower;

	/// ��P�U���̍U����
	float RunaAttackRaidPower;

	/// ���Ⴊ�ݍU���̍U����
	float RunaAttackSquatPower;

	/// ���i�a���񐔂̍ő�l
	int RunaSlashingCountMax;


private:
	/**
	* @brief �R���X�g���N�^
	*/
	CharacterParamLoader() :iniFileLoaderBase("CharacterParam.ini")
	{
		// ����
		PlayerGuardNowSpeed = GetNextParameterFloat();

		// �����A
		LiliaAdvanceSpeed = GetNextParameterFloat();
		LiliaGuardSpeed = GetNextParameterFloat();
		LiliaDashSpeed = GetNextParameterFloat();
		LiliaBackStepSpeed = GetNextParameterFloat();
		LiliaAttackStrongSpeed = GetNextParameterFloat();
		LiliaAttackSpecialPursuitSpeed = GetNextParameterFloat();
		LiliaAttackWeakPower = GetNextParameterFloat();
		LiliaAttackJumpPower = GetNextParameterFloat();
		LiliaAttackLongPower = GetNextParameterFloat();
		LiliaAttackWeakDerivationPower = GetNextParameterFloat();
		LiliaAttackMediumPower = GetNextParameterFloat();
		LiliaAttackMediumDerivationPower = GetNextParameterFloat();
		LiliaAttackStrongPower = GetNextParameterFloat();
		LiliaAttackSpecialPower = GetNextParameterFloat();
		LiliaAttackSpecialPursuitPower = GetNextParameterFloat();
		LiliaAttackDashPower = GetNextParameterFloat();
		LiliaAttackRaidPower = GetNextParameterFloat();
		LiliaAttackSquatPower = GetNextParameterFloat();
		LiliaSlashingCountMax = GetNextParameterInt();

		// ���i
		RunaAdvanceSpeed = GetNextParameterFloat();
		RunaGuardSpeed = GetNextParameterFloat();
		RunaDashSpeed = GetNextParameterFloat();
		RunaBackStepSpeed = GetNextParameterFloat();
		RunaAttackStrongSpeed = GetNextParameterFloat();
		RunaAttackSpecialPursuitSpeed = GetNextParameterFloat();
		RunaAttackWeakPower = GetNextParameterFloat();
		RunaAttackJumpPower = GetNextParameterFloat();
		RunaAttackLongPower = GetNextParameterFloat();
		RunaAttackWeakDerivationPower = GetNextParameterFloat();
		RunaAttackMediumPower = GetNextParameterFloat();
		RunaAttackMediumDerivationPower = GetNextParameterFloat();
		RunaAttackStrongPower = GetNextParameterFloat();
		RunaAttackSpecialPower = GetNextParameterFloat();
		RunaAttackSpecialPursuitPower = GetNextParameterFloat();
		RunaAttackDashPower = GetNextParameterFloat();
		RunaAttackRaidPower = GetNextParameterFloat();
		RunaAttackSquatPower = GetNextParameterFloat();
		RunaSlashingCountMax = GetNextParameterInt();
	}
};

#endif