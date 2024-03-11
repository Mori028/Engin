#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

#include "ParticleManager.h"
#include "Audio.h"
#include "Collision.h"


/*
* @file bullet.h
* @brind �G�̍U��
*/
class Player;
class Enemys;

class Bullet {
public:
	//������
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//���Z�b�g
	void Reset();
	//�Q�[���N���A
	void Clear();
	//�Q�[���I�[�o�[
	void Over();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�p�[�e�B�N���X�V
	void EffUpdate();
	//�o�[�e�B�N���`��
	void EffDraw();

	//�e�̃��[���h���W���擾
	Vector3 GetBulletWorldPosition();
	Vector3 GetBullet1WorldPosition();
	Vector3 GetBullet2WorldPosition();
	Vector3 GetBullet3WorldPosition();

	void OnColisionPlayer();

public:

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPlayer(Player* player) { player_ = player; };
	void SetEnemys(Enemys* enemys) { enemys_ = enemys; };

	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	Player* player_ = nullptr;
	Enemys* enemys_ = nullptr;
	Collision coll;

	//�e
	Object3d* enemyBulletObj_ = nullptr;
	Model* enemyBulletModel_ = nullptr;
	//�e2
	Object3d* enemyBullet1Obj_ = nullptr;
	Model* enemyBullet1Model_ = nullptr;
	//�e3
	Object3d* enemyBullet2Obj_ = nullptr;
	Model* enemyBullet2Model_ = nullptr;
	// ���@�_���e
	Object3d* enemyBullet3Obj_ = nullptr;
	Model* enemyBullet3Model_ = nullptr;

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
	bool liveFlag = true;
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