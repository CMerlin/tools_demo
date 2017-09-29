
/******************************************************************************
 * Description: 测试程序的Demo
 * file:
 * auth:merlin data:
 * *******************************************************************************/
#include "common.h"
#include "socket_use.h"

extern int serverTCP();
extern int clientTCP();

/*********************************************************************************
* Description:创建一个线程作为TCP 服务器端
***********************************************************************************/
int startTCPClient()
{
	pid_t pid1 = fork();
	if(0 < pid1){
		//sleep(1);
		//exit(0);
	}
	else if(0 == pid1){
		//trace(DEBUG, "[%s]:start TCP server line:%d\n", __func__, __LINE__);
		pid_t pid2 = fork();
		if(0 < pid2){
			sleep(1);
			exit(0);
		}
		else if(0 == pid2){
			clientTCP(); /* 创建TCP客户端 */
		}
		else{
			trace(ERROR, "[%s]:fork=%s line:%d\n", __func__, strerror(errno), __LINE__);
		}
	}
	else{
		trace(ERROR, "[%s]:fork=%s line:%d\n", __func__, strerror(errno), __LINE__);
	}
	
	return 0;
}


/**********************************************************************************
* Description:创建一个线程作为TCP 服务器端
**********************************************************************************/
int startTCPServer()
{
	//trace(DEBUG, "[%s]:start line:%d\n", __func__, __LINE__);
	pid_t pid1 = fork();
	if(0 < pid1){
		//sleep(1);
		//exit(0);
	}
	else if(0 == pid1){
		//trace(DEBUG, "[%s]:start TCP server line:%d\n", __func__, __LINE__);
		pid_t pid2 = fork();
		if(0 < pid2){
			sleep(1);
			exit(0);
		}
		else if(0 == pid2){
			serverTCP();  /* 创建TCP客户端 */
		}
		else{
			trace(ERROR, "[%s]:fork=%s line:%d\n", __func__, strerror(errno), __LINE__);
		}
	}
	else{
		trace(ERROR, "[%s]:fork=%s line:%d\n", __func__, strerror(errno), __LINE__);
	}
	
	return 0;
}



/*********************************************************************************
* Desccription:此实例的功能是，创建一个TCP服务器端口和客户端口。客户端给服务器端发信息，
* 然后服务器端再将数据回射给客户端
************************************************************************************/
int demoTCPServerAndClient()
{
	initPrintAndPthread(); /* 打印初始化和线程初始化 */
	startTCPServer(); /* 启动TCP服务器端 */
	sleep(3);
	startTCPClient(); /* 启动TCP客户端 */

	return 0;
}

/************************************************************************************************
* Description:启动测试程序
**********************************************************************************************/
int main()
{
	//demoTCPServerAndClient();
#if 1
	initPrintAndPthread(); /* 打印初始化和线程初始化 */
	startTCPServer(); /* 启动TCP服务器端 */
#endif
}
