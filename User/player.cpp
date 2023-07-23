#include"player.h"

Player::Player() {

}

Player::~Player() {

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;

	delete bulletModel_;
	delete bulletObj_;
}

void Player::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;
	camTransForm = new Transform();

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("stand");
	
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//待機
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.3f,0.0f };
	fbxObject3d_->wtf.scale = { 0.04f,0.04f,0.04f };
	fbxObject3d_->wtf.rotation = { 0.0f,0.0f,0.0f };
	fbxObject3d_->PlayAnimation(1.0f,true);

	//弾
	bulletModel_ = Model::LoadFromOBJ("boll");
	bulletObj_ = Object3d::Create();
	bulletObj_->SetModel(bulletModel_);
	bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.01f, fbxObject3d_->wtf.position.z };
	bulletObj_->wtf.scale = { 0.03f,0.03f,0.03f };
}

void Player::Update() {


	//キーボード入力による移動処理
	//プレイヤーの移動
	if (input_->PushKey(DIK_D)) {

		if (fbxObject3d_->wtf.position.x <= XMax) {
			fbxObject3d_->wtf.position.x += moveSpeed_;
		}
	}
	if (input_->PushKey(DIK_A)) {
		if (fbxObject3d_->wtf.position.x >= XMin) {
			fbxObject3d_->wtf.position.x -= moveSpeed_;
		}
	}
	if (input_->PushKey(DIK_S)) {
		if (fbxObject3d_->wtf.position.y >= YMax) {
			fbxObject3d_->wtf.position.y -= moveSpeed_;
		}
	}
	if (input_->PushKey(DIK_W)) {
		if (fbxObject3d_->wtf.position.y <= YMin) {
			fbxObject3d_->wtf.position.y += moveSpeed_;
		}
	}
	 
	//弾の発射
	float ShortSpeed = 0.05f;

	if (input_->TriggerKey (DIK_SPACE)) {
		isShootFlag = true;
	}
	if (isShootFlag == true) {
		bulletObj_->wtf.position.z += ShortSpeed;

	}
	else {
		bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y , fbxObject3d_->wtf.position.z };
	}
	if (bulletObj_->wtf.position.z >= 3.0f) {
		isShootFlag = false;
	}
	
	fbxObject3d_->Update();
	bulletObj_->Update();

}

void Player::Draw() {
	if (isShootFlag == true) {
		bulletObj_->Draw();
	}
}

void Player::FbxDraw(){
	
	fbxObject3d_->Draw(dxCommon->GetCommandList());
	
}

Vector3 Player::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}

Vector3 Player::GetWorldPosition(){
	//ワールド座標を入れる変数
	Vector3 worldPos;

	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}

Vector3 Player::GetBulletWorldPosition()
{
	Vector3 BulletWorldPos;

	bulletObj_->wtf.UpdateMat();

	//ワールド行列の平行移動成分
	BulletWorldPos.x = bulletObj_->wtf.matWorld.m[3][0];
	BulletWorldPos.y = bulletObj_->wtf.matWorld.m[3][1];
	BulletWorldPos.z = bulletObj_->wtf.matWorld.m[3][2];

	return BulletWorldPos;
}

