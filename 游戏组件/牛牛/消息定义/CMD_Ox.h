#ifndef CMD_OX_HEAD_FILE
#define CMD_OX_HEAD_FILE

#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID						101										//游戏 I D
#define GAME_PLAYER					4										//游戏人数
#define GAME_NAME					TEXT("牛牛")							//游戏名字
#define VERSION_SERVER				PROCESS_VERSION(6,0,3)					//程序版本
#define VERSION_CLIENT				PROCESS_VERSION(6,0,3)					//程序版本

#define GAME_GENRE					(GAME_GENRE_GOLD|GAME_GENRE_MATCH)		//游戏类型
#define MAXCOUNT					5										//扑克数目

//结束原因
#define GER_NO_PLAYER				0x10									//没有玩家

//游戏状态
#define GS_TK_FREE					GAME_STATUS_FREE                        //等待开始
#define GS_TK_CALL					GAME_STATUS_PLAY						//叫庄状态
#define GS_TK_SCORE					GAME_STATUS_PLAY+1						//下注状态
#define GS_TK_PLAYING				GAME_STATUS_PLAY+2						//游戏进行

//用户状态
#define USEX_NULL                   0                                       //用户状态
#define USEX_PLAYING                1                                       //用户状态
#define USEX_DYNAMIC                2                                       //用户状态   

//////////////////////////////////////////////////////////////////////////
//服务器命令结构

#define SUB_S_GAME_START				100									//游戏开始
#define SUB_S_ADD_SCORE					101									//加注结果
#define SUB_S_PLAYER_EXIT				102									//用户强退
#define SUB_S_SEND_CARD					103									//发牌消息
#define SUB_S_GAME_END					104									//游戏结束
#define SUB_S_OPEN_CARD					105									//用户摊牌
#define SUB_S_CALL_BANKER				106									//用户叫庄

//游戏状态
struct CMD_S_StatusFree
{
	LONGLONG							lCellScore;							//基础积分
};

//游戏状态
struct CMD_S_StatusCall
{
	WORD							    	wCallBanker;						//叫庄用户
	BYTE							        cbPlayStatus[GAME_PLAYER];          //用户状态
};

//游戏状态
struct CMD_S_StatusScore
{
	//下注信息
	LONGLONG								lTurnMaxScore;						//最大下注
	//LONGLONG								lTurnLessScore;						//最小下注
	LONGLONG								lTableScore[GAME_PLAYER];			//下注数目
	BYTE								    cbPlayStatus[GAME_PLAYER];          //用户状态
	WORD							    	wBankerUser;						//庄家用户
};

//游戏状态
struct CMD_S_StatusPlay
{
	//状态信息	
	BYTE								    cbPlayStatus[GAME_PLAYER];          //用户状态
	LONGLONG								lTurnMaxScore;						//最大下注
	//LONGLONG								lTurnLessScore;						//最小下注
	LONGLONG								lTableScore[GAME_PLAYER];			//下注数目
	WORD								    wBankerUser;						//庄家用户

	//扑克信息
	BYTE							    	cbHandCardData[GAME_PLAYER][MAXCOUNT];//桌面扑克
	BYTE						      		bOxCard[GAME_PLAYER];				//牛牛数据
};

//用户叫庄
struct CMD_S_CallBanker
{
	WORD							     	wCallBanker;						//叫庄用户
	bool							    	bFirstTimes;						//首次叫庄
};

//游戏开始
struct CMD_S_GameStart
{
	//下注信息
	LONGLONG								lTurnMaxScore;						//最大下注
	WORD							     	wBankerUser;						//庄家用户
};

//用户下注
struct CMD_S_AddScore
{
	WORD							    	wAddScoreUser;						//加注用户
	LONGLONG								lAddScoreCount;						//加注数目
};

//游戏结束
struct CMD_S_GameEnd
{
	LONGLONG								lGameTax[GAME_PLAYER];				//游戏税收
	LONGLONG								lGameScore[GAME_PLAYER];			//游戏得分
	BYTE							     	cbCardData[GAME_PLAYER];			//用户扑克
};

//发牌数据包
struct CMD_S_SendCard
{
	BYTE								    cbCardData[GAME_PLAYER][MAXCOUNT];	//用户扑克
};

//用户退出
struct CMD_S_PlayerExit
{
	WORD						      		wPlayerID;							//退出用户
};

//用户摊牌
struct CMD_S_Open_Card
{
	WORD							     	wPlayerID;							//摊牌用户
	BYTE							      	bOpen;								//摊牌标志
};
//////////////////////////////////////////////////////////////////////////
//客户端命令结构
#define SUB_C_CALL_BANKER				1									//用户叫庄
#define SUB_C_ADD_SCORE					2									//用户加注
#define SUB_C_OPEN_CARD					3									//用户摊牌

//用户叫庄
struct CMD_C_CallBanker
{
	BYTE							    	bBanker;							//做庄标志
};

//用户加注
struct CMD_C_AddScore
{
	LONGLONG								lScore;								//加注数目
};

//用户摊牌
struct CMD_C_OxCard
{
	BYTE							    	bOX;								//牛牛标志
};

//////////////////////////////////////////////////////////////////////////
#pragma pack()

#endif
