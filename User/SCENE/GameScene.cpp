#include "GameScene.h"

/*
* @file GameScene.cpp
* @brind ゲームの本体
*/
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
	spriteCommon->LoadTexture(1, "Titlee.png");
	titleSprite->SetTextureIndex(1);
	//タイトル(スペース表示)
	spaceSprite->Initialize(spriteCommon);
	spaceSprite->SetPozition({ 0,0 });
	spaceSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(9, "SPACE.png");
	spaceSprite->SetTextureIndex(9);
	////クリア
	clearSprite->Initialize(spriteCommon);
	clearSprite->SetPozition({ 0,0 });
	clearSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(2, "clear.png");
	clearSprite->SetTextureIndex(2);
	//クリア
	conSprite->Initialize(spriteCommon);
	conSprite->SetPozition({ 0,0 });
	conSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(22, "clearcon.png");
	conSprite->SetTextureIndex(22);
	//クリア(戻る)
	backSprite->Initialize(spriteCommon);
	backSprite->SetPozition({ 0,0 });
	backSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(23, "backT.png");
	backSprite->SetTextureIndex(23);
	
	//リトライ
	overSprite->Initialize(spriteCommon);
	overSprite->SetPozition({ 0,0 });
	overSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(19, "yes.png");
	overSprite->SetTextureIndex(19);
	//ゲームオーバー(背景)
	blackSprite->Initialize(spriteCommon);
	blackSprite->SetPozition({ 0,0 });
	blackSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(21, "Black.png");
	blackSprite->SetTextureIndex(21);
	//ゲームオーバー(選択画面)
	over2Sprite->Initialize(spriteCommon);
	over2Sprite->SetPozition({ 0,0 });
	over2Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(3, "no.png");
	over2Sprite->SetTextureIndex(3);
	//ゲームオーバー
	over3Sprite->Initialize(spriteCommon);
	over3Sprite->SetPozition({ 0,0 });
	over3Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(20, "over.png");
	over3Sprite->SetTextureIndex(20);
	//HP3
	hPSprite->Initialize(spriteCommon);
	hPSprite->SetPozition({ 0,0 });
	hPSprite->SetSize({200.0f, 100.0f });
	spriteCommon->LoadTexture(4, "HP3.png");
	hPSprite->SetTextureIndex(4);
	//HP2
	hP2Sprite->Initialize(spriteCommon);
	hP2Sprite->SetPozition({ 0,0 });
	hP2Sprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(5, "HP2.png");
	hP2Sprite->SetTextureIndex(5);
	//HP1
	hP1Sprite->Initialize(spriteCommon);
	hP1Sprite->SetPozition({ 0,0 });
	hP1Sprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(6, "HP1.png");
	hP1Sprite->SetTextureIndex(6);
	//HP0
	hP0Sprite->Initialize(spriteCommon);
	hP0Sprite->SetPozition({ 0,0 });
	hP0Sprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(7, "HP0.png");
	hP0Sprite->SetTextureIndex(7);
	//フェードイン0
	outSprite->Initialize(spriteCommon);
	outSprite->SetPozition({ 0,0 });
	outSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(10, "out.png");
	outSprite->SetTextureIndex(10);
	//フェードイン1
	out1Sprite->Initialize(spriteCommon);
	out1Sprite->SetPozition({ 0,0 });
	out1Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(11, "out1.png");
	out1Sprite->SetTextureIndex(11);
	//フェードイン2
	out2Sprite->Initialize(spriteCommon);
	out2Sprite->SetPozition({ 0,0 });
	out2Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(12, "out2.png");
	out2Sprite->SetTextureIndex(12);
	//フェードイン3
	out3Sprite->Initialize(spriteCommon);
	out3Sprite->SetPozition({ 0,0 });
	out3Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(13, "out3.png");
	out3Sprite->SetTextureIndex(13);
	//フェードイン4
	out4Sprite->Initialize(spriteCommon);
	out4Sprite->SetPozition({ 0,0 });
	out4Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(14, "out4.png");
	out4Sprite->SetTextureIndex(14);
	//フェードイン5
	out5Sprite->Initialize(spriteCommon);
	out5Sprite->SetPozition({ 0,0 });
	out5Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(15, "out5.png");
	out5Sprite->SetTextureIndex(15);
	//スタートカウント
	start3Sprite->Initialize(spriteCommon);
	start3Sprite->SetPozition({ 0,0 });
	start3Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(16, "3.png");
	start3Sprite->SetTextureIndex(16);
	//スタートの文字
	goSprite->Initialize(spriteCommon);
	goSprite->SetPozition({ 0,0 });
	goSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(17, "G.png");
	goSprite->SetTextureIndex(17);
	//スタートの文字
	go2Sprite->Initialize(spriteCommon);
	go2Sprite->SetPozition({ 0,0 });
	go2Sprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(18, "O.png");
	go2Sprite->SetTextureIndex(18);

	// カメラ生成
	mainCamera = new Camera(WinApp::window_width, WinApp::window_height);
	camera1 = new Camera(WinApp::window_width, WinApp::window_height);
	camera2 = new Camera(WinApp::window_width, WinApp::window_height);
	camera3 = new Camera(WinApp::window_width, WinApp::window_height);
	//カメラ
	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	//スカイドーム
	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	//タイトル
	title_ = new Title();
	title_->Initialize(dxCommon, input);
	title_->SetCamera(mainCamera);

	//クリア
	clear_ = new Clear();
	clear_->Initialize(dxCommon, input);
	clear_->SetCamera(mainCamera);

	//プレイヤー
	player_ = new Player();
	player_->Initialize(dxCommon,input);
	player_->SetCamera(mainCamera);

	//プレイヤーの弾
	Bullet_ = new Bullet();
	Bullet_->Initialize(dxCommon, input);
	Bullet_->SetPlayer(player_);
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
	//クラスごとのリセット
	title_->Reset();
	clear_->Reset();
	player_->Reset();
	enemy_->Reset();
	stage_->Reset();
	boss_->Reset();
	//その他初期化
	skydome->wtf.position = { 0.0f,0.0f,0.0f };
	startFlag = false;
	startCountTimer = 0;
	startCountFlag = false;
	roadTimer = 0;
	enemy_->playerHp = 15;
	enemy_->enemyCount = 0;
	overFlag = false; 
	retryFlag = 0;
	overTimer = 0;
	clearflag = false;
	clearSceneTimer = 0;
	clearCameraTimer = 0;
	clearTimer = 0;
	//スプライトの位置を初期化
	goSprite->SetPozition({ 0,0 });
	go2Sprite->SetPozition({ 0,0 });
	//カメラの位置の初期化
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);
	
}

void GameScene::FadeOut()
{
	title_->FadeOut();
}

void GameScene::FadeIn()
{
	player_->FadeIn();
}

void GameScene::Over()
{
	player_->Over();
	stage_->Over();
	enemy_->Over();
	boss_->Over();
}

void GameScene::ClearMove()
{
	player_->Clear();
	enemy_->Clear();
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (sceneNo_)
	{
	case SceneNo::TITLE:
		if (sceneNo_ == SceneNo::TITLE) {
			titleTimer++;

			if (titleTimer >= 100) {
				titleTimer = 0;
			}

			title_->Update();
			stage_->Update();

			//シーン切り替え//
			if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(RT)) {
				if (fadeCount == 0) {
					fadeCount = 1;
				}
			}
			if (fadeCount == 1) {
				outTimer++;
				FadeOut();
			}
			if (outTimer >= 90) {
				fadeFlag = true;
			}
			if (fadeFlag == true) {
				fadeTimer++;
				if (fadeTimer >= 47) {
					fadeCount = 0;
					outTimer = 0;
					Reset();
					sceneNo_ = SceneNo::GAME;
					
				}
			}

		}
		break;

	case SceneNo::GAME:
		if (sceneNo_ == SceneNo::GAME) {
			if (fadeFlag == true) {
				roadTimer++;
				if (roadTimer >= 50) {
					fadeTimer--;
					if (fadeTimer <= 1) {

						fadeFlag = false;
						fadeTimer = 0;
					}
				}
			}
			if (input->TriggerKey(DIK_R) || input->PButtonTrigger(Y)) {
				Reset();
				sceneNo_ = SceneNo::TITLE;
			}
			//ゲーム開始までの演出
			if (startFlag == false) {
				FadeIn();
				startCountTimer++;
				if (startCountTimer == 150) {
					startCountFlag = true;
				}
				if (startCountFlag == true) {
					startTimer++;
					//スタートカウント
					if (startTimer <= 30 && startTimer >= 1) {
						startCount = 1;
					}
					else if (startTimer <= 60 && startTimer >= 31) {
						startCount = 2;
					}
					else if (startTimer <= 90 && startTimer >= 61) {
						startCount = 3;
					}
					else if (startTimer <= 120 && startTimer >= 91) {
						startCount = 4;
						if (startTimer <= 103 && startTimer >= 100) {
							goSprite->SetPozition({ 0,0 });
							go2Sprite->SetPozition({ 0,0 });
						}
						else if (startTimer <= 106 && startTimer >= 104) {
							goSprite->SetPozition({ 0,-30 });
							go2Sprite->SetPozition({ 0,30 });
						}
						else if (startTimer <= 109 && startTimer >= 107) {
							goSprite->SetPozition({ 0,-60 });
							go2Sprite->SetPozition({ 0,60 });
						}
						else if (startTimer <= 112 && startTimer >= 110) {
							goSprite->SetPozition({ 0,-90 });
							go2Sprite->SetPozition({ 0,90 });
						}
						else if (startTimer <= 115 && startTimer >= 113) {
							goSprite->SetPozition({ 0,-120 });
							go2Sprite->SetPozition({ 0,120 });
						}
						else if (startTimer <= 118 && startTimer >= 116) {
							goSprite->SetPozition({ 0,-150 });
							go2Sprite->SetPozition({ 0,150 });
						}
						else if (startTimer <= 120 && startTimer >= 119) {
							goSprite->SetPozition({ 0,-180 });
							go2Sprite->SetPozition({ 0,180 });
						}
						else if (startTimer <= 123 && startTimer >= 121) {
							goSprite->SetPozition({ 0,-210 });
							go2Sprite->SetPozition({ 0,210 });
						}
						else if (startTimer <= 125 && startTimer >= 124) {
							goSprite->SetPozition({ 0,-240 });
							go2Sprite->SetPozition({ 0,240 });
						}
					}
					else if (startTimer >= 125) {
						startCount = 5;
					}
					if (startCount == 5) {
						startFlag = true;
						startTimer = 0;
						startCount = 0;
					}
				}
			} 
			
			player_->Update();
			/*Bullet_->Update();*/
			stage_->Update();
			skydome->Update();

			if (startFlag == true) {
				skydome->wtf.position.z -= skyMoveSpeed_;
				if (clearflag == false) {
					enemy_->Update();
				}
				//シーン切り替え
				if (enemy_->GetEnemyHP() >= 15)
				{
					clearflag = 1;
					if (clearflag == true) {
						ClearMove();
						clearSceneTimer++;
						if(clearSceneTimer >=100){
						enemy_->playerHp = 15;
						clearTimer++;
						if (clearTimer >= 1) {
							enemy_->enemyCount = 0;
							sceneNo_ = SceneNo::CLEAR;
						}
						}
					}
				}

				//シーン切り替え&リセット
				if (enemy_->GetPlayerHP() <= 0)
				{
					Over();
					overFlag = true;
					overTimer++;
					if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT) || input->ButtonInput(B)) {
						retryFlag = 1;
					}
					
					if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT) || input->ButtonInput(A)) {
						retryFlag = 2;
					}
					//リトライ
					if (retryFlag == 1) {
						if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(B)) {
							Reset();
							sceneNo_ = SceneNo::GAME;
						}
					}
					if (retryFlag == 2) {
						//タイトルに戻る
						if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(A)) {
							Reset();
							sceneNo_ = SceneNo::TITLE;
						}
					}

				}
			}
			if (enemy_->GetPlayerHP() <= 1) {
				//シーン切り替え
				if (input->TriggerKey(DIK_R) || input->ButtonInput(Y)) {
					Reset();
					sceneNo_ = SceneNo::TITLE;
				}
			}
		}
		break;
	case SceneNo::BOSS:

		player_->Update();

		skydome->Update();

		boss_->Update();

		stage_->Update();
		break;

	case SceneNo::CLEAR:
		if (sceneNo_ == SceneNo::CLEAR) {
			//クリア時の演出
			stage_->Update();
			clearCameraTimer++;
			if (clearCameraTimer <= 100) {
				camera1->Update();
				camera1->SetEye(camera1->GetEye() + Vector3{ 0.0f,-0.003f, 0.0f });
			}
			if (clearCameraTimer >= 250 && clearCameraTimer <= 350) {
				camera1->Update();
				camera1->SetEye(camera1->GetEye() - Vector3{ 0.0f,-0.003f, 0.0f });
			}
			if (clearCameraTimer >= 460) {
				titleTimer++;

				if (titleTimer >= 100) {
					titleTimer = 0;
				}
				////シーン切り替え
				if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(RT)) {
					sceneNo_ = SceneNo::TITLE;
				}
			}
			Object3d::SetCamera(camera1);
			FBXObject3d::SetCamera(camera1);

			clear_->Update();

		}
		break;

	case SceneNo::GAMEOVER:
		if (sceneNo_ == SceneNo::GAMEOVER) {
			overTimer++;
			//シーン切り替え
			if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(RT)) {
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
			/// <summary>
			/// 3Dオブジェクトの描画
			/// ここに3Dオブジェクトの描画処理を追加できる
			/// <summary>
			//3Dオブジェクト描画前処理
			Object3d::PreDraw(dxCommon->GetCommandList());
			//// 3Dオブクジェクトの描画
			title_->Draw();
			stage_->Draw();
			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			title_->FbxDraw();

			titleSprite->Draw();
			if (titleTimer >= 50) {
				spaceSprite->Draw();
			}
			//フェードインフェードアウト
			if (fadeTimer <= 5 && fadeTimer >= 1) {
				outSprite->Draw();
			}
			else if (fadeTimer <= 14 && fadeTimer >= 6) {
				out1Sprite->Draw();
			}
			else if (fadeTimer <= 23 && fadeTimer >= 15) {
				out2Sprite->Draw();
			}
			else if (fadeTimer <= 32 && fadeTimer >= 24) {
				out3Sprite->Draw();
			}
			else if (fadeTimer <= 39 && fadeTimer >= 33) {
				out4Sprite->Draw();
			}
			else if (fadeTimer <= 47 && fadeTimer >= 40) {
				out5Sprite->Draw();
			}
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
			Bullet_->Draw();
			if (clearflag == false) {
				enemy_->Draw();
			}
			skydome->Draw();

			stage_->Draw();
			boss_->Draw();

			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();
			if (overFlag == false) {
				enemy_->EffDraw();
				enemy_->FbxDraw();
			}
			if (startFlag == true) {
				//HPバー
				if (enemy_->GetPlayerHP() <= 15 && enemy_->GetPlayerHP() >= 11) {
					hPSprite->Draw();
				}
				else if (enemy_->GetPlayerHP() <= 10 && enemy_->GetPlayerHP() >= 6) {
					hP2Sprite->Draw();
				}
				else if (enemy_->GetPlayerHP() <= 5 && enemy_->GetPlayerHP() >= 1) {
					hP1Sprite->Draw();
				}
				else if (enemy_->GetPlayerHP() <= 0) {
					hP0Sprite->Draw();
				}
			}

			//フェードインフェードアウト
			if (fadeTimer <= 5 && fadeTimer >= 1) {
				outSprite->Draw();
			}
			else if (fadeTimer <= 14 && fadeTimer >= 6) {
				out1Sprite->Draw();
			}
			else if (fadeTimer <= 23 && fadeTimer >= 15) {
				out2Sprite->Draw();
			}
			else if (fadeTimer <= 32 && fadeTimer >= 24) {
				out3Sprite->Draw();
			}
			else if (fadeTimer <= 39 && fadeTimer >= 33) {
				out4Sprite->Draw();
			}
			else if (fadeTimer <= 47 && fadeTimer >= 40) {
				out5Sprite->Draw();
			}
			//カウントダウン
			if (startCount == 1) {
				start3Sprite->Draw();
			}else if (startCount == 2) {
				start3Sprite->Draw();
			}
			else if (startCount == 3) {
				start3Sprite->Draw();
			}
			else if (startCount == 4) {
				goSprite->Draw();
				go2Sprite->Draw();
			}
			if (enemy_->GetPlayerHP() <= 0)
			{
				
				//リトライ
				blackSprite->Draw();
				if (overTimer >= 40) {
					if (retryFlag == 1) {
						overSprite->Draw();
					}
					else if (retryFlag == 2) {
						over2Sprite->Draw();
					}
					else {
						over3Sprite->Draw();
					}
				}
			}
		}
		break;

	case SceneNo::BOSS:
		
		if (sceneNo_ == SceneNo::BOSS) {
			hPSprite->Draw();
			/// <summary>
			/// 3Dオブジェクトの描画
			/// ここに3Dオブジェクトの描画処理を追加できる
			/// <summary>
			//3Dオブジェクト描画前処理
			Object3d::PreDraw(dxCommon->GetCommandList());
			//// 3Dオブクジェクトの描画
			player_->Draw();
			Bullet_->Draw();
			skydome->Draw();
			boss_->Draw();
			stage_->Draw();
			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();
			boss_->FbxDraw();

			//HPバー
			if (enemy_->GetPlayerHP() <= 15 && enemy_->GetPlayerHP() >= 11) {
				hPSprite->Draw();
			}
			else if (enemy_->GetPlayerHP() <= 10 && enemy_->GetPlayerHP() >= 6) {
				hP2Sprite->Draw();
			}
			else if (enemy_->GetPlayerHP() <= 5 && enemy_->GetPlayerHP() >= 1) {
				hP1Sprite->Draw();
			}
			else if (enemy_->GetPlayerHP() <= 0) {
				hP0Sprite->Draw();
			}
	
		}
		break;

	case SceneNo::CLEAR:

		//3Dオブジェクト描画前処理
		Object3d::PreDraw(dxCommon->GetCommandList());
		//// 3Dオブクジェクトの描画
		skydome->Draw();
		stage_->Draw();
		clear_->Draw();
		
		//3Dオブジェクト描画後処理

		Object3d::PostDraw();
		clear_->FbxDraw();
		if (clearCameraTimer >= 280 && clearCameraTimer <= 420) {
			clearSprite->Draw();
		}
		if (clearCameraTimer >= 315 && clearCameraTimer <= 420) {
			conSprite->Draw();
			
		}
		if (clearCameraTimer >= 445) {
			backSprite->Draw();

			if (titleTimer >= 50) {
				spaceSprite->Draw();
			}
		}
		break;

	case SceneNo::GAMEOVER:

		//ゲームオーバー
		if (sceneNo_ == SceneNo::GAMEOVER) {
			blackSprite->Draw();
			if (overTimer <= 30) {
				overSprite->Draw();
			}
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