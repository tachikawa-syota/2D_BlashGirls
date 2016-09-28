// �V�[��
#include "Title.h"
#include "GameMain.h"
#include "Result.h"
#include "SequenceChanger.h"
// �T�E���h
#include "..\DirectX\SoundPlayer.h"
// �I�u�W�F�N�g
#include "..\Object\UI\UIManager.h"
// �I�u�W�F�N�g����
#include "..\Object\Stage\StageFactory.h"
#include "..\Object\Character\CharacterFactory.h"
// �G�t�F�N�g
#include "..\Object\Effect\EffectManager.h"
#include "..\Object\Effect\ShineEffect.h"
#include "..\Object\CollisionEffect\CollisionEffectManager.h"
// �p�[�e�B�N��
#include "..\Object\Particle\ParticleManager.h"
#include "..\Object\Particle\HitParticle.h"
#include "..\Object\Particle\PowerUpParticle.h"
#include "..\Object\Particle\FormParticle.h"
#include "..\Object\Particle\OffsetParticle.h"
// �V�X�e��
#include "..\GameSystem\Camera.h"
#include "..\GameSystem\Collide.h"
#include "..\GameSystem\CutIn.h"
#include "..\GameSystem\CutInManager.h"
// �p�����[�^
#include "..\Common\ParamLoader.h"
#include "..\Object\Character\CharacterParam.h"
// ��ӂȃf�[�^
#include "..\Common\UniqueData.h"
// �L�v
#include "..\Common\Utility.h"

/// �f�[�^�Ȃ�
#define NONE -1

/**
* @brief �쐬
*/
void GameMain::Create()
{
	// �C���X�^���X���擾����
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;

	// �X�e�[�W���쐬����
	//�i���o�[�W�����ł͈���ԃX�e�[�W���������j
	auto sf = make_unique<StageFactory>();
	pStage = sf->CreateStage(StageType::SubSpace);

	// �I�����ꂽ�L�����N�^�[�̏����擾����
	selectChara = UniqueData::GetInstance()->GetSelectCharacter();

	// �L�����N�^�[�C���X�^���X�����N���X
	auto cf = make_unique<CharacterFactory>();
	for (int i = 0; i < JOY_MAX; i++){
		// �v�f�ǉ�
		pPlayer.emplace_back((cf->CreateCharacter(selectChara[i], i)));
		// �L�����N�^�[�̎�ނ�ۑ�
		m_charaType[i] = selectChara[i];
	}

	// �v���C���[�̐l�����f�o�C�X�쐬
	int playerCount = UniqueData::GetInstance()->GetPlayerCount();
	for (int i = 0; i < playerCount; i++){
		m_dev.emplace_back(new InputMask(i));
		cmd.emplace_back(new Command());
	}

	uiMgr = make_unique<UIManager>();
	spGauge = make_unique<SpecialGauge>();

	// ���E�ɕ\������L�����N�^�[�̗����G
	UI_stand01.resize(6);
	UI_stand02.resize(6);

	// �e�N�X�`���ꊇ�R�s�[ -------------------------------------------------

	// �����G�e�N�X�`���R�s�[
	for (int i = 0; i < 6; i++){
		UI_stand01[i] = m_texData->GetTexture(TEX_LILIA_STAND_00 + i);
		UI_stand02[i] = m_texData->GetTexture(TEX_RUNA_STAND_00 + i);
	}
	// �����A�̓���V�[���e�N�X�`��
	spcialTex[LILIA] = m_texData->GetTexture(TEX_LILIA_SPECIAL);
	// ���i�̓���V�[���e�N�X�`��
	spcialTex[RUNA] = m_texData->GetTexture(TEX_RUNA_SPECIAL);
	for (int i = 0; i < MAGICCIRCLE_MAX; i++){
		mCircleTex[i] = m_texData->GetMagicCircleTexture(i);
	}

	// -----------------------------------------------------------------------
	
	// �o�g���J�n�O
	subWork = GameState::BattleBefore;

	// �������̏�����
	winNum[PLAYER1] = 0;
	winNum[PLAYER2] = 0;

	// ���E���h�ԍ��� 1 ��
	roundNow = 1;

	// �v���C���[���������ꂽ�����`�F�b�N����
	for (int i = 0; i != pPlayer.size(); i++)
	{
		if (pPlayer[i] == nullptr){
			// �����I��
			Utility::abortWithMsg("�v���C���[�̍쐬�Ɏ��s���܂����B");
		}
	}
}

/**
* @brief ������
*/
void GameMain::Initialize()
{
	gameWork = 0;
	spAttackWork = 0;
	spWork = 0;
	m_beforBattleWork = 0;
	m_setBattleWork = 0;
	m_gameSetWork = 0;
	gameFrame = 0;
	adjustworkFrame = 10;
	adjustFrame = 1;
	stageAlpha = ALPHA_MAX;
	stopCount = 0;
	stopFrame = 0;

	// �������v���C���[�ԍ�������
	losePlNum = NONE;

	// Fight�����̍��W�Ƒ��x��ݒ�
	fightX = GetPrm->FightFontInitX;
	fightVX = GetPrm->FightFontInitVX;
	
	// KO���Ă��Ȃ�
	isKO = NONE;

	// �p���[�A�b�v�l�̏�����
	for (int i = 0; i < 2; i++)
	{
		powerUPLilia[i] = {};
		powerUPRuna[i] = {};
	}

	isSwing[0] = isSwing[1] = false;
	isSpecial = false;
	isUseExSkill[0] = false;
	isUseExSkill[1] = false;

	magicAngle = 0.0f;
	
	workFrame = 0;
	
	specialTexY = 0.0f;
	specialTexScale[0] = 0.6f;
	mCircleScale = 0.0f;
	mCircleAngle = 0.0f;
	mCircleAlpha = 0;
	light2Angle = 0.0f;

	// �v���C���[�̐�����������������
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �ߕ��̔j���Ԃ�������
		clothesBreakCount[i] = 0;
		pwUpAlpha[i] = {};
		pwUpAlpha[i] = {};
		displayNumber[i] = NO_BREAK;
		standBack[i] = 0;
		breakState[i] = 0;
		swingVal[i] = 0.0f;
		// �v���C���[�̏�����
		pPlayer[i]->Initialize(i);
	}

	// �f�o�C�X�̐���������������
	for (int i = 0; i != m_dev.size(); i++){
		cmd[i]->Initialize();
	}

	// ����������
	EffectManager::GetInstance()->Initialize();
	CollisionEffectManager::GetInstance()->Initialize();
	ParticleManager::GetInstance()->Initialize();
	hpGauge.Initialize();
	spGauge->Initialize();
	combo.Initialize();
	uiMgr->Initialize();
	m_com.Initialize();

	// �J��������ɏ��������Ă���
	// �v���C���[�̕`�悪���S�_�����ɂ��Ă�֌W�ŕ␳����
	float left = pPlayer[PLAYER1]->GetPos().x + (pPlayer[PLAYER2]->GetPos().x - pPlayer[PLAYER1]->GetPos().x) / 2.0f - 640.0f;
	Camera::GetInstance()->SetCenterPoint(left);
}


/**
* @brief �X�V
*/
void GameMain::Update()
{
	// �X�e�[�W�̍X�V
	pStage->ChangeAlpha(stageAlpha);
	pStage->Update();

	switch (subWork)
	{
	// �J�n�O�̊|������
	case GameState::BattleBefore:
		UpdateBeforBattle();
		break;

	// ���f�B�t�@�C�g
	case GameState::Set:
		UpdateSetBattle();
		break;

	// �Q�[���v���C
	case GameState::Play:
		UpdateGame();
		break;

	// �Q�[���Z�b�g
	case GameState::GameSet:
		UpdateGameSet();
		break;

	// �m�b�N�A�E�g
	case GameState::KO:
		UpdateKO();
		break;

	// ���ꉉ�o
	case GameState::Special:
		UpdateSpecial();
		break;
		
	case GameState::End:
		UpdateEnd();
		break;

	// �o�g���̏I��
	case GameState::Exit:
		UpdateExit();
		break;

	// ��O����
	default:
		Utility::abortWithMsg("�Q�[�����ɗ�O�������������܂���");
		break;
	}
	
	// �f���v���C����
	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Demo)
	{
		// �L�[�̓��͂��m�F������
		if (m_dev[0]->CheckInputMask(INPUT_01))
		{
	//		SequenceManager::SequenceChange(Scene::Title);
			// ������
			Initialize();
		}
	}

	// �t���[���X�V
	gameFrame++;
}	

/**
* @brief �`��
*/
void GameMain::Render()
{
	// �X�e�[�W�̕`��
	pStage->Render();

	// �w�i�ɕ`��
	RenderBackGround();
	
	// �J�b�g�C���̕`��
	CutInManager::GetInstance()->Render();
//	cutin->Render();

	// �v���C���[�̕`��
	for (int i = 0; i != pPlayer.size(); i++)
		pPlayer[i]->Render();

	// �����蔻��t���G�t�F�N�g�̕`��
	CollisionEffectManager::GetInstance()->Render();

	// �G�t�F�N�g�̕`��
	EffectManager::GetInstance()->Render();
	
	// �p�[�e�B�N���̕`��
	if (subWork != GameState::Special){
		ParticleManager::GetInstance()->Render();
	}

	// UI�̕`��
	uiMgr->Render(winNum, swingVal, spGauge, hpGauge);

	// �R���{���\��
	combo.Render();

	// KO�����̕`��
	if (isKO != -1 && subWork == GameState::GameSet)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_KO_FONT), 640.0f, 290.0f, 0.0f, 0.5f);

	// Push�����̕`��
	if (subWork == GameState::KO){
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PUSH_FONT), 640.0f, 200.0f);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PUSH_FONT2), 725.0f, 200.0f + 15.0f);
	}

	// ���E���h�����̕`��
	if (subWork == GameState::Set)
	{
		RenderSetBattle();
	}
		
	// ���ꉉ�o�̕`��
	RenderSpecialProduction();
}



/**
* @brief �Q�[�������̏���
*/
void GameMain::UpdateGame()
{
	// �f�o�C�X�̍X�V
	for (int i = 0; i != m_dev.size(); i++){
		m_dev[i]->GetInput();
	}

	// �v���C���[�̕`�悪���S�_�����ɂ��Ă�֌W�ŕ␳����
	float left = pPlayer[PLAYER1]->GetPos().x + (pPlayer[PLAYER2]->GetPos().x - pPlayer[PLAYER1]->GetPos().x) / 2.0f - 640.0f;
	Camera::GetInstance()->SetCenterPoint(left);
	// �J�����̍X�V
	Camera::GetInstance()->Update();

	ScreenSwing();
	// ���s�̃`�F�b�N
	GetCheckKO();

	// �Q�[����~�t���O
	if (!m_isGameStop)
	{
		for (int i = 0; i != pPlayer.size(); ++i)
		{
			// �L�����N�^�[�X�V
			UpdateCharacter(i);
	//		cmd[i]->InputCommand(m_dev[i]->GetInputState());
			// �e�퓖���蔻����`�F�b�N
			CheckPlayerCollide(i);
			CheckUpperAttackCollide(i);
			CheckLowerAttackCollide(i);
			CheckOffsetCollide(i);
			CheckEffectCollide(i);

			SetPlayerDirection(i);

			pPlayer[i]->Update();

			// �R���{���̊m�F
			if (combo.GetComboCount(i) == 0){
				// �����͏���
				if (i == PLAYER1)
					hpGauge.SetOldGaugeDelete(PLAYER2, true);
				else if (i == PLAYER2)
					hpGauge.SetOldGaugeDelete(PLAYER1, true);
			}
		}

		// �K�E�Z�Q�[�W�X�V
		spGauge->Update();

		uiMgr->Update(breakState, hpGauge);

		UpdateBreakClothes();

		// �R���{���X�V
		combo.Update();

		// �p�[�e�B�N���̍X�V
		ParticleManager::GetInstance()->Update();

		// �G�t�F�N�g�̍X�V
		EffectManager::GetInstance()->Update();
	}


	// �p�J�Q�[�W(HP�Q�[�W)�X�V
	hpGauge.Update();

	// �����蔻������G�t�F�N�g�̍X�V
	CollisionEffectManager::GetInstance()->Update();

	// �J�b�g�C���X�V
	CutInManager::GetInstance()->Update();

	// �X�e�[�W�[
	StageEnd();

	// �w�i�����w�X�V
	UpdateBackGroundMagicCircle();

	// �p���[�A�b�v���̃G�t�F�N�g�X�V
	UpdatePowerUp();

	// �G�N�X�g���X�L���X�V
	UpdateExSkill();

	// �L�����N�^�[�̎�ނɂ���ĕK�E�Z�Q�[�W�̗��܂�����قȂ�
	for (int i = 0; i != pPlayer.size(); i++)
	{
		float spAdd = 0.0f;
		switch (m_charaType[i])
		{
		case CharaName::LILIA:
			spAdd = 0.65f;
			break;

		case CharaName::RUNA:
			spAdd = 0.65f + abs(powerUPRuna[i]);
			break;
		}

		// ���t���[���K�E�Z�Q�[�W�����Z����
		spGauge->Add(spAdd, i);
	}

	// ��~����
	if (m_isGameStop)
	{
		stopCount++;

		if (stopCount > stopFrame){
			m_isGameStop = false;
			stopCount = 0;
		}
	}

	// ����̏�Ԃ���KO��Ԃɂ��Ȃ� ---------------------------------

	if (m_isGameStop || ScreenEffect::GetInstance()->isPlayFade()) return;

	for (int i = 0; i != pPlayer.size(); i++){
		if (pPlayer[i]->GetState() == State::StrongAttack || 
			pPlayer[i]->GetState() == State::SpecialAttack){
			return;
		}
	}

	// --------------------------------------------------------------

	// �ǂ��炩��KO������
	if (isKO != -1){
		subWork = GameState::GameSet;
		workFrame = 0;
		gameFrame = 0;
	}
}


/**
* @brief �o�g���J�n�O�̏���
*/
void GameMain::UpdateBeforBattle()
{
	static unsigned short frame = 0;

	switch (m_beforBattleWork)
	{
	case 0:
		// �t�F�[�h���������Ă��Ȃ�������
		if (ScreenEffect::GetInstance()->isPlayFade()) return;

		// ��Ƀv���C���[�P����ԃZ�b�g����
		pPlayer[PLAYER1]->SetState(State::BeforBattle);
		m_beforBattleWork++;
		break;

	case 1:
		if (frame >= 60){
			m_beforBattleWork++;
		}
		break;

	case 2:
		// ��Ƀv���C���[�Q����ԃZ�b�g����
		pPlayer[PLAYER2]->SetState(State::BeforBattle);
		m_beforBattleWork++;
		break;

	case 3:
		// ���t���[���o�߂�
		if (frame >= 120){
			m_beforBattleWork = 0;
			frame = 0;
			// ���̃X�e�C�g��
			subWork = GameState::Set;
		}
		break;
	}

	// �v���C���[���X�V����
	for (int i = 0; i != pPlayer.size(); i++){
		pPlayer[i]->Update();
	}

	// �X�e�[�W���X�V����
	pStage->Update();

	// �p�[�e�B�N���̍X�V
	ParticleManager::GetInstance()->Update();

	// �t���[�������Z����
	frame++;
}


/**
*	@brief	�Z�b�g�����̍X�V����
*	@return true�ŏ����̏I��
*	@author	Syota Tachikawa
*	@since	2015/02/19
*/
void GameMain::UpdateSetBattle()
{
	// �����w��]
	magicAngle += GetPrm->MagicCircleAddAngle;

	switch (m_setBattleWork)
	{
	case 0:
		// �v���C���[�̏�Ԃ�ҋ@�ɐݒ肷��
		for (int i = 0; i != pPlayer.size(); i++)
		{
			pPlayer[i]->SetState(State::Neutral);
		}

		// �P���E���h�ڂ�������
		if (roundNow == 1){
			// BGM���Đ�����
			SoundPlayer::GetInstance()->LoopPlay(BATTLE_BGM);
		}
		m_setBattleWork++;
		break;

	case 1:
		if (workFrame >= 100){
			workFrame = 0;
			fightVX = GetPrm->FightFontVX;
			m_setBattleWork++;
		}
		break;

	case 2:
		// ���x���ʒu�ɉ��Z
		fightX += fightVX;

		if (fightX >= 570.0f)
		{
			fightVX = fightVX * 0.59f;
		}

		if (fightX >= GetPrm->FightFontX){
			fightX = GetPrm->FightFontX;
			fightVX = GetPrm->FightFontInitVX;
			workFrame = 0;
			m_setBattleWork++;
		}
		break;

	case 3:
		if (workFrame >= 30)
			m_setBattleWork++;
		break;

	case 4:
		// �Q�[���v���C��
		subWork = GameState::Play;
		break;
	}

	// �v���C���[���X�V����
	for (int i = 0; i != pPlayer.size(); i++){
		pPlayer[i]->Update();
	}

	// �X�e�[�W���X�V����
	pStage->Update();

	// �p�[�e�B�N���̍X�V
	ParticleManager::GetInstance()->Update();

	// �t���[���̍X�V
	workFrame++;
}


/**
*	@brief	�Z�b�g�����̕`�揈��
*	@author	Syota Tachikawa
*	@since	2015/02/19
*/
void GameMain::RenderSetBattle()
{
	// �Ԑ���
	ARGB a = { 255, 255, 0, 0 };

	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BER), 640.0f, 360.0f, 0.0f, 3.0f, 50);
	// �����w�`��
	m_2dTex->DrawTexture(mCircleTex[1], 1000.0f, 200.0f, magicAngle, 1.2f, ALPHA_MAX, true);
	// �����w�`��
	m_2dTex->DrawTexARGB(mCircleTex[0], 1000.0f, 200.0f, a, true, magicAngle, 1.2f);

	switch (m_setBattleWork)
	{
	case 1:
		if (roundNow == 1)
			m_2dTex->DrawTexture((m_texData->GetTexture(TEX_ROUND1_FONT)), 640.0f, 360.0f);
		else if (roundNow == 2)
			m_2dTex->DrawTexture((m_texData->GetTexture(TEX_ROUND2_FONT)), 640.0f, 360.0f);
		else if (roundNow == 3)
			m_2dTex->DrawTexture((m_texData->GetTexture(TEX_FINALROUND_FONT)), 640.0f, 360.0f);
		break;

	case 2:
	case 3:
		m_2dTex->DrawTexture((m_texData->GetTexture(TEX_FIGHT_FONT)), fightX, 360.0f);
		break;
	}
}

/**
* @brief �o�g�������̍X�V
*/
void GameMain::UpdateGameSet()
{
	// �L�[���͏�����
	for (int i = 0; i != m_dev.size(); i++){
		m_dev[i]->DataClear();
	}

	if (gameFrame % adjustFrame == 0)
	{
		switch (m_gameSetWork)
		{
		case 0:
			if (UpdateGameKO()) {
				adjustFrame = 1;
				pPlayer[losePlNum]->SetState(State::Ko);
				m_gameSetWork++;
			}
			break;

		case 1:
			// �����J�E���g�𑝂₷
			if (losePlNum == PLAYER1)
			{
				winNum[PLAYER2]++;
			}
			else if (losePlNum == PLAYER2)
			{
				winNum[PLAYER1]++;
			}
			// ���E���h���𑝂₷
			roundNow++;

			m_gameSetWork++;
			break;

		case 2:
			if (workFrame > 120){
				// 2���E���h��悵����I��
				if (winNum[PLAYER1] >= 2 || winNum[PLAYER2] >= 2){
					subWork = GameState::KO;
				}
				else {
					subWork = GameState::Set;
					Initialize();
				}
			}
			break;
		}

		// �v���C���[���X�V����
		for (int i = 0; i != pPlayer.size(); i++){
			pPlayer[i]->Update();
			// �v���C���[�̌������X�V
			SetPlayerDirection(i);
		}

		// �X�e�[�W�[
		StageEnd();

		// �X�e�[�W���X�V����
		pStage->Update();

		// �p�[�e�B�N���̍X�V
		ParticleManager::GetInstance()->Update();

		// �G�t�F�N�g�̍X�V
		EffectManager::GetInstance()->Update();

		// �����蔻��t���G�t�F�N�g�̍X�V
		CollisionEffectManager::GetInstance()->Update();

		// �G�N�X�g���X�L���̍X�V
		UpdateExSkill();
	}
	workFrame++;
}

/**
* @brief �o�g��KO�̍X�V
*/
void GameMain::UpdateKO()
{
	int winPl;

	// �����v���C���[�̐ݒ�
	if (losePlNum == PLAYER1)
		winPl = PLAYER2;
	else if (losePlNum == PLAYER2)
		winPl = PLAYER1;

	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Vs2P)
	{
		// �{�^���̓��͂��m�F��������ꉉ�o�Ƀt���O�𗧂Ă�
		if (m_dev[winPl]->CheckInputMask(INPUT_01)){
			isSpecial = true;
		}
	}
	else if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU)
	{
		// �{�^���̓��͂��m�F��������ꉉ�o�Ƀt���O�𗧂Ă�
		if (m_dev[0]->CheckInputMask(INPUT_01)){
			isSpecial = true;
		}
	}

	if (isSpecial)
	{
		// �����v���C���[����ꉉ�o��Ԃɂ���
		pPlayer[winPl]->SetState(State::SpecialProduction);

		// �t���[������萔�𒴂����牉�o�Ɉڂ�
		if (workFrame > 120){
			workFrame = 0;
			// �t�F�[�h�̐ݒ�
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::White, FADE_FRAME);
			// �{�C�X�̐ݒ�
			switch (selectChara[losePlNum])
			{
			case LILIA:
				SoundPlayer::GetInstance()->Play(LILIA_GASP_VOICE);
				break;

			case RUNA:
				SoundPlayer::GetInstance()->Play(RUNA_GASP_VOICE);
				break;
			}
			// �T�u���[�N����ꉉ�o�ɐݒ�
			subWork = GameState::Special;
		}

		// �t���[�������Z����
		workFrame++;
	}
	// ���ꉉ�o�t���O�������Ă��Ȃ���΃t���[������
	else {
		workFrame++;
	}

	// �{�^�������͂��ꂸ�Ɉ��t���[���߂�����o�g�����I��������
	if (workFrame >= 300)
	{
		subWork = GameState::End;
	}

	// �p�[�e�B�N���̍X�V
	ParticleManager::GetInstance()->Update();

	// �G�t�F�N�g�̍X�V
	EffectManager::GetInstance()->Update();

	// ���̓f�o�C�X�̍X�V
	for (int i = 0; i != m_dev.size(); i++){
		m_dev[i]->GetInput();
	}
}

/**
* @brief KO�����̏���
*/
bool GameMain::UpdateGameKO()
{
	switch (gameWork)
	{
	case 0:
		// �s�k�v���C���[�ݒ�
		losePlNum = isKO;
		// �t���[��������
		workFrame = 0;
		// ���ʉ����Đ�����
		SoundPlayer::GetInstance()->Play(KO_SE);
		// �{�C�X���Đ�����
		// �{�C�X�̐ݒ�
		switch (selectChara[losePlNum])
		{
		case LILIA:
			SoundPlayer::GetInstance()->Play(LILIA_LOSE_VOICE);
			break;

		case RUNA:
			SoundPlayer::GetInstance()->Play(RUNA_LOSE_VOICE);
			break;
		}
		gameWork++;
		break;

	case 1:
		// �t���[������
		adjustFrame = 13;
		// KO�����v���C���[�̏�Ԃ�ݒ�
		pPlayer[isKO]->SetState(State::Ko);
		gameWork++;
		break;

	case 2:
		if (workFrame >= 120){
			// �߂�
			adjustFrame = 1;
		}

		// �n�ʂɕt���܂�
		if (pPlayer[isKO]->GetPos().y < GetPrm->Ground){
			return false;
		}

		// �ǂ��炩���ҋ@��Ԃɖ߂�����			
		if (workFrame > 240)
		{
			gameWork++;
			workFrame = 0;
		}
		break;

	case 3:
		if (isKO == PLAYER1){
			pPlayer[PLAYER2]->SetState(State::Win);
		}

		else if (isKO == PLAYER2){
			pPlayer[PLAYER1]->SetState(State::Win);
		}

		if (workFrame >= 120)
		{
			workFrame = 0;
			return true;
		}
		break;
	}
	return false;
}

/**
* @brief �o�g������V�[���̍X�V
*/
void GameMain::UpdateSpecial()
{
	int black[3] = { 0, 0, 0 };

	// ���ꉉ�o���I�������
	if (SpecialProduction())
	{
		// �k�[�h
		displayNumber[PLAYER2] = NUDE;
		// �o�g���̏I��
		subWork = GameState::End;
		// �t�F�[�h�̐ݒ�
		ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);

		workFrame = 0;
	}

	// �v���C���[���X�V����
	for (int i = 0; i != pPlayer.size(); i++){
		pPlayer[i]->Update();
	}

	// �X�e�[�W�[
	StageEnd();

	// �X�e�[�W���X�V����
	pStage->Update();

	// �G�t�F�N�g�̍X�V
	EffectManager::GetInstance()->Update();

	// �����蔻��t���̃G�t�F�N�g�̍X�V
	CollisionEffectManager::GetInstance()->Update();

	// �p�[�e�B�N���̍X�V
	ParticleManager::GetInstance()->Update();

	// �����蔻��̍X�V
	for (int i = 0; i != pPlayer.size(); i++){
		CheckUpperAttackCollide(i);
	}
}

/**
* @brief �o�g���I���̍X�V
*/
void GameMain::UpdateEnd()
{
	if (!ScreenEffect::GetInstance()->isPlayFade())
		subWork = GameState::Exit;

	// �t���[������
	workFrame++;
}

/**
* @brief �o�g���I���̍X�V
*/
void GameMain::UpdateExit()
{
	// �������v���C���[�ԍ���]������
	UniqueData::GetInstance()->SetLosePlayer(losePlNum);

	if (UniqueData::GetInstance()->GetGameMode() == GameMode::Demo)
		// �f���v���C�Ȃ�^�C�g����ʂɔ�΂�
		SequenceChanger::GetInstance()->ChangeScene(new Title());
	else
		// �ʏ�o�g���Ȃ烊�U���g��ʂɔ�΂�
		SequenceChanger::GetInstance()->ChangeScene(new Result());
}



/**
* @brief �w�i�ɕ`�悷��
*/
void GameMain::RenderBackGround()
{
	// �K�E�Z���ɔw�i�ɖ����w���g��Ɖ�]�������ĕ`�悷��
	for (int i = 0; i != pPlayer.size(); i++){
		if (pPlayer[i]->GetState() == State::SpecialAttack || pPlayer[i]->GetState() == State::AttackSpecialPursuit)
		{
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_VSPREPARATION_BG), 640.0f, 360.0f);
			m_2dTex->DrawTexture(mCircleTex[0], 640.0f, 360.0f, mCircleAngle, mCircleScale, mCircleAlpha, true);
		}
	}

	if (pPlayer[PLAYER1]->GetState() == State::SpecialAttack)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_MAGICCIRCLE_P), pPlayer[PLAYER2]->GetPos().x - GetCameraPos, pPlayer[PLAYER2]->GetPos().y + 50.0f, 0.0f, 1.2f);
	if (pPlayer[PLAYER2]->GetState() == State::SpecialAttack)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_MAGICCIRCLE_P), pPlayer[PLAYER1]->GetPos().x - GetCameraPos, pPlayer[PLAYER1]->GetPos().y + 50.0f, 0.0f, 1.2f);

	// ���ꉉ�o��
	if (pPlayer[PLAYER1]->GetState() == State::SpecialProduction || pPlayer[PLAYER2]->GetState() == State::SpecialProduction)
	{
		m_2dTex->DrawBox(0.0f - 100.0f + swingVal[0], 0.0f - 100.0f + swingVal[0], AppIns->GetWindowWidth() + 100.0f + swingVal[0], AppIns->GetWindowHeight() + 100.0f + swingVal[0], 0xffffffff);
	}
}

/**
* @brief �v���C���[���m�̓����蔻��
*/
void GameMain::CheckPlayerCollide(int index)
{
	// �v���C���[�̐��������[�v
	for(int i = 0; i != pPlayer.size(); i++)
	{
		// �����͏���
		if (i == index) {
			continue;
		}

		// ����`�F�b�N
		if (Collide::CheckRectAndRect(pPlayer[index]->GetPos(), pPlayer[i]->GetPos(),
			pPlayer[index]->GetHitRect(), pPlayer[i]->GetHitRect()))
		{
			// �ϐ��������������`���Ă���
			Vector2 pos1 = pPlayer[index]->GetPos();
			Vector2 pos2 = pPlayer[i]->GetPos();
			Dir dir1 = pPlayer[index]->GetDirection();
			Dir dir2 = pPlayer[i]->GetDirection();

			// �Y�����l���v���C���[���W�ɉ��Z
			pos1.x += Collide::PlayerDisplace(pos1, pos2, pPlayer[index]->GetHitRect(), pPlayer[i]->GetHitRect(), dir1);
			// ���W�Z�b�g
			pPlayer[index]->SetPos(pos1);

			// �Y�����l���v���C���[���W�ɉ��Z
			pos2.x += Collide::PlayerDisplace(pos2, pos1, pPlayer[i]->GetHitRect(), pPlayer[index]->GetHitRect(), dir2);
			// ���W�Z�b�g
			pPlayer[i]->SetPos(pos2);
		}
	}
}

/**
* @brief ��i�U���̓����蔻��
*/
void GameMain::CheckUpperAttackCollide(int index)
{
	// �U�����肪�������Ă��Ȃ������珈�����I������
	if (!pPlayer[index]->isAttackJudge()){
		return;
	}
	
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �����͏���
		if (i == index) {
			continue;
		}

		// �������Ă��Ȃ������珈�����I������
		if (!pPlayer[index]->isUpperAttackHit(*pPlayer[i])){
			return;
		}

		// ��e���̏���
		pPlayer[i]->Damage(*pPlayer[index], AttackPoint::Upper);

		// �K�[�h
		if (pPlayer[i]->GetState() == State::Guard || pPlayer[i]->GetState() == State::GuardNow)
		{
			// �_���[�W��������
			UpdateAttackDamage(index);
			// �K�E�Z�Q�[�W���Z
			spGauge->Add(2.0f, i);
			return;
		}

		// �R���{���𑝂₷
		combo.Add(index);
		// �K�E�Z�Q�[�W�`���[�W
		spGauge->Add(7.0f, index);

		// �p�[�e�B�N������
		for (int p = 0; p < 10; p++){
			int scale = rand() % 3;
			ParticleManager::GetInstance()->Add(make_shared<HitParticle>(pPlayer[i]->GetPos(), 0.35f));
		}

		// �q�b�g�X�g�b�v���s��
		switch (pPlayer[index]->GetState())
		{
		case State::WeakAttack:
		case State::MediumAttack:
		case State::SpecialProduction:
			int stopF;
			if (pPlayer[index]->GetState() == State::WeakAttack ||
				pPlayer[index]->GetState() == State::MediumAttack)
			{
				stopF = 4;
			}
			else{
				isSwing[0] = true;
				isSwing[1] = true;
				stopF = 120;
			}
			// �Q�[�����~�߂�
			SetGameStop(stopF, true);
			break;

		case State::WeakDerivationAttack:
			// �Q�[�����~�߂�
			SetGameStop(8, true);
			break;

		case State::DashAttack:
		case State::RaidAttack:
			// �Q�[�����~�߂�
			SetGameStop(6, true);
			break;

		case State::AttackSpecialPursuit:
		{
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::White, FADE_FRAME);
			// �Q�[�����~�߂�
			SetGameStop(120, true);
			break;
		}


		case State::JumpAttack:
			// �Q�[�����~�߂�
			SetGameStop(3, true);
			break;
		}

		// �[�����̈ʒu�C��
		StageEndShift(index);
		// �_���[�W�����Z
		UpdateAttackDamage(index);
	}
}

/**
* @brief ���i�U���̓����蔻��
*/
void GameMain::CheckLowerAttackCollide(int index)
{
	// �U�����肪�������Ă��Ȃ������珈�����I������
	if (!pPlayer[index]->isAttackJudge()){
		return;
	}

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �����͏���
		if (i == index) {
			continue;
		}

		// �������Ă��Ȃ������珈�����I������
		if (!pPlayer[index]->isLowerAttackHit(*pPlayer[i])){
			return;
		}

		// ��e���̏���
		pPlayer[i]->Damage(*pPlayer[index], AttackPoint::Lower);

		// �K�[�h
		if (pPlayer[i]->GetState() == State::SquatGuard || pPlayer[i]->GetState() == State::SquatGuardNow)
		{
			// �_���[�W��������
			UpdateAttackDamage(index);
			// �K�E�Z�Q�[�W���Z
			spGauge->Add(2.0f, i);
			return;
		}

		// �R���{���𑝂₷
		combo.Add(index);
		// �K�E�Z�Q�[�W�`���[�W
		spGauge->Add(7.0f, index);

		// �p�[�e�B�N������
		for (int p = 0; p < 10; p++){
			int scale = rand() % 3;
			ParticleManager::GetInstance()->Add(make_shared<HitParticle>(pPlayer[i]->GetPos(), 0.35f));
		}

		// �[�����̈ʒu�C��
		StageEndShift(index);
		// �_���[�W�����Z
		UpdateAttackDamage(index);
	}
}

/**
* @brief ���E����
*/
void GameMain::CheckOffsetCollide(int index)
{
	// �U�����肪�������Ă��Ȃ������珈�����I������
	if (!pPlayer[index]->isAttackJudge()){
		return;
	}

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �����͏���
		if (i == index){
			continue;
		}

		// �����U����ԂłȂ��Ɣ��������Ȃ�
		if (pPlayer[index]->GetState() != pPlayer[i]->GetState()){
			return;
		}

		if (Collide::CheckRectAndRect(pPlayer[index]->GetPos(), pPlayer[i]->GetPos(),
			pPlayer[index]->GetAttackRect(), pPlayer[i]->GetAttackRect()))
		{
			// ���ʉ��̐ݒ�
			SoundPlayer::GetInstance()->Play(OFFSET_SE);
			pPlayer[index]->SetState(State::Offset);
			pPlayer[i]->SetState(State::Offset);

			// ���S���o��
			float centerPos = (pPlayer[index]->GetPos().x + pPlayer[i]->GetPos().x) / 2;

			// �p�[�e�B�N������
			for (int i = 0; i < 10; i++)
				ParticleManager::GetInstance()->Add(make_shared<OffsetParticle>(Vector2(centerPos, pPlayer[index]->GetPos().y)));
		}
	}
}

void GameMain::CheckEffectCollide(int index)
{
	// �������Ă��邩�̃`�F�b�N
	CollisionEffectManager::GetInstance()->CollisionCheckPlayer(pPlayer[index]);

	if (pPlayer[index]->GetState() != State::DamageEffect) return;

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �����͏���
		if (i == index) {
			continue;
		}

		// �R���{���𑝂₷
		combo.Add(i);
		// �_���[�W
		UpdateAttackDamage(i);
	}

}

void GameMain::SetPlayerDirection(int index)
{
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �����͏���
		if (i == index){
			continue;
		}

		if (pPlayer[index]->GetPos().x < pPlayer[i]->GetPos().x){
			pPlayer[i]->SetDirection(Dir::Left);
			pPlayer[index]->SetDirection(Dir::Right);
		}
		else{
			pPlayer[i]->SetDirection(Dir::Right);
			pPlayer[index]->SetDirection(Dir::Left);
		}
	}
}

/**
* @brief �L�����N�^�[�̍X�V
*/
void GameMain::UpdateCharacter(int index)
{
	// �R���s���[�^�[�̐����擾����
	int comCount = UniqueData::GetInstance()->GetComputerCount();

	// �R���s���[�^�[�̍X�V����
	m_com.ThinkUpdate(pPlayer, index, comCount, spGauge);
	
	// ���̓f�o�C�X�̐����擾����
	int devCount = m_dev.size();

	if (index > devCount - 1) return;

	// ����̏����𖞂������ꍇ�͔h���Z���o����
	if (pPlayer[index]->GetState() == State::WeakAttack && 
		pPlayer[index]->CanDerivation() && 
		m_dev[index]->CheckInputMask(INPUT_01))
	{
		// �h���U��
		pPlayer[index]->SetState(State::WeakDerivationAttack);
		return;
	}

	if (pPlayer[index]->GetState() == State::Jump || pPlayer[index]->GetState() == State::JumpFront || 
		pPlayer[index]->GetState() == State::JumpBack || pPlayer[index]->GetState() == State::JumpGuard)
	{
		// �W�����v�K�[�h
		if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right){
			pPlayer[index]->SetState(State::JumpGuard);
		}
		else if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left){
			pPlayer[index]->SetState(State::JumpGuard);
		}

		// �{�^�������͂��ꂽ��
		if (m_dev[index]->CheckInputMask(INPUT_01)){
			pPlayer[index]->SetState(State::JumpAttack);
		}
	}

	if (m_dev[index]->CheckInput(INPUT_01) && pPlayer[index]->CanPassive()){
		pPlayer[index]->SetState(State::Passive);
	}

	// ����s�\�Ȃ珈���I��
	if (!pPlayer[index]->CanControll()) return;

	// ����s�\��ԂȂ珈�������Ȃ�
	if (!pPlayer[index]->isControll()) return;

	// ���U��
	if (m_dev[index]->CheckInputMask(INPUT_04))
	{
		// �Q�[�W�ʂ̊m�F�i�s�����Ă��珈�����Ȃ��j
		if (!spGauge->IsUseGauge(State::StrongAttack, pPlayer[index]->GetID())) return;
		spGauge->Use(pPlayer[index]->GetID());
		isUseExSkill[index] = true;
		pPlayer[index]->SetState(State::StrongAttack);
		return;
	}
	// �K�E�Z
	else if (m_dev[index]->CheckInputMask(INPUT_02))
	{
		// �Q�[�W�ʂ̊m�F�i�s�����Ă��珈�����Ȃ��j
		if (!spGauge->IsUseGauge(State::SpecialAttack, pPlayer[index]->GetID())) return;
		spGauge->Use(pPlayer[index]->GetID());
		pPlayer[index]->SetState(State::SpecialAttack);
		return;
	}

	// �ҋ@
	if (m_dev[index]->GetInputState() == NULL){
		pPlayer[index]->SetState(State::Neutral);
	}

	// �O�i
	if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Left)
		pPlayer[index]->SetState(State::Advance);

	// �K�[�h
	else if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right)
		pPlayer[index]->SetState(State::Guard);

	// �O�i
	if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Right)
		pPlayer[index]->SetState(State::Advance);

	// �K�[�h
	else if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left)
		pPlayer[index]->SetState(State::Guard);

	// ���Ⴊ��
	if (m_dev[index]->CheckInput(INPUT_DOWN))
		pPlayer[index]->SetState(State::Squat);

	// ���Ⴊ�݃K�[�h
	if (m_dev[index]->CheckInput(INPUT_DOWN) && m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right)
		pPlayer[index]->SetState(State::SquatGuard);

	// ���Ⴊ�݃K�[�h
	else if (m_dev[index]->CheckInput(INPUT_DOWN) && m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left)
		pPlayer[index]->SetState(State::SquatGuard);

	// ���Ⴊ�ݍU��
	if (m_dev[index]->CheckInputMask(INPUT_01) && pPlayer[index]->GetState() == State::Squat){
		pPlayer[index]->SetState(State::SquatAttack);
		return;
	}
	// ���Ⴊ�݃K�[�h
	else if (m_dev[index]->CheckInputMask(INPUT_01) && pPlayer[index]->GetState() == State::SquatGuard){
		pPlayer[index]->SetState(State::SquatAttack);
		return;
	}

	// �������U��
	if (pPlayer[index]->GetState() == State::Squat && m_dev[index]->CheckInputMask(INPUT_03)){
//	if (cmd[index]->GetSkillNumber() == 0){
		pPlayer[index]->SetState(State::UnderAttack);
		return;
	}

	// �������U��
	else if (pPlayer[index]->GetState() == State::SquatGuard && m_dev[index]->CheckInputMask(INPUT_03)){
		pPlayer[index]->SetState(State::UnderAttack);
		return;
	}

	// �_�b�V��
	if (m_dev[index]->GetJoyStickRepel() && pPlayer[index]->GetState() == State::Advance)
		pPlayer[index]->SetState(State::Dash);

	// �o�b�N�X�e�b�v
	else if (m_dev[index]->GetJoyStickRepel() && pPlayer[index]->GetState() == State::Guard)
		pPlayer[index]->SetState(State::BackStep);

	// �_�b�V���U��
	if (pPlayer[index]->GetState() == State::Dash &&m_dev[index]->CheckInputMask(INPUT_01)){
		pPlayer[index]->SetState(State::DashAttack);
		return;
	}

	// �X�e�B�b�N���͂���
	if (m_dev[index]->CheckInput(INPUT_UP))
	{
		// �O�W�����v
		if (m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Right ||
			m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Left){
			pPlayer[index]->SetState(State::JumpFront);
		}
		// ��W�����v
		else if (m_dev[index]->CheckInput(INPUT_LEFT) && pPlayer[index]->GetDirection() == Dir::Right || 
			m_dev[index]->CheckInput(INPUT_RIGHT) && pPlayer[index]->GetDirection() == Dir::Left){
			pPlayer[index]->SetState(State::JumpBack);
		}
		// �W�����v
		else
			pPlayer[index]->SetState(State::Jump);
	}

	// ��P�U��
	if (m_dev[index]->CheckInputMask(INPUT_01) && m_dev[index]->CheckInputMask(INPUT_03))
		pPlayer[index]->SetState(State::RaidAttack);

	// ��U��
	else if (m_dev[index]->CheckInputMask(INPUT_01))
		pPlayer[index]->SetState(State::WeakAttack);

	// ���U��
	else if (m_dev[index]->CheckInputMask(INPUT_03))
		pPlayer[index]->SetState(State::MediumAttack);
}

/**
*	@brief	���s���t�������ۂ����擾
*
*	@author	Syota Tachikawa
*	@since	2015/12/22
*/
void GameMain::GetCheckKO()
{
	isKO = hpGauge.isDead();
}

/**
* @brief �U���҂̔ԍ�
*/
void GameMain::UpdateAttackDamage(int index)
{
	float damage = pPlayer[index]->GetPower();

	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �����͓���Ȃ�
		if (index == i){
			continue;
		}

		// �p���[�A�b�v���̃_���[�W���Z��(LILIA�ȊO��0��������Ȃ�)
		damage += abs(powerUPLilia[index]);

		// �K�[�h���Ȃ��
		if (pPlayer[i]->GetState() == State::Guard ||
			pPlayer[i]->GetState() == State::JumpGuard ||
			pPlayer[i]->GetState() == State::GuardNow)
		{
			damage = damage / GetPrm->GuardDamageMitiGation;
		}

		damage = combo.ComboDamageCorrection(damage, index);

		hpGauge.DamageAdd(damage, i);
	}
}


/**
* @brief �G�N�X�g���X�L���̍X�V
*/
void GameMain::UpdateExSkill()
{
	// �t���[��
	static int frame = 0;

	// �t���[�������Z
	frame++;

	for (int i = 0; i < JOY_MAX; i++)
	{
		// �G�N�X�g���X�L������������w�i���Â�����
		if (isUseExSkill[i]){
			// �G�t�F�N�g�𐶐�����
			EffectManager::GetInstance()->Add(make_shared<ShineEffect>(pPlayer[i]->GetPos()));
			// ���ʉ����Đ�����
			SoundPlayer::GetInstance()->Play(EXTRASKILL_SE);
			// �t���O��܂�
			isUseExSkill[i] = false;
			// �Q�[�����~�߂�
			SetGameStop(20, true);
			// �A���t�@�l�̕ύX
			stageAlpha = 150;
		}
		else {
			if (frame > 60){
				frame = 0;
				stageAlpha = ALPHA_MAX;
			}
		}

	}
	// �R���s���[�^�[�̐����擾����
	int comCount = UniqueData::GetInstance()->GetComputerCount();
	// �R���s���[�^�[�����݂�����
	if (comCount < 1) return;

	static bool flg = false;
	// ���U�����Ɉ�x������������
	if (pPlayer[PLAYER2]->GetState() == State::StrongAttack){
		// �t���O�������Ă���I��
		if (flg) return;

		// �G�N�X�g���X�L���t���OON
		isUseExSkill[PLAYER2] = true;
		flg = true;
	}
	else{
		flg = false;
	}
}

/**
* @brief �w�i�ɕ`�悷�閂���w�̍X�V
*/
void GameMain::UpdateBackGroundMagicCircle()
{
	// �K�E�Z�w�i�����w�X�V
	if (pPlayer[PLAYER1]->GetState() == State::SpecialAttack || pPlayer[PLAYER1]->GetState() == State::AttackSpecialPursuit ||
		pPlayer[PLAYER2]->GetState() == State::SpecialAttack || pPlayer[PLAYER2]->GetState() == State::AttackSpecialPursuit)
	{
		// �J�b�g�C�����\������Ă��Ȃ�������
		if (!CutInManager::GetInstance()->IsPlayCutIn()){
			mCircleAngle += 10.0f;
			mCircleAlpha++;
			mCircleScale += 0.003f;
		}
	}
	else{
		mCircleScale = 0.0f;
	}
}


void GameMain::ScreenSwing()
{
	int swingFrame = 1;

	for (int i = 0; i != pPlayer.size(); i++)
	{
		if (pPlayer[i]->GetState() == State::Blowoff){
			swingFrame = 20;
			isSwing[i] = true;
		}

		if (pPlayer[i]->GetState() == State::SpecialProduction)
		{
			swingFrame = 120;
		}

		// �X�N���[����h�炷�t���O��؂�
		if (gameFrame % swingFrame == 0)
		{
			isSwing[i] = false;
		}

		if (isSwing[i]){
			swingVal[i] = Utility::Random(-30.0f, 30.0f);
		}
		else{ swingVal[i] = 0; }
	}
}

/**
* @brief �j��G�t�F�N�g�̍X�V
*/
void GameMain::UpdateBreakClothes()
{
	for (int i = 0; i != pPlayer.size(); i++)
	{
		// �K�E�Z���͏��������Ȃ�
		if (pPlayer[i]->GetState() == State::SpecialAttack ||
			pPlayer[i]->GetState() == State::AttackSpecialPursuit)
			return;

		// �u���C�N�t���O�������Ă��Ȃ������珈�������Ȃ�
		if (!uiMgr->IsClothesBreak(i)) continue;

		// �Q�[�����~������
		SetGameStop(30, true);

		// �{�C�X�̐ݒ�
		switch (selectChara[i])
		{
		case LILIA:
			SoundPlayer::GetInstance()->Play(LILIA_SCREAM_VOICE);
			break;

		case RUNA:
			SoundPlayer::GetInstance()->Play(RUNA_SCREAM_VOICE);
			break;
		}

		// �A�p�[�e�B�N���𔭐�������
		for (int p = 0; p < 30; p++)
		{
			ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pPlayer[i]->GetPos(), Utility::Random(0.4f, 0.6f)));
		}

		// �t�F�[�h��������
		ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::White, 50);
	}
}

/**
*	@brief	���ꉉ�o
*	@author	Syota Tachikawa
*	@since	2015/01/27
*/
bool GameMain::SpecialProduction()
{
	switch (spWork)
	{
	case 0: // ����������
		workFrame = 0;
		if (!ScreenEffect::GetInstance()->isPlayFade()){
			for (int i = 0; i < 100; i++)
			{
				Vector2 pos = Vector2(Utility::Random(-20.0f, 1300.0f), Utility::Random(-20.0f, 800.0f));
				float scale = Utility::Random(1.5f, 3.0f);
				ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pos, scale));
				ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pos, scale));
				ParticleManager::GetInstance()->Add(make_shared<FormParticle>(pos, scale));
			}
			for (int i = 0; i < 5; i++){
				formX[i] = 150.0f * i;
				formY[i] = Utility::Random(10.0f, 710.0f);
			}

			spWork++;
		}
		break;

	case 1: // ����f��
		specialTexY = 1200.0f;
		workFrame++;
		if (workFrame >= 150){
			spWork++;
			workFrame = 0;
		}
		break;

	case 2: // �̂��f��
		specialTexY = 600.0f;
		workFrame++;
		if (workFrame >= 120){
			spWork++;
			workFrame = 0;
		}
		break;

	case 3: // �r���f��
		specialTexY = -100.0f;
		workFrame++;
		if (workFrame >= 120){
			spWork++;
			workFrame = 0;
			specialTexY = -400.0f;
		}
		break;

	case 4:
		workFrame++;
		specialTexY += 2.0f;
		if (specialTexY >= 1220.0f) {
			spWork++;
			specialTexY = 360.0f;
			specialTexScale[0] = 0.0f;
			workFrame = 0;
		}
		break;

	case 5:
		specialTexScale[0] += 0.001f;
		if (specialTexScale[0] >= 0.2f) {
			SoundPlayer::GetInstance()->Play(CHEER_SE);
			SoundPlayer::GetInstance()->Play(LAUGH_SE);
			spWork++;
		}
		break;

	case 6:
		workFrame++;
		if (workFrame >= 120){
			workFrame = 0;
			spWork = 0;
			return true;
		}
		break;
	}

	if (workFrame % 60)
	{
		if (formFlag)
			formFlag = false;
		else
			formFlag = true;
	}
	for (int i = 0; i < 5; i++){
		formX[i] += 0.3f;
		if (formFlag)
			formY[i] += 0.3f;
		else 
			formY[i] -= 0.3f;
	}

	light2Angle += 4.0f;

	return false;
}

/**
*	@brief	�Q�[���̍X�V���~�߂�
*	@param	frame - �~�߂�t���[����
*	@author	Syota Tachikawa
*	@since	2015/02/15
*/
void GameMain::SetGameStop(int frame , bool flag)
{
	stopFrame = frame;
	m_isGameStop = flag;
}

/**
* @brief �v���C���[���X�e�[�W�̒[�ōU�����Ă�����n����Ȃ��悤�ɑΏێ҂Ƌ����𗣂�
*/
void GameMain::StageEndShift(int index)
{
	for (int i = 0; i != pPlayer.size(); i++)
	{
		if (index == i) continue;

		if (pPlayer[i]->GetPos().x <= GetPrm->StageLeftShiftLimit || pPlayer[i]->GetPos().x >= GetPrm->StageRightShiftLimit)
		{
			pPlayer[index]->SetSpeed(-1.0f);
		}
	}
}

void GameMain::RenderSpecialProduction()
{
	// ���ꉉ�o���̔w�i
	if (spWork != 0)
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_BATTLE_BG_SPECIAL), 640.0f, 360.0f);

	// ���ꉉ�o���̃L�����N�^�[
	if (subWork == GameState::Special && spWork != 0){
		m_2dTex->DrawTexture(spcialTex[selectChara[losePlNum]], 680.0f, specialTexY, -3.0f, specialTexScale[0]);
		// �A�̕`��
		for (int i = 0; i < 5; i++)
			m_2dTex->DrawTexture(m_texData->GetTexture(TEX_FORM), formX[i], formY[i], 0.0f, 0.7f, 255, true);

		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 1100.0f, 200.0f, light2Angle, 0.4f, 255, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 100.0f, 500.0f, light2Angle, 0.4f, 255, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 600.0f, 300.0f, light2Angle, 0.4f, 255, true);
		m_2dTex->DrawTexture(m_texData->GetTexture(TEX_LIGHT3), 900.0f, 600.0f, light2Angle, 0.4f, 255, true);
	}

	if (subWork == GameState::Special){
		ParticleManager::GetInstance()->Render();
	}
}

void GameMain::UpdatePowerUp()
{
	// �ǂ��炩�̃v���C���[��HP�������ȏ゠�����珈�������Ȃ�
	if (hpGauge.GetHP(PLAYER1) >= GetPrm->HpMax / 2 ||
		hpGauge.GetHP(PLAYER2) >= GetPrm->HpMax / 2){
		return;
	}

		// �p���[�A�b�v�p�[�e�B�N��
		if (gameFrame % 10 == 0)
		{
			// ���W�o�^
			Vector2 plPos[2];
			Vector2 plLPos[2];
			Vector2 plRPos[2];

			for (int i = 0; i != pPlayer.size(); i++)
			{
				plPos[i] = Vector2(pPlayer[i]->GetPos().x, pPlayer[i]->GetPos().y + 130.0f);
				plPos[i] = Vector2(pPlayer[i]->GetPos().x - 10.0f, pPlayer[i]->GetPos().y + 120.0f);
				plPos[i] = Vector2(pPlayer[i]->GetPos().x + 10.0f, pPlayer[i]->GetPos().y + 120.0f);

				// ����
				ParticleManager::GetInstance()->Add(make_shared<PowerupParticle>(plPos[i], 1.0f, pwUpAlpha[i]));
				ParticleManager::GetInstance()->Add(make_shared<PowerupParticle>(plLPos[i], 1.0f, pwUpAlpha[i]));
				ParticleManager::GetInstance()->Add(make_shared<PowerupParticle>(plRPos[i], 1.0f, pwUpAlpha[i]));
			}
		}

	for (int i = 0; i != pPlayer.size(); i++)
	{
		switch (m_charaType[i])
		{
			// �L�����N�^�[�������A�̎�
		case LILIA:
			powerUPLilia[i] = hpGauge.GetHP(i) - GetPrm->HpMax / 2;
			pwUpAlpha[i] += 0.03f;
			// ������M��ƃp���[�A�b�v���̍U���͉��Z�ʂ�ύX�ł���
			if (pPlayer[i]->GetState() == State::SpecialAttack){
				powerUPLilia[i] = powerUPLilia[i] * 0.003f;	// �K�E�Z���͉��Z�ʂ��ɏ��ɂ���
			}
			else if (pPlayer[i]->GetState() == State::StrongAttack){
				powerUPLilia[i] = powerUPLilia[i] * 0.01f;
			}
			else{
				powerUPLilia[i] = powerUPLilia[i] * 0.05f;
			}
			break;
	
			// �L�����N�^�[�����i�̎�
		case RUNA:
			powerUPRuna[i] = hpGauge.GetHP(i) - GetPrm->HpMax / 2;
			pwUpAlpha[i] += 0.03f;

			powerUPRuna[i] = powerUPRuna[i] * 0.002f;
			break;
		}
	}
}

/**
* @brief �X�e�[�W�[����o�Ȃ��悤�ɂ���
*/
void GameMain::StageEnd()
{
	Vector2 end[2];
	
	for (int i = 0; i != pPlayer.size(); i++)
	{
		end[i].x = max(STAND_CHARACTER_WIDTH + CHARACTER_MARGIN + GetCameraPos, min(1080.0f - CHARACTER_MARGIN + GetCameraPos, pPlayer[i]->GetPos().x));
		end[i].y = pPlayer[i]->GetPos().y;
		// ���W��߂�
		pPlayer[i]->SetPos(end[i]);
	}
}

/**
* @brief �I��
*/
void GameMain::Finalize()
{
	// �o�g��BGM���~����
	SoundPlayer::GetInstance()->Stop(BATTLE_BGM);

	// �R���e�i�̗v�f�폜
	m_dev.erase(m_dev.begin(), m_dev.end());
	// �R���e�i�̗v�f�폜
	pPlayer.erase(pPlayer.begin(), pPlayer.end());
}