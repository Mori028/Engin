#include"Boss.h"
#include "player.h"

Boss::Boss() {

}

Boss::~Boss() {

	//FBX�I�u�W�F�N�g���
	delete fbxObject3d_;
	delete fbxModel_;
}

void Boss::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");


	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();

	//�ҋ@
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,1.0f,+3.0f };
	fbxObject3d_->wtf.scale = { 3.5f,3.5f,3.5f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f, true);


	//�e
	BossBulletModel_ = Model::LoadFromOBJ("boll");
	BossBulletObj_ = Object3d::Create();
	BossBulletObj_->SetModel(BossBulletModel_);
	BossBulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.2f , fbxObject3d_->wtf.position.z };
	BossBulletObj_->wtf.scale = { 0.5f,0.5f,0.5f };
}

void Boss::Update() {
	
	if (fbxObject3d_->wtf.position.y >= -0.8) {
		fbxObject3d_->wtf.position.y -= moveSpeed_;
	}
	else {
		fbxObject3d_->wtf.position = { 0.0f,-0.8f,+3.0f };
	}

	//�����蔻��(���@�e�ƓG1)
	if (coll.CircleCollision(player_->GetBulletWorldPosition(), GetWorldPosition(), 0.1f, 0.3f)) {
		OnColision();
	};	
	
	//�����蔻��(���@�ƓG�e)
	if (coll.CircleCollision(player_->GetWorldPosition(), GetBulletWorldPosition(), 0.1f, 0.1f)) {
		OnColisionPlayer();
	};

	fbxObject3d_->Update();
	BossBulletObj_->Update();
}

void Boss::Draw() {
	if (liveFlag == 1) {
		if (isShootFlag == true) {

			BossBulletObj_->Draw();

		}
	}
}

void Boss::FbxDraw() {
	
	fbxObject3d_->Draw(dxCommon->GetCommandList());
	//�G�̐ڋ�
	/*fbxObject3d_->wtf.position.z -= moveSpeed_;*/

}

Vector3 Boss::GetWorldPosition() {
	fbxObject3d_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Boss::GetBulletWorldPosition()
{
	BossBulletObj_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = BossBulletObj_->wtf.matWorld.m[3][0];
	worldPos.y = BossBulletObj_->wtf.matWorld.m[3][1];
	worldPos.z = BossBulletObj_->wtf.matWorld.m[3][2];

	return worldPos;
}

void Boss::OnColision()
{
	liveFlag = 0;
	BossCount = BossCount + 1;
}

void Boss::OnColisionPlayer()
{
	playerHp = playerHp - 1;
}

