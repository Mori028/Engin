#include "bullet.h"
#include "player.h"
#include "enemys.h"
/*
* @file Bullet.cpp
* @brind 敵の動きなど
*/

void Bullet::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();
	
	//弾1
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	enemyBulletObj_ = Object3d::Create();
	enemyBulletObj_->SetModel(enemyBulletModel_);
	enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+3.0f };
	enemyBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };


	//弾2
	enemyBullet1Model_ = Model::LoadFromOBJ("boll");
	enemyBullet1Obj_ = Object3d::Create();
	enemyBullet1Obj_->SetModel(enemyBullet1Model_);
	enemyBullet1Obj_->wtf.position = { 0.0f,-0.3f,+3.0f };
	enemyBullet1Obj_->wtf.scale = { 0.5f,0.5f,0.5f };

	//弾3
	enemyBullet2Model_ = Model::LoadFromOBJ("boll");
	enemyBullet2Obj_ = Object3d::Create();
	enemyBullet2Obj_->SetModel(enemyBullet2Model_);
	enemyBullet2Obj_->wtf.position = { 0.0f,-0.3f,+3.0f };
	enemyBullet2Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	
	//自機狙い弾
	enemyBullet3Model_ = Model::LoadFromOBJ("boll");
	enemyBullet3Obj_ = Object3d::Create();
	enemyBullet3Obj_->SetModel(enemyBullet3Model_);
	enemyBullet3Obj_->wtf.position = { 0.0f,-0.3f,+3.0f };
	enemyBullet3Obj_->wtf.scale = { 0.5f,0.5f,0.5f };

	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();
}

void Bullet::Reset()
{
	enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+3.0f };
	enemyBullet1Obj_->wtf.position = { 0.5f,-0.3f,+3.0f };
	enemyBullet2Obj_->wtf.position = { -0.5f,-0.3f,+3.0f };
	enemyBullet2Obj_->wtf.position = { 0.0f,-0.3f,+3.0f };
	//パーティクル初期化
	timer = 0;
	effTimer = 0;
	isEffFlag = 0;
	ClearMove = 0;
	liveFlag = true;
}

void Bullet::Clear()
{
	ClearMove = 1;
}

void Bullet::Over()
{
	liveFlag = false;
}

void Bullet::Update() {

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

	////////////bulletMode（1中央,2上,3下）
	//攻撃種類を作るため設置
	changeTimer++;
	if (changeTimer == 110) {
		bulletMode = 2;
	}
	if (changeTimer == 220) {
		bulletMode = 3;
	}
	if (changeTimer == 330) {
		bulletMode = 1;
		changeTimer = 0;
	}

	/////////デバッグ用////////////
	bulletMode = 4;
	////////////////////////////
	 
	
	/////////中央

	if (bulletMode == 1) {
		//雑魚敵の攻撃
		float shortSpeed = 0.05f;

		bulletTimer++;
		if (bulletTimer >= 40) {
			isShootFlag = true;
		}
		if (isShootFlag == true) {
			bulletCoolTime++;
			enemyBulletObj_->wtf.position.z -= shortSpeed;
			enemyBullet1Obj_->wtf.position.z -= shortSpeed;
			enemyBullet2Obj_->wtf.position.z -= shortSpeed;

		}
		else {
			enemyBulletObj_->wtf.position = { 0.0f,0.0f,+3.0f };
			enemyBullet1Obj_->wtf.position = { 0.5f,0.0f,+3.0f };
			enemyBullet2Obj_->wtf.position = { -0.5f,0.0f,+3.0f };
		}
		if (enemyBulletObj_->wtf.position.z <= 0.0f) {
			bulletTimer = 0;
			isShootFlag = false;
		}
	}

	/////////下段
	if (bulletMode == 2) {
		//雑魚敵の攻撃
		float shortSpeed = 0.05f;

		bulletTimer++;
		if (bulletTimer >= 40) {
			isShootFlag = true;
		}
		if (isShootFlag == true) {
			bulletCoolTime++;
			enemyBulletObj_->wtf.position.z -= shortSpeed;
			enemyBullet1Obj_->wtf.position.z -= shortSpeed;
			enemyBullet2Obj_->wtf.position.z -= shortSpeed;

		}
		else {
			enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+3.0f };
			enemyBullet1Obj_->wtf.position = { 0.5f,-0.3f,+3.0f };
			enemyBullet2Obj_->wtf.position = { -0.5f,-0.3f,+3.0f };
		}
		if (enemyBulletObj_->wtf.position.z <= 0.0f) {
			bulletTimer = 0;
			isShootFlag = false;
		}
	}
	/////////上段
	if (bulletMode == 3) {
		//雑魚敵の攻撃
		float shortSpeed = 0.05f;

		bulletTimer++;
		if (bulletTimer >= 40) {
			isShootFlag = true;
		}
		if (isShootFlag == true) {
			bulletCoolTime++;
			enemyBulletObj_->wtf.position.z -= shortSpeed;
			enemyBullet1Obj_->wtf.position.z -= shortSpeed;
			enemyBullet2Obj_->wtf.position.z -= shortSpeed;

		}
		else {
			enemyBulletObj_->wtf.position = { 0.0f,0.3f,+3.0f };
			enemyBullet1Obj_->wtf.position = { 0.5f,0.3f,+3.0f };
			enemyBullet2Obj_->wtf.position = { -0.5f,0.3f,+3.0f };
		}
		if (enemyBulletObj_->wtf.position.z <= 0.0f) {
			bulletTimer = 0;
			isShootFlag = false;
		}
	
	}
	
	/////自機狙い
	if (bulletMode == 4) {
		//雑魚敵の攻撃
		float shortSpeed = 0.05f;
		enemyBullet3Obj_->wtf.position.z += shortSpeed;
		

	}

	if (liveFlag == true) {
		//当たり判定(自機と敵弾1)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBulletWorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//当たり判定(自機と敵弾2)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet1WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//当たり判定(自機と敵弾3)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet2WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//当たり判定(自機と自機狙い敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet3WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
	}
	
	enemyBulletObj_->Update();
	enemyBullet1Obj_->Update();
	enemyBullet2Obj_->Update();
}

void Bullet::Draw() {
	
	if (liveFlag == true) {
		if (isShootFlag == true) {
			enemyBulletObj_->Draw();
			enemyBullet1Obj_->Draw();
			enemyBullet2Obj_->Draw();
		}

		if (bulletMode == 4) {
			if (isShootFlag == true) {
				enemyBullet3Obj_->Draw();
			}
		}
	}
	if (liveFlag == false) {

		enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+3.0f };
		enemyBullet1Obj_->wtf.position = { 0.5f,-0.3f,+3.0f };
		enemyBullet2Obj_->wtf.position = { -0.5f,-0.3f,+3.0f };
	}
}

void Bullet::EffUpdate()
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

void Bullet::EffDraw()
{
	
	//ダメージエフェクト
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		particleManager->Draw();
	}
	
}

Vector3 Bullet::GetBulletWorldPosition()
{
	enemyBulletObj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemyBulletObj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBulletObj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBulletObj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet1WorldPosition()
{
	enemyBullet1Obj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemyBullet1Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet1Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet1Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet2WorldPosition()
{
	enemyBullet2Obj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemyBullet2Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet2Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet2Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet3WorldPosition()
{
	enemyBullet3Obj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = enemyBullet3Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet3Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet3Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}

void Bullet::OnColisionPlayer()
{
	isEffFlag = 1;
}

