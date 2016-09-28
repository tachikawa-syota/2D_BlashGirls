/**
* @file   GameMain.h
* @brief  ���C���Q�[���̏������Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___GAMEMAIN_H
#define ___GAMEMAIN_H

#include "ISequence.h"
#include "..\Common\StdAfx.h"
#include "..\Object\IPlayer.h"
#include "..\Object\IObject.h"
#include "..\DirectX\InputMask.h"
#include "..\GameSystem\Computer.h"
#include "..\GameSystem\Command.h"
#include "..\Object\UI\SpecialGauge.h"
#include "..\GameSystem\ComboCounter.h"
#include "..\Object\UI\HpGauge.h"
#include "..\Object\UI\UIManager.h"

/// ���E���h�̍ő吔
const BYTE ROUND_MAX = 3;

class GameMain : public ISequence
{
protected:
	// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	// �e�N�X�`���f�[�^
	TextureData* m_texData;

	// �X�e�[�W�I�u�W�F�N�g
	IStagePtr pStage;

	// �v���C���[�I�u�W�F�N�g
	vector<IPlPtr> pPlayer;

	// ���̓f�o�C�X
	vector<InputRef> m_dev;

	// �R�}���h�f�[�^
	vector<Command*> cmd;

	// CPU
	Computer m_com;

	/// HP�Q�[�W
	HpGauge hpGauge;

	/// �R���{��
	ComboCounter combo;

	/// UI�}�l�[�W��
	unique_ptr<UIManager> uiMgr;

	/// �K�E�Z�Q�[�W
	SpGaugePtr spGauge;

	// �e�N�X�`���֘A ---------------------------------------------

	/// ���E�����G�p
	std::vector<int> UI_stand01;
	std::vector<int> UI_stand02;

	/// �L�����N�^�[�̎��
	int m_charaType[JOY_MAX];
	
	/// �L�����N�^�[�̉B���V�[���p
	int spcialTex[2];
	/// �`��ʒu
	float specialTexY;
	/// �傫��
	float specialTexScale[2];

	/// �����w�e�N�X�`���R�s�[�p
	int mCircleTex[2];
	
	// ------------------------------------------------------------

	/// �\�����闧���G�ԍ�
	std::array<int, JOY_MAX>displayNumber;

	/// �q�b�g�|�C���g

	/// �X�e�[�W�̃A���t�@�l
	int stageAlpha;

	// �ꎞ�I�Ɏg�p����t���[���̒�`
	
	/// ��~�t���[��
	int stopFrame;
	int stopCount;
	int workFrame;
	int adjustworkFrame;
	/// �T�u���[�N
	GameState subWork;

	/// �I�����ꂽ�L�����N�^
	const int* selectChara;

	/// �o�g���J�n�O���ł̃��[�N
	int m_beforBattleWork;

	/// �o�g���Z�b�g���ł̃��[�N
	int m_setBattleWork;

	/// �Q�[���Z�b�g���ł̃��[�N
	int m_gameSetWork;


	/// ���ꉉ�o���[�N
	int spWork;
	
	/// �K�E�Z���[�N
	int spAttackWork;

	/// ����G�t�F�N�g���[�N
	int spEffectWork;

	/// �Q�[�����[�N
	int gameWork;

	/// �����A�p���[�A�b�v�l
	float powerUPLilia[JOY_MAX];

	/// ���i�p���[�A�b�v�l
	float powerUPRuna[JOY_MAX];

	/// �����G�w�i�̕`�悷��ԍ�
	int standBack[JOY_MAX];

	/// �Q�[���t���[��
	int gameFrame;

	/// �����p�t���[��
	int adjustFrame;

	/// �j�n����p
	int isKO;

	/// ���ꉉ�o�t���O
	bool isSpecial;

	/// �Q�[����~�t���O
	bool m_isGameStop;

	/// �h�炷�l
	float swingVal[JOY_MAX];
	// �h�炷���ۂ��̃t���O
	bool isSwing[JOY_MAX];
	/// �G�N�X�g���X�L�������t���O
	bool isUseExSkill[JOY_MAX];

	/// �ߕ����j�ꂽ��
	int clothesBreakCount[JOY_MAX];
	
	/// �ߕ��j��t���O
	bool isClothesBreak[JOY_MAX];

	/// ���p�A���t�@�l
	float light2Angle;		

	/// �j����
	int breakState[JOY_MAX];

	/// �p���[�A�b�v�p�[�e�B�N���A���t�@�l
	float pwUpAlpha[JOY_MAX];
	/// 1P�p���[�A�b�v�l
	float P1pwUpValue[2];
	/// 2P�p���[�A�b�v�l
	float P2pwUpValue[2];

	/// �K�E�Z�p�̖����w�̊p�x
	float mCircleAngle;
	/// �K�E�Z�p�̖����w�̑傫��
	float mCircleScale;
	/// �K�E�Z�p�̖����w�̃A���t�@�l
	int mCircleAlpha;

	/// �A���W
	float formX[5], formY[5];
	/// �A�����t���O
	bool formFlag;

	/// �J�n�O�̖����w�p�x
	float magicAngle;
	
	/// Fight�t�H���g���W
	float fightX;
	/// Fight�t�H���g���x
	float fightVX;

	// �������ۑ�
	int winNum[JOY_MAX];
	// ���݂̃��E���h
	int roundNow;
	// �������v���C���[�ԍ�
	int losePlNum;
	
	/**
	* @brief ���C���Q�[���X�V
	*/
	void UpdateGame();

	/**
	* @brief KO�����̍X�V
	*/
	bool UpdateGameKO();
	
	/**
	* @brief �o�g���O�̉��o�X�V
	*/
	void UpdateBeforBattle();
	
	/**
	* @brief �o�g���O�̃t�H���g�����̍X�V
	*/
	void UpdateSetBattle();

	/**
	* @brief �o�g�������̍X�V
	*/
	void UpdateGameSet();

	/**
	* @brief �o�g��KO�̍X�V
	*/
	void UpdateKO();

	/**
	* @brief �o�g������V�[���̍X�V
	*/
	void UpdateSpecial();

	/**
	* @brief �o�g���I���̍X�V
	*/
	void UpdateEnd();

	/**
	* @brief �o�g���I���̍X�V
	*/
	void UpdateExit();

	/**
	* @brief �j��G�t�F�N�g�̍X�V
	*/
	void UpdateBreakClothes();

	/**
	* @brief �p���[�A�b�v�G�t�F�N�g�̍X�V
	*/
	void UpdatePowerUp();
	
	/**
	* @brief �L�����N�^�[�̍X�V
	*/
	void UpdateCharacter(int index);

	/**
	* @brief �G�N�X�g���X�L���̍X�V
	*/
	void UpdateExSkill();

	/**
	* @brief �w�i�ɕ`�悷�閂���w�̍X�V
	*/
	void UpdateBackGroundMagicCircle();

	/**
	* @brief �w�i�ɕ`�悷��
	*/
	void RenderBackGround();

	/**
	* @brief �����w��Ready�t�H���g�`��
	*/
	void RenderSetBattle();

	/**
	* @brief ���ꉉ�o�̕`��
	*/
	void RenderSpecialProduction();

	/**
	* @brief �j�n�������𔻒肷��
	*/
	void GetCheckKO();
	
	/**
	* @brief �v���C���[���m�̓����蔻��
	*/
	void CheckPlayerCollide(int index);

	/**
	* @brief �v���C���[�Ə�i�U���̓����蔻��
	*/
	void CheckUpperAttackCollide(int index);

	/**
	* @brief �v���C���[�Ɖ��i�U���̓����蔻��
	*/
	void CheckLowerAttackCollide(int index);
	
	/**
	* @brief ���E����
	*/
	void CheckOffsetCollide(int index);

	/**
	* @brief �v���C���[�ƃG�t�F�N�g�̓����蔻��
	*/
	void CheckEffectCollide(int index);

	/**
	* @brief �v���C���[�̌����𒲐�����
	*/
	void SetPlayerDirection(int index);

	/**
	* @brief �U���_���[�W�����Z����
	*/
	void UpdateAttackDamage(int index);

	/**
	* @brief �X�e�[�W�[����o�Ȃ��悤�ɂ���
	*/
	void StageEnd();

	/**
	* @brief �ǃn�����o���Ȃ��悤�ɃX�e�[�W�[�ōU������������␳����
	*/
	void StageEndShift(int index);

	/**
	* @brief ��ʂ�h�炷
	*/
	void ScreenSwing();

	/**
	* @brief �B���R�}���h�ɂ����ꉉ�o
	*/
	bool SpecialProduction();

	/**
	* @brief �Q�[���̍X�V���~����
	* @param frame - ��~����t���[����
	* @param flag  - true�Œ�~������
	*/
	void SetGameStop(int frame , bool flag = false);

public:

	/**
	* @brief ������
	*/
	void Initialize();
	
	/**
	* @brief �쐬
	*/
	void Create();
	
	/**
	* @brief �X�V
	*/
	void Update();

	/**
	* @brief �`��
	*/
	void Render();

	/**
	* @brief �I��
	*/
	void Finalize();
};

#endif