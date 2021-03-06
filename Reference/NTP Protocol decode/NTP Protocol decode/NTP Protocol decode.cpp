// NTP Protocol decode.cpp: 定义控制台应用程序的入口点。
//
/*
功能：解析NTP时间服务器返回的报文；
ntpSourcePack[48]为返回的报文源码,一定是48个
获取报文：
NTP服务器：time.windows.com/cn.pool.ntp.org/time.nist.gov/
端口：123
方式：UDP
发送内容：
uint8_t packetBuffer[16] = { 0 };
packetBuffer[0] = 0b11100011;   // LI, Version, Mode = 0xE3
packetBuffer[1] = 0x00;     // Stratum, or type of clock
packetBuffer[2] = 0x06;     // Polling Interval
packetBuffer[3] = 0xEC;		// Peer Clock Precision
packetBuffer[12] = 0x49;
packetBuffer[13] = 0x4E;
packetBuffer[14] = 0x49;
packetBuffer[15] = 0x52;

ESP8266 AT指令获取NTP时间方式：
	AT+CIPMUX=0
	AT+CIPSTART="UDP","time.windows.com",123
	AT+CIPSEND=48
	e3 00 06 ec 00 00 00 00 
	00 00 00 00 49 4e 49 52 
	00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00
	00 00 00 00 00 00 00 00
	AT+CIPCLOSE
*/

#include "stdafx.h"
#include <iostream>   
using namespace std;

void parserNTPMessage();

struct ntp_packet
{
	unsigned char leap_ver_mode; //chr(250)  

	unsigned char startum; //0x4  

	char poll; //0x3  

	char precision; //系统时钟的精度。 0x1c  
	
	unsigned int root_delay; //本地到主参考时钟源的往返时间。 //4096  

	unsigned int root_dispersion; //系统时钟相对于主参考时钟的最大误差。 //9200  

	unsigned int reference_identifier; //参考时钟源的标识。 //随便一串整数代表服务器标识  

	unsigned long int reference_timestamp; //系统时钟最后一次被设定或更新的时间。   

	unsigned long int originage_timestamp; //NTP请求报文离开发送端时发送端的本地时间。  

	unsigned long int receive_timestamp; //NTP请求报文到达接收端时接收端的本地时间。  

	unsigned long int transmit_timestamp; //应答报文离开应答者时应答者的本地时间。  

};

unsigned char ntpSourcePack[48] = {
	0x1C, 0x04, 0x06, 0xE9, 0x00, 0x00, 0x1C, 0xA3,
	0x00, 0x00, 0x27, 0x27, 0x0A, 0x40, 0x20, 0x30,
	0xDE, 0x61, 0x91, 0x39, 0x31, 0xDB, 0xC3, 0xE0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xDE, 0x61, 0x92, 0x96, 0x11, 0xDB, 0xA2, 0x52,
	0xDE, 0x61, 0x92, 0x96, 0x11, 0xDB, 0xD6, 0x55 };

int main()
{
	char stop;

	parserNTPMessage();
	
	cin >> stop;
    return 0;
}

void parserNTPMessage(void) 
{
	char li = (char)((ntpSourcePack[0] >> 6) & 0x3);
	char ver = (char)((ntpSourcePack[0] >> 3) & 0x7);
	char mode = (char)(ntpSourcePack[0] & 0x7);
	//cout<<"  LI=" << li << "; version=" << ver << "; mode=" << mode;
	if (li == (char)11) {
		//11表示当前不可对时（服务器处于闰秒状态）
		return;
	}

	// combine the four chars (two words) into a long integer
	// this is NTP time (seconds since Jan 1 1900):
	unsigned long secsSince1900 = 0;
	secsSince1900  = (unsigned long)ntpSourcePack[40] << 24;
	secsSince1900 |= (unsigned long)ntpSourcePack[41] << 16;
	secsSince1900 |= (unsigned long)ntpSourcePack[42] << 8;
	secsSince1900 |= (unsigned long)ntpSourcePack[43] << 0;

	unsigned long secs = secsSince1900 + 8 * 3600L; //东八区，加8小时

	cout << secs << endl;

	unsigned long y = 1900, mon, d, h, m, s, wk;

	wk = (secs / 86400L) % 7 + 1; //86400 is secons in one day; +1 for 1900/1/1 is Monday

	do {
		unsigned long ys;
		if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
			ys = 31622400L; //31622400 = 366 * 24 * 3600;
		}
		else {
			ys = 31536000L;  // 31536000 = 365 * 24 * 3600;
		}
		if (secs < ys) {
			break;
		}
		else {
			secs -= ys;
			y++;
		}
	} while (1);

	int mons[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
		mons[1] = 29;
	}
	for (mon = 0; mon < 12; mon++) {
		if (secs < mons[mon] * 86400UL) {
			break;
		}
		else {
			secs -= mons[mon] * 86400UL;
		}
	}
	mon++;	//mon应从1算起所以补1

	d = secs / 86400L + 1; //86400 = 24 * 3600 = how many seconds in a day
	secs = secs % 86400L;

	h = secs / 3600;
	secs = secs % 3600;
	m = secs / 60;
	s = secs % 60;

	cout << y <<"-"<< mon << "-" << d << " " << h << ":" << m << ":" << s << " " << wk;
	//NTP服务器返回的时间已经解析完毕
	//TODO:如果需要更精确的时间，需要处理报文中的服务器收到请求和处理完毕的时间戳；
	//记录arduino发送NTP request和收到response的时间戳，
	//计算网络消耗掉的时长并加到这里获得的时间上


	//char buf[50];
	//snprintf(buf, sizeof(buf), "%04d/%02d/%02d %02d:%02d:%02d %0d", y, mon + 1, d, h, m, s, wk);
	//Serial.print("DATE: ");
	//Serial.println(buf);
}

