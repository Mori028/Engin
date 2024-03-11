#pragma once

#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <string>
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"

#include "Matrix4.h"
#include "Camera.h"
#include <sstream>
#include "ParticleManager.h"

#include "Player.h"
#include "stage.h"
#include <boss.h>
#include <title.h>
#include "Bullet.h"
#include <clear.h>
#include <enemys.h>
#include <GameScene.h>
#include "effectManager.h"
/*
* @file GameScene.h
* @brind ゲームの本体
*/
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // 静的メンバ変数
	//static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);

	void Reset();


	void FadeOut();
	void FadeIn();
	void Over();
	void ClearMove();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//パーティクル更新
	void EffUpdate();
	//バーティクル描画
	void EffDraw();

	/// <summary>
	/// 敵発生
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdataEnemyPopCommands();

	/// <summary>
	/// 敵の発生
	/// </summary>
	void GenerEnemy(Vector3 EnemyPos);


	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	void OnColision();

	void OnColisionPlayer();

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	//待機中フラグ
	bool isStand_ = false;

	//待機タイマー
	int standTime_ = 0;

	void SetPlayer(Player* player) { player_ = player; };
	//敵のリスト
	const std::list<std::unique_ptr<Enemys>>& GetEnemys() { return enemys_; }

public:

	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };


private: // メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;
	MyEngine::Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	Collision coll;

private:	//メンバ変数
	const float PI = 3.141592f;

	//シーン切り替え
	enum class SceneNo {
		TITLE, //タイトル
		GAME, //ゲームシーン
		BOSS, //ボス
		CLEAR, //クリア
		GAMEOVER //ゲームオーバー
	};
	//ゲーム制作中はgameシーンにする
	SceneNo sceneNo_ = SceneNo::TITLE;

	//タイトル
	Sprite* titleSprite = new Sprite();
	Sprite* spaceSprite = new Sprite();
	Sprite* titleBSprite = new Sprite();
	//クリア
	Sprite* clearSprite = new Sprite();
	Sprite* conSprite = new Sprite();
	Sprite* backSprite = new Sprite();
	//ゲームオーバー
	Sprite* blackSprite = new Sprite();
	Sprite* overSprite = new Sprite();
	Sprite* over2Sprite = new Sprite();
	Sprite* over3Sprite = new Sprite();
	//Hp3
	Sprite* hPSprite = new Sprite();
	//Hp2
	Sprite* hP2Sprite = new Sprite();
	//Hp1
	Sprite* hP1Sprite = new Sprite();
	//Hp0
	Sprite* hP0Sprite = new Sprite();
	//ダメージ
	Sprite* damageSprite = new Sprite();

	//フェードイン＆フェードアウト
	Sprite* outSprite = new Sprite();
	Sprite* out1Sprite = new Sprite();
	Sprite* out2Sprite = new Sprite();
	Sprite* out3Sprite = new Sprite();
	Sprite* out4Sprite = new Sprite();
	Sprite* out5Sprite = new Sprite();

	//bossHP
	Sprite* h50Sprite = new Sprite();
	Sprite* h49Sprite = new Sprite();
	Sprite* h48Sprite = new Sprite();
	Sprite* h47Sprite = new Sprite();
	Sprite* h46Sprite = new Sprite();
	Sprite* h45Sprite = new Sprite();
	Sprite* h44Sprite = new Sprite();
	Sprite* h43Sprite = new Sprite();
	Sprite* h42Sprite = new Sprite();
	Sprite* h41Sprite = new Sprite();
	Sprite* h40Sprite = new Sprite();
	Sprite* h39Sprite = new Sprite();
	Sprite* h38Sprite = new Sprite();
	Sprite* h37Sprite = new Sprite();
	Sprite* h36Sprite = new Sprite();
	Sprite* h35Sprite = new Sprite();
	Sprite* h34Sprite = new Sprite();
	Sprite* h33Sprite = new Sprite();
	Sprite* h32Sprite = new Sprite();
	Sprite* h31Sprite = new Sprite();
	Sprite* h30Sprite = new Sprite();
	Sprite* h29Sprite = new Sprite();
	Sprite* h28Sprite = new Sprite();
	Sprite* h27Sprite = new Sprite();
	Sprite* h26Sprite = new Sprite();
	Sprite* h25Sprite = new Sprite();
	Sprite* h24Sprite = new Sprite();
	Sprite* h23Sprite = new Sprite();
	Sprite* h22Sprite = new Sprite();
	Sprite* h21Sprite = new Sprite();
	Sprite* h20Sprite = new Sprite();
	Sprite* h19Sprite = new Sprite();
	Sprite* h18Sprite = new Sprite();
	Sprite* h17Sprite = new Sprite();
	Sprite* h16Sprite = new Sprite();
	Sprite* h15Sprite = new Sprite();
	Sprite* h14Sprite = new Sprite();
	Sprite* h13Sprite = new Sprite();
	Sprite* h12Sprite = new Sprite();
	Sprite* h11Sprite = new Sprite();
	Sprite* h10Sprite = new Sprite();
	Sprite* h9Sprite = new Sprite();
	Sprite* h8Sprite = new Sprite();
	Sprite* h7Sprite = new Sprite();
	Sprite* h6Sprite = new Sprite();
	Sprite* h5Sprite = new Sprite();
	Sprite* h4Sprite = new Sprite();
	Sprite* h3Sprite = new Sprite();
	Sprite* h2Sprite = new Sprite();
	Sprite* h1Sprite = new Sprite();
	Sprite* h0Sprite = new Sprite();
	
	//playerのHP
	int playerHp = 15;

	int fadeCount = 0;
	int outTimer = 0;
	bool fadeFlag = false;
	int fadeTimer = 0;
	//ゲームスタート
	int roadTimer = 0;
	//カウント
	Sprite* start3Sprite = new Sprite();
	int clearTimer = 0;
	//ゲームクリア
	bool clearflag = false;
	int clearSceneTimer = 0;
	//ゲームオーバー
	bool overFlag = false;
	int retryFlag = 0;//1リプレイ//2タイトル

	Sprite* goSprite = new Sprite();
	Sprite* go2Sprite = new Sprite();
	int startCountTimer = 0;
	bool startCountFlag = false;
	int startCount = 0;
	int startTimer = 0;
	bool startFlag = false;
	//カメラ
	Camera* mainCamera = nullptr;
	Camera* camera1 = nullptr;
	Camera* camera2 = nullptr;
	Camera* camera3 = nullptr;
	//クリア時のカメラ
	int clearCameraTimer = 0;

	//タイトル
	Title* title_ = nullptr;

	//タイトル
	Clear* clear_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

	//プレイヤーの弾
	Bullet* bullet_ = nullptr;

	//ステージ
	Stage* stage_ = nullptr;

	//ボス
	Boss* boss_ = nullptr;

	// 敵キャラ
	std::list<std::unique_ptr<Enemys>> enemys_;

	//倒した敵のカウント
	int EnemyCount = 0;

	//パーティクル関連
	int effTimer = 0;
	int isEffFlag = 0;
	//パーティクルクラスの初期化 
	//ダメージ
	std::unique_ptr<ParticleManager> particleManager;

	//背景や床
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	const float skyMoveSpeed_ = 0.15f;

	int titleTimer = 0;
	int overTimer = 0;
	//UI
	
	//ゲームフロー
};