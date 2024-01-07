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

	//スプライト共通部分の初期化  ///75まで
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//タイトル
	titleSprite->Initialize(spriteCommon);
	titleSprite->SetPozition({ 0,0 });
	titleSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(1, "Titlee.png");
	titleSprite->SetTextureIndex(1);
	//クリア(スペース表示)
	spaceSprite->Initialize(spriteCommon);
	spaceSprite->SetPozition({ 0,0 });
	spaceSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(9, "SPACE.png");
	spaceSprite->SetTextureIndex(9);
	//タイトル(B表示)
	titleBSprite->Initialize(spriteCommon);
	titleBSprite->SetPozition({ 0,0 });
	titleBSprite->SetSize({ 1280.0f, 720.0f });
	spriteCommon->LoadTexture(24, "TitleB.png");
	titleBSprite->SetTextureIndex(24);
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
	//BOSSHP
	h50Sprite->Initialize(spriteCommon);
	h50Sprite->SetPozition({ 400,50 });
	h50Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(25, "EHP50.png");
	h50Sprite->SetTextureIndex(25);
	//BOSSHP
	h49Sprite->Initialize(spriteCommon);
	h49Sprite->SetPozition({ 400,50 });
	h49Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(26, "EHP49.png");
	h49Sprite->SetTextureIndex(26);
	//BOSSHP
	h48Sprite->Initialize(spriteCommon);
	h48Sprite->SetPozition({ 400,50 });
	h48Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(27, "EHP48.png");
	h48Sprite->SetTextureIndex(27);
	//BOSSHP
	h47Sprite->Initialize(spriteCommon);
	h47Sprite->SetPozition({ 400,50 });
	h47Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(28, "EHP47.png");
	h47Sprite->SetTextureIndex(28);
	//BOSSHP
	h46Sprite->Initialize(spriteCommon);
	h46Sprite->SetPozition({ 400,50 });
	h46Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(29, "EHP46.png");
	h46Sprite->SetTextureIndex(29);
	//BOSSHP
	h45Sprite->Initialize(spriteCommon);
	h45Sprite->SetPozition({ 400,50 });
	h45Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(30, "EHP45.png");
	h45Sprite->SetTextureIndex(30);
	//BOSSHP
	h44Sprite->Initialize(spriteCommon);
	h44Sprite->SetPozition({ 400,50 });
	h44Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(31, "EHP44.png");
	h44Sprite->SetTextureIndex(31);
	//BOSSHP
	h43Sprite->Initialize(spriteCommon);
	h43Sprite->SetPozition({ 400,50 });
	h43Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(32, "EHP43.png");
	h43Sprite->SetTextureIndex(32);
	//BOSSHP
	h42Sprite->Initialize(spriteCommon);
	h42Sprite->SetPozition({ 400,50 });
	h42Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(33, "EHP42.png");
	h42Sprite->SetTextureIndex(33);
	//BOSSHP
	h41Sprite->Initialize(spriteCommon);
	h41Sprite->SetPozition({ 400,50 });
	h41Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(34, "EHP41.png");
	h41Sprite->SetTextureIndex(34);
	//BOSSHP
	h40Sprite->Initialize(spriteCommon);
	h40Sprite->SetPozition({ 400,50 });
	h40Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(35, "EHP40.png");
	h40Sprite->SetTextureIndex(35);
	//BOSSHP
	h39Sprite->Initialize(spriteCommon);
	h39Sprite->SetPozition({ 400,50 });
	h39Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(36, "EHP39.png");
	h39Sprite->SetTextureIndex(36);
	//BOSSHP
	h38Sprite->Initialize(spriteCommon);
	h38Sprite->SetPozition({ 400,50 });
	h38Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(37, "EHP38.png");
	h38Sprite->SetTextureIndex(37);
	//BOSSHP
	h37Sprite->Initialize(spriteCommon);
	h37Sprite->SetPozition({ 400,50 });
	h37Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(38, "EHP37.png");
	h37Sprite->SetTextureIndex(38);
	//BOSSHP
	h36Sprite->Initialize(spriteCommon);
	h36Sprite->SetPozition({ 400,50 });
	h36Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(39, "EHP36.png");
	h36Sprite->SetTextureIndex(39);
	////BOSSHP
	h35Sprite->Initialize(spriteCommon);
	h35Sprite->SetPozition({ 400,50 });
	h35Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(40, "EHP35.png");
	h35Sprite->SetTextureIndex(40);
	//BOSSHP
	h34Sprite->Initialize(spriteCommon);
	h34Sprite->SetPozition({ 400,50 });
	h34Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(41, "EHP34.png");
	h34Sprite->SetTextureIndex(41);
	//BOSSHP
	h33Sprite->Initialize(spriteCommon);
	h33Sprite->SetPozition({ 400,50 });
	h33Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(42, "EHP33.png");
	h33Sprite->SetTextureIndex(42);
	//BOSSHP
	h32Sprite->Initialize(spriteCommon);
	h32Sprite->SetPozition({ 400,50 });
	h32Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(43, "EHP32.png");
	h32Sprite->SetTextureIndex(43);
	//BOSSHP
	h31Sprite->Initialize(spriteCommon);
	h31Sprite->SetPozition({ 400,50 });
	h31Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(44, "EHP31.png");
	h31Sprite->SetTextureIndex(44);
	//BOSSHP
	h30Sprite->Initialize(spriteCommon);
	h30Sprite->SetPozition({ 400,50 });
	h30Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(45, "EHP30.png");
	h30Sprite->SetTextureIndex(45);
	//BOSSHP
	h29Sprite->Initialize(spriteCommon);
	h29Sprite->SetPozition({ 400,50 });
	h29Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(46, "EHP29.png");
	h29Sprite->SetTextureIndex(46);
	//BOSSHP
	h28Sprite->Initialize(spriteCommon);
	h28Sprite->SetPozition({ 400,50 });
	h28Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(47, "EHP28.png");
	h28Sprite->SetTextureIndex(47);
	//BOSSHP
	h27Sprite->Initialize(spriteCommon);
	h27Sprite->SetPozition({ 400,50 });
	h27Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(48, "EHP27.png");
	h27Sprite->SetTextureIndex(48);
	//BOSSHP
	h26Sprite->Initialize(spriteCommon);
	h26Sprite->SetPozition({ 400,50 });
	h26Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(49, "EHP26.png");
	h26Sprite->SetTextureIndex(49);
	//BOSSHP
	h25Sprite->Initialize(spriteCommon);
	h25Sprite->SetPozition({ 400,50 });
	h25Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(50, "EHP25.png");
	h25Sprite->SetTextureIndex(50);
	//BOSSHP
	h24Sprite->Initialize(spriteCommon);
	h24Sprite->SetPozition({ 400,50 });
	h24Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(51, "EHP24.png");
	h24Sprite->SetTextureIndex(51);
	//BOSSHP
	h23Sprite->Initialize(spriteCommon);
	h23Sprite->SetPozition({ 400,50 });
	h23Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(52, "EHP23.png");
	h23Sprite->SetTextureIndex(52);
	//BOSSHP
	h22Sprite->Initialize(spriteCommon);
	h22Sprite->SetPozition({ 400,50 });
	h22Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(53, "EHP22.png");
	h22Sprite->SetTextureIndex(53);
	//BOSSHP
	h21Sprite->Initialize(spriteCommon);
	h21Sprite->SetPozition({ 400,50 });
	h21Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(54, "EHP21.png");
	h21Sprite->SetTextureIndex(54);
	//BOSSHP
	h20Sprite->Initialize(spriteCommon);
	h20Sprite->SetPozition({ 400,50 });
	h20Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(55, "EHP20.png");
	h20Sprite->SetTextureIndex(55);
	//BOSSHP
	h19Sprite->Initialize(spriteCommon);
	h19Sprite->SetPozition({ 400,50 });
	h19Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(56, "EHP19.png");
	h19Sprite->SetTextureIndex(56);
	//BOSSHP
	h18Sprite->Initialize(spriteCommon);
	h18Sprite->SetPozition({ 400,50 });
	h18Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(57, "EHP18.png");
	h18Sprite->SetTextureIndex(57);
	//BOSSHP
	h17Sprite->Initialize(spriteCommon);
	h17Sprite->SetPozition({ 400,50 });
	h17Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(75, "EHP17.png");
	h17Sprite->SetTextureIndex(75);
	//BOSSHP
	h16Sprite->Initialize(spriteCommon);
	h16Sprite->SetPozition({ 400,50 });
	h16Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(58, "EHP16.png");
	h16Sprite->SetTextureIndex(58);
	//BOSSHP
	h15Sprite->Initialize(spriteCommon);
	h15Sprite->SetPozition({ 400,50 });
	h15Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(59, "EHP15.png");
	h15Sprite->SetTextureIndex(59);
	//BOSSHP
	h14Sprite->Initialize(spriteCommon);
	h14Sprite->SetPozition({ 400,50 });
	h14Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(60, "EHP14.png");
	h14Sprite->SetTextureIndex(60);
	//BOSSHP
	h13Sprite->Initialize(spriteCommon);
	h13Sprite->SetPozition({ 400,50 });
	h13Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(61, "EHP13.png");
	h13Sprite->SetTextureIndex(61);
	//BOSSHP
	h12Sprite->Initialize(spriteCommon);
	h12Sprite->SetPozition({ 400,50 });
	h12Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(62, "EHP12.png");
	h12Sprite->SetTextureIndex(62);
	//BOSSHP
	h11Sprite->Initialize(spriteCommon);
	h11Sprite->SetPozition({ 400,50 });
	h11Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(63, "EHP11.png");
	h11Sprite->SetTextureIndex(63);
	//BOSSHP
	h10Sprite->Initialize(spriteCommon);
	h10Sprite->SetPozition({ 400,50 });
	h10Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(64, "EHP10.png");
	h10Sprite->SetTextureIndex(64);
	//BOSSHP
	h9Sprite->Initialize(spriteCommon);
	h9Sprite->SetPozition({ 400,50 });
	h9Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(65, "EHP9.png");
	h9Sprite->SetTextureIndex(65);
	//BOSSHP
	h8Sprite->Initialize(spriteCommon);
	h8Sprite->SetPozition({ 400,50 });
	h8Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(66, "EHP8.png");
	h8Sprite->SetTextureIndex(66);
	//BOSSHP
	h7Sprite->Initialize(spriteCommon);
	h7Sprite->SetPozition({ 400,50 });
	h7Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(67, "EHP7.png");
	h7Sprite->SetTextureIndex(67);
	//BOSSHP
	h6Sprite->Initialize(spriteCommon);
	h6Sprite->SetPozition({ 400,50 });
	h6Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(68, "EHP6.png");
	h6Sprite->SetTextureIndex(68);
	//BOSSHP
	h5Sprite->Initialize(spriteCommon);
	h5Sprite->SetPozition({ 400,50 });
	h5Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(69, "EHP5.png");
	h5Sprite->SetTextureIndex(69);
	//BOSSHP
	h4Sprite->Initialize(spriteCommon);
	h4Sprite->SetPozition({ 400,50 });
	h4Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(70, "EHP4.png");
	h4Sprite->SetTextureIndex(70);
	//BOSSHP
	h3Sprite->Initialize(spriteCommon);
	h3Sprite->SetPozition({ 400,50 });
	h3Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(71, "EHP3.png");
	h3Sprite->SetTextureIndex(71);
	//BOSSHP
	h2Sprite->Initialize(spriteCommon);
	h2Sprite->SetPozition({ 400,50 });
	h2Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(72, "EHP2.png");
	h2Sprite->SetTextureIndex(72);
	//BOSSHP
	h1Sprite->Initialize(spriteCommon);
	h1Sprite->SetPozition({ 400,50 });
	h1Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(73, "EHP1.png");
	h1Sprite->SetTextureIndex(73);
	//BOSSHP
	h0Sprite->Initialize(spriteCommon);
	h0Sprite->SetPozition({ 400,50 });
	h0Sprite->SetSize({ 500.0f, 30.0f });
	spriteCommon->LoadTexture(74, "EHP0.png");
	h0Sprite->SetTextureIndex(74);
	

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
			if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(B)) {
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
					sceneNo_ = SceneNo::BOSS;
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

		//シーン切り替え
		if (boss_->GetBossHP() >= 50)
		{
			clearflag = 1;
			if (clearflag == true) {
				ClearMove();
				clearSceneTimer++;
				if (clearSceneTimer >= 100) {
					enemy_->playerHp = 15;
					clearTimer++;
					if (clearTimer >= 1) {
						enemy_->enemyCount = 0;
						boss_->BossCount = 0;
						
						
						sceneNo_ = SceneNo::CLEAR;
					}
				}
			}
		}
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
				if (input->TriggerKey(DIK_SPACE) || input->PButtonTrigger(B)) {
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
			if (overFlag == false) {
				enemy_->EffDraw();
				enemy_->FbxDraw();
			}
			player_->FbxDraw();

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
			if (boss_->GetBossHP() <= 49) {
				boss_->FbxDraw();
			}

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
			if (boss_->GetBossHP() == 0) {
				h50Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 1) {
				h49Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 2) {
				h48Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 3) {
				h47Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 4) {
				h46Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 5) {
				h45Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 6) {
				h44Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 7) {
				h43Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 8) {
				h42Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 9) {
				h41Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 10) {
				h40Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 11) {
				h39Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 12) {
				h38Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 13) {
				h37Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 14) {
				h36Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 15) {
				h35Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 16) {
				h34Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 17) {
				h33Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 18) {
				h32Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 19) {
				h31Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 20) {
				h30Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 21) {
				h29Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 22) {
				h28Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 23) {
				h27Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 24) {
				h26Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 25) {
				h25Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 26) {
				h24Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 27) {
				h23Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 28) {
				h22Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 29) {
				h21Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 30) {
				h20Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 31) {
				h19Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 32) {
				h18Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 33) {
				h17Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 34) {
				h16Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 35) {
				h15Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 36) {
				h14Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 37) {
				h13Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 38) {
				h12Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 39) {
				h11Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 40) {
				h10Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 41) {
				h9Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 42) {
				h8Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 43) {
				h7Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 44) {
				h6Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 45) {
				h5Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 46) {
				h4Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 47) {
				h3Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 48) {
				h2Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 49) {
				h1Sprite->Draw();
			}
			else if (boss_->GetBossHP() == 50) {
				h0Sprite->Draw();
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