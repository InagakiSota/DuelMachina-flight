///////////////////////////////////
//�L�����N�^�[1�̒萔�Ǘ��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��18��
///////////////////////////////////

#include "pch.h"
#include "Character1Params.h"
#include <fstream>
#include <sstream>

Character1Params* Character1Params::m_pMyInstance = nullptr;

//�̂̓����蔻��̃T�C�Y(�ʏ펞)
const DirectX::SimpleMath::Vector3 Character1Params::BODY_COLL_SIZE_NORMAL = DirectX::SimpleMath::Vector3(0.30f, 1.02f, 0.3f);
//���̓����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character1Params::LEG_COLL_SIZE = DirectX::SimpleMath::Vector3(0.25f, 0.25f, 0.25f);
//���̓����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character1Params::HEAD_COLL_SIZE = DirectX::SimpleMath::Vector3(0.25f, 0.15f, 0.25f);
//�O�����̃x�N�g��
const DirectX::SimpleMath::Vector3 Character1Params::FRONT_VECTOR = DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);

//�̂̃T�C�Y
const float Character1Params::BODY_SIZE = 0.003f;
//Y���̊p�x
const float Character1Params::ANGLE_Y = 90.0f;

//�J�������W
const DirectX::SimpleMath::Vector3 Character1Params::CAMERA_POS = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 6.0f);


//�ړ��ł���X���W�̍ő�l
const float Character1Params::MOVE_LIMIT_X = 4.5f;
//�ړ��ł���Y���W�̏�̌��E�l
const float Character1Params::MOVE_LIMIT_TOP = 2.0f;
//�ړ��ł���Y���W�̉��̌��E�l
const float Character1Params::MOVE_LIMIT_BOTTOM = -2.0f;


//�̂̓����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character1Params::MOVE_BOOST_BODY_SIDE = DirectX::SimpleMath::Vector3(0.30f, 0.5f, 0.2f);

//�̂̓����蔻��̃T�C�Y(���Ⴊ��)
const DirectX::SimpleMath::Vector3 Character1Params::BODY_COLL_SIZE_SQUAT = DirectX::SimpleMath::Vector3(0.30f, 0.78f, 0.3f);

//�u�[�X�g�G�t�F�N�g��X���W
const float Character1Params::BOOST_EFFECT_POS_X = 0.8f;
//�u�[�X�g�G�t�F�N�g��Y���W
const float Character1Params::BOOST_EFFECT_POS_Y = 0.5f;
//�u�[�X�g�G�t�F�N�g�̊p�x(����)	
const float Character1Params::BOOST_EFFECT_ANGLE_LEFT = 190.0f;
//�u�[�X�g�G�t�F�N�g�̊p�x(�E��)
const float Character1Params::BOOST_EFFECT_ANGLE_RIGHT = -10.0f;


//�R���X�g���N�^
Character1Params::Character1Params()
{
}

//�f�X�g���N�^
Character1Params::~Character1Params()
{
}


Character1Params * Character1Params::GetInstance()
{
	if (m_pMyInstance == nullptr)
	{
		m_pMyInstance = new Character1Params();
	}

	return m_pMyInstance;
}

void Character1Params::ReleaseInstance()
{
	if (m_pMyInstance != nullptr)
	{
		delete m_pMyInstance;
		m_pMyInstance = nullptr;
	}
}

void Character1Params::LoadStatusData()
{
	std::wstring str;

	//�t�@�C���̃I�[�v��
	std::wifstream ifs(L"CharacterStatusData\\Character1_StatusData.csv");

	//�w�b�_������
	std::wstring headName = L"HP";

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, headName.size(), headName) == 0)
		{
			break;
		}
	}

	//�̗͂̓ǂݍ���
	getline(ifs, str);
	std::wstring tmp1;
	std::wistringstream stream1(str);
	std::getline(stream1, tmp1);
	MAX_HP = std::stoi(tmp1);
		
	//�w�b�_�������ς���
	 headName = L"BOOST_CAP";
	//�t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, headName.size(), headName) == 0)
		{
			break;
		}
	}

	//�u�[�X�g�e�ʂ̓ǂݍ���
	getline(ifs, str);
	std::wstring tmp2;
	std::wistringstream stream2(str);
	std::getline(stream2, tmp2);
	BOOST_CAP_MAX = std::stoi(tmp2);

	//�w�b�_�������ς���
	headName = L"JUMP";
	//�t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, headName.size(), headName) == 0)
		{
			break;
		}
	}

	//�W�����v�͂̓ǂݍ���
	getline(ifs, str);
	std::wstring tmp3;
	std::wistringstream stream3(str);
	std::getline(stream3, tmp3);
	JUMP_FORCE = std::stof(tmp3);

	//�w�b�_�������ς���
	headName = L"MOVE_FRONT";
	//�t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, headName.size(), headName) == 0)
		{
			break;
		}
	}

	//�O�ړ��̑��x�̓ǂݍ���
	getline(ifs, str);
	std::wstring tmp4;
	std::wistringstream stream4(str);
	std::getline(stream4, tmp4);
	MOVE_FRONT_FORCE = std::stof(tmp4);

	//�w�b�_�������ς���
	headName = L"MOVE_BACK";
	//�t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, headName.size(), headName) == 0)
		{
			break;
		}
	}

	//��ړ��̑��x�̓ǂݍ���
	getline(ifs, str);
	std::wstring tmp5;
	std::wistringstream stream5(str);
	std::getline(stream5, tmp5);
	MOVE_BACK_FORCE = std::stof(tmp5);

	//�w�b�_�������ς���
	headName = L"MOVE_BOOST";
	//�t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	//�w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, headName.size(), headName) == 0)
		{
			break;
		}
	}

	//�u�[�X�g�ړ��̑��x�̓ǂݍ���
	getline(ifs, str);
	std::wstring tmp6;
	std::wistringstream stream6(str);
	std::getline(stream6, tmp6);
	MOVE_BOOST_FORCE = std::stof(tmp6);


	//�t�@�C���̃N���[�Y
	ifs.close();

}
