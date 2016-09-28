/**
* @file CharacterParam.h
* @brief �L�����N�^�[�̃p�����[�^�f�[�^��Z�߂�
* @author Syota Tachikawa
* @since 2016/03/17
*/

// ---------------------------------------------------------------------------
//
// �ړ��֌W
//
// ---------------------------------------------------------------------------

/// �K�[�h���x
const float GUARD_VX = -2.0f;

/// �ړ����x
const float WALK_VX = 5.3f;

/// �_�b�V�����x
const float DASH_VX = 15.0f;

/// �o�b�N�X�e�b�v���x
const float BACK_STEP_VX = -10.0f;

/// �K�E�Z�ǌ����x
const float ATTACK_SPECIAL_PURSUIT_VX = 30.0f;

/// ��P�U���̑��x
const float ATTACK_RAID_VX = 70.0f;

/// ���E���̑��x
const float OFFSET_VX = 30.0f;

/// ��g�̑��x
const float PASSIVE_VX = 4.0f;
const float PASSIVE_VY = 10.0f;

/// �����|�[�Y�̑��x
const float WIN_VY = 10.0f;

/// �j�n�ɂȂ����u�Ԃ̑��x
const float KO_VX = 4.0f;
const float KO_VY = 20.0f;

// �W�����v���x
const float JUMP_VY = -17.0f;

/// ���Ⴊ�݃K�[�h���m�b�N�o�b�N���x
const float CHARACTER_GUARD_VX = 3.0f;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// �U���͊֌W
//
// ---------------------------------------------------------------------------

/// ��U���̍U����
const float ATTACK_WEAK_POWER = 20.0f;

/// �㉺�U���̍U����
const float ATTACK_WEAK_UNDER_POWER = 20.0f;

/// ��U���ǌ��̍U����
const float ATTACK_WEAK_DERIVATION_POWER = 40.0f;

/// ���U���̍U����
const float ATTACK_MEDIUM_POWER = 75.0f;

/// ���U���ǌ��̍U����
const float ATTACK_MEDIUM_DERIVATION_POWER = 50.0f;

/// ���U���̍U���́i���i�q�b�g�ׁ̈A1�q�b�g�̈З͂𗎂Ƃ��Ă���j
const float ATTACK_STRONG_POWER = 8.05f;

/// �K�E�Z�̍U���́i���i�q�b�g�ׁ̈A1�q�b�g�̈З͂𗎂Ƃ��Ă���j
const float ATTACK_SPECIAL_POWER = 9.0f;

/// �K�E�Z�ǌ��̍U����
const float ATTACK_SPECIAL_PURSUIT_POWER = 20.0f;

/// �_�b�V���U���̍U����
const float ATTACK_DASH_POWER = 10.0f;

/// ���Ⴊ�ݍU���̍U����
const float ATTACK_SQUAT_POWER = 7.0f;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// �t���[���֌W
//
// ---------------------------------------------------------------------------

/// ���Ⴊ�ݍU��������t���[��
const int BENDBACKWARDFRAME_SQUAT = 15;

/// ��U��������t���[��
const int BENDBACKWARDFRAME_WEAK = 22;

/// ��h���U��������t���[��
const int BENDBACKWARDFRAME_WEAK_DERIVATION = 30;

/// ���U��������t���[��
const int BENDBACKWARDFRAME_MEDIUM = 30;

/// ���U��������t���[��
const int BENDBACKWARDFRAME_STRONG = 90;

/// �K�E�Z������t���[��
const int BENDBACKWARDFRAME_SPECIAL_PURSUIT = 110;

///	�W�����v�U��������t���[��
const int BENDBACKWARDFRAME_JUMP = 5;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// ���W�֌W
//
// ---------------------------------------------------------------------------

/// Player1�̏����ʒu
const float INIT_PLAYER1_X = 350.0f;

/// Player2�̏����ʒu
const float INIT_PLAYER2_X = 930.0f;

// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
//
// ���̑�
//
// ---------------------------------------------------------------------------

/// �����G�L�����N�^�[�̉���
const float STAND_CHARACTER_WIDTH = 200.0f;

/// �L�����N�^�[�̗]��
const float CHARACTER_MARGIN = 40.0f;

/// ���㒆�̃A���t�@���Z�l
const int BURNING_ADD_ALPHA = 8;

/// ������я�Ԃ̊p�x���Z
const float BLOWOFF_ADD_ANGLE = 6.0f;

const float HITPARTICLESIZE = 0.9f;

/// �W�����v�ő吔
const int JUMP_MAX = 1;

// ---------------------------------------------------------------------------