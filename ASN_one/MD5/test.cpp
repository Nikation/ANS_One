#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<openssl/md5.h>


using namespace std;
int main()
{
	int ret = -1;
	MD5_CTX c;
	unsigned char md[MD5_DIGEST_LENGTH];
	unsigned char buf[MD5_DIGEST_LENGTH * 2 + 1];

	//int MD5_Init(MD5_CTX *c);
	//int MD5_Update(MD5_CTX *c, const void *data, size_t len);
	//int MD5_Final(unsigned char *md, MD5_CTX *c);
	//unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md);

	const void *data = "看看时间，还来得及";
	//1.初始化
	ret = MD5_Init(&c);
	if (1 != ret)
	{
		cout << "MD5_Init err:.." << endl;
		return 1;
	}
	//2.添加需要哈希的数据
	ret = MD5_Update(&c, data, strlen((char *)data));
	if (1 != ret)
	{
		cout << "MD5_Update err:.." << endl;
		return 1;
	}
	//3.计算结果
	ret = MD5_Final(md, &c);
	if (1 != ret)
	{
		cout << "MD5_Final err:.." << endl;
		return 1;
	}

	//4.输出结果
	cout << md << endl;
	memset(buf, 0, MD5_DIGEST_LENGTH * 2 + 1);
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf((char*)&buf[i * 2], "%02x", md[i]);
	}
	cout << buf << endl;


	cout << "-----------------------------------------------------" << endl;
	memset(md, 0, MD5_DIGEST_LENGTH);
	MD5((unsigned char *)data, strlen((char *)data), md);

	memset(buf, 0, MD5_DIGEST_LENGTH * 2 + 1);
	for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
	{
		sprintf((char *)&buf[i * 2], "%02X", md[i]);
	}
	cout << buf << endl;

	cout << "-----------------------------------------------------" << endl;
	cout << "hello worl " << endl;
	return 0;
}