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
* @file enemy.h
* @brind �G�̓����Ȃ�
*/
class Player;

class Enemy {
public:
	Enemy();
	~Enemy();
public:
	//������
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//���Z�b�g
	void Reset();
	//�Q�[���I�[�o�[
	void Over();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//FBX�̕`��
	void FbxDraw();
	//�p�[�e�B�N���X�V
	void EffUpdate();
	//�o�[�e�B�N���`��
	void EffDraw();

	////���[���h���W���擾
	Vector3 GetWorldPosition();

	Vector3 GetEne2WorldPosition();

	Vector3 GetEne3WorldPosition();

	//�e�̃��[���h���W���擾
	Vector3 GetBulletWorldPosition();

	void OnColision();
	void OnColisionPlayer();

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { fbxObject3d_->wtf.position = pos; };
	void SetPlayer(Player* player) { player_ = player; };
public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	int GetPlayerHP() { return playerHp; }

	int GetEnemyHP() { return enemyCount; }

	//player��HP
	int playerHp = 15;
	//enemy�̐�
	int enemyCount = 0;

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;
	Collision coll;
	//�G1
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	//�G2
	FBXModel* fbxredModel_ = nullptr;
	FBXObject3d* enemyObject3d_ = nullptr;
	//�G3
	FBXModel* fbxwhiteModel_ = nullptr;
	FBXObject3d* enemy1Object3d_ = nullptr;

	//�e
	Object3d* enemyBulletObj_ = nullptr;
	Model* enemyBulletModel_ = nullptr;
	//����
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�e�̃t���O
	bool isShootFlag = false;
	float bulletTimer = 0;
	//�G�̃X�s�[�h
	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;
	//�G�֘A
	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	int liveFlag = 1;

	//�p�[�e�B�N���֘A
	int effTimer = 0;
	int isEffFlag = 0;
	//�p�[�e�B�N���N���X�̏����� 
	//�_���[�W
	std::unique_ptr<ParticleManager> particleManager;
	
	//���[���h���W������ϐ�
	Vector3 worldPos;

};