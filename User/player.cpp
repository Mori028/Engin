#include"player.h"

Player::Player() {

}

Player::~Player() {

	//FBXオブジェクト解放

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

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("playerNeutral"); 
	fbxRoteModel_ = FbxLoader::GetInstance()->LoadModelFromFile("player");
	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();

	//通常時
	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->wtf.position = { 0.0f,-0.1f,0.0f };
	fbxObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	/*fbxObject3d_->wtf.rotation = { 0.0f,-1.7f,0.0f };*/
	fbxObject3d_->PlayAnimation(4.0f, true);

	//回転
	fbxRoteObject3d_ = new FBXObject3d;
	fbxRoteObject3d_->Initialize();
	fbxRoteObject3d_->SetModel(fbxRoteModel_);
	fbxRoteObject3d_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y, fbxObject3d_->wtf.position.z };
	fbxRoteObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	fbxRoteObject3d_->PlayAnimation(4.0f, true);

	//弾
	bulletModel_ = Model::LoadFromOBJ("boll");
	bulletObj_ = Object3d::Create();
	bulletObj_->SetModel(bulletModel_);
	bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.01f, fbxObject3d_->wtf.position.z };
	bulletObj_->wtf.scale = { 0.3f,0.3f,0.3f };

	//レティクル
	ReticleModel_ = Model::LoadFromOBJ("C");
	ReticleObj_ = Object3d::Create();
	ReticleObj_->SetModel(ReticleModel_);
	ReticleObj_->wtf.scale = { 1.0f,1.0f,1.0f };
	ReticleObj_->wtf.rotation = { 0.0f,0.0f,0.0f };
	ReticleObj_->wtf.position = { 0.0f,0.0f,10.0f };

	////レティクル
	//RetSprite->Initialize(spriteCommon);
	//RetSprite->SetPozition({ 0,0 });
	//RetSprite->SetSize({ 50.0f, 50.0f });
	//spriteCommon->LoadTexture(8, "ret.png");
	//RetSprite->SetTextureIndex(8);

	Reset();
}

void Player::Reset()
{
	//プレイヤー
	fbxObject3d_->Initialize();
	fbxObject3d_->wtf.position = { 0.0f,+1.5f,0.0f };
	fbxObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	//プレイヤー回転
	fbxRoteObject3d_->Initialize();
	fbxRoteObject3d_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y, fbxObject3d_->wtf.position.z };
	fbxRoteObject3d_->wtf.scale = { 0.03f,0.03f,0.03f };
	//弾
	bulletObj_->Initialize();
	bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.01f, fbxObject3d_->wtf.position.z };
	//レティクル
	ReticleObj_->Initialize();
	ReticleObj_->wtf.position = { 0.0f,0.0f,10.0f };
	//その他初期化
	stoptimer = 0;
	moovFlag = 0;
}

void Player::FadeIn()
{
	if (fbxObject3d_->wtf.position.y >= 0) {
		fbxObject3d_->wtf.position.y -= moveSpeed_;
	}
	
}

void Player::Update() {
	
	//キーボード入力による移動処理
	// //ゲーム開始からの攻撃受付
	if (moovFlag ==0) {
		stoptimer++;
	}
	if (stoptimer >= 250) {
		moovFlag = 1;
	}
	if (moovFlag == 1) {
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
		else if (rollD == 0) {
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
				ReticleObj_->wtf.position.x += moveSpeed_ + 0.1f;
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
		if (moovFlag == 1) {
			if (input_->TriggerKey(DIK_SPACE) || input_->ButtonInput(RT)) {
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
		}
	}
	//FBXモデル位置固定
	fbxRoteObject3d_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y , fbxObject3d_->wtf.position.z };

	fbxObject3d_->Update();
	fbxRoteObject3d_->Update();
	bulletObj_->Update();
	ReticleObj_->Update();
}

void Player::Draw() {
	ReticleObj_->Draw();
	/*RetSprite->Draw();*/
	if (isShootFlag == true) {
		bulletObj_->Draw();
	}
}

void Player::FbxDraw(){
	if (moovFlag == 0) {
		fbxRoteObject3d_->Draw(dxCommon->GetCommandList());
	}else{
	fbxObject3d_->Draw(dxCommon->GetCommandList());
	}
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