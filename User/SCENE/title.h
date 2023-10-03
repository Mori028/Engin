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


class Title {
public:
	Title();
	~Title();

	void Initialize(DirectXCommon* dxCommon, Input* input);
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
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;

	//player
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	Object3d* playerObj_ = nullptr;
	Model* playerModel_ = nullptr;
	
	const float moveSpeed_ = 0.013f;
	const float movexSpeed_ = 0.005f;
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