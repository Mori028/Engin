#include"fade.h"

/*
* @file Fade.cpp
* @brind �G�̓o��Ȃ�
*/

void Fade::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input) {
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
	fbxObject3d_->wtf.position = { 0.0f,1.0f,3.0f };
	fbxObject3d_->wtf.scale = { 1.0f,1.0f,1.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f, true);


	
}

void Fade::Reset()
{
	//�{�X
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.position = { 0.0f,1.0f,+3.0f };
	fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };
	fbxObject3d_->wtf.scale = { 1.2f,1.2f,1.2f };
	
}

void Fade::Update() {
	
		
	if (fbxObject3d_->wtf.position.y >= -0.3) {
		fbxObject3d_->wtf.position.y -= moveSpeed_;
	}
	else {
		fbxObject3d_->wtf.position.z += fadeSpeed_;
	}	
		
	fbxObject3d_->Update();
	
}

void Fade::FbxDraw() {

	fbxObject3d_->Draw(dxCommon->GetCommandList());
	
}
