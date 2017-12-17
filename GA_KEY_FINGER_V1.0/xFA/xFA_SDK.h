// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _xFA_SDK_H_
#define _xFA_SDK_H_

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#define _IN_
#define _OUT_

#define def_maxMeSize               (248)  // ָ������ֵ�ֽ���
#define def_template_size           (1024) // ָ��ע��ģ���ֽ���
#define def_FingerMaxCount          (10) // ��� 10 ö��ָ

#define def_no_size       (1)  // �洢ָ�Ʊ�� 1 �ֽ�
#define def_public_size   (16) // �洢ָ�ƹ�����Ϣ 16 �ֽ�
#define def_private_size  (16) // �洢ָ��˽����Ϣ 16 �ֽ�

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//
// MOC �㷨�ӿڷ�����
//

#define def_xFA_OK                  (0x9000) // ִ����ȷ���ȶԳɹ���ͬһ��ָ��

#define def_xFA_MatchFalse          (0x9001) // �ȶԳɹ�������ͬһ��ָ��
#define def_xFA_Func_NotFinished    (0x90FF) // ָ����������δ���
#define def_xFA_FPC1080_FingerOn    (0x90F0) // FPC1080 ��⵽��ָ
#define def_xFA_FPC1080_Finished    (0x90F1) // FPC1080 �����ɼ�����
#define def_xFA_NoFinger_invalid    (0x90E0) // ָ����ŵ�ָ�Ʋ�����

#define def_xFA_Base_Er             (0x6A80) // �����뿪ʼ
#define def_xFA_Unknown_Er          (def_xFA_Base_Er) // δ֪����
#define def_xFA_Ins_Er              (def_xFA_Base_Er + 0x0001) // �����ִ�
#define def_xFA_Ret_Er              (def_xFA_Base_Er + 0x0002) // ����ʱ������
#define def_xFA_Addr_Er             (def_xFA_Base_Er + 0x0003) // ��ַ����
#define def_xFA_DataChk_Er          (def_xFA_Base_Er + 0x0004) // ����У����󣬼����ݲ��Ϸ���ָ��ģ�� �� ָ������ֵ ���ݴ���
#define def_xFA_FlashWrite_Er       (def_xFA_Base_Er + 0x0005) // ����д�� Flash ����
#define def_xFA_MOC_Er              (def_xFA_Base_Er + 0x0006) // MOC ���رȶ�ʧ�ܴ�������ֵ���ݴ���
#define def_xFA_CRC_Er              (def_xFA_Base_Er + 0x0007) // У��ֵ����
#define def_xFA_DataInfo_Er         (def_xFA_Base_Er + 0x0008) // Ҫд������ݴ���
#define def_xFA_FingerData_Er       (def_xFA_Base_Er + 0x0009) // ָ��ģ�� �� ָ������ֵ ���ݴ���

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef struct _typ_xFA_VersionInfo
{
  unsigned int
    version; // �㷨�汾��
  char
    author[16], // �㷨����
    copyright[16], // �㷨��Ȩ
    mobile[32], // �㷨�����ֻ���
    email[32], // email
    QQ_WeiXin[48], // QQ �� ΢��

    company[32], // ��˾����
    chip[32], // оƬ����
    sensor[36]; // ֧�ֵ� sensor ��������
  unsigned short
    sensorType,
    sensorH,
    sensorW,
    sensorDpi;
}typ_xFA_VersionInfo; // 256 �ֽ� <= 4 + 16 + 16 + 32 + 32 + 48 + 32 + 32 + 36 + 8

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//
// ��ȡ�㷨�汾����Ϣ
//
// �ɹ����� 1��ʧ�ܷ��� 0
//
extern
int xFA_ReadVersionInfo(typ_xFA_VersionInfo *info);

//
// �������ܣ�ָ���㷨��ʼ��������������ʼ��һ�μ���
//
extern
void xFA_Init();

//
// �������ܣ������ָ�Ƿ���
//
// ���� 0 ��ʾû�м�⵽��ָ
// ���� 1 ��ʾ��⵽��ָ
// ���� -1 ��ʾ�ɼ�������
//
extern
int xFA_FingerDetect();

//
// �������ܣ�ָ�Ʋɼ�
//
// unsigned int timeout����ʱʱ������������������ 8000 ��ʾ 8 �룩��Ĭ��ֵ 8000
//
// ���� 0 ��ʾ��ʱ
// ���� 1 ��ʾ�ɼ��ɹ�
// ���� -1 ��ʾ�ɼ�������
//
extern
int xFA_GetImage(unsigned int timeout);

//
// �������ܣ�ָ��������ȡ
//
// �������أ����� Q����������� C����Ч��� V������Ӧ�ò���и����жϣ�
//
// ���� 0 ��ʾʧ��
// ���� 1 ��ʾ�ɹ�
//
extern
int xFA_ProcessReturnQCV(unsigned char *XFA_Q, unsigned char *XFA_C, unsigned int *XFA_V);

//
// �������ܣ�ע��ģ���ʼ��
//
// �ɹ����� 1��ʧ�ܷ��� 0
//
extern
int xFA_TemplateInit();

//
// �������ܣ�����ȷ��ȡ��ָ�������ϲ���ָ��ģ��
//
// �� xFA_ProcessReturnQCV ֮��ִ�У�
//
// int countThreshold����ʾָ��ע�����������ֵΪ 3 ��
// int sameFinger����ʾע���Ƿ����Ϊͬһ����ָ��0 - ����Ϊ��ͬ��ָ��1 - ����Ϊͬһ����ָ
// int *count�����ص�ǰ��Ч����
//
// �������أ�
// 0x9000��ģ��ɹ�����
// 0x9010�����β����ɹ���ɣ�����ģ������û����ɣ���Ҫ�����˲���
// 0x9011��û�г�ʼ�������ȵ��� xFA_TemplateInit() ���г�ʼ��
// 0x9012������ģ��Ƿ� �� ����ֵ�Ƿ���ע��ģ��ʧ��
// 0x9013������ģ���ڲ��㷨�����߼����⣬��Ҫ���ԣ�ע��ģ��ʧ��
// 0x9014���ﵽ���������ƣ�ע��ģ��ʧ��
// 0x9016��ģ���ʼ�����󣬿����Ƕ����ģ�� Buf �� ʵ�ʲ����� Buf ��һ��Ŷ��
// 0x9017���������ָ������У��ʧ�ܣ�
// 0x9018������ֵ �� ����ģ�� �е����������⣬�ȶ�ʱ���ظ�ֵ
// 0x9019�������⣬��Ҫ������� 4
// 0x9015��ע��ģ��δ֪����
//
extern
unsigned short xFA_AddToTemplate(int countThreshold, int sameFinger, int *count);

//
// �������ܣ����ָ����ŵ�ָ��
//
// int No��������ָ����ţ�No ����Ϊ��0 - 9��
//
// ���� 0 ��ʾʧ��
// ���� 1 ��ʾ�ɹ�
//
extern
int xFA_CheckAFinger(int No);

//
// �������ܣ����ָ�����ݣ�����δ�洢��ָ����������
//
// ������ȷ���� 1,
// ���ݴ��󷵻� 0
//
extern
int xFA_CheckAllFinger();

//
// �������ܣ���ȡָ����ŵ�ָ�Ƶ� No �ţ�public, private ��Ϣ
//
// int No������ȡ��ָ����ţ�No ����Ϊ��0 - 9��
// unsigned char info[def_no_size + def_public_size + def_private_size]����ȡ����Ϣ��No + public + private
//
// ���� 0 ��ʾʧ�ܣ�ָ����ŵ�ָ�Ʋ����ڻ����ݷǷ�
// ���� 1 ��ʾ�ɹ�
//
extern
int xFA_ReadAFingerInfo(_IN_ int No, _OUT_ unsigned char info[def_no_size + def_public_size + def_private_size]);

//
// �������ܣ���ȡ�洢����Чָ�Ƶĸ���
//
// ���ش洢����Чָ�Ƹ�����-1 Ϊ��ȡʧ��
//
extern
int xFA_ReadAllFingerCount();

//
// �������ܣ�ɾ��ָ����ŵ�ָ��
//
// int No����ɾ����ָ����ţ�No ����Ϊ��0 - 9��
//
// ���� 0 ��ʾʧ��
// ���� 1 ��ʾ�ɹ�
//
extern
int xFA_EraseAFinger(int No);

//
// �������ܣ�ɾ��ȫ��ָ��
//
// ���� 0 ��ʾʧ��
// ���� 1 ��ʾ�ɹ�
//
extern
int xFA_EraseAllFinger();

//
// �������ܣ���ָ����Ϣ��public �� private����ͬ��ȷ���ɵ�ָ��ģ��д��ָ�����
//
// �ڳɹ�����ָ��ģ���ִ�У��� xFA_AddToTemplate(...) ���� 0x9000 �ɹ���ɽ�ָ��д����Ҫ�ı�Ŵ�
//
// int No����д���ָ����ţ�No ����Ϊ��0 - 9��
// unsigned char info[def_no_size + def_public_size + def_private_size]��ָ�Ʊ�� + public + private ��Ϣ
//
// ���� 0 ��ʾʧ��
// ���� 1 ��ʾ�ɹ�
//
extern
int xFA_WriteTemplateToAFinger(int No, _IN_ unsigned char info[def_no_size + def_public_size + def_private_size]);

//
// �������ܣ�����ȷ��ȡ��ָ��������ָ����ŵ�ָ�ƽ��бȶԣ�
//           ��� No ����������ȫ�������ָ�ƽ��бȶ�
//
// �� xFA_ProcessReturnQCV(...) ֮��ִ�У�
//
// int No�����ȶԵ�ָ����ţ�No ����Ϊ��0 - 9����
//         ��� No �������ޣ�0 - 9������ȫ�������ָ�ƽ��бȶ�
//         �� No ������ MatchA ���� MatchAll
// int sThreshold���ȶ����ƶ����ޣ�����ֵΪ 40������ 30
//
// ���� 1 �ȶԳɹ�
// ���� 0 �ȶ�ʧ�ܣ�����ͬһ����ָ
// ���� -1 Ϊ�ȶԺ���ִ�д��󣬿���Ϊ����ֵ �� ָ��ģ�����ݷǷ�
//
extern
int xFA_MatchFinger(int No, int sThreshold);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

#endif // _xFA_SDK_H_

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
