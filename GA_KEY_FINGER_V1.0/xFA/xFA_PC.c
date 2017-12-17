
//
// ��Ϣ��ʾ ����
//
void xMessageNormal(String tStr)
{
}

//
// ��Ϣ���� ����
//
void ProcessMessages()
{
  //
  // ���������Ϣ���������Է�ֹ�������
  //
}

/*
ע�⣺
    1��ָ��ע�� �� ָ����֤ģ��ο����������
    2����Ҫ�� COS �˵� xFA_SDK.h �е�ĳЩ����ͨ�� USB ͨѶ�� PC �˷�װ��ͬ������
*/
#include "xFA_SDK.h"

//
// ָ��ע��ģ��
//
void EnrollFinger()
{
  int
    result,
    countThreshold = 3, // ע����Ҫ�ɼ��Ĵ���
    sameFinger = 1, // ע��ʱ�Ƿ���Ҫͬһ����ָ
    count; // ע��ɹ��ɼ��Ĵ���
  unsigned int
    timeout = 8000, // �ɼ�ָ�Ƶȴ��û�ʱ�䣬Ĭ�� 8 �룬1000 ��Ϊ 1 ��
    V;
  unsigned char
    Q, C;
  String
    tStr;

  xMessageNormal("ָ��ע���С���");

  result = xFA_TemplateInit();
  if (1 != result)
  {
    xMessageNormal("fail - xFA_TemplateInit() !");
    goto gt_close;
  }
  xMessageNormal("ok - xFA_TemplateInit() .");
  count = 0;
  while (1)
  {
    //
    // ������������Ϣ���������Է�ֹ�������
    //
    ProcessMessages(); // ��ֹ�������

    xMessageNormal(tStr.sprintf("�� %d ��ָ�Ʋɼ��У��� %d �Σ����밴��ָ����", count + 1, countThreshold));
    result = xFA_GetImage(timeout);
    if (1 == result)
    {
      xMessageNormal("ָ������ֵ��ȡ�У����Ժ򡭡�");

      result = xFA_ProcessReturnQCV(&Q, &C, &V);
      if (1 == result)
      {
        xMessageNormal(tStr.sprintf("ok -- Q = %d, C = %d, V = %d", Q, C, V));
        if (Q < 60 || C < 5 || V < 18000)
        {
          xMessageNormal("����̫������²ɼ�����");
          //
          // ��ָ���
          //
          result = xFA_FingerDetect();
          if (1 == result)
          {
            xMessageNormal("��̧����ָ����");
            while (1 == xFA_FingerDetect()) // �ȴ���ָ̧����
            {
              ProcessMessages(); // ��ֹ�������
            }
            continue;
          }
          else if (0 != result)
          {
            xMessageNormal("fail - xFA_FingerDetect(...)�������豸������ !");
            goto gt_close;
          }
          continue;
        }

        xMessageNormal("ģ�������С���");
        result = xFA_AddToTemplate(countThreshold, sameFinger, &count);
        switch (result)
        {
          case 0x9000 : // 0x9000��ģ��ɹ�����
          {
            xMessageNormal(tStr.sprintf("ok -- ָ��ע��ɹ� ��[ %d / %d ]�����Խ���д�롭��", count, countThreshold));
            goto gt_close;
          }
          case 0x9010 : // 0x9010�����β����ɹ���ɣ�����ģ������û����ɣ���Ҫ�����˲���
          {
            xMessageNormal(tStr.sprintf("δ��ɣ��������������Ч�� %d / ���� %d��", count, countThreshold));
            //
            // ��ָ���
            //
            result = xFA_FingerDetect();
            if (1 == result)
            {
              xMessageNormal("��̧����ָ����");
              while (1 == xFA_FingerDetect()) // �ȴ���ָ̧����
              {
                ProcessMessages(); // ��ֹ�������
              }
              continue;
            }
            else if (0 != result)
            {
              xMessageNormal("fail - xFA_FingerDetect(...)�������豸������ !");
              goto gt_close;
            }
            continue;
          }
          case 0x9011 : // 0x9011��û�г�ʼ�������ȵ��� xFA_TemplateInit() ���г�ʼ��
          {
            xMessageNormal("fail -- ���ȵ��� xFA_TemplateInit() ���г�ʼ������");
            goto gt_close;
          }
          case 0x9014 : // 0x9014���ﵽ���������ƣ�ע��ģ��ʧ��
          {
            xMessageNormal("fail -- ָ��ע��ʧ�ܣ������δ�ɹ����ﵽ���������ƣ�");
            goto gt_close;
          }
          default :
          {
            // 0x9012������ģ��Ƿ� �� ����ֵ�Ƿ���ע��ģ��ʧ��
            // 0x9013������ģ���ڲ��㷨�����߼����⣬��Ҫ���ԣ�ע��ģ��ʧ��
            // 0x9016��ģ���ʼ�����󣬿����Ƕ����ģ�� Buf �� ʵ�ʲ����� Buf ��һ��Ŷ��
            // 0x9017���������ָ������У��ʧ�ܣ�
            // 0x9018������ֵ �� ����ģ�� �е����������⣬�ȶ�ʱ���ظ�ֵ
            // 0x9019�������⣬��Ҫ������� 4
            // 0x9015��ע��ģ��δ֪����
            xMessageNormal(tStr.sprintf("fail -- ָ��ע��ʧ�ܣ��������룺0x%04X��", (unsigned short)result));
            goto gt_close;
          }
        }
      }
      else
      {
        xMessageNormal("fail -- xFA_ProcessReturnQCV(...) !");
        goto gt_close;
      }
    }
    else if (0 == result)
    {
      xMessageNormal("time out !");
      goto gt_close;
    }
    else
    {
      xMessageNormal("fail - xFA_GetImage(...)�������豸������ !");
      goto gt_close;
    }
  }

gt_close:
  return;
}

void __fastcall TForm1::Button50Click(TObject *Sender)
{
  String
    tStr;
  int
    result,
    sThreshold = 40; // �ȶ����ޣ�����ֵ 40��Ҳ��30
  unsigned int
    timeout = 8000;
  unsigned char
    Q, C;
  unsigned int
    V;


  xMessageNormal("ָ��ʶ���С���");
  xMessageNormal("�밴��ָ����");
  result = xFA_GetImage(timeout);
  if (1 == result)
  {
    xMessageNormal("ָ������ֵ��ȡ�У����Ժ򡭡�");

    result = xFA_ProcessReturnQCV(&Q, &C, &V);
    if (1 == result)
    {
      xMessageNormal(tStr.sprintf("ok -- Q = %d, C = %d, V = %d", Q, C, V));
      xMessageNormal("�ȶ��У����Ժ򡭡�");
      result = xFA_MatchFinger(0xFF, sThreshold); // 0xFF ����ָ��洢��ȫ��ָ�ƽ��бȶ�
      if (1 == result)
      {
        xMessageNormal("�ȶԳɹ������ȶ�Ϊ��ָͬ�ƣ�");
      }
      else if (0 == result)
      {
        if (Q < 60 || C < 5 || V < 18000)
        {
          xMessageNormal("�ȶ�ʧ�ܣ�������̫�");
        }
        else
        {
          xMessageNormal("�ȶ�ʧ�ܣ����ȶ�Ϊ��ָͬ�ƣ�");
        }
      }
      else
      {
        xMessageNormal("�ȶԺ���ִ�д��� ��");
        goto gt_close;
      }
    }
    else
    {
      xMessageNormal("fail -- xFA_ProcessReturnQCV(...) !");
      goto gt_close;
    }
  }
  else if (0 == result)
  {
    xMessageNormal("time out !");
    goto gt_close;
  }
  else
  {
    xMessageNormal("fail - xFA_GetImage(...)�������豸������ !");
    goto gt_close;
  }

gt_close:
  return;
}

void fingertest()
{
	int result;
	int count,num;
	unsigned int V,timeout=8000;int countThreshold=3;
	
	UART_printf("ָ��ע���С���");
	num=xFA_ReadAllFingerCount();
UART_printf("ָ������  %d\r\n",num);

#if 0
  result = xFA_TemplateInit();
  if (1 != result)
  {
    UART_printf("fail - xFA_TemplateInit() !");
    goto gt_close;
  }
  UART_printf("ok - xFA_TemplateInit() .");
  count = 0;
  while (1)
  {
    //
    // ������������Ϣ���������Է�ֹ�������
    //
	 UART_printf("START\r\n");
    result = xFA_GetImage(timeout);
    if (1 == result)
    {
      UART_printf("ָ������ֵ��ȡ�У����Ժ򡭡�");

      result = xFA_ProcessReturnQCV(G_XFA_Data, G_XFA_Data+1, &V);
      if (1 == result)
      {
        if (G_XFA_Data[0] < 60 || G_XFA_Data[1] < 5 || V < 18000)
        {
          UART_printf("����̫������²ɼ�����");
          //
          // ��ָ���
          //
          result = xFA_FingerDetect();
          if (1 == result)
          {
            UART_printf("��̧����ָ����");
            while (1 == xFA_FingerDetect()) // �ȴ���ָ̧����
            {
            }
            continue;
          }
          else if (0 != result)
          {
            UART_printf("fail - xFA_FingerDetect(...)�������豸������ !");
            goto gt_close;
          }
          continue;
        }

        UART_printf("ģ�������С���");
        result = xFA_AddToTemplate(countThreshold, 1, &count);
        switch (result)
        {
          case 0x9000 : // 0x9000��ģ��ɹ�����
          {
            UART_printf("ok -- ָ��ע��ɹ� �����Խ���д�롭��");
            goto gt_success;
          }
          case 0x9010 : // 0x9010�����β����ɹ���ɣ�����ģ������û����ɣ���Ҫ�����˲���
          {
            UART_printf("δ��ɣ��������������Ч�� %d / ���� %d��", count, countThreshold);
            //
            // ��ָ���
            //
            result = xFA_FingerDetect();
            if (1 == result)
            {
              UART_printf("��̧����ָ����");
              while (1 == xFA_FingerDetect()) // �ȴ���ָ̧����
              {

              }
              continue;
            }
            else if (0 != result)
            {
              UART_printf("fail - xFA_FingerDetect(...)�������豸������ !");
              goto gt_close;
            }
            continue;
          }
          case 0x9011 : // 0x9011��û�г�ʼ�������ȵ��� xFA_TemplateInit() ���г�ʼ��
          {
            UART_printf("fail -- ���ȵ��� xFA_TemplateInit() ���г�ʼ������");
            goto gt_close;
          }
          case 0x9014 : // 0x9014���ﵽ���������ƣ�ע��ģ��ʧ��
          {
            UART_printf("fail -- ָ��ע��ʧ�ܣ������δ�ɹ����ﵽ���������ƣ�");
            goto gt_close;
          }
          default :
          {
            // 0x9012������ģ��Ƿ� �� ����ֵ�Ƿ���ע��ģ��ʧ��
            // 0x9013������ģ���ڲ��㷨�����߼����⣬��Ҫ���ԣ�ע��ģ��ʧ��
            // 0x9016��ģ���ʼ�����󣬿����Ƕ����ģ�� Buf �� ʵ�ʲ����� Buf ��һ��Ŷ��
            // 0x9017���������ָ������У��ʧ�ܣ�
            // 0x9018������ֵ �� ����ģ�� �е����������⣬�ȶ�ʱ���ظ�ֵ
            // 0x9019�������⣬��Ҫ������� 4
            // 0x9015��ע��ģ��δ֪����
            UART_printf("fail -- ָ��ע��ʧ�ܣ��������룺0x%04X��", (unsigned short)result);
            goto gt_close;
          }
        }
      }
      else
      {
        UART_printf("fail -- xFA_ProcessReturnQCV(...) !");
        goto gt_close;
      }
    }
    else if (0 == result)
    {
      UART_printf("time out !");
      goto gt_close;
    }
    else
    {
      UART_printf("fail - xFA_GetImage(...)�������豸������ !");
      goto gt_close;
    }
  }
gt_success:
#endif
  if(0)
  {
  	unsigned char buf[33]={0};
	
	
	buf[0]=1;
	if(xFA_WriteTemplateToAFinger(1,buf)==1)	
		 UART_printf("ע��ɹ�\r\n");
	else
		 UART_printf("ע��ʧ��\r\n");

	num=xFA_ReadAllFingerCount();
	UART_printf("ָ������  %d\r\n",num);
  }

  num=xFA_ReadAllFingerCount();
	UART_printf("ָ������  %d\r\n",num);

	if(1)		
	{
		int sThreshold=40;
		result = xFA_GetImage(timeout);
		if (1 == result)
		{
			UART_printf("ָ������ֵ��ȡ�У����Ժ򡭡�");
			result = xFA_ProcessReturnQCV(p_G_XFA_Q, p_G_XFA_C, &G_XFA_V);
			if (1 == result)
			{
				UART_printf("�ȶ��У����Ժ򡭡�");
				 result = xFA_MatchFinger(0xFF, sThreshold); // 0xFF ����ָ��洢��ȫ��ָ�ƽ��бȶ�
				if (1 == result)
				{
		        		UART_printf("�ȶԳɹ������ȶ�Ϊ��ָͬ�ƣ�");
		     		}
				else if (0 == result)
			      {
			        	if (*p_G_XFA_Q < 60 || *p_G_XFA_C < 5 || G_XFA_V < 18000)
					{
			          		UART_printf("�ȶ�ʧ�ܣ�������̫�");
			        	}
			        	else
			        	{
			         		UART_printf("�ȶ�ʧ�ܣ����ȶ�Ϊ��ָͬ�ƣ�");
			        	}
			      }
			
		    }
		    else
		    {
				UART_printf("fail -- xFA_ProcessReturnQCV(...) !");
		    }
		}
		
	}

gt_close:
	 UART_printf("fail -  !");
  return;
}

void sm4_test()
{
	unsigned char test[]={0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,8};
	unsigned char iv[16]={0};
	unsigned char key[16]={0x0A,0xDB,0x9B,0x65,0x76,0xDC,0x86,0x66,0x1B,0x33,0x27,0xEB,0xE3,0xF2,0xED,0x7B};

	unsigned char out[16];

	hal_sm4_oper(test,32,key,iv,SYMALG_SENC|SYMALG_CBC,out);
	HAL_UART_SEND_ASC(out,32);
	hal_sm4_oper(test,32,key,iv,SYMALG_SENC|SYMALG_CBC,out);
	HAL_UART_SEND_ASC(out,32);
}

void sm2_test()
{
	unsigned char pub[64],pri[32];

	unsigned char buf[16],out[128]={0};
	unsigned char data[]={0,1,2,3,4,5,6,7,8};

	UART_printf("����SM2��˽Կ\r\n");

	hal_sm2_init();
	UART_printf("����SM2��˽Կ1\r\n");
	hal_alg_SM2producekeys(pub,pri);

	hal_alg_SM2encrypt(pub,data,8,out);

	hal_alg_SM2decrypt(pri,out,104,buf);
	
	HAL_UART_SEND_ASC(pub,64);
	HAL_UART_SEND_ASC(pri,32);
	HAL_UART_SEND_ASC(out,104);
	HAL_UART_SEND_ASC(buf,16);
}

