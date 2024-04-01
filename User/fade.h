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
#include "Collision.h"

/*
* @file boss.h
* @brind 敵の登場など
*/

class Fade {

public:
	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//リセット
	void Reset();
	//ゲームオーバー
	void Over();
	//更新
	void Update();
	//FBXの描画
	void FbxDraw();

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	//敵1
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//動くスピード
	const float moveSpeed_ = 0.01f;
	const float fadeSpeed_ = 0.45f;
	const float rotaSpeed_ = 0.1f;
	const float attackMoveSpeed_ = 0.30f;
	float timer = 0;
	bool move = true;

	//敵の登場
	float entryTimer = 300.0f;
	int entry = 1;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};