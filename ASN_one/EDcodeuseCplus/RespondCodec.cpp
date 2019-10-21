#define _CRT_SECURE_NO_WARNINGS
#include "RespondCodec.h"


RespondCodec::RespondCodec():Codec()
{
	
}
RespondCodec::RespondCodec(RespondMsg *msg): Codec()
{
	
	m_msg.rv = msg->rv;
	m_msg.seckeyid = msg->seckeyid;
	strcpy(m_msg.clientId, msg->clientId);
	strcpy(m_msg.serverId, msg->serverId);
	strcpy(m_msg.r2, msg->r2);
}

RespondCodec::~RespondCodec()
{

}
//序列化
int RespondCodec::msgEncode(char ** outData, int & len)
{
	//int		rv;				// 返回值
	//int		seckeyid;		// 对称密钥编号    keysn
	//char	clientId[12];	// 客户端编号
	//char	serverId[12];	// 服务器编号
	//char	r2[64];			// 服务器端随机数
	
	writeHeadNode(m_msg.rv);
	writeNextNode(m_msg.seckeyid);
	writeNextNode(m_msg.clientId, strlen(m_msg.clientId) + 1);
	writeNextNode(m_msg.serverId, strlen(m_msg.serverId) + 1);
	writeNextNode(m_msg.r2, strlen(m_msg.r2) + 1);

	packSequence(outData, len);

	return 0;
}

void * RespondCodec::msgDecode(char * inData, int inLen)
{
	unpackSequence(inData, inLen);
	readHeadNode(m_msg.rv);
	readNextNode(m_msg.seckeyid);
	readNextNode(m_msg.clientId);
	readNextNode(m_msg.serverId);
	readNextNode(m_msg.r2);

	return &m_msg;
}

int RespondCodec::msgMemFree(void ** point)
{
	//参数检查
	if (NULL == point || NULL == *point)
	{
		mLog.Log(__FILE__, __LINE__, ItcastLog::ERROR, -1, "readNextNode err");
		return -1;
	}

	//释放内存
	delete (*point);

	*point = NULL;
}
