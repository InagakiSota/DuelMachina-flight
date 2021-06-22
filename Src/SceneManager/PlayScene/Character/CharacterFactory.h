///////////////////////////////////
//�L�����N�^�[�̐����N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��20��
///////////////////////////////////

#pragma once

class CharacterBase;

#include "CharacterID.h"

class CharacterFactory
{
public:
	//�R���X�g���N�^
	CharacterFactory();
	//�f�X�g���N�^
	~CharacterFactory();

	//�L�����N�^�[���� �v���C���[�P
	static CharacterBase* CreatePlayer1();
	//�L�����N�^�[���� �v���C���[2
	static CharacterBase* CreatePlayer2();

	//�v���C���[�P�̑I���L����
	static eCHARACTER_ID m_player1Chara;
	//�v���C���[�P�̑I���L����
	static eCHARACTER_ID m_player2Chara;


};

