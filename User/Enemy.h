//#pragma once
//#include "DirectXCommon.h"
//#include "Audio.h"
//
//class Player;
//#include "Collision.h"
//#include "ParticleManager.h"
//
//#include "FBXModel.h"
//#include "FbxLoader.h"
//#include "FBXObject3d.h"
// 
//class Enemy {
//public:
//	Enemy();
//
//	~Enemy();
//
//	void Initialize(DirectXCommon* dxCommon, Vector3 pos);
//	void Update();
//	void Draw();
//	void FbxDraw();
//
//	void SetPlayer(Player* player) { player_ = player; };
//
//	void CreatDaggerBullet(int bulletNum);
//
//	void CreatCrystalBullet();
//
//	bool IsDead() const { if (isLive) { return false; } else { return true; } };
//
//	void OnColision(int damage);
//
//
//	void AttackDistance();
//
//	void ResetHit2player() { isHitPlayer = false; };
//
//	void AttackInterval();
//
//
//	////ワールド座標を取得
//	Vector3 GetWorldPosition();
//
//	//音を止める関数
//	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };
//
//private:
//	DirectXCommon* dxCommon = nullptr;
//	Player* player_ = nullptr;
//	Collision coll;
//
//	Audio* audio = nullptr;
//
//	bool isLive = true;
//	const int hpMax = 500;
//	int hp = hpMax;
//
//	EnemyBullet* enemyBullet = nullptr;
//
//public:
//	bool isActionStop;
//};