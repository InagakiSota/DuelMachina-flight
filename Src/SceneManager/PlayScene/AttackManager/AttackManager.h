#pragma once
#include "../../../FrameWork/Collision/Collision.h"
#include "GeometricPrimitive.h"
#include "DeviceResources.h"
#include "../../PlayerID.h"

//�U���̍\����
struct AttackStruct
{
	//�R���X�g���N�^
	AttackStruct()
		:power(0),
		pos{},
		attackColl{},
		geoBox(nullptr),
		isUsed(false),
		vel{},
		world{},
		timer(0),
		playerID(ePLAYER_ID::NONE),
		isHit(false)
	{
	}

	//�З�
	int power;
	//�����蔻��
	Collision::BoxCollision attackColl;
	//�W�I���g���b�N�v���~�e�B�u(��)
	std::unique_ptr<DirectX::GeometricPrimitive> geoBox;
	//�g�p����Ă���t���O
	bool isUsed;
	//���W
	DirectX::SimpleMath::Vector3 pos;
	//�ړ���
	DirectX::SimpleMath::Vector3 vel;
	//���[���h�s��
	DirectX::SimpleMath::Matrix world;
	//�^�C�}�[
	float timer;
	//�g�p����v���C���[��ID
	ePLAYER_ID playerID;
	//���������t���O
	bool isHit;
};

class AttackManager
{
public:
	//�U���̑���
	static const int ATTACK_NUM = 128;


	//������
	void Initialize(DX::DeviceResources* pDeviceResources);
	//�X�V
	void Update();
	//�`��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�I������
	void Finalize();

	//�U���̍\���̂̎擾
	AttackStruct* GetAttackStruct(const int& index);

	//���Z�b�g
	void Reset(const int& index);

	//�C���X�^���X�̎擾
	static AttackManager* GetInstance();
	//�C���X�^���X�̉��
	static void ReleaseInstance();

private:
	//�V���O���g����
	//�R���X�g���N�^
	AttackManager();
	//�f�X�g���N�^
	~AttackManager();
	//���g�̃C���X�^���X
	static AttackManager* m_pMyInstance;


	//�U���̔z��
	std::unique_ptr<AttackStruct> m_pAttackArray[ATTACK_NUM];
	//�f�o�C�X
	DX::DeviceResources* m_pDeviceResources;
	
};

