#include "title.h"

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();
	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.0f,0.0f };
	fbxObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	/*fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };*/
	fbxObject3d_->PlayAnimation(4.0f, true);

	playerModel_ = Model::LoadFromOBJ("player");
	playerObj_ = Object3d::Create();
	playerObj_->SetModel(playerModel_);
	playerObj_->wtf.position = { 0.0f,-0.0f,0.0f };
	playerObj_->wtf.scale = { 0.03f,0.03f,0.03f };

	Reset();
}

void Title::Reset()
{
	//タイトルの回転するプレイヤー
	fbxObject3d_->wtf.position = { 0.0f,-0.1f,0.0f };
}

void Title::FadeOut()
{
	fbxObject3d_->wtf.position.z += moveSpeed_;
	if (fbxObject3d_->wtf.position.z >= 0.5) {
		fbxObject3d_->wtf.position.x += movexSpeed_;
		fbxObject3d_->wtf.position.y += moveSpeed_;
	}
}

void Title::Update()
{
	
	fbxObject3d_->Update();
}

void Title::Draw()
{
	
}

void Title::FbxDraw()
{
	fbxObject3d_->Draw(dxCommon->GetCommandList());
}
