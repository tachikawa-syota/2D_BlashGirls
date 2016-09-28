/**
* @file   Runa.h
* @brief  �L�����N�^�["���i"�̋������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___RUNA_H
#define ___RUNA_H

#include "..\IPlayer.h"

/**
* @brief �L�����N�^�[�E���i
*/
class Runa : public IPlayer
{
public:
	/**
	* @brief �R���X�g���N�^
	* @param �v���C���[�ԍ�
	*/
	Runa(int index);
	/**
	* @brief �f�X�g���N�^
	*/
	~Runa();

#pragma region IPlayer
	/**
	* @brief ������
	*/
	void Initialize(int index);

	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief ���Ⴊ��
	*/
	void Squat();

	/**
	* @brief �O�i
	*/
	void Advance();

	/**
	* @brief �K�[�h
	*/
	void Guard();

	/**
	* @brief �W�����v
	*/
	void Jump();

	/**
	* @brief �W�����v�o���邩�̔���
	*/
	bool IsJump();

	/**
	* @brief ��g�����邩�̔���
	*/
	bool CanPassive();

	/**
	* @brief �ǌ�(�h���Z)���\��
	*/
	bool CanDerivation();

	/**
	* @brief �_�E����
	*/
	bool isDown();

	/**
	* @brief ����
	*/
	bool isControll();

	/**
	* @brief ����
	*/
	void SetBurning();

	/**
	* @brief ��i�U��������������
	*/
	bool isUpperAttackHit(const IPlayer& enemy);

	/**
	* @brief ���i�U��������������
	*/
	bool isLowerAttackHit(const IPlayer& enemy);

	/**
	* @brief ��e
	* @param attacker - �U����
	* @param hitType - ��i or ���i
	*/
	void Damage(const IPlayer& attacker, AttackPoint hitType);

	/**
	* @brief �p�����[�^���Z�b�g
	*/
	void ActionReset();

	/**
	* @brief �ʒu��ݒ�
	*/
	void SetPos(const Vector2& pos);

	/**
	* @brief ��Ԃ�ݒ�
	*/
	void SetState(const State state);

	/**
	* @brief ������ݒ�
	*/
	void SetDirection(const Dir& dir);

	/**
	* @brief ���x��ݒ肷��
	*/
	void SetSpeed(const float spx = 0.0f, const float spy = 0.0f);

	/**
	* @brief �v���C���[�ԍ����擾
	*/
	const unsigned int GetID() const;

	/**
	* @brief �U���͂��擾
	*/
	const float GetPower() const;

	/**
	* @brief �ʒu���擾
	*/
	const Vector2& GetPos() const;

	/**
	* @brief ��Ԃ��擾
	*/
	const State GetState() const;

	/**
	* @brief �U���͈͂��擾
	*/
	const Rect GetAttackRect() const;

	/**
	* @brief �q�b�g�͈͂��擾
	*/
	const Rect GetHitRect() const;

	/**
	* @brief �������擾
	*/
	const Dir GetDirection() const;

	/**
	* @brief �U�����蔭�������ۂ�
	*/
	bool isAttackJudge();

#pragma endregion

	/**
	* @brief �ҋ@
	*/
	void Neutral();

	/**
	* @brief �_�b�V��
	*/
	void Dash();

	/**
	* @brief ���
	*/
	void BackStep();

	/**
	* @brief ���Ⴊ�ݍU��
	*/
	void SquatAttack();

	/**
	* @brief �_�b�V���U��
	*/
	void DashAttack();

	/**
	* @brief �W�����v�U��
	*/
	void JumpAttack();

	/**
	* @brief �_�E��
	*/
	void Down();

	/**
	* @brief �K�[�h��
	*/
	void GuardNow();

	/**
	* @brief ���Ⴊ�݃K�[�h��
	*/
	void SquatGuardNow();

	/**
	* @brief ������
	*/
	void Knockback();

	/**
	* @brief ��U��
	*/
	void WeakAttack();

	/**
	* @brief ��U���h���Z
	*/
	void WeakAttackDerivation();

	/**
	* @brief ���U��
	*/
	void MediumAttack();

	/**
	* @brief ���U��
	*/
	void StrongAttack();

	/**
	* @brief ���U���h���Z
	*/
	void StrongAttackDerivation();

	/**
	* @brief �������U��
	*/
	void LongAttack();

	/**
	* @brief �K�E�Z
	*/
	void SpecialAttack();

	/**
	* @brief �K�E�Z�ǌ�
	*/
	void SpecialPursuitAttack();

	/**
	* @brief ��P�U��
	*/
	void RaidAttack();

	/**
	* @brief �������
	*/
	void BlowOff();

	/**
	* @brief ���E
	*/
	void Offset();

	/**
	* @brief ��g
	*/
	void Passive();

	/**
	* @brief �o�g���O
	*/
	void BeforeBattle();

	/**
	* @brief �m�b�N�A�E�g
	*/
	void KO();

	/**
	* @brief ����
	*/
	void Win();

	/**
	* @brief ���ꉉ�o
	*/
	void SpecialProduction();

private:
	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;

	/// �����A�g��A��]�A�ʒu
	Object2DPacket m_obj;

	/// ���x
	Vector2 m_spd;

	/// �P�t���[���O�̑��x
	Vector2 m_oldSpd;

	/// ���
	State m_state;

	/// 1�t���[���O�̏��
	State m_oldState;

	/// �U������͈̔�
	Rect m_attackRect;

	/// ��炢����͈̔�
	Rect m_hitRect;

	/// �U���^�C�v
	AttackPoint m_attackPoint;

	/// �L�����N�^�̔ԍ�
	int m_id;

	/// �W�����v��
	int m_jumpCount;

	/// �K�E�Z�a���J�E���g
	int m_slashingCount;

	/// ��g�t���O
	bool m_isPassive;

	/// ����t���O
	bool m_isControll;

	/// ���G�t���O
	bool m_isInvincible;

	/// �ڒn�t���O
	bool m_isFloor;

	/// �U�����蔭�����t���O
	bool m_isAttackJudge;

	/// �U�������t���O
	bool m_isAttackSuccess;

	/// �ǌ��\�t���O
	bool m_isDerivation;

	/// �R���Ă��邩�ǂ����̃t���O
	bool m_isBurning;

	/// �ҋ@�e�N�X�`��
	int m_hNeutral[3];

	/// �U���e�N�X�`��
	int m_hAttack[6];

	/// �W�����v�U���e�N�X�`��
	int m_hJumpAttack[3];

	/// ���Ⴊ�ݍU���e�N�X�`��
	int m_hSquatAttack[3];

	/// �_�E���e�N�X�`��
	int m_hDown;

	/// �q�b�g�e�N�X�`��
	int m_hHit;

	/// �W�����v�e�N�X�`��
	int m_hJump;

	/// ���Ⴊ�݃e�N�X�`��
	int m_hSquat;

	/// �����e�N�X�`��
	int m_hWalk;

	/// �����e�N�X�`��
	int m_hWin[2];

	/// �A�j���[�V����
	int m_animation;

	/// �T�u���[�N
	int m_subWork;

	///�e�X�̃��[�N���ł̃J�E���^�ɗ��p����
	int m_subFrame;

	/// ������t���[��
	int m_knockbackFrame;

	/// ��e�t���[��
	int m_damageFrame;

	/// �_�E����Ԑ�p�t���[��
	int m_downFrame;

	/// �U����
	float m_power;

	/**
	* @brief ����\���ۂ�
	*/
	bool CanControll();

	/**
	* @brief �p�x�����Z����
	*/
	void AddAngle(float speed);

	/**
	* @brief �K�E�Z�̃G�t�F�N�g��������
	*/
	void SpecialAttackCreateEffect();
};

#endif