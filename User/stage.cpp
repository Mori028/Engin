#include "stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();

	felld = Model::LoadFromOBJ("stage");
	stage_ = Object3d::Create();
	stage_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage_->SetModel(felld);

}

void Stage::Reset()
{
	stage_->Initialize();
	stage_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage_->wtf.rotation = { 0.0f,-1.5f,0.0f };
}

void Stage::Update()
{
	stage_->wtf.position.z -= moveSpeed_;
	stage_->Update();
}

void Stage::Draw()
{
	stage_->Draw();
}
