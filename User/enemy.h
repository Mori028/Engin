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
	void Update();

	void Draw();
	void FbxDraw();
	////ワールド座標を取得
	Vector3 GetWorldPosition();

	Vector3 GetEne2WorldPosition();

	Vector3 GetEne3WorldPosition();

	void OnColision();

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

	/*bool isAliveFlag = true;*/

	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;

	float timer = 0;

	int hp = 1;

	int aliveFlag = 1;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};