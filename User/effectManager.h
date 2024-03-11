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

/*
* @file effectManager.h
* @brind �G�t�F�N�g�Ȃ�
*/
class Player;

class EffectManager {
public:
	EffectManager();
public:
	//������
	void Initialize(DirectXCommon* dxCommon, MyEngine::Input* input);
	void Update();
	//�p�[�e�B�N���X�V
	void EffUpdate();
	//�o�[�e�B�N���`��
	void EffDraw();

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

	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//�p�[�e�B�N���֘A
	int effTimer = 0;
	int isEffFlag = 0;
	//�p�[�e�B�N���N���X�̏����� 
	//�_���[�W
	std::unique_ptr<ParticleManager> particleManager;

	//���[���h���W������ϐ�
	Vector3 worldPos;

};