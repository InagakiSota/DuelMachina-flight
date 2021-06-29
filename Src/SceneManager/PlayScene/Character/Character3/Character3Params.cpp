///////////////////////////////////
//�L�����N�^�[3�̒萔�Ǘ��N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N12��18��
///////////////////////////////////

#include "pch.h"
#include "Character3Params.h"
#include <fstream>
#include <sstream>

Character3Params* Character3Params::m_pMyInstance = nullptr;


//�̂̃T�C�Y
const float Character3Params::BODY_SIZE = 0.015f;
//Y���̊p�x
const float Character3Params::ANGLE_Y = 30.0f;
//�ړ��ł���X���W�̍ő�l
const float Character3Params::MOVE_LIMIT_X = 4.5f;
//�ړ��ł���Y���W�̏�̍ő�l
const float Character3Params::MOVE_LIMIT_TOP = 3.0f;
//�ړ��ł���Y���W�̏�̍ő�l
const float Character3Params::MOVE_LIMIT_BOTTOM = -1.0f;
//�̂̓����蔻��̃T�C�Y(�ʏ펞)
const DirectX::SimpleMath::Vector3 Character3Params::BODY_COLL_SIZE_NORMAL = DirectX::SimpleMath::Vector3(0.40f, 1.0f, 0.30f);
//�̂̓����蔻��̃T�C�Y(���Ⴊ��)
const DirectX::SimpleMath::Vector3 Character3Params::BODY_COLL_SIZE_SQUAT = DirectX::SimpleMath::Vector3(0.40f, 0.75f, 0.30f);
//���̓����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character3Params::LEG_COLL_SIZE = DirectX::SimpleMath::Vector3(0.35f, 0.25f, 0.25f);
//���̓����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character3Params::HEAD_COLL_SIZE = DirectX::SimpleMath::Vector3(0.35f, 0.15f, 0.25f);
//�O�����̃x�N�g��
const DirectX::SimpleMath::Vector3 Character3Params::FRONT_VECTOR = DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
//�J�������W
const DirectX::SimpleMath::Vector3 Character3Params::CAMERA_POS = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 6.0f);
//�V�[���h��Y���W
const float Character3Params::SHIELD_POS_Y = 1.3f;

//�u�[�X�g�G�t�F�N�g��X���W
const float Character3Params::BOOST_EFFECT_POS_X = 0.8f;
//�u�[�X�g�G�t�F�N�g��Y���W
const float Character3Params::BOOST_EFFECT_POS_Y = -1.1f;
//�u�[�X�g�G�t�F�N�g�̊p�x(����)	
const float Character3Params::BOOST_EFFECT_ANGLE_LEFT = 190.0f;
//�u�[�X�g�G�t�F�N�g�̊p�x(�E��)
const float Character3Params::BOOST_EFFECT_ANGLE_RIGHT = -10.0f;

//�q�b�g�G�t�F�N�g��Y���W
const float Character3Params::HIT_EFFECT_POS_Y = -1.3f;

//�R���X�g���N�^
Character3Params::Character3Params()
{
}

//�f�X�g���N�^
Character3Params::~Character3Params()
{
}


Character3Params * Character3Params::GetInstance()
{
	if (m_pMyInstance == nullptr)
	{
		m_pMyInstance = new Character3Params();
	}

	return m_pMyInstance;
}

void Character3Params::ReleaseInstance()
{
	if (m_pMyInstance != nullptr)
	{
		delete m_pMyInstance;
		m_pMyInstance = nullptr;
	}
}

void Character3Params::LoadStatusData()
{
	std::wstring str;

	//�t�@�C���̃I�[�v��
	std::wifstream ifs(L"CharacterStatusData\\Character3_StatusData.csv");

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
