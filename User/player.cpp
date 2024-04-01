#include"player.h"

/*
* @file player.cpp
* @brind プレイヤーの動きなど
*/

void Player::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input) {
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

	//レティクル1重
	ReticleModel_ = Model::LoadFromOBJ("Ret");
	ReticleObj_ = Object3d::Create();
	ReticleObj_->SetModel(ReticleModel_);
	ReticleObj_->wtf.scale = { 5.0f,5.0f,5.0f };
	ReticleObj_->wtf.rotation = { 0.0f,0.0f,0.0f };
	ReticleObj_->wtf.position = { 0.0f,0.0f,10.0f };

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
	ReticleObj_->wtf.position = { 0.0f,0.0f,30.0f };
	
	//その他初期化
	stoptimer = 0;
	moovFlag = 0;
	ClearMove = false;
}

void Player::FadeIn()
{
	if (fbxObject3d_->wtf.position.y >= -0.2) {
		fbxObject3d_->wtf.position.y -= moveSpeed_;
	}
	
}

void Player::Start()
{
	moovFlag = 1;
}

void Player::Retry()
{
	fbxObject3d_->wtf.position = { 0.0f,-0.2f,0.0f };
	moovFlag = 1;
}

void Player::Over()
{
	fbxObject3d_->wtf.position = { 0.0f,+1.5f,0.0f };
	moovFlag = 2;
}

void Player::Clear()
{
	ClearMove = true;
	if (fbxObject3d_->wtf.position.x >= 0) {
		fbxObject3d_->wtf.position.x -= clearMoveSpeed_;
	}
	if (fbxObject3d_->wtf.position.x <= 0) {
		fbxObject3d_->wtf.position.x += clearMoveSpeed_;
	}
	if (fbxObject3d_->wtf.position.y >= 0) {
		fbxObject3d_->wtf.position.y -= clearMoveSpeed_;
	}
	if (fbxObject3d_->wtf.position.y <= 0) {
		fbxObject3d_->wtf.position.y += clearMoveSpeed_;
	}
	bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.01f, fbxObject3d_->wtf.position.z };
	ReticleObj_->wtf.position = { 0.0f,0.0f,10.0f };
}

void Player::Update() {
	
	//キーボード入力による移動処理
	// //ゲーム開始からの攻撃受付
	if (moovFlag == 0) {
		
	}
	if(ClearMove==false){


		if (moovFlag == 1) {
			//プレイヤーの移動
			/////D/////
			if (input_->PushKey(DIK_D) || input_->StickInput(L_RIGHT)) {
				if (fbxObject3d_->wtf.position.x <= xMax) {
					fbxObject3d_->wtf.position.x += moveSpeed_;
				}
			}
			//////A/////
			if (input_->PushKey(DIK_A) || input_->StickInput(L_LEFT)) {
				// 左の移動処理
				if (fbxObject3d_->wtf.position.x >= xMin) {
					fbxObject3d_->wtf.position.x -= moveSpeed_;
				}
			}
	
			/////S/////
			if (input_->PushKey(DIK_S) || input_->StickInput(L_DOWN)) {
				// 下の移動処理
				if (fbxObject3d_->wtf.position.y >= yMax) {
					fbxObject3d_->wtf.position.y -= moveSpeed_;
				}
			}

			/////W/////
			if (input_->PushKey(DIK_W) || input_->StickInput(L_UP)) {
				// 上の移動処理
				if (fbxObject3d_->wtf.position.y <= yMin) {
					fbxObject3d_->wtf.position.y += moveSpeed_;
				}
			}
		}
		if (moovFlag == 1) {
			//プレイヤーの移動
			/////D/////
			if (input_->PushKey(DIK_D) || input_->StickInput(L_RIGHT)) {
				rollD = 1;
			}
			else {
				rollD = 0;
			}
			if (rollD == 1) {
				// 右の傾き処理
				if (fbxObject3d_->wtf.rotation.z >= -1.0) {
					fbxObject3d_->wtf.rotation.z -= rotateSpeed_;
				}
			}
			else if (rollD == 0) {
				if (fbxObject3d_->wtf.rotation.z <= -0.02) {
					fbxObject3d_->wtf.rotation.z += rotateSpeed_;
				}
			}

			//////A/////
			if (input_->PushKey(DIK_A) || input_->StickInput(L_LEFT)) {
				rollA = 1;
			}
			else {
				rollA = 0;
			}
			if (rollA == 1) {
				// 左の傾き処理
				if (fbxObject3d_->wtf.rotation.z <= 1.0) {
					fbxObject3d_->wtf.rotation.z += rotateSpeed_;
				}
			}
			else if (rollA == 0) {
				if (fbxObject3d_->wtf.rotation.z >= 0.02) {
					fbxObject3d_->wtf.rotation.z -= rotateSpeed_;
				}
			}

			/////S/////
			if (input_->PushKey(DIK_S) || input_->StickInput(L_DOWN)) {
				rollS = 1;
			}
			else {
				rollS = 0;
			}
			if (rollS == 1) {
				// 下の傾き処理
				if (fbxObject3d_->wtf.rotation.x <= 0.6) {
					fbxObject3d_->wtf.rotation.x += rotateSpeed_;
				}
			}
			else if (rollS == 0) {
				if (fbxObject3d_->wtf.rotation.x >= 0.02) {
					fbxObject3d_->wtf.rotation.x -= rotateSpeed_;
				}
			}

			/////W/////
			if (input_->PushKey(DIK_W) || input_->StickInput(L_UP)) {
				rollW = 1;
			}
			else {
				rollW = 0;
			}
			if (rollW == 1) {
				// 上の傾き処理
				if (fbxObject3d_->wtf.rotation.x >= -0.1) {
					fbxObject3d_->wtf.rotation.x -= rotateSpeed_;
				}
			}
			else if (rollW == 0) {
				// 上の傾き処理
				if (fbxObject3d_->wtf.rotation.x <= -0.02) {
					fbxObject3d_->wtf.rotation.x += rotateSpeed_;
				}

			}
		}
		//レティクル
		if (input_->PushKey(DIK_D)|| input_->StickInput(L_RIGHT)) {

			if (ReticleObj_->wtf.position.x <= retXMax) {
				ReticleObj_->wtf.position.x += retSpeed;
			}
		}
		if (input_->PushKey(DIK_RIGHT) || input_->StickInput(R_RIGHT)) {
			if (ReticleObj_->wtf.position.x <= retXMax) {
				ReticleObj_->wtf.position.x += retSubSpeed;
			}
		}
		if (input_->PushKey(DIK_A)|| input_->StickInput(L_LEFT)) {
			if (ReticleObj_->wtf.position.x >= retXMin) {
				ReticleObj_->wtf.position.x -= retSpeed;
			}
		}
		if (input_->PushKey(DIK_LEFT)|| input_->StickInput(R_LEFT)) {
			if (ReticleObj_->wtf.position.x >= retXMin) {
				ReticleObj_->wtf.position.x -= retSubSpeed;
			}
		}
		if (input_->PushKey(DIK_S)|| input_->StickInput(L_DOWN)) {
			if (ReticleObj_->wtf.position.y >= retYMax) {
			ReticleObj_->wtf.position.y -= retSpeed;
			}
		}
		if (input_->PushKey(DIK_DOWN)|| input_->StickInput(R_DOWN)) {
			if (ReticleObj_->wtf.position.y >= retYMax) {
				ReticleObj_->wtf.position.y -= retSubSpeed;
			}
		}
		if (input_->PushKey(DIK_W)|| input_->StickInput(L_UP)) {
			if (ReticleObj_->wtf.position.y <= retYMin) {
			ReticleObj_->wtf.position.y += retSpeed;
			}
		}
		if (input_->PushKey(DIK_UP)|| input_->StickInput(R_UP)) {
			if (ReticleObj_->wtf.position.y <= retYMin) {
				ReticleObj_->wtf.position.y += retSubSpeed;
			}
		}
		//弾の発射
		float shortSpeed = 0.001f;
		if (moovFlag == 1) {
			if (input_->PushKey(DIK_SPACE) || input_->ButtonInput(RT)) {
				enemyDistance = ReticleObj_->wtf.position - bulletObj_->wtf.position;
				enemyDistance.nomalize();
				isShootFlag = true;
			}
			else {
				isShootFlag = false;
			}
			
			if (isShootFlag == true) {
				bulletCoolTime++;
				bulletObj_->wtf.position += enemyDistance;
				distance = enemyDistance;
				distance *= shortSpeed;
				if (bulletCoolTime >= 10.0f) {
					bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y - 0.05f , fbxObject3d_->wtf.position.z  };
					bulletCoolTime = 0;
				}
			}
			if (isShootFlag == false) {
				bulletObj_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y + 0.01f, fbxObject3d_->wtf.position.z };
			}
		}
	}
	///////////////傾き処理/////////////
	
	//FBXモデル位置固定
	fbxRoteObject3d_->wtf.position = { fbxObject3d_->wtf.position.x,fbxObject3d_->wtf.position.y , fbxObject3d_->wtf.position.z };

	fbxObject3d_->Update();
	fbxRoteObject3d_->Update();
	bulletObj_->Update();
	ReticleObj_->Update();

}

void Player::Draw() {	
	
	if (ClearMove == false) {

		if (moovFlag == 1) {
			ReticleObj_->Draw();
		}

		if (isShootFlag == true) {
			bulletObj_->Draw();
		}
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