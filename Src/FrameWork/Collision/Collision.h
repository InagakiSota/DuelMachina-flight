#pragma once

#include "../Math/Math.h"
#include <SimpleMath.h>

namespace Collision
{
	//AABB�̓����������
	enum eAABB_HIT_STATE
	{
		eAABB_HIT_STATE_LEFT = 1,		//�����瓖����
		eAABB_HIT_STATE_TOP = 4,		//�ォ�瓖����
		eAABB_HIT_STATE_RIGHT = 2,		//�E���瓖����
		eAABB_HIT_STATE_BOTTOM = 8,		//�����瓖����
	};

	//�~�̓����蔻��\����
	struct CircleCollosion
	{
		//���W
		Vec2D pos;

		//���a
		float red;
	};

	//���̓����蔻��\����
	struct BoxCollision
	{
		//���W
		DirectX::SimpleMath::Vector3 pos;
		//���̔���
		DirectX::SimpleMath::Vector3 size_h;
	};

	//���̓����蔻��\����
	struct SphereCollision
	{
		//���W
		DirectX::SimpleMath::Vector3 pos;
		//���a
		float r;
	};

	//�J�v�Z���̓����蔻��\����
	struct CapsuleCollision
	{
		//���S���W
		DirectX::SimpleMath::Vector3 pos;
		//���S�̐����̎n�_
		DirectX::SimpleMath::Vector3 startPos;
		//���S�̐����̏I�_
		DirectX::SimpleMath::Vector3 endPos;
		//���a
		float r;
		//�n�_�A�I�_�܂ł̋���
		float length;
		//�N�H�[�^�j�I��
		DirectX::SimpleMath::Quaternion q;
		//��]��
		DirectX::SimpleMath::Vector3 rotAxis;
		//�p�x
		float rot;
	};

	//�~�Ɖ~�̓����蔻��
	bool CheckCircleCollision(CircleCollosion c1, CircleCollosion c2);

	//AABB
	int AABBCheck(float a1X, float a1Y, float b1X, float b1Y, float a2X, float a2Y, float b2X, float b2Y);

	//3D�̔��Ɣ��̓����蔻��
	bool CheckHitBox2Box(Collision::BoxCollision box1, Collision::BoxCollision box2);

	//���Ƌ��̓����蔻��
	bool CheckHitSphere2Sphere(Collision::SphereCollision sphere1, Collision::SphereCollision sphere2);

	//���ƃJ�v�Z���̓����蔻��
	bool CheckHitSphere2Capsule(Collision::SphereCollision sphere, Collision::CapsuleCollision capsule);

	//�J�v�Z���ƃJ�v�Z���̓����蔻��
	bool CheckHitCapsule2Capsule(Collision::CapsuleCollision capsule1, Collision::CapsuleCollision capsule2);

	// �_c�Ɛ���ab�̊Ԃ̋����̕��������߂�
	float SqDistPointSegment(DirectX::SimpleMath::Vector3 startPos, DirectX::SimpleMath::Vector3 endPos, DirectX::SimpleMath::Vector3 pos);

	// �Q�̐����̍ŒZ�����̕�����Ԃ��֐�
	float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3  p1, DirectX::SimpleMath::Vector3  q1, DirectX::SimpleMath::Vector3  p2,
		DirectX::SimpleMath::Vector3  q2, float &s, float &t, 
		DirectX::SimpleMath::Vector3 & c1, DirectX::SimpleMath::Vector3 & c2);

	//�J�v�Z���̊p�x����n�_�A�I�_�̍��W�����߂�
	void SetCapsuleStartEndPos(Collision::CapsuleCollision* capsuleColl);
	// �N�����v�֐�
	float Clamp(float n, float min, float max);

	//�X�N���[�����W�����[���h���W�ɕϊ�����s����쐬
	DirectX::SimpleMath::Matrix CreateMatrix_Screen2World(int screen_w, int screen_h,
		DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);


}

