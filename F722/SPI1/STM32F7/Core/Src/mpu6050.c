/*****************************************************************************
  �ļ�: mpu6050.c
  ����: Zhengyu https://gzwelink.taobao.com
  �汾: V1.0.0
  ʱ��: 20200401
	ƽ̨:MINI-F103C8T6

*******************************************************************************/

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "mpu6050.h"
#include "i2c.h"
/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/

/**
  * ��������: д���ݵ�MPU6050�Ĵ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
	HAL_I2C_Mem_Write(&hi2c1,MPU6050_SLAVE_ADDRESS,reg_add,1,&reg_dat,1,1000);
}

/**
  * ��������: ��MPU6050�Ĵ�����ȡ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050_ReadData(uint8_t reg_add,unsigned char*Read,uint8_t num)
{
 HAL_I2C_Mem_Read(&hi2c1,MPU6050_SLAVE_ADDRESS,reg_add,1,Read,num,1000);
}


void Motion_Interrupt(void)             //�˶��ж�
{
    MPU6050_WriteReg(MPU6050_RA_MOT_THR,30);              //�˶���ֵ�����Ҫ���������ȣ����԰�ֵ�ĵ�10����
    MPU6050_WriteReg(MPU6050_RA_MOT_DUR,0x14);            //���ʱ��20ms ��λ1ms 
}

/**
  * ��������: �жϳ�ʼ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU_INT_Init(void)
{

 
//�������塢�˶�����ֹ�ж� ��ѡһ  
//    Free_Fall_Interrupt();                          //���������ж�
   // Motion_Interrupt();                               //�˶��ж�
//    Zero_Motion_Interrupt();                        //��ֹ�ж�
    MPU6050_WriteReg(MPU6050_RA_CONFIG,0x04);           //�����ⲿ���Ų�����DLPF���ֵ�ͨ�˲���
    MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG,0x04);     //���ٶȴ��������̺͸�ͨ�˲�������
//    MPU6050_WriteReg(MPU6050_RA_INT_PIN_CFG,0X1C);      //INT���ŵ͵�ƽƽʱ
//    MPU6050_WriteReg(MPU6050_RA_INT_ENABLE,0x40);       //�ж�ʹ�ܼĴ���
}
/**
  * ��������: ��ʼ��MPU6050оƬ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050_Init(void)
{
  int i=0,j=0;
  //�ڳ�ʼ��֮ǰҪ��ʱһ��ʱ�䣬��û����ʱ����ϵ�����ϵ����ݿ��ܻ����
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++)
    {
      ;
    }
  }
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	    //�������״̬
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //�����ǲ����ʣ�1KHz
	MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	        //��ͨ�˲��������ã���ֹƵ����1K��������5K
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);	  //���ü��ٶȴ�����������2Gģʽ�����Լ�
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	MPU_INT_Init();
	

}

/**
  * ��������: ��ȡMPU6050��ID
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
    MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //��������ַ
	if(Re != 0x68)
	{
		return 0;
	}
	else
	{
		return 1;
	}
		
}

/**
  * ��������: ��ȡMPU6050�ļ��ٶ�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
		MPU6050_ReadData(MPU6050_ACC_OUT, &buf[0], 6);

	
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

/**
  * ��������: ��ȡMPU6050�Ľ��ٶ�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050ReadGyro(short *gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

/**
  * ��������: ��ȡMPU6050��ԭʼ�¶�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050ReadTemp(short *tempData)
{
	uint8_t buf[2];
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //��ȡ�¶�ֵ
	*tempData = (buf[0] << 8) | buf[1];
}

/**
  * ��������: ��ȡMPU6050���¶����ݣ�ת�������϶�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050_ReturnTemp(short*Temperature)
{
	short temp3;
	uint8_t buf[2];
	
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //��ȡ�¶�ֵ
	temp3= (buf[0] << 8) | buf[1];
	*Temperature=(((double) (temp3 + 13200)) / 280)-13;
}

 


