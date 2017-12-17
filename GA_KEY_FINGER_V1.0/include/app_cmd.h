#ifndef __APP_CMD_H_
#define __APP_CMD_H_


#pragma pack(1)/*ָ����1�ֽڶ���*/

typedef enum{	
	EF_NORMAL=0,
	RSA_PUB=0x0A,
	RSA_PRI=0x0B,
	SM2_PUB=0x0D,
	SM2_PRI=0x0E,
	CERT_FILE=0x0C,
	PRINT_FILE=0X0F
}APP_FILE_TYPE;


#define KEY_CMD_DEVAUTH  0x0050

typedef struct
{
	unsigned short cmd;
	unsigned short (*function)();
}CMD_TABLE;


typedef struct
{
	unsigned char type;
	unsigned char key_sta;
	unsigned char iv_sta;
	unsigned char rfu;
	unsigned char key[16];
	unsigned char iv[16];
	unsigned char init;
}CRYPT_DATA;


typedef struct
{	
	unsigned char state;
	unsigned char type;
	unsigned char keyid[2];//�Ự��ԿID	
	unsigned char key[16];
}SESSION_KEY;


#pragma pack () /*ȡ��ָ�����룬�ָ�ȱʡ����*/


#endif

