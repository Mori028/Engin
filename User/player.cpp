#include"player.h"

Player::Player() {

}

Player::~Player() {
	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;
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
	fbxObject3d_->PlayAnimation();
	


	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();

	particleHealManager = std::make_unique<ParticleManager>();
	particleHealManager.get()->Initialize();
	particleHealManager->LoadTexture("hill.png");
	particleHealManager->Update();

	particleHiHealManager = std::make_unique<ParticleManager>();
	particleHiHealManager.get()->Initialize();
	particleHiHealManager->LoadTexture("hihill.png");
	particleHiHealManager->Update();


	audio = new Audio();

	audio->Initialize();
	audio->LoadWave("col.wav");
	audio->LoadWave("kaihi.wav");
	audio->LoadWave("heal.wav");

	sensitivity = 10;


	Reset();
}

void Player::Reset() {
	camTransForm->Initialize();
	eyePos = { 0.0f, 3.0f, -8.0f };
	targetPos = { 0.0f,0.0f,targetDistance };
	
	fbxObject3d_->Initialize();

}

void Player::Attack() {
	
}

void Player::OnCollision() {
	
}

void Player::Move() {
	
}

void Player::Rota() {
	
}

void Player::camUpdate() {
	camTransForm->position = fbxObject3d_->wtf.position;
	
}

void Player::Update() {
	
}

void Player::Draw() {
}

void Player::FbxDraw(){				
	//待機
	fbxObject3d_->Draw(dxCommon->GetCommandList());

}

//ダメージエフェクト
void Player::EffUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos += GetWorldPosition();
		pos.y += 1.5f;
		//速度
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		particleManager->Add(60, pos, vel, acc, 1.0f, 0.0f);

		particleManager->Update();
	}

}

//回復エフェクト
void Player::EffHealUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 2; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos += GetWorldPosition();
		pos.y += 1.0f;
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.000001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		particleHealManager->Add(60, pos, vel, acc, 0.3f, 0.0f);

		particleHealManager->Update();
	}

}

void Player::EffHiHealUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 2; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 5.0f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 3.0f;
		pos += GetWorldPosition();
		pos.y += 1.0f;
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 2.0f;

		//追加
		particleHiHealManager->Add(60, pos, vel, acc, 0.3f, 0.0f);

		particleHiHealManager->Update();
	}

}

void Player::EffDraw()
{
	//ダメージエフェクト
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		particleManager->Draw();
	}

	//回復エフェクト
	if (isEffHealFlag == 1) {
		// 3Dオブクジェクトの描画
		particleHealManager->Draw();
	}

	//回復エフェクト(大)
	if (isEffHiHealFlag == 1) {
		// 3Dオブクジェクトの描画
		particleHiHealManager->Draw();
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
	fbxObject3d_->wtf.UpdateMat();
	//ワールド行列の平行移動成分
	worldPos.x = fbxObject3d_->wtf.matWorld.m[3][0];
	worldPos.y = fbxObject3d_->wtf.matWorld.m[3][1];
	worldPos.z = fbxObject3d_->wtf.matWorld.m[3][2];

	return worldPos;
}


Vector3 Player::GetMoveBack() {
	Vector3 result = moveBack;
	moveBack = { 0,0,0 };
	return result;
}