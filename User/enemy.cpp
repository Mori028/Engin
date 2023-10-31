#include"Enemy.h"
#include "player.h"

/*
* @file enemy.cpp
* @brind �G�̓����Ȃ�
*/
Enemy::Enemy() {

}

Enemy::~Enemy() {

	//FBX�I�u�W�F�N�g���
	delete fbxObject3d_;
	delete fbxModel_;
}

void Enemy::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	//���f��
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");

	fbxredModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma1");

	fbxwhiteModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma2");

	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();

	//�ҋ@
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

	//�e
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	enemyBulletObj_ = Object3d::Create();
	enemyBulletObj_->SetModel(enemyBulletModel_);
	enemyBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y +0.2f , fbxObject3d_->wtf.position.z };
	enemyBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };

	//�p�[�e�B�N������
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();
}

void Enemy::Reset()
{
	//�G�P
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//�G2
	enemyObject3d_->Initialize();
	enemyObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	//�G3
	enemy1Object3d_->Initialize();
	enemy1Object3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	enemyBulletObj_->Initialize();
	//�p�[�e�B�N��������
	effTimer = 0;
	isEffFlag = 0;
}

void Enemy::Over()
{
	liveFlag = 2;
}

void Enemy::Update() {
	//�_���[�W�G�t�F�N�g
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

		////////////
		//�U����ނ���邽�߉��ݒu�i��ŏ����j
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
			//�G���G�̍U��
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
			//�G���G�̍U��
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
			//�G���G�̍U��
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

		//�����蔻��(���@�e�ƓG1)
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
			//�G���G�̍U��
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
			//�G���G�̍U��
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
			//�G���G�̍U��
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
		//�����蔻��(���@�e�ƓG2)
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
			//�G���G�̍U��
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
			//�G���G�̍U��
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
			//�G���G�̍U��
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
		//�����蔻��(���@�e�ƓG3)
		if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetEne3WorldPosition(), 0.1f, 0.3f)) {
			OnColision();
		};
	}
	//�����蔻��(���@�ƓG�e)
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
			//�G�̐ڋ�
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
			//���̍��W�ɖ߂�
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
			//���̍��W�ɖ߂�
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
			//���̍��W�ɖ߂�
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

void Enemy::EffUpdate()
{
	//�p�[�e�B�N���͈�
	for (int i = 0; i < 20; i++) {
		//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 0.1f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 0.1f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		
		pos += player_->GetWorldPosition();
		
		//���x
		//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 0.5f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 0.5f;

		//�ǉ�
		particleManager->Add(20, pos, vel, acc, 1.0f, 0.0f);

		particleManager->Update();
	}
}

void Enemy::EffDraw()
{
	if (liveFlag == 1) {
		//�_���[�W�G�t�F�N�g
		if (isEffFlag == 1) {
			// 3D�I�u�N�W�F�N�g�̕`��
			particleManager->Draw();
		}
	}
}

Vector3 Enemy::GetWorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne2WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemyObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemyObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetEne3WorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemy1Object3d_->wtf.matWorld.m[3][0];
	worldPos.y = enemy1Object3d_->wtf.matWorld.m[3][1];
	worldPos.z = enemy1Object3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Enemy::GetBulletWorldPosition()
{
	enemyBulletObj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
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
	isEffFlag = 1;
	playerHp = playerHp - 1;
}

