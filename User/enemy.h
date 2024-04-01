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


/*
* @file enemy.h
* @brind 敵の動きなど
*/
class Player;

class Enemy {
public:
	Enemy();
	~Enemy();
	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//リセット
	void Reset();
	//ゲームオーバー
	void Over();
	//更新
	void Update();
	//描画
	void Draw();
	//FBXの描画
	void FbxDraw();

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	Vector3 GetEne2WorldPosition();

	Vector3 GetEne3WorldPosition();

	Vector3 GetEne4WorldPosition();

	//当たり判定
	void OnColision1();
	void OnColision2();
	void OnColision3();
	void OnColision4();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { fbxObject3d_->wtf.position = pos; };
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
	//敵1
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	//敵2
	FBXModel* fbxredModel_ = nullptr;
	FBXObject3d* enemyObject3d_ = nullptr;
	//敵3
	FBXModel* fbxwhiteModel_ = nullptr;
	FBXObject3d* enemy1Object3d_ = nullptr;
	//敵4
	FBXObject3d* enemy2Object3d_ = nullptr;

	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//敵のスピード
	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;
	//敵関連
	float timer1 = 0;
	float timer2 = 0;
	float timer3 = 0;
	float timer4 = 0;

	bool liveFlag1 = true;
	bool liveFlag2 = true;
	bool liveFlag3 = true;
	bool liveFlag4 = true;

	//パーティクルクラスの初期化 
	//ダメージ
	std::unique_ptr<ParticleManager> particleManager;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};