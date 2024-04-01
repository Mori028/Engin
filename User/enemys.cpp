#include "enemys.h"
#include <imgui.h>


void Enemys::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	//���f��
	EnemysModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");

	//�G�̑ҋ@
	EnemysObject3d_ = new FBXObject3d;
	EnemysObject3d_->Initialize();
	EnemysObject3d_->SetModel(EnemysModel_);
	EnemysObject3d_->wtf.position = { 0.0f,-0.2f,5.5f };
	EnemysObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	EnemysObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
	EnemysObject3d_->PlayAnimation(1.0f, true);
}

void Enemys::Update()
{
	//�G�̍s��
	/*EnemysObject3d_->wtf.position.x -= moveSpeed_;*/
	
	// ���Ԍo�߂Ńf�X
	//if (--dethTimer_ <= 0) {
	//	isDead_ = true;
	//}

	//// HP0�Ńf�X
	//if (dethHp_ <= 0) {
	//	isDead_ = true;
	//}

	// �G�̍X�V
	EnemysObject3d_->Update();
}

void Enemys::Draw()
{
	// �G�̕`��
	//EnemysObj_->Draw();
}

void Enemys::FbxDraw()
{
	// �G�̕`��
	EnemysObject3d_->Draw(dxCommon->GetCommandList());
}

void Enemys::OnColision()
{
	isDead_ = true;
}

Vector3 Enemys::GetWorldPosition()
{
	Vector3 worldPos;

	EnemysObject3d_->wtf.UpdateMat();
	//���[���h�s��̕��s�ړ�����
	worldPos.x = EnemysObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = EnemysObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = EnemysObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}