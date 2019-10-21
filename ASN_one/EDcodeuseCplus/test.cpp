#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include"RequestCodec.h"
#include"comm.h"
using namespace std;

//测试请求报文编解码
int main()
{
	Codec *code = NULL;
	char *outData = NULL;
	int outDataLen = 0;

	RequestMsg msg;
	memset(&msg, 0, sizeof(RequestMsg));
	msg.cmdType = 0x1;
	strcpy(msg.clientId, "0001");
	strcpy(msg.serverId, "0000");
	strcpy(msg.r1, "hhhsssjjjkkkoooppp");
	strcpy(msg.authCode, "121221");
	//1.编码
	code = new RequestCodec(&msg);
	code->msgEncode(&outData, outDataLen);
	//写入文件
	writecodeTofile("./test.ber", (unsigned char*)outData, outDataLen);
	
	cout << "data: " << outData << "len: " << outDataLen << endl;
	cout << "编码ok" << endl;

	delete code;
	code = NULL;

	//2.解码
	code = new RequestCodec;
	RequestMsg *prmsg = static_cast<RequestMsg*>(code->msgDecode(outData, outDataLen));
	cout << "cmdType: " << prmsg->cmdType << endl;
	cout << "clientId: " << prmsg->clientId << endl;
	cout << "severId: " << prmsg->serverId << endl;
	cout << "r1: " << prmsg->r1 << endl;
	cout << "authCode: " << prmsg->authCode << endl;
	
	delete code;
	code = NULL;
	delete outData;
	outData = NULL;


	cout << "hello world .." << endl;
}