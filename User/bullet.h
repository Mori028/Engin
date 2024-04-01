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
	//ボスの攻撃
	void ModeChange();
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
	Vector3 GetBullet4WorldPosition();
	Vector3 GetBullet5WorldPosition();
	Vector3 GetBullet6WorldPosition();
	Vector3 GetBullet7WorldPosition();
	Vector3 GetBullet8WorldPosition();
	Vector3 GetBullet9WorldPosition();
	Vector3 GetBullet10WorldPosition();
	Vector3 GetBullet11WorldPosition();
	Vector3 GetBullet12WorldPosition();
	Vector3 GetBullet13WorldPosition();
	Vector3 GetBullet14WorldPosition();

	void OnColisionPlayer();

public:

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { enemyBullet3Obj_->wtf.position = pos; };
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
	//弾4
	Object3d* enemyBullet3Obj_ = nullptr;
	Model* enemyBullet3Model_ = nullptr;
	//弾5
	Object3d* enemyBullet4Obj_ = nullptr;
	Model* enemyBullet4Model_ = nullptr;
	//弾6
	Object3d* enemyBullet5Obj_ = nullptr;
	Model* enemyBullet5Model_ = nullptr;
	//弾7
	Object3d* enemyBullet6Obj_ = nullptr;
	Model* enemyBullet6Model_ = nullptr;
	//弾8
	Object3d* enemyBullet7Obj_ = nullptr;
	Model* enemyBullet7Model_ = nullptr;
	//弾9
	Object3d* enemyBullet8Obj_ = nullptr;
	Model* enemyBullet8Model_ = nullptr;
	//弾10
	Object3d* enemyBullet9Obj_ = nullptr;
	Model* enemyBullet9Model_ = nullptr;
	//弾11
	Object3d* enemyBullet10Obj_ = nullptr;
	Model* enemyBullet10Model_ = nullptr;
	//弾12
	Object3d* enemyBullet11Obj_ = nullptr;
	Model* enemyBullet11Model_ = nullptr;
	//弾13
	Object3d* enemyBullet12Obj_ = nullptr;
	Model* enemyBullet12Model_ = nullptr;
	//弾14
	Object3d* enemyBullet13Obj_ = nullptr;
	Model* enemyBullet13Model_ = nullptr;
	//弾15
	Object3d* enemyBullet14Obj_ = nullptr;
	Model* enemyBullet14Model_ = nullptr;

	//飛ばすまでの時間とフラグ
	int crystalTimer;
	bool isLive = false;
	int shotTimer;

	//距離
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	float bulletTimer = 0;
	//敵のスピード
	const float moveSpeed_ = 0.01f;
	const float bossMoveSpeed_ = 0.06f;
	const float rotaSpeed_ = 0.1f;
	float shortSpeed = 0.05f;
	float shortXSpeed = 0.005f;
	//敵関連
	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	bool liveFlag = true;
	bool mode = false;
	int bossTimer = 0;
	bool bossAttack = true;
	bool verticalAttack = true;
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