/**
* @file   SwordTrajectoryEffect.h
* @brief  剣の軌跡エフェクトを管理する
* @author Syota Tachikawa
*/

#ifndef ___SWORDTRAJECTORYEFFECT_H
#define ___SWORDTRAJECTORYEFFECT_H

#include "..\IObject.h"

/**
* @brief 剣の軌跡エフェクトクラス
*/
class SwordTrajectoryEffect : public IEffect
{
public:
	/**
	* @brief コンストラクタ
	*/
	SwordTrajectoryEffect(const int texid, const Vector2& pos, const Dir& dir, const float rot = 0.0f);

	/**
	* @brief デストラクタ
	*/
	~SwordTrajectoryEffect(){};

	/**
	* @brief 更新
	*/
	bool Update();

	/**
	* @brief 描画
	*/
	void Render();

private:
	/// グラフィックスマネージャ
	GraphicsManager* m_2dTex;

	/// テクスチャデータ
	TextureData* m_texData;
	
	/// 2Dオブジェクト用
	Object2DPacket m_obj;

	///番号
	int m_id;

	/// テクスチャデータ
	int hTex[SLASH_MAX];
};

#endif