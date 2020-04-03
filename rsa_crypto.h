
#include<iostream>
#include<string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include<time.h>
#include<string.h>

//类的功能：
	//1、封装了非对称加密

//带更新功能
	//1、对秘钥、密文，进行bash64编码，便于使用
	//2、不要返回NULL

//枚举，加密级别
enum sign_level
{
	level1 = NID_md5,
	level2 = NID_sha1,
	level3 = NID_sha224,
	level4 = NID_sha256,
	level5 = NID_sha384,
	level6 = NID_sha512
};

class rsa_crypto
{
public:
	//功能：构造，获取保存在文件中的秘钥
	//参数1：文件名
	//参数2：获取公钥或私钥,true私钥，false公钥
    rsa_crypto( std::string finle_name,
		bool is_private=true);
	
	//功能：构造，为成员变量分配空间
	rsa_crypto();

	//功能：析构，释放成员变量的空间
	~rsa_crypto();

	//功能：生成秘钥对,同时秘钥保存到文件中
	//参数1：秘钥的长度，单位是位(bit)
	//参数2：保存公钥的文件
	//参数3：保存私钥的文件
	//成功返回：1，失败返回：负数
	int  generate_key_pair(int bist,
         std::string pub = "public.pem",
         std::string pri = "private.pem");

	//功能：使用公钥加密
	//参数：传入需要加密的数据
	//返回值：
		//成功返回加密后的数据
		//失败返回：NULL
     std::string rsa_pubkey_encrypt( std::string data);
	
	//功能：使用私钥解密
	//参数：传入需要解密的数据
	//返回值：
		//成功返回:解密后的数据
		//失败返回：NULL
     std::string rsa_prikey_decrypt( std::string data);

	//功能：使用RSA签名
	//参数1：需要签名的哈希值或数据
	//参数2：选择哈希算法
	//成功返回：签名后的密文，失败返回：NULL
     std::string rsa_sign( std::string data,
		sign_level level =level3);

	//使用RSA验证签名
	//参数1：原始哈希数据
	//参数2：加密后的哈希数据
	//参数3：选择哈希算法
	//成功返回：true,失败返回：false
    bool rsa_verify( std::string data, std::string sign_data,
		sign_level level = level3);

	int get_key_siz();


private:
	//功能：获取保存在文件中的公钥或私钥
	//参数：传入保存秘钥的文件名
    bool init_public_key( std::string finle_name);
    bool init_private_key( std::string finle_name);

private:
	RSA* public_key;
	RSA* private_key;
};
