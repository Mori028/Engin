#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"

#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "Collision.h"
#include "ParticleManager.h"
/*
* @file Enemys.h
* @brind 敵の動きなど
*/
class Player;

class Enemys {
public:
	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);	
	//更新
	void Update();
	//描画
	void Draw();

	//FBXの描画
	void FbxDraw();
	bool IsDead() const { return isDead_; }
	//当たり判定
	void OnColision();
	////ワールド座標を取得
	Vector3 GetWorldPosition();

	Vector3 GetPos() { return EnemysObject3d_->wtf.position; };
	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { EnemysObject3d_->wtf.position = pos; };
	void SetPlayer(Player* player) { player_ = player; };
	
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;
	Collision coll;
	
	//敵
	FBXModel* EnemysModel_ = nullptr;
	FBXObject3d* EnemysObject3d_ = nullptr;

	bool MaxX = true;
	bool MinX = false;
	bool MaxY = false;
	bool MinY = false;

	//行動制限
	const float PosXMax = 0.09f;
	const float PosXMin = -0.09f;
	const float PosYMax = 0.04f;
	const float PosYMin = -0.2f;
	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	float bulletTimer = 0;
	//敵のスピード
	const float moveSpeed_ = 0.001f;
	const float rotaSpeed_ = 0.1f;
	//敵関連
	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	bool liveFlag = true;
	//敵の撃破時
	int downTimer = 0;
	int downRotate = 0;
	bool dounDraw = false;
	//クリア時
	int ClearMove = 0;

	// デスフラグ
	bool isDead_ = false;

	// デスタイマー
	int32_t dethTimer_ = lifeTime_;

	static const int32_t lifeTime_ = 50 * 5;

	static const int32_t Hp_ = 1;
	int32_t dethHp_ = Hp_;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};