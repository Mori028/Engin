#include "effectManager.h"
#include "player.h"

EffectManager::EffectManager()
{
}

void EffectManager::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	input_ = input;

	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();
}

void EffectManager::Update()
{
	//ダメージエフェクト
	if (isEffFlag == 1) {
		effTimer++;
	}
	if (effTimer <= 10 && effTimer >= 1) {
		EffUpdate();
	}
	if (effTimer >= 11) {
		isEffFlag = 0;
		effTimer = 0;
	}

	particleManager->Update();
}

void EffectManager::EffUpdate()
{
	//パーティクル範囲
	for (int i = 0; i < 20; i++) {
		//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 0.01f;
		Vector3 pos{};
		pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 0.1f;
		pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 0.1f;
		pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		pos += player_->GetWorldPosition();

		//速度
		//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
		const float rnd_vel = 0.1f;
		Vector3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.5f;
		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
		const float rnd_acc = 0.00001f;
		Vector3 acc{};
		acc.x = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 0.5f;
		acc.y = (float)rand() / RAND_MAX * rnd_acc - rnd_acc / 0.5f;

		//追加
		particleManager->Add(20, pos, vel, acc, 1.0f, 0.0f);

		particleManager->Update();
	}
}

void EffectManager::EffDraw()
{
	
	//ダメージエフェクト
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		particleManager->Draw();
	}
	
}
