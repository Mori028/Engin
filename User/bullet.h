#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"
#include "Collision.h"


/*
* @file bullet.h
* @brind 敵の攻撃
*/
class Player;
class Enemys;

class Bullet {
public:
	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//リセット
	void Reset();
	//ゲームクリア
	void Clear();
	//ゲームオーバー
	void Over();
	//更新
	void Update();
	//描画
	void Draw();
	//パーティクル更新
	void EffUpdate();
	//バーティクル描画
	void EffDraw();

	//弾のワールド座標を取得
	Vector3 GetBulletWorldPosition();
	Vector3 GetBullet1WorldPosition();
	Vector3 GetBullet2WorldPosition();
	Vector3 GetBullet3WorldPosition();

	void OnColisionPlayer();

public:

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPlayer(Player* player) { player_ = player; };
	void SetEnemys(Enemys* enemys) { enemys_ = enemys; };

	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;
	Enemys* enemys_ = nullptr;
	Collision coll;

	//弾
	Object3d* enemyBulletObj_ = nullptr;
	Model* enemyBulletModel_ = nullptr;
	//弾2
	Object3d* enemyBullet1Obj_ = nullptr;
	Model* enemyBullet1Model_ = nullptr;
	//弾3
	Object3d* enemyBullet2Obj_ = nullptr;
	Model* enemyBullet2Model_ = nullptr;
	// 自機狙い弾
	Object3d* enemyBullet3Obj_ = nullptr;
	Model* enemyBullet3Model_ = nullptr;

	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	float bulletTimer = 0;
	//敵のスピード
	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;
	//敵関連
	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	bool liveFlag = true;
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