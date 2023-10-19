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
* @file boss.h
* @brind ボスの動きなど
*/
class Player;

class Boss {
public:
	Boss();
	~Boss();
	//初期化
	void Initialize(DirectXCommon* dxCommon, Input* input);
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

	//弾のワールド座標を取得
	Vector3 GetBulletWorldPosition();
	//当たり判定
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
	//playerのHP管理
	int GetPlayerHP() { return playerHp; }
	//enemyのHP管理
	int GetBossHP() { return BossCount; }

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

	//弾
	Object3d* BossBulletObj_ = nullptr;
	Model* BossBulletModel_ = nullptr;

	//壁
	Object3d* BossWallObj_ = nullptr;
	Model* BossWallModel_ = nullptr;
	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	float bulletTimer = 0;
	//動くスピード
	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;
	const float attackMoveSpeed_ = 0.30f;
	float timer = 0;
	//敵のHP
	int hp = 1;
	//攻撃の種類
	int bulletMode = 1;
	float changeTimer = 0;
	//生存しているか
	int liveFlag = 1;
	float enemyTimer = 0.0f;
	int returnFlag = 0;
	//攻撃をしているか
	int attackFlag = 0;
	//敵の登場
	float entryTimer = 300.0f;
	int entry = 1;

	//HP
	//playerHP
	int playerHp = 15;//hp0が3
	//BossCount
	int BossCount = 0;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};