///////////////////////////////////
//���U���g�V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��28��
///////////////////////////////////

#pragma once
#include "../SceneBase.h"
#include "Src\SceneManager\PlayerID.h"

#include <SimpleMath.h>

class Sprite2D;

class ResultScene :public SceneBase
{
public:
	//�R���X�g���N�^
	ResultScene();
	//�f�X�g���N�^
	~ResultScene();
	//������
	void Initialize() override;
	//�X�V
	void Update(DX::StepTimer const& timer) override;		
	//�`��
	void Render() override;			
	//�I������
	void Finalize() override;

	static ePLAYER_ID m_winPlayerID;

private:
	std::unique_ptr<Sprite2D> m_winPlayer1Sprite;
	std::unique_ptr<Sprite2D> m_winPlayer2Sprite;


};