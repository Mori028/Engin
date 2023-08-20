#include"Enemy.h"
#include "player.h"

Enemy::Enemy() {

}

Enemy::~Enemy() {

	//FBXƒIƒuƒWƒFƒNƒg‰ð•ú
	delete fbxObject3d_;
	delete fbxModel_;
}

void Enemy::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrƒ`ƒFƒbƒN
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");

	fbxredModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma1");

	fbxwhiteModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma2");

	// ƒfƒoƒCƒX‚ðƒZƒbƒg
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// ƒOƒ‰ƒtƒBƒbƒNƒXƒpƒCƒvƒ‰ƒCƒ“¶¬
	FBXObject3d::CreateGraphicsPipeline();

	//‘Ò‹@
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

	//’e
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	enemyBulletObj_ = Object3d::Create();
	enemyBulletObj_->SetModel(enemyBulletModel_);
	enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y +0.2f , fbxObject3d_->wtf.position.z };
	enemyBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };
}

void Enemy::Update() {
	if (hp == 1) {

		////////////
		//UŒ‚Ží—Þ‚ðì‚é‚½‚ß‰¼Ý’uiŒã‚ÅÁ‚·j
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
			//ŽG‹›“G‚ÌUŒ‚
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
			//ŽG‹›“G‚ÌUŒ‚
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
			//ŽG‹›“G‚ÌUŒ‚
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

		//“–‚½‚è”»’è(Ž©‹@’e‚Æ“G1)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetWorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	if (hp == 2) {
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
			//ŽG‹›“G‚ÌUŒ‚
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
			//ŽG‹›“G‚ÌUŒ‚
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
			//ŽG‹›“G‚ÌUŒ‚
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
		//“–‚½‚è”»’è(Ž©‹@’e‚Æ“G2)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne2WorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	if (hp == 3) {
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
			//ŽG‹›“G‚ÌUŒ‚
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
			//ŽG‹›“G‚ÌUŒ‚
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
			//ŽG‹›“G‚ÌUŒ‚
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
		//“–‚½‚è”»’è(Ž©‹@’e‚Æ“G3)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne3WorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	//“–‚½‚è”»’è(Ž©‹@‚Æ“G’e)
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
			
			enemyBulletObj_->Draw();
			
		}
	}
	if (hp == 1) {
		if (liveFlag == 0) {

			enemyBulletObj_->wtf.position = { enemyObject3d_->wtf.position.x,enemyObject3d_->wtf.position.y + 0.2f , enemyObject3d_->wtf.position.z };
		}
	}
	else if (hp == 2) {
		if (liveFlag == 0) {

			enemyBulletObj_->wtf.position = { enemy1Object3d_->wtf.position.x,enemy1Object3d_->wtf.position.y + 0.2f , enemy1Object3d_->wtf.position.z };
		}
	}
	else if (hp == 3) {
		if (liveFlag == 0) {

			enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
		}
	}
}

void Enemy::FbxDraw() {
	if (liveFlag == 1) {
		if (hp == 1) {

			fbxObject3d_->Draw(dxCommon->GetCommandList());
			//“G‚ÌÚ‹ß
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
			//Œ³‚ÌÀ•W‚É–ß‚·
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
			//Œ³‚ÌÀ•W‚É–ß‚·
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
			//Œ³‚ÌÀ•W‚É–ß‚·
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
	//ƒ[ƒ‹ƒhs—ñ‚Ì•½sˆÚ“®¬•ª
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne2WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ƒ[ƒ‹ƒhs—ñ‚Ì•½sˆÚ“®¬•ª
	worldPos.x = enemyObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemyObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemyObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne3WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//ƒ[ƒ‹ƒhs—ñ‚Ì•½sˆÚ“®¬•ª
	worldPos.x = enemy1Object3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemy1Object3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemy1Object3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetBulletWorldPosition()
{
	enemyBulletObj_->wtf.UpdateMat();
	//ƒ[ƒ‹ƒhs—ñ‚Ì•½sˆÚ“®¬•ª
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

