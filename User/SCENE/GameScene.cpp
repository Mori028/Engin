#include "GameScene.h"


/// <summary>
	/// コンストクラタ
	/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	
	delete mainCamera;
	delete camera1;
	delete camera2;
	delete camera3;
	delete player_;
	delete skydome;
	delete skydomeMD;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//タイトル
	titleSprite->Initialize(spriteCommon);
	titleSprite->SetPozition({ 0,0 });
	titleSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(1, "title.png");
	titleSprite->SetTextureIndex(1);

	////クリア
	clearSprite->Initialize(spriteCommon);
	clearSprite->SetPozition({ 0,0 });
	clearSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(2, "clear.png");
	clearSprite->SetTextureIndex(2);

	////ゲームオーバー
	overSprite->Initialize(spriteCommon);
	overSprite->SetPozition({ 0,0 });
	overSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(3, "gameover.png");
	overSprite->SetTextureIndex(3);
	//HP
	HPSprite->Initialize(spriteCommon);
	HPSprite->SetPozition({ 0,0 });
	HPSprite->SetSize({200.0f, 100.0f });
	spriteCommon->LoadTexture(4, "HP3.png");
	HPSprite->SetTextureIndex(4);
	// カメラ生成
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);

	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	//プレイヤー
	player_ = new Player();
	player_->Initialize(dxCommon,input);
	player_->SetCamera(mainCamera);

	//敵
	enemy_ = new Enemy();
	enemy_->Initialize(dxCommon, input);
	enemy_->SetPlayer(player_);

	//ボス
	boss_ = new Boss();
	boss_->Initialize(dxCommon, input);
	boss_->SetPlayer(player_);

	//ステージ
	stage_ = new Stage();
	stage_->Initialize(dxCommon, input);
	stage_->SetCamera(mainCamera);

}

void GameScene::Reset() {
	
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (sceneNo_)
	{
	case SceneNo::TITLE:
		if (sceneNo_ == SceneNo::TITLE) {
			//シーン切り替え
			if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(RT)) {
				sceneNo_ = SceneNo::GAME;
			}
		}
		break;

	case SceneNo::GAME:
		if (sceneNo_ == SceneNo::GAME) {
			skydome->wtf.position.z -= skyMoveSpeed_;

			player_->Update();

			enemy_->Update();

			stage_->Update();

			skydome->Update();

			//シーン切り替え
			if (enemy_->GetEnemyHP() == 10)
			{
				sceneNo_ = SceneNo::BOSS;
			}

			//シーン切り替え
			if (enemy_->GetPlayerHP() ==0)
			{
				sceneNo_ = SceneNo::GAMEOVER;
				enemy_->playerHp = 15;

			}
		}
		break;
	case SceneNo::BOSS:

		player_->Update();

		skydome->Update();

		boss_->Update();
		break;

	case SceneNo::CLEAR:
		if (sceneNo_ == SceneNo::CLEAR) {
			//シーン切り替え
			if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(RT)) {
				sceneNo_ = SceneNo::TITLE;
			}
		}
		break;

	case SceneNo::GAMEOVER:
		if (sceneNo_ == SceneNo::GAMEOVER) {
			//シーン切り替え
			if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(RT)) {
				sceneNo_ = SceneNo::TITLE;
			}
		}
		break;
	}
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {
	switch (sceneNo_)
	{
	case SceneNo::TITLE:
		//タイトル
		if (sceneNo_ == SceneNo::TITLE) {
			titleSprite->Draw();
			/*HPSprite->Draw();*/

		}
		break;
	case SceneNo::GAME:
		if (sceneNo_ == SceneNo::GAME) {
			
			/// <summary>
			/// 3Dオブジェクトの描画
			/// ここに3Dオブジェクトの描画処理を追加できる
			/// <summary>
			//3Dオブジェクト描画前処理
			Object3d::PreDraw(dxCommon->GetCommandList());
			//// 3Dオブクジェクトの描画
			player_->Draw();
			enemy_->Draw();
			skydome->Draw();

			stage_->Draw();
			boss_->Draw();

			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();

			enemy_->FbxDraw();
			HPSprite->Draw();
		}
		break;

	case SceneNo::BOSS:
		//クリア
		if (sceneNo_ == SceneNo::BOSS) {
			HPSprite->Draw();
			/// <summary>
			/// 3Dオブジェクトの描画
			/// ここに3Dオブジェクトの描画処理を追加できる
			/// <summary>
			//3Dオブジェクト描画前処理
			Object3d::PreDraw(dxCommon->GetCommandList());
			//// 3Dオブクジェクトの描画
			player_->Draw();
			skydome->Draw();
			boss_->Draw();
			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();
			boss_->FbxDraw();
	
		}
		break;

	case SceneNo::CLEAR:
		//クリア
		if (sceneNo_ == SceneNo::CLEAR) {
			clearSprite->Draw();
		}
		break;

	case SceneNo::GAMEOVER:
		//ゲームオーバー
		if (sceneNo_ == SceneNo::GAMEOVER) {
			overSprite->Draw();
		}
		break;
	}

}

Vector3 GameScene::bVelocity(Vector3& velocity, Transform& worldTransform)
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