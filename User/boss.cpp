#include"Boss.h"
#include "player.h"

/*
* @file boss.cpp
* @brind ボスの動きなど
*/
Boss::Boss() {

}

Boss::~Boss() {

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
}

void Boss::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");


	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,1.0f,3.0f };
	fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f, true);


	//弾
	BossBulletModel_ = Model::LoadFromOBJ("boll");
	BossBulletObj_ = Object3d::Create();
	BossBulletObj_->SetModel(BossBulletModel_);
	BossBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
	BossBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };

	//壁
	BossWallModel_ = Model::LoadFromOBJ("box");
	BossWallObj_ = Object3d::Create();
	BossWallObj_->SetModel(BossWallModel_);
	BossWallObj_->wtf.position = { 0.0f,-0.3f,+2.3f };
	BossWallObj_->wtf.rotation = { 0.0f,-1.6f,0.0f };
	BossWallObj_->wtf.scale = { 0.02f,0.02f,0.02f };
}

void Boss::Reset()
{
	//ボス
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.position = { 0.0f,1.0f,+3.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->wtf.scale = { 1.2f,1.2f,1.2f };
	//ボスの弾
	BossBulletObj_->Initialize();
	BossBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
	BossBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//ボスの攻撃１
	BossWallObj_->Initialize();
	BossWallObj_->wtf.position = { 0.0f,-0.3f,+2.3f };
	BossWallObj_->wtf.rotation = { 0.0f,-1.6f,0.0f };
	BossWallObj_->wtf.scale = { 0.02f,0.02f,0.02f };
	liveFlag = true;
	entry = 1;
	enemyTimer = 0;
	BossCount = 0;
}

void Boss::Over()
{
}

void Boss::Update() {
	if (liveFlag == true) {

		enemyTimer++;
		if (entry == 1) {
			if (fbxObject3d_->wtf.position.y >= -0.3) {
				fbxObject3d_->wtf.position.y -= moveSpeed_;
			}
			else {
				fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
				entry = 0;
			}
		}
		//////敵の攻撃１//////
		/*if (returnFlag == false) {
			if (enemyTimer >= 290) {

				fbxObject3d_->wtf.position.z += attackMoveSpeed_;

				if (fbxObject3d_->wtf.position.z >= 12.0) {
					fbxObject3d_->wtf.position = { 0.0f,2.0f,+3.0f };
					returnFlag = true;
				}
			}
		}
		if (returnFlag == true) {
			BossWallObj_->wtf.position.z -= moveSpeed_;
			entryTimer--;
			if (entryTimer <= 0) {
				entry = 1;
				enemyTimer = 0;
				BossWallObj_->wtf.position = { 0.0f,-0.3f,+2.3f };
				returnFlag = false;
				entryTimer = 300.0f;
			}

		}*/
		//////敵の攻撃１//////

		if (BossCount >= 50) {
			liveFlag = false;
		}
		
		if (entry == 0) {

			//当たり判定(自機弾とボス)
			if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetWorldPosition(), 0.1f, 0.3f)) {
				OnColision();
			};

			//当たり判定(自機と敵弾)
			if (coll.CircleCollision(player_->GetWorldPosition(), GetBulletWorldPosition(), 0.1f, 0.1f)) {
				OnColisionPlayer();
			};
		}
	}
	fbxObject3d_->Update();
	BossBulletObj_->Update();
	BossWallObj_->Update();
}

void Boss::Draw() {
	if (liveFlag == true) {
		if (isShootFlag == true) {

			BossBulletObj_->Draw();
		}
		if (returnFlag == true) {
			BossWallObj_->Draw();
		}
	}
}

void Boss::FbxDraw() {
	if(liveFlag = true){
		fbxObject3d_->Draw(dxCommon->GetCommandList());
	}
	//敵の接近
	/*fbxObject3d_->wtf.position.z -= moveSpeed_;*/

}

Vector3 Boss::GetWorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Boss::GetBulletWorldPosition()
{
	BossBulletObj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = BossBulletObj_->wtf.matWorld.m[3][0];
	worldPos.y = BossBulletObj_->wtf.matWorld.m[3][1];
	worldPos.z = BossBulletObj_->wtf.matWorld.m[3][2];

	return worldPos;
}

void Boss::OnColision()
{
	BossCount = BossCount + 1;
}

void Boss::OnColisionPlayer()
{
	playerHp = playerHp - 1;
}

