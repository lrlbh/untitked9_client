
#include<iostream>
#include<openssl/aes.h>
#include<string>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//using namespace std;

//功能：openssl aes对称加密

//带更新功能
	//1、对秘钥、密文，进行bash64编码，便于使用


class aes_crypto
{
public:
	//功能：构造,对象构造失败，成员变量key是空构造
	//参数1：生成秘钥的字符串，长度（size）决定加密的位（bist）
    aes_crypto(std::string key);

	//功能：加密，返回解密后的字符串
    std::string aes_cbc_encrypy(std::string data);
	//功能：解密，返回解密后的字符串
    std::string aes_cbc_decrypy(std::string data);

private:
	//功能：aes 加解密函数
     std::string aes_crypto_cbc( std::string data,int crypto);
	//功能：生成参与加解密运算的字符串（向量）
	void generate_ivec(unsigned char *ivec);
private:
	//保存生成秘钥的字符串，通过这个字符串的长度决定加密级别
     std::string key;

	AES_KEY enc_key;
	AES_KEY dec_key;
};
