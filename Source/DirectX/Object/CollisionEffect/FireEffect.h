/**
* @file   FireEffect.h
* @brief  火の玉エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___FIREEFFECT_H
#define ___FIREEFFECT_H

#include "..\IObject.h"

/**
* @brief 火の玉エフェクト
*/
class FireEffect : public ICollisionEffect
{
public:
	/**
	* @brief コンストラクタ
	* @param id - 番号
	* @param pos - 描画位置
	* @param dir - 描画向き
	*/
	FireEffect(const unsigned int id, const Vector2& pos, const Dir& dir);

	/**
	* @brief デストラクタ
	*/
	~FireEffect(){};

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
	
	/// 生死判定
	bool m_isDead;
};

#endif