#include "CharaSelect.h"
#include "VSPreparation.h"
#include "GameMain.h"
#include "SequenceChanger.h"
#include "..\DirectX\SoundPlayer.h"
#include "..\Common\ParamLoader.h"
#include "..\Common\UniqueData.h"
#include "..\Common\Utility.h"

vector<unique_ptr<CHARAICON>> icn;
vector<unique_ptr<CURSOL>> cur;
vector<unique_ptr<BACKCHARA>> back;
vector<unique_ptr<MAGICAL>> mgc;
vector<unique_ptr<SELECTCHARA>> slc;

const int MAGICAL_TEX_MAX = 20;

/**
* @brief 作成
*/
void CharaSelect::Create()
{
	// インスタンスの作成
	m_2dTex = GetGraphicsManager;
	m_texData = GetTextureData;
	
	// CPU対戦ならデバイスを一つしか作らない
	if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU){
		m_dev.emplace_back(new InputMask(0));
	}
	else{
		for (int i = 0; i < JOY_MAX; i++){
			m_dev.emplace_back(new InputMask(i));
		}
	}
}

/**
* @brief 初期化
*/
void CharaSelect::Initialize()
{
	controlJoy = 0;
	subWork = 0;
	animFrame = 0;
	adjustAnimFrame = 1;
	m_cursolNum = 0;

	for (int i = 0; i < JOY_MAX; i++)
	{
		// メモリの確保
		back.emplace_back(new BACKCHARA);
		back[i]->y = 600.0f;
		back[i]->vx = 0.0f;
		back[i]->flag = false;
		back[i]->isSet = true;
		back[i]->isDisp = false;
		back[i]->frame = 0;

		// アイコン
		icn.emplace_back(new CHARAICON());
		icn[i]->x = (i + 1) * 400.0f;
		icn[i]->y = 580.0f;
		icn[i]->kind = NULL;


		slc.emplace_back(new SELECTCHARA);
		slc[i]->y = 350.0f;
		slc[i]->isDisp = false;
		slc[i]->isFlash = false;
		slc[i]->alpha = ALPHA_MAX;
	}

	float temp = 0.0f;	// 一時変数

	// メモリの確保
	for (int i = 0; i < JOY_MAX; i++)
	{
		cur.emplace_back(new CURSOL);

		if (i == 1) temp = 40.0f;

		cur[i]->x = 380.0f + temp;
		cur[i]->y = 480.0f;
		cur[i]->num = 0;
		cur[i]->isSelect = false;
		cur[i]->frame = 0;
	}


	// 選択立ち絵キャラ
	slc[0]->x = 100.0f;
	slc[1]->x = 1180.0f;

	// 背景キャラ
	back[PLAYER1]->initX = 200.0f;
	back[PLAYER1]->x = back[PLAYER1]->initX;
	back[PLAYER1]->alpha = back[PLAYER2]->alpha = 0;
	back[PLAYER2]->initX = 1080.0f;
	back[PLAYER2]->x = back[PLAYER2]->initX;

	for (int i = 0; i < MAGICAL_TEX_MAX; i++)
	{
		mgc.emplace_back(new MAGICAL);
		mgc[i]->tex[0] = m_texData->GetTexture(TEX_MAGIC_FONT_B);
		mgc[i]->tex[1] = m_texData->GetTexture(TEX_MAGIC_FONT_R);
		mgc[i]->pos.x = 0.0f;
		mgc[i]->pos.y = 0.0f;
		mgc[i]->v = 0.0f;
		mgc[i]->flag = false;
	}
	
	bgRot = 0.0f;

	// テクスチャのコピー-------------------------------------------------
	for (int plNum = 0; plNum < JOY_MAX; plNum++){
		for (int i = 0; i < 3; i++)
		{
			slc[plNum]->girl1[i] = m_texData->GetLiliaAnim(15 + i);
			slc[plNum]->girl1[i] = m_texData->GetLiliaAnim(15 + i);
			slc[plNum]->girl2[i] = m_texData->GetRunaAnim(12 + i);
			slc[plNum]->girl2[i] = m_texData->GetRunaAnim(12 + i);
		}
	}
	// キャラ背景
	back[LILIA]->tex = m_texData->GetTexture(TEX_LILIA_CUTIN_00);
	back[RUNA]->tex = m_texData->GetTexture(TEX_RUNA_CUTIN_00);
	// アイコン
	icn[LILIA]->tex = m_texData->GetTexture(TEX_LILIA_ICON);
	icn[RUNA]->tex = m_texData->GetTexture(TEX_RUNA_ICON);
	// キャラクター文字
	charaFont[LILIA] = m_texData->GetTexture(TEX_LILIA_FONT);
	charaFont[RUNA] = m_texData->GetTexture(TEX_RUNA_FONT);
	charaText[LILIA] = m_texData->GetTexture(TEX_LILIA_TEXT);
	charaText[RUNA] = m_texData->GetTexture(TEX_RUNA_TEXT);

	// カーソル
	cur[PLAYER1]->tex = m_texData->GetTexture(TEX_CURSOL_1P);
	cur[PLAYER2]->tex = m_texData->GetTexture(TEX_CURSOL_2P);

	// ------------------------------------------------------------------

	// BGMの再生
	SoundPlayer::GetInstance()->LoopPlay(CHARACTERSELECT_BGM);
}

/**
* @brief 初期化
*/
void CharaSelect::Animation()
{
	animFrame++;
	if (animFrame % adjustAnimFrame == 0)
	{
		animation++;
		if (animation >= animMax)
		{
			animation = 0;
		}
	}
}

/**
* @brief 更新
*/
void CharaSelect::Update()
{
	switch (subWork)
	{
	case 0:
		// フェードが終了したら次へ進む
		if (!ScreenEffect::GetInstance()->isPlayFade())
			subWork++;
		break;

	case 1:
		Animation();
		CursolMove();
		CharaMove();
		MagicalMove();
		// アニメーションを設定
		SetAnimation(3, 10);
		bgRot += 2;
		if (frame % 60 == 0) {
			MagicalCreate();
		}
		// キャラクターの選択が終了したら
		if (UpdateSelect()){
			// フェードを入れる
			ScreenEffect::GetInstance()->SetFade(Fade::Out, FadeColor::Black, FADE_FRAME);
			subWork++;
		}
		break;

	case 2:
		if (!ScreenEffect::GetInstance()->isPlayFade())
		{
			// 選択キャラクターを次のシーンへ渡す
			UniqueData::GetInstance()->SetSelectCharacter(m_selectChara);
			// シーン切り替え
			SequenceChanger::GetInstance()->ChangeScene(new VSPreparation());
		}
		break;
	}

	// フレーム更新
	frame++;
}

/**
* @brief 描画
*/
void CharaSelect::Render()
{
	// 加算
	static float a, a2;
	a += 0.07f;
	int alpha = static_cast<int>(sinf(a) * 255);

	// 背景
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CHARASELECT_BG), 640.0f, 360.0f);

	// 加算用
	for (auto& m : mgc)
	{
		if (m->flag){
			m_2dTex->DrawTexture(m->tex[m->kind], m->pos.x, m->pos.y, 90, 0.3f, 255);
			m_2dTex->DrawTexture(m->tex[m->kind], m->pos.x, m->pos.y, 90, 0.3f, alpha, true);
		}
	}

	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_MAGICCIRCLE_G), 640.0f, 200.0f, bgRot);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_MAGICCIRCLE_G), 640.0f, 200.0f, bgRot, 1.0f, alpha, true);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CHARASELECT_BG2), 640.0f, 360.0f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CHARASELECT_BG2), 640.0f, 360.0f, 0.0f, 1.0f, alpha, true);
	
	// 背景キャラクター
	if (back[PLAYER1]->isDisp)
		m_2dTex->DrawTexture(back[cur[0]->num]->tex, back[0]->x, back[0]->y, 0, 0.9f, back[0]->alpha);
	if (back[PLAYER2]->isDisp)
		m_2dTex->DrawTexture(back[cur[1]->num]->tex, back[1]->x, back[1]->y, 0, 0.9f, back[1]->alpha);

	// カーソル
	for (auto& p : cur)
	{
		m_2dTex->DrawTexture(p->tex, p->x, p->y, 180.0f, 0.5f);
	}

	// 赤成分
	ARGB red = { 255, 255, 0, 0 };

	// 選択されているミニキャラの表示
	if (slc[0]->isDisp){
		if (cur[0]->num == 0)
			m_2dTex->DrawTexture(slc[0]->girl1[animation], slc[0]->x, slc[0]->y, 0.0f, 1.0f, slc[0]->alpha);
		else
			m_2dTex->DrawTexture(slc[0]->girl2[animation], slc[0]->x, slc[0]->y, 0.0f, 1.0f, slc[0]->alpha);

		m_2dTex->DrawTexture(charaFont[cur[0]->num], 150.0f, 530.0f);
		m_2dTex->DrawTexture(charaText[cur[0]->num], 450.0f, 300.0f);
	}

	if (slc[1]->isDisp){
		if (cur[1]->num == 0)
			m_2dTex->DrawTexture(slc[1]->girl1[animation], slc[1]->x, slc[1]->y, 0.0f, 1.0f, slc[1]->alpha, false, true);
		else 
			m_2dTex->DrawTexture(slc[1]->girl2[animation], slc[1]->x, slc[1]->y, 0.0f, 1.0f, slc[1]->alpha, false, true);

		m_2dTex->DrawTexture(charaFont[cur[1]->num], 1150.0f, 530.0f);
		m_2dTex->DrawTexture(charaText[cur[1]->num], 850.0f, 300.0f);
	}

	// キャラアイコン
	for(auto& i : icn)
	{
		m_2dTex->DrawTexture(i->tex, i->x, i->y, 0.0f, 0.5f);
	}

	// CharacterSelect文字
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_CHARASELECT_FONT), 640.0f, 50.0f, 0.0f, 0.45f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PLAYER1_FONT), 500.0f, 140.0f, 0.0f, 0.15f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_PLAYER2_FONT), 780.0f, 140.0f, 0.0f, 0.15f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_DESCRIOTION_FRAME), 640.0f, 680.0f);
	m_2dTex->DrawTexture(m_texData->GetTexture(TEX_DESCRIOTION_FONT), 640.0f, 680.0f);
}


/**
*	@brief	キャラクター選択
*	@author	Syota Tachikawa
*	@return true - 処理の終了、false - 処理の継続
*	@since	2015/01/05
*/
bool CharaSelect::UpdateSelect()
{
	for (int i = 0; i != m_dev.size(); i++)
	{
		// カーソル番号とデバイス番号を同期させる
		m_cursolNum = i;

		// CPU対戦ならコントローラー1つで制御
		if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU)
		{
			// １キャラ目が選択されたら２キャラ目の操作に移る
			if (cur[PLAYER1]->isSelect) {
				m_cursolNum = 1; // 制御権を1Pコントローラーへ	
			}
		}

		// キャラクターが選択されていなかったら
		if (!cur[m_cursolNum]->isSelect)
		{
			if (m_dev[i]->CheckInputMask(INPUT_01))
			{
				switch (cur[m_cursolNum]->num)
				{
				case LILIA:
					// ボイスと効果音の再生
					SoundPlayer::GetInstance()->Play(LILIA_CHARASELECT_VOICE);
					SoundPlayer::GetInstance()->Play(DECISION_SE);
					// キャラクターの種類を登録
					m_selectChara[m_cursolNum] = LILIA;
					break;

				case RUNA:
					// ボイスと効果音の再生
					SoundPlayer::GetInstance()->Play(RUNA_CHARASELECT_VOICE);
					SoundPlayer::GetInstance()->Play(DECISION_SE);
					// キャラクターの種類を登録
					m_selectChara[m_cursolNum] = RUNA;
					break;
				}
				// 選択済みフラグを立てる
				cur[m_cursolNum]->isSelect = true;
				// キャラクターのアルファ値を設定する
				slc[m_cursolNum]->alpha = 100;
			}
		}

		// 選択状態のキャンセル
		if (m_dev[i]->CheckInputMask(INPUT_02))
		{
			cur[m_cursolNum]->isSelect = false;
			slc[m_cursolNum]->alpha = ALPHA_MAX;
		}
	}

	// 両方ともキャラクターを選択したら
	if (cur[PLAYER1]->isSelect && cur[PLAYER2]->isSelect)
	{
		static int waitFrame = 0;
		waitFrame++;
		if (waitFrame > 90){
			waitFrame = 0;
			return true;
		}
	}
	return false;
}


/**
*	@brief	カーソルの動き
*	@author	Syota Tachikawa
*	@since	2015/01/05
*/
void CharaSelect::CursolMove()
{
	int oldNum[2];
	// 現在のカーソル番号を代入
	oldNum[0] = cur[0]->num;
	oldNum[1] = cur[1]->num;

	for (int i = 0; i != m_dev.size(); i++)
	{
		// カーソル番号とデバイス番号を同期させる
		m_cursolNum = i;

		// CPU対戦ならコントローラー1つで制御
		if (UniqueData::GetInstance()->GetGameMode() == GameMode::VsCPU)
		{
			// １キャラ目が選択されたら２キャラ目の操作に移る
			if (cur[PLAYER1]->isSelect) {
				m_cursolNum = 1; // 制御権を1Pコントローラーへ	
			}
		}

		// コントローラーから入力を取得
		m_dev[i]->GetInput();

		if (!cur[m_cursolNum]->isSelect)
		{
			// カーソルフレーム更新
			cur[m_cursolNum]->frame++;
			if (cur[m_cursolNum]->frame >= 300)
			{
				switch (cur[m_cursolNum]->num)
				{
				case LILIA:
					SoundPlayer::GetInstance()->Play(LILIA_CHARASELECTWAIT_VOICE);
					break;

				case RUNA:
					SoundPlayer::GetInstance()->Play(RUNA_CHARASELECTWAIT_VOICE);
					break;
				}
				cur[m_cursolNum]->frame = 0;
			}

			// スティックが倒されたらカーソル番号(位置)を動かす
			if (m_dev[i]->CheckInputMask(INPUT_RIGHT))
			{
				cur[m_cursolNum]->num++;
				SoundPlayer::GetInstance()->Play(CURSOL_SE);
			}
			else if (m_dev[i]->CheckInputMask(INPUT_LEFT))
			{
				cur[m_cursolNum]->num--;
				SoundPlayer::GetInstance()->Play(CURSOL_SE);
			}

			// カーソルが範囲外に出ないように調整
			if (cur[m_cursolNum]->num < 0)
			{
				cur[m_cursolNum]->num = JOY_MAX - 1;
			}
			if (cur[m_cursolNum]->num >= JOY_MAX)
			{
				cur[m_cursolNum]->num = 0;
			}

			// 前のフレームと現在のフレームでカーソル位置が違ったら
			// 背景のキャラクターを動かすフラグを立てる
			if (oldNum[m_cursolNum] != cur[m_cursolNum]->num)
			{
				// カーソル
				cur[m_cursolNum]->frame = 0;
				// 背景キャラ
				back[m_cursolNum]->x = back[m_cursolNum]->initX;
				back[m_cursolNum]->frame = 0;
				back[m_cursolNum]->isSet = true;
				back[m_cursolNum]->isDisp = false;
				// 選択キャラ
				slc[m_cursolNum]->isDisp = false;
			}
		}

		// 一時変数
		float temp = 0.0f;
		// 変数名が分かりにくいのでコピー
		int joyStickNumber = m_cursolNum;

		if (joyStickNumber == 1) temp = 40.0f;

		switch (cur[m_cursolNum]->num)
		{
		case PLAYER1:
			cur[m_cursolNum]->x = 380.0f + temp;
			break;
		case PLAYER2:
			cur[m_cursolNum]->x = 780.0f + temp;
			break;
		}
	}
}


/**
*	@brief	背景キャラクターの移動
*	@author	Syota Tachikawa
*	@since	2015/01/07
*/
void CharaSelect::CharaMove()
{
	// 座標に速度を加算
	back[0]->x += back[0]->vx;
	back[1]->x -= back[1]->vx;
	
	// アルファ値を加算
	back[0]->alpha += GetPrm->BackCharacterAddAlpha;
	back[1]->alpha += GetPrm->BackCharacterAddAlpha;

	for (auto& b : back)
	{
		// カーソルが動いたら背景キャラクターを変更
		if (b->flag)
		{
			b->flag = false;
		}
	}

	// 指定座標で止める
	if (back[0]->x > GetPrm->BackPlayer1X)
	{
		back[0]->vx = 0;
		back[0]->x = GetPrm->BackPlayer1X;
	}
	if (back[1]->x < GetPrm->BackPlayer2X)
	{
		back[1]->vx = 0;
		back[1]->x = GetPrm->BackPlayer2X;
	}

	for (int i = 0; i < JOY_MAX; i++)
	{
		back[i]->frame++;

		if (back[i]->frame >= 30){
			slc[i]->isDisp = true;
		}

		// 一瞬のみ判定する
		if (back[i]->frame >= 60 && back[i]->frame <= 62){
			back[i]->isDisp = true;
			back[i]->vx = GetPrm->BackCharacterVX;
			back[i]->alpha = ALPHA_MIN;
		}
	}
}

/**
* @brief キャラクターアニメーション
*/
void CharaSelect::SetAnimation(const int aniMax, const int adjustAniFrame)
{
	animMax = aniMax;
	adjustAnimFrame = adjustAniFrame;
}

/**
*	@brief	空いてる配列を探す
*	@author	Syota Tachikawa
*	@since	2015/01/24
*/
int CharaSelect::FindEmptyArray()
{
	for (int i = 0; i<MAGICAL_TEX_MAX; i++)
	{
		if (!mgc[i]->flag){
			return i;
		}
	}
	return -1;
}


/**
*	@brief	魔法テクスチャの生成
*	@author	Syota Tachikawa
*	@since	2015/01/24
*/
void CharaSelect::MagicalCreate()
{
	int	idx = FindEmptyArray();
	if (idx == -1) return;

	mgc[idx]->pos.x = Utility::Random(0.0f, 1280.0f);
	mgc[idx]->v = GetPrm->MagicFontVX;
	mgc[idx]->flag = true;
	mgc[idx]->kind = rand() % 2;

	// 位置の初期化
	if (mgc[idx]->kind == 0) {
		mgc[idx]->pos.y = GetPrm->MagicFontInitY1;
	}
	else if (mgc[idx]->kind == 1) {
		mgc[idx]->pos.y = GetPrm->MagicFontInitY2;
	}
}


/**
*	@brief	魔法テクスチャの移動
*	@author	Syota Tachikawa
*	@since	2015/01/24
*/
void CharaSelect::MagicalMove()
{
	for (auto& m : mgc)
	{
		if (m->kind == 0)
		{
			m->pos.y += m->v;

			// 初期化
			if (m->pos.y > GetPrm->MagicFontY1Limit)
			{
				m->flag = false;
				m->pos.y = GetPrm->MagicFontInitY1;
				m->v = 0.0f;
				m->kind = -1;
			}
		}

		else if (m->kind == 1)
		{
			m->pos.y -= m->v;
		
			if (m->pos.y < GetPrm->MagicFontY2Limit)
			{
				m->flag = false;
				m->pos.y = GetPrm->MagicFontInitY2;
				m->v = 0.0f;
				m->kind = -1;
			}
		}
	}
}

/**
* @brief 終了
*/
void CharaSelect::Finalize()
{
	// ＢＧＭを停止してからゲームメインに突入する
	SoundPlayer::GetInstance()->Stop(CHARACTERSELECT_BGM);
	// コンテナの要素を削除する
	mgc.clear();
	back.clear();
	icn.clear();
	cur.clear();
	slc.clear();
}