#include "print.h"
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
		Compare(elemtype a = 0, elemtype b = 0):x(a), y(b){}//创建构造函数，默认值为0  
		elemtype Max();  
		elemtype Min();
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
#endif

#if 0 /*模板函数的使用*/
	auto ret = templateFun<double, int ,int>(11,22);
	std::cout<<"ret="<<ret<<endl;
	auto str = templateFun<string, string , string>("hello", " world!");
	std::cout<<"ret="<<str<<endl;
	ret = templateFun<double, double, double>(12.2, 12.3);
	std::cout<<"ret="<<ret<<endl;
#endif

#if 1 /*模板类的使用*/
	int a = 3, b = 4;
	Compare<int> cmpObj(a,b);//使用类模板定义对象  
	cout << "min = " << cmpObj.Min() << endl << "max = " << cmpObj.Max() << endl;

	string str1 = "abc", str2 = "bcd";
	Compare<string> strObj(str1, str2);//使用类模板定义对象  
	cout << "min = " << strObj.Min() << endl << "max = " << strObj.Max() << endl;
#if 0
int main(int argc, char const *argv[])  
{  
	elmtpe a,b;  
	cout << "input 2 numbers:" << endl;  
	cin >> a >> b;  
	Compare<elmtpe> cmp(a,b);//使用类模板定义对象  
	cout << "min = " << cmp.Min() << endl << "max = " << cmp.Max() << endl;  
	return 0;  
} 
#endif

#endif

	return 0;
}
