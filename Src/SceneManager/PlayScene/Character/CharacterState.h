///////////////////////////////////
//キャラクターのステートの列挙体
//作成者：GS3_05_稲垣
//作成日：2020年10月17日
///////////////////////////////////

#pragma once

enum class eCHARACTER_STATE : int
{
	NONE = -1,

	WAIT,			//待機
	JUMP,			//ジャンプ
	MOVE,			//移動
	MOVE_FRONT,		//前移動
	MOVE_BACK,		//後ろ移動
	MOVE_UP,		//上移動
	MOVE_DOWN,		//下移動
	SQUAT,			//しゃがみ
	DAMAGE,			//やられ
	GUARD,			//ガード
	SQUAT_GUARD,	//しゃがみガード
	BOOST_MOVE,		//ブースト移動
	BOOST_MOVE_FRONT,	//ブースト移動　前
	BOOST_MOVE_BACK,	//ブースト移動　後
	BOOST_MOVE_UP,		//ブースト移動　上
	BOOST_MOVE_DOWN,	//ブースト移動　下
	WIN,			//勝利
	LOSE,			//敗北


	MAX_NUM
};
