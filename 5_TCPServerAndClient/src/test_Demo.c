
/******************************************************************************
 * Description: ���Գ����Demo
 * file:
 * auth:merlin data:
 * *******************************************************************************/
#include "common.h"
#include "socket_use.h"

extern int serverTCP();
extern int clientTCP();

/*********************************************************************************
* Description:����һ���߳���ΪTCP ��������
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
			clientTCP(); /* ����TCP�ͻ��� */
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
* Description:����һ���߳���ΪTCP ��������
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
			serverTCP();  /* ����TCP�ͻ��� */
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
* Desccription:��ʵ���Ĺ����ǣ�����һ��TCP�������˿ںͿͻ��˿ڡ��ͻ��˸��������˷���Ϣ��
* Ȼ����������ٽ����ݻ�����ͻ���
************************************************************************************/
int demoTCPServerAndClient()
{
	initPrintAndPthread(); /* ��ӡ��ʼ�����̳߳�ʼ�� */
	startTCPServer(); /* ����TCP�������� */
	sleep(3);
	startTCPClient(); /* ����TCP�ͻ��� */

	return 0;
}

/************************************************************************************************
* Description:�������Գ���
**********************************************************************************************/
int main()
{
	//demoTCPServerAndClient();
#if 1
	initPrintAndPthread(); /* ��ӡ��ʼ�����̳߳�ʼ�� */
	startTCPServer(); /* ����TCP�������� */
#endif
}
