#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "itcast_asn1_der.h"

//�ṹ������
typedef struct _teacher_t
{
	char name[32];
	int age;
	char *p;
	int pLen;
}teacher_t;

//д�ļ�
int writecodeTofile(const char* filepath,unsigned char *data, int dataLen )
{
	FILE *fp = NULL;
	fp = fopen(filepath, "w");
	if (NULL == fp)
	{
		printf("fopen failed ..\n");
		return 1;
	}

	fwrite(data, sizeof(char), dataLen, fp);

	fclose(fp);
	return 0;
}


//�򵥽ṹ�����
int TeacherEncode(teacher_t *t, unsigned char **outData, int *outLen)
{
	int ret = -1;
	ITCAST_ANYBUF *head = NULL;
	ITCAST_ANYBUF *tmp = NULL;
	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *outNode = NULL;

	//��������
	unsigned char *out = NULL;

	//1.������
	if (NULL == t || NULL == outData || NULL == outLen)
	{
		printf("agv is err\n");
		return 1;
	}
	//2.���б���ṹ���Ա
	//name
	ret = EncodeChar(t->name, strlen(t->name), &head);
	if (-1 == ret)
	{
		printf("EncodeChar err ..\n");
		return 1;
	}
	//age
	tmp = head;
	//ret = DER_ItAsn1_WriteInteger(t->age, &(tmp->next));
	ret = DER_ItAsn1_WriteInteger(t->age, &tmpNode);
	if (-1 == ret)
	{
		printf("DER_ItAsn1_WriteInteger err ..\n");
		return 1;
	}
	tmp->next = tmpNode;
	tmp = tmp->next;
	//p
	ret = EncodeChar(t->p, t->pLen, &tmpNode);
	if (-1 == ret)
	{
		printf("EncodeChar err ..\n");
		return 1;
	}
	tmp->next = tmpNode;
	tmp = tmp->next;
	//plen
	ret = DER_ItAsn1_WriteInteger(t->pLen, &tmpNode);
	if (-1 == ret)
	{
		printf("DER_ItAsn1_WriteInteger err ..\n");
		return 1;
	}
	tmp->next = tmpNode;
	tmp = tmp->next;
	//3.���б���ṹ��
	ret = DER_ItAsn1_WriteSequence(head, &outNode);
	if (-1 == ret)
	{
		printf("DER_ItAsn1_WriteSequence err ..\n");
		return 1;
	}

	//4.����������
	out = malloc((outNode->dataLen + 1));
	if (NULL == out)
	{
		printf("malloc err..\n");
		return 1;
	}
	memset(out, 0, outNode->dataLen + 1);
	memcpy(out, outNode->pData, outNode->dataLen);

	*outData = out;
	*outLen = outNode->dataLen;
	//5.�ͷ��ڴ�
	if (NULL != head)
	{
		DER_ITCAST_FreeQueue(head);
	}
	if (outNode != NULL)
	{
		DER_ITCAST_FreeQueue(outNode);
	}

	return 0;
}

//�򵥽ṹ�����
int TeacherDecode(unsigned char *inData,int inDataLen,teacher_t **t)
{
	int ret = -1;
	ITCAST_ANYBUF *head = NULL;
	ITCAST_ANYBUF *tmpNodeStruct = NULL;
	ITCAST_ANYBUF *tmp = NULL;
	ITCAST_ANYBUF *tmpName = NULL;
	ITCAST_ANYBUF *tmpP = NULL;

	teacher_t *pT = NULL;
	//0.������
	if (NULL == inData || inDataLen <= 0)
	{
		printf("agv err:...\n");
		return -1;
	}

	//1. ����ṹ��
	ret = DER_ITCAST_String_To_AnyBuf(&tmpNodeStruct,inData,inDataLen);
	if (-1 == ret)
	{
		printf("DER_ITCAST_String_To_AnyBuf err ..\n");
		return -1;
	}
	ret = DER_ItAsn1_ReadSequence(tmpNodeStruct,&head);
	if (-1 == ret)
	{
		printf("DER_ItAsn1_ReadSequence err ..\n");
		return -1;
	}

	pT = malloc(sizeof(teacher_t));
	if (NULL == pT)
	{
		printf("malloc failed..\n");
		return -1;
	}
	memset(pT, 0, sizeof(teacher_t));
	//��ʼ����
	//ame
	tmp = head;
	ret = DER_ItAsn1_ReadPrintableString(tmp, &tmpName);
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadPrintableString failed...\n");
		return -1;
	}
	memcpy(pT->name, tmpName->pData,tmpName->dataLen);

	//age
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadInteger(tmp, &(pT->age));
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadInteger failed...\n");
		return -1;
	}

	//p
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadPrintableString(tmp, &tmpP);
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadPrintableString failed...\n");
		return -1;
	}
	//malloc pT->p
	pT->p = malloc(tmpP->dataLen + 1);
	if (NULL == pT->p)
	{
		printf("malloc err: \n");
		return -1;
	}
	memset(pT->p, 0, tmpP->dataLen + 1);
	memcpy(pT->p, tmpP->pData, tmpP->dataLen + 1);

	//pLen
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadInteger(tmp, &(pT->pLen));
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadInteger failed...\n");
		return -1;
	}


	//6. ����
	*t = pT;
	//7. �ͷ��ڴ�
	if (NULL != head)
	{
		DER_ITCAST_FreeQueue(head);
	}
	if (NULL != tmpNodeStruct)
	{
		DER_ITCAST_FreeQueue(tmpNodeStruct);
	}
	if (NULL != tmpName)
	{
		DER_ITCAST_FreeQueue(tmpName);
	}
	if (NULL != tmpP)
	{
		DER_ITCAST_FreeQueue(tmpP);
	}
	return 0;
}

//�򵥽ṹ���ͷ��ڴ�
int TeacherMemFree(teacher_t **t)
{
	teacher_t *pT = NULL;
	if (NULL == t || NULL == *t)
	{
		printf("TeacherMemFree agv err: \n");
		return -1;
	}
	pT = *t;
	if (NULL != pT->p)
	{
		free(pT->p);
	}
	if (NULL != pT)
	{
		free(pT);
	}

	pT = NULL;
	return 0;
}


int testofTeacherEnDecode()
{
	int ret = -1;
	//�����������
	unsigned char *outData = NULL;
	int outDataLen = 0;
	//�������
	teacher_t *pTeacher = NULL;


	//�������ݶ���
	teacher_t t = {
		.name="maomao",
		.age=20,
		.p="hello world..",
		.pLen=13
	};

	//1.���ñ��뺯��
	ret = TeacherEncode(&t, &outData, &outDataLen);
	if (-1 == ret)
	{
		printf("TeacherEncode err..����ʧ��..\n");
		return ret;
	}

	printf("����ɹ�..\n");
	writecodeTofile("../test.ber", outData, outDataLen);
	printf("outData:%s  outDataLen:%d", outData, outDataLen);
	//ok

	//2.���ý��뺯��
	ret = TeacherDecode(outData, outDataLen, &pTeacher);
	if (-1 == ret)
	{
		printf("TeacherDecode failed..\n");
		return -1;
	}
	printf("����ɹ�..\n");
	printf("name: %s ,age: %d ,p: %s, pLen: %d \n", pTeacher->name
		, pTeacher->age
		, (char*)pTeacher->p
		, pTeacher->pLen);

	//3��֤�����Ƿ�ok
	if ((strcmp(t.name, pTeacher->name) == 0) && (t.age == pTeacher->age) && (t.pLen == pTeacher->pLen))
	{
		printf("�����һ��..ok.\n");
	}
	else
	{
		printf("����벻һ��..not..ok.\n");
	}

	//4.�ͷ��ڴ�
	TeacherMemFree(&pTeacher);
}

int main()
{
	int ret = -1;
	//test
	ret = testofTeacherEnDecode();

	printf("test..\n");
	return ret;
}