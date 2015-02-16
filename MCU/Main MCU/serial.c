//�ٶ�����оƬ�Ĺ���Ƶ��Ϊ12MHz

#include "reg52.h"
#include "intrins.h"

//-----------------------------------------------

unsigned char dat;

sbit p10=P1^0;
sbit p11=P1^1;

void InitUart();

int count=0;


void Intr() interrupt 0  //�ж�
{
	count = 1;
	dat = P0;
	TI = 1;

}

void main()
{
    InitUart();                     //��ʼ������
    ES = 1;
    EA = 1;
	TI = 0;

	IT0 = 1;   //��ʼ���ж�
	EX0 = 1;

	p10=0;
	while (1);
}

/*----------------------------
UART �жϷ������
-----------------------------*/
void Uart() interrupt 4 using 1
{
 
	if (TI)
    {
        TI = 0;                     //���TIλ
        if (count != 0)
        {
            count--;
            SBUF = dat;          //��������Ӧ������
        }
    }

    if (RI)
    {
        RI = 0;                     //���RIλ
        count = 1;
        dat = SBUF;              //��������Ӧ������
		//P1 = dat;

		switch (dat)
		{
			case 0xfe:p10=0;break;
			case 0xfd:p11=0;break;
			case 0x01:p10=1;break;
			case 0x02:p11=1;break;
			case 0xff:P1=0xff;break;
		 	
		}
    }
}

/*----------------------------
��ʼ������
----------------------------*/
void InitUart()
{
    TMOD = 0x20;                //���ö�ʱ��1Ϊ8λ�Զ���װ��ģʽ
	SCON = 0x50;
	PCON = 0x00;
	
    TH1 = 0xfd;
    TL1 = 0xfd;           //������9600
    TR1 = 1;
}

