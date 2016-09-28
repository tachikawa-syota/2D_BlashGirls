#ifndef ___IPLAYER_H
#define ___IPLAYER_H

#include "..\Common\StdAfx.h"
#include "..\Common\Struct.h"
#include "..\Common\Enum.h"

/**
* @brief �v���C���[�C���^�[�t�F�C�X
*/
__interface IPlayer
{
	/**
	* @brief ������
	* @param �L�����N�^�[�̔ԍ�
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
	* @brief �W�����v�o���邩�̔���
	*/
	bool IsJump();

	/**
	* @brief ��g�����邩
	*/
	bool CanPassive();

	/**
	* @brief �ǌ�(�h���Z)���\��
	*/
	bool CanDerivation();

	/**
	* @brief ����
	* @return true - ����Ffalse - ����s��
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
	*/
	void Damage(const IPlayer& attacker, AttackPoint hitType);

	/**
	* @brief ����\��
	*/
	bool CanControll();	

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
};

// shared_ptr��IPlayer
using IPlPtr = shared_ptr<IPlayer>;

#endif