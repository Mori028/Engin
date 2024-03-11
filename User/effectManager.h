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

/*
* @file effectManager.h
* @brind エフェクトなど
*/
class Player;

class EffectManager {
public:
	EffectManager();
public:
	//初期化
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	void Update();
	//パーティクル更新
	void EffUpdate();
	//バーティクル描画
	void EffDraw();

	void SetPlayer(Player* player) { player_ = player; };
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;

	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//パーティクル関連
	int effTimer = 0;
	int isEffFlag = 0;
	//パーティクルクラスの初期化 
	//ダメージ
	std::unique_ptr<ParticleManager> particleManager;

	//ワールド座標を入れる変数
	Vector3 worldPos;

};