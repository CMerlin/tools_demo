#include "print.h"

#include <sys/time.h>

#include <chrono>
#if 0
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <vector>
//using std::vector;
#endif

typedef unsigned char uint8_t;
typedef signed char int8_t;

#if 1 /*RTP数据包header的解析*/
static int parsingRTPPacket(unsigned char *data, int size) {  
	if (size < 12) {  
		return -1;  
	}  
	unsigned int version = (data[0] >> 6); /*版本*/   
	unsigned int numCSRCs = data[0] & 0x0f;  
	unsigned int payloadOffset = 12 + 4 * numCSRCs;    
	unsigned int rtpTime = data[4] << 24 | data[5] << 16 | data[6] << 8 | data[7]; /*时间戳*/
	unsigned int srcId = data[8] << 24 | data[9] << 16 | data[10] << 8 | data[11];  
	unsigned int seqNum = data[2] << 8 | data[3];  
	printf("[%s]:seqNum=%d version=%d numCSRCs=%d payloadOffset=%d rtpTime=%d srcId=%d line:%d\n", __func__, seqNum, version, numCSRCs, payloadOffset, rtpTime, srcId, __LINE__);

	return 0;  
}  
#endif

#if 1 /*定义一个模板函数*/
	template <typename RET_T , typename IN1_T , typename IN2_T >
RET_T templateFun(IN1_T in1 , IN2_T in2)
{
	RET_T ret;
	ret = in1 +in2;
	std::cout<<"["<<__func__<<"]:ret="<<ret<<" in1="<<in1<<" in2="<<in2<<" line:"<<__LINE__<<std::endl;
	//std::cout<<"["<<__func__<<"]:"<<" line:"<<__LINE__<<std::endl;
	return ret;
}
#endif

#if 1 /*定义模板类*/
template <class elemtype>//声明一个模板，虚拟类型为elemtype  
class Compare  
{  
	private:  
		elemtype x, y; 
	public:  
		Compare(elemtype a = 0, elemtype b = 0):x(a), y(b){
			std::cout<<"["<<__func__<<"]:construction......"<<std::endl;	
		}//创建构造函数，默认值为0  
		elemtype Max();  
		elemtype Min();
		~Compare(){};
};  

	template <class elemtype>//由于方法在类外定义，需要指定以下函数也使用的虚拟数据类型  
elemtype Compare<elemtype>::Max()//返回类型为elemtype类型，"Compare<elemtype>"是一个整体，表示带参数的类，  
{  
	return ((x > y)? x:y);  
}  

	template <class elemtype>//同上  
elemtype Compare<elemtype>::Min()//同上  
{  
	return ((x < y)? x:y);  
}  
#endif

#if 1 /*普通类的定义*/
class Test
{
	private:
		string str;
	public:
		Test(){
			str = "hello";
			std::cout<<"["<<__func__<<"]:construction......"<<std::endl;	
		}
		Test(string pStr){
			str = pStr;
			std::cout<<"["<<__func__<<"]:construction......"<<std::endl;	
		}
		~Test(){
			std::cout<<"["<<__func__<<"]:destructor......"<<std::endl;
		}
		void setSTR(string pstr){
			str = pstr;
		}
		void print(){
			std::cout<<"["<<__func__<<"]:str="<<str<<std::endl;	
		}
};
#endif

#if 0
int gettimeofday(struct timeval *tp, void *tzp) {
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif

/*获取当前系统时间，单位是毫秒*/
unsigned int getCurTimeMillisecond() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/*获取当前的系统时间，返回的是时间字符串*/
int getCurTime(char *systime)
{
	memset(systime, 0, strlen(systime));
	time_t now;
	now = time(NULL);
	struct tm *tm = localtime(&now);
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);

	//sprintf(systime, "%d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	sprintf(systime, "%d%02d%02d %02d:%02d:%02d.%ld", 
			tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
	
	return 0;
}

int main(int argc, const char *argv[])
{
#if 0
	/*输出的目标字符串前面会加上系统时间*/
	const int TIME = 1;
	printInfo print(USERD, TIME);
	print.print(USERD, "Hello!\n");
	//输出结果为：2015082415:08:35.789772 Hello!
#endif

#if 0 /*获取进程和线程号*/
	char buffer[65] = {0};
	sprintf(buffer, "%d.%lu", getpid(), pthread_self());
	std::cout<<"buffer="<<buffer<<std::endl;
	parsingRTPPacket((unsigned char*)buffer, 12);
#endif

#if 0 /*string字符串的处理*/
	string str("hello");
	std::cout<<"str="<<str<<std::endl;
	str.erase();
	std::cout<<"str="<<str<<std::endl;
#endif

#if 0
	#define RTSP_FIELD "rtsp."
	const char kPort[] = RTSP_FIELD"port";
	std::cout<<"kPort:"<<kPort<<std::endl;
#endif

#if 0 //decltyp的功能相当于C中的typedef 关键字
	int intData = 5;
	string str("hello");
	decltype(intData) dintData = 10;
	decltype(str) dStr("good");
	std::cout<<"dintData="<<dintData<<" dStr="<<dStr<<endl;
	dStr = str;
	std::cout<<"dintData="<<dintData<<" dStr="<<dStr<<endl;

	//Test TObj("this is test");
	//TObj.print();
	//Test TObj1;
	//TObj1.print();

	Test *pt = new Test[3];
	pt[0].setSTR("good");
	pt[0].print();
	pt[1].print();
	pt[2].print();
#endif

#if 0 /*模板函数的使用*/
	auto ret = templateFun<double, int ,int>(11,22);
	std::cout<<"ret="<<ret<<endl;
	auto str = templateFun<string, string , string>("hello", " world!");
	std::cout<<"ret="<<str<<endl;
	ret = templateFun<double, double, double>(12.2, 12.3);
	std::cout<<"ret="<<ret<<endl;
#endif

#if 0 /*模板类的使用*/
	int a = 3, b = 4;
	Compare<int> cmpObj(a,b);//使用类模板定义对象  
	cout << "min = " << cmpObj.Min() << endl << "max = " << cmpObj.Max() << endl;

	string str1 = "abc", str2 = "bcd";
	Compare<string> strObj(str1, str2);//使用类模板定义对象  
	cout << "min = " << strObj.Min() << endl << "max = " << strObj.Max() << endl;
#endif

#if 1 /*C++时间的使用*/
	//std::cout<<"["<<__func__<<"]:"<<" line:"<<__LINE__<<std::endl;
	//int ret = getCurTimeMillisecond();
	//std::cout<<"curTime="<<ret<<std::endl;
	//chrono::milliseconds(millisecond_sleep);
	char timeCur[64] = {0};
	getCurTime(timeCur);
	std::cout<<"["<<__func__<<"]:now="<<timeCur<<" line:"<<__LINE__<<std::endl;
	//chrono::milliseconds(1000000000);
	usleep(1000*1000);
	getCurTime(timeCur);
	std::cout<<"["<<__func__<<"]:now="<<timeCur<<" line:"<<__LINE__<<std::endl;
#endif

	return 0;
}
