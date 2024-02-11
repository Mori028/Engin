/*
 * @file stageState.h
 * @brind ステージパターン
 */

#pragma once
#include"Transform.h"
#include"stage.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

class Stage;

class StageState {
public:

	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//ゲームオーバー時に動きを止める
	void Over();

	//リセット
	void Reset();
	//ステージのループ
	void Loop();

	/// <summary>
	/// ポジション
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { stage_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	//ステージのモデル
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
	//ステージの進むスピード
	const float moveSpeed_ = 0.53f;
	const float rotaSpeed_ = 0.1f;
	int moveFlag = 1;
	//カメラ関連
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