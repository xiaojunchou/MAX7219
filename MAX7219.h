#ifndef __MAX7219_H__
#define __MAX7219_H__

#define  DECODE_MODE   0x09	//解码模式
#define  INTENSITY     0x0A //亮度
#define  SCAN_LIMIT    0x0B	//扫描位数
#define  SHUT_DOWN     0x0C //工作模式
#define  DISPLAY_TEST  0x0F //显示器自检

void MAX7219_Init(unsigned char Pian,DOWN,MODE,WEI,ITY);//功能寄存器的初始化
void MAX7219_DET(unsigned char wei_cs);
void MAX7219_Digit(unsigned char pianxuan,digit,Biters);//点阵驱动
void MAX7219_W(unsigned char pianxuan,digit,Biters);//数码管驱动


#endif
