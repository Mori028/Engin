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

	//弾
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	enemyBulletObj_ = Object3d::Create();
	enemyBulletObj_->SetModel(enemyBulletModel_);
	enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y +0.2f , fbxObject3d_->wtf.position.z };
	enemyBulletObj_->wtf.scale = { 2.0f,2.0f,2.0f };
}

void Enemy::Update() {
	if (hp == 1) {

		////////////
		//攻撃種類を作るため仮設置（後で消す）
		changeTimer++;
		if (changeTimer == 120) {
			bulletMode = 2;
		}
		if (changeTimer == 240) {
			bulletMode = 3;
		}
		if (changeTimer == 360) {
			bulletMode = 1;
			changeTimer = 0;
		}
		////////////

		if (bulletMode == 1) {
			//雑魚敵の攻撃
			float shortSpeed = 0.05f;
			bulletTimer++;
			if (bulletTimer >= 60) {
				isShootFlag = true;
			}
			if (isShootFlag == true) {
				bulletCoolTime++;
				enemyBulletObj_->wtf.position.z -= shortSpeed;

			}
			else {
				enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}

		if (bulletMode == 2) {
			//雑魚敵の攻撃
			float shortSpeed = 0.05f;

			float shortXSpeed = 0.005f;
			bulletTimer++;
			if (bulletTimer >= 60) {
				isShootFlag = true;
			}
			if (isShootFlag == true) {
				bulletCoolTime++;
				enemyBulletObj_->wtf.position.z -= shortSpeed;
				enemyBulletObj_->wtf.position.x -= shortXSpeed;
			}
			else {
				enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}

		if (bulletMode == 3) {
			//雑魚敵の攻撃
			float shortSpeed = 0.05f;

			float shortXSpeed = 0.005f;
			bulletTimer++;
			if (bulletTimer >= 60) {
				isShootFlag = true;
			}
			if (isShootFlag == true) {
				bulletCoolTime++;
				enemyBulletObj_->wtf.position.z -= shortSpeed;
				enemyBulletObj_->wtf.position.x += shortXSpeed;
			}
			else {
				enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}

		//当たり判定(自機弾と敵1)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetWorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	if (hp == 2) {
		//当たり判定(自機弾と敵2)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne2WorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	if (hp == 3) {
		//当たり判定(自機弾と敵3)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne3WorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	//当たり判定(自機と敵弾)
	if (coll.CircleCollision(player_->GetWorldPosition(),GetBulletWorldPosition(), 0.1f, 0.1f)) {
		OnColisionPlayer();
	};
		
	fbxObject3d_->Update();
	enemyObject3d_->Update();
	enemy1Object3d_->Update();
	enemyBulletObj_->Update();
}

void Enemy::Draw() {
	if (liveFlag == 1) {
		if (isShootFlag == true) {
			if (hp == 1) {
				enemyBulletObj_->Draw();
			}
		}
	}
	if (liveFlag == 0) {
		enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y +0.2f , fbxObject3d_->wtf.position.z };
	}
}

void Enemy::FbxDraw() {
	if (liveFlag == 1) {
		if (hp == 1) {

			fbxObject3d_->Draw(dxCommon->GetCommandList());
			//敵の接近
			/*fbxObject3d_->wtf.position.z -= moveSpeed_;*/

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
	}
	else if (liveFlag == 0) {
		if (hp == 1) {
			timer++;
			//元の座標に戻す
			fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
			enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
			enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
			if (timer >= 50) {
				timer = 0;
				hp = 2;
				liveFlag = 1;
			}
		}
		if (hp == 2) {
			timer++;
			//元の座標に戻す
			fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
			enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
			enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
			if (timer >= 50) {
				timer = 0;
				hp = 3;
				liveFlag = 1;
			}
		}
		if (hp == 3) {
			timer++;
			//元の座標に戻す
			fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
			enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
			enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
			if (timer >= 50) {
				timer = 0;
				hp = 1;
				liveFlag = 1;
			}
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

Vector3 Enemy::GetBulletWorldPosition()
{
	enemyBulletObj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemyBulletObj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBulletObj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBulletObj_->wtf.matWorld.m[3][2];

	return worldPos;
}

void Enemy::OnColision()
{
	liveFlag = 0;
	enemyCount = enemyCount +1;
}

void Enemy::OnColisionPlayer()
{
	playerHp = playerHp - 1;
}

