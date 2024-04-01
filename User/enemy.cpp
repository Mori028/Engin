#include"Enemy.h"
#include "player.h"

/*
* @file enemy.cpp
* @brind 敵の動きなど
*/
Enemy::Enemy() {

}

Enemy::~Enemy() {

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
}

void Enemy::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	//モデル
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");

	fbxredModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma1");

	fbxwhiteModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma2");

	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//青の待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxredModel_);
	fbxObject3d_->wtf.position = { +0.75f,-0.5f,+5.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f, true);
	//赤
	enemyObject3d_ = new FBXObject3d;
	enemyObject3d_->Initialize();
	enemyObject3d_->SetModel(fbxredModel_);
	enemyObject3d_->wtf.position = { -0.75f,-0.5f,+5.0f };
	enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemyObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
	enemyObject3d_->PlayAnimation(1.0f, true);
	//白
	enemy1Object3d_ = new FBXObject3d;
	enemy1Object3d_->Initialize();
	enemy1Object3d_->SetModel(fbxwhiteModel_);
	enemy1Object3d_->wtf.position = { +0.75f,+0.3f,+5.0f };
	enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemy1Object3d_->PlayAnimation(1.0f, true);

	enemy2Object3d_ = new FBXObject3d;
	enemy2Object3d_->Initialize();
	enemy2Object3d_->SetModel(fbxwhiteModel_);
	enemy2Object3d_->wtf.position = { -0.75f,+0.3f,+5.0f };
	enemy2Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemy2Object3d_->PlayAnimation(1.0f, true);

	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();
}

void Enemy::Reset()
{
	enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemy2Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };

	liveFlag1 = true;
	liveFlag2 = true;
	liveFlag3 = true;
	liveFlag4 = true;
}

void Enemy::Over()
{
	liveFlag1 = false;
	liveFlag2 = false;
	liveFlag3 = false;
	liveFlag4 = false;
}

void Enemy::Update() {
	//1
	if (liveFlag1 == false) {
		timer1++;

		if (timer1 >= 150) {
			liveFlag1 = true;
			timer1 = 0;
		}
	}
	//2
	if (liveFlag2 == false) {
		timer2++;

		if (timer2 >= 150) {
			liveFlag2 = true;
			timer2 = 0;
		}
	}
	//3
	if (liveFlag3 == false) {
		timer3++;

		if (timer3 >= 150) {
			liveFlag3 = true;
			timer3 = 0;
		}
	}
	//4
	if (liveFlag4 == false) {
		timer4++;

		if (timer4 >= 150) {
			liveFlag4 = true;
			timer4 = 0;
		}
	}


	fbxObject3d_->Update();
	enemyObject3d_->Update();
	enemy1Object3d_->Update();
	enemy2Object3d_->Update();
	
}

void Enemy::Draw() {
	
}

void Enemy::FbxDraw() {

	//1体目
	if (liveFlag1 == true) {
		fbxObject3d_->Draw(dxCommon->GetCommandList());
	}
	else if (liveFlag1 == false) {
		if (timer1 >= 0 && timer1 <= 30) {
			fbxObject3d_->Draw(dxCommon->GetCommandList());
			fbxObject3d_->wtf.rotation.y++;
		}
		if (timer1 >= 31) {
			fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
		}
	}
	//2体目
	if (liveFlag2 == true) {
		enemyObject3d_->Draw(dxCommon->GetCommandList());
	}
	else if (liveFlag2 == false) {
		if (timer2 >= 0 && timer2 <= 30) {
			enemyObject3d_->Draw(dxCommon->GetCommandList());
			enemyObject3d_->wtf.rotation.y++;
		}
		if (timer2 >= 31) {
			enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
		}
	}
	//3体目
	if (liveFlag3 == true) {
		enemy1Object3d_->Draw(dxCommon->GetCommandList());
	}
	else if (liveFlag3 == false) {
		if (timer3 >= 0 && timer3 <= 30) {
			enemy1Object3d_->Draw(dxCommon->GetCommandList());
			enemy1Object3d_->wtf.rotation.y++;
		}
		if (timer3 >= 31) {
			enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
		}
	}
	//4体目
	if (liveFlag4 == true) {
		enemy2Object3d_->Draw(dxCommon->GetCommandList());
	}
	else if (liveFlag4 == false) {
		if (timer4 >= 0 && timer4 <= 30) {
			enemy2Object3d_->Draw(dxCommon->GetCommandList());
			enemy2Object3d_->wtf.rotation.y++;
		}
		if (timer4 >= 31) {
			enemy2Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
		}
	}
}


Vector3 Enemy::GetWorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne2WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemyObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemyObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemyObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne3WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemy1Object3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemy1Object3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemy1Object3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne4WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemy2Object3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemy2Object3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemy2Object3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

void Enemy::OnColision1()
{
	liveFlag1 = false;
}
void Enemy::OnColision2()
{
	liveFlag2 = false;
}

void Enemy::OnColision3()
{
	liveFlag3 = false;
}

void Enemy::OnColision4()
{
	liveFlag4 = false;
}

