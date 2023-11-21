#pragma once
#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"
#include <player.h>

/*
* @file playerBullet.h
* @brind プレイヤーの攻撃
*/
class Player;

class Bullet {
public:
	Bullet();
	~Bullet();
public:
	//初期化
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//更新
	void Update();
	//弾の挙動
	void Move();
	//描画
	void Draw();

	//積
	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	//弾のワールド座標を取得
	Vector3 GetBulletWorldPosition();
	void SetPlayer(Player* player) { player_ = player; };
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	//プレイヤー
	Player* player_ = nullptr;
	//スタート演出
	int stoptimer = 0;
	bool moovFlag = false;
	//弾
	Object3d* bulletObj_ = nullptr;
	Model* bulletModel_ = nullptr;
	Vector3 enemyDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;
	
	//カメラ
	float camMoveSpeed = 0.2f;
	Vector2 camRotaSpeed = { PI / 1800, PI / 1800 };

	//ワールド座標を入れる変数
	Vector3 worldPos;

};