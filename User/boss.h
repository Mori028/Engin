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
* @file boss.h
* @brind �{�X�̓����Ȃ�
*/
class Player;

class Boss {
public:
	Boss();
	~Boss();
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
	////���[���h���W���擾
	Vector3 GetWorldPosition();

	//�e�̃��[���h���W���擾
	Vector3 GetBulletWorldPosition();
	//�����蔻��
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
	//player��HP�Ǘ�
	int GetPlayerHP() { return playerHp; }
	//enemy��HP�Ǘ�
	int GetBossHP() { return BossCount; }

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

	//�e
	Object3d* BossBulletObj_ = nullptr;
	Model* BossBulletModel_ = nullptr;

	//��
	Object3d* BossWallObj_ = nullptr;
	Model* BossWallModel_ = nullptr;
	//����
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�e�̃t���O
	bool isShootFlag = false;
	float bulletTimer = 0;
	//�����X�s�[�h
	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;
	const float attackMoveSpeed_ = 0.30f;
	float timer = 0;
	//�G��HP
	int hp = 1;
	//�U���̎��
	int bulletMode = 1;
	float changeTimer = 0;
	//�������Ă��邩
	int liveFlag = 1;
	float enemyTimer = 0.0f;
	int returnFlag = 0;
	//�U�������Ă��邩
	int attackFlag = 0;
	//�G�̓o��
	float entryTimer = 300.0f;
	int entry = 1;

	//HP
	//playerHP
	int playerHp = 15;//hp0��3
	//BossCount
	int BossCount = 0;

	//���[���h���W������ϐ�
	Vector3 worldPos;

};