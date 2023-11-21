#pragma once
#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"
#include <player.h>

/*
* @file playerBullet.h
* @brind �v���C���[�̍U��
*/
class Player;

class Bullet {
public:
	Bullet();
	~Bullet();
public:
	//������
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//�X�V
	void Update();
	//�e�̋���
	void Move();
	//�`��
	void Draw();

	//��
	Vector3 bVelocity(Vector3& velocity, Transform& worldTransform);

	//�e�̃��[���h���W���擾
	Vector3 GetBulletWorldPosition();
	void SetPlayer(Player* player) { player_ = player; };
public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	//�v���C���[
	Player* player_ = nullptr;
	//�X�^�[�g���o
	int stoptimer = 0;
	bool moovFlag = false;
	//�e
	Object3d* bulletObj_ = nullptr;
	Model* bulletModel_ = nullptr;
	Vector3 enemyDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�e�̃t���O
	bool isShootFlag = false;
	
	//�J����
	float camMoveSpeed = 0.2f;
	Vector2 camRotaSpeed = { PI / 1800, PI / 1800 };

	//���[���h���W������ϐ�
	Vector3 worldPos;

};