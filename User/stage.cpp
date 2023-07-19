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
	stage_->SetModel(felld);

}

void Stage::Update()
{
}

void Stage::Draw()
{
}
