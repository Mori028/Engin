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
	//�{�X�̍U��
	void ModeChange();
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
	Vector3 GetBullet4WorldPosition();
	Vector3 GetBullet5WorldPosition();
	Vector3 GetBullet6WorldPosition();
	Vector3 GetBullet7WorldPosition();
	Vector3 GetBullet8WorldPosition();
	Vector3 GetBullet9WorldPosition();
	Vector3 GetBullet10WorldPosition();
	Vector3 GetBullet11WorldPosition();
	Vector3 GetBullet12WorldPosition();
	Vector3 GetBullet13WorldPosition();
	Vector3 GetBullet14WorldPosition();

	void OnColisionPlayer();

public:

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { enemyBullet3Obj_->wtf.position = pos; };
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
	//�e4
	Object3d* enemyBullet3Obj_ = nullptr;
	Model* enemyBullet3Model_ = nullptr;
	//�e5
	Object3d* enemyBullet4Obj_ = nullptr;
	Model* enemyBullet4Model_ = nullptr;
	//�e6
	Object3d* enemyBullet5Obj_ = nullptr;
	Model* enemyBullet5Model_ = nullptr;
	//�e7
	Object3d* enemyBullet6Obj_ = nullptr;
	Model* enemyBullet6Model_ = nullptr;
	//�e8
	Object3d* enemyBullet7Obj_ = nullptr;
	Model* enemyBullet7Model_ = nullptr;
	//�e9
	Object3d* enemyBullet8Obj_ = nullptr;
	Model* enemyBullet8Model_ = nullptr;
	//�e10
	Object3d* enemyBullet9Obj_ = nullptr;
	Model* enemyBullet9Model_ = nullptr;
	//�e11
	Object3d* enemyBullet10Obj_ = nullptr;
	Model* enemyBullet10Model_ = nullptr;
	//�e12
	Object3d* enemyBullet11Obj_ = nullptr;
	Model* enemyBullet11Model_ = nullptr;
	//�e13
	Object3d* enemyBullet12Obj_ = nullptr;
	Model* enemyBullet12Model_ = nullptr;
	//�e14
	Object3d* enemyBullet13Obj_ = nullptr;
	Model* enemyBullet13Model_ = nullptr;
	//�e15
	Object3d* enemyBullet14Obj_ = nullptr;
	Model* enemyBullet14Model_ = nullptr;

	//��΂��܂ł̎��Ԃƃt���O
	int crystalTimer;
	bool isLive = false;
	int shotTimer;

	//����
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�e�̃t���O
	bool isShootFlag = false;
	float bulletTimer = 0;
	//�G�̃X�s�[�h
	const float moveSpeed_ = 0.01f;
	const float bossMoveSpeed_ = 0.06f;
	const float rotaSpeed_ = 0.1f;
	float shortSpeed = 0.05f;
	float shortXSpeed = 0.005f;
	//�G�֘A
	float timer = 0;
	int hp = 1;
	int bulletMode = 1;
	float changeTimer = 0;
	bool liveFlag = true;
	bool mode = false;
	int bossTimer = 0;
	bool bossAttack = true;
	bool verticalAttack = true;
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