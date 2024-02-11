#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input)
{
	//’e
	bulletModel_ = Model::LoadFromOBJ("boll");
	bulletObj_ = Object3d::Create();
	bulletObj_->SetModel(bulletModel_);
	bulletObj_->wtf.position = { 0,0,0 };
}


void Bullet::Update()
{
	if (moovFlag == false) {
		stoptimer++;

		if (stoptimer >= 250) {
			moovFlag = true;
		}
	}
	//’e‚Ì”­ŽË
	float shortSpeed = 1.0f;
	if (moovFlag == 1) {
		if (input_->PushKey(DIK_SPACE) || input_->ButtonInput(RT)) {
			enemyDistance.nomalize();
			isShootFlag = true;
		}
		else {
			isShootFlag = false;
		}
	}
}

void Bullet::Draw()
{
	if (isShootFlag == true) {
		bulletObj_->Draw();
	}
}

Vector3 Bullet::bVelocity(Vector3& velocity, Transform& worldTransform)
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

Vector3 Bullet::GetBulletWorldPosition()
{
	Vector3 BulletWorldPos;

	bulletObj_->wtf.UpdateMat();

	//ƒ[ƒ‹ƒhs—ñ‚Ì•½sˆÚ“®¬•ª
	BulletWorldPos.x = bulletObj_->wtf.matWorld.m[3][0];
	BulletWorldPos.y = bulletObj_->wtf.matWorld.m[3][1];
	BulletWorldPos.z = bulletObj_->wtf.matWorld.m[3][2];

	return BulletWorldPos;
}
