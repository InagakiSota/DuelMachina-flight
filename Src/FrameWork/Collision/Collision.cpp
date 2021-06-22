#include "pch.h"
#include "Collision.h"
#include "../Math/Math.h"	

////////////////////////
//�~�Ɖ~�̔���
//����:�~�̏��
//�߂�l:�����������ǂ���
////////////////////////
bool Collision::CheckCircleCollision(Collision::CircleCollosion c1, Collision::CircleCollosion c2)
{
	//��̉~�̋����𑪂�
	Vec2D v = c1.pos;			//�ʂ̕ϐ��ɃR�s�[
	SubVec2D(&v, c2.pos);		//�x�N�g���̈����Z�����Č��_�ɖ߂�
	float len = LengthVec2D(v);	//�����̎擾

	//���a�̍��v�Ƌ������r
	float rad = c1.red + c2.red;

	if (len < rad)//��_�̋��������a�̍��v��菬������Γ������Ă���
	{
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
//! @brief AABB�̓����蔻����s��
//!
//! @param[in]
//!	int a1X, int a1Y		1�ڂ̃I�u�W�F�N�g�̍�����W
//!	int b1X, int b1Y		1�ڂ̃I�u�W�F�N�g�̉E�����W
//!	int a2X, int a2Y		2�ڂ̃I�u�W�F�N�g�̍�����W
//!	int b2X, int b2Y		2�ڂ̃I�u�W�F�N�g�̉E�����W
//!
//! @return int				0 = �������Ă��Ȃ�
//!							�܂��́A�ȉ��̍��v
//!							1 = 1��2���猩�č����瓖�����Ă���
//!							2 = 1��2���猩�ďォ�瓖�����Ă���
//!							4 = 1��2���猩�ĉE���瓖�����Ă���
//!							8 = 1��2���猩�ĉ����瓖�����Ă���
//----------------------------------------------------------------------
int Collision::AABBCheck(float a1X, float a1Y, float b1X, float b1Y, float a2X, float a2Y, float b2X, float b2Y)
{
	int ret = 0;

	if (a1X < b2X &&

		a1Y < b2Y &&
		b1X > a2X &&
		b1Y > a2Y)
	{
		int checkFlag = 0;
		float checkXRatio = 0.0f;
		float checkYRatio = 0.0f;
		float obj1Widht = b1X - a1X;
		float obj1Height = b1Y - a1Y;
		float objRightRatio = (float)(b2X - a1X) / (float)obj1Widht;
		float objLeftRatio = (float)(b1X - a2X) / (float)obj1Widht;
		float objUpRatio = (float)(b1Y - a2Y) / (float)obj1Height;
		float objDownRatio = (float)(b2Y - a1Y) / (float)obj1Height;

		//	���E�̔䗦���珬���������`�F�b�N�ɓ����
		if (objLeftRatio < objRightRatio)
		{
			checkFlag = 1;
			checkXRatio = objLeftRatio;
		}
		else if (objLeftRatio > objRightRatio)
		{
			checkFlag = 2;
			checkXRatio = objRightRatio;
		}
		else
		{
			checkFlag = 3;
			checkXRatio = objLeftRatio;
		}

		//	�㉺�̔䗦���珬���������`�F�b�N�ɓ����
		if (objUpRatio < objDownRatio)
		{
			checkFlag += 4;
			checkYRatio = objUpRatio;
		}
		else if (objUpRatio > objDownRatio)
		{
			checkFlag += 8;
			checkYRatio = objDownRatio;
		}
		else
		{
			checkFlag += 12;
			checkYRatio = objUpRatio;
		}

		//	�㉺�ƍ��E�Ŕ䗦�̏���������߂�l�ɓ����
		if (checkXRatio < checkYRatio)
		{
			ret = checkFlag & 3;
		}
		else if (checkXRatio > checkYRatio)
		{
			ret = checkFlag & 12;
		}
		else
		{
			ret = checkFlag & 15;
		}
		//	ret��15�ɂȂ����ꍇ�A���S���W�����S�ɏd�Ȃ��Ă���
	}

	return ret;
}

///////////////////////////
//3D�̔��Ɣ��̓����蔻��
//����:��
//�߂�l:�����������ǂ���
//////////////////////////
bool Collision::CheckHitBox2Box(Collision::BoxCollision box1, Collision::BoxCollision box2)
{
	if (fabsf(box1.pos.x - box2.pos.x) > (box1.size_h.x + box2.size_h.x)) return false;

	if (fabsf(box1.pos.y - box2.pos.y) > (box1.size_h.y + box2.size_h.y)) return false;

	if (fabsf(box1.pos.z - box2.pos.z) > (box1.size_h.z + box2.size_h.z)) return false;

	return true;

}

///////////////////////////
//���Ƌ��̓����蔻��
//����:���̍\����
//�߂�l:�����������ǂ���
//////////////////////////
bool Collision::CheckHitSphere2Sphere(Collision::SphereCollision sphere1, Collision::SphereCollision sphere2)
{
	//2�̋��̒��S�_�̃x�N�g�������߂�
	DirectX::SimpleMath::Vector3 v3 = sphere1.pos - sphere2.pos;
	//2�̋��̒��S�_�̒����̂Q������߂�
	float l2 = v3.Dot(v3);
	//�Q�_�Ԃ̋����̂Q�悪�Q�̋��̔��a�̘a�̂Q���菬������Γ������Ă���
	float radiusSum = sphere1.r + sphere2.r;
	if (l2 <= radiusSum * radiusSum)
	{
		return true;
	}
	
	return false;
}

///////////////////////////
//���ƃJ�v�Z���̓����蔻��
//����:���̍\���́A�J�v�Z���̍\����
//�߂�l:�����������ǂ���
//////////////////////////
bool Collision::CheckHitSphere2Capsule(Collision::SphereCollision sphere, Collision::CapsuleCollision capsule)
{
	// ���̒��S�ƃJ�v�Z���̒��S�̐����Ƃ̋����̕������v�Z
	float dist2 = SqDistPointSegment(capsule.startPos, capsule.endPos, sphere.pos);

	float radius = sphere.r + capsule.r;

	return dist2 <= radius * radius;
}


///////////////////////////
//�J�v�Z���ƃJ�v�Z���̓����蔻��
//����:�J�v�Z���̍\���̂P�A�J�v�Z���̍\���̂Q
//�߂�l:�����������ǂ���
//////////////////////////
bool Collision::CheckHitCapsule2Capsule(Collision::CapsuleCollision capsule1, Collision::CapsuleCollision capsule2)
{
	float s, t;

	DirectX::SimpleMath::Vector3 c1, c2;

	// �J�v�Z���̒��S�̐����Ԃ̋����̕������v�Z

	float dist2 = ClosestPtSegmentSegment(capsule1.startPos, capsule1.endPos, capsule2.startPos, capsule2.endPos, s, t, c1, c2);

	float radius = capsule1.r + capsule2.r;

	return dist2 <= radius * radius;
}

///////////////////////////
// �_c�Ɛ���ab�̊Ԃ̋����̕��������߂�
//����:a:�����̊J�_�Ab:�����̏I�_�Ac:�_�̍��W
//�߂�l:�_c�Ɛ���ab�̊Ԃ̋����̕���
//////////////////////////
float Collision::SqDistPointSegment(DirectX::SimpleMath::Vector3 startPos, DirectX::SimpleMath::Vector3 endPos, DirectX::SimpleMath::Vector3 pos)
{
	DirectX::SimpleMath::Vector3 ab = endPos - startPos;

	DirectX::SimpleMath::Vector3 ac = pos - startPos;

	DirectX::SimpleMath::Vector3 bc = pos - endPos;

	float e = ac.Dot(ab);

	if (e <= 0.0f) return ac.Dot(ac);

	float f = ab.Dot(ab);

	if (e >= f) return bc.Dot(bc);

	return ac.Dot(ac) - e * e / f;
}
// �N�����v�֐�

float Collision::Clamp(float n, float min, float max)
{

	if (n < min) return min;

	if (n > max) return max;

	return n;

}
///////////////////////////
//�Q�̐����̍ŒZ�����̕�����Ԃ��֐�
//����: p1:����1�̎n�_, q1:����1�̏I�_
//		p2:����2�̎n�_, q2:����2�̏I�_
//		s: �����P��̍ŒZ�ʒu��\���W�� t: ����2��̍ŒZ�ʒu��\���W��
//		c1: �����P��̍ŒZ�����̈ʒu c2: ����2��̍ŒZ�����̈ʒu
//�߂�l:�Q�̐����̍ŒZ�����̕���
//////////////////////////
float  Collision::ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3  p1, DirectX::SimpleMath::Vector3  q1, DirectX::SimpleMath::Vector3  p2,
	DirectX::SimpleMath::Vector3  q2, float &s, float &t,
	DirectX::SimpleMath::Vector3 & c1, DirectX::SimpleMath::Vector3 & c2)
{
	DirectX::SimpleMath::Vector3 d1 = q1 - p1; DirectX::SimpleMath::Vector3 d2 = q2 - p2; DirectX::SimpleMath::Vector3 r = p1 - p2;

	float a = d1.Dot(d1); float e = d2.Dot(d2); float f = d2.Dot(r);

	if (a <= FLT_EPSILON && e <= FLT_EPSILON)

	{

		s = t = 0.0f;

		c1 = p1;

		c2 = p2;

		return (c1 - c2).Dot(c1 - c2);

	}

	if (a <= FLT_EPSILON)

	{

		s = 0.0f;

		t = f / e;

		t = Clamp(t, 0.0f, 1.0f);

	}

	else

	{

		float c = d1.Dot(r);

		if (e <= FLT_EPSILON)

		{

			t = 0.0f;

			s = Clamp(-c / a, 0.0f, 1.0f);

		}

		else

		{

			float b = d1.Dot(d2);

			float denom = a * e - b * b;

			if (denom != 0.0f)

			{

				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);

			}

			else

			{

				s = 0.0f;

			}

			float tnom = (b * s + f);

			if (tnom < 0.0f)

			{

				t = 0.0f;

				s = Clamp(-c / a, 0.0f, 1.0f);

			}

			else if (tnom > e)

			{

				t = 1.0f;

				s = Clamp((b - c) / a, 0.0f, 1.0f);

			}

			else

			{

				t = tnom / e;

			}

		}

	}

	c1 = p1 + d1 * s;

	c2 = p2 + d2 * t;

	return (c1 - c2).Dot(c1 - c2);
}

///////////////////////////
//�J�v�Z���̎n�_�ƏI�_�̍��W�����߂�
//����:�J�v�Z���̓����蔻��\����
//�߂�l:�Ȃ�
//////////////////////////
void Collision::SetCapsuleStartEndPos(Collision::CapsuleCollision* capsuleColl)
{
	
	capsuleColl->q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(capsuleColl->rotAxis, DirectX::XMConvertToRadians(capsuleColl->rot));

	//���S�_����n�_�܂Ō������x�N�g��
	DirectX::SimpleMath::Vector3 vec1(0.0f, capsuleColl->length, 0.0f);
	//���S�_����I�_�܂Ō������x�N�g��
	DirectX::SimpleMath::Vector3 vec2(0.0f, -capsuleColl->length, 0.0f);

	//�n�_�ƏI�_�̍��W�����߂�
	capsuleColl->startPos = capsuleColl->pos + DirectX::SimpleMath::Vector3::Transform(vec1, capsuleColl->q);
	capsuleColl->endPos = capsuleColl->pos + DirectX::SimpleMath::Vector3::Transform(vec2, capsuleColl->q);


}

///////////////////////////
//�X�N���[�����W�����[���h���W�ɕϊ�����s����쐬
//����:�X�N���[���̕��A�X�N���[���̍����A�r���[�s��A�ˉe�s��
//�߂�l:�ϊ������s��
//////////////////////////
DirectX::SimpleMath::Matrix Collision::CreateMatrix_Screen2World(int screen_w, int screen_h, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

	// �r���[�|�[�g�X�P�[�����O�s����쐬

	DirectX::SimpleMath::Matrix viewport;

	viewport._11 = screen_w / 2.0f;

	viewport._22 = -screen_h / 2.0f;

	viewport._41 = screen_w / 2.0f;

	viewport._42 = screen_h / 2.0f;

	// �t�s����쐬

	DirectX::SimpleMath::Matrix invS = viewport.Invert();

	DirectX::SimpleMath::Matrix invP = projection.Invert();

	DirectX::SimpleMath::Matrix invV = view.Invert();

	// �w�r���[�|�[�g�X�P�[�����O�s��̋t�s��x �~ �w�ˉe�s��̋t�s��x �~ �w�r���[�s��̋t�s��x

	return invS * invP * invV;

}