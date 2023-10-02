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

class Player;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Reset();
	
	void Update();

	void Draw();
	void FbxDraw();
	////ワールド座標を取得
	Vector3 GetWorldPosition();

	Vector3 GetEne2WorldPosition();

	Vector3 GetEne3WorldPosition();

	//弾のワールド座標を取得
	Vector3 GetBulletWorldPosition();

	void OnColision();
	void OnColisionPlayer();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { fbxObject3d_->wtf.position = pos; };
	void SetPlayer(Player* player) { player_ = player; };
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	int GetPlayerHP() { return playerHp; }

	int GetEnemyHP() { return enemyCount; }

	//HP
	//playerHP
	int playerHp = 15;//hp0が4
	//enemyCount
	int enemyCount = 0;

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
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

	//弾
	Object3d* enemyBulletObj_ = nullptr;
	Model* enemyBulletModel_ = nullptr;
	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	float bulletTimer = 0;

	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;

	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	int liveFlag = 1;
	
	//ワールド座標を入れる変数
	Vector3 worldPos;

};