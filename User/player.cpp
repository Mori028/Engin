﻿#include"player.h"

Player::Player() {

}

Player::~Player() {

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
}

void Player::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("enemystand");
	
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.3f,0.0f };
	fbxObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	fbxObject3d_->wtf.rotation = { 0.0f,3.3f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f,true);
}

void Player::Update() {
	//キーボード入力による移動処理
	//プレイヤーの移動
	if (input_->PushKey(DIK_D)) {
		
		if (fbxObject3d_->wtf.position.x <= XMax) {
			fbxObject3d_->wtf.position.x += moveSpeed_;
		}
	}
	if (input_->PushKey(DIK_A)) {
		if (fbxObject3d_->wtf.position.x >= XMin) {
			fbxObject3d_->wtf.position.x -= moveSpeed_;
		}
	}
	if (input_->PushKey(DIK_S)) {
		if (fbxObject3d_->wtf.position.y >= YMax) {
			fbxObject3d_->wtf.position.y -= moveSpeed_;
		}
	}
	if (input_->PushKey(DIK_W)) {
		if (fbxObject3d_->wtf.position.y <= YMin) {
			fbxObject3d_->wtf.position.y += moveSpeed_;
		}
	}
	

	fbxObject3d_->Update();
}

void Player::Draw() {
}

void Player::FbxDraw(){
	
	fbxObject3d_->Draw(dxCommon->GetCommandList());
}

Vector3 Player::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}

Vector3 Player::GetWorldPosition(){
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

