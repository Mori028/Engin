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

#include "ParticleManager.h"

#include "Player.h"
#include "enemy.h"
#include "stage.h"
#include <boss.h>
#include <title.h>
#include "playerBullet.h"

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
	void Initialize(DirectXCommon* dxCommon, Input* input);

	void Reset();

	void FadeOut();
	void FadeIn();
	void Over();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };


private: // メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


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

	//クリア
	Sprite* clearSprite = new Sprite();

	//ゲームオーバー
	Sprite* blackSprite = new Sprite();
	Sprite* overSprite = new Sprite();
	Sprite* over2Sprite = new Sprite();
	Sprite* over3Sprite = new Sprite();
	//Hp
	Sprite* hPSprite = new Sprite();
	//Hp
	Sprite* hP2Sprite = new Sprite();
	//Hp
	Sprite* hP1Sprite = new Sprite();
	//Hp
	Sprite* hP0Sprite = new Sprite();

	//フェードイン＆フェードアウト
	Sprite* outSprite = new Sprite();
	Sprite* out1Sprite = new Sprite();
	Sprite* out2Sprite = new Sprite();
	Sprite* out3Sprite = new Sprite();
	Sprite* out4Sprite = new Sprite();
	Sprite* out5Sprite = new Sprite();
	int fadeCount = 0;
	int outTimer = 0;
	int fadeFlag = 0;
	int fadeTimer = 0;
	//ゲームスタート
	int roadTimer = 0;
	 
	//カウント
	Sprite* start3Sprite = new Sprite();

	//ゲームオーバー
	int overFlag = 0;
	int retryFlag = 0;

	Sprite* goSprite = new Sprite();
	Sprite* go2Sprite = new Sprite();
	int startCountTimer = 0;
	int startCountFlag = 0;
	int startCount = 0;
	int startTimer = 0;
	int startFlag = 0;
	//カメラ
	Camera* mainCamera = nullptr;
	Camera* camera1 = nullptr;
	Camera* camera2 = nullptr;
	Camera* camera3 = nullptr;

	//タイトル
	Title* title_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

	//プレイヤーの弾
	PlayerBullet* playerBullet_ = nullptr;

	//プレイヤー
	Enemy* enemy_ = nullptr;

	//ステージ
	Stage* stage_ = nullptr;

	//ボス
	Boss* boss_ = nullptr;

	//背景や床
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	const float skyMoveSpeed_ = 0.15f;

	int titleTimer = 0;
	int overTimer = 0;
	//UI
	
	//ゲームフロー
};