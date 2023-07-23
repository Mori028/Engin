#include"Enemy.h"
#include "player.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
}

void Enemy::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");

	fbxredModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma1");

	fbxwhiteModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma2");

	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
	/*fbxObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };*/
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f, true);

	enemyObject3d_ = new FBXObject3d;
	enemyObject3d_->Initialize();
	enemyObject3d_->SetModel(fbxredModel_);
	enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
	/*enemyObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };*/
	enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemyObject3d_->PlayAnimation(1.0f, true);

	enemy1Object3d_ = new FBXObject3d;
	enemy1Object3d_->Initialize();
	enemy1Object3d_->SetModel(fbxwhiteModel_);
	enemy1Object3d_->wtf.position = { +0.5f,-0.3f,+3.0f };
	/*enemy1Object3d_->wtf.scale = { 0.03f,0.03f,0.03f };*/
	enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemy1Object3d_->PlayAnimation(1.0f, true);
}

void Enemy::Update() {

	//当たり判定(自機弾と雑魚敵)
	if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetWorldPosition(), 0.1f, 0.3f)) {
		OnColision();
	};

		
	fbxObject3d_->Update();
	enemyObject3d_->Update();
	enemy1Object3d_->Update();
}

void Enemy::Draw() {
}

void Enemy::FbxDraw() {
	
	if (hp == 1) {

		fbxObject3d_->Draw(dxCommon->GetCommandList());

		fbxObject3d_->wtf.position.z -= moveSpeed_;

		if (fbxObject3d_->wtf.position.z <= 0.5) {
			hp = 2;
			fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
		}
	}
	else if (hp == 2) {

		enemyObject3d_->Draw(dxCommon->GetCommandList());

		enemyObject3d_->wtf.position.z -= moveSpeed_;

		if (enemyObject3d_->wtf.position.z <= 0.5) {
			hp = 3;
			enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
		}
	}
	else if (hp == 3) {

		enemy1Object3d_->Draw(dxCommon->GetCommandList());

		enemy1Object3d_->wtf.position.z -= moveSpeed_;

		if (enemy1Object3d_->wtf.position.z <= 0.5) {
			hp = 1;
			enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
		}
	}
	else if (hp == 0) {
		timer++;
		//元の座標に戻す
		fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
		enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
		enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
		if (timer >= 50) {
			timer = 0;
			hp = 1;
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

void Enemy::OnColision()
{
	hp = 0;
}

