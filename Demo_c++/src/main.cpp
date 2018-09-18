#include "print.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/time.h>

#include <chrono>
#include <memory>

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

#if 1
#define MBUFFER_SIZE 1024
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

#if 1
#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void useUnorderedMap(){
	int count = 0;
    unordered_map<string,int> months;
    //插入数据
    cout<<"insert data"<<endl;
    months["january"]=31;
    months["february"] = 28;
    months["march"] = 31;
    months["september"] = 30;

    //直接使用key值访问键值对，如果没有访问到，返回0
    cout<<"[merlin]:"<<"mapSize="<<(months.size())<<endl;
    cout<<"[merlin]:"<<"september->"<<months["september"]<<endl;
    cout<<"[merlin]:"<<"xx->"<<months["xx"]<<endl;
	cout<<"[merlin]:"<<"mapSize="<<(months.size())<<endl;
	cout<<"----------------------------------------------------"<<endl;
	decltype(months) mapCopy;
	mapCopy = months;
	cout<<"[merlin]:"<<"mapSize="<<(mapCopy.size())<<endl;
	cout<<"[merlin]:"<<"september->"<<mapCopy["september"]<<endl;
	cout<<"[merlin]:"<<"xx->"<<mapCopy["xx"]<<endl;
	cout<<"[merlin]:"<<"mapSize="<<(mapCopy.size())<<endl;

	count = 0;
	for (auto &pr : mapCopy) {
		//auto reader = pr.second.lock();
		int reader = pr.second;
		count++;
		cout<<"[merlin]:count="<<count<<" val="<<reader<<endl;
	}
	cout<<"[merlin]:@size="<<(mapCopy.size())<<endl;



	typedef unordered_map<int,int> mymap;
	mymap mapping;
	mymap::iterator it;
	mapping[2]=110;
    mapping[5]=220;
    const int x=2;const int y=3;//const是一个C语言（ANSI C）的关键字，它限定一个变量不允许被改变,产生静态作用，提高安全性。

    //寻找是否存在键值对
    //方法一：
    cout<<"find data where key=2"<<endl;
    if( mapping.find(x)!=mapping.end() ){//找到key值为2的键值对
        cout<<"get data where key=2! and data="<<mapping[x]<<endl;
    }
    cout<<"find data where key=3"<<endl;
    if( mapping.find(y)!=mapping.end() ){//找到key值为3的键值对
        cout<<"get data where key=3!"<<endl;
    }
    //方法二：
    it=mapping.find(x);
    printf("find data where key=2 ?  %d\n",(it==mapping.end()));
    it=mapping.find(y);
    printf("find data where key=3 ?  %d\n",(it==mapping.end()));

    //遍历hash table
    for( mymap::iterator iter=mapping.begin();iter!=mapping.end();iter++ ){
        cout<<"key="<<iter->first<<" and value="<<iter->second<<endl;
    }

    system("pause");
}

#endif

#if 1 /*智能指针和weak_ptr的使用*/
int test_share_ptr()
{
	//Test 
	shared_ptr<Test> sptest(new Test("Obj1"));
	weak_ptr<Test> wptest(sptest);
	weak_ptr<Test> wptest2(sptest);
	shared_ptr<Test> sptemp = wptest.lock();
	shared_ptr<Test> sptemp2 = wptest2.lock();
	sptemp->print();
	sptemp->setSTR("1-str1");
	sptemp->print();
	std::cout<<"weak2-------------"<<std::endl;
	sptemp2->print();
	std::cout<<"object2-------------"<<std::endl;
	Test test2 = *sptest;
	test2.print();
	//std::cout<<"[merlin]:val="<<(sptemp->print())<<std::endl;
	
	return 0;
}
#endif

/*********************************************************************
 * Description:获取客户端的IP
 * Input fd:套接字文件描述符
 ********************************************************************/
int getPeerAddr(int fd)
{
	int port = 0;
	char ipAddr[64] = {0};
	struct sockaddr addr;
	struct sockaddr_in* addr_v4;
	socklen_t addr_len = sizeof(addr);
	if (0 > getpeername(fd, &addr, &addr_len)){
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
	}
	if (addr.sa_family == AF_INET) {
		addr_v4 = (sockaddr_in*) &addr;
		strcpy(ipAddr, (inet_ntoa(addr_v4->sin_addr))); /*IP*/
		port = ntohs(addr_v4->sin_port); /*port*/
	}
	printf("[%s]:addr=%s-%d line:%d\n", __func__, ipAddr, port, __LINE__);

	return 0;
}

/*********************************************************************
 * Description:获取本端口的地址
 * Input fd:套接字文件描述符
 *********************************************************************/
int getLocalAddr(int fd)
{
	int port = 0;
	char ipAddr[64] = {0};
	struct sockaddr addr;
	struct sockaddr_in* addr_v4;
	socklen_t addr_len = sizeof(addr);
	if (0 > getsockname(fd, &addr, &addr_len)){
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	if (addr.sa_family == AF_INET) {
		addr_v4 = (sockaddr_in*) &addr;
		strcpy(ipAddr, (inet_ntoa(addr_v4->sin_addr))); /*IP*/
		port = ntohs(addr_v4->sin_port); /*port*/
	}
	printf("[%s]:addr=%s-%d line:%d\n", __func__, ipAddr, port, __LINE__);

	return 0;
}

#if 1 /*虚函数的使用*/
class  animal
{
	public:
		animal(){
			name = "animal";
			std::cout<<"["<<__func__<<"]:"<<__LINE__<<std::endl;
		}
		~ animal(){
			std::cout<<"["<<__func__<<"]:"<<__LINE__<<std::endl;
		}
		
		virtual int printName(){
			std::cout<<__LINE__<<"["<<__func__<<"]:name="<<name<<std::endl;
			return 0;
		}
		int sowName(){
			printName();
			return 0;
		}
		
	private:
	string name;
};

class dog:public animal
{
	public:
		dog(){
			name = "dog";
			std::cout<<"["<<__func__<<"]:"<<std::endl;
		}
		~ dog(){
			std::cout<<"["<<__func__<<"]:"<<std::endl;
		}
		
		virtual int printName(){
			std::cout<<__LINE__<<"["<<__func__<<"]:name="<<name<<std::endl;
			return 0;
		}
		
	private:
	string name;	
};

class cat:public animal
{
	public:
		cat(){
			name = "cat";
			std::cout<<"["<<__func__<<"]:"<<std::endl;
		}
		~ cat(){
			std::cout<<"["<<__func__<<"]:"<<std::endl;
		}
		
		virtual int printName(){
			std::cout<<__LINE__<<"["<<__func__<<"]:name="<<name<<std::endl;
			return 0;
		}
		
	private:
	string name;

};

#endif

#if 1
/***********************************
* Brief：将数据组装到固定长度
* in param inData：长度必须小于等于1024个字节
* out param dest:长度一定不能小于2048个字节
* return 0<出错， 0>组装好的字符串的长度;
***********************************/
int myStrcatHex(const unsigned     char *inData, int inDataLen, unsigned char *dest, int len){		
	static int outDataLen = 0, ret = 0, nextDataLen = 0;
	static unsigned char outdata[32768] = {0};
	static unsigned char nextData[32768] = {0};
	unsigned char *p = NULL, *q = NULL;	
	
	if((NULL==inData) || (len<inDataLen)){
		printf("[%s][Error]:inData is null or size wrong len=%d inDataLen=%d line:%d\n", __func__, len, inDataLen, __LINE__);
		return -1;
	}

	if(0 == outDataLen){
		memset(outdata, 0, outDataLen);
	}

	/*拼装装上一次残留的数据*/
	if(0 < nextDataLen){
		memcpy(outdata, nextData, nextDataLen);
		outDataLen += nextDataLen;
		nextDataLen = 0;
	}
	
	p = outdata;
	q = p+outDataLen;
	memcpy(q, inData, inDataLen);
	outDataLen += inDataLen;
	ret = outDataLen;
	//memcpy(dest, outdata, outDataLen);
	memcpy(dest, outdata, len);
	
	/*缓存区超过限长，不再向缓存区添加数据*/
	printf("[%s]:len=%d-%d nextDataLen=%d line:%d\n", __func__, len , outDataLen, nextDataLen, __LINE__);
	if(len <= outDataLen){
		nextDataLen = outDataLen - len;
		p = outdata;
		q = p + len;
		//printf("[%s]:q=%s line:%d\n", __func__, q, __LINE__);
		memset(nextData, 0, 32768);
		memcpy(nextData, q, nextDataLen);
		memset(outdata, 0, outDataLen);
		outDataLen = 0;
	}
	
	return ret;
}

#endif


#if 1 //TS数据包的解析
/*第一个TS包 = TS头 + TS自适应字段 + PES头 + PES可选头 + SEI + SPS + PPS + TS负载(IDR Frame) */
/*TS数据包的头(TS头)*/
typedef struct _tsHead{
	unsigned char sync; /*8b TS同步字节 固定是0X47*/
	unsigned char TPE; /*1b 传输数据包差错指示*/
	unsigned char PUS; /*1b 净荷单元起始指示*/
	unsigned char TSP; /*1b 传送优先权*/
	int PID; /*13b 包标识符*/
	unsigned char TPSC; /*2b 传送加扰控制*/
	unsigned char AFC; /*2b 调整字段控制*/
	unsigned char CT; /*4b 连续记数器 */
} TS_HEAD, *P_TS_HEAD;

/********************************************
* brief:解析TS数据包的包头（4byte）
* in param phead:包头
* out param pdest:解析好的数据
**********************************************/
int parseTSHead(unsigned char *phead, TS_HEAD *pdest){
	if(0x47 != phead[0]) return -1;
	unsigned char cData = '\0';

	memset(pdest, 0, sizeof(TS_HEAD));
	pdest->sync = phead[0];
	pdest->TPE = (phead[1] & 0x80) >> 7;
	pdest->PUS = (phead[1] & 0x40) >> 6;
	pdest->TSP = (phead[1] & 0x20) >> 5;
	/*PID 13b*/
	cData = phead[1] << 4;
	pdest->PID = cData;
	pdest->PID = (pdest->PID) << 4;
	pdest->PID = (pdest->PID) | phead[2];
	pdest->TPSC = (phead[3] & 0xC0) >> 6;
	pdest->AFC = (phead[3] & 0x30) >> 4;
	pdest->CT = ((phead[3] << 4) & 0xF0) >> 4;
	printf("[%s]:TS_head=%X %X %X %X %X %X %X %X\n", __func__, (pdest->sync), (pdest->TPE), (pdest->PUS), (pdest->TSP), (pdest->PID), (pdest->TPSC), (pdest->AFC), (pdest->CT));
	return 0;
}

/*TS 数据包中解析自适应字段（TS自适应字段）*/
typedef struct _AdaptationField{
	unsigned char AFL; /*7b*/
	unsigned char DI; /*1b*/
	unsigned char RI; /*1b*/
	unsigned char ESPI; /*1b*/
	unsigned char PCRF; /*1b*/
	unsigned char OPCRF; /*1b*/
	unsigned char SPF; /*1b*/
	unsigned char TPDF; /*1b*/
	unsigned char AFEF; /*1b*/
	long long int PCR; /*33b*/
	unsigned char Reserved; /*6b*/
	int PCRE; /*9b*/
}ADAPTATION_FIELD, *P_ADAPTATION_FIELD;

/*char 型和 long long int的转化*/
typedef union{
	long long int lli;
	unsigned char buf[8];
}U_LLI_DATA;

/*char 型和int型的转化*/
typedef union{
	int iData;
	unsigned char buf[4];
}U_I_DATA;

/************************************************
* Brief：解析自适应字段(8byte)
* In param psrc:需要解析的自适应字段数据（2byte）
* Out param pdest:解析好的数据
*************************************************/
int parseAdaptationField(unsigned char *psrc, ADAPTATION_FIELD *pdest){
	memset(pdest, 0, sizeof(ADAPTATION_FIELD));
	pdest->AFL = psrc[0];
	pdest->DI = (psrc[1] & 0x80) >> 7;
	pdest->RI = (psrc[1] & 0x40) >> 6;
	pdest->ESPI = (psrc[1] & 0x20) >> 5;
	pdest->PCRF = (psrc[1] & 0x10) >> 4;
	pdest->OPCRF = (psrc[1] & 0x8) >> 3;
	pdest->SPF = (psrc[1] & 0x4) >> 2;
	pdest->TPDF = (psrc[1] & 0x2) >> 1;
	pdest->AFEF = (psrc[1] & 0x1);
	/*PCR*/
	U_LLI_DATA udata;
	udata.lli = 0;
	udata.buf[6] = 0x00;
	udata.buf[7] = 0x00;
	udata.buf[5] = psrc[2];
	udata.buf[4] = psrc[3];
	udata.buf[3] = psrc[4];
	udata.buf[2] = psrc[5];
	udata.buf[1] = psrc[6];
	udata.buf[0] = psrc[7];
	for(int i=0; i<sizeof(udata.lli); i++){printf("%X ", (udata.buf[i]));} printf(" value=%lld\n", (udata.lli));
	udata.lli = udata.lli >> 15;
	pdest->PCR = udata.lli;
	return 0;
}

/*解析PES head的定义（PES头）*/
typedef struct _PES_head{
	int PSCP; /*3byte PES 固定的三个字节都是 00 00 01*/
	unsigned char SID; /*1byte 表示此包数据的类型，是音频or视屏*/
	int PPL; /*2byte 此PES包的长度*/
	long long int pts;
	long long int dts;
} PES_HEAD, *P_PES_HEAD;

/************************************************
* Brief：解析PES head(6byte)
* In param psrc:需要解析的PES head（6byte）
* Out param pdest:解析好的数据
*************************************************/
int parsePESHead(unsigned char *psrc, PES_HEAD * pdest){
	U_I_DATA uIdata;

	memset(pdest, 0, sizeof(PES_HEAD));
#if 0 /*PES的 开始三个字节都是 00 000 01*/
	uIdata.iData = 0;
	uIdata.buf[2] = psrc[0];
	uIdata.buf[1] = psrc[1];
	uIdata.buf[0] = psrc[2];
	pdest->PSCP = uIdata.iData;
#endif
	pdest->SID = psrc[3]; /*表示此包数据的类型，是音频or视屏*/
	uIdata.iData = 0;
	uIdata.buf[1] = psrc[4];
	uIdata.buf[0] = psrc[5];
	pdest->PPL = uIdata.iData;
	/*PTS*/
	if(psrc[7]&0x80){
		pdest->pts = ((long long int)(psrc[9]&0x0e ) << 29)|
			(long long int)(psrc[10] << 22)|
			((long long int)(psrc[11]&0xfe) << 14)|
			(long long int)(psrc[12] << 7)|
			(long long int)(psrc[12] >> 1);
	}

	/*PDS*/
	if( psrc[7]&0x40){
             pdest->dts = ((long long int)(psrc[14]&0x0e ) << 29)|
			 	(long long int)(psrc[15] << 22)|
			 	((long long int)(psrc[16]&0xfe) << 14)|
			 	(long long int)(psrc[17] << 7)|
			 	(long long int)(psrc[18] >> 1);
	}
	printf("%X %X %X pts=%lld dts=%lld\n", (pdest->PSCP), (pdest->SID), (pdest->PPL), (pdest->pts), (pdest->dts));
	return 0;
}
#endif

int printBufData(unsigned char *pdata){
	int intData = 0;

	intData = pdata[1] + 1;
	printf("[%s]:intData=%d(%X) line:%d\n", __func__, intData, intData, __LINE__);
	
	return 0;
}

#if 1
#include <sys/types.h>
#include <dirent.h>
long int pidByName(char* pidName){
    DIR *dir;
	FILE *status;
    struct dirent *next;
	long int ret = 0;
	char filename[512] = {0}, buffer[512] = {0},  name[512] = {0};

	/*proc中包括当前的进程信息,读取该目录*/
    dir = opendir("/proc");
	if(NULL == dir){
		printf("[%s][%d][Error]:info=%s\n", __func__, __LINE__, strerror(errno));
		return -1;
	}
	while ((next = readdir(dir)) != NULL){
		if (strcmp(next->d_name, "..") == 0){
			continue;
		}
		if (!isdigit(*next->d_name)){
			continue; /* If it isn't a number, we don't want it */
		}
		sprintf(filename, "/proc/%s/status", next->d_name);
		if (!(status = fopen(filename, "r"))){
            continue;
        }
        if (fgets(buffer, sizeof(buffer), status) == NULL) {
            fclose(status);
            continue;
        }
        fclose(status);
        sscanf(buffer, "%*s %s", name);  /* Buffer should contain a string like "Name:   binary_name" */
        if (strcmp(name, pidName) == 0) {
            ret = strtol(next->d_name, NULL, 0);
			printf("[%s][%d]:pidData=%ld\n", __func__, __LINE__, ret);
			return  ret; /*返回目标进程号*/
        }
    }
    return 0;
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

#if 0 /*C++时间的使用*/
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

	//useUnorderedMap(); /*unordered_map对象的使用*/
	//test_share_ptr(); /*智能指针的使用*/
#if 0	
	dog mydog;
	cat mycat;
	mydog.sowName();
	usleep(200*1000);
	mycat.sowName();
#endif

#if 0 //将字符串根据长度打成多串
	int tmpLen = 5, i = 0;
	char temp[6] = {0}, *p = NULL, *q = NULL;
	char cmdline[1024] = {"1234567888888888888888888888888888889"};
	p = cmdline;
	for(i=0; i<=(strlen(cmdline)/tmpLen); i++){
		memset(temp, 0, sizeof(temp));
		q = p + (i*tmpLen);
		memcpy(temp, q, tmpLen);
		printf("%s\n", temp);
	}
#endif

#if 0 /*将数拼装成固定的长度*/
	int i = 0, ret = 0, outLen = 11;
	unsigned char inData[32] = {"hello"}, outData[1024] = {0};
	for(i = 0; i<10; i++){
		ret = myStrcatHex(inData, strlen((char*)inData), outData, outLen);
		//ret = myStrcatHex(inData, 5, outData, 11);
		if(outLen < ret){
			printf("[%s]:outdata=%s line:%d\n", __func__, outData, __LINE__);
		}
		
	}
	//printf("[%s][merlin]:outdata=%s line:%d\n", __func__, outData, __LINE__);
#endif

#if 0 /*解析TS包头5byte的长度*/
	TS_HEAD ts_head;
	//unsigned char buffer[32] = {0x47, 0x41, 0x01, 0x30};
	//unsigned char buffer[32] = {0x47, 0x01, 0x01, 0x3C};
	//parseTSHead(buffer, &ts_head);
	//unsigned char buffer[32] = {0x07, 0x10, 0x00, 0x07, 0x24, 0x00, 0x7E, 0x00};
	ADAPTATION_FIELD adapta_field;
	//parseAdaptationField(buffer, &adapta_field);
	PES_HEAD pes_head;
	unsigned char buffer[32] = {0x00, 0x00, 0x01, 0xE0, 0x00, 0x00};
	parsePESHead(buffer, &pes_head);
	//long long int lli = 0;
	//printf("lliSize=%d\n", sizeof(lli));
#endif

#if 1
	char proName[32] = {"printInfo"};
	printf("[%s][%d]:pid=%d\n", __func__, __LINE__, getpid());
	pidByName(proName);
#endif

	return 0;
}

