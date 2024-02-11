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

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { EnemysObj_->wtf.position = pos; };
	void SetPlayer(Player* player) { player_ = player; };
	
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	int GetPlayerHP() { return playerHp; }

	int GetEnemysHP() { return EnemysCount; }

	//playerのHP
	int playerHp = 15;
	//Enemysの数
	int EnemysCount = 0;



private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;
	Collision coll;
	
	//弾
	Object3d* EnemysObj_ = nullptr;
	Model* EnemysModel_ = nullptr;

	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	float bulletTimer = 0;
	//敵のスピード
	const float moveSpeed_ = 0.05f;
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
	//パーティクル関連
	int effTimer = 0;
	int isEffFlag = 0;
	//パーティクルクラスの初期化 
	//ダメージ
	std::unique_ptr<ParticleManager> particleManager;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};