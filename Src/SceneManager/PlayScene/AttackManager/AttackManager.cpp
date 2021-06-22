#include "pch.h"
#include "AttackManager.h"

AttackManager* AttackManager::m_pMyInstance = nullptr;

//�R���X�g���N�^
AttackManager::AttackManager()
	:m_pAttackArray{}
{
}

//�f�X�g���N�^
AttackManager::~AttackManager()
{
	m_pDeviceResources = nullptr;
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//if (m_pAttackArray[i]->geoBox != nullptr)
		//{
		//	//m_pAttackArray[i]->geoBox = nullptr;
		//}

		//if (m_pAttackArray[i] != nullptr)
		//{
		//	m_pAttackArray[i].reset();
		//}
	}

}

///////////////////////////
//������
//����:�f�o�C�X
//�߂�l:�Ȃ�
//////////////////////////
void AttackManager::Initialize(DX::DeviceResources* pDeviceResources)
{
	m_pDeviceResources = pDeviceResources;
	auto context = m_pDeviceResources->GetD3DDeviceContext();

	//�l��������
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//�|�C���^�̓ǂݍ���
		m_pAttackArray[i] = std::make_unique<AttackStruct>();

		//�W�I���g���b�N�v���~�e�B�u�̍쐬
		//m_pAttackArray[i]->geoBox = DirectX::GeometricPrimitive::CreateCube(context);
		//�l�̏�����
		Reset(i);
	}

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void AttackManager::Update()
{

	for (int i = 0; i < ATTACK_NUM; i++)
	{
		if (m_pAttackArray[i]->isUsed == false)
		{
			Reset(i);
			continue;
		}
		//if (m_pAttackArray[i]->geoBox == nullptr)
		{
			m_pAttackArray[i]->geoBox = DirectX::GeometricPrimitive::CreateBox(m_pDeviceResources->GetD3DDeviceContext(), m_pAttackArray[i]->attackColl.size_h * 2);
		}
		DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_pAttackArray[i]->pos);
		m_pAttackArray[i]->world = trans;

	}

}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void AttackManager::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		//�g�p����Ă��Ȃ���΃X���[
		if (m_pAttackArray[i]->isUsed == false)continue;

		if (m_pAttackArray[i]->geoBox != nullptr)
		{
			m_pAttackArray[i]->geoBox->Draw(m_pAttackArray[i]->world, view, proj, DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 0.3f));
		}
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void AttackManager::Finalize()
{
	for (int i = 0; i < ATTACK_NUM; i++)
	{
		m_pAttackArray[i]->geoBox.reset();
		m_pAttackArray[i].reset();
	}
}

///////////////////////////
//�U���̍\���̂̎擾
//����:�v�f��
//�߂�l:�U���̍\���̂̃|�C���^
//////////////////////////
AttackStruct * AttackManager::GetAttackStruct(const int& index)
{
	////�U���̍\���̂̃|�C���^�ϐ�
	//AttackStruct* pAttack;
	//for (int i = 0; i < ATTACK_NUM; i++)
	//{
	//	//�g�p����Ă�����X���[
	//	if (m_pAttackArray[i]->isUsed == true)continue;

	//	else
	//	{
	//		//�g�p����Ă��Ȃ���΃|�C���g�Ɋi�[
	//		pAttack = m_pAttackArray[i].get();
	//		break;
	//	}
	//}

	//return pAttack;

	return m_pAttackArray[index].get();
}

///////////////////////////
//���Z�b�g
//����:
//�߂�l:
//////////////////////////
void AttackManager::Reset(const int & index)
{
	m_pAttackArray[index]->isUsed = false;
	m_pAttackArray[index]->pos = DirectX::SimpleMath::Vector3::Zero;
	m_pAttackArray[index]->vel = DirectX::SimpleMath::Vector3::Zero;
	m_pAttackArray[index]->attackColl = {};
	m_pAttackArray[index]->power = 0;
	m_pAttackArray[index]->world.Identity;
	m_pAttackArray[index]->isHit = false;
	m_pAttackArray[index]->playerID = ePLAYER_ID::NONE;


	if (m_pAttackArray[index]->geoBox != nullptr)
	{
		//m_pAttackArray[index].reset();
		m_pAttackArray[index]->geoBox = nullptr;

	}

}

///////////////////////////
//�C���X�^���X�̎擾
//����:�Ȃ�
//�߂�l:���g(�U���}�l�[�W���[)�̃|�C���^
//////////////////////////
AttackManager * AttackManager::GetInstance()
{
	if (m_pMyInstance == nullptr)
	{
		m_pMyInstance = new AttackManager();
	}

	return m_pMyInstance;
}

///////////////////////////
//�C���X�^���X�̉��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void AttackManager::ReleaseInstance()
{
	if (m_pMyInstance != nullptr)
	{
		delete m_pMyInstance;
	}
	m_pMyInstance = nullptr;
}
