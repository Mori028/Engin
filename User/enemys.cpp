#include "enemys.h"
#include <imgui.h>


void Enemys::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	//モデル
	EnemysModel_ = FbxLoader::GetInstance()->LoadModelFromFile("kuma");

	//敵の待機
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
	//敵の行動
	/*EnemysObject3d_->wtf.position.x -= moveSpeed_;*/
	
	// 時間経過でデス
	//if (--dethTimer_ <= 0) {
	//	isDead_ = true;
	//}

	//// HP0でデス
	//if (dethHp_ <= 0) {
	//	isDead_ = true;
	//}

	// 敵の更新
	EnemysObject3d_->Update();
}

void Enemys::Draw()
{
	// 敵の描画
	//EnemysObj_->Draw();
}

void Enemys::FbxDraw()
{
	// 敵の描画
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
	//ワールド行列の平行移動成分
	worldPos.x = EnemysObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = EnemysObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = EnemysObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}