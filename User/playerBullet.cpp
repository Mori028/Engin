#include "playerBullet.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize(DirectXCommon* dxCommon, Input* input)
{
	//’e
	bulletModel_ = Model::LoadFromOBJ("boll");
	bulletObj_ = Object3d::Create();
	bulletObj_->SetModel(bulletModel_);
	bulletObj_->wtf.position = { 0,0,0 };
}

void PlayerBullet::Update()
{
	if (moovFlag == 0) {
		stoptimer++;

		if (stoptimer >= 250) {
			moovFlag = 1;
		}
	}
	//’e‚Ì”­ŽË
	float shortSpeed = 1.0f;
	if (moovFlag == 1) {
		if (input_->TriggerKey(DIK_SPACE) || input_->ButtonInput(RT)) {
			isShootFlag = true;
		}
		if (isShootFlag == true) {
			bulletCoolTime++;
			bulletObj_->wtf.position += enemyDistance;
			distance = enemyDistance;
			distance *= shortSpeed;
		}
		else {
			bulletObj_->wtf.position = { player_->GetWorldPosition() };
		}
		if (bulletCoolTime >= 10.0f) {
			bulletCoolTime = 0;
			isShootFlag = false;
		}
	}
}

void PlayerBullet::Move()
{
	
}

void PlayerBullet::Draw()
{
	if (isShootFlag == true) {
		bulletObj_->Draw();
	}
}

Vector3 PlayerBullet::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//“àÏ
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

Vector3 PlayerBullet::GetBulletWorldPosition()
{
	Vector3 BulletWorldPos;

	bulletObj_->wtf.UpdateMat();

	//ƒ[ƒ‹ƒhs—ñ‚Ì•½sˆÚ“®¬•ª
	BulletWorldPos.x = bulletObj_->wtf.matWorld.m[3][0];
	BulletWorldPos.y = bulletObj_->wtf.matWorld.m[3][1];
	BulletWorldPos.z = bulletObj_->wtf.matWorld.m[3][2];

	return BulletWorldPos;
}
