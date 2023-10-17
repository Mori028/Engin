#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"


class Stage {
public:
	Stage();
	~Stage();

	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Reset();
	void Loop();
	void Update();

	void Draw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	////ワールド座標を取得
	Vector3 GetWorldPosition();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { stage_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;

	Object3d* stage_ = nullptr;
	Object3d* stage2_ = nullptr;
	Object3d* stage3_ = nullptr;
	Object3d* stage4_ = nullptr;
	Object3d* stage5_ = nullptr;
	Object3d* stage6_ = nullptr;
	Object3d* stage7_ = nullptr;
	Object3d* stage8_ = nullptr;
	Object3d* stage9_ = nullptr;
	Object3d* stage10_ = nullptr;
	Model* felld = nullptr;
	const float moveSpeed_ = 0.53f;
	const float rotaSpeed_ = 0.1f;

	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;

	Vector2 camRotaSpeed = { PI / 1800, PI / 1800 };


	//ワールド座標を入れる変数
	Vector3 worldPos;

};