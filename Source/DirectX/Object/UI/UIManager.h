/**
* @file   UIManager.h
* @brief  UI���Ǘ�����
* @author Syota Tachikawa
*/

#ifndef ___UIMANAGER_H
#define ___UIMANAGER_H

#include "..\..\Common\StdAfx.h"
#include "SpecialGauge.h"
#include "HpGauge.h"

/**
* @brief UI���Ǘ�����N���X
*/
class UIManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	UIManager();
	
	/**
	* @brief �f�X�g���N�^
	*/
	~UIManager();

	/**
	* @brief ������
	*/
	void Initialize();

	/**
	* @brief �X�V
	*/
	void Update(int breakState[], HpGauge hp);

	/**
	* @brief �`��
	*/
	void Render(int winCount[], float swingAdd[], const SpGaugePtr& sp, HpGauge hp);

	/**
	* @brief �ߕ����j�ꂽ
	*/
	bool IsClothesBreak(int index);

	/**
	* @brief �Q�[�W�f�[�^��ݒ�
	*/
	bool SetGaugeData(int index);

private:

	const float GAUGE_SIZE_X = 289.0f;

	/// �O���t�B�b�N�X�}�l�[�W��
	GraphicsManager* m_2dTex;

	/// �e�N�X�`���f�[�^
	TextureData* m_texData;

	/// HP�Q�[�W�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_tex;
	LPDIRECT3DTEXTURE9 m_oldTex;

	/// �����A�̗����G�e�N�X�`��
	int m_standLiliaTex[6];

	/// ���i�̗����G�e�N�X�`��
	int m_standRunaTex[6];

	/// ���E�ɕ\������L�����N�^�[�̗����G�ԍ�
	int m_displayNumber[JOY_MAX];

	/// ���E�ɕ\������L�����N�^�[�̗����G���
	int m_standCharaState[JOY_MAX];

	/// ���E�ɕ\������L�����N�^�[�̗����G�̔w�i
	int m_standCharaBack[3];

	/// �����G�̈ߕ����
	int m_breakClothesCount[JOY_MAX];

	/// �I�������L�����N�^�[
	const int* m_selectChara;

	/// �����e�N�X�`��
	int m_numberTex[NUMBER_MAX];

	/// �ߕ����j�ꂽ
	bool m_isClothesBreak[JOY_MAX];

	/// �K�E�Z�Q�[�W�̐�����\��������W
	float m_spGaugeNumberX[JOY_MAX];

};

#endif