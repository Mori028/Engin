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

	//クリア
	Sprite* clearSprite = new Sprite();

	//ゲームオーバー
	Sprite* overSprite = new Sprite();
	//Hp
	Sprite* HPSprite = new Sprite();


	//カメラ
	Camera* mainCamera = nullptr;
	Camera* camera1 = nullptr;
	Camera* camera2 = nullptr;
	Camera* camera3 = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

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
	
	//UI
	
	//ゲームフロー
};