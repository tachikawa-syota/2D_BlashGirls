/**
* @file   Enum.h
* @brief  Enum��`��Z�߂�
* @author Syota Tachikawa
*/

#ifndef ___ENUM_H
#define ___ENUM_H

/// ����
enum class Dir
{
	Right,
	Left
};

/// �L�����N�^�[���
enum class State
{
	Neutral,
	Advance,					// �O�i
	Dash,						// �t�����g�X�e�b�v(�_�b�V��)
	BackStep,					// �o�b�N�X�e�b�v
	Squat,						// ���Ⴊ��
	SquatAttack,				// ���Ⴊ�ݍU��
	Jump,
	JumpFront,					// �O���W�����v
	JumpBack,					// ����W�����v
	JumpAttack,					// �󒆍U��
	DashAttack,					// �_�b�V���U��
	WeakAttack,					// ��U��
	UnderAttack,				// �㉺�U��
	WeakDerivationAttack,		// ��U���h���Z
	MediumAttack,				// ���U��
	StrongAttack,				// ���U��
	StrongDerivationAttack,		// ���U���h���Z
	SpecialAttack,				// �K�E�Z
	AttackSpecialPursuit,		// �K�E�Z�ǌ�
	RaidAttack,					// ��P�U��
	Guard,						// �ʏ�K�[�h
	SquatGuard,					// ���Ⴊ�݃K�[�h
	SquatGuardNow,				// ���Ⴊ�݃K�[�h��
	JumpGuard,					// �W�����v�K�[�h
	GuardNow,					// �ʏ�K�[�h��
	Down,						// �_�E�����
	AIRHIT,						// �󒆔�e
	Blowoff,					// �������
	Damage,						// ��e
	DamageEffect,				// �G�t�F�N�g��e
	Offset,						// ���E
	Passive,					// ��g
	BeforBattle,				// �o�g���J�n�O
	Win,						// ����
	Ko,
	SpecialProduction,			// ���ꉉ�o
	STATE_MAX
};

// �t�F�[�h
enum class Fade
{
	None,
	In,
	Out
};

// �t�F�[�h�J���[
enum class FadeColor
{
	Black,
	White
};

// �Q�[�����[�h
enum class GameMode
{
	Default = 0,
	VsCPU,
	Vs2P,
	Demo,		// �f���v���C
	Exit
};

// �L�����N�^�[�l�[��
enum CharaName
{
	LILIA,
	RUNA
};

// �ߕ��̏��
enum ClotheState
{
	NO_BREAK = 0,
	BREAK_TORSO,
	BREAK_TORSO_AND_OUTERWEAR,
	BREAK_TORSO_AND_SKIRT,
	ALL_BREAK,
	NUDE
};

// �Q�[���̏��
enum class GameState
{
	BattleBefore = 0,
	Set,
	Play,
	GameSet,
	KO,
	Special,
	End,
	Exit
};

// �G�t�F�N�g�̎��
enum EffectKind
{
	Hinoko,        // �΂̕�
	Slash,         // �a��
	Slash2,        // �a��
	Light,         // ��
	Smoke,         // ��
	Slash3,        // �a��
	Ring,          // �ւ���
	Blur,          // �u���[
	Trajectory,    // ���̋O��
	Slash4 = 9,    // �a��
	RedRing,       // �Ԃ���
	BurstRing,     // �Ռ��g
};

// �K�E�Z�Q�[�W�̏��
enum class SpecialGaugeState
{
	None,  // �Ȃ�
	Empty, // ��
	Add,   // ����
	Full,  // ���^��
	Use,   // �g�p
};

// �X�e�[�W�̎��
enum class StageType
{
	SubSpace, // �����
};

// �U���|�C���g
enum class AttackPoint
{
	// �f�[�^����
	None,
	// ��i
	Upper,
	// ���i
	Lower
};

#endif