#include "stage.h"


/*
* @file stage.cpp
* @brind ステージ配置など
*/
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

	felld = Model::LoadFromOBJ("stage2");
	stage_ = Object3d::Create();
	stage_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage_->SetModel(felld);

	stage2_ = Object3d::Create();
	stage2_->wtf.position = { -0.3f,-1.0f,50.0f };
	stage2_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage2_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage2_->SetModel(felld);

	stage3_ = Object3d::Create();
	stage3_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage3_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage3_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage3_->SetModel(felld);

	stage4_ = Object3d::Create();
	stage4_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage4_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage4_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage4_->SetModel(felld);

	stage5_ = Object3d::Create();
	stage5_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage5_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage5_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage5_->SetModel(felld);

	stage6_ = Object3d::Create();
	stage6_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage6_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage6_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage6_->SetModel(felld);

	stage7_ = Object3d::Create();
	stage7_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage7_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage7_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage7_->SetModel(felld);

	stage8_ = Object3d::Create();
	stage8_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage8_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage8_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage8_->SetModel(felld);

	stage9_ = Object3d::Create();
	stage9_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage9_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage9_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage9_->SetModel(felld);

	stage10_ = Object3d::Create();
	stage10_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage10_->wtf.rotation = { 0.0f,-1.5f,0.0f };
	stage10_->wtf.scale = { 1.0f,4.0f,5.0f };
	stage10_->SetModel(felld);
}

void Stage::Reset()
{
	//ステージの位置初期化
	stage_->Initialize();
	stage_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage2_->Initialize();
	stage2_->wtf.position = { -0.3f,-1.0f,50.0f };
	stage2_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage3_->Initialize();
	stage3_->wtf.position = { -0.3f,-1.0f,100.0f };
	stage3_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage4_->Initialize();
	stage4_->wtf.position = { -0.3f,-1.0f,150.0f };
	stage4_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage5_->Initialize();
	stage5_->wtf.position = { -0.3f,-1.0f,200.0f };
	stage5_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage6_->Initialize();
	stage6_->wtf.position = { -0.3f,-1.0f,250.0f };
	stage6_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage7_->Initialize();
	stage7_->wtf.position = { -0.3f,-1.0f,300.0f };
	stage7_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage8_->Initialize();
	stage8_->wtf.position = { -0.3f,-1.0f,350.0f };
	stage8_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage9_->Initialize();
	stage9_->wtf.position = { -0.3f,-1.0f,400.0f };
	stage9_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage10_->Initialize();
	stage10_->wtf.position = { -0.3f,-1.0f,450.0f };
	stage10_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	moveFlag = 1;
}

void Stage::Loop()
{
	//ステージの位置をループさせる
	stage_->Initialize();
	stage_->wtf.position = { -0.3f,-1.0f,-50.0f };
	stage_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage2_->Initialize();
	stage2_->wtf.position = { -0.3f,-1.0f,0.0f };
	stage2_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage3_->Initialize();
	stage3_->wtf.position = { -0.3f,-1.0f,50.0f };
	stage3_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage4_->Initialize();
	stage4_->wtf.position = { -0.3f,-1.0f,100.0f };
	stage4_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage5_->Initialize();
	stage5_->wtf.position = { -0.3f,-1.0f,150.0f };
	stage5_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage6_->Initialize();
	stage6_->wtf.position = { -0.3f,-1.0f,200.0f };
	stage6_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage7_->Initialize();
	stage7_->wtf.position = { -0.3f,-1.0f,250.0f };
	stage7_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage8_->Initialize();
	stage8_->wtf.position = { -0.3f,-1.0f,300.0f };
	stage8_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage9_->Initialize();
	stage9_->wtf.position = { -0.3f,-1.0f,350.0f };
	stage9_->wtf.rotation = { 0.0f,-1.5f,0.0f };

	stage10_->Initialize();
	stage10_->wtf.position = { -0.3f,-1.0f,400.0f };
	stage10_->wtf.rotation = { 0.0f,-1.5f,0.0f };

}

void Stage::Over()
{
	moveFlag = 0;
}

void Stage::Update()
{
	//ステージ3でループさせる
	if (stage3_->wtf.position.z <= 0) {
		Loop();
	}
	if (moveFlag == 1) {
		stage_->wtf.position.z -= moveSpeed_;
		stage2_->wtf.position.z -= moveSpeed_;
		stage3_->wtf.position.z -= moveSpeed_;
		stage4_->wtf.position.z -= moveSpeed_;
		stage5_->wtf.position.z -= moveSpeed_;
		stage6_->wtf.position.z -= moveSpeed_;
		stage7_->wtf.position.z -= moveSpeed_;
		stage8_->wtf.position.z -= moveSpeed_;
		stage9_->wtf.position.z -= moveSpeed_;
		stage10_->wtf.position.z -= moveSpeed_;
	}
	stage_->Update();
	stage2_->Update();
	stage3_->Update();
	stage4_->Update();
	stage5_->Update();
	stage6_->Update();
	stage7_->Update();
	stage8_->Update();
	stage9_->Update();
	stage10_->Update();
}

void Stage::Draw()
{
	stage_->Draw();
	stage2_->Draw();
	stage3_->Draw();
	stage4_->Draw();
	stage5_->Draw();
	stage6_->Draw();
	stage7_->Draw();
	stage8_->Draw();
	stage9_->Draw();
	stage10_->Draw();
}
