/****************************************************************************************************
 * Description:UDP 广播和组播的实例
 * file: 
 * auht:merlin data:
 *****************************************************************************************************/
#if 0
#include "common.h"
#include "socket_use.h"
#include <sys/socket.h>
#endif

//#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include <errno.h>

#define MCAST_PORT 8888
#define MCAST_ADDR "224.0.0.88"  // 多播地址
#define MCAST_DATA "BROADCAST TEST DATA"  // 多播内容
#define MCAST_INTERVAL 5  //多播时间间隔

#define MCAST_PORT 8888
#define MCAST_ADDR "224.0.0.88" /*一个局部连接多播地址，路由器不进行转发*/
#define MCAST_INTERVAL 5  //发送时间间隔
#define BUFF_SIZE 256   //接收缓冲区大小


/*************************************************************************************************
 * Description:UDP 服务器端（广播）
 *************************************************************************************************/
int broadcast_udp_server()
{
	setvbuf(stdout,NULL,_IONBF,0);
	fflush(stdout);
	int sock=-1;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	const int opt=-1;
	int nb=0;
	nb=setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(char*)&opt,sizeof(opt));//设置套接字类型
	if(nb==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	struct sockaddr_in addrto;
	bzero(&addrto,sizeof(struct sockaddr_in));
	addrto.sin_family=AF_INET;
	inet_pton(AF_INET, "255.255.255.255", &(addrto.sin_addr));
	//addrto.sin_addr.s_addr=htonl(INADDR_BROADCAST);//套接字地址为广播地址
	addrto.sin_port=htons(6000);//套接字广播端口号为6000
	int nlen=sizeof(addrto);
	getLocalAddr(sock);
	while(1)
	{
		sleep(1);
		char msg[]={"the message broadcast"};
		//getPeerAddr(sock);
		int ret=sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&addrto,nlen);//向广播地址发布消息
		if(ret<0)
		{
			printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
			return -1;
		}
		else 
		{
			printf("[%s]:send=%s line:%d\n", __func__, msg, __LINE__);
		}
	}
	return 0;
}

/*************************************************************************************************
 * Description:UDP 客户端（广播）
 *************************************************************************************************/
int broadcast_udp_client()
{
	setvbuf(stdout,NULL,_IONBF,0);
	fflush(stdout);
	struct sockaddr_in addrto;
	bzero(&addrto,sizeof(struct sockaddr_in));
	addrto.sin_family=AF_INET;
	addrto.sin_addr.s_addr=htonl(INADDR_ANY);
	addrto.sin_port=htons(6000);
	socklen_t len=sizeof(addrto);
	int sock=-1;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	const int opt=-1;
	int nb=0;
	nb=setsockopt(sock,SOL_SOCKET,SO_BROADCAST,(char*)&opt,sizeof(opt));
	if(nb==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	if(bind(sock,(struct sockaddr*)&(addrto),len)==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	char msg[100]={0};
	getLocalAddr(sock);
	while(1)
	{
		int ret=recvfrom(sock,msg,100,0,(struct sockaddr*)&addrto,&len);
		if(ret<=0)
		{
			printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		}
		else
		{
			//getPeerAddr(sock);
			printf("[%s]:recv=%s line=%d\n", __func__, msg, __LINE__);
		}
		sleep(1);
	}
	return 0;
}

/*************************************************************************************************
 * Description:UDP 服务器端（组播）
 *************************************************************************************************/
int multicast_udp_server()
{
	int sock;
	struct sockaddr_in mcast_addr;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	memset(&mcast_addr,0,sizeof(mcast_addr));
	mcast_addr.sin_family=AF_INET;
	mcast_addr.sin_addr.s_addr=inet_addr(MCAST_ADDR);
	mcast_addr.sin_port=htons(MCAST_PORT);
	while(1)
	{       //向局部多播地址发送多播内容
		int n=sendto(sock,MCAST_DATA,sizeof(MCAST_DATA),0,(struct sockaddr*)&mcast_addr,sizeof(mcast_addr));
		if(n<0)
		{
			printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
			return -2;
		}
		else
		{
			printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		}
		sleep(MCAST_INTERVAL);

	}
	return 0;
}

/*************************************************************************************************
 * Description:UDP 客户端（组播）
 *************************************************************************************************/
int multicast_udp_client()
{
	int sock;
	struct sockaddr_in local_addr;
	int err=-1;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock==-1)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	/*初始化地址*/
	local_addr.sin_family=AF_INET;
	local_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	local_addr.sin_port=htons(MCAST_PORT);
	/*绑定socket*/
	err=bind(sock,(struct sockaddr*)&local_addr,sizeof(local_addr));
	if(err<0)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -2;
	}
	/*设置回环许可*/
	int loop=1;
	err=setsockopt(sock,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop));
	if(err<0)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -3;
	}
	struct ip_mreq mreq;/*加入广播组*/
	mreq.imr_multiaddr.s_addr=inet_addr(MCAST_ADDR);//广播地址
	mreq.imr_interface.s_addr=htonl(INADDR_ANY); //网络接口为默认
	/*将本机加入广播组*/
	err=setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	if(err<0)
	{
		printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -4;
	}
	int times=0;
	socklen_t addr_len=0;
	char buff[BUFF_SIZE];
	int n=0;
	/*循环接受广播组的消息，5次后退出*/
	for(times=0;;times++)
	{
		addr_len=sizeof(local_addr);
		memset(buff,0,BUFF_SIZE);
		n=recvfrom(sock,buff,BUFF_SIZE,0,(struct sockaddr*)&local_addr,&addr_len);
		if(n==-1)
		{
			printf("[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
			return -5;
		}
		/*打印信息*/
		printf("RECV %dst message from server : %s\n",times,buff);
		sleep(MCAST_INTERVAL);
	}
	/*退出广播组*/
	err=setsockopt(sock,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq));
	close(sock);
	return 0;
}

