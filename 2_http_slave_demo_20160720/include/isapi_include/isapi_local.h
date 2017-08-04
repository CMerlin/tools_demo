#ifndef _ISAPI_LOCAL_H_
#define _ISAPI_LOCAL_H_

#include "common.h"
#include "log.h"
#include "goahead.h"

#define MAX_UPGRADE_SIZE    (0x800000 * 4 + 0x800)  /* �����ļ��������Ϊ32Mb + 2Kb(2K��Ԥ������9��FILE_HEADER_S�ṹ��ռ�Ĵ�С) */
#define ISAPI_CMD_MAX_NUM   16
#define ISAPI_CMD_MAX_LEN   128
#define ISAPI_MAX_STRLEN    256
#define ISAPI_IPLEN   4

typedef enum
{
	ISAPI_STATUSCODE_OK = 1,
	ISAPI_STATUSCODE_DEVBUSY = 2,
    ISAPI_STATUSCODE_DEVERROR = 3,
    ISAPI_STATUSCODE_INVALID_OPERATION = 4,
    ISAPI_STATUSCODE_INVALID_XMLFORMAT = 5,
    ISAPI_STATUSCODE_INVALID_XMLCONTENT = 6,
    ISAPI_STATUSCODE_REBOOTREQUIRED = 7,

}ISAPI_STATUSCODE_E;

typedef enum
{
    ISAPI_SUBSTATUSCODE_OK = 1,
    
    ISAPI_SUBSTATUSCODE_NOTSUPPORT = 10,
    ISAPI_SUBSTATUSCODE_INVALID_OPERATION,
    ISAPI_SUBSTATUSCODE_LOWPRIVILEGE,

    ISAPI_SUBSTATUSCODE_BAD_PARAM = 20,

    ISAPI_SUBSTATUSCODE_REBOOTREQUIRE = 30,
    
    ISAPI_SUBSTATUSCODE_ERROR_IP = 40,
    ISAPI_SUBSTATUSCODE_ERROR_MAC,
    ISAPI_SUBSTATUSCODE_ERROR_PWD,
    ISAPI_SUBSTATUSCODE_ERROR_USER,
    ISAPI_SUBSTATUSCODE_ERROR_OTHER,
}ISAPI_SUBSTATUSCODE_E;

enum
{
    ISAPI_USER_RIGHT_PREVIEW = 0,                 //ʵʱԤ��Ȩ��C
    ISAPI_USER_RIGHT_REC_MANUAL,              //�ֶ�¼��C
    ISAPI_USER_RIGHT_REC_PB,                  //¼���ѯ�ط�C
    ISAPI_USER_RIGHT_BACKUP,                  //���ݹ���C
    ISAPI_USER_RIGHT_REC_SET_REC_PARAM,       //¼�����C
    ISAPI_USER_RIGHT_PTZ,                     //��̨Ȩ��C
    ISAPI_USER_RIGHT_SNAPSHOT,                //��ͼC
    ISAPI_USER_RIGHT_SET_CH_SET,              //ͨ������C
    ISAPI_USER_RIGHT_REC_SET_REC_PLAN,        //��ʱ¼��C
    ISAPI_USER_RIGHT_ALM_SET_MOTION,          //�ƶ�����C
    ISAPI_USER_RIGHT_ALM_SET_ALM,             //��������C

    ISAPI_USER_RIGHT_NVR_MGR,                 //��������          11
    ISAPI_USER_RIGHT_CH_MGR,                 //ͨ������

    ISAPI_USER_RIGHT_SET_MAN_GENERAL,         //��������
    ISAPI_USER_RIGHT_SET_MAN_UART,            //��������
    ISAPI_USER_RIGHT_HDD_MAN,                 //���̹���
    ISAPI_USER_RIGHT_SET_MAN_NET,             //��������
    ISAPI_USET_RIGHT_INFO_VIEW,               //��Ϣ�鿴Ȩ��
    ISAPI_USER_RIGHT_SYS_MAN_UPGRADE,         //����Ȩ��
    ISAPI_USER_RIGHT_SYS_MAN_FAST_SET,        //��������
    ISAPI_USER_RIGHT_SYS_MAN_DEFAULT,         //�ָ���������Ȩ��
    ISAPI_USER_RIGHT_IMPORT,                  //���뵼��          21
    ISAPI_USER_RIGHT_SHUTDOWN,                //ϵͳ�ػ�

    ISAPI_USER_RIGHT_REC_SET_REC_CARD,        //����¼������C
    ISAPI_USER_RIGHT_MAX,
};


enum
{
    ISAPI_USER_REMOTE_RIGHT_PREVIEW  = 0,          //ʵʱԤ��Ȩ��C
    ISAPI_USER_REMOTE_PARAM_SET,              //��������Ȩ��C
    ISAPI_USER_REMOTE_PB,                     //�ط�Ȩ��C
    ISAPI_USER_REMOTE_BACKUP,                 //����Ȩ��C
    ISAPI_USER_REMOTE_LOG,                    //��־�鿴Ȩ��
    ISAPI_USER_REMOTE_VOICE_CHAT,             //�Խ�
    ISAPI_USER_REMOTE_UPGRADE,                //����
    ISAPI_USER_REMOTE_RIGHT_MAX,
};

enum
{
   ISAPI_STAT_NULL = 0,
   ISAPI_STAT_CMD_START,
   ISAPI_STAT_CMD_END,
   ISAPI_STAT_CMD_ERROR,
};

enum {
    ISAPI_UPNP_DISCONNECT,    // �ѶϿ�����
    ISAPI_UPNP_SEARCHING,     // ��������    
    ISAPI_UPNP_SCAN_SUCC,     // ɨ��ɹ�
    ISAPI_UPNP_SCAN_FAIL,     // ɨ��ʧ��
    ISAPI_UPNP_PORT_CONFLICT, // �˿ڳ�ͻ
}ISAPI_UPNP_STAT_E;


typedef struct
{
    //uint32 flag; /* ���ںϷ��Լ�� */
    //uint32 healthy; /* �������״��,0-����,����-���� */
    //sint32 running; /* �߳����б�� */
    sint32	sysnetapi_handle;			//���ؽӿھ��
    WebsHash is_t;
    WebsHash system_t;
    WebsHash contentmgmt_t;
    WebsHash network_t;
    WebsHash media_t;
    WebsHash ptz_t;
    WebsHash event_t;
    WebsHash security_t;
    WebsHash streaming_t;
    WebsHash notification_t;
    notifycallback notifyfunc;  /* ��Ϣ�ص�֪ͨ���� */
    pthread_mutex_t mutex;      /* �̻߳��� */
    pthread_t tid;              /* �߳�ID�� */
    pid_t pid;                  /* �߳�PID */
    sint32 update_process;
    sint32 upgradestart;
    sint32 backupstatus;
    char   backupid[64]; 
    sint32 backup_process;
    sint32 maxchannel;
    uint32 sensorin_no;         // ����������
    uint32 sensorout_no;        //���������
    sint32 upnpstatus;
    sint32 webstat;
    char   webcmd[ISAPI_CMD_MAX_LEN];
} ISAPI_FD_S, *PISAPI_FD_S;

extern  ISAPI_FD_S isapi_fd;

#endif
