#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"
#include "Wolf.h"

#include "Gorilla.h"
#include "ParticleManager.h"
#include "Audio.h"

#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"


class Player {
public:
	Player();
	~Player();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Reset();
	void SetSensitivity(float newSensitivity) { sensitivity = newSensitivity; };

	void Update();
	void Rota();
	void Move();
	void camUpdate();

	void Attack();

	void Draw();
	void FbxDraw();
	void EffUpdate();
	void EffHealUpdate();
	void EffHiHealUpdate();
	void EffDraw();

	void OnCollision();

	

	void LightAttack();
	void HeavyAttack();
	void Dodge();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	
	Vector3 GetCamShake() { return camShakeVec; };
	Vector3 GetMoveBack();
	bool GetIsAttackFin() { return isAttackFin; };

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) {fbxObject3d_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

	int EffTimer = 0;
	int isEffFlag = 0;
	
	int EffHealTimer = 0;
	int isEffHealFlag = 0;
	
	int EffHiHealTimer = 0;
	int isEffHiHealFlag = 0;

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Collision col;
	Audio* audio = nullptr;
	//待機
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	const float moveSpeed_ = 0.1f;
	const float rotaSpeed_ = 0.1f;

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;
  
	Vector2 camRotaSpeed = { PI / 1800, PI / 1800};

	float sensitivity;
	float dashSpeed = 0.4f;
	bool isDash;
	const float dashMP = 2.0f / 60.0f;

	//ステータス
	const int defaultHp = 100;
	int hp;
	bool isLive = true;
	bool isAttackFin;
	bool nextAttack;

	//無敵時間
	bool isInvincible;
	const float invincibleLimit = 15;
	float invincibleTimer = invincibleLimit;

	//画面シェイク
	bool isCamShake;
	const int camShakeLimit = 20;
	int camShakeTimer = camShakeLimit;
	Vector3 camShakeVec;
	Vector3 moveBack;

	//アニメーション速度
	float lightAttackAnime[4] = { 2.5f,1.0f,1.5f,1.5f };
	//一回の攻撃全体の時間
	float lightAttackLimit[4] = { 52 / lightAttackAnime[0],26 / lightAttackAnime[1],44 / lightAttackAnime[2],50 / lightAttackAnime[3]};
	float lightAttackTimer;
	//攻撃の当たり判定の有無
	bool isLightAttack;
	//判定が出始める時間
	float lightAttackPopTime[4] = { 14,13,15,24 };
	//判定が消える時間
	float lightAttackDeathTime[4] = { 13,12,14,22 };
	//次の連撃への入力受付開始時間
	float lightAttackInput[4] = { 20,20,20,0 };

	

	//OBJ関係
	//移動した時のplayerOBJを変える
	int objRotaTimer;
	//攻撃した時のplayerOBJを変える
	int attackFlag = 0;
	int objAttackTimer;

	//敵
	Transform* enemyPos_ = nullptr;

	//パーティクルクラスの初期化 
	//ダメージ
	std::unique_ptr<ParticleManager> particleManager;
	//回復
	std::unique_ptr<ParticleManager> particleHealManager;
	std::unique_ptr<ParticleManager> particleHiHealManager;
	//ワールド座標を入れる変数
	Vector3 worldPos;

	//音関係まとめ
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;

public:
	bool isActionStop;
	int isAction;
	//バディ
	Wolf* wolf_ = nullptr;
};