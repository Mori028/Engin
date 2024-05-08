#include "GameScene.h"
/*
* @file GameScene.cpp
* @brind ゲームの本体
*/

/// コンストクラタ
GameScene::GameScene() {
}
/// デストラクタ
GameScene::~GameScene() {
	
	delete mainCamera;
	delete camera1;
	delete camera2;
	delete camera3;
	delete skydome;
	delete skydomeMD;
}
/// 初期化
void GameScene::Initialize(DirectXCommon* dxCommon, MyEngine::Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);
	this->dxCommon = dxCommon;
	this->input = input;
	//スプライト共通部分の初期化  ///107まで 77~91削除 27~73削除
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	//タイトル
	titleSprite->Initialize(spriteCommon);titleSprite->SetPozition({ 0,0 });
	titleSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(1, "Titlee.png");titleSprite->SetTextureIndex(1);
	//クリア(スペース表示)
	spaceSprite->Initialize(spriteCommon);spaceSprite->SetPozition({ 0,0 });
	spaceSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(2, "SPACE.png");spaceSprite->SetTextureIndex(2);
	//タイトル(B表示)
	titleBSprite->Initialize(spriteCommon);titleBSprite->SetPozition({ 0,0 });
	titleBSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(3, "TitleB.png");titleBSprite->SetTextureIndex(3);
	////クリア
	clearSprite->Initialize(spriteCommon);clearSprite->SetPozition({ 0,0 });
	clearSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(4, "clear.png");clearSprite->SetTextureIndex(4);
	//クリア
	conSprite->Initialize(spriteCommon);conSprite->SetPozition({ 0,0 });
	conSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(5, "clearcon.png");conSprite->SetTextureIndex(5);
	//クリア(戻る)
	backSprite->Initialize(spriteCommon);backSprite->SetPozition({ 0,0 });
	backSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(6, "backT.png");backSprite->SetTextureIndex(6);
	//リトライ
	overSprite->Initialize(spriteCommon);overSprite->SetPozition({ 0,0 });
	overSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(7, "yes.png");overSprite->SetTextureIndex(7);
	//ゲームオーバー(背景)
	blackSprite->Initialize(spriteCommon);blackSprite->SetPozition({ 0,0 });
	blackSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(8, "Black.png");blackSprite->SetTextureIndex(8);
	//ゲームオーバー(選択画面)
	over2Sprite->Initialize(spriteCommon);over2Sprite->SetPozition({ 0,0 });
	over2Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(9, "no.png");over2Sprite->SetTextureIndex(9);
	//ゲームオーバー
	over3Sprite->Initialize(spriteCommon);over3Sprite->SetPozition({ 0,0 });
	over3Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(10, "over.png");over3Sprite->SetTextureIndex(10);
	//HP3
	hPSprite->Initialize(spriteCommon);hPSprite->SetPozition({ 0,0 });
	hPSprite->SetSize({200.0f, 100.0f });spriteCommon->LoadTexture(11, "HP3.png");hPSprite->SetTextureIndex(11);
	//HP2
	hP2Sprite->Initialize(spriteCommon);hP2Sprite->SetPozition({ 0,0 });
	hP2Sprite->SetSize({ 200.0f, 100.0f });spriteCommon->LoadTexture(12, "HP2.png");hP2Sprite->SetTextureIndex(12);
	//HP1
	hP1Sprite->Initialize(spriteCommon);hP1Sprite->SetPozition({ 0,0 });
	hP1Sprite->SetSize({ 200.0f, 100.0f });spriteCommon->LoadTexture(13, "HP1.png");hP1Sprite->SetTextureIndex(13);
	//HP0
	hP0Sprite->Initialize(spriteCommon);hP0Sprite->SetPozition({ 0,0 });
	hP0Sprite->SetSize({ 200.0f, 100.0f });spriteCommon->LoadTexture(14, "HP0.png");hP0Sprite->SetTextureIndex(14);
	//フェードイン0
	outSprite->Initialize(spriteCommon);outSprite->SetPozition({ 0,0 });
	outSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(15, "out.png");outSprite->SetTextureIndex(15);
	//フェードイン1
	out1Sprite->Initialize(spriteCommon);out1Sprite->SetPozition({ 0,0 });
	out1Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(16, "out1.png");out1Sprite->SetTextureIndex(16);
	//フェードイン2
	out2Sprite->Initialize(spriteCommon);out2Sprite->SetPozition({ 0,0 });
	out2Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(17, "out2.png");out2Sprite->SetTextureIndex(17);
	//フェードイン3
	out3Sprite->Initialize(spriteCommon);out3Sprite->SetPozition({ 0,0 });
	out3Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(18, "out3.png");out3Sprite->SetTextureIndex(18);
	//フェードイン4
	out4Sprite->Initialize(spriteCommon);out4Sprite->SetPozition({ 0,0 });
	out4Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(19, "out4.png");out4Sprite->SetTextureIndex(19);
	//フェードイン5
	out5Sprite->Initialize(spriteCommon);out5Sprite->SetPozition({ 0,0 });
	out5Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(20, "out5.png");out5Sprite->SetTextureIndex(20);
	//スタートカウント
	start3Sprite->Initialize(spriteCommon);start3Sprite->SetPozition({ 0,0 });
	start3Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(21, "3.png");start3Sprite->SetTextureIndex(21);
	//スタートの文字
	goSprite->Initialize(spriteCommon);goSprite->SetPozition({ 0,0 });
	goSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(22, "G.png");goSprite->SetTextureIndex(22);
	//スタートの文字
	go2Sprite->Initialize(spriteCommon);go2Sprite->SetPozition({ 0,0 });
	go2Sprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(23, "O.png");go2Sprite->SetTextureIndex(23);
	//BOSSHP
	h50Sprite->Initialize(spriteCommon);h50Sprite->SetPozition({ 400,50 });
	h50Sprite->SetSize({ 500.0f, 30.0f });spriteCommon->LoadTexture(24, "EHP50.png");h50Sprite->SetTextureIndex(24);
	//BOSSHP
	h49Sprite->Initialize(spriteCommon); h49Sprite->SetPozition({ 400,50 });
	h49Sprite->SetSize({ 500.0f, 30.0f }); spriteCommon->LoadTexture(25, "EHP49.png"); h49Sprite->SetTextureIndex(25);
	//BOSSHP
	h0Sprite->Initialize(spriteCommon);h0Sprite->SetPozition({ 400,50 });
	h0Sprite->SetSize({ 500.0f, 30.0f });spriteCommon->LoadTexture(26, "EHP0.png");h0Sprite->SetTextureIndex(26);
	//damage
	damageSprite->Initialize(spriteCommon);damageSprite->SetPozition({ 0,0 });
	damageSprite->SetSize({ 1280.0f, 720.0f });spriteCommon->LoadTexture(27, "sousa.png");damageSprite->SetTextureIndex(27);
	//敵数30カウント
	E15Sprite->Initialize(spriteCommon); E15Sprite->SetPozition({ 1200,0 });
	E15Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(28, "15t.png"); E15Sprite->SetTextureIndex(28);
	E14Sprite->Initialize(spriteCommon); E14Sprite->SetPozition({ 1200,0 });
	E14Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(29, "14t.png"); E14Sprite->SetTextureIndex(29);
	E13Sprite->Initialize(spriteCommon); E13Sprite->SetPozition({ 1200,0 });
	E13Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(30, "13t.png"); E13Sprite->SetTextureIndex(30);
	E12Sprite->Initialize(spriteCommon); E12Sprite->SetPozition({ 1200,0 });
	E12Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(31, "12t.png"); E12Sprite->SetTextureIndex(31);
	E11Sprite->Initialize(spriteCommon); E11Sprite->SetPozition({ 1200,0 });
	E11Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(32, "11t.png"); E11Sprite->SetTextureIndex(32);
	E10Sprite->Initialize(spriteCommon); E10Sprite->SetPozition({ 1200,0 });
	E10Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(33, "10t.png"); E10Sprite->SetTextureIndex(33);
	E9Sprite->Initialize(spriteCommon); E9Sprite->SetPozition({ 1200,0 });
	E9Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(34, "9t.png"); E9Sprite->SetTextureIndex(34);
	E8Sprite->Initialize(spriteCommon); E8Sprite->SetPozition({ 1200,0 });
	E8Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(35, "8t.png"); E8Sprite->SetTextureIndex(35);
	E7Sprite->Initialize(spriteCommon); E7Sprite->SetPozition({ 1200,0 });
	E7Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(36, "7t.png"); E7Sprite->SetTextureIndex(36);
	E6Sprite->Initialize(spriteCommon); E6Sprite->SetPozition({ 1200,0 });
	E6Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(37, "6t.png"); E6Sprite->SetTextureIndex(37);
	E5Sprite->Initialize(spriteCommon); E5Sprite->SetPozition({ 1200,0 });
	E5Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(38, "5t.png"); E5Sprite->SetTextureIndex(38);
	E4Sprite->Initialize(spriteCommon); E4Sprite->SetPozition({ 1200,0 });
	E4Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(39, "4t.png"); E4Sprite->SetTextureIndex(39);
	E3Sprite->Initialize(spriteCommon); E3Sprite->SetPozition({ 1200,0 });
	E3Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(40, "3t.png"); E3Sprite->SetTextureIndex(40);
	E2Sprite->Initialize(spriteCommon); E2Sprite->SetPozition({ 1200,0 });
	E2Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(41, "2t.png"); E2Sprite->SetTextureIndex(41);
	E1Sprite->Initialize(spriteCommon); E1Sprite->SetPozition({ 1200,0 });
	E1Sprite->SetSize({ 80.0f, 80.0f }); spriteCommon->LoadTexture(42, "1t.png"); E1Sprite->SetTextureIndex(42);
	damagesSprite->Initialize(spriteCommon); damagesSprite->SetPozition({ 0,0 });
	damagesSprite->SetSize({ 1280.0f, 720.0f }); spriteCommon->LoadTexture(43, "damage.png"); damagesSprite->SetTextureIndex(43);
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
	//ボス
	enemy_ = new Enemy();
	enemy_->Initialize(dxCommon, input);
	enemy_->SetPlayer(player_);
	//敵の弾
	bullet_ = new Bullet();
	bullet_->Initialize(dxCommon, input);
	bullet_->SetPlayer(player_);
	//ボス
	boss_ = new Boss();
	boss_->Initialize(dxCommon, input);
	boss_->SetPlayer(player_);
	//ゲーム開始時
	fade_ = new Fade();
	fade_->Initialize(dxCommon, input);
	//ステージ
	stage_ = new Stage();
	stage_->Initialize(dxCommon, input);
	stage_->SetCamera(mainCamera);
	//パーティクル生成
	particleManager = std::make_unique<ParticleManager>();
	particleManager.get()->Initialize();
	particleManager->LoadTexture("blod.png");
	particleManager->Update();

	audio = new Audio();
	audio->Initialize();
	audio->LoadWave("Title.wav");
	audio->LoadWave("game.wav");
	audio->LoadWave("open.wav");
	//ファイルの読み込み
	LoadEnemyPopData();
}
//リセット
void GameScene::Reset() {
	//クラスごとのリセット
	title_->Reset();
	clear_->Reset();
	player_->Reset();
	bullet_->Reset();
	enemy_->Reset();
	stage_->Reset();
	boss_->Reset();
	fade_->Reset();
	//その他初期化
	skydome->wtf.position = { 0.0f,0.0f,0.0f };
	startFlag = false;
	startCountTimer = 0;
	startCountFlag = false;
	roadTimer = 0;
	playerHp = 15;
	overFlag = false; 
	retryFlag = 0;
	overTimer = 0;
	damagecount = 0;
	damageFlag = false;
	clearflag = false;
	clearSceneTimer = 0;
	clearCameraTimer = 0;
	clearTimer = 0;
	EnemyCount = 15;
	startTimer = 280;
	soundCheckFlag = 0;
	soundCheckFlag2 = 0;
	soundCheckFlag3 = 0;
	soundCheckFlag4 = 0;
	//スプライトの位置を初期化
	goSprite->SetPozition({ 0,0 });
	go2Sprite->SetPozition({ 0,0 });
	//カメラの位置の初期化
	Object3d::SetCamera(mainCamera);
	FBXObject3d::SetCamera(mainCamera);
}
//フェ-ドアウト
void GameScene::FadeOut()
{
	title_->FadeOut();
}
//フェードイン
void GameScene::FadeIn()
{
	player_->FadeIn();
}
//スタート
void GameScene::Start()
{
	player_->Start();
}
//リトライ
void GameScene::Retry()
{
	player_->Retry();
}
//ゲームオーバー
void GameScene::Over()
{
	player_->Over();
	stage_->Over();
	boss_->Over();
	bullet_->Over();
	enemy_->Over();
}
//クリア
void GameScene::ClearMove()
{
	player_->Clear();
	bullet_->Clear();
}
/// 毎フレーム処理
void GameScene::Update() {
	switch (sceneNo_)
	{
	case SceneNo::TITLE:
		if (sceneNo_ == SceneNo::TITLE) {
			titleTimer++;

			if (soundCheckFlag3 == 1) {
				//ゲームシーンの音楽を止める
				pSourceVoice[2]->Stop();
				soundCheckFlag3 = 0;
			}

			if (soundCheckFlag == 0) {
				//タイトルBGM再生
				pSourceVoice[0] = audio->PlayWave("Title.wav");
				pSourceVoice[0]->SetVolume(0.3f);
				soundCheckFlag = 1;
			}

			if (titleTimer >= 100) {
				titleTimer = 0;
			}

			title_->Update();
			stage_->Update();
			//シーン切り替え//
			if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(B)) {
				if (fadeCount == 0) {
					//ステージ選択時の効果音
					pSourceVoice[1] = audio->PlayWave("open.wav");
					pSourceVoice[1]->SetVolume(0.4f);
					soundCheckFlag2 = 1;

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
			//タイトルの音楽を止める
			pSourceVoice[0]->Stop();
			soundCheckFlag = 0;

			if (soundCheckFlag3 == 0) {
				//ゲームBGM再生

				pSourceVoice[2] = audio->PlayWave("game.wav");
				pSourceVoice[2]->SetVolume(0.5f);
				soundCheckFlag3 = 1;
			}

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
			if (input->TriggerKey(DIK_R)) {
				Reset();
				sceneNo_ = SceneNo::TITLE;
			}
			//ゲーム開始までの演出
			if (startFlag == false) {
				player_->FadeIn();
				startCountTimer++;
				if (startCountTimer == 150) {
					startCountFlag = true;
				}
				if (startCountFlag == true) {

					startTimer++;
					
					//スタートカウント
					if (startTimer <= 280 && startTimer >= 251) {
						startCount = 1;
					}
					else if (startTimer <= 310 && startTimer >= 281) {
						startCount = 2;
					}
					else if (startTimer <= 340 && startTimer >= 311) {
						startCount = 3;
					}
					else if (startTimer <= 380 && startTimer >= 341) {
						startCount = 4;
						if (startTimer <= 353 && startTimer >= 350) {
							goSprite->SetPozition({ 0,0 });
							go2Sprite->SetPozition({ 0,0 });
						}
						else if (startTimer <= 356 && startTimer >= 354) {
							goSprite->SetPozition({ 0,-30 });
							go2Sprite->SetPozition({ 0,30 });
						}
						else if (startTimer <= 359 && startTimer >= 357) {
							goSprite->SetPozition({ 0,-60 });
							go2Sprite->SetPozition({ 0,60 });
						}
						else if (startTimer <= 362 && startTimer >= 360) {
							goSprite->SetPozition({ 0,-90 });
							go2Sprite->SetPozition({ 0,90 });
						}
						else if (startTimer <= 365 && startTimer >= 363) {
							goSprite->SetPozition({ 0,-120 });
							go2Sprite->SetPozition({ 0,120 });
						}
						else if (startTimer <= 368 && startTimer >= 366) {
							goSprite->SetPozition({ 0,-150 });
							go2Sprite->SetPozition({ 0,150 });
						}
						else if (startTimer <= 370 && startTimer >= 369) {
							goSprite->SetPozition({ 0,-180 });              
							go2Sprite->SetPozition({ 0,180 });
						}
						else if (startTimer <= 373 && startTimer >= 371) {
							goSprite->SetPozition({ 0,-210 });
							go2Sprite->SetPozition({ 0,210 });
						}
						else if (startTimer <= 375 && startTimer >= 374) {
							goSprite->SetPozition({ 0,-240 });
							go2Sprite->SetPozition({ 0,240 });
						}
					}
					else if (startTimer >= 375) {
						startCount = 5;   
					}
					if (startCount == 5) {
						Start();
						startFlag = true;
						startTimer = 0;
						startCount = 0;
					}
				}
			} 
			player_->Update();
			stage_->Update();
			skydome->Update();

			if (startFlag == true) {
				skydome->wtf.position.z -= skyMoveSpeed_;
				if (clearflag == false) {
					bullet_->Update();
					enemy_->Update();
					for (std::unique_ptr<Enemys>& enemys : enemys_) {
						enemys->Update();
					}
					//敵の無敵時間
					if (live1 == false) {
						live1Timer++;
						if (live1Timer >= 100) {
							live1 = true;
							live1Timer = 0;
						}
					}
					if (live2 == false) {
						live2Timer++;
						if (live2Timer >= 100) {
							live2 = true;
							live2Timer = 0;
						}
					}
					if (live3 == false) {
						live3Timer++;
						if (live3Timer >= 100) {
							live3 = true;
							live3Timer = 0;
						}
					}
					if (live4 == false) {
						live4Timer++;
						if (live4Timer >= 100) {
							live4 = true;
							live4Timer = 0;
						}
					}
					if (live5 == false) {
						live5Timer++;
							if (live5Timer >= 100) {
								live5 = true;
								live5Timer = 0;
							}
					};
					if (damageFlag == true) {
						damagecount++;
						if (damagecount >= 13) {
							damageFlag = false;
							damagecount = 0;
						}
					}

					// 敵発生コマンドの更新
					UpdataEnemyPopCommands();
					if (live1 == true) {
						////当たり判定(敵1機と自弾)
						if (coll.CircleCollision(enemy_->GetWorldPosition(), player_->GetBulletWorldPosition(), 0.1f, 0.1f)) {
							OnColision1();
						};
					}
					if (live2 == true) {
						////当たり判定(敵2機と自弾)
						if (coll.CircleCollision(enemy_->GetEne2WorldPosition(), player_->GetBulletWorldPosition(), 0.1f, 0.1f)) {
							OnColision2();
						};
					}
					if (live3 == true) {
						////当たり判定(敵3機と自弾)
						if (coll.CircleCollision(enemy_->GetEne3WorldPosition(), player_->GetBulletWorldPosition(), 0.1f, 0.1f)) {
							OnColision3();
						};
					}
					if (live4 == true) {
						////当たり判定(敵4機と自弾)
						if (coll.CircleCollision(enemy_->GetEne4WorldPosition(), player_->GetBulletWorldPosition(), 0.1f, 0.1f)) {
							OnColision4();
						};
					}
					////当たり判定(自機と敵弾)
					if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBulletWorldPosition(), 0.1f, 0.1f)) {
						OnColisionPlayer();
					};
					////当たり判定(自機と敵弾)
					if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet1WorldPosition(), 0.1f, 0.1f)) {
						OnColisionPlayer();
					};
					////当たり判定(自機と敵弾)
					if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet2WorldPosition(), 0.1f, 0.1f)) {
						OnColisionPlayer();
					};
					//if (live5 == true) {
					//	for (std::unique_ptr<Enemys>& enemys : enemys_) {
					//		//当たり判定(敵機と自機弾)
					//		if (coll.CircleCollision(player_->GetBulletWorldPosition(), enemys->GetWorldPosition(), 0.1f, 0.1f)) {
					//			OnColision();
					//		}
					//	}
					//}1dd
					// デスフラグの立った敵を削除
					enemys_.remove_if([](std::unique_ptr<Enemys>& enemys) {
						return enemys->IsDead();
						});
				}
				//シーン切り替え
				if (EnemyCount >= 30)
				{
					bullet_->ModeChange();
					sceneNo_ = SceneNo::BOSS;
				}
				//シーン切り替え&リセット
				if (playerHp <= 0)
				{
					if (soundCheckFlag3 == 1) {
						//ゲームシーンの音楽を止める
						pSourceVoice[2]->Stop();
						soundCheckFlag3 = 0;
					}
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
							//選択時の効果音
							pSourceVoice[1] = audio->PlayWave("open.wav");
							pSourceVoice[1]->SetVolume(0.4f);
							soundCheckFlag2 = 1;
							Reset();
							sceneNo_ = SceneNo::GAME;
						}
					}
					if (retryFlag == 2) {
						//タイトルに戻る
						if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(A)) {
							//選択時の効果音
							pSourceVoice[1] = audio->PlayWave("open.wav");
							pSourceVoice[1]->SetVolume(0.4f);
							soundCheckFlag2 = 1;
							Reset();
							sceneNo_ = SceneNo::TITLE;
						}
					}
				}
			}
			if (playerHp <= 1) {
				//シーン切り替え
				if (input->TriggerKey(DIK_R) || input->ButtonInput(Y)) {
					Reset();
					sceneNo_ = SceneNo::TITLE;
				}
			}
			
			camera2->Update();

			if (input->PushKey(DIK_D) || input->StickInput(L_RIGHT)) {
				camera2->SetEye(camera2->GetEye() + Vector3{ -0.001f,0.0f, 0.0f });
			}
			if (input->PushKey(DIK_A) || input->StickInput(L_LEFT)) {
				camera2->SetEye(camera2->GetEye() - Vector3{ -0.001f,0.0f, 0.0f });
			}
			if (input->PushKey(DIK_S) || input->StickInput(L_DOWN)) {
				camera2->SetEye(camera2->GetEye() - Vector3{ 0.0f,-0.001f, 0.0f });
			}
			if (input->PushKey(DIK_W) || input->StickInput(L_UP)) {
				camera2->SetEye(camera2->GetEye() + Vector3{ 0.0f,-0.001f, 0.0f });
			}
			
			
			Object3d::SetCamera(camera2);
			FBXObject3d::SetCamera(camera2);
		}
		break;
	case SceneNo::BOSS:
		//雑魚敵戦の音楽を止める
		/*pSourceVoice[2]->Stop();*/
		soundCheckFlag3 = 0;

		if (soundCheckFlag4 == 0) {
			//ゲームBGM再生

			pSourceVoice[3] = audio->PlayWave("game.wav");
			pSourceVoice[3]->SetVolume(0.5f);
			soundCheckFlag4 = 1;
		}

		player_->Update();
		skydome->Update();
		boss_->Update();
		stage_->Update();
		bullet_->Update();
		//シーン切り替え
		if (boss_->GetBossHP() >= 50)
		{
			clearflag = 1;
			if (clearflag == true) {
				ClearMove();
				clearSceneTimer++;
				if (clearSceneTimer >= 100) {
					playerHp = 15;
					clearTimer++;
					if (clearTimer >= 1) {
						boss_->BossCount = 0;
						
						sceneNo_ = SceneNo::CLEAR;
					}
				}
			}
		}
		if (damageFlag == true) {
			damagecount++;
			if (damagecount >= 13) {
				damageFlag = false;
				damagecount = 0;
			}
		}
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBulletWorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet1WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet2WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet3WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet4WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet5WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet6WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet7WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet8WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet9WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet10WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet11WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet12WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet13WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		////当たり判定(自機と敵弾)
		if (coll.CircleCollision(player_->GetWorldPosition(), bullet_->GetBullet14WorldPosition(), 0.1f, 0.1f)) {
			OnColisionPlayer();
		};
		//シーン切り替え&リセット
		if (playerHp <= 0)
		{
			if (clearflag == false) {
				//ボス戦の音楽を止める
				pSourceVoice[3]->Stop();
				soundCheckFlag4 = 0;

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
						//選択時の効果音
						pSourceVoice[1] = audio->PlayWave("open.wav");
						pSourceVoice[1]->SetVolume(0.4f);
						soundCheckFlag2 = 1;
						Reset();
						bullet_->ModeChange();
						Retry();
						sceneNo_ = SceneNo::BOSS;
					}
				}
				if (retryFlag == 2) {
					//選択時の効果音
					pSourceVoice[1] = audio->PlayWave("open.wav");
					pSourceVoice[1]->SetVolume(0.4f);
					soundCheckFlag2 = 1;
					//タイトルに戻る
					if (input->TriggerKey(DIK_SPACE) || input->ButtonInput(A)) {
						Reset();
						sceneNo_ = SceneNo::TITLE;
					}
				}
			}
		}
		camera2->Update();

		if (input->PushKey(DIK_D) || input->StickInput(L_RIGHT)) {
			camera2->SetEye(camera2->GetEye() + Vector3{ -0.001f,0.0f, 0.0f });
		}
		if (input->PushKey(DIK_A) || input->StickInput(L_LEFT)) {
			camera2->SetEye(camera2->GetEye() - Vector3{ -0.001f,0.0f, 0.0f });
		}
		if (input->PushKey(DIK_S) || input->StickInput(L_DOWN)) {
			camera2->SetEye(camera2->GetEye() - Vector3{ 0.0f,-0.001f, 0.0f });
		}
		if (input->PushKey(DIK_W) || input->StickInput(L_UP)) {
			camera2->SetEye(camera2->GetEye() + Vector3{ 0.0f,-0.001f, 0.0f });
		}


		Object3d::SetCamera(camera2);
		FBXObject3d::SetCamera(camera2);
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
				if (input->TriggerKey(DIK_SPACE)|| input->PButtonTrigger(B)) {
					//選択時の効果音
					pSourceVoice[1] = audio->PlayWave("open.wav");
					pSourceVoice[1]->SetVolume(0.4f);
					soundCheckFlag2 = 1;
					Reset();
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
			if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(B)) {
				sceneNo_ = SceneNo::TITLE;
			}
		}
		break;
	}
}
/// 描画
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
				titleBSprite->Draw();
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

			Object3d::PreDraw(dxCommon->GetCommandList());
			//// 3Dオブクジェクトの描画
			skydome->Draw();
			stage_->Draw();
			if (startFlag == true) {
				bullet_->Draw();
			}
			if (startTimer <= 250 && startTimer >= 1) {
				//ボスの登場
				fade_->FbxDraw();
			}
			player_->Draw();

			//3Dオブジェクト描画後処理
			Object3d::PostDraw();
			//// パーティクル UI FBX スプライト描画
			player_->FbxDraw();
			//ダメージエフェクト
			bullet_->EffDraw();
			boss_->FbxDraw();
			if (startFlag == true) {
				for (std::unique_ptr<Enemys>& enemys : enemys_) {
					enemys->FbxDraw();
				}
				enemy_->FbxDraw();
				//操作説明
				damageSprite->Draw();
				//HPバー
				if (playerHp <= 15 && playerHp >= 11) {
					hPSprite->Draw();
				}
				else if (playerHp <= 10 && playerHp >= 6) {
					hP2Sprite->Draw();
				}
				else if (playerHp <= 5 && playerHp >= 1) {
					hP1Sprite->Draw();
				}
				else if (playerHp <= 0) {
					hP0Sprite->Draw();
				}
				if (EnemyCount == 15) {
					E15Sprite->Draw();
				}if (EnemyCount == 16) {
					E14Sprite->Draw();
				}if (EnemyCount == 17) {
					E13Sprite->Draw();
				}if (EnemyCount == 18) {
					E12Sprite->Draw();
				}if (EnemyCount == 19) {
					E11Sprite->Draw();
				}if (EnemyCount == 20) {
					E10Sprite->Draw();
				}if (EnemyCount == 21) {
					E9Sprite->Draw();
				}if (EnemyCount == 22) {
					E8Sprite->Draw();
				}if (EnemyCount == 23) {
					E7Sprite->Draw();
				}if (EnemyCount == 24) {
					E6Sprite->Draw();
				}if (EnemyCount == 25) {
					E5Sprite->Draw();
				}if (EnemyCount == 26) {
					E4Sprite->Draw();
				}if (EnemyCount == 27) {
					E3Sprite->Draw();
				}if (EnemyCount == 28) {
					E2Sprite->Draw();
				}if (EnemyCount == 29) {
					E1Sprite->Draw();
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
			}
			else if (startCount == 2) {
				start3Sprite->Draw();
			}
			else if (startCount == 3) {
				start3Sprite->Draw();
			}
			else if (startCount == 4) {
				goSprite->Draw();
				go2Sprite->Draw();
			}
			if (damageFlag == true) {
				damagesSprite->Draw();
			}
			if (playerHp <= 0)
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
			skydome->Draw();
			boss_->Draw();
			bullet_->Draw();
			stage_->Draw();
			//3Dオブジェクト描画後処理
			Object3d::PostDraw();
			//// パーティクル UI FBX スプライト描画
			//ダメージエフェクト
			bullet_->EffDraw();
			player_->FbxDraw();
			if (boss_->GetBossHP() <= 49) {
				boss_->FbxDraw();
			}
			if (damageFlag == true) {
				damagesSprite->Draw();
			}
			//HPバー
			if (playerHp <= 15 && playerHp >= 11) {
				hPSprite->Draw();
			}
			else if (playerHp <= 10 && playerHp >= 6) {
				hP2Sprite->Draw();
			}
			else if (playerHp <= 5 && playerHp >= 1) {
				hP1Sprite->Draw();
			}
			else if (playerHp <= 0) {
				hP0Sprite->Draw();
			}
		
			h0Sprite->Draw();
			h49Sprite->Draw();
			if (boss_->GetBossHP() == 0) {
				h50Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 1) {
				h49Sprite->SetSize({ 490.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 2) {
				h49Sprite->SetSize({ 480.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 3) {
				h49Sprite->SetSize({ 470.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 4) {
				h49Sprite->SetSize({ 460.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 5) {
				h49Sprite->SetSize({ 450.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 6) {
				h49Sprite->SetSize({ 440.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 7) {
				h49Sprite->SetSize({ 430.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 8) {
				h49Sprite->SetSize({ 420.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 9) {
				h49Sprite->SetSize({ 410.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 10) {
				h49Sprite->SetSize({ 400.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 11) {
				h49Sprite->SetSize({ 390.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 12) {
				h49Sprite->SetSize({ 380.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 13) {
				h49Sprite->SetSize({ 370.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 14) {
				h49Sprite->SetSize({ 360.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 15) {
				h49Sprite->SetSize({ 350.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 16) {
				h49Sprite->SetSize({ 340.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 17) {
				h49Sprite->SetSize({ 330.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 18) {
				h49Sprite->SetSize({ 320.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 19) {
				h49Sprite->SetSize({ 310.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 20) {
				h49Sprite->SetSize({ 300.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 21) {
				h49Sprite->SetSize({ 290.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 22) {
				h49Sprite->SetSize({ 280.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 23) {
				h49Sprite->SetSize({ 270.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 24) {
				h49Sprite->SetSize({ 260.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 25) {
				h49Sprite->SetSize({ 250.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 26) {
				h49Sprite->SetSize({ 240.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 27) {
				h49Sprite->SetSize({ 230.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 28) {
				h49Sprite->SetSize({ 220.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 29) {
				h49Sprite->SetSize({ 210.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 30) {
				h49Sprite->SetSize({ 200.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 31) {
				h49Sprite->SetSize({ 190.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 32) {
				h49Sprite->SetSize({ 180.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 33) {
				h49Sprite->SetSize({ 170.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 34) {
				h49Sprite->SetSize({ 160.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 35) {
				h49Sprite->SetSize({ 150.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 36) {
				h49Sprite->SetSize({ 140.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 37) {
				h49Sprite->SetSize({ 130.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 38) {
				h49Sprite->SetSize({ 120.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 39) {
				h49Sprite->SetSize({ 110.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 40) {
				h49Sprite->SetSize({ 100.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 41) {
				h49Sprite->SetSize({ 90.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 42) {
				h49Sprite->SetSize({ 80.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 43) {
				h49Sprite->SetSize({ 70.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 44) {
				h49Sprite->SetSize({ 60.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 45) {
				h49Sprite->SetSize({ 50.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 46) {
				h49Sprite->SetSize({ 40.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 47) {
				h49Sprite->SetSize({ 30.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 48) {
				h49Sprite->SetSize({ 20.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 49) {
				h49Sprite->SetSize({ 10.0f, 30.0f });
			}
			else if (boss_->GetBossHP() == 50) {
				h49Sprite->SetSize({ 0.0f, 0.0f });
			}
			if (playerHp <= 0)
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
//エフェクト
void GameScene::EffUpdate()
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
//エフェクト描画
void GameScene::EffDraw()
{
	//ダメージエフェクト
	if (isEffFlag == 1) {
		// 3Dオブクジェクトの描画
		particleManager->Draw();
	}
}
//敵のデータ
void GameScene::LoadEnemyPopData() {

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");

	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();

}
//敵の出現
void GameScene::UpdataEnemyPopCommands()
{
	//待機処理
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//待機完了
			isStand_ = false;
		}
		return;
	}

	// 1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行分の文字数をストリームに変換して解折しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			std::getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// Y座標
			std::getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// Z座標
			std::getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			GenerEnemy(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = std::atoi(word.c_str());

			//待機開始
			isStand_ = true;
			standTime_ = waitTime;

			//ループを抜ける
			break;
		}
	}
}
//敵のデータ読み込み
void GameScene::GenerEnemy(Vector3 EnemyPos)
{
	std::unique_ptr<Enemys> newEnemys = std::make_unique<Enemys>();

	newEnemys->Initialize(dxCommon, input);
	//敵キャラにアドレスを渡す
	newEnemys->SetPlayer(player_);

	enemys_.push_back(std::move(newEnemys));
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
//敵の当たり判定
void GameScene::OnColision()
{
	EnemyCount = EnemyCount + 1;
	isEffFlag = 1;
	live5 = false;
	//当たり判定(敵機と自機弾)
	for (std::unique_ptr<Enemys>& enemys : enemys_) {
		enemys->OnColision();
	}
}
//プレイヤーが当たった時
void GameScene::OnColisionPlayer()
{
	playerHp = playerHp - 1;
	damageFlag = true;
}
 
void GameScene::OnColision1()
{
	EnemyCount = EnemyCount + 1;
	live1 = false;
	pSourceVoice[1] = audio->PlayWave("open.wav");
	pSourceVoice[1]->SetVolume(0.4f);
	enemy_->OnColision1();
}
void GameScene::OnColision2()
{
	EnemyCount = EnemyCount + 1;
	live2 = false;
	pSourceVoice[1] = audio->PlayWave("open.wav");
	pSourceVoice[1]->SetVolume(0.4f);
	enemy_->OnColision2();
}
void GameScene::OnColision3()
{
	EnemyCount = EnemyCount + 1;
	live3 = false;
	pSourceVoice[1] = audio->PlayWave("open.wav");
	pSourceVoice[1]->SetVolume(0.4f);
	enemy_->OnColision3();
}
void GameScene::OnColision4()
{
	EnemyCount = EnemyCount + 1;
	live4 = false;
	pSourceVoice[1] = audio->PlayWave("open.wav");
	pSourceVoice[1]->SetVolume(0.4f);
	enemy_->OnColision4();
}