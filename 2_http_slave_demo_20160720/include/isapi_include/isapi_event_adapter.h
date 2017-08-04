#ifndef _ISAPI_EVENTADAPTER_H_
#define _ISAPI_EVENTADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"

typedef enum
{
    EVENT_DISK_FULL = 0,//Ӳ����
    EVENT_DISK_ERR,//Ӳ�̴���
    EVENT_NET_DISCONNENT,//����Ͽ�
    EVENT_IP_COLLISION,//IP��ͻ
    EVENT_ILLACCESS,//�Ƿ�����
    EVENT_BADVIDEO,//��Ƶ�ź��쳣
    EVENT_VIDEOMISMATCH,//��Ƶ��ʽ��ƥ��
    EVENT_RECORD_FAILURE,//¼���ץͼ�쳣
    EVENT_VIDEO_LOSS  //��Ƶ��ʧ
}TRIGGER_TYPE_E;

typedef struct
{
    int enable;//����
    int beep; //������
    int fullscreen;//ȫ��
    int email;//�ʼ��ϴ�
    int almpush;//�����ϴ�
    int sensor_out;
    int temp_limit;//�����¶�(�¶ȱ�����Ч)
    int outputDelay;//���������ʱʱ��
    int almoutaudio;//�����Ƶ
    int ptzEnable;//����Ԥ�õ㿪��
    uint32 presetenable[MAX_CH];//������Ԥ�õ�
    int link_record[MAX_CH];
    int link_snap[MAX_CH];//��ͼ����
}TRIGGER_INFO_S, *PTRIGGER_INFO_S;

typedef struct
{
    char event_type[32];//�¼�����
    TRIGGER_INFO_S triggerinfo;
    SCHEDULEINFO_S scheduleinfo;
} EVENT_TRIGGER_S, *PEVENT_TRIGGER_S;

typedef struct
{
    int status[32];
    int alarm_out_no;
} EVENT_MANUAL_S, *PEVENT_MANUAL_S;

int event_get_trigger_info (EVENT_TRIGGER_S * event_info);
int event_set_trigger_info (EVENT_TRIGGER_S * event_info, WEB_CMD_INFO_S *webinfo);
int event_get_schedule_info (EVENT_TRIGGER_S * event_info);
int event_set_schedule_info (EVENT_TRIGGER_S * event_info, WEB_CMD_INFO_S *webinfo);
int event_get_manual_info(PEVENT_MANUAL_S info);
int event_set_manual_info(PEVENT_MANUAL_S info);

#endif

