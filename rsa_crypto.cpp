#include "rsa_crypto.h"



rsa_crypto::rsa_crypto( std::string finle_name, bool is_private)
{

	this->private_key = RSA_new();
	this->public_key = RSA_new();
	
	if (is_private)
		this->init_private_key(finle_name);
	else
		this->init_public_key(finle_name);
	
}

rsa_crypto::rsa_crypto()
{
	this->private_key = RSA_new();
	this->public_key = RSA_new();
}

rsa_crypto::~rsa_crypto()
{
	RSA_free(this->private_key);
	RSA_free(this->public_key);

}



int rsa_crypto::generate_key_pair(int bist,  std::string pub,  std::string pri)
{
	if (bist <= 0)
		return -100;

	RSA* key_pair;
	BIGNUM* e;
	BIO* pub_io;
	BIO* pri_io;

	//用于保存秘钥
	key_pair = RSA_new();
	if (key_pair == NULL)
		return - 101;

	//生成秘钥时要是用的数据
	e = BN_new();
	if (e == NULL)
		goto error_1;
	BN_set_word(e,999999);

	//生成秘钥对
	if (RSA_generate_key_ex(key_pair, bist, e, NULL) == 0)
		goto error_1;

	//创建BIO文件对象将公钥写入文件中
	pub_io = BIO_new_file(pub.data(),"w");
	if (pub_io == NULL)
		goto error_1;
	//写入文件
	if (PEM_write_bio_RSAPublicKey(pub_io, key_pair) == 0)
		goto error_3;
	//缓存中的数据刷到文件中
	BIO_flush(pub_io);


	//创建BIO文件对象将私钥钥对写入文件中
	pri_io = BIO_new_file(pri.data(), "w");
	if (pri_io == NULL)
		goto error_3;
	//写入文件
	if (PEM_write_bio_RSAPrivateKey(pri_io, key_pair,
		NULL, NULL, 0, NULL, NULL) == 0)
		goto error_4;
	//缓存中的数据刷到文件中
	BIO_flush(pri_io);
	

	//得到秘钥对
	this->private_key = RSAPrivateKey_dup(key_pair);
	if (this->private_key == NULL)
		goto error_4;
	this->public_key = RSAPublicKey_dup(key_pair);
	if (public_key == NULL)
		goto error_4;


	//释放资源
	BN_free(e);
	RSA_free(key_pair);
	BIO_free(pub_io);
	BIO_free(pri_io);
	return 1;

error_1:
		RSA_free(key_pair);
		return -1;
error_2:
		RSA_free(key_pair);
		BN_free(e);
		return -2;
error_3:
		BN_free(e);
		RSA_free(key_pair);
		BIO_free(pub_io);
		return -3;
error_4:
		BN_free(e);
		RSA_free(key_pair);
		BIO_free(pub_io);
		BIO_free(pri_io);
		return -4;

}

 std::string rsa_crypto::rsa_pubkey_encrypt( std::string data)
{
	if (this->public_key == NULL || data.size() <=0 )
		return	NULL;
	//计算公钥长度
	int key_len = RSA_size(this->public_key);
	//加密
	char* encode = new char[key_len+1];
	int ret = RSA_public_encrypt(data.size(),
		(const unsigned char*)data.data(),
		(unsigned char*)encode,this->public_key,
		RSA_PKCS1_PADDING);
	if (ret ==-1)
	{
		delete[] encode;
		return NULL;
	}

	//加密成功
     std::string ret_str =  std::string();
    ret_str =  std::string(encode,ret);
	delete[] encode;
	return ret_str;

}

 std::string rsa_crypto::rsa_prikey_decrypt( std::string data)
{
	//计算私钥长度
	int key_len = RSA_size(this->private_key);
	//使用私钥解密
	char* decode = new char[key_len+1];
	int ret =  RSA_private_decrypt(data.size(),
		(const unsigned char*)data.data(),
		(unsigned char*)decode,this->private_key,
		RSA_PKCS1_PADDING);
     std::string ret_str =  std::string();
	if (ret == -1)
	{
		delete[] decode;
		return NULL;
	}
		
    ret_str =  std::string(decode,ret);
	delete[] decode;
	return ret_str;
}

 std::string rsa_crypto::rsa_sign( std::string data, sign_level level)
{
	int temp_len = 0;
	char buf[RSA_size(this->private_key) + 1];
	memset(buf,0,RSA_size(this->private_key) + 1);
	;

	if (RSA_sign(level, (const unsigned char*)data.data(),
		data.size(),
		(unsigned char*)buf,
		(unsigned int*)& temp_len,
		this->private_key) 
		==1)
	{
        return  std::string(buf,temp_len);
	}
	return NULL;
}

bool rsa_crypto::rsa_verify( std::string data, std:: string sign_data, sign_level level)
{
	if (RSA_verify(level, 
		(const unsigned char*)data.data(),
		data.size(),
		(const unsigned char*)sign_data.data(),
		RSA_size(this->public_key),
		this->public_key)==1)
		return true;

	return false;
}

int rsa_crypto::get_key_siz()
{
	for (int i = 0; i < 5; i++)
	{
		if (*(((char*)this->private_key) + i) != '\0')
		{
			break;
		}

		if (i==4)
		{
			return RSA_size(this->private_key);
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		if (*((char*)this->public_key) + i == '\0')
		{

			break;
		}
		if (i == 4)
		{
			return RSA_size(this->public_key);
		}

	}

	return -1;

	
}



bool rsa_crypto::init_public_key( std::string finle_name)
{
	//创建读秘钥的BIO
	BIO* pub_bio = BIO_new_file(
		finle_name.data(),"r");
	//从文件中读取公钥
	if (PEM_read_bio_RSAPublicKey(pub_bio,&this->public_key,
		NULL,NULL) == NULL)
	{
		BIO_free(pub_bio);
		return false;
	}

	BIO_free(pub_bio);
	return true;
}

bool rsa_crypto::init_private_key( std::string finle_name)
{
	//创建读秘钥的BIO
	BIO* pri_bio = BIO_new_file(
		finle_name.data(), "r");
	//从文件中读取私钥
	if (PEM_read_bio_RSAPrivateKey(pri_bio, &this->private_key,
		NULL, NULL) == NULL)
	{
		BIO_free(pri_bio);
		return false;
	}

	BIO_free(pri_bio);
	return true;
}
