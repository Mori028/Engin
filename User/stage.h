#pragma once
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Input.h"
#include "Camera.h"

/*
* @file stage.h
* @brind �X�e�[�W�z�u�Ȃ�
*/
class Stage {
public:
	Stage();
	~Stage();
	//������
	void Initialize(DirectXCommon* dxCommon, Input* input);
	//���Z�b�g
	void Reset();
	//�X�e�[�W�̃��[�v
	void Loop();
	//�Q�[���I�[�o�[���ɓ������~�߂�
	void Over();
	//�X�V
	void Update();
	//�`��
	void Draw();

	/// <summary>
	/// �|�W�V����
	/// </summary>
	/// <param name="pos"></param>
	void SetPos(Vector3 pos) { stage_->wtf.position = pos; };
	void SetCamera(Camera* cam) { camera = cam; };

private:
	const float PI = 3.141592f;
	Input* input_ = nullptr;
	DirectXCommon* dxCommon = nullptr;
	//�X�e�[�W�̃��f��
	Object3d* stage_ = nullptr;
	Object3d* stage2_ = nullptr;
	Object3d* stage3_ = nullptr;
	Object3d* stage4_ = nullptr;
	Object3d* stage5_ = nullptr;
	Object3d* stage6_ = nullptr;
	Object3d* stage7_ = nullptr;
	Object3d* stage8_ = nullptr;
	Object3d* stage9_ = nullptr;
	Object3d* stage10_ = nullptr;
	Model* felld = nullptr;
	//�X�e�[�W�̐i�ރX�s�[�h
	const float moveSpeed_ = 0.53f;
	const float rotaSpeed_ = 0.1f;
	int moveFlag = 1;
	//�J�����֘A
	Camera* camera = nullptr;
	Transform* camTransForm = nullptr;
	Vector3 targetPos;
	Vector3 eyePos;
	Vector3 centerPos;
	float targetTheta;
	float targetDistance = 10;
	float camMoveSpeed = 0.2f;

	Vector2 camRotaSpeed = { PI / 1800, PI / 1800 };

	//���[���h���W������ϐ�
	Vector3 worldPos;

};