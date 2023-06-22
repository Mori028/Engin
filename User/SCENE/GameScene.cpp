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
	delete spriteCommon;
	delete mainCamera;
	delete camera1;
	delete camera2;
	delete camera3;
	delete player_;
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

	// カメラ生成
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);

	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	floorMD = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorMD);
	floor->wtf.position = (Vector3{ 0, -10, 0 });

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	fieldMD = Model::LoadFromOBJ("field");
	field = Object3d::Create();
	field->SetModel(fieldMD);
	field->wtf.scale = (Vector3{ 2, 2, 2 });

	//プレイヤー
	player_ = new Player();
	player_->Initialize(dxCommon,input);
	player_->SetCamera(mainCamera);

	//タイトル
	Title = new Sprite();
	Title->Initialize(spriteCommon);
	Title->SetPozition({ 0,0 });
	Title->SetSize({ 1280.0f, 720.0f });

	//セレクト
	Select = new Sprite();
	Select->Initialize(spriteCommon);
	Select->SetPozition({ 0,0 });
	Select->SetSize({ 1280.0f, 720.0f });

	//クリア
	Clear = new Sprite();
	Clear->Initialize(spriteCommon);
	Clear->SetPozition({ 0,0 });
	Clear->SetSize({ 1280.0f, 720.0f });

	//ゲームオーバー
	GameOver = new Sprite();
	GameOver->Initialize(spriteCommon);
	GameOver->SetPozition({ 0,0 });
	GameOver->SetSize({ 1280.0f, 720.0f });

	//ゲームフロー
	scene = Scene::Title;
	stage = 0;

	spriteCommon->LoadTexture(0, "Title.png");
	Title->SetTextureIndex(0);

	spriteCommon->LoadTexture(1, "Select.png");
	Select->SetTextureIndex(1);

	spriteCommon->LoadTexture(2, "Clear.png");
	Clear->SetTextureIndex(2);

	spriteCommon->LoadTexture(3, "GameOver.png");
	GameOver->SetTextureIndex(3);
	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("tit.wav");
	audio->LoadWave("bb.wav");
	audio->LoadWave("serect.wav");
	audio->LoadWave("open.wav");
	audio->LoadWave("clear.wav");
	audio->LoadWave("over.wav");

	Reset();
}

void GameScene::Reset() {
	player_->Reset();

	camera1->SetEye({ 0, 1, 6 });
	camera1->SetTarget({ 0,3,0 });
	camera2->SetEye({ -4, 4, 4 });
	camera2->SetTarget({ 0,3,0 });
	camera3->SetEye({ 4, 4, 4 });
	camera3->SetTarget({ 0,3,0 });

	player_->EffTimer = 0;
	player_->isEffFlag = 0;

	player_->EffHealTimer = 0;
	player_->isEffHealFlag = 0;

}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (scene)
	{
	case Scene::Title:
		soundCheckFlag3 = 0;
		soundCheckFlag4 = 0;
		

		//シーン切り替え
		if (input->PButtonTrigger(B) || input->TriggerKey(DIK_SPACE)) {
			/*selectMode = 0;*/
			scene = Scene::Select;
			pSourceVoice[3] = audio->PlayWave("open.wav");
			pSourceVoice[3]->SetVolume(0.4f);
		}

		//音声再生
		if (soundCheckFlag == 0) {
			//音声再生

			pSourceVoice[0] = audio->PlayWave("tit.wav");
			pSourceVoice[0]->SetVolume(0.1f);
			soundCheckFlag = 1;
		}


		
	case Scene::Select:

		//0:ゲームプレイ、1:操作説明
		
		if (input->PushKey(DIK_SPACE)) {
			pSourceVoice[2] = audio->PlayWave("serect.wav");
			pSourceVoice[2]->SetVolume(0.6f);

		}
		

		if (input->PushKey(DIK_RETURN)) {
			//ゲームプレイ
			Reset();
			pSourceVoice[4] = audio->PlayWave("open.wav");
			pSourceVoice[4]->SetVolume(0.4f);
			scene = Scene::Play;

		}

		break;
	case Scene::Play:
		
			//ゲーム画面
			camera1->Update();
			camera2->Update();
			camera3->Update();

			pSourceVoice[0]->Stop();
			soundCheckFlag = 0;
			//音声再生
			if (soundCheckFlag2 == 0) {
				//音声再生
				pSourceVoice[1] = audio->PlayWave("bb.wav");
				pSourceVoice[1]->SetVolume(0.1f);
				soundCheckFlag2 = 1;
			}


			floor->Update();
			skydome->Update();
			field->Update();

			//シーン切り替え
			/*if (player_->GetHp() < 0) {
				scene = Scene::Gameover;
			}*/
		
		break;
	case Scene::Clear:
		pSourceVoice[1]->Stop();
		soundCheckFlag2 = 0;
		
		//音声再生
		if (soundCheckFlag3 == 0) {
			//音声再生

			pSourceVoice[5] = audio->PlayWave("clear.wav");
			pSourceVoice[5]->SetVolume(0.3f);
			soundCheckFlag3 = 1;
		}
		
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
			pSourceVoice[2] = audio->PlayWave("serect.wav");
			pSourceVoice[2]->SetVolume(0.6f);
		}
		break;
	case Scene::Gameover:
		pSourceVoice[1]->Stop();
		soundCheckFlag2 = 0;
		//音声再生
		if (soundCheckFlag4 == 0) {
			//音声再生
			pSourceVoice[6] = audio->PlayWave("over.wav");
			pSourceVoice[6]->SetVolume(0.3f);
			soundCheckFlag4 = 1;
		}
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
			pSourceVoice[2] = audio->PlayWave("serect.wav");
			pSourceVoice[2]->SetVolume(0.6f);
		}
		break;
	}

}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	/// <summary>
	/// 3Dオブジェクトの描画
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	//// 3Dオブクジェクトの描画
	switch (scene)
	{
	case Scene::Title:
		Title->Draw();
		break;
	case Scene::Select:
		Select->Draw();
		break;
	case Scene::Play:
		player_->Draw();
		
    
		floor->Draw();
		skydome->Draw();
		break;
	case Scene::Clear:
		Clear->Draw();

		break;
	case Scene::Gameover:
		GameOver->Draw();

		break;
	}
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//// パーティクル UI FBX スプライト描画
	switch (scene)
	{
	case Scene::Title:

		break;
	case Scene::Select:
		
		break;
	case Scene::Play:
		
		player_->FbxDraw();

		// パーティクル描画前処理
	/*	ParticleManager::PreDraw(dxCommon->GetCommandList());*/
		player_->EffDraw();
		//// パーティクル描画後処理
		//ParticleManager::PostDraw();
		
	//	UI->Draw();
	//	if (isPause == false) {
	//		if (input->ButtonInput(X)) {
	//			buttomx->Draw();
	//		}

	//		if (input->ButtonInput(Y)) {
	//			buttomy->Draw();
	//		}
	//		if (input->ButtonInput(B)) {
	//			buttomb->Draw();
	//		}
	//	}
	//	if (input->ButtonInput(LT)) {
	//		buttomPng2->Draw();
	//	}
	//	else {
	//		buttomPng1->Draw();
	//	}

	//	
	//	


	//	hpGauge->Draw();
	//	mpGauge->Draw();

	//	srr->Draw();
	//	srl->Draw();

	//	//カウントダウン
	//	if (actionStopTimer > 60 * 2) {
	//		std3->Draw();
	//	}else if (actionStopTimer > 60 * 1) {
	//		std2->Draw();
	//	}else if (actionStopTimer > 0) {
	//		std1->Draw();
	//	}else if (actionStopTimer > -20) {
	//		stdgo->Draw();
	//	}else if (actionStopTimer > -35) {
	//		stdgo2->Draw();
	//	}

	//	break;
	//case Scene::Clear:
	//	clearPic->Draw();

	//	break;
	//case Scene::Gameover:
	//	gameoverPic->Draw();

	//	break;
	//case Scene::Option:
	//	optionPic->Draw();
	//	mouse->Draw();

	//	break;
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