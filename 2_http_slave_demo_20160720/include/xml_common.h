#ifndef _XML_INFO_H_
#define _XML_INFO_H_

#include "common.h"

/*�궨��*/
#define PT_SUCCESS          1
#define PT_FAILED           0

#define PTZ_CMD_START       32
#define MAX_PTNUM           64          //16//��֧�ֵ�ƽ̨��
#define MAX_REG             8
#define MAX_MASK            4

#define MAX_OSD_NUM         6           //���6��OSD
#define MAX_MASK            4           //���4����������
#define MAX_MOTION          4           //���4���ƶ��������
#define MAX_DEV_DISK        (16)
#define MAX_DEV_USB         (12)
#define MAX_DEV_ESATA       (12)
#define MAX_DEV_CDDVD       (12)
#define PT_MAX_POE_NUM      (32)

#define MAX_PRESET          128
#define PT_MAX_STRING_EXT      64
#define MAX_STRING          32
#define MAX_DNS             4
#define MAX_AM              64
#define MAX_AMOUT           64
#define MAX_CH              64
#define MAX_PERIOD          4           //���ʱ���
#define PT_MAX_ACCOUNT      16          //����û���
#define PT_MAX_PTZ          100
#define PT_MAX_BK           16          //��󱸷���
#define PT_GRP_ACCOUNT      16
#define PT_MAX_MATRIX       64
#define PT_MAX_SMTP_HOST    128
#define PT_MAX_SMTP_ADDR    256
#define PT_MAX_LINE         256
#define PT_MAX_RESNUM       16          //��������ȸ���     0-QCIF, 1-QVGA, 2-CIF, 3-DCIF, 4-HD1, 5-VGA, 6-FD1, 7-SD, 8-HD, 
#define MAX_AM_COUNT        16
#define MAX_VER_LEN         (64)
#define MAX_PAT			        15          //UPNP���ת���˿ڸ���
#define PT_MAX_YDTDOMAIN    (128)       // һ��ͨ������ַ���� 
#define PT_CLIENT_DL_ADDR   (128)       // �ֻ��ͻ������ص�ַ���� 
#define MAX_IP_DEV_NUM 6
#define MAX_DNS_NUM      2
#define MAX_IPADDR_STR_LEN 128
#define MAX_DOMAINNAME_STR_LEN 256


#define NETMGR_MAX_DEVNUM       4 

#define PT_MAX_ADDR_STR        (128)
#define PT_GRAPH_REC_CH_NUM    (8)
#define PT_MAX_COMP_NUM        (36)     //���ģ����
#define PT_MAX_USER		  	   (16)		// ����û���
#define PT_MAX_REC_CH_NUM      (32)
#define PT_REC_DATA_GRAPH_PAGE_NUM (8)
#define PT_MAX_PB_NAME            (2)
#define PT_MAX_RAID_DEV_NUM     (10)
#define PT_MAX_DEV_NUM          (16)
#define PT_MAX_DEV_PATH         (32)
#define PT_GRAPH_DATA_MASK_NUM  (360)

#define PT_MAX_PSK_LEN          (65)
#define PT_MAX_WIFIAP_NUM       (10)
#define PT_MAX_SSID_LEN         (33)
#define PT_MAX_DISPLAY_TYPE_NUM   (4)

#define PT_MAX_INTEL_BLOCK_NUM   (50) //�����������֧������ (n) * 8,��ǰΪ22 * 18 = 396

#define MAX_FILENAME_LENTH (256)
#define MAX_LOGO_NUM (10)           //������ǰ���logo����

#define IPC_SEARCH_MAX_NUM      256     /* ֧����������豸�� */
#define PT_MAX_NVD              16      /* ֧�ֹ���NVR/DVR����豸�� */
#define PT_MAX_ALLOT_NVD        4       /* ÿ��ipc��౻����NVR���� */

#define YDT_MOBILE_ADDR_HB      "http://www.hbydt.cn/emobile.html"       /* ����logo�����÷����������µ��ֻ��ͻ������ص�ַ */
#define YDT_MOBILE_ADD_HB_ZW    "http://www.hbydt.cn/mobile.html"        /* ����logo���������������µ��ֻ��ͻ������ص�ַ */
#define YDT_MOBILE_ADDR_ENG     "http://www.ivview.com/emobile.html"     /* ������Ӣ��logo������Ӣ�������µ��ֻ��ͻ������ص�ַ */
#define YDT_MOBILE_ADDR_SDVR_ZW "http://www.ivview.com/mobile.html"      /* ������Ӣ��logo���������������µ��ֻ��ͻ������ص�ַ */

#define PTUMIN(a, b)      ((a)<(b)?(a):(b))
#define PTIMAX(a, b)      ((a)>(b)?(a):(b))
#define PTCLIP(x, a, b)   ((x)<(a)?(a):((x)>(b)?(b):(x)))
#define PTICLIPI(x, b)    PTCLIP(x, 0, b)
#define PTIZERO(a, b)     ((a)?(b):0)       //aΪ0��0������Ϊb
#define PTINONZERO(a, b)  ((a)?0:(b))       //a��Ϊ0��0��Ϊ0��Ϊb
#define PTIABS(x)         ((x)<0?-(x):(x))  //ȡx ����ֵ
#define PTPACKBYTES(a, b)  (((a<<8)&0xff00)|((b)&0x00ff))
#define PTPACK16LSB(a, b) (((a<<16)&0xffff0000)|((b)&0x0000ffff))
#define PTMUX(x, a, b)    ((x)?(a):(b))     //x��Ϊ0��Ϊa,Ϊ0��Ϊb
#define PTUBYTESEL(x,b)   (((x)>>((b)<<3))&0xff)
#define PTZERO_VAL {0,0,0,0,0,0,0,0}
#define PTPLANAR_ZERO_VAL {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}

#define ISAPI_STREAM_MAXCH 128
#define PT_MAX_LIST 16
#define MAX_DEVINFO_STR_LEN 32
#define MAX_IP_ADDR_LEN     64
#define MAX_STREAMID 2
#define MAX_INPUTIO 4
#define MAX_OUTPUTIO 4
#define MAX_INTPUTPROXYCH 32

#define MAX_STRLEN_128 128
#define MAX_STRLEN_32 32
#define WEEK_DAYNUM  7
#define DAY_SEGNUM 6
#define WEB_LOG_PAGE_SIZE 500
#define ADAPTER_MAX_LIST 16
#define ISAPI_CMD_MAX_LEN   128

typedef enum
{
    ISAPI_DDNS_HANBANG = 0,
    ISAPI_DDNS_ORAY,
    ISAPI_DDNS_DYNDNS,
    ISAPI_DDNS_NO_IP,
    ISAPI_DDNS_MEIBU,
    ISAPI_DDNS_FREEDNS
} DDNS_SERVER_E;

typedef enum
{
    PT_AUTOMODE,        //����Ӧ
    PT_HALFMODE_10M,    //10M��˫��
    PT_FULLMODE_10M,    //10Mȫ˫��
    PT_HALFMODE_100M,   //100M��˫��
    PT_FULLMODE_100M ,  //100Mȫ˫��
    PT_FULLMODE_1000M   //1000Mȫ˫��
} PT_NETMODE_E;

typedef enum
{
    PT_OSD_SYSTIME = 0,
    PT_OSD_CHNAME = 1,
    PT_OSD_CHTIME = 2,
} PT_OSD_E;

typedef enum
{
    PT_OSD_TIME = 0,
    PT_OSD_CHANNEL = 1,
} PT_OSD_OLD_E;

typedef enum addressingFormatType
{
    ipaddress = 1,
    hostname = 2
} addrtype_e;

typedef enum proxyProtocol
{
     HBGK = 0,
    ONVIF = 1,
    MAX_PROTO
} protocol_e;

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

typedef enum connMode
{
    manual = 1,
    plugplay = 2
} conmode_e;

typedef enum
{
    PT_LINKSTATUS_DISABLE,  //������
    PT_LINKSTATUS_ENABLE,   //����
} PT_LINKSTATUS_E;

typedef enum
{
    PT_LOWER = 0, //���
    PT_LOW,     //��
    PT_NORMAL,  //����
    PT_HIGH,    //��
    PT_HIGHER,  //���
} PT_SENSITIVITY_E;

typedef enum
{
    PT_BLOCK_DISABLE,   //���������ƶ��������
    PT_BLOCK_ENABLE,    //�������ƶ��������
} PT_BLOCKENABLE_E;

typedef enum
{
    PT_ALMTYPE_CLOSE,   //����
    PT_ALMTYPE_OPEN,    //����
} PT_ALMTYPE_E;

typedef enum
{
    WEB_PTZ_CMD_STOP,
    WEB_PTZ_CMD_UP,            // ��
    WEB_PTZ_CMD_DOWN,          // ��
    WEB_PTZ_CMD_LEFT,          // ��
    WEB_PTZ_CMD_RIGHT,         // ��
    WEB_PTZ_CMD_FOCUS_INC,     /* �۽�+ */
    WEB_PTZ_CMD_FOCUS_DEC,     /* �۽�- */
    WEB_PTZ_CMD_IRIS_INC,      /* ��Ȧ+ */
    WEB_PTZ_CMD_IRIS_DEC,      /* ��Ȧ- */
    WEB_PTZ_CMD_ZOOM_DEC,      /* ����+ */
    WEB_PTZ_CMD_ZOOM_INC,      /* ����- */
    WEB_PTZ_CMD_F1,            // ����
    WEB_PTZ_CMD_F1_1,
    WEB_PTZ_CMD_F2,            // ����
    WEB_PTZ_CMD_F2_1,
    WEB_PTZ_CMD_AUTO,          // �Զ�
    WEB_PTZ_CMD_AUTO_1,
    WEB_PTZ_CMD_PRESET_SET,    // Ԥ��
    WEB_PTZ_CMD_PRESET_GET,    // ����
    WEB_PTZ_CMD_SETUP,
    WEB_PTZ_CMD_ENTER,
    WEB_PTZ_CMD_PAGEUP,
    WEB_PTZ_CMD_PAGEDOWN,
    WEB_PTZ_CMD_BRUSH,         // ��ˢ
    WEB_PTZ_CMD_LEFT_UP,       //24����
    WEB_PTZ_CMD_LEFT_DOWN,     //25����
    WEB_PTZ_CMD_RIGHT_UP,      //26����
    WEB_PTZ_CMD_RIGHT_DOWN,    //27����
    WEB_PTZ_CMD_PRESET_CLR,    //28Ԥ�õ����
    WEB_PTZ_CMD_SET_PATTERN_START, //29�켣Ѳ��--���ÿ�ʼ
    WEB_PTZ_CMD_SET_PATTERN_END,   //30�켣Ѳ��--���ý���
    WEB_PTZ_CMD_SET_PATTERN_RUN,   //31�켣Ѳ��--����

} ADDTYPE_E;

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
    PT_AUTO_DISABLE,    //���Զ�����
    PT_AUTO_ENABLE,     //�Զ�����
} PT_AUTOENABLE_E;

typedef enum
{
    PT_SUCCESS_FAIL,    //ʧ��
    PT_SUCCESS_SUCC,    //�ɹ�
} PT_SUCCESS_E;

typedef enum
{
    PT_CONNECT_NO,      //�Ͽ�
    PT_CONNECT_YES,     //����
    PT_NOOPERATE        //�޶���
} PT_CONNECT_E;

/*�ṹ�嶨��*/
typedef struct
{
    uint16 left; //��ʼ�������
    uint16 top; //��ʼ��������
    uint16 width; //���
    uint16 height; //�߶�
} ADAPTER_AREA_S;

typedef enum
{
    SINGLE  = 0,
    DUAL    = 1
} LIPVER_E;

typedef enum
{
    half = 0,
    full = 1
} DUPLEX_E;

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

/*�ṹ��Ķ���*/
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
    char almout_name[MAX_STRING];
    int defaultState;
    int outputState;
    int pulseDuration;
}SYSTEM_IO_OUTPUT_S, *PSYSTEM_IO_OUTPUT_S;

typedef struct
{
    SYSTEM_IO_OUTPUT_S  io_output[MAX_AMOUT];
}SYSTEM_IO_OUTPUTLIST_S, *PSYSTEM_IO_OUTPUTLIST_S;

typedef struct
{
    char   almin_name[MAX_STRING];
    sint32 enabled;
    sint32 triggering;    
}SYSTEM_IO_INPUT_S, *PSYSTEM_IO_INPUT_S;

typedef struct
{
    SYSTEM_IO_INPUT_S  io_input[MAX_AM];
}SYSTEM_IO_INPUTLIST_S, *PSYSTEM_IO_INPUTLIST_S;

typedef struct
{
    char dev_name[MAX_DEVINFO_STR_LEN];     /* �豸���� */
    char dev_no[MAX_DEVINFO_STR_LEN];       /* �豸���к� */
    char dev_id[MAX_DEVINFO_STR_LEN];       /* �豸�� */
    char dev_type[MAX_DEVINFO_STR_LEN];     /* �豸�ͺ� */
    char main_ver[MAX_DEVINFO_STR_LEN];     /* ���ذ汾 */
    char main_date[MAX_DEVINFO_STR_LEN];
    char venc_ver[MAX_DEVINFO_STR_LEN];     /* ����汾 */
    char venc_date[MAX_DEVINFO_STR_LEN];
	uint32 telecontrol_id;                  /* ���ڿ��ƺ� */
    uint32 ch_num;                          /* ͨ������ */
    uint32 disk_num;                        /* Ӳ�̸��� */
    uint32 sensor_in;                       /* ����������� */
    uint32 sensor_out;                      /* ����������� */
    uint32 ipc_pap;                         /* IPC���弴��ʹ�� */
}SYSTEM_DEVICE_INFO_S, *PSYSTEM_DEVICE_INFO_S;

typedef struct
{
    uint32 sec : 6;     /* ��: 0~63 */
    uint32 min : 6;     /* ��: 0~63 */
    uint32 hour : 5;    /* ʱ: 0~23 */
    uint32 day : 5;     /* ��: 1~31 */
    uint32 month : 4;   /* ��: 1~12 */
    uint32 year : 6;    /* ��: 0~63 */
}SYSTEM_TIME_S, *PSYSTEM_TIME_S;

typedef struct
{
    SYSTEM_TIME_S    dev_time;        /* ����ʱ�� */
}SYSTEM_TIME_CFG_S, *PSYSTEM_TIME_CFG_S;

//�˿ڵ�ַ��Ϣ
typedef struct
{
    char rout_ip[20];                   //·����ip
    char server_name[MAX_STRING];       //ת���˿�����
    uint16 protocol;        //Э��
    uint16 dvr_port;        //DVR�˿�
    uint16 rount_port;      //·�����˿�
    sint16  status;         //״̬
    uint32 pat_en;          //��־�����Ƿ�ѡ��:1:ѡ�У�0:δѡ��
} NETWORK_PAT_UPNP_S;

typedef struct
{
    char rout_ip[20];            //·����ip
    char wan_ip[20];             //wan�˿ڵ�ַ
} NETWORK_UPNP_SEARCH;

//UPNP����
typedef struct
{
    uint32  upnp_en;                     // UPNP ʹ��
    uint16  pat_count;                   //ת���˿ڸ���
    uint16  status;                    //·��������
    NETWORK_PAT_UPNP_S  pat_info[MAX_PAT];   //ת���˿���Ϣ
    NETWORK_UPNP_SEARCH rout_info; //�����ӵ�·��������Ϣ
} NETWORK_UPNP_S, *PNETWORK_UPNP_S;

typedef struct
{
    sint32  index;                      //ddns����
    uint8   server[MAX_STRING];         // ��ǰ��������ַ
    uint8   user[MAX_STRING];           // �û���
    uint8   pwd[MAX_STRING];            // ����
    uint32  ip_addr;                    // ���������ص�IP��ַ    
    uint8   dn[MAX_DNS * MAX_STRING];   // �����ĵ�ַ ��֧�ַ������4��DNS����
    PT_AUTOENABLE_E auto_connect;       // �Ƿ�Ϊ�Զ�����
    PT_SUCCESS_E    status;             // �Ƿ�����ɹ�
    PT_CONNECT_E    command;            // ���Ӷ���
    uint8   set_dn[PT_MAX_LINE];        // ��������(��Щ������������Ҫ�趨���������߶������ʱָ��һ��ʱ��)
    uint32  gui_get_flag;               //ֵΪ1����ʾֱ�ӽ���״̬����ȡ�Ķ��������ַ����dn_set�����GUI    
    uint8   hb_defuser[MAX_STRING];           // �û���
    uint16  domain_default_flag;        // ����Ĭ�Ϸ�Ĭ�ϱ�־λ��0ΪĬ�ϣ�1Ϊ��Ĭ��
    uint16	iterm_num;
    uint8   list_iterm[12][MAX_STRING]; //֧�ַ������ĸ����Լ��������б���ǰ����������
}NETWORK_DDNS_S, *PNETWORK_DDNS_S;

typedef struct
{
    char userName[MAX_STRING];
    char pwd[MAX_STRING];
    int  status;
    int  autologin;
} NETWORK_PPPOE_S, *PNETWORK_PPPOE_S;

typedef struct
{
    int iterm_num;   //֧��������
    int list_iterm[PT_MAX_LIST];      //�б��� ,// 0-����Ӧ, 1-10M��˫����2-10ȫ˫����3-100M��˫���� 4-100Mȫ˫����5-1000Mȫ˫��
} PHY_MODE_LIST_S, *PPHY_MODE_LIST_S;

typedef struct
{
    PHY_MODE_LIST_S phy_mode; // 0-����Ӧ, 1-10M��˫����2-10ȫ˫����3-100M��˫���� 4-100Mȫ˫����5-1Gȫ˫��
    char mac[16];
    int  nego;
    int speed;
    DUPLEX_E duplex;
    int mtu;
    int mtu_min;
    int mtu_max;
} LINK_S, *PLINK_S;

typedef struct
{
    LIPVER_E ipver;
    int dhcp_enable;     //dhcpʹ��
    int ipaddr;
    int netmask;
    int gateway;
    int dns1;
    int dns2;
    int ipv6[4];
    int ipv6_mask[4];
} IPADDR_S, *PIPADDR_S;

typedef struct
{
    int upnp;
    int zeroconf;
} DISCOVERY_S, *PDISCOVERY_S;

typedef struct
{
    int id;
    IPADDR_S ip;
    DISCOVERY_S discovery;
    LINK_S link;
}NETWORK_DEVICE_INFO_S, *PNETWORK_DEVICE_INFO_S;

/* ϵͳʱ�䶨�� */
typedef struct
{
    uint32 sec : 6;     /* ��: 0~63 */
    uint32 min : 6;     /* ��: 0~63 */
    uint32 hour : 5;    /* ʱ: 0~23 */
    uint32 day : 5;     /* ��: 1~31 */
    uint32 month : 4;   /* ��: 1~12 */
    uint32 year : 6;    /* ��: 0~63 */
} SYSTIME, *PSYSTIME;

typedef struct
{
    char   streamid[64];
    int    status;
    sint16 channel;
    sint16 type;
}STREAMING_STATUS_INFO;

typedef struct
{
    STREAMING_STATUS_INFO stream_info[ISAPI_STREAM_MAXCH];
}WEB_HEARTBEAT_INFO;

typedef struct
{
    char   streamid[64];
    char   option[32];
    sint32 speed;
}STREAMING_PB_CONTROL, *PSTREAMING_PB_CONTROL;

typedef struct SecurityUser
{
    char user_name[MAX_STRING];
    char user_pwd[MAX_STRING];
    uint64    local_authority[32];
    uint64    remote_authority[16];
    uint32    bind_ipaddr;                  // Զ�̰�IP
    uint8     bind_macaddr[8];        // Զ�̰�MAC
    sint32    user_pwdflag;  //�Ƿ��޸�����
} SECURITY_USER_S, *PSECURITY_USER_S;

typedef struct
{
    sint32 httpport;
    sint32 listenport;
    sint32 rtspport;
    sint32 rtmpport;
    sint32 upgradeport;
}SECURITY_PORTINFO_S, *PSECURITY_PORTINFO_S;

typedef struct
{
    int status[32];
    int alarm_out_no;
} EVENT_MANUAL_S, *PEVENT_MANUAL_S;

typedef struct timeSpan
{
    SYSTIME start;
    SYSTIME end;
} timeSpan_S, *ptimeSpan_S;

typedef struct
{
    timeSpan_S tmperiod[DAY_SEGNUM];    
}TIMEPERIOD_S, *PTIMEPERIOD_S;

typedef struct
{
    TIMEPERIOD_S timeperiodinfo[WEEK_DAYNUM];
}SCHEDULEINFO_S, *PSCHEDULEINFO_S;

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
    uint32  channel;    // ͨ����
    uint32  command;    // ��̨�������� Ϊ0x00010028��ֹͣ
    uint32  index;      // Ԥ�Ƶ��(�������Чֵ��ΧӰ��)[0, 255]
    uint32  speed;      // �����ٶ� [0, 255] ��0���ٶ���������
} PTZ_DEVICE_CTRL;

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

typedef struct
{
    int starth;  //��ʼСʱ
    int startm;  //��ʼ����
    int endh;    //����Сʱ
    int endm;    //��������
}RECORD_TMPERIOD_S, *PRECORD_TMPERIOD_S;

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
    sint32 almin_no;
    uint8  almin_name[MAX_STRING];  //̽ͷ��
    PT_ALMTYPE_E almtype;           //̽ͷ���� 0-���� 1-����
}CONTENT_ALMIN_CONF_S, *PCONTENT_ALMIN_CONF_S;


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
    sint16 width;
    sint16 height;
}ADAPTER_RES_S;

typedef struct 
{
    uint32 count;//��ǰ�б�����
    ADAPTER_RES_S list[ADAPTER_MAX_LIST];
} CONTENT_RESLIST_S; //�б��޶��ṹ��

typedef struct 
{
    sint32 max_value;
    sint32 min_value;
} ADAPTER_RANGE_S; //��Χ�޶��ṹ��

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

#if 0
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
ISAPI_FD_S isapi_fd = {0};
#endif

/*NTP������ص���Ϣ*/
typedef struct
{
    char    ntp_host[MAX_IP_ADDR_LEN];   /* NTP���������� */
    uint32  ntp_port;               /* NTP�������˿� */
    uint32  autontp_enable;                     /* NTPУʱʹ�� */// ����ntp����,0- ������ ,1-��ʾ�Զ� ��2-��ʾ�ֶ�
    uint32  server_index;         // ������������
    uint32  ajust_period;               /* NTPУʱ����() */
    uint32  sync_unit;                   /* ���ڵ�λ��0-���� 1-Сʱ 2-�� 3-���� 4-��*/
    sint32  time_zone;            /* ʱ�� */
}SYSTEM_NTP_CFG_S, *PSYSTEM_NTP_CFG_S;

typedef struct
{
    int id;
    char   host[PT_MAX_SMTP_HOST];     // �����ʼ���SMTP�����������磺126�������smtp.126.com
    int    port;                        // �������˿ڣ������ʼ�(SMTP)�˿ڣ�Ĭ��ֵ25
    char   user[MAX_STRING];            // �ʼ��û���
    char   pwd[MAX_STRING];             // �ʼ��û�����
    char   send_addr[PT_MAX_SMTP_HOST];  // FROM���ʼ���ַ
    char   recv_addr[PT_MAX_SMTP_ADDR];  // TO���ʼ���ַ�����8�������ַ
    int    send_period;                 // �ϴ�����,��λ(����,���ֵ120)
    int    snap_enable;              // �Ƿ�ץ���ϴ�
    int    ssl_enable;              // ssl����ʹ�ܣ�0-�ر� 1-����
    int    starttls_enable;         // 0-�ر� 1-����
} NETWORK_SMTP_S, *PNETWORK_SMTP_S;

/*Webͨ�õ�״̬�ظ�*/
typedef struct _common_response
{
	char requestURL[256];
	int statusCode;
	char statusString[32];
	char subStatusCode[32];
} COMMON_RESPONSE_S, *PCOMMON_RESPONSE_S;
#endif
