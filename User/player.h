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
#include "SpriteCommon.h"
#include "Sprite.h"

/*
* @file player.h
* @brind プレイヤーの動きなど
*/

class Player {
public:
	Player() = default;
	~Player() = default;
public:
	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//リセット
	void Reset();
	//登場時
	void FadeIn();
	//ゲームオーバー時
	void Over();
	//ゲームクリア時
	void Clear();
	//更新
	virtual void Update();
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
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;

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

	Object3d* Reticle1Obj_ = nullptr;
	Model* Reticle1Model_ = nullptr;

	Object3d* Reticle2Obj_ = nullptr;
	Model* Reticle2Model_ = nullptr;

	Object3d* Reticle3Obj_ = nullptr;
	Model* Reticle3Model_ = nullptr;

	//移動の速度
	const float moveSpeed_ = 0.013f;
	const float rotaSpeed_ = 0.1f;
	const float rotateSpeed_ = 0.02f;
	const float clearMoveSpeed_ = 0.0055f;
	//行動制限
	const float xMax = 0.5f;
	const float xMin = -0.5f;
	const float yMax = -0.3f;
	const float yMin = 0.2f;
	//レティクルの移動速度
	const float retXMax = 3.5f;
	const float retXMin = -3.5f;
	const float retYMax = -1.9f;
	const float retYMin = 1.9f;
	const float retSpeed = 0.1f;
	const float ret1Speed = 0.09f;
	const float ret2Speed = 0.08f;
	//傾きフラグ
	float rollW = 0;
	float rollA = 0;
	float rollS = 0;
	float rollD = 0;
	//スタート演出
	int stoptimer = 0;
	int moovFlag = 0;
	//クリア
	bool ClearMove = false;
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