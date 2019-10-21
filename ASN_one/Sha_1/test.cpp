#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<openssl/sha.h>


using namespace std;
int main()
{
	int ret = -1;
	SHA_CTX c;
	const void *data = "看看时间，还来得及";

	unsigned char sha[SHA_DIGEST_LENGTH];
	unsigned char buf[SHA_DIGEST_LENGTH * 2 + 1];

	//int SHA1_Init(SHA_CTX *c);
	//int SHA1_Update(SHA_CTX *c, const void *data, size_t len);
	//int SHA1_Final(unsigned char *md, SHA_CTX *c);
	//unsigned char *SHA1(const unsigned char *d, size_t n, unsigned char *md);
	//void SHA1_Transform(SHA_CTX *c, const unsigned char *data);

	
	//1.初始化
	ret = SHA1_Init(&c);
	if (1 != ret)
	{
		cout << "SHA1_Init err.." << endl;
		return 1;
	}
	//2.添加需要哈希的数据
	ret = SHA1_Update(&c, data, strlen((char *)data));
	if (1 != ret)
	{
		cout << "SHA1_Update err.." << endl;
		return 1;
	}
	//3.计算结果
	ret = SHA1_Final(sha,&c);
	if (1 != ret)
	{
		cout << "SHA1_Final err.." << endl;
		return 1;
	}
	memset(buf, 0, SHA_DIGEST_LENGTH * 2 + 1);
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		sprintf((char *)&buf[i * 2], "%02X", sha[i]);
	}
	cout << buf << endl;
	//4.输出结果
	cout << "-----------------------------------------------------" << endl;
	memset(sha, 0, SHA_DIGEST_LENGTH);
	SHA1((unsigned char *)data, strlen((char *)data), sha);

	memset(buf, 0, SHA_DIGEST_LENGTH * 2 + 1);
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		sprintf((char *)&buf[i * 2], "%02x", sha[i]);
	}
	cout << buf << endl;

	cout << "-----------------------------------------------------" << endl;
	cout << "hello worl " << endl;
	return 0;
}