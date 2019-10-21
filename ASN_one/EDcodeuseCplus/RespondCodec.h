#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Codec.h"


struct RespondMsg
{
	int		rv;				// 返回值
	int		seckeyid;		// 对称密钥编号    keysn
	char	clientId[12];	// 客户端编号
	char	serverId[12];	// 服务器编号
	char	r2[64];			// 服务器端随机数
	RespondMsg(){}
	RespondMsg(char* clientID, char* serverID, char* r2, int rv, int seckeyID)
	{
		this->rv = rv;
		this->seckeyid = seckeyID;
		memcpy(this->serverId, serverID,strlen(this->serverId));
		memcpy(this->clientId, clientID, strlen(this->clientId));
		memcpy(this->r2, r2, strlen(this->r2));
		//strcpy(this->clientId, clientID);
		//strcpy(this->serverId, serverID);
		//strcpy(this->r2, r2);
	}
};
class RespondCodec :public Codec
{
public:
	RespondCodec();
	RespondCodec(RespondMsg *msg);

	~RespondCodec();
	// 重写父类函数
	//编码函数
	int msgEncode(char** outData, int &len);

	//解码函数
	void* msgDecode(char *inData, int inLen);

	//内存释放
	int msgMemFree(void **point);

private:
	RespondMsg m_msg;
	ItcastLog mLog;
};

