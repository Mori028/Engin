#include "enemys.h"


void Enemys::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;

	//弾
	EnemysModel_ = Model::LoadFromOBJ("boll");
	EnemysObj_ = Object3d::Create();
	EnemysObj_->SetModel(EnemysModel_);
	EnemysObj_->wtf.position = { -0.0f,-0.0f,+3.0f };
	EnemysObj_->wtf.scale = { 0.1f,0.1f,0.1f };

}


void Enemys::Update()
{
	EnemysObj_->wtf.position.z -= moveSpeed_;
	// 敵の更新
	EnemysObj_->Update();
}

void Enemys::Draw()
{
	EnemysObj_->Draw();
}



