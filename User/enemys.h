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
#include "ParticleManager.h"
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

	//FBX�̕`��
	void FbxDraw();
	bool IsDead() const { return isDead_; }
	//�����蔻��
	void OnColision();
	////���[���h���W���擾
	Vector3 GetWorldPosition();

	Vector3 GetPos() { return EnemysObject3d_->wtf.position; };
	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { EnemysObject3d_->wtf.position = pos; };
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
	
	//�G
	FBXModel* EnemysModel_ = nullptr;
	FBXObject3d* EnemysObject3d_ = nullptr;

	bool MaxX = true;
	bool MinX = false;
	bool MaxY = false;
	bool MinY = false;

	//�s������
	const float PosXMax = 0.09f;
	const float PosXMin = -0.09f;
	const float PosYMax = 0.04f;
	const float PosYMin = -0.2f;
	//����
	Vector3 playerDistance;
	Vector3 distance;
	float bulletCoolTime = 0;
	//�e�̃t���O
	bool isShootFlag = false;
	float bulletTimer = 0;
	//�G�̃X�s�[�h
	const float moveSpeed_ = 0.001f;
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

	// �f�X�t���O
	bool isDead_ = false;

	// �f�X�^�C�}�[
	int32_t dethTimer_ = lifeTime_;

	static const int32_t lifeTime_ = 50 * 5;

	static const int32_t Hp_ = 1;
	int32_t dethHp_ = Hp_;

	//���[���h���W������ϐ�
	Vector3 worldPos;

};