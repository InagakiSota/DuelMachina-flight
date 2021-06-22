///////////////////////////////////
//�L�����N�^�[�̐����N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��20��
///////////////////////////////////
#include "pch.h"
#include "CharacterFactory.h"

#include "CharacterBase.h"
#include "Character1\Character1.h"
#include "Character2\Character2.h"
#include "Character3\Character3.h"

#include "../../PlayerID.h"

eCHARACTER_ID CharacterFactory::m_player1Chara = eCHARACTER_ID::CHARACTER_1;
eCHARACTER_ID CharacterFactory::m_player2Chara = eCHARACTER_ID::CHARACTER_1;

//�R���X�g���N�^
CharacterFactory::CharacterFactory()
{
}

//�f�X�g���N�^
CharacterFactory::~CharacterFactory()
{
}

///////////////////////////
//�L�����N�^�[���� �v���C���[�P�p
//����:�L�����N�^�[��ID
//�߂�l:���������L�����N�^�[�̃|�C���^
//////////////////////////
CharacterBase * CharacterFactory::CreatePlayer1()
{
	//�L�����N�^�[�̃|�C���^
	CharacterBase* chara;

	//ID�ɑΉ������L�����N�^�[��ǂݍ���
	switch (m_player1Chara)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			chara = new Character1(ePLAYER_ID::PLAYER_1);
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			chara = new Character2(ePLAYER_ID::PLAYER_1);
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			chara = new Character3(ePLAYER_ID::PLAYER_1);
			break;
		}

		default:
			break;
	}

	return chara;
}

///////////////////////////
//�L�����N�^�[���� �v���C���[2�p
//����:�L�����N�^�[��ID
//�߂�l:���������L�����N�^�[�̃|�C���^
//////////////////////////
CharacterBase * CharacterFactory::CreatePlayer2()
{
	//�L�����N�^�[�̃|�C���^
	CharacterBase* chara;

	//ID�ɑΉ������L�����N�^�[��ǂݍ���
	switch (m_player2Chara)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			chara = new Character1(ePLAYER_ID::PLAYER_2);
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			chara = new Character2(ePLAYER_ID::PLAYER_2);
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			chara = new Character3(ePLAYER_ID::PLAYER_2);
			break;
		}

		default:
			break;
	}

	return chara;
}
