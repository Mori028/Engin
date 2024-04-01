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
	//������
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
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

	Vector3 GetEne2WorldPosition();

	Vector3 GetEne3WorldPosition();

	Vector3 GetEne4WorldPosition();

	//�����蔻��
	void OnColision1();
	void OnColision2();
	void OnColision3();
	void OnColision4();

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { fbxObject3d_->wtf.position = pos; };
	void SetPlayer(Player* player) { player_ = player; };
public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
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
	//�G4
	FBXObject3d* enemy2Object3d_ = nullptr;

	//����
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�G�̃X�s�[�h
	const float moveSpeed_ = 0.01f;
	const float rotaSpeed_ = 0.1f;
	//�G�֘A
	float timer1 = 0;
	float timer2 = 0;
	float timer3 = 0;
	float timer4 = 0;

	bool liveFlag1 = true;
	bool liveFlag2 = true;
	bool liveFlag3 = true;
	bool liveFlag4 = true;

	//�p�[�e�B�N���N���X�̏����� 
	//�_���[�W
	std::unique_ptr<ParticleManager> particleManager;

	//���[���h���W������ϐ�
	Vector3 worldPos;

};