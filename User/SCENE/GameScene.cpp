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
	spriteCommon->LoadTexture(1, "Titlee.png");
	titleSprite->SetTextureIndex(1);

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

	////ゲームオーバー
	overSprite->Initialize(spriteCommon);
	overSprite->SetPozition({ 0,0 });
	overSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(3, "gameover.png");
	overSprite->SetTextureIndex(3);
	//HP3
	HPSprite->Initialize(spriteCommon);
	HPSprite->SetPozition({ 0,0 });
	HPSprite->SetSize({200.0f, 100.0f });
	spriteCommon->LoadTexture(4, "HP3.png");
	HPSprite->SetTextureIndex(4);

	//HP2
	HP2Sprite->Initialize(spriteCommon);
	HP2Sprite->SetPozition({ 0,0 });
	HP2Sprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(5, "HP2.png");
	HP2Sprite->SetTextureIndex(5);

	//HP1
	HP1Sprite->Initialize(spriteCommon);
	HP1Sprite->SetPozition({ 0,0 });
	HP1Sprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(6, "HP1.png");
	HP1Sprite->SetTextureIndex(6);

	//HP0
	HP0Sprite->Initialize(spriteCommon);
	HP0Sprite->SetPozition({ 0,0 });
	HP0Sprite->SetSize({ 200.0f, 100.0f });
	spriteCommon->LoadTexture(7, "HP0.png");
	HP0Sprite->SetTextureIndex(7);

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
	
	goSprite->Initialize(spriteCommon);
	goSprite->SetPozition({ 0,0 });
	goSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(17, "G.png");
	goSprite->SetTextureIndex(17);
	
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

	ParticleManager::SetCamera(mainCamera);
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	//タイトル
	title_ = new Title();
	title_->Initialize(dxCommon, input);
	title_->SetCamera(mainCamera);

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
	//クラスごとのリセット
	title_->Reset();
	player_->Reset();
	enemy_->Reset();
	stage_->Reset();
	boss_->Reset();
	//その他初期化
	startFlag = 0;
	startCountTimer = 0;
	startCountFlag = 0;
	roadTimer = 0;
	//スプライトの位置を初期化
	goSprite->SetPozition({ 0,0 });
	go2Sprite->SetPozition({ 0,0 });
}

void GameScene::FadeOut()
{
	title_->FadeOut();
}

void GameScene::FadeIn()
{
	player_->FadeIn();
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
			if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(RT)) {
				if (fadeCount == 0) {
					fadeCount = 1;
				}
			}
			if (fadeCount == 1) {
				outTimer++;
				FadeOut();
			}
			if (outTimer >= 90) {
				fadeFlag = 1;
			}
			if (fadeFlag == 1) {
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
			if (fadeFlag == 1) {
				roadTimer++;
				if (roadTimer >= 50) {
					fadeTimer--;
					if (fadeTimer <= 1) {

						fadeFlag = 0;
						fadeTimer = 0;
					}
				}
			}
			//ゲーム開始までの演出
			if (startFlag == 0) {
				FadeIn();
				startCountTimer++;
				if (startCountTimer == 150) {
					startCountFlag = 1;
				}
				if (startCountFlag == 1) {
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
							goSprite->SetPozition({ 0,-20 });
							go2Sprite->SetPozition({ 0,20 });
						}else if (startTimer <= 106 && startTimer >= 104) {
							goSprite->SetPozition({ 0,-40 });
							go2Sprite->SetPozition({ 0,40 });
						}
						else if (startTimer <= 109 && startTimer >= 107) {
							goSprite->SetPozition({ 0,-60 });
							go2Sprite->SetPozition({ 0,60 });
						}
						else if (startTimer <= 113 && startTimer >= 110) {
							goSprite->SetPozition({ 0,-80 });
							go2Sprite->SetPozition({ 0,80 });
						}
						else if (startTimer <= 117 && startTimer >= 114) {
							goSprite->SetPozition({ 0,-100 });
							go2Sprite->SetPozition({ 0,100 });
						}
						else if (startTimer <= 120 && startTimer >= 118) {
							goSprite->SetPozition({ 0,-120 });
							go2Sprite->SetPozition({ 0,120 });
						}
					}
					else if (startTimer >= 121) {
						startCount = 5;
					}
					if (startCount == 5) {
						startFlag = 1;
						startTimer = 0;
						startCount = 0;
					}
				}
			}
			
			player_->Update();
			stage_->Update();
			skydome->Update();

			if (startFlag == 1) {
				skydome->wtf.position.z -= skyMoveSpeed_;

				enemy_->Update();
				//シーン切り替え
				if (enemy_->GetEnemyHP() == 10)
				{
					sceneNo_ = SceneNo::BOSS;
					enemy_->playerHp = 15;
					enemy_->enemyCount = 0;
				}

				//シーン切り替え&リセット
				if (enemy_->GetPlayerHP() <= 0)
				{
					sceneNo_ = SceneNo::GAMEOVER;
					enemy_->playerHp = 15;
					enemy_->enemyCount = 0;


				}
			}
			//シーン切り替え
			if (input->TriggerKey(DIK_R) || input->ButtonInput(Y)) {
				Reset();
				sceneNo_ = SceneNo::TITLE;
			}
		}
		break;
	case SceneNo::BOSS:

		player_->Update();

		skydome->Update();

		boss_->Update();

		stage_->Update();


		//シーン切り替え
		if (input->TriggerKey(DIK_R) || input->ButtonInput(RT)) {
			Reset();
			sceneNo_ = SceneNo::GAME;
		}
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
			enemy_->Draw();
			skydome->Draw();

			stage_->Draw();
			boss_->Draw();

			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();
			enemy_->EffDraw();
			enemy_->FbxDraw();
			if (startFlag == 1) {
				//HPバー
				if (enemy_->GetPlayerHP() <= 15 && enemy_->GetPlayerHP() >= 11) {
					HPSprite->Draw();
				}
				else if (enemy_->GetPlayerHP() <= 10 && enemy_->GetPlayerHP() >= 6) {
					HP2Sprite->Draw();
				}
				else if (enemy_->GetPlayerHP() <= 5 && enemy_->GetPlayerHP() >= 1) {
					HP1Sprite->Draw();
				}
				else if (enemy_->GetPlayerHP() <= 0) {
					HP0Sprite->Draw();
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
			stage_->Draw();
			//3Dオブジェクト描画後処理
			Object3d::PostDraw();

			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();
			boss_->FbxDraw();

			//HPバー
			if (enemy_->GetPlayerHP() <= 15 && enemy_->GetPlayerHP() >= 11) {
				HPSprite->Draw();
			}
			else if (enemy_->GetPlayerHP() <= 10 && enemy_->GetPlayerHP() >= 6) {
				HP2Sprite->Draw();
			}
			else if (enemy_->GetPlayerHP() <= 5 && enemy_->GetPlayerHP() >= 1) {
				HP1Sprite->Draw();
			}
			else if (enemy_->GetPlayerHP() <= 0) {
				HP0Sprite->Draw();
			}
	
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