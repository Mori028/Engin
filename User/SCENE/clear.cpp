#include "clear.h"

/*
* @file Clear.cpp
* @brind �N���A�̉��o�Ȃ�
*/
Clear::Clear()
{
}

Clear::~Clear()
{
}

void Clear::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();

	//�ҋ@
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,0.0f,0.0f };
	fbxObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	/*fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };*/
	fbxObject3d_->PlayAnimation(4.0f, true);

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	Reset();
}

void Clear::Reset()
{
	//�N���A�̉�]����v���C���[
	fbxObject3d_->wtf.position = { 0.0f,-0.1f,0.0f };
}

void Clear::FadeOut()
{
}

void Clear::Update()
{
	fbxObject3d_->wtf.position.z += moveSpeed_;
	if (fbxObject3d_->wtf.position.z >= 0.5) {
		fbxObject3d_->wtf.position.x += movexSpeed_;
		fbxObject3d_->wtf.position.y += moveSpeed_;
	}

	skydome->Update();
	fbxObject3d_->Update();
}

void Clear::Draw()
{
	/*skydome->Draw();*/
}

void Clear::FbxDraw()
{
	fbxObject3d_->Draw(dxCommon->GetCommandList());
}
