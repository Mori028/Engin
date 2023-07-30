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


class Player {
public:
	Player();
	~Player();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();
	void FbxDraw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////プレイヤーのワールド座標を取得
	Vector3 GetWorldPosition();

	//弾のワールド座標を取得
	Vector3 GetBulletWorldPosition();

	//ワールド座標を取得(レティクル)
	Vector3 GetReticleWorldPosition();

	Vector3 GetPos() { return fbxObject3d_->wtf.position; };
	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) {fbxObject3d_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	//待機
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	//弾
	Object3d* bulletObj_ = nullptr;
	Model* bulletModel_ = nullptr;
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

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;
  
	Vector2 camRotaSpeed = { PI / 1800, PI / 1800};

	//ワールド座標を入れる変数
	Vector3 worldPos;
	
};