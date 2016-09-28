/**
* @file   Runa.h
* @brief  キャラクター"ルナ"の挙動を管理する
* @author Syota Tachikawa
*/

#ifndef ___RUNA_H
#define ___RUNA_H

#include "..\IPlayer.h"

/**
* @brief キャラクター・ルナ
*/
class Runa : public IPlayer
{
public:
	/**
	* @brief コンストラクタ
	* @param プレイヤー番号
	*/
	Runa(int index);
	/**
	* @brief デストラクタ
	*/
	~Runa();

#pragma region IPlayer
	/**
	* @brief 初期化
	*/
	void Initialize(int index);

	/**
	* @brief 更新
	*/
	void Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief しゃがみ
	*/
	void Squat();

	/**
	* @brief 前進
	*/
	void Advance();

	/**
	* @brief ガード
	*/
	void Guard();

	/**
	* @brief ジャンプ
	*/
	void Jump();

	/**
	* @brief ジャンプ出来るかの判定
	*/
	bool IsJump();

	/**
	* @brief 受身を取れるかの判定
	*/
	bool CanPassive();

	/**
	* @brief 追撃(派生技)が可能か
	*/
	bool CanDerivation();

	/**
	* @brief ダウン中
	*/
	bool isDown();

	/**
	* @brief 制御
	*/
	bool isControll();

	/**
	* @brief 炎上
	*/
	void SetBurning();

	/**
	* @brief 上段攻撃が当たったか
	*/
	bool isUpperAttackHit(const IPlayer& enemy);

	/**
	* @brief 下段攻撃が当たったか
	*/
	bool isLowerAttackHit(const IPlayer& enemy);

	/**
	* @brief 被弾
	* @param attacker - 攻撃者
	* @param hitType - 上段 or 下段
	*/
	void Damage(const IPlayer& attacker, AttackPoint hitType);

	/**
	* @brief パラメータリセット
	*/
	void ActionReset();

	/**
	* @brief 位置を設定
	*/
	void SetPos(const Vector2& pos);

	/**
	* @brief 状態を設定
	*/
	void SetState(const State state);

	/**
	* @brief 向きを設定
	*/
	void SetDirection(const Dir& dir);

	/**
	* @brief 速度を設定する
	*/
	void SetSpeed(const float spx = 0.0f, const float spy = 0.0f);

	/**
	* @brief プレイヤー番号を取得
	*/
	const unsigned int GetID() const;

	/**
	* @brief 攻撃力を取得
	*/
	const float GetPower() const;

	/**
	* @brief 位置を取得
	*/
	const Vector2& GetPos() const;

	/**
	* @brief 状態を取得
	*/
	const State GetState() const;

	/**
	* @brief 攻撃範囲を取得
	*/
	const Rect GetAttackRect() const;

	/**
	* @brief ヒット範囲を取得
	*/
	const Rect GetHitRect() const;

	/**
	* @brief 向きを取得
	*/
	const Dir GetDirection() const;

	/**
	* @brief 攻撃判定発生中か否か
	*/
	bool isAttackJudge();

#pragma endregion

	/**
	* @brief 待機
	*/
	void Neutral();

	/**
	* @brief ダッシュ
	*/
	void Dash();

	/**
	* @brief 後退
	*/
	void BackStep();

	/**
	* @brief しゃがみ攻撃
	*/
	void SquatAttack();

	/**
	* @brief ダッシュ攻撃
	*/
	void DashAttack();

	/**
	* @brief ジャンプ攻撃
	*/
	void JumpAttack();

	/**
	* @brief ダウン
	*/
	void Down();

	/**
	* @brief ガード中
	*/
	void GuardNow();

	/**
	* @brief しゃがみガード中
	*/
	void SquatGuardNow();

	/**
	* @brief 仰け反り
	*/
	void Knockback();

	/**
	* @brief 弱攻撃
	*/
	void WeakAttack();

	/**
	* @brief 弱攻撃派生技
	*/
	void WeakAttackDerivation();

	/**
	* @brief 中攻撃
	*/
	void MediumAttack();

	/**
	* @brief 強攻撃
	*/
	void StrongAttack();

	/**
	* @brief 強攻撃派生技
	*/
	void StrongAttackDerivation();

	/**
	* @brief 遠距離攻撃
	*/
	void LongAttack();

	/**
	* @brief 必殺技
	*/
	void SpecialAttack();

	/**
	* @brief 必殺技追撃
	*/
	void SpecialPursuitAttack();

	/**
	* @brief 奇襲攻撃
	*/
	void RaidAttack();

	/**
	* @brief 吹き飛び
	*/
	void BlowOff();

	/**
	* @brief 相殺
	*/
	void Offset();

	/**
	* @brief 受身
	*/
	void Passive();

	/**
	* @brief バトル前
	*/
	void BeforeBattle();

	/**
	* @brief ノックアウト
	*/
	void KO();

	/**
	* @brief 勝利
	*/
	void Win();

	/**
	* @brief 特殊演出
	*/
	void SpecialProduction();

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;

	/// 向き、拡大、回転、位置
	Object2DPacket m_obj;

	/// 速度
	Vector2 m_spd;

	/// １フレーム前の速度
	Vector2 m_oldSpd;

	/// 状態
	State m_state;

	/// 1フレーム前の状態
	State m_oldState;

	/// 攻撃判定の範囲
	Rect m_attackRect;

	/// 喰らい判定の範囲
	Rect m_hitRect;

	/// 攻撃タイプ
	AttackPoint m_attackPoint;

	/// キャラクタの番号
	int m_id;

	/// ジャンプ回数
	int m_jumpCount;

	/// 必殺技斬撃カウント
	int m_slashingCount;

	/// 受身フラグ
	bool m_isPassive;

	/// 制御フラグ
	bool m_isControll;

	/// 無敵フラグ
	bool m_isInvincible;

	/// 接地フラグ
	bool m_isFloor;

	/// 攻撃判定発生中フラグ
	bool m_isAttackJudge;

	/// 攻撃成功フラグ
	bool m_isAttackSuccess;

	/// 追撃可能フラグ
	bool m_isDerivation;

	/// 燃えているかどうかのフラグ
	bool m_isBurning;

	/// 待機テクスチャ
	int m_hNeutral[3];

	/// 攻撃テクスチャ
	int m_hAttack[6];

	/// ジャンプ攻撃テクスチャ
	int m_hJumpAttack[3];

	/// しゃがみ攻撃テクスチャ
	int m_hSquatAttack[3];

	/// ダウンテクスチャ
	int m_hDown;

	/// ヒットテクスチャ
	int m_hHit;

	/// ジャンプテクスチャ
	int m_hJump;

	/// しゃがみテクスチャ
	int m_hSquat;

	/// 歩きテクスチャ
	int m_hWalk;

	/// 勝利テクスチャ
	int m_hWin[2];

	/// アニメーション
	int m_animation;

	/// サブワーク
	int m_subWork;

	///各々のワーク内でのカウンタに利用する
	int m_subFrame;

	/// 仰け反りフレーム
	int m_knockbackFrame;

	/// 被弾フレーム
	int m_damageFrame;

	/// ダウン状態専用フレーム
	int m_downFrame;

	/// 攻撃力
	float m_power;

	/**
	* @brief 操作可能か否か
	*/
	bool CanControll();

	/**
	* @brief 角度を加算する
	*/
	void AddAngle(float speed);

	/**
	* @brief 必殺技のエフェクト生成処理
	*/
	void SpecialAttackCreateEffect();
};

#endif