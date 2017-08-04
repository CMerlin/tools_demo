/*
 * FileName:
 * Author: luny  Version: 1.0  Date: 2014-5-6
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */


#ifndef _ISAPI_RECORDADAPTER_H_
#define _ISAPI_RECORDADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"

#define MAX_ADAPTER_REC_SEG 1000


typedef struct trackDailyParam
{
    int year;
    int month;
    int days[32];
} trackDailyParam_S, *ptrackDailyParam_S;

typedef struct SearchRec
{
    char sid[64];
    int track_id;
    timeSpan_S time_span;
    int startindex;//��ѯ��ʼλ��
    int max_ret;//��ѯ�������
    int real_totalnum;//ʵ�������ѯ������������
    int seg_num;//��ǰ��������
    int success;
    char seg_buf[280000]; //MAX_ADAPTER_REC_SEG * sizeof(PT_RECFILE_SEGINFO_S) = 32000
} SearchRec_S, *pSearchRec_S;

typedef struct SearchRecRet
{
    char sid[36];
    int track_id;
    timeSpan_S time_span;
    int max_ret;
} SearchRecRet_S, *pSearchRecRet_S;

typedef struct
{
    int starth;  //��ʼСʱ
    int startm;  //��ʼ����
    int endh;    //����Сʱ
    int endm;    //��������
}RECORD_TMPERIOD_S, *PRECORD_TMPERIOD_S;

typedef enum
{
    RECORD_CMR = 0,
    RECORD_MOTION,
    RECORD_ALARM,
    RECORD_EDR,
    RECORD_ALARMANDMOTION
}RECORD_MODE_E;

typedef enum
{
    RECORD_WEEK_MON,        //����һ
    RECORD_WEEK_TUES,       //���ڶ�
    RECORD_WEEK_WED,        //������
    RECORD_WEEK_THUR,       //������
    RECORD_WEEK_FRI,        //������
    RECORD_WEEK_SAT,        //������    
    RECORD_WEEK_SUN        //������
} RECORD_WEEK_E;


typedef struct
{
    RECORD_MODE_E recordmode;
    RECORD_TMPERIOD_S tmperiod;    
}RECORD_SCHEDULEINFO_S, *PRECORD_SCHEDULEINFO_S;

typedef struct
{
    RECORD_SCHEDULEINFO_S scheduleinfo[DAY_SEGNUM];//8��ʱ������
}RECORD_TRACKSINFO_S, *PRECORD_TRACKSINFO_S;

typedef struct 
{
    int resolution_w;
    int resolution_h;
    int framerate;
    int bitrate;
    int track_enable;//¼��ƻ��Ƿ�����
    int SaveAudio;//�Ƿ��¼��Ƶ
    int Duration;//¼�����ʱ��
    int LoopEnable;//�Ƿ�ѭ��¼��
    int RedundancyRecord;//�Ƿ�����¼��
    int PreRecordTimeSeconds;//Ԥ¼ʱ��
    int PostRecordTimeSeconds;//�ӳ�¼��ʱ��
    RECORD_TRACKSINFO_S trackinfo[WEEK_DAYNUM];//һ������7��
}RECORD_TRACKSCHANNEL_S, *PRECORD_TRACKSCHANNEL_S;

typedef struct
{
    int online_num;
    int cur_channel;//��λ��ʾ��ͨ����������ʹ��
    RECORD_TRACKSCHANNEL_S tracklist[MAX_CH];
}RECORD_TRACKSLIST_S, *PRECORD_TRACKSLIST_S;

typedef struct
{
    int id;   //ͨ����
    int enable;    //ʹ��
}MANUAL_RECORD_TRACKSCHANNEL_S, *PMANUAL_RECORD_TRACKSCHANNEL_S;

typedef struct
{
    MANUAL_RECORD_TRACKSCHANNEL_S tracklist[MAX_CH];
}MANUAL_RECORD_TRACKSLIST_S, *PMANUAL_RECORD_TRACKSLIST_S;
typedef enum
{
    ISAPI_REC_TYPE_UNKNOW = 0,
    ISAPI_REC_TYPE_MANUAL = 1,      //�ֶ�¼��
    ISAPI_REC_TYPE_SCHEDULE = 2,    //��ʱ¼��
    ISAPI_REC_TYPE_MOTION = 4,      //�ƶ�¼��
    ISAPI_REC_TYPE_ALARM = 8,       //����¼��
    ISAPI_REC_TYPE_CARD = 9,        //����¼��
    ISAPI_PIC_TYPE_MANUAL = 0x11,   //ͼƬ-�ֶ�¼��
    ISAPI_PIC_TYPE_SCHEDULE = 0x12, //ͼƬ-��ʱ¼��
    ISAPI_PIC_TYPE_MOTION = 0x14,   //ͼƬ-�ƶ�¼��
    ISAPI_PIC_TYPE_ALARM = 0x18,    //ͼƬ-����¼��
    ISAPI_PIC_TYPE_ALLPIC = 0x1f,   //ͼƬ-����
    ISAPI_REC_TYPE_ALL = 0xff       //����
} ISAPI_RECTYPE_E;


typedef struct
{
    int channel;
    PT_RECFILESEG_S  recfileseg_info; 
}RECORD_BACKUPINFO_S, *PRECORD_BACKUPINFO_S;

typedef struct
{
    PT_RECSEGINFO_S seginfo;
}RECORD_SEGINFO_S, *PRECORD_SEGINFO_S;

typedef struct
{
    uint32 readsize;
    RECORD_SEGINFO_S recseginfo;
    PT_BACKUPREAD_S  backup_read;
}RECORD_BACKUPREAD_S, *PRECORD_BACKUPREAD_S;

int GetIStrackDailyParam(int channel, trackDailyParam_S * daily);
int GetISSearchRecord(SearchRec_S * search_rec);

#endif
