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
* @brind �G�̓o��Ȃ�
*/

class Fade {

public:
	//������
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	//���Z�b�g
	void Reset();
	//�Q�[���I�[�o�[
	void Over();
	//�X�V
	void Update();
	//FBX�̕`��
	void FbxDraw();

private:
	const float PI = 3.141592f;
	MyEngine::Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	//�G1
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//�����X�s�[�h
	const float moveSpeed_ = 0.01f;
	const float fadeSpeed_ = 0.45f;
	const float rotaSpeed_ = 0.1f;
	const float attackMoveSpeed_ = 0.30f;
	float timer = 0;
	bool move = true;

	//�G�̓o��
	float entryTimer = 300.0f;
	int entry = 1;

	//���[���h���W������ϐ�
	Vector3 worldPos;

};