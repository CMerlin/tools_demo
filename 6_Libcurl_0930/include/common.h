/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:common.h
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:一些共用结构体的定义
 * History:
 * *************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#if 1
#include <math.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <errno.h>
#include <netdb.h>
#include <time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/sem.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <dirent.h>
#endif

/*基础数据类型的定义*/
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;
typedef signed long         slng32;
typedef signed long long    sint64;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long       ulng32;
typedef unsigned long long  uint64;

/* 模块ID定义 */
typedef enum
{
    COMP_SSOCKET        = 115,  /* 网络套接字基础模块 */
    COMP_NDCMPSRV       = 116,  /* 设备组网管理服务器模块 */
    COMP_DANALE         = 117,  /* 大拿穿透服务 */
    COMP_MAX
} COMPID, *PCOMPID;

/*日志打印级别*/
typedef enum
{
	RELEASE,
	ERROR,
	TRACE,
	DEBUG,
} PRINT_LEVEL_E;

/***********************************************************************
* Description:数据包的属性信息
*************************************************************************/
typedef struct _package_attr
{
	char head[32];
	char tail[32];
	char special[32];
	int len;
	int attr;
} PACKET_ATTR_S, *PPACKET_ATTR_S;

/*收发数据帧的特点描述*/
typedef enum
{
	PACKET_ATTR_MIN_E,
	PACKET_ATTR_HEADANDTAIL_E, /*有头有尾*/
	PACKET_ATTR_HEAD_E, /*有头无尾*/
	PACKET_ATTR_LEN_E, /*固定长度*/
	PACKET_ATTR_SPECIAL_E, /*特殊字符串*/
	PACKET_ATTR_TAIL_E, /*只有尾巴*/
	PACKET_ATTR_MAX_E,
} PACKET_ATTR_E;

/*日志操作相关函数*/
extern int init_print_level();
extern int trace(const int plevel, const char *format, ...);
extern int initPrintAndPthread();
/* 公共函数 */
extern int time_utoc(time_t src_time, char *dest_time, int rank);
#endif

