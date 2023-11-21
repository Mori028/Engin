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

void Enemy::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	//モデル
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");
	fbxKnockModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kumaDamage");
	fbxredModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma1");
	fbxKnockRedModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kumaDamage2");
	fbxwhiteModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma2");
	fbxKnocWhitekModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kumaDamage3");
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	//青の待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f, true);
	//赤
	enemyObject3d_ = new FBXObject3d;
	enemyObject3d_->Initialize();
	enemyObject3d_->SetModel(fbxredModel_);
	enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
	enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemyObject3d_->PlayAnimation(1.0f, true);
	//白
	enemy1Object3d_ = new FBXObject3d;
	enemy1Object3d_->Initialize();
	enemy1Object3d_->SetModel(fbxwhiteModel_);
	enemy1Object3d_->wtf.position = { +0.5f,-0.3f,+3.0f };
	enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemy1Object3d_->PlayAnimation(1.0f, true);

	// 青撃破
	Knock0Object3d_ = new FBXObject3d;
	Knock0Object3d_->Initialize();
	Knock0Object3d_->SetModel(fbxKnockModel_);
	Knock0Object3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
	Knock0Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	Knock0Object3d_->PlayAnimation(1.0f, true);

	//赤撃破
	Knock1Object3d_ = new FBXObject3d;
	Knock1Object3d_->Initialize();
	Knock1Object3d_->SetModel(fbxKnockRedModel_);
	Knock1Object3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
	Knock1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	Knock1Object3d_->PlayAnimation(1.0f, true);

	//白撃破
	Knock2Object3d_ = new FBXObject3d;
	Knock2Object3d_->Initialize();
	Knock2Object3d_->SetModel(fbxKnocWhitekModel_);
	Knock2Object3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
	Knock2Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	Knock2Object3d_->PlayAnimation(1.0f, true);

	//弾
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	 enemyBulletObj_ = Object3d::Create();
	enemyBulletObj_->SetModel(enemyBulletModel_);
	enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y +0.2f , fbxObject3d_->wtf.position.z };
	enemyBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };

	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();
}

void Enemy::Reset()
{
	//敵1
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//敵1ダウン
	Knock0Object3d_->Initialize();
	Knock0Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//敵2
	enemyObject3d_->Initialize();
	enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//敵2ダウン
	Knock1Object3d_->Initialize();
	Knock1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//敵3
	enemy1Object3d_->Initialize();
	enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//敵3ダウン
	Knock2Object3d_->Initialize();
	Knock2Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemyBulletObj_->Initialize();
	//パーティクル初期化
	timer = 0;
	effTimer = 0;
	isEffFlag = 0;
	enemyCount = 0;
	ClearMove = 0;
	liveFlag = true;
	dounDraw = false;
}

void Enemy::Clear()
{
	ClearMove = 1;
}

void Enemy::Over()
{
	liveFlag = false;
}

void Enemy::Update() {

	//ダメージエフェクト
	if (isEffFlag == 1) {
		effTimer++;
	}
	if (effTimer <= 10 && effTimer >= 1) {
		EffUpdate();
	}
	if (effTimer >= 11) {
		isEffFlag = 0;
		effTimer = 0;
	}

	if (hp == 1) {
		Knock0Object3d_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y , fbxObject3d_->wtf.position.z };
		////////////
		//攻撃種類を作るため設置
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
		if (liveFlag == true) {
			//当たり判定(自機弾と敵1)
			if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetWorldPosition(), 0.1f, 0.3f)) {
				OnColision();
			};
		}
	}
	if (hp == 2) {
		Knock1Object3d_->wtf.position = { enemyObject3d_->wtf.position.x,enemyObject3d_->wtf.position.y , enemyObject3d_->wtf.position.z };
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
				enemyBulletObj_->wtf.position = { enemyObject3d_->wtf.position.x,enemyObject3d_->wtf.position.y + 0.2f , enemyObject3d_->wtf.position.z };
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
				enemyBulletObj_->wtf.position = { enemyObject3d_->wtf.position.x,enemyObject3d_->wtf.position.y + 0.2f , enemyObject3d_->wtf.position.z };
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
				enemyBulletObj_->wtf.position = { enemyObject3d_->wtf.position.x,enemyObject3d_->wtf.position.y + 0.2f , enemyObject3d_->wtf.position.z };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}
		if (liveFlag == true) {
			//当たり判定(自機弾と敵2)
			if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne2WorldPosition(), 0.1f, 0.3f)) {
				OnColision();
			};
		}
	}
	if (hp == 3) {
		Knock2Object3d_->wtf.position = { enemy1Object3d_->wtf.position.x,enemy1Object3d_->wtf.position.y , enemy1Object3d_->wtf.position.z };
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
				enemyBulletObj_->wtf.position = { enemy1Object3d_->wtf.position.x,enemy1Object3d_->wtf.position.y + 0.2f , enemy1Object3d_->wtf.position.z };
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
				enemyBulletObj_->wtf.position = { enemy1Object3d_->wtf.position.x,enemy1Object3d_->wtf.position.y + 0.2f , enemy1Object3d_->wtf.position.z };
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
				enemyBulletObj_->wtf.position = { enemy1Object3d_->wtf.position.x,enemy1Object3d_->wtf.position.y + 0.2f , enemy1Object3d_->wtf.position.z };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}
		//当たり判定(自機弾と敵3)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne3WorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	if (liveFlag == true) {
		//当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBulletWorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
	}
	
	fbxObject3d_->Update();
	Knock0Object3d_->Update();
	enemyObject3d_->Update();
	Knock1Object3d_->Update();
	enemy1Object3d_->Update();
	Knock2Object3d_->Update();
	enemyBulletObj_->Update();
}

void Enemy::Draw() {
	if (liveFlag == true) {
		if (isShootFlag == true) {
			
			enemyBulletObj_->Draw();
			
		}
	}
	if (hp == 1) {
		if (liveFlag == false) {

			enemyBulletObj_->wtf.position = { enemyObject3d_->wtf.position.x,enemyObject3d_->wtf.position.y + 0.2f , enemyObject3d_->wtf.position.z };
		}
	}
	else if (hp == 2) {
		if (liveFlag == false) {

			enemyBulletObj_->wtf.position = { enemy1Object3d_->wtf.position.x,enemy1Object3d_->wtf.position.y + 0.2f , enemy1Object3d_->wtf.position.z };
		}
	}
	else if (hp == 3) {
		if (liveFlag == false) {

			enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
		}
	}
}

void Enemy::FbxDraw() {
	if (ClearMove == 0) {
		if (liveFlag == true) {
			if (hp == 1) {

				fbxObject3d_->Draw(dxCommon->GetCommandList());
				
				if (fbxObject3d_->wtf.position.z <= 0.5) {
					hp = 2;
					fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
				}

			}
			else if (hp == 2) {
			
				enemyObject3d_->Draw(dxCommon->GetCommandList());

				enemyObject3d_->wtf.position.z -= moveSpeed_;

				if (enemyObject3d_->wtf.position.z <= 0.5) {
					//元の座標に戻す
					fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemyObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemy1Object3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					hp = 3;
					enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
				}
			}
			else if (hp == 3) {

				enemy1Object3d_->Draw(dxCommon->GetCommandList());

				enemy1Object3d_->wtf.position.z -= moveSpeed_;

				if (enemy1Object3d_->wtf.position.z <= 0.5) {
					//元の座標に戻す
					fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemyObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemy1Object3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					hp = 1;
					enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
				}
			}
		}
		else if (liveFlag == false) {
			timer++;
			if (hp == 1) {
				//リアクション
			
				if (timer <= 69) {
					fbxObject3d_->Draw(dxCommon->GetCommandList());
					fbxObject3d_->wtf.rotation.y++;

				}
				
				if (timer >= 100) {
					//元の座標に戻す
					fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
					enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
					enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
					fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemyObject3d_->wtf.rotation = { 0.0f,-2.8f,0.0f };
					enemy1Object3d_->wtf.rotation = { 0.0f,-2.8f,0.0f };
					fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemyObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemy1Object3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					timer = 0;
					hp = 2;
					liveFlag = true;
				}
			}
			if (hp == 2) {
				//リアクション
				
				if (timer <= 69) {
					enemyObject3d_->Draw(dxCommon->GetCommandList());
					enemyObject3d_->wtf.rotation.y++;
				}
				
				if (timer >= 100) {
					//元の座標に戻す
					fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
					enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
					enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
					fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemyObject3d_->wtf.rotation = { 0.0f,-2.8f,0.0f };
					enemy1Object3d_->wtf.rotation = { 0.0f,-2.8f,0.0f };
					fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemyObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemy1Object3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					timer = 0;
					hp = 3;
					liveFlag = true;
				}
			}
			if (hp == 3) {
				//リアクション
				
				if (timer <= 69) {
					enemy1Object3d_->Draw(dxCommon->GetCommandList());
					enemy1Object3d_->wtf.rotation.y++;
				}
				if (timer >= 100) {
					//元の座標に戻す
					fbxObject3d_->wtf.position = { 0.0f,-0.3f,+3.0f };
					enemyObject3d_->wtf.position = { -0.5f,-0.3f,+3.0f };
					enemy1Object3d_->wtf.position = { 0.5f,-0.3f,+3.0f };
					fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
					enemyObject3d_->wtf.rotation = { 0.0f,-2.8f,0.0f };
					enemy1Object3d_->wtf.rotation = { 0.0f,-2.8f,0.0f };
					fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemyObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					enemy1Object3d_->wtf.scale = { 1.0f,1.0f,1.0f };
					timer = 0;
					hp = 1;
					liveFlag = true;
				}
			}
		}
	}
}

void Enemy::EffUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 0.1f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 0.1f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		
		pos += player_->GetWorldPosition();
		
		//速度
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 0.5f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 0.5f;

		//追加
		particleManager->Add(20, pos, vel, acc, 1.0f, 0.0f);

		particleManager->Update();
	}
}

void Enemy::EffDraw()
{
	if (liveFlag == true) {
		//ダメージエフェクト
		if (isEffFlag == 1) {
			// 3Dオブクジェクトの描画
			particleManager->Draw();
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
	liveFlag = false;
	enemyCount = enemyCount + 1;
}

void Enemy::OnColisionPlayer()
{
	isEffFlag = 1;
	playerHp = playerHp - 1;
}

