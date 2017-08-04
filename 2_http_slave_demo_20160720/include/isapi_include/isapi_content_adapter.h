/*
 * FileName:
 * Author:         luny  Version: 1.0  Date: 2014-5-5
 * Description:
 * Version:
 * Function List:
 *                 1.
 * History:
 *     <author>   <time>    <version >   <desc>
 */

#ifndef _ISAPI_CONTENTADAPTER_H_
#define _ISAPI_CONTENTADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "config_usr.h"
#include "config.h"


//#define MAX_DEV_DISK        (12)
#define  ISAPI_MAX_HD  32

typedef enum proxyProtocol
{
     HBGK = 0,
    ONVIF = 1,
    MAX_PROTO
} protocol_e;


#if 0
char protocol_c[][16] =
{
    "HBGK",
    "ONVIF",
    "HUATU"
};
#endif

typedef enum connMode
{
    manual = 1,
    plugplay = 2
} conmode_e;

#if 0
char conmode_c[][16] =
{
    "manual",
    "plugplay"
};
#endif


typedef struct sourceinputportdescriptor
{
    protocol_e proto;
    addrtype_e atype;
    char ipaddr[MAX_STRLEN_128];
    int mport;
    int sport;
    char uname[MAX_STRLEN_32];
    char upw[MAX_STRLEN_32];
    conmode_e cmode;
} inputport_s;

typedef struct InputProxyChannel
{
    int id;
    int online_status;
    int poechannel;//POEͨ����־0-��ͨIPC 1-POEͨ��IPC
    char name[PT_MAX_STRING_EXT];
    inputport_s desc;
} inputproxych_s, *pinputproxych_s;

typedef struct InputProxyChannelList
{
    inputproxych_s ich[MAX_INTPUTPROXYCH];

} INPUTPROXY_S, *pinputproxy_s;

typedef struct streamingProxyChannelIdList
{
    int spch_id[MAX_STREAMID];

} sproxyid_s, *psproxyid_s;


typedef struct inputProxyPortIdList
{
    int ipch_id[MAX_INPUTIO];

} iproxyid_s, *piproxyid_s;


typedef struct outputProxyPortIdList
{
    int opch_id[MAX_INPUTIO];

} oproxyid_s, *poproxyid_s;

typedef struct relatedIOProxy
{
    iproxyid_s iplist;
    oproxyid_s oplist;
} relatedio_s, *prelatedio_s;

typedef struct InputProxyChannelStatus
{
    int id;
    inputport_s desc;
    int online;
    sproxyid_s sid;
    relatedio_s rio;
} instatusch_s, *pinstatusch_s;


typedef struct InputProxyChannelStatusList
{
    instatusch_s ics_list[MAX_INTPUTPROXYCH];

} inproxystat_s, *pinproxystat_s;

typedef enum
{
    CONTENT_RTSP = 0,
} CONTENT_TRANSPORT_E;

typedef enum
{
    CONTENT_H264 = 0,
} CONTENT_VIDEO_CODECTYPE_E;

typedef enum
{
    CONTENT_PROGRESSIVE = 0,//progressive
} CONTENT_VIDEO_SCANTYPE_E;

typedef enum
{
    CONTENT_VBR = 0,
    CONTENT_CBR = 1,
} CONTENT_VIDEO_QUALITYTYPE_E;

typedef enum
{
    CONTENT_JPEG = 0,
} CONTENT_SNAP_IMAGETYPE_E;

typedef enum
{
    CONTENT__AUSTREAM_DISABLE,    //��Ƶ��
    CONTENT__AUSTREAM_ENABLE,     //������
} CONTENT_AUSTREAMADD_E;

typedef struct 
{
    uint32 count;//��ǰ�б�����
    ADAPTER_RES_S list[ADAPTER_MAX_LIST];
} CONTENT_RESLIST_S; //�б��޶��ṹ��

typedef struct
{
    CONTENT_RESLIST_S resoution;  /*�ֱ���*/
    ADAPTER_RANGE_S frame_rate;      /*֡�ʷ�Χ*/
    ADAPTER_RANGE_S bit_rate;        /*��·�Χ�*/
    ADAPTER_RANGE_S quality;   /*ͼ������*/
} CONTENT_VENC_RANGE_S, *PCONTENT_VENC_RANGE_S;

typedef struct
{
    CONTENT_AUSTREAMADD_E byStreamType;  //��Ƶ������
    ADAPTER_RES_S byResolution;   //��Ƶ�ֱ���
    CONTENT_VIDEO_QUALITYTYPE_E byBitrateType; //��������
    int byPicQuality;     //ͼ������
    int dwVideoBitrate;          //��Ƶ���� ʵ������
    int dwVideoFrameRate;        //֡�� PAL 2-30 N 2-30
    int quant;                   //�������� 1-31
}CONTENT_VENC_CONFIG_S, *PCONTENT_VENC_CONFIG_S;

typedef struct
{
    int channel;
    int streamtype;
    CONTENT_VENC_CONFIG_S venc_config;
    CONTENT_VENC_RANGE_S venc_range;    
}CONTENT_VENC_PARAM_S, *PCONTENT_VENC_PARAM_S;

typedef struct
{
    int channel;
    int bright;      /* ����0-255 */
    int contrast;    /* �Աȶ�0-255 */
    int saturation;  /* ���Ͷ�0-255 */
    int hue;         /* ɫ��0-255 */
    int sharp;       /* ��� 0��1 */
    int nr_enable;   /* ��Ƶȥ��ʹ�� 0-�ر� 1-���� */
    int nr_level;    /* ��Ƶȥ�뼶��(0-5) */
    int image_lossdetection; /*��Ƶ��ʧ���*/
}CONTENT_IMAGE_PARAM_S, *PCONTENT_IMAGE_PARAM_S;

typedef struct
{
    uint32 bright;      /* ����0-100 */
    uint32 contrast;    /* �Աȶ�0-100 */
    uint32 saturation;  /* ���Ͷ�0-100 */
    uint32 hue;         /* ɫ��0-100 */
    uint32 sharp;       /* ��� 0-100 */
} CONTENT_IMAGE_SYSCOLOR_S, *PCONTENT_IMAGE_SYSCOLOR_S;

typedef struct
{
    int channel;
    CONTENT_IMAGE_SYSCOLOR_S scene[PT_SCENE_WEAK_LIGHT+1];
}CONTENT_IMAGE_SCENE_PARAM_S, *PCONTENT_IMAGE_SCENE_PARAM_S;

typedef struct
{
    int channel;
    int enable;
    int samplingInterval;
    int startTriggerTime;
    int endTriggerTime;
    int regionType;
    int rowGranularity;
    int columnGranularity;
    int sensitivityLevel;
    uint32  block[18];
}CONTENT_VIDEO_MOTIONDETECTION_S, *PCONTENT_VIDEO_MOTIONDETECTION_S;

typedef enum
{
    DEVTYPE_NULL,           /* Null device */
    DEVTYPE_IDE,            /* IDE hard or SATA hard disk */
    DEVTYPE_RAM,            /* RAM disk */
    DEVTYPE_FLASH,          /* Flash memory */
    DEVTYPE_SD,             /* SD Card */
    DEVTYPE_USB,            /* USB host device */
    DEVTYPE_CDDVD,          /* CDDVD Rom */
    DEVTYPE_ESATA,          /* ESATA device */
    DEVTYPE_NETWORK,        /* network device */
    DEVTYPE_MAX
} DEVTYPE_E;

typedef enum
{
    DEVSTAT_NORMAL   = 0x00, // �豸��������״̬
    DEVSTAT_STANDBY  = 0x01, // �豸���ڴ���״̬(��PT_DEVSTAT_NORMAL����������Ӳ��)
    DEVSTAT_SLEEP    = 0x02, // �豸����˯��״̬(��PT_DEVSTAT_NORMAL��������������Ӳ��,ֻ��������дӲ��ʱ��ȥ����)----��ʱδʹ�������ʽ
    DEVSTAT_ERROR    = 0x03, // �豸���ڴ���״̬
    DEVSTAT_NOFORMAT = 0x04, // �豸δ��ʽ��
} DEVSTATUS_E;

typedef enum
{
    CONTENT_DISK_INFORMAT = 0,//�������ڱ���ʽ��
    CONTENT_DISK_FORMATEND,   //��ʽ������
    CONTENT_FARMAT_ERR ,      //��ʽ������

    CONTENT_DISK_NOEXIST,     //Ҫ��ʽ���Ĵ��̲�����
    CONTENT_DISK_LOST,        //��ʽ����;����
    CONTENT_DISK_BUSY,        //�������ڱ�ʹ��
} CONTENT_FORMATTYPE_E;

typedef struct
{
    uint16 dev_num;         //��ʽ���Ĵ��̺�
    uint16 dev_type;        //��ʽ���Ĵ������� DEVTYPE_E
    sint16 percentstate;    //��ǰ����ֻ��format_stateΪCONTENT_DISK_INFORMATʱ��Ч
    uint16 format_state;    //��ʽ��״̬ CONTENT_FORMATTYPE_E
} CONTENT_FORMATSTATE_S, *PCONTENT_FORMATSTATE_S;

typedef struct
{
    sint16  hdd_attri;      // ��������0:��д��1 ֻ�� ��2 ����
    sint8   hdd_group;      // �����
    sint8   hdd_devno;      // ��ΪESATA��ʱ����ESATA�豸��
    DEVTYPE_E  dev_type;
    sint16  hdd_type;      // ��������0: ������ 1 ������ ��2 ����
    sint16 recv;
} DEVICE_DISK_ATTR_S, *PDEVICE_DISK_ATTR_S;

typedef struct
{
    uint16 dev_num;                 //�豸����ͨ����(���������й���)
    DEVICE_DISK_ATTR_S dev_attr;    //�豸���ԣ�Ĭ��Ӳ�̣�
    DEVSTATUS_E dev_status;         //�豸״̬
    uint32 active;                  //�豸����״̬�����߻��߻��
    uint64 device_capabilty;        //�豸����(�ֽ�) ƽ̨���ݸ�����Ҫ������Ӧת��
    uint32  mfs_fs_active;          //�豸�ļ�ϵͳ�Ƿ��ʽ����0-δ��ʽ����1-�Ѹ�ʽ����2-Ԥ����
    uint64 mfs_free;                //��ǰ��������(�ֽ�)ƽ̨���ݸ�����Ҫ������Ӧת��
} DEVICEINFO_S, *PDEVICEINFO_S;

typedef struct
{
    int disk_num;   /*��ǰ�豸����Ӳ����*/
    DEVICEINFO_S disk_info[ISAPI_MAX_HD];
} CONTENT_DISKINFO_S, *PCONTENT_DISKINFO_S;

typedef struct
{
    sint32 support;
    sint32 port;
}CONTENT_IPC_PROTOCOL_S;


/* �����б����ݽṹ�� */
typedef struct
{
    uint16   cur_index;
    uint16   item_num;
    CONTENT_IPC_PROTOCOL_S  item_list[MAX_PROTO]; /*�豸Э��֧��-protocol_e*/
} CONTENT_IP_SUPPORT_PROT_S;

typedef struct
{
    char       ip_addr[MAX_IPADDR_STR_LEN];    /* ip addr*/
    uint16      dev_type;                       // �豸����: GUI_IPC_TYPE_E
    uint8      stat;                           // ״̬: 0-δ���,1-�����,2-���ʧ��,3-�������
    uint8      online_stat;                    // ����״̬: 0-δ����  1-����
    //uint32      port;                           // �˿ں�
    char        mac_addr[32];           // MAC ��ַ
    char        manufacturer[32];       // ����
    CONTENT_IP_SUPPORT_PROT_S protl;                //�豸֧�ֵ�Э��
    char username[32];
    char password[32];
} CONTENT_IPC_SEARCH_INFO_S;

typedef struct
{
    uint16  num;                       // ���������豸��
    CONTENT_IPC_SEARCH_INFO_S    dev_info[IPC_SEARCH_MAX_NUM]; // IPC��Ϣ
} CONTENT_IPC_SEARCH_S;

typedef struct
{
    sint32 en_title;     // 1-��ʾOSD��0-����ʾ
    uint8 title[PT_MAX_STRING_EXT];// OSD��
    ADAPTER_AREA_S pos_title;    //OSD����������Ϣ
}CONTENT_IPC_OSDATTRI_S, *PCONTENT_IPC_OSDATTRI_S;

typedef struct
{
    sint32  channel;
    uint16  osdnum;          //osd��Ŀ
    uint16  osdattrib;      //OSD����0-��͸�� 1 -͸��
    uint16  format_date;         //���ڸ�ʽ ���������OSD��ò�������,PT_DATEFORMAT_E
    uint16  format_time;         //ʱ����ʾ��ʽ ���������OSD��ò�������,PT_TIMEFORMAT_E
    uint16   en_week;          //�Ƿ���ʾ���� ���������OSD��ò�������
    uint16   refresh_osd;        /* �Ƿ�ˢ��osd 0-Ĭ��ˢ��  1-��ˢ��*/
    CONTENT_IPC_OSDATTRI_S osd[MAX_OSD_NUM];
}CONTENT_IPC_OSDINFO_S, *PCONTENT_IPC_OSDINFO_S;

typedef struct
{
    sint32 almin_no;
    uint8  almin_name[MAX_STRING];  //̽ͷ��
    PT_ALMTYPE_E almtype;           //̽ͷ���� 0-���� 1-����
}CONTENT_ALMIN_CONF_S, *PCONTENT_ALMIN_CONF_S;

int content_get_ipc_info(int ch, INPUTPROXY_S * input);
int content_oper_ipc_add(INPUTPROXY_S * input, WEB_CMD_INFO_S *webinfo);
int content_oper_ipc_delete(int ch, INPUTPROXY_S * input, WEB_CMD_INFO_S *webinfo);
int content_oper_ipc_edit(int ch, INPUTPROXY_S * input, WEB_CMD_INFO_S *webinfo);
int content_get_storage_info(CONTENT_DISKINFO_S * disk_param);
int content_format_storage_progress(CONTENT_FORMATSTATE_S * format_status);
int content_format_storage_disk(sint32 hddtype, sint32 disk_id);
int content_set_storage_attri(sint32 disk_id, DEVICE_DISK_ATTR_S * dev_attr, WEB_CMD_INFO_S *webinfo);
int content_search_ipc(CONTENT_IPC_SEARCH_S * serch_info);
int content_get_channel_param(CONTENT_VENC_PARAM_S * venc_param);
int content_set_channel_param(CONTENT_VENC_PARAM_S * venc_param, WEB_CMD_INFO_S *webinfo);
int content_get_image_param(CONTENT_IMAGE_PARAM_S *image_param);
int content_set_image_param(CONTENT_IMAGE_PARAM_S *image_param, WEB_CMD_INFO_S *webinfo);
int content_get_scene_param(CONTENT_IMAGE_SCENE_PARAM_S *scene_param);
int content_get_video_motiondetection(CONTENT_VIDEO_MOTIONDETECTION_S *motiondetection);
int content_set_video_motiondetection(CONTENT_VIDEO_MOTIONDETECTION_S *motiondetection, WEB_CMD_INFO_S *webinfo);
int content_get_channel_osdinfo(CONTENT_IPC_OSDINFO_S *osdinfo);
int content_set_channel_osdinfo(CONTENT_IPC_OSDINFO_S *osdinfo, WEB_CMD_INFO_S *webinfo);


#endif
