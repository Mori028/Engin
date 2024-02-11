#include "enemys.h"


void Enemys::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;

	//�e
	EnemysModel_ = Model::LoadFromOBJ("boll");
	EnemysObj_ = Object3d::Create();
	EnemysObj_->SetModel(EnemysModel_);
	EnemysObj_->wtf.position = { -0.0f,-0.0f,+3.0f };
	EnemysObj_->wtf.scale = { 0.1f,0.1f,0.1f };

}


void Enemys::Update()
{
	EnemysObj_->wtf.position.z -= moveSpeed_;
	// �G�̍X�V
	EnemysObj_->Update();
}

void Enemys::Draw()
{
	EnemysObj_->Draw();
}



