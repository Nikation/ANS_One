#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Codec.h"


struct RespondMsg
{
	int		rv;				// ����ֵ
	int		seckeyid;		// �Գ���Կ���    keysn
	char	clientId[12];	// �ͻ��˱��
	char	serverId[12];	// ���������
	char	r2[64];			// �������������
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
	// ��д���ຯ��
	//���뺯��
	int msgEncode(char** outData, int &len);

	//���뺯��
	void* msgDecode(char *inData, int inLen);

	//�ڴ��ͷ�
	int msgMemFree(void **point);

private:
	RespondMsg m_msg;
	ItcastLog mLog;
};

