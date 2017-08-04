/*
 * FileName:
 * Author:         luny  Version: 1.0  Date: 2014-5-6
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _ISAPI_LOGADAPTER_H_
#define _ISAPI_LOGADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "log.h"


#define WEB_LOG_PAGE_SIZE 500

typedef struct
{
    SYSTIME time;  // ��¼��־ʱ��
    char pri_type;     // ������
    char sec_type;     // ������
    char param;        // ��������
    char channel;      // ͨ����
    int host;        // 0-���� ���� �CԶ��IP��0xc0a80006
    char user[17];     // �û���
    char hard_driver;  // Ӳ�̺�
    char sensor_in;    // ��������
    char sensor_out;   // �������
    char reserve[32];  // ����
} WEB_LOGINFO_S, *PWEB_LOGINFO_S;


typedef struct SearchLog
{
    char sid[128];
    char mid[128];
    SYSTIME start_time;
    SYSTIME end_time;
    int  pri_type;   
    int  sec_type;
    int startindex;//��ѯ��ʼλ��
    int max_ret;       
    int result_ret;
    int real_totalnum;//ʵ�������ѯ������������
    WEB_LOGINFO_S log_data[WEB_LOG_PAGE_SIZE];
} SearchLog_S, *pSearchLog_S;

typedef struct
{
    char weblogstr[32];
    int  hostlogindex;
}LOG_TYPE_TRANS, *PLOG_TYPE_TRANS;

int GetISSearchLog(SearchLog_S * search_log);
int master_get_paratype(int index, SearchLog_S * search_log, char *paradata);
int master2web_log_opertype_switch(int index, SearchLog_S * search_log);
int web2master_log_querytype_switch(char * query_xml, int * pri_type, int * sec_type);

#endif
