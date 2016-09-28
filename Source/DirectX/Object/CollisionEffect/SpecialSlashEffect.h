/**
* @file   SpecialSlashEffect.h
* @brief  必殺技用斬撃エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___SPECIALSLASHEFFECT_H
#define ___SPECIALSLASHEFFECT_H

#include "..\IObject.h"

class SpecialSlashEffect : public ICollisionEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	SpecialSlashEffect(const unsigned int id, const Vector2& pos, const Dir& dir, const Vector2& vel, const float rot = 0.0f);

	/**
	* @brief デストラクタ
	*/
	~SpecialSlashEffect(){};

	/**
	* @brief 更新
	*/
	bool Update();

	/**
	* @brief 描画
	*/
	void Render();

	/**
	* @brief プレイヤーとの当たり判定
	*/
	void CollisionCheckPlayer(IPlPtr obj);

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;
	
	/// 2Dオブジェクト用
	Object2DPacket m_obj;
	
	/// 速度
	Vector2 m_v;

	/// ヒット範囲
	Rect m_hitRect;
	
	/// 番号
	unsigned int m_id;
	
	/// 生存フレーム
	int m_liveFrame;
	
	/// ヒットフラグ
	bool m_isHit;
};

#endif