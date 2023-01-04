#include <REGX52.H>

/*功能寄存器定义*/
#define  DECODE_MODE   0x09	//解码模式
#define  INTENSITY     0x0A //亮度
#define  SCAN_LIMIT    0x0B	//扫描位数
#define  SHUT_DOWN     0x0C //工作模式
#define  DISPLAY_TEST  0x0F //显示器自检

/*位选寄存器地址定义*/
#define  D_1  0x01
#define  D_2  0x02
#define  D_3  0x03
#define  D_4  0x04
#define  D_5  0x05
#define  D_6  0x06
#define  D_7  0x07
#define  D_8  0x08

/*控制端口定义*/
sbit DIN=P1^0; 
sbit CLK=P1^2;

sbit LOAD1=P1^1;
sbit LOAD2=P1^3;
sbit LOAD3=P1^4;

unsigned char GESHI;


/**----------------------------------------------------------------------------------------------
  * @brief  数据二进制循环移位数据
  * @param  biter	要转换的数据

  * @retval dier 转换好的数据8位
---------------------------------------------------------------------------------*/
unsigned char biter_zuo(unsigned char biter)
{
	biter = biter << 7 | biter >> 1;
	return biter;
}

/**----------------------------------------------------------------------------------------------
  * @brief  基本函数，写入一个8位数据0xXX 
  * @param  temp：写入的字节
  * @retval 无
---------------------------------------------------------------------------------*/
void Max7219_Wbyte(unsigned char temp)
{
	unsigned char i;
	for (i=0;i<8;i++)
	{
		CLK = 0;
		DIN = temp&(0x80>>i);
		CLK = 1;
	}
}

/**----------------------------------------------------------------------------------------------
  * @brief  调试函数，传输原地址，数据,数码管数据

  * @param  pianxuan：片选，选择要写入的芯片序号1-3
			digit：	  功能命令地址
			Biters：  要传的数据
  * @retval 无
---------------------------------------------------------------------------------*/
void MAX7219_W(unsigned char pianxuan,digit,Biters)
{
	if(pianxuan == 1)
	{
		LOAD1 = 0;
		Max7219_Wbyte(digit);
		Max7219_Wbyte(Biters);
		LOAD1 = 1;
	}
	if(pianxuan == 2)
	{
		LOAD2 = 0;
		Max7219_Wbyte(digit);
		Max7219_Wbyte(Biters);
		LOAD2 = 1;
	}	
	if(pianxuan == 3)
	{
		LOAD3 = 0;
		Max7219_Wbyte(digit);
		Max7219_Wbyte(Biters);
		LOAD3 = 1;
	}
}

/**----------------------------------------------------------------------------------------------
  * @brief  点阵驱动应用函数，可以将数据自动经过转换后正常显示

  * @param  pianxuan：片选 1-3
			digit：	  位选
			Biters：  传的数据
  * @retval 无
---------------------------------------------------------------------------------*/
void MAX7219_Digit(unsigned char pianxuan,digit,Biters)
{
	Biters = biter_zuo(Biters);
	MAX7219_W(pianxuan,digit,Biters);
}

/**----------------------------------------------------------------------------------------------
  * @brief 	MAX7219初始化
  * @param  Pian	片选选择1-255（这款芯片最多级联255块）
			DOWN	运行模式：1或0（开机1，关机0）
			MODE	解码模式：0x01到0xFF（就是将传输的数据转换成对应数码管段码）
			WEI		扫描位数选择：0-7
			ITY		亮度选择 0x00到0x0F

  * @retval 无
---------------------------------------------------------------------------------*/
void MAX7219_Init(unsigned char Pian,DOWN,MODE,WEI,ITY)     
{
	GESHI = MODE;
	MAX7219_W(Pian,SHUT_DOWN, DOWN);   	//正常运行:0xx1 关机模式:0xx0
	MAX7219_W(Pian,DISPLAY_TEST, 0x00);  //正常运行:0xx0 显示测试模式:
	MAX7219_W(Pian,DECODE_MODE, MODE);   //解码模式选择 BOS码
	MAX7219_W(Pian,SCAN_LIMIT, WEI);   	//扫描限制:0~7 0xX0~0xX7
	MAX7219_W(Pian,INTENSITY, ITY);   	//亮度选择0xX0~0xXF
}

/**----------------------------------------------------------------------------------------------
  * @brief  清屏
  * @param  wei_cs	哪个个芯片清屏

  * @retval 无
---------------------------------------------------------------------------------*/
void MAX7219_DET(unsigned char wei_cs)
{
	unsigned char DET;
	if(GESHI == 0x00)
	{
		for(DET=0;DET<8;DET++)
		{
			MAX7219_W(wei_cs,DET+1,0x00);
		}
	}
	else
	{
		for(DET=0;DET<8;DET++)
		{
			MAX7219_W(wei_cs,DET+1,0x7F);
		}
	}
}
