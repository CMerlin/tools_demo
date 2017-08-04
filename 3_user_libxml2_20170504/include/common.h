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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
//#include <mxml.h>
#include <stdbool.h>

/* 数据类型定义 */
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
    COMP_SDKAUDIOPRO    = 112,  /* 音频处理模块,主要处理报警,对讲音频 */
    COMP_POECTRL        = 113,  /* POE功率控制模块 */
    COMP_NDCMP          = 114,  /* 设备组网管理模块 */
    COMP_SSOCKET        = 115,  /* 网络套接字基础模块 */
    COMP_NDCMPSRV       = 116,  /* 设备组网管理服务器模块 */
    COMP_DANALE         = 117,  /* 大拿穿透服务 */
    COMP_MAX
} COMPID, *PCOMPID;

/*日志系统用到的打印级别*/
typedef enum
{
	RELEASE,
	ERROR,
	TRACE,
	DEBUG,
} PRINT_LEVEL_E;

/*错误码：函数执行错误的原因*/
typedef enum
{
	SUCCEED, //执行成功
	ERROR_INFO_MIN = -100,
	NULL_VALUE, //传入的参数为null
	CREATE_SOCKET, //创建套接字失败
	CONNECT_FAILED, //创建连接失败
	CREATE_PACKAGE, //创建数据包失败
	SEND_ERROR, //发送数据失败
	RECEIVE_ERROR, //接收数据失败
	XML_WRONG, //http响应帧中没有xml数据
	CREATE_XML, //组装xml文件失败
	HTTP_WRONG, //不正确的http数据帧
	HTTP_EXTEND, //不上上层应用所需要的HTTP数据包
	HTTP_CREATE, //创建http请求包失败
	MEMORY_FAILURE, //获取内存失败
}ERROR_INFO_E;

/*临时结构体*/
typedef struct _interim_data
{
	int id;
	int ip;
	int data;
} ITERIM_DATA_S, *PITERIM_DATA_S;

/*虚拟参数*/
typedef struct _isapi_null
{
	sint32 dummy;
} ISAPI_NULL_S;


/*日志系统相关的函数*/
extern int init_print_level();
extern int trace(const int plevel, const char *format, ...);
/*字符串处理函数*/
extern char* lstrtok_r(char *s, const char *delim, char **save_ptr);
extern int web2master_log_querytype_switch(char * query_xml, int * pri_type, int * sec_type);
#endif
