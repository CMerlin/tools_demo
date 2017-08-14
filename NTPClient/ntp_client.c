#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <poll.h>

#define uchar unsigned char
#define uint unsigned int

#define LEN 30 //读取配置文件缓冲区大小
#define From00to70 0x83aa7e80U
#define NTPPORT 123//ntp端口

/*NTP配置信息*/
typedef struct _ntp_server{
	char domain[32]; /*域名*/
	char ip[32]; /*IP*/
	int port; /*端口*/
	char note[32]; /*简述信息*/
} NTP_SERVER, *P_NTP_SERVER;

typedef struct NTPPACK
{
	char li_vn_mode;
	char stratum;
	char pool;
	char precision;
	unsigned long root_delay;
	unsigned long root_dispersion;
	char ref_id[4];

	unsigned long reftimestamphigh;
	unsigned long reftimestamplow;

	unsigned long oritimestamphigh;
	unsigned long oritimestamplow;

	unsigned long recvtimestamphigh;
	unsigned long recvtimestamplow;

	unsigned long trantimestamphigh;
	unsigned long trantimestamplow;
}NTPPacket;

NTPPacket ntppack, newpack;

long long firsttimestamp, finaltimestamp;
long long diftime, delaytime;

/*******************************************************
 * Description：检测目标文件是否可读可写
 * Input file：需要检测的文件
 * Input time: 超时时间(单位是毫秒)
 * Return：0-可读 1-可写 -1-超时或错误
 * *****************************************************/
int is_read_write(const     int *file, int time) 
{
	int ret = 0;
	struct pollfd fds[1];
	memset(fds, '\0', sizeof(struct pollfd) * 1);
	fds[0].fd = (*file);
	fds[0].events = (POLLIN | POLLOUT);
	ret = poll(fds, 1, time); //1000毫秒的超时时间
	if(ret <= 0) //超时或出错
		return -1;
	if(fds[0].revents & POLLIN) //可读
		return 0;
	else if(fds[0].revents & POLLOUT) //可写
		return 1;

	return -1;
}

void NTP_Init()
{
	bzero(&ntppack, sizeof(ntppack));
	ntppack.li_vn_mode = 0x1b;

	firsttimestamp = From00to70 + time(NULL); //获取初始时间戳 -8*3600
	ntppack.oritimestamphigh = htonl(firsttimestamp);
}

void NTP_server(char *server)
{
	memset(server, 0, strlen(server));
	sprintf(server, "%s", "24.56.178.140");
}

int main(void)
{
	fd_set inset1; //select
	struct timeval tv, tv1;//select

	int sockfd; //socked
	struct sockaddr_in addr; //socked

//	struct timezone tz;
	/*初始化NTP服务器端的信息*/
	NTP_SERVER ntpServer;
	memset(&ntpServer, 0, sizeof(ntpServer));
	sprintf((ntpServer.domain), "%s", "us.ntp.org.cn");
	sprintf((ntpServer.ip), "%s", "24.56.178.140");
	ntpServer.port = 123;
	sprintf((ntpServer.note), "%s", "American");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(ntpServer.port); //NTP专用123端口
	addr.sin_addr.s_addr = inet_addr(ntpServer.ip); //从配置文件中读取校时服务器端口
	bzero(&(addr.sin_zero), 8); //select 监听端口清零

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("[%s][Error]:socket=%s line:%d\n", __func__, strerror(errno), __LINE__);
		exit(1);
	}
	tv.tv_sec = 10; //select 10s等待
	tv.tv_usec = 0;
	FD_ZERO(&inset1);
	FD_SET(sockfd, &inset1);

	
	NTP_Init(); //ntp初始化

	sendto(sockfd, &ntppack, sizeof(ntppack), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr)); //发送数据请求包

	if(select(sockfd + 1, &inset1, NULL, NULL, &tv) < 0)
	{
		perror("select error!\n");
		exit(1);
	}
	else
	{
		printf("select is OK\n");
		if(FD_ISSET(sockfd, &inset1))
		{
			//if(recv(sockfd, &newpack, sizeof(newpack), 0) < 0)
			int ret = 0;
			ret = recv(sockfd, &newpack, sizeof(newpack), 0);
			printf("[%s]:ret=%d line:%d\n", __func__, ret, __LINE__);
			if(ret<0)
			{//接收数据到newpack中
				perror("recv newpack error!\n");
				exit(1);
			}
		}
	}

	//到达客户机时间
	finaltimestamp = time(NULL) + From00to70;

	//将网络上传送的大端数据改为小端形式
	newpack.root_delay = ntohl(newpack.root_delay);
	newpack.root_dispersion = ntohl(newpack.root_dispersion);

	newpack.reftimestamphigh = ntohl(newpack.reftimestamphigh);
	newpack.reftimestamplow = ntohl(newpack.reftimestamplow);

	newpack.oritimestamphigh = ntohl(newpack.oritimestamphigh);
	newpack.oritimestamplow = ntohl(newpack.oritimestamplow);

	newpack.recvtimestamphigh = ntohl(newpack.recvtimestamphigh);
	newpack.recvtimestamplow = ntohl(newpack.recvtimestamplow);

	newpack.trantimestamphigh = ntohl(newpack.trantimestamphigh);
	newpack.trantimestamplow = ntohl(newpack.trantimestamplow);

	//求出客户机与服务器的时间差
	diftime = ((newpack.recvtimestamphigh - firsttimestamp) + (newpack.trantimestamphigh - finaltimestamp)) >> 1;
	//求出延时
	delaytime = ((newpack.recvtimestamphigh - firsttimestamp) - (newpack.trantimestamphigh - finaltimestamp)) >> 1;

	//求出真正的时间戳
	tv1.tv_sec = time(NULL) + diftime + delaytime;
	tv1.tv_usec = 0;
	settimeofday(&tv1, NULL);
	system("hwclock -w");
	system("date");
	//free(server_t);
	return 0;
}
