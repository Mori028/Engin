#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"

#include "FBXModel.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "Collision.h"

/*
* @file Enemys.h
* @brind �G�̓����Ȃ�
*/
class Player;

class Enemys {
public:
	//������
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	
	//�X�V
	void Update();
	//�`��
	void Draw();

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { EnemysObj_->wtf.position = pos; };
	void SetPlayer(Player* player) { player_ = player; };
	
public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	int GetPlayerHP() { return playerHp; }

	int GetEnemysHP() { return EnemysCount; }

	//player��HP
	int playerHp = 15;
	//Enemys�̐�
	int EnemysCount = 0;



private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;
	Collision coll;
	
	//�e
	Object3d* EnemysObj_ = nullptr;
	Model* EnemysModel_ = nullptr;

	//����
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�e�̃t���O
	bool isShootFlag = false;
	float bulletTimer = 0;
	//�G�̃X�s�[�h
	const float moveSpeed_ = 0.05f;
	const float rotaSpeed_ = 0.1f;
	//�G�֘A
	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	bool liveFlag = true;
	//�G�̌��j��
	int downTimer = 0;
	int downRotate = 0;
	bool dounDraw = false;
	//�N���A��
	int ClearMove = 0;
	//�p�[�e�B�N���֘A
	int effTimer = 0;
	int isEffFlag = 0;
	//�p�[�e�B�N���N���X�̏����� 
	//�_���[�W
	std::unique_ptr<ParticleManager> particleManager;

	//���[���h���W������ϐ�
	Vector3 worldPos;

};