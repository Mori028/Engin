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

	//レティクル
	ReticleModel_ = Model::LoadFromOBJ("boll");
	ReticleObj_ = Object3d::Create();
	ReticleObj_->SetModel(ReticleModel_);
	ReticleObj_->wtf.scale = { 0.3f,0.3f,0.3f };
	ReticleObj_->wtf.rotation = { 0.0f,0.0f,0.0f };
	ReticleObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y ,fbxObject3d_->wtf.position.z + 10.0f };
}

void Player::Update() {


	//キーボード入力による移動処理
	//プレイヤーの移動
	/////D/////
	if (input_->PushKey(DIK_D) || input_->StickInput(L_RIGHT)) {
		rollD = 1;
		if (fbxObject3d_->wtf.position.x <= XMax) {
			fbxObject3d_->wtf.position.x += moveSpeed_;
		}
	}
	else {
		rollD = 0;
	}
	if (rollD == 1) {
		// 右の傾き処理
		if (fbxObject3d_->wtf.rotation.z >= -1.0) {
			fbxObject3d_->wtf.rotation.z -= 0.02f;
		}
	}
	else if(rollD == 0) {
		if (fbxObject3d_->wtf.rotation.z <= -0.02) {
			fbxObject3d_->wtf.rotation.z = 0.0f;
		}
	}

	//////A/////
	if (input_->PushKey(DIK_A) || input_->StickInput(L_LEFT)) {
		rollA = 1;
		// 左の移動処理
		if (fbxObject3d_->wtf.position.x >= XMin) {
			fbxObject3d_->wtf.position.x -= moveSpeed_;
		}
	}
	else {
		rollA = 0;
	}
	if (rollA == 1) {
		// 左の傾き処理
		if (fbxObject3d_->wtf.rotation.z <= 1.0) {
			fbxObject3d_->wtf.rotation.z += 0.02f;
		}
	}
	else if (rollA == 0) {
		if (fbxObject3d_->wtf.rotation.z >= 0.02) {
			fbxObject3d_->wtf.rotation.z = 0.0f;
		}
	}

	/////S/////
	if (input_->PushKey(DIK_S) || input_->StickInput(L_DOWN)) {
		rollS = 1;
		// 下の移動処理
		if (fbxObject3d_->wtf.position.y >= YMax) {
			fbxObject3d_->wtf.position.y -= moveSpeed_;
		}
	}
	else {
		rollS = 0;
	}
	if (rollS == 1) {
		// 下の傾き処理
		if (fbxObject3d_->wtf.rotation.x <= 1) {
			fbxObject3d_->wtf.rotation.x += 0.02f;
		}
	}
	else if (rollS == 0) {
		if (fbxObject3d_->wtf.rotation.x >= 0.02) {
			fbxObject3d_->wtf.rotation.x = 0.0f;
		}
	}

	/////W/////
	if (input_->PushKey(DIK_W) || input_->StickInput(L_UP)) {
		rollW = 1;
		// 上の移動処理
		if (fbxObject3d_->wtf.position.y <= YMin) {
			fbxObject3d_->wtf.position.y += moveSpeed_;
		}
	}
	else {
		rollW = 0;
	}
	if (rollW == 1) {
		// 上の傾き処理
		if (fbxObject3d_->wtf.rotation.x >= -1) {
			fbxObject3d_->wtf.rotation.x -= 0.02f;
		}
	}
	else if (rollW == 0) {
		// 上の傾き処理
		if (fbxObject3d_->wtf.rotation.x <= -0.02) {
			fbxObject3d_->wtf.rotation.x = 0.0f;
		}
		
	}

	//レティクル
	if (input_->PushKey(DIK_RIGHT) || input_->StickInput(R_RIGHT)) {

		if (ReticleObj_->wtf.position.x <= retXMax) {
			ReticleObj_->wtf.position.x += moveSpeed_+0.1f;
		}
	}
	if (input_->PushKey(DIK_LEFT) || input_->StickInput(R_LEFT)) {
		if (ReticleObj_->wtf.position.x >= retXMin) {
			ReticleObj_->wtf.position.x -= moveSpeed_ + 0.1f;
		}
	}
	if (input_->PushKey(DIK_DOWN) || input_->StickInput(R_DOWN)) {
		/*if (ReticleObj_->wtf.position.y >= retYMax) {*/
		ReticleObj_->wtf.position.y -= moveSpeed_ + 0.1f;
		//}
	}
	if (input_->PushKey(DIK_UP) || input_->StickInput(R_UP)) {
		/*if (ReticleObj_->wtf.position.y <= retYMin) {*/
			ReticleObj_->wtf.position.y += moveSpeed_ + 0.1f;
		//}
	}
	//弾の発射
	float shortSpeed = 1.0f;

	if (input_->TriggerKey (DIK_SPACE) || input_->ButtonInput(RT)) {
		enemyDistance = ReticleObj_->wtf.position - bulletObj_->wtf.position;
		enemyDistance.nomalize();
		isShootFlag = true;
	}
	if (isShootFlag == true) {
		bulletCoolTime++;
		bulletObj_->wtf.position += enemyDistance;
		distance = enemyDistance;
		distance *= shortSpeed;
	}
	else {
		bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y , fbxObject3d_->wtf.position.z };
	}
	if (bulletCoolTime >= 10.0f) {
		bulletCoolTime = 0;
		isShootFlag = false;
	}
	
	fbxObject3d_->Update();
	bulletObj_->Update();
	ReticleObj_->Update();
}

void Player::Draw() {
	ReticleObj_->Draw();
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

Vector3 Player::GetReticleWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 RetWorldPos;

	bulletObj_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	RetWorldPos.x = ReticleObj_->wtf.matWorld.m[3][0];
	RetWorldPos.y = ReticleObj_->wtf.matWorld.m[3][1];
	RetWorldPos.z = ReticleObj_->wtf.matWorld.m[3][2];

	return RetWorldPos;
}