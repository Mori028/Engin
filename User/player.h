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
#include "Sprite.h"
#include "SpriteCommon.h"

/*
* @file player.h
* @brind プレイヤーの動きなど
*/
class Player {
public:
	Player();
	~Player();
	//初期化
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//リセット
	void Reset();
	//登場時
	void FadeIn();
	//ゲームオーバー時
	void Over();
	//更新
	void Update();
	//描画
	void Draw();
	//FBXの描画
	void FbxDraw();

	//積
	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////プレイヤーのワールド座標を取得
	Vector3 GetWorldPosition();

	//弾のワールド座標を取得
	Vector3 GetBulletWorldPosition();

	//ワールド座標を取得(レティクル)
	Vector3 GetReticleWorldPosition();

	Vector3 GetPos() { return fbxObject3d_->wtf.position; };
	/// <summary>
	/// カメラポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { fbxObject3d_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };
	SpriteCommon* spriteCommon = nullptr;

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;

	//レティクル
	Sprite* RetSprite = new Sprite();
	//player回転
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	//player通常時
	FBXModel* fbxRoteModel_ = nullptr;
	FBXObject3d* fbxRoteObject3d_ = nullptr;
	
	//弾
	Object3d* bulletObj_ = nullptr;
	Model* bulletModel_ = nullptr;
	Vector3 enemyDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//弾のフラグ
	bool isShootFlag = false;

	//レティクル
	Object3d* ReticleObj_ = nullptr;
	Model* ReticleModel_ = nullptr;

	const float moveSpeed_ = 0.013f;
	const float rotaSpeed_ = 0.1f;
	//行動制限
	const float XMax = 0.5f;
	const float XMin = -0.5f;
	const float YMax = -0.3f;
	const float YMin = 0.2f;

	const float retXMax = 3.5f;
	const float retXMin = -3.5f;
	const float retYMax = 0.3f;
	const float retYMin = -9.3f;
	//傾きフラグ
	float rollW = 0;
	float rollA = 0;
	float rollS = 0;
	float rollD = 0;

	int stoptimer = 0;
	int moovFlag = 0;
	//カメラ関連
	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	//レティクル
	float targetTheta;
	//レティクルの距離
	float targetDistance = 10;
	//カメラ
	float camMoveSpeed = 0.2f;
	Vector2 camRotaSpeed = { PI / 1800, PI / 1800};

	//ワールド座標を入れる変数
	Vector3 worldPos;
	
};