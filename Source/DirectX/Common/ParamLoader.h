#ifndef ___PARAMLOADER_H
#define ___PARAMLOADER_H

#include "..\iniFileLoader\iniFileLoaderBase.h"

// �C���X�^���X�擾
#define GetPrm ParamLoader::GetInstance()

/**
* @brief ini�t�@�C���ŊǗ����Ă���p�����[�^�[��ǂݍ��ރN���X
*/
class ParamLoader : public iniFileLoaderBase
{
public:
	static ParamLoader* GetInstance(){
		static ParamLoader singleton;
		return &singleton;
	}

	/// �v���C���[�P�̏������W
	float Player1InitPosX;

	/// �v���C���[�Q�̏������W
	float Player2InitPosX;

	/// �v���C���[�̏������W�iY���W�͗��ҋ��ʂȂ̂Œ萔�͈�����j
	float PlayerInitPosY;

	/// ���̍��W
	float Ground;

	/// �d��
	float Gravity;

	/// �P�G�t�F�N�g�̊g��l
	float FlushEffectAddScale;

	/// �P�G�t�F�N�g�̑傫���̍ő�l
	float FlushEffectMaxScale;

	/// �K�[�h�G�t�F�N�g�̑傫���̍ő�l
	float GuardEffectMaxScale;

	/// �K�[�h�G�t�F�N�g�̊g��l
	float GuardEffectAddScale;

	/// ���G�t�F�N�g�̑傫���̍ő�l
	float LightEffectMaxScale;

	/// �����C���G�t�F�N�g�̑��x
	float LightlineEffectVX;

	/// �g�G�t�F�N�g�̃A�j���[�V�����ő吔
	int WaveEffectMaxAnimation;

	/// Player1���̃q�b�g�t�H���g�̈ʒu
	float HitFontPlayer1X;

	/// Player2���̃q�b�g�t�H���g�̈ʒu
	float HitFontPlayer2X;

	/// Player1���̐����t�H���g�̈ʒu
	float NumberFontPlayer1X;

	/// Player2���̐����t�H���g�̈ʒu
	float NumberFontPlayer2X;

	/// �R���{�����t���[���̃��~�b�g
	int ComboFrameLimit;

	/// �R���{�_���[�W�ɂ��␳�W��
	float ComboCorrectionCoefficient;

	/// �␳�l�̃��~�b�g
	float ComboCorrectionCoefficientLimit;

	/// Player1���̃J�b�g�C���̏����ʒu�w
	float InitCutinPlayer1X;

	/// �J�b�g�C���̏����ʒu�x
	float InitCutinY;

	/// Player2���̃J�b�g�C���̏����ʒu�w
	float InitCutinPlayer2X;

	/// �����J�b�g�C�����x
	float InitCutinV;

	/// Player1�̃J�b�g�C���ʒu
	float CutinPlayer1X;

	/// �J�b�g�C���ʒu
	float CutinY;

	/// Player2�̃J�b�g�C���ʒu
	float CutinPlayer2X;

	/// �p�J�Q�[�W�̍ő�l�i�g�o�Q�[�W�j
	float HpMax;

	/// �㒅�ϋv�̍ő�l
	float OuterWearEnduranceMax;

	/// �X�J�[�g�ϋv�̍ő�l
	float SkirtEnduranceMax;

	/// ���ϋv�̍ő�l
	float TorsoEnduranceMax;

	/// �w�i�L�����N�^�[�̈ʒu
	float BackPlayer1X;
	float BackPlayer2X;

	/// �w�i�L�����N�^�[�̑��x
	float BackCharacterVX;

	/// �w�i�L�����N�^�[�̃A���t�@���Z�l
	int BackCharacterAddAlpha;

	/// �L�����N�^�[�I����ʖ��@�t�H���g�̑��x
	float MagicFontVX;

	/// �L�����N�^�[�I����ʖ��@�t�H���g�ʒu�̃��~�b�g
	float MagicFontY1Limit;
	float MagicFontY2Limit;

	/// �L�����N�^�[�I����ʖ��@�t�H���g�̏����ʒu
	float MagicFontInitY1;
	float MagicFontInitY2;

	/// Fight�t�H���g�̏����ʒu
	float FightFontInitX;

	/// Fight�t�H���g�̏������x
	float FightFontInitVX;

	/// Fight�t�H���g�̈ʒu
	float FightFontX;

	/// Fight�t�H���g�̑��x
	float FightFontVX;

	// �o�g���J�n�O�̖����w����]���x
	float MagicCircleAddAngle;

	/// �K�[�h�ɂ��_���[�W�y����
	float GuardDamageMitiGation;

	/// �␳������X�e�[�W�̉E�[�ʒu
	float StageLeftShiftLimit;

	/// �␳������X�e�[�W�̉E�[�ʒu
	float StageRightShiftLimit;

	/// �K�E�Z�Q�[�W�ʂ̍ő�l
	float MaxSpecialGauge;

	/// �K�E�Z�Q�[�W�̑傫��
	float SpecialGaugeSizeX;

private:
	/**
	* @brief �R���X�g���N�^
	*/
	ParamLoader() :iniFileLoaderBase("Param.ini")
	{
		Player1InitPosX = GetNextParameterFloat();
		Player2InitPosX = GetNextParameterFloat();
		PlayerInitPosY = GetNextParameterFloat();
		Ground = GetNextParameterFloat();
		Gravity = GetNextParameterFloat();
		FlushEffectAddScale = GetNextParameterFloat();
		FlushEffectMaxScale = GetNextParameterFloat();
		GuardEffectMaxScale = GetNextParameterFloat();
		GuardEffectAddScale = GetNextParameterFloat();
		LightEffectMaxScale = GetNextParameterFloat();
		LightlineEffectVX = GetNextParameterFloat();
		WaveEffectMaxAnimation = GetNextParameterInt();
		HitFontPlayer1X = GetNextParameterFloat();
		HitFontPlayer2X = GetNextParameterFloat();
		NumberFontPlayer1X = GetNextParameterFloat();
		NumberFontPlayer2X = GetNextParameterFloat();
		ComboFrameLimit = GetNextParameterInt();
		ComboCorrectionCoefficient = GetNextParameterFloat();
		ComboCorrectionCoefficientLimit = GetNextParameterFloat();
		InitCutinPlayer1X = GetNextParameterFloat();
		InitCutinY = GetNextParameterFloat();
		InitCutinPlayer2X = GetNextParameterFloat();
		InitCutinV = GetNextParameterFloat();
		CutinPlayer1X = GetNextParameterFloat();
		CutinY = GetNextParameterFloat();
		CutinPlayer2X = GetNextParameterFloat();
		HpMax = GetNextParameterFloat();
		OuterWearEnduranceMax = GetNextParameterFloat();
		SkirtEnduranceMax = GetNextParameterFloat();
		TorsoEnduranceMax = GetNextParameterFloat();
		BackPlayer1X = GetNextParameterFloat();
		BackPlayer2X = GetNextParameterFloat();
		BackCharacterVX = GetNextParameterFloat();
		BackCharacterAddAlpha = GetNextParameterInt();
		MagicFontVX = GetNextParameterFloat();
		MagicFontY1Limit = GetNextParameterFloat();
		MagicFontY2Limit = GetNextParameterFloat();
		MagicFontInitY1 = GetNextParameterFloat();
		MagicFontInitY2 = GetNextParameterFloat();
		FightFontInitX = GetNextParameterFloat();
		FightFontInitVX = GetNextParameterFloat();
		FightFontX = GetNextParameterFloat();
		FightFontVX = GetNextParameterFloat();
		MagicCircleAddAngle = GetNextParameterFloat();
		GuardDamageMitiGation = GetNextParameterFloat();
		StageLeftShiftLimit = GetNextParameterFloat();
		StageRightShiftLimit = GetNextParameterFloat();
		MaxSpecialGauge = GetNextParameterFloat();
		SpecialGaugeSizeX = GetNextParameterFloat();
	}
};

#endif