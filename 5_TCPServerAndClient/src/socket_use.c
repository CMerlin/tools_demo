/****************************************************************************************************
 * Description:套接字的相关操作
 * file: 
 * auht:merlin data:
 *****************************************************************************************************/
#include "common.h"
#include "socket_use.h"
#include <sys/socket.h>
 
static CONNECT_INFO TCPClientConnectInfo; /*TCP客户端连接状态信息*/
sint32 initTCPClientConnectInfo()
{
	pthread_mutex_init(&(TCPClientConnectInfo.lock), NULL); /*初始化互斥锁*/
	memset(&(TCPClientConnectInfo.attr), 0, sizeof(TCPClientConnectInfo.attr));; /*初始化数据区*/
	return 0;
}

/*******************************************************
 * Description：更新TCP客户端的网络信息
 * Input attr：需要更新的信息
 * Return：0-成功； -1-失败
 * *****************************************************/
sint32 setNetAttrTCPC(NETWORK_ATTR_S *attr)
{
	pthread_mutex_lock(&(TCPClientConnectInfo.lock));
	TCPClientConnectInfo.attr = (*attr);
	pthread_mutex_unlock(&(TCPClientConnectInfo.lock));

	return 0;
}

/*******************************************************
 * Description：获取TCP客户端的网络信息
 * Output attr：连接信息
 * Return：0-成功； -1-失败
 * *****************************************************/
sint32 getNetAttrTCPC(NETWORK_ATTR_S *attr)
{
	pthread_mutex_lock(&(TCPClientConnectInfo.lock));
	memset(attr, 0, sizeof(NETWORK_ATTR_S));
	(*attr) = TCPClientConnectInfo.attr;
	pthread_mutex_unlock(&(TCPClientConnectInfo.lock));

	return 0;
}

/************************************************************
* Description:设置TCP客户端和服务器端的连接状态
************************************************************/
sint32 setConnetStatusTCPC(int status)
{
	pthread_mutex_lock(&(TCPClientConnectInfo.lock));
	TCPClientConnectInfo.attr.connect = status;
	pthread_mutex_unlock(&(TCPClientConnectInfo.lock));
	return 0;
}

/*****************************************************************************
* Description:得到主机的地址信息
* Output ipAddr:获取到的IP地址
* Return:0-成功 -1-失败
*******************************************************************************/
int getHostAddr(char *ipAddr)
{
	char *ptr = NULL, **pptr;
	char str[128] = {0},  hname[128] = {0};
	struct hostent *hptr = NULL;

	/* 获取主机名 */
	if(0 > gethostname(hname, sizeof(hname))){
		trace(ERROR, "[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	/* 获取主机的网络配置信息 */
	if((hptr=gethostbyname(hname))==NULL){
		trace(ERROR, "[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	trace(DEBUG, "[%s]:real hostname:%s\n", __func__, hptr->h_name, __LINE__);//正式主机名
	/* 遍历所有的主机别名 */
	for(pptr=hptr->h_aliases; *pptr!=NULL; pptr++){
		trace(DEBUG, "[%s]:alias name:%s  line:\n", __func__,  (*pptr),__LINE__);
	}
	/* 判断socket类型 */
	switch(hptr->h_addrtype)
	{
	case AF_INET:  //IP类为AF_INET
		pptr=hptr->h_addr_list; //IP地址数组
		for(;*pptr!=NULL;pptr++){
			inet_ntop(hptr->h_addrtype, (*pptr), ipAddr, 64);
			trace(DEBUG, "[%s]:ipaddr=%s line:%d\n", __func__, ipAddr, __LINE__); //inet_ntop转换为点分十进制	
		}	
		break;
	default:
		trace(DEBUG, "[%s]:unknown address type line:%d\n", __func__, __LINE__);
		break;
	}
	return 0;
}

/*********************************************************************
 * Description:根据文件描述符，获取客户端的IP
 * Input fd:套接字文件描述符
 ********************************************************************/
int getPeerAddr(int fd)
{
	int port = 0;
	char ipAddr[64] = {0};
	struct sockaddr addr;
	struct sockaddr_in* addr_v4;
	socklen_t addr_len = sizeof(addr);
	if(0 > getpeername(fd, &addr, &addr_len)){
		trace(ERROR, "[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
	}
	if(addr.sa_family == AF_INET){
		addr_v4 = (struct sockaddr_in*) &addr;
		strcpy(ipAddr, (inet_ntoa(addr_v4->sin_addr))); /*IP*/
		port = ntohs(addr_v4->sin_port); /*port*/
	}
	trace(DEBUG, "[%s]:addr=%s-%d line:%d\n", __func__, ipAddr, port, __LINE__);

	return 0;
}

/*********************************************************************
 * Description:根据文件描述符，获取本端口的地址(IP和端口)
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
		trace(ERROR, "[%s][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	if(addr.sa_family == AF_INET){
		addr_v4 = (struct sockaddr_in*)&addr;
		strcpy(ipAddr, (inet_ntoa(addr_v4->sin_addr))); /*IP*/
		port = ntohs(addr_v4->sin_port); /*port*/
	}
	trace(DEBUG, "[%s]:addr=%s-%d line:%d\n", __func__, ipAddr, port, __LINE__);

	return 0;
}

/******************************************************************************
 * Description：创建套接字 
 * Input family：协议族 
 * Input type：协议类型 
 * Input protocol：
 * Return：创建好的文件描述符
 * *****************************************************************************/
int createSocket(const int family, const int type, const int protocol)
{ 
	int fd = socket(family, type, protocol);	
	if(fd < 0)	{	
		close(fd);
		trace(ERROR, "[%s]:socket=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
	}
	return fd;
}

/***************************************************************************************
 * Description:bind套接字
 * Input:fd-套接字文件描述符 family-协议类型 addr-字符串类型的IP地址 port-端口号 
 * *************************************************************************************/
int bindSocket(const int fd, const int family, char * addr, const int port)
{
	int result = 0;
	struct sockaddr_in bindAddr;
	
	bzero(&bindAddr,sizeof(struct sockaddr_in));
	//addr.sin_family=AF_INET;
	bindAddr.sin_family=family;
	//addr.sin_addr.s_addr=htonl(INADDR_ANY);
	//char serverIP[64] = {"192.168.5.192"};
	//memcpy((addr.sin_addr.s_addr), serverIP, strlen(serverIP) );
	inet_pton(AF_INET, addr, &(bindAddr.sin_addr));
	bindAddr.sin_port=htons(port);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &result, sizeof(result)); //解除bind
	if(bind(fd,(struct sockaddr *)&bindAddr,sizeof(struct sockaddr_in))<0)
	{
		trace(ERROR, "[%s]:bind=%s line:%d\n", __func__, strerror(errno), __LINE__); 
		return -1;
	}
	return 0;
}

/******************************************************************************
 * Description：监听套接字 
 * Input fd：
 * Input max：listen最多可监听的文件数
 * Return：监听的文件
 * *****************************************************************************/
int listenSocket(const int fd, const int max)
{	
	if(listen(fd, max) < 0) 
	{	
		trace(ERROR, "[%s]:listen=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	return fd;
}

/********************************************************************************
* Description:接收客户端的连接请求
*
*********************************************************************************/
int acceptSocket(const int fd, struct sockaddr_in *clientAddr)
{
	int ret = 0;
	int len = sizeof(struct sockaddr_in);
	memset(clientAddr, 0, sizeof(struct sockaddr_in));
	ret = accept(fd, (struct sockaddr *)clientAddr, (socklen_t*)&len);
	if(0 > ret){
		trace(ERROR, "[%s]:accept=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	trace(DEBUG, "[%s]:client IP=%s port=%d socket=%d line=%d\n", __func__, inet_ntoa(clientAddr->sin_addr), (int)ntohs(clientAddr->sin_port), ret, __LINE__);

	return ret;
}

/****************************************************************************** 
 * Description：申请和服务器端建立连接
 * Input：
 * Output：
 * Return： 
 * *****************************************************************************/
int connectSocket(int *fd, const int family, char *ip, const int port) //TCP UDP
{	
	struct sockaddr_in addr;
	addr.sin_family = family;
	//un.sin_addr.sin_addr.s_addr = addr;
	//inet_pton(AF_INET, ip, addr.sin_addr.sin_addr.s_addr);
	inet_pton(AF_INET, ip, &(addr.sin_addr));
	addr.sin_port = htons(port);
	//if(connect(*fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
	if(0 > connect(*fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)))
	{		
		close(*fd); 
		//printf("[%s]:connect=%s LINE:%d\n", __func__, strerror(errno),__LINE__);		
		trace(ERROR, "[%s]:connect=%s LINE:%d\n", __func__, strerror(errno),__LINE__);		
		return -1;	
	}	
	return 0;
}
/****************************************************************************************************/

/******************************************************************************
 * Description：和服务器建立连接，连接方式是阻塞的
 * Input ip and port：服务器端的ip和端口
 * Output fd and complete：套接字文件描述符和一些连接相关的信息
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 retry_connect_server_block(NETWORK_ATTR_S *server)
{
	sint32 ret = 0;
	NETWORK_ATTR_S history;
	
	getNetAttrTCPC(&history);
	//trace(DEBUG, "[%s]:history connect info fd=%d ip=%s port=%d connect=%d type=%d LINE:%d\n", __func__, history.fd, history.ip, history.port, history.connect, history.type, __LINE__);
	/*检测服务器端口的IP是否发生了改变*/
	if(0 != strncmp(history.ip, server->ip, strlen(history.ip))){
		history.connect = 0;
		close(history.fd);
	}
	/*如果是短连接，建立新的连接*/
	if(server->type != KEEP_ALIVE){
		history.connect = 0;
	}
	/*连接正常不再进行连接操作*/
	if(history.connect == 1){
		(*server) = history;
		return 0;
	}

	/*连接异常建立新的连接*/
	if(server->fd > 0){
		close(server->fd);
		server->fd = 0;
	}
	/*创建套接字*/
	server->btime = time(NULL);
	server->fd = createSocket(AF_INET, SOCK_STREAM, 0);
	if(server->fd < 0){
		trace(ERROR, "[%s]:createSocket excuate faild! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
#if 0 /*bind端口的操作, 客户端最好别bind端口*/
	int cliPort = 9009;
	bindSocket((server->fd), AF_INET, (server->ip), cliPort);
#endif
	/*请求建立连接*/
	ret = connectSocket(&(server->fd), AF_INET, server->ip, server->port);
	if(ret < 0){
		trace(ERROR, "[%s]:connectSocket excuate faild! ip=%s port=%d LINE:%d\n", __func__, server->ip, server->port, __LINE__);
		return -1;
	}
	trace(TRACE, "[%s]:succed try connect to server->ip=%s port=%d LINE:%d\n", __func__, server->ip, server->port, __LINE__);
	/*设置成功建立连接的标志*/
	server->connect = 1;
	memset(&history, 0, sizeof(history));
	history = (*server);
	setNetAttrTCPC(&history);

	return 0;
}

/****************************************************************************************
* Description:结束线程，对线程资源进行回收
*****************************************************************************************/
int myPthreadExit()
{
	pthread_detach(pthread_self());
	pthread_exit(NULL);
	return 0;
}

#if 1
/******************************************************************************************
* Description:接收数据，并显示收到的数据
******************************************************************************************/
void dealWithData(void *inParam)
{
	int timeOut = 0;
	char buffer[1024] = {0};
	int ret = 0, bufLen = 256;
	TCPDEMO_ATTR clientAttr;
	
	if(NULL == inParam){
		trace(ERROR, "[%s]:in param is wrong! line:%d\n", __func__, __LINE__);
		myPthreadExit();
		return;
	}
	memcpy(&clientAttr, inParam, sizeof(TCPDEMO_ATTR));
	getLocalAddr((clientAttr.fd));
	getPeerAddr((clientAttr.fd));
	
	/* 具体和客户端的交互处理 */
	timeOut = time(NULL);
	while(1){
		/*很久还没有收到客户端口的数据，就结束*/
		if(30 <= (time(NULL)-timeOut)){
			trace(DEBUG, "[%s]:timeout close client! line:%d\n", __func__, __LINE__);
			myPthreadExit();
			close(clientAttr.fd);
		}
		/*接收数据*/
		memset(buffer, 0, strlen(buffer));
		ret = read_data(&(clientAttr.fd), buffer, bufLen);
		if(0 >= ret){
			//trace(ERROR, "[%s]:ret=%d read failure! line:%d\n", __func__, ret, __LINE__);
			//usleep(1*1000*1000); /*休眠3秒在读*/
			continue;
		}
		timeOut = time(NULL);
		trace(DEBUG, "[%s]:recv[%d]:%s line:%d\n", __func__, ret, buffer, __LINE__);
	}
	
	return;
}
#endif

#if 0
/********************************************************************************************
* Description:接收数据,并将数据进行回射
********************************************************************************************/
void dealWithData(void *inParam)
{
	int timeOut = 0;
	char buffer[1024] = {0};
	int ret = 0, bufLen = 256;
	TCPDEMO_ATTR clientAttr;
	
	if(NULL == inParam){
		trace(ERROR, "[%s]:in param is wrong! line:%d\n", __func__, __LINE__);
		myPthreadExit();
		return;
	}

	memcpy(&clientAttr, inParam, sizeof(TCPDEMO_ATTR));
	timeOut = time(NULL);
	while(1){
		/*很久还没有收到客户端口的数据，就结束*/
		if(10 <= (time(NULL)-timeOut)){
			trace(DEBUG, "[%s]:timeout close client! line:%d\n", __func__, __LINE__);
			myPthreadExit();
			close(clientAttr.fd);
		}
		/*收发数据*/
		memset(buffer, 0, strlen(buffer));
		ret = read_data(&(clientAttr.fd), buffer, bufLen);
		if(0 >= ret){
			//trace(ERROR, "[%s]:ret=%d read failure! line:%d\n", __func__, ret, __LINE__);
			//usleep(1*1000*1000); /*休眠3秒在读*/
			continue;
		}
		timeOut = time(NULL);
		trace(DEBUG, "[%s]:recv[%d]:%s line:%d\n", __func__, ret, buffer, __LINE__);
		if(0 >= send_data(&(clientAttr.fd), buffer, strlen(buffer))){
			trace(ERROR, "[%s]:send failure! line:%d\n", __func__, __LINE__);
		}
	}
	
	return;
}
#endif

/*****************************************************************************************
 * Description:套接字的接口测试函数,TCP服务器端
 *******************************************************************************************/
int serverTCP()
{
	pthread_t pthreadID = 0;
	TCPDEMO_ATTR ClientAttr;
	struct sockaddr_in clientAddr;
	sint32 sfd = 0, ret = 0, port = 20010, cliSocket = -1;
	char ip[64] = {"127.0.0.1"};

	trace(DEBUG, "[%s]:begin line:%d\n", __func__, __LINE__);
#if 1
	/*获取本机ip*/
	char localIP[64] = {0};
	if(0 > (getHostAddr(localIP))){
		trace(ERROR, "[%s]:get local ip failed! line:%d\n", __func__, __LINE__);
	}else{
		memset(ip, 0, strlen(ip));
		memcpy(ip, localIP, strlen(localIP));
	}
#endif
	trace(DEBUG, "[%s]:server addr:%s-%d line:%d\n", __func__, ip, port, __LINE__);
	/*创建套接字*/
	sfd= createSocket(AF_INET, SOCK_STREAM, 0);
	if(0 >= sfd){
		trace(ERROR, "[%s]:create socket failure! line:%d\n", __func__, __LINE__);
		return -1;
	}
	/*bind套接字*/
	if(0 > bindSocket(sfd, AF_INET, ip, port)){
		return -1;
	}
	/*监听套接字*/
	if(listenSocket(sfd, 3) < 0){
		trace(ERROR, "[%s]:listen timeout! line:%d\n", __func__, __LINE__);
		return -1;
	}
	
	trace(DEBUG, "[%s]:server addr:%s-%d fd:%d line:%d\n", __func__, ip, port,  sfd, __LINE__);
	while(1){
		trace(DEBUG, "[%s]:local----------------  line:%d\n", __func__, __LINE__);
		/*接收连接请求*/
		memset(&clientAddr, 0, sizeof(clientAddr));
		cliSocket = acceptSocket(sfd, &clientAddr);
		if(0 >= cliSocket){
			usleep(3*1000*1000);
			trace(ERROR, "[%s][Error]:accept failure re=%d line:%d\n", __func__, ret, __LINE__);
			continue;
		}
		trace(DEBUG, "[%s]:new conenct socket=%d *********************** line:%d\n", __func__, cliSocket, __LINE__);
		memset(&ClientAttr, 0, sizeof(ClientAttr));
		memcpy(&(ClientAttr.addr), &clientAddr, sizeof(clientAddr));
		ClientAttr.fd = cliSocket;
		ret = pthread_create(&pthreadID, NULL, (void *)dealWithData, (void *)&ClientAttr);
		if(ret < 0){
			trace(ERROR, "[%s]:create pthread failure! line:%d\n", __func__, __LINE__);
		}
	}

	return 0;
}

/*****************************************************************************************
 * Description:套接字的接口测试函数,TCP客户端
 *******************************************************************************************/
int clientTCP()
{
	NETWORK_ATTR_S serverNetAttr; /*TCP服务器端的网络信息*/
	int ret = 0, bufLen = 256;
	char ip[64] = {"192.168.5.95"};
	char buffer[256] = {"hello I'm is client!"};

	trace(DEBUG, "[%s]:begin line:%d\n", __func__, __LINE__);
	/*获取本机ip*/
	char localIP[64] = {0};
	if(0 > getHostAddr(localIP)){
		trace(ERROR, "[%s]:get local ip failed! line:%d\n", __func__, __LINE__);
	}else{
		memset(ip, 0, strlen(ip));
		memcpy(ip, localIP, strlen(localIP));
	}
	/*设置TCP服务器端的网络信息*/
	memset(&serverNetAttr, 0, sizeof(serverNetAttr));
	memcpy((serverNetAttr.ip), ip, strlen(ip));
	serverNetAttr.port = 9002;
	serverNetAttr.type = KEEP_ALIVE;
	initTCPClientConnectInfo();
	setNetAttrTCPC(&serverNetAttr);
	
	/*收发送数据*/
	while(1){
		usleep(2*1000*1000);
		/*检测连接是否正常,异常就重新创建连接*/
		if(0 > retry_connect_server_block(&serverNetAttr)){
			trace(ERROR, "[%s]:create connect failure! line:%d\n", __func__, __LINE__);
		} 
		/*收发送数据*/
		ret = send_data(&(serverNetAttr.fd), buffer, strlen(buffer));
		if(0 >= ret){
			serverNetAttr.connect = -1;
			setConnetStatusTCPC(serverNetAttr.connect);
			trace(ERROR, "[%s]:send data failure! line:%d\n", __func__, __LINE__);
			continue;
		}
		trace(DEBUG, "[%s]:send[%d]:%s line:%d\n", __func__, ret, buffer, __LINE__);
		usleep(1*1000*1000);
		//memset(buffer, 0, strlen(buffer));
		ret = read_data(&(serverNetAttr.fd), buffer, bufLen);
		if(0 >= ret){
			trace(ERROR, "[%s]:read data failure! line:%d\n", __func__, __LINE__);
			continue;
		}
		trace(DEBUG, "[%s]:recv[%d]:%s line:%d\n", __func__, ret, buffer, __LINE__);
	}

	return 0;
}



