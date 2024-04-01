#include "bullet.h"
#include "player.h"
#include "enemys.h"
/*
* @file Bullet.cpp
* @brind �G�̓����Ȃ�
*/

void Bullet::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();
	
	//�e1
	enemyBulletModel_ = Model::LoadFromOBJ("boll");
	enemyBulletObj_ = Object3d::Create();
	enemyBulletObj_->SetModel(enemyBulletModel_);
	enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+5.0f };
	enemyBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };


	//�e2
	enemyBullet1Model_ = Model::LoadFromOBJ("boll");
	enemyBullet1Obj_ = Object3d::Create();
	enemyBullet1Obj_->SetModel(enemyBullet1Model_);
	enemyBullet1Obj_->wtf.position = { -0.6f,-0.3f,+5.0f };
	enemyBullet1Obj_->wtf.scale = { 0.5f,0.5f,0.5f };

	//�e3
	enemyBullet2Model_ = Model::LoadFromOBJ("boll");
	enemyBullet2Obj_ = Object3d::Create();
	enemyBullet2Obj_->SetModel(enemyBullet2Model_);
	enemyBullet2Obj_->wtf.position = { 0.6f,-0.3f,+5.0f };
	enemyBullet2Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	
	//���@�_���e
	enemyBullet3Model_ = Model::LoadFromOBJ("boll");
	enemyBullet3Obj_ = Object3d::Create();
	enemyBullet3Obj_->SetModel(enemyBullet3Model_);
	enemyBullet3Obj_->wtf.position = { 0.0f,0.0f,+5.0f };
	enemyBullet3Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e5
	enemyBullet4Model_ = Model::LoadFromOBJ("boll");
	enemyBullet4Obj_ = Object3d::Create();
	enemyBullet4Obj_->SetModel(enemyBullet4Model_);
	enemyBullet4Obj_->wtf.position = { -0.6f,0.0f,+5.0f };
	enemyBullet4Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e6
	enemyBullet5Model_ = Model::LoadFromOBJ("boll");
	enemyBullet5Obj_ = Object3d::Create();
	enemyBullet5Obj_->SetModel(enemyBullet5Model_);
	enemyBullet5Obj_->wtf.position = { 0.6f,0.0f,+5.0f };
	enemyBullet5Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet6Model_ = Model::LoadFromOBJ("boll");
	enemyBullet6Obj_ = Object3d::Create();
	enemyBullet6Obj_->SetModel(enemyBullet6Model_);
	enemyBullet6Obj_->wtf.position = { 0.0f,0.3f,+5.0f };
	enemyBullet6Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet7Model_ = Model::LoadFromOBJ("boll");
	enemyBullet7Obj_ = Object3d::Create();
	enemyBullet7Obj_->SetModel(enemyBullet7Model_);
	enemyBullet7Obj_->wtf.position = { -0.6f,0.3f,+5.0f };
	enemyBullet7Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet8Model_ = Model::LoadFromOBJ("boll");
	enemyBullet8Obj_ = Object3d::Create();
	enemyBullet8Obj_->SetModel(enemyBullet8Model_);
	enemyBullet8Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet8Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	////�c�e
	enemyBullet9Model_ = Model::LoadFromOBJ("boll");
	enemyBullet9Obj_ = Object3d::Create();
	enemyBullet9Obj_->SetModel(enemyBullet8Model_);
	enemyBullet9Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet9Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet10Model_ = Model::LoadFromOBJ("boll");
	enemyBullet10Obj_ = Object3d::Create();
	enemyBullet10Obj_->SetModel(enemyBullet8Model_);
	enemyBullet10Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet10Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet11Model_ = Model::LoadFromOBJ("boll");
	enemyBullet11Obj_ = Object3d::Create();
	enemyBullet11Obj_->SetModel(enemyBullet8Model_);
	enemyBullet11Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet11Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet12Model_ = Model::LoadFromOBJ("boll");
	enemyBullet12Obj_ = Object3d::Create();
	enemyBullet12Obj_->SetModel(enemyBullet8Model_);
	enemyBullet12Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet12Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet13Model_ = Model::LoadFromOBJ("boll");
	enemyBullet13Obj_ = Object3d::Create();
	enemyBullet13Obj_->SetModel(enemyBullet8Model_);
	enemyBullet13Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet13Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	//�e
	enemyBullet14Model_ = Model::LoadFromOBJ("boll");
	enemyBullet14Obj_ = Object3d::Create();
	enemyBullet14Obj_->SetModel(enemyBullet8Model_);
	enemyBullet14Obj_->wtf.position = { 0.6f,0.3f,+5.0f };
	enemyBullet14Obj_->wtf.scale = { 0.5f,0.5f,0.5f };
	

	//�p�[�e�B�N������
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();
}

void Bullet::Reset()
{
	enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+5.0f };
	enemyBullet1Obj_->wtf.position = { -0.6f,-0.3f,+5.0f };
	enemyBullet2Obj_->wtf.position = { 0.6f,-0.3f,+5.0f };
	enemyBullet3Obj_->wtf.position = { 0.0f,0.0f,+5.0f };
	enemyBullet4Obj_->wtf.position = { -0.6f,0.0f,+5.0f };
	enemyBullet5Obj_->wtf.position = { 0.6f,0.0f,+5.0f };
	enemyBullet6Obj_->wtf.position = { 0.0f,0.3f,+5.0f };
	enemyBullet7Obj_->wtf.position = { -0.6f,0.3f,+5.0f };
	enemyBullet8Obj_->wtf.position = { 0.6f,0.3f,+5.0f };

	enemyBullet9Obj_->wtf.position = { 0.3f,-0.3f,+5.0f };
	enemyBullet10Obj_->wtf.position = { 0.3f,0.0f,+5.0f };
	enemyBullet11Obj_->wtf.position = { 0.3f,0.3f,+5.0f };
	enemyBullet12Obj_->wtf.position = { -0.3f,-0.3f,+5.0f };
	enemyBullet13Obj_->wtf.position = { -0.3f,0.0f,+5.0f };
	enemyBullet14Obj_->wtf.position = { -0.3f,0.3f,+5.0f };
	//�p�[�e�B�N��������
	timer = 0;
	effTimer = 0;
	isEffFlag = 0;
	ClearMove = 0;
	liveFlag = true;
	mode = false;
	bossTimer = 0;
	bossAttack = false;
	verticalAttack = false;
}

void Bullet::Clear()
{
	ClearMove = 1;
}

void Bullet::Over()
{
	liveFlag = false;
}

void Bullet::ModeChange()
{
	mode = true;
	enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+5.0f };
	enemyBullet1Obj_->wtf.position = { -0.4f,-0.3f,+5.0f };
	enemyBullet2Obj_->wtf.position = { 0.4f,-0.3f,+5.0f };
	enemyBullet3Obj_->wtf.position = { 0.0f,0.0f,+5.0f };
	enemyBullet4Obj_->wtf.position = { -0.4f,0.0f,+5.0f };
	enemyBullet5Obj_->wtf.position = { 0.4f,0.0f,+5.0f };
	enemyBullet6Obj_->wtf.position = { 0.0f,0.3f,+5.0f };
	enemyBullet7Obj_->wtf.position = { -0.4f,0.3f,+5.0f };
	enemyBullet8Obj_->wtf.position = { 0.4f,0.3f,+5.0f };
	enemyBullet9Obj_->wtf.position = { 0.3f,-0.3f,+5.0f };
	enemyBullet10Obj_->wtf.position = { 0.3f,0.0f,+5.0f };
	enemyBullet11Obj_->wtf.position = { 0.3f,0.3f,+5.0f };
	enemyBullet12Obj_->wtf.position = { -0.3f,-0.3f,+5.0f };
	enemyBullet13Obj_->wtf.position = { -0.3f,0.0f,+5.0f };
	enemyBullet14Obj_->wtf.position = { -0.3f,0.3f,+5.0f };
}

void Bullet::Update() {

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
	if (mode == false) {


		////////////bulletMode�i1����,2��,3���j
		//�U����ނ���邽�ߐݒu
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

		/////////�f�o�b�O�p////////////

		/*bulletMode = 4;*/

		////////////////////////////


		/////////����

		if (bulletMode == 1) {
			//�G���G�̍U��

			bulletTimer++;
			if (bulletTimer >= 40) {
				isShootFlag = true;
			}
			if (isShootFlag == true) {
				bulletCoolTime++;
				enemyBulletObj_->wtf.position.z -= shortSpeed;
				enemyBullet1Obj_->wtf.position.z -= shortSpeed;
				enemyBullet2Obj_->wtf.position.z -= shortSpeed;
				enemyBullet1Obj_->wtf.position.x += shortXSpeed;
				enemyBullet2Obj_->wtf.position.x -= shortXSpeed;

			}
			else {
				enemyBulletObj_->wtf.position = { 0.0f,0.0f,+5.0f };
				enemyBullet1Obj_->wtf.position = { 0.0f,0.0f,+5.0f };
				enemyBullet2Obj_->wtf.position = { -0.0f,0.0f,+5.0f };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}

		/////////���i
		if (bulletMode == 2) {
			//�G���G�̍U��
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
				enemyBullet1Obj_->wtf.position.x += shortXSpeed;
				enemyBullet2Obj_->wtf.position.x -= shortXSpeed;
			}
			else {
				enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+5.0f };
				enemyBullet1Obj_->wtf.position = { 0.0f,-0.3f,+5.0f };
				enemyBullet2Obj_->wtf.position = { -0.0f,-0.3f,+5.0f };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}
		}
		/////////��i
		if (bulletMode == 3) {
			//�G���G�̍U��
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
				enemyBullet1Obj_->wtf.position.x += shortXSpeed;
				enemyBullet2Obj_->wtf.position.x -= shortXSpeed;

			}
			else {
				enemyBulletObj_->wtf.position = { 0.0f,0.3f,+5.0f };
				enemyBullet1Obj_->wtf.position = { 0.0f,0.3f,+5.0f };
				enemyBullet2Obj_->wtf.position = { 0.0f,0.3f,+5.0f };
			}
			if (enemyBulletObj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
			}

		}

		///���@�_��
		if (bulletMode == 4) {
			//�G���G�̍U��
			float shortSpeed = 0.03f;

			bulletTimer++;
			if (bulletTimer >= 60) {
				isShootFlag = true;
			}

			enemyBullet3Obj_->wtf.position.z -= shortSpeed;

			if (enemyBullet3Obj_->wtf.position.z <= 0.0f) {
				bulletTimer = 0;
				isShootFlag = false;
				enemyBullet3Obj_->wtf.position = { 0.0f,-0.3f,+3.0f };
			}
		}
	}
	if (mode == true) {
		bossTimer++;
		if (bossTimer >= 200) {
			bossAttack = true;
		}
		if (bossTimer >= 240) {
			verticalAttack = true;
		}
		if (bossTimer >= 350) {
			bossAttack = false;
			verticalAttack = false;
			bossTimer = 0;
		}
		if (bossTimer <= 0) {
			ModeChange();
		}

		if (bossAttack == true) {
			enemyBulletObj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet1Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet2Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet3Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet4Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet5Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet6Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet7Obj_->wtf.position.z-= bossMoveSpeed_;
			enemyBullet8Obj_->wtf.position.z-= bossMoveSpeed_;
		}
		if (verticalAttack == true) {
			enemyBullet9Obj_->wtf.position.z -= bossMoveSpeed_;
			enemyBullet10Obj_->wtf.position.z -= bossMoveSpeed_;
			enemyBullet11Obj_->wtf.position.z -= bossMoveSpeed_;
			enemyBullet12Obj_->wtf.position.z -= bossMoveSpeed_;
			enemyBullet13Obj_->wtf.position.z -= bossMoveSpeed_;
			enemyBullet14Obj_->wtf.position.z -= bossMoveSpeed_;
		}
	}

	if (liveFlag == true) {
		//�����蔻��(���@�ƓG�e1)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBulletWorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e2)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet1WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e3)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet2WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�Ǝ��@�_���G�e)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet3WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e2)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet4WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e3)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet5WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�Ǝ��@�_���G�e)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet6WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e2)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet7WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e3)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet8WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�Ǝ��@�_���G�e)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet9WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e2)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet10WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�ƓG�e3)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet11WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�Ǝ��@�_���G�e)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet12WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�Ǝ��@�_���G�e)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet13WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//�����蔻��(���@�Ǝ��@�_���G�e)
		if (coll.CircleCollision(player_->GetWorldPosition(), GetBullet14WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};

	}

	enemyBulletObj_->Update();
	enemyBullet1Obj_->Update();
	enemyBullet2Obj_->Update();
	enemyBullet3Obj_->Update();
	enemyBullet4Obj_->Update();
	enemyBullet5Obj_->Update();
	enemyBullet6Obj_->Update();
	enemyBullet7Obj_->Update();
	enemyBullet8Obj_->Update();
	enemyBullet9Obj_->Update();
	enemyBullet10Obj_->Update();
	enemyBullet11Obj_->Update();
	enemyBullet12Obj_->Update();
	enemyBullet13Obj_->Update();
	enemyBullet14Obj_->Update();
}

void Bullet::Draw() {
	if (mode == false) {
		if (liveFlag == true) {
			if (bulletMode == 4) {
				if (isShootFlag == true) {
					enemyBullet3Obj_->Draw();
				}
			}
			else {
				if (isShootFlag == true) {
					enemyBulletObj_->Draw();
					enemyBullet1Obj_->Draw();
					enemyBullet2Obj_->Draw();
				}
			}

		}
		if (liveFlag == false) {

			enemyBulletObj_->wtf.position = { 0.0f,-0.3f,+5.0f };
			enemyBullet1Obj_->wtf.position = { 0.0f,-0.3f,+5.0f };
			enemyBullet2Obj_->wtf.position = { 0.0f,-0.3f,+5.0f };
			enemyBullet3Obj_->wtf.position = { 0.0f,-0.3f,+5.0f };
		}
	}
	else if (mode == true) {
		if (liveFlag == true) {
			if (bossTimer >= 180) {
				enemyBulletObj_->Draw();
			}
			if (bossTimer >= 160) {
				enemyBullet1Obj_->Draw();
			}
			if (bossTimer >= 140) {
				enemyBullet2Obj_->Draw();
			}
			if (bossTimer >= 120) {
				enemyBullet3Obj_->Draw();
			}
			if (bossTimer >= 100) {
				enemyBullet4Obj_->Draw();
			}
			if (bossTimer >= 80) {
				enemyBullet5Obj_->Draw();
			}
			if (bossTimer >= 60) {
				enemyBullet6Obj_->Draw();
			}
			if (bossTimer >= 40) {
				enemyBullet7Obj_->Draw();
			}
			if (bossTimer >= 20) {
				enemyBullet8Obj_->Draw();
			}

			if (verticalAttack == true) {
				enemyBullet9Obj_->Draw();
				enemyBullet10Obj_->Draw();
				enemyBullet11Obj_->Draw();
				enemyBullet12Obj_->Draw();
				enemyBullet13Obj_->Draw();
				enemyBullet14Obj_->Draw();
			}
		}
	}

}

void Bullet::EffUpdate()
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

void Bullet::EffDraw()
{
	
	//�_���[�W�G�t�F�N�g
	if (isEffFlag == 1) {
		// 3D�I�u�N�W�F�N�g�̕`��
		particleManager->Draw();
	}
	
}

Vector3 Bullet::GetBulletWorldPosition()
{
	enemyBulletObj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBulletObj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBulletObj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBulletObj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet1WorldPosition()
{
	enemyBullet1Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet1Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet1Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet1Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet2WorldPosition()
{
	enemyBullet2Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet2Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet2Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet2Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet3WorldPosition()
{
	enemyBullet3Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet3Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet3Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet3Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet4WorldPosition()
{
	enemyBullet4Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet4Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet4Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet4Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet5WorldPosition()
{
	enemyBullet5Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet5Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet5Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet5Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet6WorldPosition()
{
	enemyBullet6Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet6Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet6Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet6Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet7WorldPosition()
{
	enemyBullet7Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet7Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet7Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet7Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet8WorldPosition()
{
	enemyBullet8Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet8Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet8Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet8Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet9WorldPosition()
{
	enemyBullet9Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet9Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet9Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet9Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet10WorldPosition()
{
	enemyBullet10Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet10Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet10Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet10Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet11WorldPosition()
{
	enemyBullet11Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet11Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet11Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet11Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet12WorldPosition()
{
	enemyBullet12Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet12Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet12Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet12Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet13WorldPosition()
{
	enemyBullet13Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet13Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet13Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet13Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}
Vector3 Bullet::GetBullet14WorldPosition()
{
	enemyBullet14Obj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = enemyBullet14Obj_->wtf.matWorld.m[3][0];
	worldPos.y = enemyBullet14Obj_->wtf.matWorld.m[3][1];
	worldPos.z = enemyBullet14Obj_->wtf.matWorld.m[3][2];

	return worldPos;
}


void Bullet::OnColisionPlayer()
{
	isEffFlag = 1;
}

