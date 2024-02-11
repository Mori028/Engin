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
* @file Clear.h
* @brind クリアの演出など
*/
class Clear {
public:
	Clear();
	~Clear();

	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	void Reset();
	void FadeOut();
	void Update();
	void Draw();
	void FbxDraw();

	/// <summary>
	/// ポジション
	/// </summary>
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

	//player
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	
	const float moveSpeed_ = 0.013f;
	const float movexSpeed_ = 0.005f;
	const float rotaSpeed_ = 0.1f;

	//背景や床
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
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