#ifndef SYSNET_H_
#define SYSNET_H_

#include "common.h"

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

typedef int PT_MFSDEV_HANDLE;//�豸�����������
/*********************************************************************************
* �������ܣ���̨���ƺ���
* ���������handle: ���ƾ��
            cmd: ��������
            puartconf: ���ڲ���
            speed: ��̨����
            addr:��̨��ַ��
            param:���Ʋ�������Ԥ�Ƶ�
* �����������
* ����ֵ  ��0---�ɹ���<0---ʧ��
**********************************************************************************/
typedef int (*ptptz_control)(int handle, int cmd, int puartconf, int speed, int addr, int param);

/*********************************************************************************
* �������ܣ����ݴ���ص�
* ���������idx: ͨ����
            data: ���ݽ��ջ�����
            size: ���ݽ��ջ�������С
            flag: 0--���������� 1--����������
               paramin---����ָ���ݲ���
* �����������
* ����ֵ  ����
* ע: ��fifoΪ0ʱ�����ݴ洢��data�У�size��ʾ���ݳ���
*     ��fifo��Ϊ0ʱ�����ݴ洢��fifo�У�data��ʾ�û���������ַ��size��ʾ����������
*     ��fifo,data��Ϊ��ʱ����ʾ��������Ҫ����Ҳ�����ݴ���������
**********************************************************************************/
typedef int (*PNETSETVSTREAM)(sint32 idx, sint8 * data, uint32 size, sint32 flag, void * paramin);

/*********************************************************************************
* �������ܣ��Խ���Ƶ���ݴ���ص�
* ���������pdata --- ��Ƶ����ָ��
                                len --- ��Ƶ���ݴ�С
                                paramin---����ָ���ݲ���
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef int (*PNETSETASTREAM)(sint8 * data, uint32 size, sint32 type, void * paramin);

/********************************************
��������:  ������Ϣ�ص�����
�������:  ch--- ͨ���Ż�̽ͷ��(��0��ʼ)
                         type---���ṹ��PT_ALARMTYPE_E
                         status---���ṹ��PT_ALARMSTATUS_E
                         paramin---����ָ���ݲ���
�������:  ��
����ֵ:    ��
*********************************************/
typedef int (*PNETSETALARMINFO)(sint32 ch, sint32 type, sint32 status, void * paramin);

/********************************************
��������:  ¼��طŻص�����
�������:  idx--- ͨ���Ż�̽ͷ��(��0��ʼ)
                         data: ���ݽ��ջ�����
                         size: ���ݽ��ջ�������С
                         paramin---����ָ���ݲ���
�������:  ��
����ֵ:    ��
*********************************************/
typedef int (*PPLAYBACKSTREAM)(sint32 idx, sint8 * data, uint32 size, void * paramin);

/********************************************
��������: ֪ͨ����ģ��ص�����
�������:
                         wparam: ����
                         lparam: ����
�������:  ��
����ֵ:    ��
*********************************************/
typedef void (*PNETNOTIFYCALL)(int wparam, int lparam);

/*********************************************************************************
* �������ܣ�͸���������ݴ���ص�
* ���������data --- ͸����������ָ��
                                size --- ͸���������ݴ�С
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef int(*PNETSERIALSTREAM)(sint8 * data, uint32 size);
/*********************************************************************************
* �������ܣ�����ģ�鱨����Ϣ����ص�
* ���������alarminfo --- ����ģ����Ϣָ��
                              size_alarminfo --- ����ģ����Ϣ��С
                              pic_data--ͼƬ�����ַ�������ͼƬ����ΪNULL
                              pic_size--ͼƬ���ݴ�С
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef int(*PATMIALARMINFONOTIFY)(sint8 * alarminfo, uint32 size_alarminfo, sint8 * pic_data, uint32 pic_size);

/************************************************
    *��������:����������Ƶ�ص�����
    * ���������idx: ͨ����
                fifo: ���ݻ���FIFO
                data: ���ݽ��ջ�����
                size: ���ݽ��ջ�������С
    �������:��
    ����ֵ:��
*************************************************/
datacallback sysnetapi_privideocallback(sint32 idx, sint32 fifo, sint8 * data, sint32 size);

/************************************************
*��������:  ����������Ƶ�ص�����
* ���������idx: ͨ����
            fifo: ���ݻ���FIFO
            data: ���ݽ��ջ�����
            size: ���ݽ��ջ�������С
�������:��
����ֵ:��
*************************************************/
datacallback sysnetapi_secvideocallback(sint32 idx, sint32 fifo, sint8 * data, sint32 size);

/************************************************
*��������:  �Խ��ص�����
* ���������idx: ͨ����
            fifo: ���ݻ���FIFO
            data: ���ݽ��ջ�����
            size: ���ݽ��ջ�������С
�������:��
����ֵ:��
*************************************************/
datacallback sysnetapi_talkcallback(sint32 idx, sint32 fifo, sint8 * data, sint32 size);

/********************************************
��������:  ͳһ����Ϣ/���ݻص���ʽ(�Ƽ�ʹ��)
�������:
�������:  ��
����ֵ:    ��
*********************************************/
typedef int (*PNETAPICALLBACK)(sint32 cmd, sint32 ch, sint32 * param, sint32 param_size, int flag);

typedef sint32(*PNETDATACALLBACK)(sint32 channel, sint32 id, sint8 * data, uint32 size, void * user_data, sint32 data_size);

typedef enum
{
    SYSNETAPI_SENSOR = 0,       //̽ͷ����
    SYSNETAPI_MOTION,           //�ƶ���ⱨ��
    SYSNETAPI_VLOST,            //��Ƶ��ʧ����
    SYSNETAPI_DISKFULL,         //����������
    SYSNETAPI_DISKERR,          //���̴��󱨾�
    SYSNETAPI_VMASK,            //��Ƶ�ڵ�����  5
    SYSNETAPI_PTCONFIG_CHANGE,  //ƽ̨�����ļ��ı� ��ƽ̨ģ���յ��ñ�����Ϣ����Ҫ���»�ȡƽ̨�����ļ���ԭ�е������ļ��Ա�
    SYSNETAPI_VIDEO_CONNECT,    //0-������ 1-������
    SYSNETAPI_SENSOR_DETECT,    //0-�޴��� 1-�д���
    SYSNETAPI_MOTION_DETECT,    //0-�޴��� 1-�д���
    SYSNETAPI_ATMI_ALARM,       //����ģ�鱨��
    SYSNETAPI_DISK_NO_FORMAT,   //Ӳ��δ��ʽ��
    SYSNETAPI_DEFENCE_STAT,     //֪ͨ����/����״̬
} PT_ALARMTYPE_E;

typedef enum
{
    ALARM_START = 0,    //��������
    ALARM_END,          //�������
} PT_ALARMSTATUS_E;

typedef enum
{
    SYSPT_CMD_GET_PTINFO,
    SYSPT_CMD_SET_PTINFO,
    SYSPT_CMD_TEST_FTPUPLOAD,
} SYSPT_CMD;

typedef enum
{
    PT_NOTIFY_UPDATE,
    PT_NOTIFY_UPGRADEPOS,
    PT_NOTIFY_VIDEOSYS,
    PT_NOTIFY_ALARMINOPEN, //��ʱ����
    PT_NOTIFY_ALARMINCLOSE, //����
} PT_SYSNETAPI_NOTIFY_E;

typedef enum
{
    PT_UPDATE_START,       //��ʼ����״̬
    PT_UPDATE_SUCCESS,     //�����ɹ�
} PT_UPDATE_STATUS_E;

typedef enum
{
    PT_UPDATE_ERROR_CHECKFILE = ERRNO(COMP_ERROR_START, COMP_HBSDK), //�����ļ�У�����
    PT_UPDATE_ERROR_COVERFILE,      //�����ļ��滻����
    PT_UPDATE_ERROR_PARAM,          //��������
    PT_UPDATE_ERROR_RWFILE,         //��д�ļ�ʧ��
    PT_UPDATE_ERROR_OPENFAIL,       //������ģ��ʧ��
    PT_UPDATE_ERROR_USB_NOTFIND,    //
    PT_UPDATE_ERROR_FTP_DOWNLOAD,
    PT_UPDATE_ERROR_FTP_UPGRADE,
    PT_UPDATE_ERROR_NET_DOWNLOAD,  //������������ʧ��
    PT_UPDATE_ERROR_NET_UPGRADE,   //��������ʧ��
} PT_UPDATE_ERR_STATUS_E;

#define PT_MAX_LIST 16
typedef struct
{
    sint32 max_value;
    sint32 min_value;
} PT_RANGE_S; //��Χ�޶��ṹ��

typedef struct
{
    uint32 count;//��ǰ�б�����
    sint32 list[PT_MAX_LIST];
} PT_LIST_S; //�б��޶��ṹ��

// ��̨����
typedef enum
{
    PTZ_UNKNOWN = 0,
    PTZ_RV800,
    PTZ_TOTA120,
    PTZ_S1601,
    PTZ_CLT_168,
    PTZ_TD_500,
    PTZ_V1200,
    PTZ_ZION,
    PTZ_ANT,
    PTZ_CBC,
    PTZ_CS850A = 10,
    PTZ_CONCORD,
    PTZ_HD600,
    PTZ_SAMSUNG,
    PTZ_YAAN,
    PTZ_PIH,        //����
    PTZ_MG_CS160,
    PTZ_WISDOM,
    PTZ_PHILIPS,
    PTZ_NEOCAM,
    PTZ_ZHCD = 20,
    PTZ_DONGTIAN,
    PTZ_EMERSON,
    PTZ_TOTA160,
    PTZ_BANGTVD,
    PTZ_BANGTVP,
    PTZ_SANSHAND,
    PTZ_SANSHANP,
    PTZ_LILIN1,
    PTZ_LILIN2,
    PTZ_PDDR = 30,  //PLECOD����
    PTZ_PPDR,       //PLECOP����
    PTZ_TOYANI,
    PTZ_HY,
    PTZ_TEOP,
    PTZ_PELCOD1,
    PTZ_PELCOD2,
    PTZ_PELCOD3,
    PTZ_PELCOD4,
    PTZ_PELCOD5,
    PTZ_PELCOD7 = 40,
    PTZ_PELCOD_ZH,
    PTZ_PELCOD_5F,
    PTZ_PELCOD,
    PTZ_PELCO_D,
    PTZ_PELCOP1,
    PTZ_PELCOP2,
    PTZ_PELCOP3,
    PTZ_PELCOP5,
    PTZ_PELCOP6,
    PTZ_PELCOP7 = 50,
    PTZ_PELCO_P,
} PT_PROTOCOL_E;

typedef struct
{
    uint32 type;        //��̨���� ��ϸ��PT_PROTOCOL_E
    uint32 addr;        //��̨��ַ��
    uint32 speed;       //��̨�ٶ�
    uint32 uart_type;   //�������RS-485����0, sdi-485 1
} PT_PTZPARAM_S, *PPT_PTZPARAM_S;

typedef enum
{
    PT_UART_RS485 = 0,
    PT_UART_RS232 = 1,
    PT_UART_SDI485 = 2,
    PT_UART_RS422 = 3,
} PT_UART_TYPE_E;

typedef enum
{
    PT_DEF_FB_NULL = 0,
    PT_DEF_FB0 = 1,
    PT_DEF_FB1 = 2,
    PT_DEF_FB2 = 3,
    PT_DEF_FB3 = 4,
    PT_DEF_FB4 = 5,
    PT_DEF_FB5 = 6,
} PT_DEF_FB_E;

typedef struct
{
    uint32 host_addr;   //��ַ
    uint32 baudrate; 	//���ڲ����� (0-300,1-1200,2-2400,3-4800,4-9600,5-19200,6-38400,7-57600,8-115200)
    uint32 enable;      //�Ƿ�ʹ��-off,1-on
    uint32 func;        //0-no,1-ptz,2-keyboard,3-transparent uart
    uint32 databits;    //����λ(7,8)
    uint32 stopbits;    //ֹͣλ(1,2)
    uint32 parity;      //У��λ(0-NONE,1-ODD,2-EVEN,3-SPACE)
    uint16 flow_control;//����(0-��,1-Xon/Xoff,2-Ӳ��)
    uint16 rc_lock;     //Զ��ң��������ʹ��
    uint16 uart_mode;   // �������� 0 -- ��˫�� 1 -- ȫ˫��
    uint16 atm_protocol;//ATMЭ�飬��ʱ����
} PT_UARTPARAM_S, *PPT_UARTPARAM_S;

typedef enum
{
    SYSNETAPIPTZ_CMD_GETLIST = CMDNO(0, COMP_PTZ), // ��ȡЭ���б�,����:ָ��PPTZ_LIST��ָ��,����ֵ��ʾЭ�����
    SYSNETAPIPTZ_CMD_GETSPEED,      // ��ȡ��Ӧͨ����̨�����ٶ�param(int *)
    SYSNETAPIPTZ_CMD_SETSPEED,      // ������Ӧͨ����̨�����ٶ�param(int)
    SYSNETAPIPTZ_CMD_GETADDR,       // ��ȡ��Ӧͨ����̨���Ƶ�ַ,param(int *)
    SYSNETAPIPTZ_CMD_SETADDR,       // ������Ӧͨ����̨���Ƶ�ַ,param(int)
    SYSNETAPIPTZ_CMD_GETPROTOCOL,   // ��ȡ��Ӧͨ����̨Э������,param(int *)
    SYSNETAPIPTZ_CMD_SETPROTOCOL,   // ������Ӧͨ����̨Э������,param(int)
    SYSNETAPIPTZ_CMD_GET_PATTERN,   // ��ȡ��Ӧͨ����̨Э���Ƿ�֧�ֹ켣Ѳ��,param(int)

    SYSNETAPIPTZ_CMD_STOP = CMDNO(PTZ_CMD_START, COMP_PTZ),
    SYSNETAPIPTZ_CMD_UP,            // ��
    SYSNETAPIPTZ_CMD_DOWN,          // ��
    SYSNETAPIPTZ_CMD_LEFT,          // ��
    SYSNETAPIPTZ_CMD_RIGHT,         // ��
    SYSNETAPIPTZ_CMD_FOCUS_INC,     /* �۽�+ */
    SYSNETAPIPTZ_CMD_FOCUS_DEC,     /* �۽�- */
    SYSNETAPIPTZ_CMD_IRIS_INC,      /* ��Ȧ+ */
    SYSNETAPIPTZ_CMD_IRIS_DEC,      /* ��Ȧ- */
    SYSNETAPIPTZ_CMD_ZOOM_INC,      /* ����+ */
    SYSNETAPIPTZ_CMD_ZOOM_DEC,      /* ����- */
    SYSNETAPIPTZ_CMD_F1,            // ����
    SYSNETAPIPTZ_CMD_F1_1,
    SYSNETAPIPTZ_CMD_F2,            // ����
    SYSNETAPIPTZ_CMD_F2_1,
    SYSNETAPIPTZ_CMD_AUTO,          // �Զ�
    SYSNETAPIPTZ_CMD_AUTO_1,
    SYSNETAPIPTZ_CMD_PRESET_SET,    // Ԥ��
    SYSNETAPIPTZ_CMD_PRESET_GET,    // ����
    SYSNETAPIPTZ_CMD_SETUP,
    SYSNETAPIPTZ_CMD_ENTER,
    SYSNETAPIPTZ_CMD_PAGEUP,
    SYSNETAPIPTZ_CMD_PAGEDOWN,
    SYSNETAPIPTZ_CMD_BRUSH,         // ��ˢ
    SYSNETAPIPTZ_CMD_LEFT_UP,       //24����
    SYSNETAPIPTZ_CMD_LEFT_DOWN,     //25����
    SYSNETAPIPTZ_CMD_RIGHT_UP,      //26����
    SYSNETAPIPTZ_CMD_RIGHT_DOWN,    //27����
    SYSNETAPIPTZ_CMD_PRESET_CLR,    //28Ԥ�õ����
    SYSNETAPIPTZ_CMD_SET_PATTERN_START, //29�켣Ѳ��--���ÿ�ʼ
    SYSNETAPIPTZ_CMD_SET_PATTERN_END,   //30�켣Ѳ��--���ý���
    SYSNETAPIPTZ_CMD_SET_PATTERN_RUN,   //31�켣Ѳ��--����

} PT_PTZCMD_E;

typedef struct
{
    int cmd;            //��̨�����������PT_PTZCMD_E
    int param;          //���ò���
} PT_PTZCTRL_S, *PPT_PTZCTRL_S;

typedef enum
{
    PT_SCENE_CUSTOM = 0,
    PT_SCENE_STANDARD = 1,
    PT_SCENE_INDOOR = 2,
    PT_SCENE_OUTDOOR = 3,
    PT_SCENE_STONG_LIGHT = 4,
    PT_SCENE_WEAK_LIGHT = 5,
} PT_SYSCOLOR_SCENE_E;

/* ��ֵΪ0xFFFF ʱ��ʾ���֧�� */
typedef struct
{
    uint32 bright;      /* ����0-100 */
    uint32 contrast;    /* �Աȶ�0-100 */
    uint32 saturation;  /* ���Ͷ�0-100 */
    uint32 hue;         /* ɫ��0-100 */
    uint32 sharp;       /* ��� 0-100 */
} PT_SYSCOLOR_S, *PPT_SYSCOLOR_S;

typedef struct
{
    uint16 year ;       //�� ��2009
    uint16 month ;      //�� 1-12
    uint8   day ;       //�� 1-31
    sint8   hour ;      //Сʱ 0-23
    sint8   minute ;    //���� 0-59
    sint8   second ;    //�� 0-59
    sint32 msec;        //����
} PT_TIME_S, *PPT_TIME_S;

typedef enum
{
    PT_WEEK_SUN,        //������
    PT_WEEK_MON,        //����һ
    PT_WEEK_TUES,       //���ڶ�
    PT_WEEK_WED,        //������
    PT_WEEK_THUR,       //������
    PT_WEEK_FRI,        //������
    PT_WEEK_SAT,        //������
} PT_WEEK_E;

typedef struct
{
    PT_TIME_S time;
    PT_WEEK_E week;     //����   ��ȡʱ����
} PT_SYSTIME_S, *PPT_SYSTIME_S;

typedef enum
{
    PT_TYPE_PRI = 0,        //������
    PT_TYPE_SEC = 1,        //������
} PT_STREAMTYPE_E;

typedef enum
{
    PT_DISABLE = 0,         //�ر�
    PT_ENABLE = 1,          //����
} PT_ENABLE_E;
typedef struct
{
    PT_STREAMTYPE_E  type;
    PT_ENABLE_E          enable;
} PT_ENCSTATUS_S, *PPT_ENCSTATUS_S;

typedef struct
{
    PT_STREAMTYPE_E  type;
    sint32 user_handle;
} PT_VIDEOTYPE_S;
typedef enum
{
    PT_AUTOMODE,        //����Ӧ
    PT_HALFMODE_10M,    //10M��˫��
    PT_FULLMODE_10M,    //10Mȫ˫��
    PT_HALFMODE_100M,   //100M��˫��
    PT_FULLMODE_100M ,  //100Mȫ˫��
    PT_FULLMODE_1000M   //1000Mȫ˫��
} PT_NETMODE_E;
typedef struct
{
    uint32 enable;
    uint32 ip_addr;
    uint16 port[MAX_CH]; // �ಥ�˿�
} PT_MULTICAST_S, *PPT_MULTICAST_S;
typedef struct
{
    sint8 type[MAX_STRING]; //�������� �����������
    uint32 ip ;             //dvr ip��ַ
    uint32 mask ;           //dvr��������
    uint32 gateway ;        //����
    uint32 dns[2];          //DNS
    uint8 mac_addr[8];      //�����ַ
    PT_NETMODE_E phy_mode;  //��������ģʽ
    uint32 dhcp_enable;     //dhcpʹ��
    uint32 ip_reserve;      //����ip��ַ
    uint32 mask_reserve;    //������������
    uint32 gateway_reserve; //��������
    uint32 dns_reserve[2];  // ����DNS
    sint32 dhcpflag;        //��ȡ��ʱ����Ч:0-��ʾ��ip���ֶ����õ�ip, 1-��ʾ��ip���Զ���ȡ��ip, 2-��ʾ��ip�Ǳ���ip
    uint16 cmdport;             //��������˿�
    uint16 httpport;            //����http�˿�
    uint16 rtmpport;            //����rtmp�˿�
    PT_MULTICAST_S  multicast;  //�ಥ����
} PT_IPCONFIG_S, *PPT_IPCONFIG_S;

/* ������ģʽ */
typedef enum
{
    PT_ETH_BOND_BALANCE_RR = 0,       /* ���ؾ��� */
    PT_ETH_BOND_ACTIVE_BACKUP = 1,    /* ���Ӹ��� */
    PT_ETH_BOND_ADDR_SETTING = 2,     /* ��ַ�趨 */
} PT_ETH_BOND_MODE_E;

typedef struct
{
    PT_LIST_S speed_mode;   /* ����˫��ģʽ */
    PT_LIST_S bond_mode;    /* ��ģʽ PT_ETH_BOND_MODE_E */
}PT_ETH_LIST_S;

typedef struct
{
    sint8 host_name[MAX_STRING];
    PT_IPCONFIG_S  ip_config;
    uint16 cmdport;             //��������˿�---�˲����Ѿ���Ч���Ѿ���������PT_IPCONFIG_S�ṹ������֪Ϥ
    uint16 httpport;            //����http�˿�---�˲����Ѿ���Ч���Ѿ���������PT_IPCONFIG_S�ṹ������֪Ϥ
    PT_MULTICAST_S  multicast;  //�ಥ����    ---�˲����Ѿ���Ч���Ѿ���������PT_IPCONFIG_S�ṹ������֪Ϥ
    PT_IPCONFIG_S  sec_ip_config;
    sint32 muti_work_mode;//˫��������ģʽ          ��PT_ETH_BOND_MODE_E                ����������˫����ģʽ����Ч
    sint32 muti_def_route;//˫����Ĭ��·�ɡ�0---������·��eth0�� 1---������eth1·��  ����������˫����ģʽ����Ч
    sint32 muti_pri_net_card;//˫����Ĭ������������0---�������� 1---������  �������� ����������˫����ģʽ����Ч
} PT_NETCONFIG_S, *PPT_NETCONFIG_S;
typedef struct
{
    char    ftp_server[PT_MAX_ADDR_STR];//ftp��������ַ
    char    ftp_usr[MAX_STRING];        //ftp�û���
    char    ftp_pwd[MAX_STRING];        //ftp����
    char    ftp_path[PT_MAX_ADDR_STR];  //ftp�ļ�·��
    sint32  ftp_port;                   //ftp�˿ں�
    uint32  reserve;
} PT_FTPCONFIG_S, *PPT_FTPCONFIG_S;

typedef enum
{
    PT_AUTO_DISABLE,    //���Զ�����
    PT_AUTO_ENABLE,     //�Զ�����
} PT_AUTOENABLE_E;

typedef enum
{
    PT_SAVEPWD_DISABLE, //����������
    PT_SAVEPWD_ENABLE,  //��������
} PT_SAVEPWD_E;

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

typedef enum
{
    PT_WIRELESS_PPPOE, //PPPOE
    PT_WIRELESS_3G, //3g
} PT_WIRELESS_E;


typedef enum
{
    PT_NETSTD_TYPE_ETH0 = 0,        //���߲���
    PT_NETSTD_TYPE_WCDMA ,          // ��ͨWCDMA
    PT_NETSTD_TYPE_CDMA2000_EVDO,   //����CDMA2000-EVDO
    PT_NETSTD_TYPE_CDMA1x,          //����CDMA1x
    PT_NETSTD_TYPE_TD_CDMA,         //�ƶ�TD-CDMA
    PT_NETSTD_TYPE_GPRS,
} PT_NETSTD_TYPE_E;

typedef struct
{
    uint8 user[MAX_STRING];         // �û���
    uint8 pwd[MAX_STRING];          // ����
    PT_AUTOENABLE_E auto_connect;   // �Ƿ��Զ�����
    PT_SAVEPWD_E save_pwd;          //�Ƿ񱣴�����
    PT_SUCCESS_E status;            // �Ƿ�����ɹ�
    PT_CONNECT_E command;
    PT_IPCONFIG_S ip_config;
    PT_WIRELESS_E wireless_en;      //����ʹ��
    PT_NETSTD_TYPE_E   net_std;     //������ʽ
    uint8   apn[MAX_STRING];		// APN
    uint8	dailnum[MAX_STRING];	// ���ź���
} PT_PPPOECONFIG_S, *PPT_PPPOECONFIG_S;

typedef struct
{
    sint32  index;                      //ddns����
    uint8   server[MAX_STRING];         // ��ǰ��������ַ
    uint8   user[MAX_STRING];           // �û���
    uint8   pwd[MAX_STRING];            // ����
    uint8   dn[MAX_DNS * MAX_STRING];   // �����ĵ�ַ ��֧�ַ������4��DNS����
    uint32  ip_addr;                    // ���������ص�IP��ַ
    PT_AUTOENABLE_E auto_connect;       // �Ƿ�Ϊ�Զ�����
    PT_SUCCESS_E    status;             // �Ƿ�����ɹ�
    PT_CONNECT_E    command;            // ���Ӷ���
    uint8   dn_set[PT_MAX_LINE];        // ��������(��Щ������������Ҫ�趨���������߶������ʱָ��һ��ʱ��)
    uint32  gui_get_flag;               //ֵΪ1����ʾֱ�ӽ���״̬����ȡ�Ķ��������ַ����dn_set�����GUI
    uint16  domain_default_flag;        // ����Ĭ�Ϸ�Ĭ�ϱ�־λ��0ΪĬ�ϣ�1Ϊ��Ĭ��
    uint16	iterm_num;
    uint8   list_iterm[12][MAX_STRING]; //֧�ַ������ĸ����Լ��������б���ǰ����������
} PT_DDNSCONFIG_S, *PPT_DDNSCONFIG_S;

typedef enum
{
    PT_WEPTYPE_UNABLE,  //unable
    PT_WEPTYPE_64B,     //64bit
    PT_WEPTYPE_128B,    //128bit
    PT_WEPTYPE_152B,    //152bit
} PT_WEPTYPE_E, *PPT_WEPTYPE_E;

typedef struct
{
    char wlan_enable;           //0-δ���ã�1-������
    char ssid_connected;        //��wlan_enable==1ʱ��Ч��0-û��������ap��1-��ʾ�Ѿ�������ap
    uint8 ssid[PT_MAX_SSID_LEN];//SSID��
    uint8 wirelessIP[16];       //����ip
    uint32 wpa_set;             //wpa��ȫ��������
    PT_WEPTYPE_E wep_type;
    uint8 psw[PT_MAX_PSK_LEN];
} PT_WIFICONFIG_S, *PPT_WIFICONFIG_S;

typedef struct
{
    char wlan_enable;//0-δ���ã�1-������
    char ssid_connected;//��wlan_enable==1ʱ��Ч��0-û��������ap��1-��ʾ�Ѿ�������ap
    char ssid[PT_MAX_SSID_LEN];// �Ѿ����ϵ�ap��ssid��ssid��󳤶���32�����Ͻ�������33���ֽڣ�
} PT_WLAN_CFG_S, *PPT_PWLAN_CFG_S;

typedef struct
{
    char savepsk;
    //��ȡʱ��==0����ʾ��ssidδ��������룬ssid��psk��auth_type����Ч��
    // 			     ==1����ʾ��������������Ч
    //����ʱ��==0����ʾɾ��ssid ��������
    // 			    ==1����ʾ�������ò�����,���֮ǰ���������������
    // 			    ==2����ʾ��������
    char psk_status;  // 0-��ʾ����δ���棬1-��ʾ�����ѱ���
    char ssid[PT_MAX_SSID_LEN];// ssid��󳤶���32�����Ͻ�������33���ֽڣ�
    char psk[PT_MAX_PSK_LEN];// ������󳤶���64�����Ͻ�������65���ֽڣ�
    uint32 auth_type;//0-����ʽ����������,1-wep��2-wpa/wpa2-psk
} PT_WIFI_CFG_S, *PPT_PWIFI_CFG_S;

typedef struct
{
    int signallevel;        //�ź�ǿ��
    uint32 auth_type;       //��ȫ��:0-����ʽ����������,1-wep��2-wpa/wpa2-psk
    char ssid[MAX_STRING];  // ssid��󳤶���32�����Ͻ�������33���ֽ�
    char connect_state;     //����״̬��SSID_CONNECT_STA_E
    char psk_state;         //����״̬��0-δ���ã�1-�ѱ���
    char wps_state;         //WPS״̬��0-�����ã�1-����
    int connection_speed;   //�����ٶ�
    uint8 bssid[8];
} PT_WIFIAP_CFG, *PPT_WIFIAP_CFG;

typedef struct
{
    int ssid_num;           //��������ap����
    PT_WIFIAP_CFG aplist[PT_MAX_WIFIAP_NUM]; //��������ap�б����10��
} PT_WIFIAP_LIST_S, *PPT_WIFIAP_LIST_S;

/*******************UPNP***************/
typedef struct
{
    char lanip[20];
    char wanip[20];
} PT_ROUTE_S, *PPT_ROUTE_S;

typedef struct
{

    char server_name[MAX_STRING];		//ת���˿�����
    uint8  port_status;			//�˿�ӳ��״̬״̬
    uint8  port_enable;	        //�����˿�ӳ���Ƿ�Ҫ��ӵ�·������ʹ�ܿ���
    uint8   reserve[2];
    uint16 dvr_port;		//DVR�˿�
    uint16 rount_port;		//·�����˿�
    uint32 protocol;		//Э��
} PT_UPNP_PORT_S, *PPT_UPNP_PORT_S;

typedef struct
{
    uint16          upnp_en;
    uint16          pat_count;				 //ת���˿ڸ���
    uint32  iaddr;             /*DVR IP*/
    uint32  gatewayip;         /*DVR ��ǰ����IP*/
    PT_ROUTE_S routerip;		   /*����·������ַ*/
    PT_UPNP_PORT_S pat_info[MAX_PAT];	     //ת���˿���Ϣ
} PT_UPNP_CONN_S, *PPT_UPNP_CONN_S;

/********************************************/


typedef struct
{
    uint32 minver; //�׶ΰ汾��
    uint32 secver; //�Ӱ汾��
    uint32 majver; //���汾��
    PT_TIME_S time;//ʱ��
    COMPID comp_type;
} PT_VERSION_S, *PPT_VERSION_S;

typedef enum
{
    PT_AUSTREAM_DISABLE,    //��Ƶ��
    PT_AUSTREAM_ENABLE,     //������
} PT_AUSTREAMADD_E;

typedef enum
{
    PT_QCIF     = 0, //QCIF,176��144
    PT_QQ960H   = 1,
    PT_QVGA     = 2, //QVGA,240��320
    PT_Q960H    = 3,
    PT_CIF      = 4, //CIF, 352*288/360*288
    PT_DCIF     = 5, //DCIF,704*288
    PT_HD1      = 6, //HD1,704*288/720*288
    PT_VGA      = 7, //VGA,640X480
    PT_FD1      = 8, //FD1,705*576
    PT_SD       = 9, //SD,
    PT_HD       = 10, //HD
    PT_960H     = 11,//960*576
    PT_720P     = 12,//1280��720
    PT_1080P    = 13,//1920��1080
    PT_960P     = 14,   /* 1280*960 130w��������������볣�÷ֱ���4:3 */
    PT_1024P    = 15,   /* 1280*1024 */
    PT_768x432  = 16,   /* 768*432 */
    PT_640x368  = 17,   /* 640*368 */
    PT_320x192  = 18,   /* 320*192 */
    PT_1920x960  = 19,   /* 1920*960 */
    PT_720x576  = 20,   /* 720*576 */
    PT_NONE     = 0xFF, /*���ĳЩIPC�������ֱ��ʹ��˴���*/
    PT_MAX_RES     // PT_MAX
} PT_RESOLUTION_E;


/*vga HDMI�ֱ���*/
typedef enum
{
    PT_VGA_MOD_800x600      = 0,
    PT_VGA_MOD_1024x768     = 1,
    PT_VGA_MOD_1280x1024    = 2,
    PT_VGA_MOD_1440x900     = 3,
    PT_VGA_MOD_1280x720P    = 4,
    PT_VGA_MOD_1920x1080I   = 5,
    PT_VGA_MOD_1920x1080P   = 6 ,
    PT_VGA_MOD_3840x2160    = 7,
} PT_VGA_MOD_E;

typedef enum
{
    PT_RATE_30K    = 0,
    PT_RATE_45K    = 45,
    PT_RATE_60K    = 60,
    PT_RATE_75K    = 75,
    PT_RATE_90K    = 90,
    PT_RATE_100K   = 100,
    PT_RATE_128K   = 128,
    PT_RATE_256K   = 256,
    PT_RATE_512K   = 512,
    PT_RATE_768K   = 768,
    PT_RATE_1M     = 1024,
    PT_RATE_1536K  = 1536,
    PT_RATE_2M     = 2048,
    PT_RATE_3M     = 3072,
    PT_RATE_4M     = 4096,
    PT_RATE_5M     = 5120,
    PT_RATE_6M     = 6144,
    PT_RATE_7M     = 7168,
    PT_RATE_8M     = 8192,
    PT_RATE_9M     = 9216,
    PT_RATE_10M    = 10240,
    PT_RATE_11M    = 11264,
    PT_RATE_12M    = 12288,
} PT_RATE_MOD_E;

/*������ƵԴ����*/
typedef enum
{
    PT_VIDEO_FORMAT_NO = 0,
    PT_VIDEO_1080P60 = 1,   //��������Դ,1920*1080 60֡.
    PT_VIDEO_1080P50,
    PT_VIDEO_1080P30,
    PT_VIDEO_1080P25,
    PT_VIDEO_1080P24,
    PT_VIDEO_720P60,
    PT_VIDEO_720P50,
    PT_VIDEO_720P30,
    PT_VIDEO_720P25,
    PT_VIDEO_720P24,
    PT_VIDEO_PAL,
    PT_VIDEO_NTSC,
    PT_VIDEO_EXT = 13,
    PT_VIDEO_960H,          //ģ������Դ,960*576
    PT_VIDEO_D1,            //720*576
    PT_VIDEO_NONE = 0xFF, /*���ĳЩIPC�������ֱ��ʹ��˴���*/
    PT_VIDEO_MAX,
} PT_VIDEO_SRC_TYPE_E;

typedef enum
{
    PT_VIDEO_NOSIGNAL,
    PT_VIDEO_OK,
    PT_VIDEO_NOTSUPPORT,
    PT_NO_REFRESH,
} PT_VIDEO_STATUS;

typedef enum
{
    PT_MODE_SMART = 0,  /*����ģʽ*/
    PT_MODE_COMMON,     /*��ͨģʽ*/
    PT_MODE_HIK,        /*�ຣ��ģʽ*/
    PT_MODE_ZW,         /*����άģʽ*/
    PT_MODE_YCX,        /*���д���ģʽ*/
} PT_IPC_MANAGE_MODE_E;


typedef struct
{
    sint16 width;
    sint16 height;
} PT_RES_S;

typedef struct
{
    PT_LIST_S vga_mod;              //������ֱ��� (��ͨ���޹�) PT_VGA_MOD_E
    PT_LIST_S vga_sub_mod;          //sub����ֱ��� (��ͨ���޹�) PT_VGA_MOD_E
    /*INVALID*/
    PT_LIST_S resolution;           //������Ƶ�ֱ��� PT_RESOLUTION_E
    PT_LIST_S net_resolution;       //������Ƶ�ֱ��� PT_RESOLUTION_E
    PT_LIST_S snapshot_resolution;  //��ͼ������ PT_RESOLUTION_E
    /*INVALID*/
    PT_LIST_S phy_mode;             //����ģʽ
} PT_COMMON_RANGE_S; //ͨ�÷�Χ

#if 1 /*INVALID*/
typedef struct
{
    uint32 resolution;              //PT_RESOLUTION_E �������

    PT_RANGE_S frame_rate;          //����֡��
    PT_RANGE_S bit_rate;            //��������
    PT_LIST_S  bit_rate_list;       //���������б� ƽ̨�����Լ�ѡ��ѡ��bit_rate��bit_rate_list����һ��

    PT_RANGE_S net_frame_rate;      //������֡��
    PT_RANGE_S net_bit_rate;        //����������
    PT_LIST_S  net_bit_rate_list;   //�����������б� ƽ̨�����Լ�ѡ��ѡ��net_bit_rate��net_bit_rate_list����һ��
} PT_ENCPARAM_RANGE_S; //����Ƶ�ֱ�����صı�������ķ�Χ.
#endif

typedef struct
{
    int src_type;       //PT_VIDEO_SRC_TYPE_E
    int src_status;     //PT_VIDEO_STATUS
} PT_VIDEO_SRC_S;

typedef enum
{
    PT_BITRATE_CHANGE,   //������
    PT_BITRATE_NOCHANGE, //������
} PT_BITRATETYPE_E;

typedef enum
{
    PT_VQUALITY_BEST = 0, //���
    PT_VQUALITY_BETTER, //�ϸ�
    PT_VQUALITY_GOOD,   //��
    PT_VQUALITY_NORMAL, //��
    PT_VQUALITY_BAD,    //��
    PT_VQUALITY_WORSE   //���
} PT_VQUALITY_E;

typedef struct
{
    PT_AUSTREAMADD_E byStreamType;  //��Ƶ������
    PT_RES_S byResolution;          //��Ƶ�ֱ���
    PT_BITRATETYPE_E byBitrateType; //��������
    sint32 byPicQuality;            //ͼ������
    uint32 dwVideoBitrate;          //��Ƶ���� ʵ������
    uint16 dwVideoFrameRate;        //֡�� PAL 2-30 N 2-30
    uint16 quant;                   //�������� 1-31
    uint32 encode;                  //�����������ͣ�h264\h265,PT_VIDEO_ENCODING_E
} PT_ENCCONFIG_S, *PPT_ENCCONFIG_S;

typedef enum
{
    SYENETAPI_REC_TYPE_UNKNOW = 0,
    SYENETAPI_REC_TYPE_MANUAL = 1,      //�ֶ�¼��
    SYENETAPI_REC_TYPE_SCHEDULE = 2,    //��ʱ¼��
    SYENETAPI_REC_TYPE_MOTION = 4,      //�ƶ�¼��
    SYENETAPI_REC_TYPE_ALARM = 8,       //����¼��
    SYENETAPI_REC_TYPE_CARD = 9,        //����¼��
    SYENETAPI_PIC_TYPE_MANUAL = 0x11,   //ͼƬ-�ֶ�¼��
    SYENETAPI_PIC_TYPE_SCHEDULE = 0x12, //ͼƬ-��ʱ¼��
    SYENETAPI_PIC_TYPE_MOTION = 0x14,   //ͼƬ-�ƶ�¼��
    SYENETAPI_PIC_TYPE_ALARM = 0x18,    //ͼƬ-����¼��
    SYENETAPI_PIC_TYPE_ALLPIC = 0x1f,   //ͼƬ-����
    SYENETAPI_PIC_TYPE_IP_INVALID =0xe0, //IP��Ч
    SYENETAPI_PIC_TYPE_STREAM_CLOSE =0xe1, //�������ر�
    SYENETAPI_REC_TYPE_ALL = 0xff       //����
} PT_RECTYPE_E;

typedef struct
{
    PT_STREAMTYPE_E streamtype; //Ҫ���û��߻�ȡ����������
    PT_RECTYPE_E       rectype; //¼������
    PT_ENCCONFIG_S enc;         //�������
} PT_STREAMENCPARAM_S, *PPT_STREAMENCPARAM_S;

typedef struct
{
    uint16 left; //��ʼ�������
    uint16 top; //��ʼ��������
    uint16 width; //���
    uint16 height; //�߶�
} PT_AREA_S, *PPT_AREA_S;

typedef enum
{
    MASK_DISABLE = 0,   /* ���� */
    MASK_ALL,       /* ȫ���� */
    MASK_REAL,      /* ʵʱ���� */
    MASK_RECORD,    /* ¼������ */
} PT_MASK_TYPE_E;

typedef struct
{
    PT_MASK_TYPE_E enable;  //��Ƶ�������Σ�
    sint32 num; 	//�������
    PT_AREA_S area[MAX_MASK];   /* ������(10000*10000)������ϵ���� */
} PT_MASKPARAM_S, *PPT_MASKPARAM_S;

typedef struct
{
    sint32 enable;              //��Ƶ��������0-���ã�1����(�ر��ע�����Ƿ���ʾ)
    sint32 num;                 //�������
    PT_AREA_S area[MAX_MASK];
    sint32 type;                //�ر��ע��������
    sint32 value;               //�ر��ע����ֵ
} PT_SPECIALAREA_S, *PPT_SPECIALAREA_S;

typedef struct
{
    uint32 starth;  //��ʼСʱ
    uint32 startm;  //��ʼ����
    uint32 endh;    //����Сʱ
    uint32 endm;    //��������
} PT_TMPERIOD_S, *PPT_TMPERIOD_S;

typedef enum
{
    PT_STATUS_OFF,  //NO/OFF
    PT_STATUS_ON,   //YES/ON
} PT_STATUS_E;

typedef struct
{
    PT_STATUS_E bselect;                //0-no 1-yes
    PT_TMPERIOD_S period[MAX_PERIOD];   //����ʱ��
    uint32      seg_enable;             //ȱʡֵΪ0������ȡ��������period����ֵΪ1ʱ����segment�ṹ�塣
    uint32      segment[3];             // ��λ�ָ�24Сʱ���ܹ�96λ��ÿλ��ʱ��Ϊ15����
} PT_TMITEM_S, *PPT_TMITEM_S;

typedef struct
{
    uint32 bstatus : 1;         // �Ƿ����ã�0-���ã�1-����
    uint32 force_enable : 1;    // ǿ�ƿ��أ�0-�رգ�1-�򿪣�ǿ�ƿ��ش�ʱ��ȫ�첼����ʱ������ò������ã�
    uint32 reserve : 30;        // ����λ
    PT_TMITEM_S item[8];        // 0-7: everyday, monday...sunday
} PT_TMSCHEDULE_S, *PPT_TMSCHEDULE_S;

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

typedef struct
{
    PT_TMSCHEDULE_S schedule;   //����ʱ������
    uint16 almdelay;            //������ʱʱ�� ȱʡΪ0
    uint16 almoutsec;           //�������ʱ��
    //PT_ENABLE_E forcestatus;  //ǿ�Ʊ������״̬
} PT_LINKOUTPARAM_S, *PPT_LINKOUTPARAM_S;

typedef struct
{
    uint16 recordtime;          //��������¼��ʱ��
    uint16 prerecordtime;       //Ԥ¼ʱ��
    //PT_TMSCHEDULE_S schedule; //����ʱ������
} PT_LINKRECPARAM_S, *PPT_LINKRECPARAM_S;

typedef struct
{
    uint32 stay_time;           //ͣ��ʱ��
    uint8 alm2preset[MAX_CH];   //������Ԥ�õ�
    //PT_TMSCHEDULE_S schedule; //����ʱ������
} PT_LINKPRESETPARAM_S, *PPT_LINKPRESETPARAM_S;

typedef struct
{
    uint32 snaptimes;           //ץ�Ĵ���
    uint32 snaptimeval;         //ץ�ļ�� ����Ϊ��λ
    //PT_TMSCHEDULE_S schedule; //����ʱ������
} PT_LINKSNAPPARAM_S, *PPT_LINKSNAPPARAM_S;

typedef struct
{
    uint32 almout[MAX_AMOUT];   //����������� ������̽ͷ�����0-��������1-����
    uint32 record[MAX_CH];      //����¼�� ������¼��ͨ����0-��������1-����
    uint32 presetenable[MAX_CH];//������Ԥ�õ�
    uint32 snap[MAX_CH];        //����ץ��
    /*INVALID*/
    uint32 local_record[MAX_CH];      //��������ͨ��¼�� ������¼��ͨ����0-��������1-����
    uint32 ipc_record[MAX_CH];      //����IPCͨ��¼�� ������¼��ͨ����0-��������1-����
    uint32 local_presetenable[MAX_CH];//����ͨ��������Ԥ�õ�
    uint32 ipc_presetenable[MAX_CH];//IPCͨ��������Ԥ�õ�
    uint32 local_snap[MAX_CH];        //����ͨ������ץ��
    uint32 ipc_snap[MAX_CH];        //IPCͨ������ץ��
    /*INVALID*/
} PT_ALMLINKPLAN_S, *PPT_ALMLINKPLAN_S;

//��������Ԥ�����ò���
typedef struct
{
    PT_LINKOUTPARAM_S  almout[MAX_AMOUT];
    PT_LINKRECPARAM_S   rec[MAX_CH];
    PT_LINKPRESETPARAM_S  preset[MAX_AM];       //����̽ͷ��������Ԥ�õ�
    PT_LINKPRESETPARAM_S  ipc_preset[MAX_CH];   //Զ��̽ͷ��������Ԥ�õ�
    PT_LINKPRESETPARAM_S  mv_preset[MAX_CH];    //�ƶ���������Ԥ�õ�
    PT_LINKSNAPPARAM_S   snap[MAX_CH];      
} PT_PLANCONFIG_S, *PPT_PLANCONFIG_S;

typedef struct
{
    PT_TMSCHEDULE_S schedule;       //����ʱ������
    PT_ALMLINKPLAN_S plan;          //��������Ԥ��
    uint16 enalmmax;                //�������ʵʱ����ʹ�ܣ���Ҫ���̽ͷ�������ƶ���ⱨ��
    uint8 almoutbuzzer;             //�����ͷ�����
    uint8 almoutaudio;              //�����������ʹ��
    //chanaged by ypxiao 1112
    uint8 mail_enable;             //�����ʼ�ʹ��  0-�ر� 1-����
    uint8 alm_durative;             //����������־ 0-�ǳ���������1-��������     //added by ypxiao 1112
    uint8 motion_area_show_en;      //�ƶ���������Ƿ���ʾ
    uint8 motion_sen_show_en;       //�ƶ�����������Ƿ���ʾ
} PT_MOTIONRECPARAM_S, *PPT_MOTIONRECPARAM_S;

typedef struct
{
    uint32 sensitivity;             /* �ƶ���������� PT_SENSITIVITY_E*/
    uint32 block[18];               /* �ƶ���������������� 22*18���� */
} PT_IPCMOTIONRULES_S;

typedef struct
{
    sint32 col;
    sint32 row;
    uint32 blk_num;                 /* �ƶ������*/
    uint32 block[18];               /* �ƶ��������� 22*18���� */
} PT_IPCSMARTMOTION_S;

typedef struct
{
    PT_ALMLINKPLAN_S plan;          //��������Ԥ��
    uint16 reserve;                 //����
} PT_ATMCARDRECPARAM_S, *PPT_ATMCARDRECPARAM_S;

typedef struct
{
    uint8  almin_name[MAX_STRING];  //̽ͷ��
    uint16 enalmmax;                //�������ʵʱ����ʹ�ܣ���Ҫ���̽ͷ�������ƶ���ⱨ��
    uint8 almoutbuzzer;             //�����ͷ�����
    uint8 almoutaudio;              //�����������ʹ��
    PT_ALMTYPE_E almtype;           //̽ͷ���� 0-���� 1-����
    PT_TMSCHEDULE_S schedule;       //����ʱ������
    PT_ALMLINKPLAN_S plan;          //��������Ԥ��
    uint16 mail_enable;             //�����ʼ�ʹ��  0-�ر� 1-����
    uint16 almin_attr;              //̽ͷ����  0-���� 1-Զ��
} PT_ALARMINRECPARAM_S, *PPT_ALARMINRECPARAM_S;

typedef struct
{
    sint32 almtype;           //̽ͷ���� 0-���� 1-���� PT_ALMTYPE_E
    sint32 reserve[3];
} PT_IPCALARMINRECPARAM_S, *PPT_IPCALARMINRECPARAM_S;

typedef struct
{
    uint32            second : 6;   // ��: 0~59
    uint32            minute : 6;   // ��: 0~59
    uint32            hour : 5;     // ʱ: 0~23
    uint32            day : 5;      // ��: 1~31
    uint32            month : 4;    // ��: 1~12
    uint32            year : 6;     // ��: 2000~2063
} PT_MFSTIME_S, *PPT_MFSTIME_S;

typedef struct
{
    PT_MFSTIME_S  begin_time, end_time; //��ѯ��ʼʱ�䣬����ʱ��
    uint32 lengh;                       //��λ:�ֽ�
    uint8 ch;                           //ͨ����
    uint8 type;                         //¼������
#if 1
    uint8 dev_type;						//�豸����
    uint8 dev_num;						//�豸��
    uint8 use_stat;						//ʹ��״̬
#endif
} PT_RECSEGINFO_S, *PPT_RECSEGINFO_S;

typedef struct
{
    PT_TIME_S time_bg, time_ed;     //��ѯ��ʼʱ�䣬����ʱ��
    PT_RECTYPE_E type;              //¼������
    PT_RECSEGINFO_S * data;         //¼�����Ϣbuffer
    uint32 start;                   //��ȡ��ε���ʼ�ţ���0��ʼ��
    uint32 limit;                   //���ȡ��¼�����(buffer_length / sizeof(PLATFORM_Mfs_RecSeg_Info))
    uint32 total_num;               //�������������¼���������output��
    uint32 realmum;                 //ʵ�ʶ���¼��������output��
} PT_RECFILESEG_S, *PPT_RECFILESEG_S;

typedef struct
{
    sint32   channel;           //�ط�ͨ��
    PT_TIME_S time;             //��¼������
    PT_RECTYPE_E type;          //��¼������
    uint32 openrec_handle;      //��¼����(output)
} PT_SEGSTREAMREADOPEN_S, *PPT_SEGSTREAMREADOPEN_S;

typedef enum
{
    //�����������
    SYSNETAPI_VOD_PLAY = 0,
    SYSNETAPI_VOD_PAUSE,
    SYSNETAPI_VOD_STOP,
    SYSNETAPI_VOD_FASTFORWARD,
    SYSNETAPI_VOD_SLOWFORWARD,
    SYSNETAPI_VOD_FASTBACKWARD,
    SYSNETAPI_VOD_SLOWBACKWARD, // 6
    SYSNETAPI_VOD_FRAMEFORWARD,
    SYSNETAPI_VOD_FRAMEBACKWARD,//֡��
    SYSNETAPI_VOD_SEEK,
    SYSNETAPI_VOD_TIMEJUMP,     //����ָ��ʱ��
    SYSNETAPI_VOD_SPLITSET,     //���������������Ч 10
    SYSNETAPI_VOD_PIC_SPLITSET, //���������������Ч 10
    SYSNETAIP_VOD_PIC_PBTIME,   //ͼƬ�Զ�����ʱ���� 11
    SYSNETAPI_VOD_PIC_FASTBACKWARD,//
    SYSNETAPI_VOD_PBPLAY_SPLITSET,
    SYSNETAPI_VOD_CHANNELJUMP,  //����ָ��ͨ��
} PT_PLAYBACKSTATUS_E;

typedef enum
{
    //��������
    SYSNETAPI_SPEED_2X,         //���ʱΪ2����� ,����ʱΪ1/2����
    SYSNETAPI_SPEED_4X,         //
    SYSNETAPI_SPEED_8X,
    SYSNETAPI_SPEED_16X,
} PT_PLAYBACKSPEED_E;

typedef union
{
    uint32  longtime;
    PT_MFSTIME_S fieldtime;
} PT_MFSTIME_U;

typedef struct
{
    PT_PLAYBACKSTATUS_E  status;
    uint32    param;//��statusΪSYSNETAPI_VOD_SEEKʱparamΪ0-99    ��statusΪSYSNETAPI_VOD_TIMEJUMPʱ��paramΪPT_MFSTIME_U�е�longtime����
} PT_PLAYBACKPARA_S, *PPT_PLAYBACKPARA_S;

typedef enum
{
    //��������
    SYSNETAPI_READ_NORMAL = 0,
    SYSNETAPI_READ_FORWARD = 0x10,      // �ؼ�֡��������Ϊ����ʹ�ã�
    SYSNETAPI_READ_FORWARD_1X = 0x11,   // �ؼ�֡����
    SYSNETAPI_READ_FORWARD_2X = 0x12,   // 2������ؼ�֡����
    SYSNETAPI_READ_FORWARD_3X = 0x13,   // 3��
    SYSNETAPI_READ_FORWARD_4X = 0x14,   // 4��
    SYSNETAPI_READ_FORWARD_5X = 0x15,   // 5��
    SYSNETAPI_READ_BACKWARD = 0x20,     // �ؼ�֡�ˣ�����Ϊ����ʹ�ã�
    SYSNETAPI_READ_BACKWARD_1X = 0x21,  // �ؼ�֡��
    SYSNETAPI_READ_BACKWARD_2X = 0x22,  // 2������ؼ�֡��
    SYSNETAPI_READ_BACKWARD_3X = 0x23,  // 3��
    SYSNETAPI_READ_BACKWARD_4X = 0x24,  // 4��
    SYSNETAPI_READ_BACKWARD_5X = 0x25,  // 5��
    SYSNETAPI_READ_SEEK = 0x40          // ��seek
} PT_READSPEED_E;

typedef struct
{
    uint32 openrec_handle;      //��¼����
    PT_READSPEED_E speed;       //�������ٶ�
    uint32 size;                //��ȡ���ݴ�Сbuffer����
    PT_TIME_S time;             //��ǰ֡���ڹؼ�֡������ʱ��(output)
    uint32 len;                 //ʵ�ʶ�������������(output)
    sint8 * data;               //��Ŷ������ݻ�������ַ(output)
} PT_ENCODESTREAMREAD_S, *PPT_ENCODESTREAMREAD_S;

typedef struct
{
    uint32 openrec_handle;      //��¼����
    PT_READSPEED_E speed;       //�������ٶ�
    uint32 size;                //��ȡ���ݴ�Сbuffer����
    uint32 percent;             //��speed == SYSNETAPI_READ_SEEK , �ô�ֵ���嶨λ�ٷֱ�(0~99)
    uint32 len;                 //ʵ�ʶ�������������(output)
    sint8 * data;               //��Ŷ������ݻ�������ַ(output)
} PT_ENCODESTREAMREADSEG_S, *PPT_ENCODESTREAMREADSEG_S;

typedef enum
{
    PT_SHOW_DISABLE,            //����ʾ
    PT_SHOW_ENABLE,             //��ʾ
} PT_SHOW_E;

typedef enum
{
    PT_DATE_YMD1 = 0,           // YYYY/MM/DD
    PT_DATE_MDY1 = 1,           // MM/DD/YYYY
    PT_DATE_DMY1 = 2,           // DD/MM/YYYY
    PT_DATE_YMD2 = 3,           // YYYY.MM.DD
    PT_DATE_MDY2 = 4,           // MM.DD.YYYY
    PT_DATE_DMY2 = 5,           // DD.MM.YYYY
    PT_DATE_YMD3 = 6,           // YYYY-MM-DD
    PT_DATE_MDY3 = 7,           // MM-DD-YYYY
    PT_DATE_DMY3 = 8,           // DD-MM-YYYY
} PT_DATEFORMAT_E;

typedef enum
{
    PT_TIME_24HOUR,         // 24Сʱ��
    PT_TIME_12HOUR,         // 12Сʱ��
} PT_TIMEFORMAT_E;

typedef struct
{
    sint32 date_format;     /* PT_DATEFORMAT_E */
    sint32 time_format;     /* PT_TIMEFORMAT_E */
} PT_TIME_CFG_S;

typedef enum
{
    CUSTOM      = 0,    /*����*/
    UPPERLEFT   = 1,    
    UPPERRIGHT  = 2,
    LOWERLEFT   = 3,
    LOWERRIGHT  = 4,
} PT_OSD_POSTYPE_E;

typedef struct
{
    PT_SHOW_E en_title;     // 1-��ʾOSD��0-����ʾ
    uint8 title[PT_MAX_STRING_EXT];// OSD��
    sint32 pos_type;        //OSDλ�����ͣ�PT_OSD_POSTYPE_E
    PT_AREA_S pos_title;    //OSD����������Ϣ��pos_type = 0 ʱ��Ч
} PT_OSDATTRI_S, *PPT_OSDATTRI_S;

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

typedef struct
{
    PT_OSDATTRI_S osd[MAX_OSD_NUM];

    uint16  osdnum;          //osd��Ŀ
    uint16  osdattrib;      //OSD����0-��͸�� 1 -͸��
    uint16  format_date;         //���ڸ�ʽ ���������OSD��ò�������,PT_DATEFORMAT_E
    uint16  format_time;         //ʱ����ʾ��ʽ ���������OSD��ò�������,PT_TIMEFORMAT_E
    PT_SHOW_E en_week;          //�Ƿ���ʾ���� ���������OSD��ò�������
    uint8   en_src_type;        /* �Ƿ���ʾ��ƵԴ��Ϣ,��960H,1080p�� */
    uint8   en_atm_type;		/* �Ƿ�ATM���ͣ�ATM���� osd[1].title ����Ϊ ͨ����+'&'+����*/
    uint8   refresh_osd;        /* �Ƿ�ˢ��osd 0-Ĭ��ˢ��  1-��ˢ��*/
    uint8   reserve[1];         /* ����λ */
    PT_SHOW_E en_logo_watermark;			// �Ƿ�ʹ��OSDǰ����logoˮӡͼƬ
    PT_AREA_S pos_logo_watermark;    		//logoˮӡͼƬ��������Ϣ
} PT_OSDPARAM_S, *PPT_OSDPARAM_S;

typedef struct
{
    uint16 enalmmax;            // 1-senor or move alarm to chang one real window
    uint8 almoutbuzzer;         //�����ͷ�����
    uint8 almoutaudio;          //�����������ʹ��
    PT_ENABLE_E enable;         // ��Ƶ��ʧ����ʹ��
    PT_ALMLINKPLAN_S plan;      //��������Ԥ��
    uint32 mail_enable;         //�����ʼ�ʹ��  0-�ر� 1-����
} PT_VLOSTLINKPLAN_S, *PPT_VLOSTLINKPLAN_S;
typedef struct
{
    uint32 ch_host;             //������ӦΨһ���� input
    PT_TIME_S date;             //��ѯ��־ʱ��input
    uint32 totalnum;            //��ѯָ��ʱ���ڵ���־����output
} PT_QUERYLOGNUM_S, *PPT_QUERYLOGNUM_S;

typedef enum
{
    PT_PRI_OPERATE, // ����
    PT_PRI_ALARM,   // ����
    PT_PRI_ERROR,   // �쳣
    PT_PRI_MAX,
} PT_PRITYPE_E;
typedef enum
{
    PT_OP_PTZ,              // ��̨����   0
    PT_OP_PLAYBACK,         // �ط�1
    PT_OP_UPGRADE,          // ����2
    PT_OP_TALKBACK_START,   // �Խ���ʼ3
    PT_OP_TALKBACK_STOP,    // �Խ�����4
    PT_OP_GETSTATUS,        // ��ȡ״̬5
    PT_OP_SETCONFIG,        // ����6
    PT_OP_GETCONFIG,        // ��ȡ����7
    PT_OP_TRANSCOM_OPEN,    // ����͸��ͨ��8
    PT_OP_TRANSCOM_CLOSE,   // �Ͽ�͸��ͨ��9
    PT_OP_RECORD_START,     // ����¼��10
    PT_OP_RECORD_STOP,      // ֹͣ¼��11
    PT_OP_LOGIN,            // ��½12
    PT_OP_LOGOUT,           // ע��13
    PT_OP_SETTIME,          // ����ϵͳʱ��14
    PT_OP_SHUTDOWN,         // �ػ�15
    PT_OP_REBOOT,           // ����16
    PT_OP_POWERON,          // ����17
    PT_OP_FORMAT_DISK,      // ��ʽ��Ӳ��18
    PT_OP_DEFAULT,          // �ָ�ȱʡ19
    PT_OP_CLR_ALARM,        // �������20
    PT_OP_BACKUP,           // ����21
    PT_OP_STREAM_OPEN,      // ��������Ԥ��22
    PT_OP_STREAM_CLOSE,     // �ر�����Ԥ��23
    PT_OP_ARMING,           // ����
    PT_OP_DISARMING,        // ����
    PT_OP_MAILUPLOAD_SUCCE, // �ʼ��ϴ��ɹ�
    PT_OP_MAILUPLOAD_ERROR, // �ʼ��ϴ�ʧ��
    PT_OP_FILE_LOCK,        // �����ļ�
    PT_OP_FILE_UNLOCK,      // �����ļ�
    PT_OP_FILE_DELETE,      // ɾ���ļ�
    PT_OP_SNAPSHOT_START,   // ��ʼ��ͼ  31
    PT_OP_SNAPSHOT_STOP,    // ��ʼ��ͼ  32
    PT_OP_TIME_BACKUP,      //��ʱ����
    PT_OP_TIME_REBOOT,      //��ʱ����
    PT_OP_ALARM_MANUAL,     //  �ֶ�����

    PT_OP_PLAYBACK_CUT,        // �طż���
    PT_OP_RAID_CREATE,         /* RAID�̴��� */
    PT_OP_RAID_DEL,            /* RAID��ɾ�� */
    PT_OP_REBUILD,			  /* RAID���ؽ� */
    PT_OP_HD_PLUGIN,           /* ���̲��� 40*/
    PT_OP_HD_PLUGOUT,           /* ���̰γ� 41*/
    PT_OP_NTP_SETSUC,           /* NTPУʱ�ɹ� 42*/
    PT_OP_IPC_SEARCH,			/* IPC���� */
    PT_OP_IPC_ADD,           /* IPC��� */
    PT_OP_IPC_EDIT,		    /* IPC�༭ */
    PT_OP_IPC_DEL,		        /* IPCɾ�� */
    PT_OP_IPC_STREAM_OPEN,     /* ipc������ */
    PT_OP_IPC_STREAM_CLOSE,    /* ipc���Ͽ� */
    PT_OP_BAOXIU,        //��� �û�������Ϣ�ϴ� 41
    PT_OP_WEIXIU,		//���  ά����Ϣ�ϴ� 42
    PT_OP_WEIBAO,		//���  ά����Ϣ�ϴ�43
    PT_OP_TESTPIC_UPLOAD,			//���  ����ͼƬ�ϴ�44
    PT_OP_BAOYANGPIC_UPLOAD,		//���  ����ͼƬ�ϴ�45
    PT_OP_YANSHOUPIC_UPLOAD,		//���  ����ͼƬ�ϴ�46
    PT_OP_ALMLINKPIC_UPLOAD,		//���  ��������ͼƬ�ϴ�47
    PT_OP_DAILYPIC_UPLOAD,			//���	�ճ�ͼƬ�ϴ�  48
    PT_OP_TYPE_MAX,         //24
} PT_OPERATETYPE_E;

typedef enum
{
    PT_ALM_SENSORIN,        // ��������
    PT_ALM_SENSOROUT,       // �������
    PT_ALM_MOTION_START,    // �ƶ���⿪ʼ
    PT_ALM_MOTION_STOP,     // �ƶ�������
    PT_ALM_CARDID_START,    // ����¼��ʼ
    PT_ALM_CARDID_STOP,     // ����¼�����
    PT_ALM_PTZ_OPERATE,     // ��̨����
    PT_ALM_MAIL_UPLOAD,     // �ʼ��ϴ�

    PT_ALM_ATMI_FACE_BLOCK,         //�����ڵ�
    PT_ALM_ATMI_FACE_UNUSUAL,       //�����쳣

    PT_ALM_ATMI_PANEL_BLOCK,        //����ڵ�
    PT_ALM_ATMI_PANEL_PASTE,        //����
    PT_ALM_ATMI_PANEL_KEYBOARD,     //װ�ټ���
    PT_ALM_ATMI_PANEL_KEYMASK,      //�ƻ����������
    PT_ALM_ATMI_PANEL_CARDREADER,   //�ƻ�������
    PT_ALM_ATMI_PANEL_TMIEOUT,      //��ʱ����

    PT_ALM_ATMI_MONEY_UNUSUAL,      //�ӳ����쳣,�����˴���ӳ���

    PT_ALM_ATMI_ENVI_GATHER,        //���˾ۼ�
    PT_ALM_ATMI_ENVI_MANYPEOPLEINREGION,    //Υ��ȡ��
    PT_ALM_ATMI_ENVI_LINGERING,             //��Ա�ǻ�
    PT_ALM_ATMI_ENVI_LIEDOWN,               //��Ա����
    PT_ALM_ATMI_ENVI_FORBIDREGION,          //�Ƿ����뾯����
    PT_ALM_ATMI_ENVI_LEAVEOBJECT,           //��Ʒ����
    PT_ALM_RAID_DEGRADE,                   /* ���� */
    PT_ALM_TYPE_MAX,
} PT_ALARMMTYPE_E;

typedef enum
{
    PT_ERR_VIDEOLOST,       // ��Ƶ��ʧ
    PT_ERR_HD_ERROR,        // ���̴���
    PT_ERR_HD_FULL,         // ������
    PT_ERR_LOGIN_FAIL,      // ��½ʧ��
    PT_ERR_FIFO_ERROR,      // �������
    PT_ERR_TEMP_HI,         // �¶ȹ���
    PT_ERR_HD_PFILE_INDEX,  // ��������������
    PT_ERR_HD_DEV_FATAL,    // �����豸��������
    PT_ERR_VIDEO_COVER,     // ��Ƶ�ڵ�
    PT_ERR_HD_RW_SLOW,     /* �����ٶ��� */
    PT_ERR_HD_LINK_ERR,  /* �������Ӵ���*/
    PT_ERR_HD_IDX_ERR, /*  �������ļ��쳣*/
    PT_ERR_HD_IDX_ADX_ERR, /*���������쳣 */
    PT_ERR_HD_LOG_ERR, /* ��־�ļ��쳣 */
    PT_ERR_TYPE_MAX,
} PT_ERRORTYPE_E;

typedef enum
{
    PT_PAR_START,           // ������ʼ
    PT_PAR_COMMON,          // ͨ������
    PT_PAR_MANUAL,          // �ֶ�¼��
    PT_PAR_TIME,            // ��ʱ¼��
    PT_PAR_MOTION,          // �ƶ�¼��
    PT_PAR_SENSOR,          // ̽ͷ����
    PT_PAR_CHCONFIG,        // ͨ������
    PT_PAR_NTP,             // NTP����
    PT_PAR_NETWORK,         // ��������
    PT_PAR_PPPOE,           // PPPOE����
    PT_PAR_DDNS,            // DDNS����
    PT_PAR_ALARM_SERV,      // ����������
    PT_PAR_CMS_SERV,        // CMS������
    PT_PAR_UART,            // ��������
    PT_PAR_PTZ,             // ��̨����
    PT_PAR_ACCOUNT,         // �˻�����
    PT_PAR_OSD,             // OSD����
    PT_PAR_POLL,            // ��ѵ����
    PT_PAR_VENC,            // �������
    PT_PAR_CARDID_REC,      // ����¼��
    PT_PAR_ALARM_LINKAGE,   // ��������
    PT_PAR_VMODE_MODIFY,    // ��ʽ�޸�
    PT_PAR_SNAPSHOT_MANUAL, // �ֶ���ͼ����
    PT_PAR_SNAPSHOT_TIME, // ��ʱ��ͼ����
    PT_PAR_SNAPSHOT_MOTION, // �ƶ���ͼ����
    PT_PAR_SNAPSHOT_ALARM, // ������ͼ����
    PT_PAR_HDD_GROUP, // Ӳ�̷���
    PT_PAR_REC_GROUP, // ¼�����
    PT_PAR_COMPLEX, // ����ͨ������
    PT_PAR_ADVANCE, // �洢�߼�����
    PT_PAR_EMAIL_SET,       // �ʼ�����
    PT_PAR_INPUT,           // ����Դ����
    PT_PAR_REBUILD_START,     /* ��ʼ�ؽ� */
    PT_PAR_REBUILD_DONE,        /* �ؽ���� */
    PT_PAR_ESATA_MODIFY,
    PT_PAR_TYPE_MAX,
} PT_PARAMTYPE_E;

typedef struct
{
    PT_MFSTIME_S time;  // ��¼��־ʱ��
    uint8 pri_type;     // ������
    uint8 sec_type;     // ������
    uint8 param;        // ��������
    uint8 channel;      // ͨ����
    uint32 host;        // 0-���� ���� �CԶ��IP��0xc0a80006
    uint8 user[17];     // �û���
    uint8 hard_driver;  // Ӳ�̺�
    uint8 sensor_in;    // ��������
    uint8 sensor_out;   // �������
    uint8 reserve[32];  // ����
} PT_LOGINFO_S, *PPT_LOGINFO_S;

typedef struct
{
    PT_MFSTIME_S time;  // ��¼��־ʱ��
    uint16 pri_type;     // ������
    uint16 sec_type;     // ������
    uint8 segconf[8];     //MFS_SEGCONF_S segconf;      /* segconf */
    sint16 channel;
    uint8 rev_key[24];          /* �����ؼ��� */
    uint8 area_flag[PT_MAX_INTEL_BLOCK_NUM];
    uint8 ref_reserve[36];          /* ����λ */
} PT_INTEL_LOGINFO_S, *PPT_INTEL_LOGINFO_S;     /*��չ��־ר�ã�����Щ����λ���������չ 128�ֽ�*/

typedef enum
{
    PT_DEVTYPE_NULL,           /* Null device */
    PT_DEVTYPE_IDE,            /* IDE hard or SATA hard disk */
    PT_DEVTYPE_RAM,            /* RAM disk */
    PT_DEVTYPE_FLASH,          /* Flash memory */
    PT_DEVTYPE_SD,             /* SD Card */
    PT_DEVTYPE_USB,            /* USB host device */
    PT_DEVTYPE_CDDVD,          /* CDDVD Rom */
    PT_DEVTYPE_ESATA,          /* ESATA device */
    PT_DEVTYPE_NETWORK,        /* network device */
    PT_DEVTYPE_MAX
} PT_DEVTYPE_E;

typedef struct
{
    uint32 ch_host;     //������ӦΨһ���� input
    PT_TIME_S date;     //��ѯ��־ʱ��input
    uint16 start;       //��ʼ
    uint16 limit;       //��Ҫ��ȡ��־������(info�Ĵ�С /sizeof(PT_LOGINFO_S)) input
    uint32 realnum;     //������ʵ����־��  (output)
    uint32 total_num;   //
    sint16  pri_type;   // ������
    sint16  sec_type;   // ������
    sint16  dev_no;     // �豸���
    sint16  dev_type;   // �豸���� ,��PT_DEVTYPE_E input
    PT_LOGINFO_S * info; //��־������Ϣ(output)
} PT_QUERYLOGINFO_S, *PPT_QUERYLOGINFO_S;

typedef enum
{
    PT_RECOVERMODE_MANU,
    PT_RECOVERMODE_AUTO,
} PT_RECOVERMODE_E;
typedef struct
{
    uint32 ch_host;     //������ӦΨһ���� input
    uint32 covermode;	//¼�񸲸Ƿ�ʽ 1-�Զ���0-�ֶ�
    uint32 reserve; 	/* ����λ */
} PT_RECCOVERMODE_S, *PPT_RECCOVERMODE_S;

/*typedef enum
{
    PT_DEV_NORMAL,      //����
    PT_DEV_DISK_ERROR,  //���̴���
    PT_DEV_FS_FAILED    //�ļ�ϵͳ����
}PT_DEVSTATUS_E;*/

typedef enum
{
    PT_DEVSTAT_NORMAL   = 0x00, // �豸��������״̬
    PT_DEVSTAT_STANDBY  = 0x01, // �豸���ڴ���״̬(��PT_DEVSTAT_NORMAL����������Ӳ��)
    PT_DEVSTAT_SLEEP    = 0x02, // �豸����˯��״̬(��PT_DEVSTAT_NORMAL��������������Ӳ��,ֻ��������дӲ��ʱ��ȥ����)----��ʱδʹ�������ʽ
    PT_DEVSTAT_ERROR    = 0x03, // �豸���ڴ���״̬
} PT_DEVSTATUS_E;

typedef enum
{
    PT_DEV_RAID_NORMAL,     // raid ����
    PT_DEV_RAID_DEGRED,     // raid ����
    PT_DEV_RAID_REBUILDING, // raid �ؽ�
    PT_DEV_RAID_BROKEN,     // raid ��
    PT_DEV_RAID_NO_RAID,    // raid û�н���
    PT_DEV_RAID_UNKOWN      // NO USE STAUS NOW
} PT_RAIDSTATUS_E;

typedef enum
{
    PT_SYSCOLOR_PAL = 0, //PAL��ʽ
    PT_SYSCOLOR_NTSC443 = 1,// NTSC4.43��ʽ
    PT_SYSCOLOR_NTSC358 = 2, // NTSC3.58��ʽ
} PT_SYSCOLOR_E;

typedef enum
{
    PT_STANDARD_H264,       //H.264
    PT_STANDARD_MPG4,       // MPG4
} PT_STANDARD_E;
typedef enum
{
    PT_LOGSIZ_32M,          // 32M
    PT_LOGSIZ_64M,          // 64M
    PT_LOGSIZ_128M,         // 128M
    PT_LOGSIZ_256M,         // 256M
    PT_LOGSIZ_512M,         // 512M
} PT_LOGSIZE_E;

typedef struct
{
    uint64 serial_num;      //�������к�
    uint8 rec_port;         //¼��ͨ����4;8;16
    uint8 rec_format;       //¼��ֱ���CIF;D1   PT_RESOLUTION_E
    uint8 rec_colorsystem;  //¼����ʽNtsc;Pal  PT_SYSCOLOR_E
    uint8 rec_standard;     //¼��ѹ���㷨H264;MPG4   PT_STANDARD_E
    PT_TIME_S sys_time;     //ϵͳ�����ʴ���ʱ��
    uint8 log_size;         // PT_LOGSIZE_E
    uint8 esata_enable;     //esata�豸λ��ʹ��  PT_ENABLE_E
    uint8 sys_hd_num;       //��ǰϵͳ֧�ֵ����Ӳ����
    uint8 reserve1[5];      //����
} PT_SYSINFO_S, *PPT_SYSINFO_S;
typedef enum
{
    PT_RAID_LEVEL_NULL,           /*δ���raidģʽ*/
    PT_RAID_LEVEL_0,              /*RAID 0*/
    PT_RAID_LEVEL_1,              /*RAID 1*/
    PT_RAID_LEVEL_2,              /*RAID 2*/
    PT_RAID_LEVEL_3,              /*RAID 3*/
    PT_RAID_LEVEL_4,              /*RAID 4*/
    PT_RAID_LEVEL_5,              /*RAID 5*/
    PT_RAID_LEVEL_10              /*RAID 10*/
} PT_Raid_Level_E;

#if 0
typedef struct
{
    uint8 Name[64];         //�ͺ�
    uint64 dev_capabilty;   //����
} PT_RAIDDEVINFO_S, *PPT_RAIDDEVINFO_S;
#endif

/* RAID ������Ϣ*/
typedef struct
{
    uint8 disktab[5];       /*����RAID ��Ա�Ĵ������*/
    uint8 count;            /*����RAID ���̸���*/
    uint8 level;            /*RAID���� */
    uint8 reserve[2];       /*����λ */
} PT_RAID_DISK_COUNT_S, *PPT_RAID_DISK_COUNT_S;

/* RAID�豸��Ϣ */
typedef struct
{
    char Name[32];    /* ���̵��ͺ� */
    uint64 dev_capabilty;               /* ���̵����� */
} PT_RAIDDEVINFO_S, *PPT_RAIDDEVINFO_S;

#if 0
typedef struct
{
    PT_RAIDSTATUS_E raid_status;        //�豸raid״̬  PT_RAIDSTATUS_E
    PT_Raid_Level_E raid_level;         //�豸raid ģʽ�ļ���
    uint32          raid_dev_table;     //ÿ��raid���ϵ��豸����λ�����
    PT_RAIDDEVINFO_S raid_dev_info[10]; //ÿ�����̵��ͺź�����
} PT_RAIDINFO_S, *PPT_RAIDINFO_S;
#endif

typedef struct
{
    uint8 stat;  /* ����״̬���������쳣 */
    uint8 reserve[3];

    uint8 raid_status;         /* �豸RAID״̬(MFS_RAIDSTAT_E) */
    uint8 raid_level;        /* �豸RAIDģʽ�ļ���(MFS_RAIDLEVEL_E) */
    uint8 raid_ctrlor;  /* ���������*/
    uint8 PortIndex;    /* ��Ӳ���ڿ����µ�λ��*/
    uint32 raid_dev_table;       /* ÿ��RAID���ϵ��豸����λ����� */
    PT_RAIDDEVINFO_S raid_dev_info[10];
} PT_RAIDINFO_S, *PPT_RAIDINFO_S;

typedef struct
{
    uint16        type;     // SATA������, GUI_SATA_PORT_TYPE_E
    uint16        state;    // SATA��״̬, GUI_SATA_PORT_STATE_E
} PT_DISK_LOAD_INFO_S, *PPT_DISK_LOAD_INFO_S;

/* Ӳ�̼���״̬ */
typedef struct
{
    uint32                port_num;       // �ӿ�����
    PT_DISK_LOAD_INFO_S   info[18];   // ����SATA�����ͼ�״̬
} PT_DISK_LOAD_DATA_S, *PPT_DISK_LOAD_DATA_S;

typedef struct
{
    uint16 dev_num;                 //�豸����ͨ����(���������й���)
    uint16 dev_type;                //�豸���ͣ�Ĭ��Ӳ�̣�,PT_DEVTYPE_E
    uint32 removable;               //�豸�Ƿ���ƶ����ã�Ĭ�Ϸ�
    uint32 backup;                  //�豸�Ƿ񱸷����ã�Ĭ�Ϸ�
    PT_DEVSTATUS_E dev_status;      //�豸״̬
    uint32 is_raid_dev;             //�豸�Ƿ�raid װ��(Ĭ�Ϸ�)
    PT_RAIDINFO_S raid_info;        //��ǰ�豸raidװ�õ���ϸ��Ϣ
    uint32 active;                  //�豸����״̬�����߻��߻��
    uint64 device_capabilty;        //�豸����(�ֽ�) ƽ̨���ݸ�����Ҫ������Ӧת��
    uint32  mfs_fs_active;          //�豸�ļ�ϵͳ�Ƿ��ʽ����0-δ��ʽ����1-�Ѹ�ʽ����2-Ԥ����
    uint64 mfs_capability;          //�ļ�ϵͳ������������ʽ����������ֽڣ�ƽ̨���ݸ�����Ҫ������Ӧת��
    uint64 mfs_free;                //��ǰ��������(�ֽ�)ƽ̨���ݸ�����Ҫ������Ӧת��
    PT_MFSDEV_HANDLE device_handle; //�豸�������
    PT_SYSINFO_S device_sys_info;   //������¼����ص�ϵͳ��Ϣ
} PT_DEVICEINFO_S, *PPT_DEVICEINFO_S;

typedef enum
{
    PT_COVERMODE_ALM,               //��������
    PT_COVERMODE_CYCLE,             //ѭ������
} PT_COVERMODE_E;

typedef struct
{
    PT_COVERMODE_E cycle_overlay;   //���̸��Ƿ�ʽ
    uint32 dev_table;               //�洢�豸�б���λ��ʾ
    uint32 usb_table;
    uint32 esata_table;
    uint32 cddvd_table;
    PT_DEVICEINFO_S disk_info[MAX_DEV_DISK];
    PT_DEVICEINFO_S usb_info[MAX_DEV_USB];
    PT_DEVICEINFO_S esata_info[MAX_DEV_ESATA];
    PT_DEVICEINFO_S cddvd_info[MAX_DEV_CDDVD];
} PT_DISKINFO_S, *PPT_DISKINFO_S;

typedef struct
{
    uint32 Preset[MAX_PRESET];      //ÿ��Ԥ�õ�1-255֮��
    PT_ENABLE_E PresetPoll;         //��Ԥ�õ���Ѳ������رձ�ʾ
    uint32 presettime;              //��Ԥ�õ���Ѳʱ��(1s~99s)
} PT_PRESETPOLL_S, *PPT_PRESETPOLL_S;

typedef enum
{
    PT_UPGRADE_READY = 0,   //׼������,��Ҫ����֪ͨ��ģ��
    PT_UPGRADE_START,       //��ʼ����
    PT_UPGRADE_PROGRESS,    //��������
    PT_UPGRADE_FINISH,      //�������
    PT_UPGRADE_ERROR,       //����ʧ��,�������ͼ�PT_UPDATE_ERR_STATUS_E
} PT_UPGRADE_STATUS_E;
typedef enum
{
    PT_SCAN_ROUTER_SUCC = 0,   //ɨ��·�����ɹ�
    PT_SCAN_ROUTER_FAILED, //ɨ��·����ʧ��
    PT_ADD_PORTMAP,       //��Ӷ˿�ӳ��
} PT_UPNP_STATUS_E;

typedef struct
{
    uint8 * data;       //�����ļ�����ָ��
    uint32 size;        //�����ļ���С
} PT_NETUPGRADE_S, *PPT_NETUPGRADE_S;

typedef enum
{
    OEM_TYPE_HB = 0,    //����
    OEM_TYPE_ZX,        //����
    OEM_TYPE_OEM,       //һ��OEM�ͻ�
    OEM_TYPE_NH,        //����ũ��
    OEM_TYPE_ZXLW,      //������ά
    OEM_TYPE_XJSX,      //�Ƚ���Ѷ
    OEM_TYPE_HYGJ,      //��ҵ����
    OEM_TYPE_XMBL,      //���ű���
    OEM_TYPE_WHWW,      //�人��ά
    OEM_TYPE_OSK,       //ŷ˼��
    OEM_TYPE_2D1,       //  2D1����汾      10
    OEM_TYPE_SHJC,      // �Ϻ����汾
    OEM_TYPE_YBDZ,      // �Ѱ����           80T  ����esata
    OEM_TYPE_SHGL,      // �Ϻ����ְ汾
    OEM_TYPE_ISPT,      // Innotec Solutions Pte Ltd
    OEM_TYPE_LILIN,     //��������
    OEM_TYPE_BJJT,      // ������ͼ
    OEM_TYPE_YTAF,      //Ӣ�ذ���
    OEM_TYPE_OEM_9_PIC, //9ͼ��OEM�ͻ�

    OEM_TYPE_PBS = 20,  //����ʿ���̼��
    OEM_TYPE_AUTOCOP,
    OEM_TYPE_SZSM,      //��������
    OEM_TYPE_SGPT,      //���ƽ̨
    OEM_TYPE_XM,	    //Ѷ��
    OEM_TYPE_QZRX,      //Ȫ������
} PT_OEM_TYPE_E;

typedef enum
{
    PT_DEVTYPE_7000T = 0,
    PT_DEVTYPE_8000T,
    PT_DEVTYPE_8200T,
    PT_DEVTYPE_8000ATM,
    PT_DEVTYPE_8600T,//8600T
    PT_DEVTYPE_6200T,
    PT_DEVTYPE_8004AH,
    PT_DEVTYPE_8004AI,
    PT_DEVTYPE_7000H,
    PT_DEVTYPE_7200H,
    PT_DEVTYPE_7000M = 12,
    PT_DEVTYPE_8000M,
    PT_DEVTYPE_8200M,
    PT_DEVTYPE_7000L,
    PT_DEVTYPE_2201TL = 16,
    PT_DEVTYPE_2600T,		    //ATM���ܷ�����
    PT_DEVTYPE_2600TB,	        //����ͳ�����ܷ�����
    PT_DEVTYPE_2600TC,	        //����ʶ�����ܷ�����
    PT_DEVTYPE_HB9304 = 170,    //����:��Ψһ��ʶһ�־������
    PT_DEVTYPE_HB9308,
    PT_DEVTYPE_HB9404,
    PT_DEVTYPE_HB9408,
    PT_DEVTYPE_HB7216XT3,
    PT_DEVTYPE_HB7016X3,
    PT_DEVTYPE_HB7208XT3,
} PT_DEV_TYPE_E;

typedef struct
{
    uint32 lang_ver;        //���԰汾  0�����ģ�1��Ӣ��
    uint32 logo_ver;        //logo�汾 0�����1������
    sint8  internal_ver[16]; //�ڲ��汾��
    PT_OEM_TYPE_E oem_type; //OEM ���ͣ��������ֲ�ͬ�Ŀͻ�,��OEM_TYPE_E
    uint32 dev_type;	    //�豸�ͺţ���PT_DEV_TYPE_E
    uint8  full_pb_flag;    //ȫ�طű�־
    uint8  reserve1;        //����1
    uint16 reserve2;        //����2
    sint8   oem_name[MAX_STRING];
} PT_KEYINFO_S, *PPT_KEYINFO_S;

typedef struct
{
    uint16 starttm;         //hour<<8|min
    uint16 endtm;           //hour<<8|min
    PT_SYSCOLOR_S param;    //��Ƶ����
    sint32 bselect;         //0:��׼ 1:���� 2:���� 3:���� 4:�Զ���1 5:�Զ���2
} PT_VPARAM_SEG_S, *PPT_VPARAM_SEG_S;

#if 0 //������Ƶ�������������ֶ�
typedef struct
{
    sint32 bselect;                     //reserve
    PT_VPARAM_SEG_S  videoparam[2];     //   0-ʱ���1  1-ʱ���2   ����
    PT_SYSCOLOR_S     defvparam;        //һ���ȥʱ���1��ʱ���2�����ʱ���
} PT_VIDEOPARAM_EXT_S, *PPT_VIDEOPARAM_EXT_S;
#else
typedef struct
{
    PT_VPARAM_SEG_S  videoparam[2];     //   0-ʱ���1  1-ʱ���2   ����
    PT_SYSCOLOR_S     defvparam;        //һ���ȥʱ���1��ʱ���2�����ʱ���
    sint32 bselect_def;                     //0:δ���� 1:��׼ 2:���� 3:���� 4:���� 5:�Զ���1 6:�Զ���2
} PT_VIDEOPARAM_EXT_S, *PPT_VIDEOPARAM_EXT_S;
#endif

typedef enum
{
    PT_AUTH_GUI2 = 0, //gui1.0ʱ��Ȩ��ģʽ(7000L,8000T��ʹ�õĺ�ɫ���gui)
    PT_AUTH_GUI3 = 1, //gui2.0Ȩ��ģʽ(7000L��ʹ�õĺ���gui)
    PT_AUTH_GUI4 = 2, //gui3.0Ȩ��ģʽ(9000��ʹ�õĺ���gui)
} PT_AUTHORITY_MODE_E;

typedef struct
{
    uint32 audioin_no;          	// ��Ƶ������
    uint32 videoin_no;          	// ��Ƶ������
    /*INVALID*/
    uint32 ipc_videoin_no;
    /*INVALID*/
    uint32 sensorin_no;         	// ����������
    uint32 sensorout_no;        	//���������
    uint32 spot_support;        	// SPOT���֧��
    uint32 cvbs_support;        	// CVBS֧��
    uint32 vga_support;         	// VGA֧��
    uint32 hdmi_support;        	//HDMI���֧��
    uint32 color_system;        	// 0-PAL, 1-NTSC
    PT_RESOLUTION_E max_res;                // �����Ƶ�ֱ���
    uint32 max_hd;                          // ���֧�ִ��̸���
    sint8  dev_machine_type[PT_MAX_STRING_EXT];	// DVR/NVR/HVR
    sint8  host_type[PT_MAX_STRING_EXT];    //��������  ��7004T
    uint32 modelno;                         //�������ͺ���7T04
    sint8  serialnumber[MAX_STRING];        //�������к�
    sint8  fbversion[MAX_STRING];           //ǰ���汾��
    sint8  pri_res_support[PT_MAX_RESNUM];  //0-��֧�� 1-֧��      ������֧�ֵķֱ���
    sint8  sec_res_support[PT_MAX_RESNUM];  //0-��֧�� 1-֧��     ������֧�ֵķֱ���
    uint32 lang_ver;            	//���԰汾  0�����ģ�1��Ӣ��
    uint32 logo_ver;            	//logo�汾 0�����1������

    uint8 mix_support;          	// ����֧��
    uint8 esata_support;        	// ESATA֧��
    uint8 raid_support;         	// RAID֧��
    uint8 videomatrix_support;  	// ��Ƶ����֧��

    uint8 vga_auto;             	// 0-�ֶ� 1-�Զ�
    uint8 vga_mode;             	// VGA�ֱ���, 0-800x600, 1-1024x768, 2-1280x1024, 3-1440*900, 4-1280*720P, 5-1920*1080I, 6-1920*1080P
    uint8 chip_no;              	// ��оƬ����
    uint8 output_dev;

    uint8 mcu_support;          	//7000L������Ч
    uint8 authority_mode;
    uint8 digital_audio_support;	//�Ƿ�֧��������Ƶ
    uint8 input_set_support;    	//�Ƿ�֧����������

    uint8 uart232_support;      	//�Ƿ�֧��uart232
    uint8 uart485_support;      	//�Ƿ�֧��uart485
    uint8 sdi485_support;       	//�Ƿ�֧��SDI485
    uint8 slowbackpb_support;   	//�Ƿ�֧�����˻ط�

    uint8 weekshow_support;     	//�Ƿ�֧��������ʾ
    uint8 videozoomin_pause_support;//�Ƿ�֧��
    uint8 wireless3g_support;     	//�Ƿ�֧��
    uint8 buzzer_support;         	//�Ƿ�֧�ַ�����

    uint8 max_esata_support;
    uint8 hdd_map_support;
    uint8 full485_support;       	/* ȫ˫��485�Ƿ�֧�� */
    uint8 pic_support;	         	/* �Ƿ�֧��ץͼ 0 --��֧��	1--֧�� */

    uint8 talk_support;	         	/* �Ƿ�֧�ֶԽ� 0 --��֧��	1--֧�� */
    uint8 zero_support;	         	/* �Ƿ�֧�ָ���ͨ�� 0 --��֧��	1--֧��*/
    uint8 alm_support;          	/*�Ƿ�֧�ֱ�������*/
    uint8 remoter_support;      	/* �Ƿ�֧��ң���� */

    uint8 wlan_support;         	/*�Ƿ�֧��wlan*/
    uint8 autodown_player;      	/* �Զ����ز�����*/
    uint8 pb_switch_ch;         	/* �طŽ����л�ͨ�� */
    uint8 player_support;       	/* ϵͳ�Դ������� */

    uint8 lcd_support;				/*�Ƿ�֧��LCD��Ļ���� 0--��֧�� 1--֧��*/
    uint8 shake_alarm_support; 		/*�Ƿ�֧���𶯱������� 0--��֧�� 1--֧��*/
    uint8 card_rec_support;  		/*�Ƿ�֧�ֿ���¼���� 0--��֧�� 1--֧��*/
    uint8 ch_enable_flag;       	/*ͨ��ʹ�ܽӿ� 1Ϊ�����޸�ͨ���� 0Ϊ�������޸�*/

    uint8 logo_watermask_support;	/*�Ƿ�֧��logoˮӡ*/
    uint8 full_playback_support; 	/*�Ƿ�֧��ȫ�ط�ѡ��*/
    uint8 multi_scene_support; 		/*�Ƿ�֧�ֶೡ������*/
    uint8 auto_fps_support;     	/*�Ƿ�֧���Զ�����֡��*/

    uint8 ipserver_upload_support; 	/*�Ƿ�֧��ipserver,upload�����ϴ����ܣ�0--��֧�֣�1--֧��*/
    uint8 net_upgrade_type;
    uint8 usb_upgrade_type;
    uint8 pback_zoomin_support; 	/*�Ƿ�֧�ֻط�����Ŵ�*/

    uint8 cd_burning_support;   	/*�Ƿ�֧��CD��¼*/
    uint8 NRT_support;          	/*�Ƿ�֧�ַ�ʵʱ*/
    uint8 video_in_adjust_support;  /*��Ƶ�������*/
    uint8 video_out_adjust_support; /*��Ƶ�������*/

    uint8 network_manage_support;         /* �Ƿ�֧���������� */
    uint8 conffile_import_export_support; /* �Ƿ�֧�������ļ����뵼�� */

    uint8 auto_format_support;   	/*�Ƿ�֧���Զ���ʽ��Ӳ��*/
    uint8 rec_packtime_support;		/*�Ƿ�֧��¼����ʱ���趨*/
    uint8 allch_timeshow_support;  	/*�Ƿ�����ͨ��ʵʱGUI������ʾʱ��*/
    uint8 logo_delay;              	/*logo��ʱ��ʾ 0-����  ����--��ʱ����*/

    uint8 update_logo_support;      //gui��Ҫ�ݴ�flag����Ӧ�Ƿ����logo����ʾ"��������..."
    uint8 shutdown_logo_support;    //gui��Ҫ�ݴ�flag����Ӧ�Ƿ����logo����ʾ"���ڹػ�..."
    uint8 preivew_split_support;    /*Ԥ����ʾ�Ƿ�֧�ַ���*/
    uint8 popmenu_split_support;    /*����Ҽ������Ƿ���ʾ������ʽѡ��*/

    uint8 preview_set_support;      /*�Ƿ�֧��Ԥ�����ã�0-��֧�֣�1-֧��  */
    uint8 coveralm_support;         /*�Ƿ�֧���ڵ�����*/
    uint8 avi_playback_support;     /*�Ƿ�֧��avi�������ݱ��ز���*/
    uint8 audioout_support;         /*�Ƿ�֧����Ƶ���*/
    uint8 poe_ctrl_support;         /* �Ƿ�֧��POE���ʿ��ƹ��� 0-��֧�֣�1-֧�� */
    uint8 intel_search_support;     /* �Ƿ�֧����������  1---֧�֣�0---��֧�� */
    uint8 poe_port_no;              /*֧��POE������*/
    uint8 pb_view_support;          /*�Ƿ�֧��С����Ԥ��*/
    uint32 system_id;               /*�������ID*/
    uint32 poe_power;               /*֧��POE����ܹ���*/
    uint32 total_bitrate;           /*֧��������,�����������,����150M��ʾΪ200M*/
    uint32 real_bitrate;            /*ʵ��֧�ֵ�������*/
    uint8 preview_policy_support;   /*֧��Ԥ������ѡ��*/
    uint8 muti_network_port_support;//������֧�� 
	uint8 multicast_support;		/* �Ƿ�֧�ֶಥ���� add by xcli 2015/11/25*/
    uint8 alarm_push_support;      /* �Ƿ�֧�ֱ������� 0 -- ��֧�֣�1 -- ֧�� */
} PT_IOCONFIG_S, *PPT_IOCONFIG_S;

/*************************************************************
* �ṹ����ܣ�logo������Ϣ����
*             ����Ԫ�غ���:0-uboot 1-״̬ 2-����Ƶ�ź� 3-ˮӡ 4-osd���Ͻ� 5-IE  6-9 ��չ
*************************************************************/
typedef struct
{
    uint8       file_path[MAX_FILENAME_LENTH];       //������·����ͼƬ����
    uint32      logo_support;         //�Ƿ�֧�֣�1-֧��, 0-��֧��
    uint32      file_format;          //bit:0-֧�ֵ�ͼƬ��ʽΪjpg ,1-֧�ֵ�ͼƬ��ʽΪbmp , 2-֧�ֵ�ͼƬ��ʽΪYUV
    uint32      max_width;            //ͼƬ����;
    uint32      max_height;           //ͼƬ����;
    uint32      min_width;            //ͼƬ��С��;
    uint32      min_height;           //ͼƬ��С��
    uint32      logo_bitdepth;        //ͼƬλ��ȣ�����λ��Ϊ8����7λΪ1��λ��Ϊ12����11λΪ1����������
    uint32      logo_size;            //ͼƬ��С;
    uint32      reserver;             //����;
} LOGO_IMG_INFO_S;

typedef struct
{
    uint8               key_devinfo_path[MAX_FILENAME_LENTH];   //key��devinfo.ini��·��
    sint8               host_type[PT_MAX_STRING_EXT];           //��������,�ӽű������л�ȡ��
    sint8               host_model[PT_MAX_STRING_EXT];           //�����������ƣ�������ʾ��
    LOGO_IMG_INFO_S     logo_img_info_arr[MAX_LOGO_NUM];
} PT_LOGO_LIMIT_INFO_S;

/*************************************************************
* �ṹ����ܣ�key �ļ�88 �ֽ�
*************************************************************/
typedef struct
{
    sint8   internal_ver[16]; //�ڲ��汾��
    sint8   external_ver7004t[16]; //�ⲿ�汾��7004t
    sint8   external_ver7008t[16]; //�ⲿ�汾��7008t
    sint8   external_ver7016t[16]; //�ⲿ�汾��7016t
    sint8   external_ver8004t[16]; //�ⲿ�汾��8004t
    sint8   external_ver8008t[16]; //�ⲿ�汾��8008t
    sint8   external_ver8016t[16]; //�ⲿ�汾��8016t
    sint8   external_ver700xt[16]; //�ⲿ�汾��700xt
    sint8   external_ver800xt[16]; //�ⲿ�汾��800xt
    uint32 lang_ver; //���԰汾  0�����ģ�1��Ӣ��
    uint32 logo_ver; //logo�汾 0�����1������2: OEM
    uint32  lang_maskl;                         //֧�ֵ����������32 λ����32������
    uint32  lang_maskh;                         //֧�ֵ����������32 λ��������32������
    uint16  oem_type;                   // OEM ���ͣ��������ֲ�ͬ�Ŀͻ�
    sint8   full_pb_flag;			//�Ƿ�֧��ȫ�ط� 0��֧��,1֧��
    sint8   reserve[21];
} PT_KEY_FIELD_S;
typedef enum
{
    PT_AUDIO_NONE       = 0,    /* ����Ƶ */
    PT_AUDIO_DIGITAL    = 1,    /* ֻ��������Ƶ */
    PT_AUDIO_ANALOG     = 2,    /* ֻ��ģ����Ƶ */
    PT_AUDIO_AAD        = 3,    /* both ANALOG and DIGITAL */
} PT_AUDIO_TYPE_E;

typedef enum
{
    PT_CAMERA_ANALOG_D1             = 0,    /* ֻ֧��ģ��D1 */
    PT_CAMERA_ANALOG_D1_960H        = 1,    /* ֧��ģ��D1��960H */
    PT_CAMERA_ANALOG_D1_ENCODE_CIF  = 2,    /* ����ģ��D1,��ֻ����CIF���� */
    PT_CAMERA_ANALOG_D1_ENCODE_6FPS = 3,    /* ����ģ��D1,��D1����ֻ��6֡ */

    PT_CAMERA_DIGITAL_1080P = 10,  /* ����Դ1080p */
    PT_CAMERA_DIGITAL_720P  = 11,
} PT_CAMERA_TYPE;

typedef struct
{
    uint32 audio_type;  /* PT_AUDIO_TYPE_E */
    uint32 camera_type; /* PT_CAMERA_TYPE */
} PT_CHANNEL_CONFIG_S;

typedef enum
{
    PT_DEV_UNDEF = -1,  /* δָ������豸 */
    PT_DEV_PRI  = 0,    /* ������豸 */
    PT_DEV_SEC  = 1,    /* ������豸 */
    PT_DEV_SPOT = 2,
    PT_DEV_ALL  = 0xFF, /* ��������豸 */
} PT_OUTPUT_DEV_E;      /* ��������豸 */

typedef struct
{
    uint8 auto_logout;      // �Զ�������0-���ã�����-���з�����                                 n
    uint8 gui_alpha;        // GUI͸����0~255                                                      n
    uint8 gui_lang;         // GUI����ѡ�0-���ġ�1-Ӣ�ġ�2-...                                   n
    uint8 alarm_delay;      // ��ʱ�������أ�0-���ã�����-������ʱʱ�䣬��λ����                 n
    uint8 mute;             // ������0-��������1-����                                               n
    uint8 mix;              // ������0-��������1-����                                                n
    uint8 r1;               /* �����ò��ṩ�������ʵ����� */
    uint8 alarm_snapshot;   // ����ץ��ͼƬ��0-���ã�1-����                               n
    uint8 vga_auto;         // 0-�ֶ� 1-�Զ�                                                    n
    uint8 gui_dflicker;     // 0-��ȥ�� 1-ȥ��                                               n
    uint8 talkback_type;    // �Խ��������ͣ�0-��˷磬1-ʰ����                                n
    uint8 reclight_enable;  // ¼��״ָ̬ʾ�����ÿ��أ�0-���ã�1-����                        n
    uint8 esata_enable;     // ESATAʹ�ܣ�0-�رգ�1-����                                     n
    uint8 softraid_enable1; // softraidʹ�ܣ�0-�رգ�1-����                               n
    uint16 audio_alarm;     // ����������0-���ã�1-���ã�����-��������ʱ�䣨��λ���룩          n
    uint8 reclight[MAX_CH]; // ¼��״ָ̬ʾ�ƣ���λ��ʾ��ͨ��״̬ ?                    n
    uint8 ao_mode;          // ��Ƶ���ģʽ, 0--BNC��� 1--MIC���                               n
    uint8 r2;
    uint8 set_guide;        // �Ƿ����ÿ�����0: ������ 1: ����                              n
    uint8 montion_beep;     // �ƶ�����������������0-���ã�1-����(�����û���Ч, һ��汾��ЧFirst Option)    n
    uint32 screen_saver;    // ��Ļ������0-���ã�����-���з�����                           n
    uint32 lang_mask;       // ֧�����ԣ���λ��ʾ
    uint8 set_output_dev;   // �����Ƿ���ʾ�豸��ʾ��. 1��ʾ 0����ʾ
    uint8 toolbar_enable;   //�Ƿ���ʾ�����ع�����0; ���أ�1-��ʾ
    uint8 without_login_mode; //�Ƿ������ģʽ0-�رգ�1-����
    uint8 ipc_manage_mode;  /*IPC����ģʽ PT_IPC_MANAGE_MODE_E*/
} PT_COMMON_CONFIG, *PPT_COMMON_CONFIG;

typedef enum
{
    PT_FRAMETYPE_P,     //P֡
    PT_FRAMETYPE_I,     //I֡
    PT_FRAMETYPE_AUDIO, //��Ƶ֡
} PT_FRAMETYPE_E;

typedef struct
{
    uint32 flag;        // MSHEAD_FLAG
    uint32 mshsize;     // ý��ͷ��Ϣ, MAX size=511
    uint32 msdsize;     // ý����������С, Max size=512K-1
    uint32 algorithm;   // ý������׼ISO_...
    PT_FRAMETYPE_E type;
    uint32 width;       //��Ϊ��Ƶ��ʾ��ȣ���λ16���أ��� ��Ϊ��Ƶ��ʾ����λ����λbit��
    uint32 height;      //��Ϊ��Ƶ��ʾ�߶ȣ���λ16���أ��� ��Ϊ��Ƶ��ʾ�����ʣ���λK��1000����
    uint32 serial_no;   // 0~511ѭ�����������ڱ�׼��֡�����жϣ��������֡��Ų�����ʱ����ʾ�м�֡��ʧ��
    uint32 time_msec;   //��ǰ֡ʱ�䣨��λ10���룩
    uint32 time_sec;    //��ǰ֡ʱ�䣨��λ�룩��ʾ��1970��1��1��0ʱ0��0�����������UTCʱ��������������
    uint32 fcount;      // ����������֡����
    PT_TIME_S time;     //֡����ʱ��
} PT_FRAMEHEADINFO_S, *PPT_FRAMEHEADINFO_S;



typedef struct
{
    PT_RECTYPE_E type;      //¼������
    PT_ENABLE_E status;     //¼��ʹ��
} PT_RECENABLE_S, *PPT_RECENABLE_S;


typedef struct pt_msg_buf
{
    long    type;           // ��Ϣ����,����>0
    int     buffer[4];      // ��Ϣ����
} PT_MSG_BUF, *PPT_MSG_BUF;

typedef enum
{
    NETKEY_CMD_GUI_LOGIN,       // ��¼
    NETKEY_CMD_GUI_DN,          //������                                      1
    NETKEY_CMD_GUI_STOP,        //STOP                                            2
    NETKEY_CMD_GUI_RETURN,      // ����                                    3
    NETKEY_CMD_GUI_ENTER,       //ȷ��                                       4
    NETKEY_CMD_GUI_UP,          //��                                                 5
    NETKEY_CMD_GUI_DOWN,        // ��                                            6
    NETKEY_CMD_GUI_LEFT,        //��                                              7
    NETKEY_CMD_GUI_RIGHT,       //��                                            8
    NETKEY_CMD_GUI_INFO,        //��Ϣ                                          9
    NETKEY_CMD_GUI_RECORD,      //¼��                                       10
    NETKEY_CMD_GUI_PLAYBACK,    //�ط�                                   11
    NETKEY_CMD_GUI_SETUP,       //����                                         12
    NETKEY_CMD_GUI_BACKUP,      //����                                       13
    NETKEY_CMD_GUI_ZOOM_INC,        //����ͷ��                                   14
    NETKEY_CMD_GUI_ZOOM_DEC,         //����ͷԶ                                    15
    NETKEY_CMD_GUI_FOCUS_INC,       // ����ͷ�佹��(ZOOM+)      16
    NETKEY_CMD_GUI_FOCUS_DEC,       // ����ͷ�佹Զ(ZOOM-)    17
    NETKEY_CMD_GUI_IRIS_INC,        // ����ͷ��Ȧ+                  18
    NETKEY_CMD_GUI_IRIS_DEC,        // ����ͷ��Ȧ-                   19
    NETKEY_CMD_GUI_PAGEUP,      //��ҳ                                       20
    NETKEY_CMD_GUI_PAGEDOWN,    // ��ҳ                                  21
    NETKEY_CMD_GUI_PRESET_SET,  //����ͷԤ��                  22
    NETKEY_CMD_GUI_PRESET_GET,  // ����ͷ����                23
    NETKEY_CMD_GUI_CN,          // ���� 70                                          24
    NETKEY_CMD_GUI_AUTO,        // �Զ�                                           25
    NETKEY_CMD_GUI_MUTE,        // ����                                          26
    NETKEY_CMD_GUI_F1,          //F1                                                       27
    NETKEY_CMD_GUI_F2,          //F2                                                       28
    NETKEY_CMD_GUI_REFRESH,     // REAL GUI USE 110                       29
    NETKEY_CMD_GUI_IGEFORMAT,   // �����ʽ 100                30
    NETKEY_CMD_GUI_IGESWITCH,   // �����ֻ�                      31
    NETKEY_CMD_GUI_SHUTDOWN,    // ��Դ,�ػ�����            32
    NETKEY_CMD_GUI_MOUSESTATUS, //  ���                           33
    NETKEY_CMD_GUI_VIDEOPARAM,  // ��Ƶ����                              34
    NETKEY_CMD_GUI_DIGIT,       // ����(����Ϊ0,1,2,3,4,5,6,7,8,9)          35
    NETKEY_CMD_GUI_CHAR,        // �ַ�(����ΪA,B,C,...,X,Y,Z,*,#)            36
    NETKEY_CMD_GUI_F1VGA2TV,    // vga������л�                       37
    NETKEY_CMD_GUI_STEP,        // ֡��                                            38
    NETKEY_CMD_GUI_PLAY,        // ����                                            39
    NETKEY_CMD_GUI_FASTF,       // ���                                          40
    NETKEY_CMD_GUI_FASTB,       // ����                                          41
    NETKEY_CMD_GUI_REFRESHTIME, // REAL GUI USE                      42
    NETKEY_CMD_GUI_PWDRST,      //���븴λ                              43
} PT_NETKEYCMD_E;

typedef enum
{
    // SERIAL SEND GUI
    SYSNETAPI_SERIAL_GUI_LOGIN = 100,   // ��¼512
    SYSNETAPI_SERIAL_GUI_RECORD,        // ¼��
    SYSNETAPI_SERIAL_GUI_PLAYBACK,      // �ط�
    SYSNETAPI_SERIAL_GUI_SETUP,         // ����
    SYSNETAPI_SERIAL_GUI_BACKUP,        // ����
    SYSNETAPI_SERIAL_GUI_DN,            // ������
    SYSNETAPI_SERIAL_GUI_CN,            // ����
    SYSNETAPI_SERIAL_GUI_DIGIT,         // ����(����Ϊ0,1,2,3,4,5,6,7,8,9)
    SYSNETAPI_SERIAL_GUI_CHAR,          // �ַ�(����ΪA,B,C,...,X,Y,Z,*,#)  520
    SYSNETAPI_SERIAL_GUI_BKSPACE,       // ɾ��
    SYSNETAPI_SERIAL_GUI_UP,            // ��                110
    SYSNETAPI_SERIAL_GUI_DOWN,          // ��
    SYSNETAPI_SERIAL_GUI_LEFT,          // ��
    SYSNETAPI_SERIAL_GUI_RIGHT,         // ��
    SYSNETAPI_SERIAL_GUI_PAGEUP,        // ��ҳ
    SYSNETAPI_SERIAL_GUI_PAGEDOWN,      // ��ҳ
    SYSNETAPI_SERIAL_GUI_RETURN,        // ����
    SYSNETAPI_SERIAL_GUI_ENTER,         // ȷ��
    SYSNETAPI_SERIAL_GUI_ZOOM_INC,      // ����ͷԶ��+
    SYSNETAPI_SERIAL_GUI_ZOOM_DEC,      // ����ͷԶ��-
    SYSNETAPI_SERIAL_GUI_FOCUS_INC,     // ����ͷ�佹+
    SYSNETAPI_SERIAL_GUI_FOCUS_DEC,     // ����ͷ�佹-
    SYSNETAPI_SERIAL_GUI_IRIS_INC,      // ����ͷ��Ȧ+
    SYSNETAPI_SERIAL_GUI_IRIS_DEC,      // ����ͷ��Ȧ-
    SYSNETAPI_SERIAL_GUI_PRESET_SET,    // ����ͷԤ��
    SYSNETAPI_SERIAL_GUI_PRESET_GET,    // ����ͷ����//80
    SYSNETAPI_SERIAL_GUI_AUTO,          // ����ͷ�Զ�
    SYSNETAPI_SERIAL_GUI_MUTE,          // ����
    SYSNETAPI_SERIAL_GUI_INFO,          // ��Ϣ//540
    SYSNETAPI_SERIAL_GUI_STEP,          // ֡��
    SYSNETAPI_SERIAL_GUI_PLAY,          // ����
    SYSNETAPI_SERIAL_GUI_FASTF,         // ���
    SYSNETAPI_SERIAL_GUI_FASTB,         // ����
    SYSNETAPI_SERIAL_GUI_CLRALT,        // �������
    SYSNETAPI_SERIAL_GUI_F1,            // F1
    SYSNETAPI_SERIAL_GUI_F2,            // F2//90
    SYSNETAPI_SERIAL_GUI_IGEFORMAT,     // �����ʽ
    SYSNETAPI_SERIAL_GUI_IGESWITCH,     // �����ֻ�
    SYSNETAPI_SERIAL_GUI_STOP,          // STOP //550
    SYSNETAPI_SERIAL_GUI_SHUTDOWN,      // ��Դ,�ػ�����
    SYSNETAPI_SERIAL_GUI_PWDRST,        // ���븴λ
    SYSNETAPI_SERIAL_GUI_PWDNRST,       //���벻��λ
    SYSNETAPI_SERIAL_GUI_F1VGA2TV,      // vga������л�
    SYSNETAPI_SERIAL_GUI_MOUSESTATUS,   // ���
    SYSNETAPI_SERIAL_GUI_VIDEOPARAM,    // ��Ƶ����
    SYSNETAPI_SERIAL_GUI_BRUSH,         // ��ˢ
    SYSNETAPI_SERIAL_GUI_PTZ,           // PTZ//100
    SYSNETAPI_SERIAL_GUI_REFRESH,       // REAL GUI USE
    SYSNETAPI_SERIAL_GUI_REFRESHTIME,   // REAL GUI USE//560
    SYSNETAPI_SERIAL_GUI_TEMPERATURE,   // ǰ����¶�
    SYSNETAPI_SERIAL_GUI_SETSYSTIME,    //����ϵͳʱ��
    SYSNETAPI_SERIAL_GUI_REBOOT,        //ϵͳ����
    SYSNETAPI_SERIAL_GUI_CLOSE,         //ϵͳ�ػ�
    SYSNETAPI_SERIAL_GUI_PS2STATUS,     //PS2���״̬
    SYSNETAPI_SERIAL_GUI_SET,           //110
    SYSNETAPI_SERIAL_GUI_DELAY_SHUTDOWN,//��ʱ�ػ�

    // KEYBOARD CMD
    SYSNETAPI_SERIAL_KEYB_GETADDR = 200,        // ��ȡ���ڼ��̵�ַ��,param(int *)
    SYSNETAPI_SERIAL_KEYB_SETADDR,              // ���ô��ڼ��̵�ַ��,param(int(0~512)),

    SYSNETAPI_SERIAL_GUI_LCDSTATE,
    SYSNETAPI_SERIAL_GUI_VIDEOMATRIX_SINGLE,    //������Ƶ����ͨ�����
    SYSNETAPI_SERIAL_GUI_VIDEOMATRIX_MUTI,      //������Ƶ�����ͨ�����
    SYSNETAPI_SERIAL_GUI_VIDEOMATRIX_POLL,      //������Ƶ������ѯ
    SYSNETAPI_SERIAL_GUI_MAINPIC_SWITCH_MODE,   //������������ʾ��ʽ
    SYSNETAPI_SERIAL_CMD_GUI_DOOR_STATE,  //ǰ����ŵ�״̬������1������0��״̬�ı��ʱ���ϱ�
    SYSNETAPI_SERIAL_GUI_OTREC,//һ��¼��
} SYSNETAPI_SERIAL_GUI_E;
typedef struct
{

    int status; // 0 -- ����   1 -- ����
    sint32 reserve;
} PT_LCDCTRL_S;

typedef struct
{
    PT_NETKEYCMD_E cmd;
    uint32 keycode;
} PT_NETKEY_S, *PPT_NETKEY_S;

/* �����ļ����뵼��*/
typedef enum
{
    PT_BACK_TYPE_GUI = 1,
    PT_BACK_TYPE_NET, 
    PT_BACK_TYPE_UNKNOW,
}PT_BACK_TYPE_E;

typedef struct
{
    uint32 choose_flag;//����ѡ���־����0XFF---Ȩ�ޡ������������������ֵ���
    uint8 sys_general_im;//ϵͳ�����Ƿ���  0--������ 1--����
    uint8 output_im;// ��������Ƿ���   0--������ 1--����
    uint8 rec_param_im;//��������Ƿ���   0--������ 1--����
    uint8 rec_plan_im;//��ʱ¼���Ƿ���   0--������ 1--����
    
    uint8 alm_set_im;//���������Ƿ���  0--������ 1--����
    uint8 uart_set_im;//���������Ƿ���  0--������ 1--����
    uint8 ptz_set_im;//��̨�����Ƿ���  0--������ 1--����
    uint8 net_set_im;//���������Ƿ���  0--������ 1--����
    
    uint8 card_set_im;//����¼�������Ƿ���  0--������ 1--����
    uint8 sys_time_set_im;//ϵͳʱ�������Ƿ���  0--������ 1--����
    uint8 storage_set_im;//�洢�����Ƿ���  0--������ 1--����
    uint8 time_reboot_im;//��ʱ�����Ƿ���  0--������ 1--����

    uint8 input_set_im;//���������Ƿ���  0--������ 1--����
    uint8 usr_manage_im;//�û���������Ƿ���   0--������ 1--����
    uint8 reserve[2];
}PT_IMPORT_S, *PPT_IMPORT_S;

typedef struct
{
    uint32 backup_type;					//U�̱���-1�� ���籸��-2��  PT_BACK_TYPE_E
    uint8  file_path[256];				//U�̱���-�ļ�·��
    uint8  file_name[PT_MAX_STRING_EXT];   //������ߵ��������ļ����ơ�
    uint32 file_len;					//���籸��-�ļ����ݳ���
    void * file_addr;					//���籸��-�ļ�����ָ��  �ⲿ�����ڴ洫��
    PT_IMPORT_S import_choose;          //����ѡ��----�ݲ�֧��
} PT_CONFIG_BACKUP_S, *PPT_CONFIG_BACKUP_S;

/* �û������ļ���Ϣ */
typedef struct
{
    sint32 conf_size;  //�����ļ���С
} PT_USERCONF_INFO_S, *PPT_USERCONF_INFO_S;
/* �û���Ϣ */
typedef struct
{
    uint8 user[MAX_STRING];         // �û���
    uint8 pwd[MAX_STRING];          // �û�����
    uint8 grp_name[MAX_STRING];     // ���ڷ�����

    // ÿλ����һ��ͨ��,bit0~bit63��ʾ0~63ͨ��,�������32��Ȩ��.Զ�����16��Ȩ��.
    uint64 local_authority[32];     // �����û�ʹ��Ȩ��;
    uint64 remote_authority[16];    // Զ��Ȩ��

    uint32 bind_ipaddr;             // Զ�̰�IP
    uint8 bind_macaddr[8];          // Զ�̰�MAC
} PT_ACCOUNT_S, *PPT_ACCOUNT_S;

/* �û�����Ϣ */
typedef struct
{
    uint8 name[MAX_STRING];           // ������

    uint64 local_authority[32];       // �����û�ʹ��Ȩ��;
    uint64 remote_authority[16];      //Զ��Ȩ��
} PT_GROUPACCOUNT_S, *PPT_GROUPACCOUNT_S;

/* �û����� */
typedef struct
{
    uint8 count;                // �û�����
    uint8 grp_count;            // �û�������
    uint16 list_enable;         // ��½ʱ�Ƿ���ʾ�û��б�
    PT_ACCOUNT_S        cur_user;                       // ���ص�ǰ��¼�û�
    PT_ACCOUNT_S        accounts[PT_MAX_ACCOUNT];       // �û��б�
    PT_GROUPACCOUNT_S   grp_accounts[PT_GRP_ACCOUNT];   // �û����б�
} PT_ACCOUNT_CONFIG_S, *PPT_ACCOUNT_CONFIG_S;

typedef struct
{
    uint16 enalmmax;            //�������ʹ�ñ�ʶ��0--δʹ�ܣ�1--ʹ��
    uint8 almoutbuzzer;         //�����ͷ�����
    uint8 almoutaudio;          //�����������ʹ��

    PT_TMSCHEDULE_S schedule;   //����ʱ������
    PT_ALMLINKPLAN_S plan;      //��������Ԥ��
    PT_AREA_S    coverarea[MAX_MASK];
    uint32 mail_enable;         //�����ʼ�ʹ��  0-�ر� 1-����
} PT_MASKRECPARAM_S, *PPT_MASKRECPARAM_S;

typedef struct
{
    uint16  enalmmax;           //�������ʹ�ñ�ʶ��0--δʹ�ܣ�1--ʹ��
    uint16  almoutbuzzer;       //�����ͷ�����
    uint16  almoutaudio;        //�����������ʹ��
    uint16  almoutsec;          //�������ʱ��
    PT_TMSCHEDULE_S schedule;   //����ʱ������
} PT_ALARMOUTPARAM_S, *PPT_ALARMOUTPARAM_S;

typedef struct
{
    uint32 open_bk_handle;       // �Ѵ򿪵ı��ݾ��
    uint32 size;                 // �뱸�����ݴ�С������ʵ����Ҫ����
    sint8 * data;                // �������ݣ�����buf��С����С��size
} PT_BACKUPREAD_S, *PPT_BACKUPREAD_S;


typedef struct
{
    char name[16];
    ptptz_control func;
} PT_PTZLIST_S, *PPT_PTZLIST_S;

typedef struct
{
    uint8 server[MAX_STRING];   // ������
    uint16 port;                // �˿�
    uint8 auto_enbale;          // ����ntp����,0- ������ ,1-��ʾ�Զ� ��2-��ʾ�ֶ�
    uint8 server_index;         // ������������
    uint16 sync_period;         // ͬ�����ڣ�
    uint16 sync_unit;           // ͬ�����ڣ�0-���� 1-Сʱ 2-�� 3-���� 4-��
    uint16 sync_time;           // ͬ��ʱ�䣬��ʽ Сʱ:����
    uint16 reserve;             // ����λ
    int    time_zone;           // ʱ��
} PT_NTPCONFIG_S, *PPT_NTPCONFIG_S;

typedef struct
{
    uint8   host[PT_MAX_SMTP_HOST];     // �����ʼ���SMTP�����������磺126�������smtp.126.com
    uint32 port;                        // �������˿ڣ������ʼ�(SMTP)�˿ڣ�Ĭ��ֵ25
    uint8  user[MAX_STRING];            // �ʼ��û���
    uint8  pwd[MAX_STRING];             // �ʼ��û�����
    uint8 send_addr[PT_MAX_SMTP_HOST];  // FROM���ʼ���ַ
    uint8 recv_addr[PT_MAX_SMTP_ADDR];  // TO���ʼ���ַ�����8�������ַ
    uint16 send_period;                 // �ϴ�����,��λ(����,���ֵ120)
    uint16 snap_enable: 1;              // �Ƿ�ץ���ϴ�
    uint16 ssl_enable : 1;              // ssl����ʹ�ܣ�0-�ر� 1-����
    uint16 starttls_enable : 1;         // 0-�ر� 1-����
    uint16 reserves : 13;               // ����λ
    uint8  reserve[MAX_STRING];         // �����ֽ�
} PT_SMTPCONFIG_S, *PPT_SMTPCONFIG_S;


// ʵʱͼ����ѵ
typedef struct
{
    uint8 enable;               // ���ã�0-���ã�1-����
    uint8 period;               // ��ѵ�������λ��
    uint16 format;              // �����ʽ��0-0ff, 1-1, 2-2, 4-2x2, 9-3x3, 16-4x4
    uint16 ch_list[MAX_CH];      // ȡֵ[0��n-1]����0xff��n��ͨ������oxff��ʾ��������Ч
    uint32 lock_time;                // ����ʱ�� ��λ ����
} PT_POLLCONFIG_S, *PPT_POLLCONFIG_S;

typedef struct
{
    uint8 matrix_channel[PT_MAX_MATRIX];    // ��Ƶ�����Ӧͨ�� ��1��ʼ��0xff��ʾ�ر�
    uint8 reserve[MAX_STRING];              // ����λ
} PT_VIDEOMATRIX_S, *PPT_VIDEOMATRIX_S;


typedef struct
{
    uint8 hderr_enable;         // ���̴���ʹ��
    uint8 temp_enable;          // �¶ȱ���ʹ��
    uint8 temp_show;            // �¶��Ƿ���ʾ��0-����ʾ��1-��ʾ
    uint8 temp_unit;            // �¶ȵ�λ��0-���϶ȣ�1-���϶�
    uint8 threshold_enable;     // ʹ��
    uint8 threshold_high;       // ���̸߷�ֵ0-100
    uint8 threshold_low;        // ���̵ͷ�ֵ0-100
    uint8 net_down_enable : 1;  // �������ʹ��
    uint8 ip_collision_enable : 1; //IP��ͻʹ��
    uint8 alarminfo_send : 1;   // ������Ϣ�Ƿ���0: �ϴ� 1:���ϴ�(����: Ϊʹ��֮ǰ�汾ͳһ)
    uint8 usb_ico_show : 1;     // usbͼ���Ƿ���ʾ
    uint8 email_ico_shaow : 1;  // emailͼ���Ƿ���ʾ
    uint8 hderr_mail_enable : 1;// ���̱��������ʼ��ϴ�ʹ�ܣ�0-���ϴ���1-�ϴ�
    uint8 temp_mail_enable : 1; // �¶ȱ��������ʼ��ϴ�ʹ�ܣ�0-���ϴ���1-�ϴ�
    uint8 reserve : 1;          // ����

    uint8 hdfull_alm_enable;
    uint8 hdfull_mail_enable;
    uint16 temp_limit;          // �¶����ޣ���λ���϶�
    uint32 sensor_out;          // ����̽ͷ���
} PT_ERRALARM_S, *PPT_ERRALARM_S;

typedef struct
{
    uint8 video_stat[MAX_CH];    // ��Ƶ��ʧ״̬
    uint8 motion_detect[MAX_CH]; // �ƶ�֡�ⱨ��״̬
    uint8 sensor_detect[MAX_AM];	// ̽ͷ��������״̬
    uint8 ipc_sensor_detect[MAX_CH];	// IPC̽ͷ��������״̬
    uint8 sensor_out[MAX_AMOUT]; // ��ͨ��̽ͷ���״̬
    uint8 vcover_detect[MAX_CH];	// �ڵ�����״̬
    uint8 poeconfict_detect[MAX_CH];	// POEtͨ�������ͻ����״̬
    uint8 rectype[MAX_CH];      // ��ͨ��¼������
    uint8 manual_rec[MAX_CH];
    uint8 time_rec[MAX_CH];
    uint8 motion_rec[MAX_CH];
    uint8 sensor_rec[MAX_CH];   // ��ͨ��������¼��״̬
    uint16 disk_err; 			// ���̱���״̬
    uint16 disk_full_alm;       //����������
    uint16 temp_error;          // ���̺�ϵͳ�¶ȴ���
    uint16 net_down;            // ������ߴ���
    uint8 pic_rectype[MAX_CH];  // ��ͨ��¼������
} PT_IOSTATUS_S, *PPT_IOSTATUS_S;

typedef struct
{
    char    name[MAX_STRING];   // �û���
    uint32  ip;                 // IP
    PT_MFSTIME_S login_time;    // ��¼ʱ��
    uint32  usr_id;             // �û�ID��Ψһ
    uint32 reserve;             //
} PT_ONLINE_USER_S, *PPT_ONLINE_USER_S;

//����״̬
typedef struct
{
    uint32                  user_num;               //�����û���
    PT_ONLINE_USER_S  online_user[PT_MAX_USER];     //�û���Ϣ
    uint32                  reserve;                //��ǰ�û����ڹۿ���ͨ��
} PT_ONLINE_USER_INFO_S, *PPT_ONLINE_USER_INFO_S;

//��ʽ���豸��Ϣ
typedef struct
{
    sint32  dev_num;    //�洢�豸����ͨ��
    sint32  dev_type;   //�洢�豸���ͣ�PT_DEVTYPE_E
    sint32  reserve;    //����λ
} PT_FORMAT_DEV_S;
//��ʽ������ṹ��
typedef struct
{
    uint32          format_num;                 //��Ҫ��ʽ���豸����
    uint32          format_log_flg;	            //�Ƿ��ʽ����־��־��0--����ʽ����1--��ʽ��
    PT_FORMAT_DEV_S dev_info[PT_MAX_DEV_NUM];   //ÿ��Ҫ��ʽ���豸����Ϣ
} PT_FORMATINFO_S, *PPT_FORMATINFO_S;

typedef enum
{
    SYSNETAPI_DISK_INFORMAT = 0,//�������ڱ���ʽ��
    SYSNETAPI_DISK_FORMATEND,   //��ʽ������
    SYSNETAPI_DISK_ALL_FMTEND,  //���д��̸�ʽ������
    SYSNETAPI_FARMAT_ERR ,      //��ʽ������

    SYSNETAPI_DISK_NOEXIST,     //Ҫ��ʽ���Ĵ��̲�����
    SYSNETAPI_DISK_LOST,        //��ʽ����;����
    SYSNETAPI_DISK_BUSY,        //�������ڱ�ʹ��
} PT_FORMATTYPE_E;

typedef struct
{
    uint16 dev_num;         //��ʽ���Ĵ��̺�
    uint16 dev_type;        //��ʽ���Ĵ�������
    uint16 percentstate;    //��ǰ����ֻ��format_stateΪSYSNETAPI_DISK_INFORMATʱ��Ч
    uint8  format_state;    //��ʽ��״̬����PT_FORMATTYPE_E
    uint8  err_status;      //����
} PT_FORMATSTATE_S, *PPT_FORMATSTATE_S;


typedef struct
{
    uint16 enable;              //0-������1-����
    uint16 time;                //������ʱʱ��
    uint32 reserver[4];         //����
} PT_REAL_DEFENCE_S, *PPT_REAL_DEFENCE_S;

typedef struct
{
    uint16 alm_ch;              //����ͨ��
    uint16 alm_type;            //��������0-�ޱ���1-̽ͷ����2-�ƶ����3-��Ƶ��ʧ
    PT_MFSTIME_S time;          //��������ʱ���
} PT_ALMINFO_S, *PPT_ALMINFO_S;
typedef struct
{
    uint32 alm_count;                   //�����ڼ䱨������
    PT_ALMINFO_S alminfo[MAX_AM_COUNT]; //ÿ�α����������Ϣ��ֻ�洢���µ�16�α���
    uint32 reserver[4];  			    //����
} PT_DISCONN_ALMSTAT_S, *PPT_DISCONN_ALMSTAT_S;

typedef enum
{
    SIZE_8M = 0,		//8M
    SIZE_16M ,			//16M
    SIZE_32M ,			//32M
    SIZE_64M ,			//64M
    SIZE_128M ,		    //128M
    SIZE_256M ,		    //256M
    SIZE_512M ,		    //512M
    SIZE_1024M,		    //1024M
} PT_MEMSIZE_E;
typedef struct
{
    uint16	mem_size;	        //���������ڴ��С,�����PT_MEMSIZE_E
    uint16	flash_size;         //����flash��С,�����PT_MEMSIZE_E
    uint16  disk_free_percent;  //��ǰ�������̿��������ٷֱ�
    uint16  hdd_num;            //������ǰ�ѽӴ��̸���
    uint16  encrypt;            //�����Ƿ�Ƿ���־��0--�Ϸ�����0--�Ƿ�
    uint16  serial_num;         //����֧�ִ��ڸ���
    uint16  pb_num;             //����֧��¼��ط�ͨ��
    uint16  pic_pb_num;         //����֧��ͼƬ�ط�ͨ��
    uint16  esata_num;          //�����̵�ESATA����
    uint16  reserve;            //����
    sint8   android[PT_CLIENT_DL_ADDR];     //��׿�ֻ��ͻ������ص�ַ
    sint8   ios[PT_CLIENT_DL_ADDR];         //IOS�ֻ��ͻ������ص�ַ
} PT_HOST_SYSINFO_S, *PPT_HOST_SYSINFO_S;

typedef struct
{
    uint32 enable;
    uint8 chlist[MAX_CH];
    PT_ENCCONFIG_S venc_conf;
    uint32 reserve;
} PT_ZERO_VENC_CONFIG_S, *PPT_PZERO_VENC_CONFIG_S;

typedef struct
{
    uint8 vcover_enable;        //�ڵ�����ʹ�ܣ�1-���ã�0-������
    uint8 vcover_email_enable;  //�ڵ�����ʹ�ܣ�1-���ã�0-������
    uint8 vcover_sensitivity;   //�ڵ����������� (0-5)              //added by ypxiao 1112
    uint8 reserve;              //����λ
    uint32 sensor_out;          //���������������λ��ʾ��1-������0-������
} PT_VCOVER_ALM_CONFIG_S, *PPT_VCOVER_ALM_CONFIG_S;

typedef struct
{
    uint8 enable;               //POEͨ����ͻ����ʹ�ܣ���Ҫ������POE�ڱ���POE�豸ռ�õ����
    uint8 mail_enable;          //POEͨ����ͻ���������ʼ��ϴ�ʹ�ܣ�0-���ϴ���1-�ϴ�
    uint16 reserve;             //����
} PT_POE_CONFLICT_CONFIG_S, *PPT_POE_CONFLICT_CONFIG_S;

//MFS2.0 ��������
//��������Ϣ
typedef struct
{
    sint16  hdd_attri;      // ��������0:��д��1 ֻ�� ��2 ����
    sint8   hdd_group;      // �����
    sint8   hdd_devno;      // ��ΪESATA��ʱ����ESATA�豸��
    sint16  dev_type;
    sint16  hdd_type;      // ��������0: ������ 1 ������ ��2 ����
} PT_HDD_GROPE_INFO_S, *PPT_HDD_GROPE_INFO_S;

//¼��ͨ������Ϣ
typedef struct
{
    sint16  hdd_group;      //��������
    sint16  reserve;        //����
} PT_REC_GROPE_INFO_S, *PPT_REC_GROPE_INFO_S;

typedef struct
{
    uint8 dev_tbl[PT_DEVTYPE_MAX][PT_MAX_DEV_NUM]; /* Ӳ�����ñ�,PT_DEVTYPE_E,ÿ�������豸���֧��MAX_DSK��Ӳ�� */
    uint8 ch_tbl[MAX_CH];                   /* ͨ�����ñ�,���֧��MAX_CH��ͨ�� */
    uint8 group;                            /* �������(0~63) */
    uint8 reserve[3];                       /* ����λ */
} PT_DISK_GROUP_INFO_S, *PPT_DISK_GROUP_INFO_S;

//��ͼ����
//�ֶ���ͼ����
typedef struct
{
    sint8 resolution;       //ͼƬ������0:CIF 1:D1
    sint8 quality;          //ͼƬ���� 1~6
    sint16 reserve;
} PT_MANUAL_SANPSHOT_CONFIG_S, *PPT_MANUAL_SANPSHOT_CONFIG_S;

//��ʱ��ͼ����
typedef struct
{
    sint8 resolution;       //ͼƬ������0:CIF 1:D1
    sint8 quality;          //ͼƬ���� 1~6
    uint8 period;           //��ͼ���(1~255S)
    uint8 num;              //��ͼͼƬ����(1~255S)
    PT_TMSCHEDULE_S schedule;
    sint32 reserve;
} PT_TIME_SANPSHOT_CONFIG_S, *PPT_TIME_SANPSHOT_CONFIG_S;

//�ƶ���ͼ����
typedef struct
{
    sint8 resolution;       //ͼƬ������0:CIF 1:D1
    sint8 quality;          //ͼƬ���� 1~6
    uint8 period;           //��ͼ���(1~255S)
    uint8 num;              //��ͼͼƬ����
    uint8 snap_bind[MAX_CH];//������ͼ
    PT_TMSCHEDULE_S schedule;
    sint32 reserve;
} PT_MOTION_SANPSHOT_CONFIG_S, *PPT_MOTION_SANPSHOT_CONFIG_S;

//̽ͷ��ͼ����
typedef struct
{
    sint8 resolution;       //ͼƬ������0:CIF 1:D1
    sint8 quality;          //ͼƬ���� 1~6
    uint8 period;           //��ͼ���(1~255S)
    uint8 num;              //��ͼͼƬ����
    uint8 snap_bind[MAX_CH];//������ͼ
    PT_TMSCHEDULE_S schedule;
    sint32 reserve;
} PT_SENSOR_SANPSHOT_CONFIG_S, *PPT_SENSOR_SANPSHOT_CONFIG_S;

/* �洢���ݲ�����Ϣ */
typedef struct
{
    uint16 rec_priority;    /* ¼�����ݴ洢���ȼ�(���𰴴�С�ɵ͵���[0-15]) */
    uint16 rec_time;        /* ¼������ʱ������(��λ: ��[0-4096]) */
    uint16 pic_priority;    /* ͼƬ���ݴ洢���ȼ�(���𰴴�С�ɵ͵���[0-15]) */
    uint16 pic_time;        /* ͼƬ����ʱ������(��λ: ��[0-4096]) */
    uint16 channel;         /* ͨ����[0-255] */
    uint16 enable;          /* �Զ�ɾ������ʹ�ܱ�־(1-ʹ�� 0-��ʹ��) */
    uint32 reserve;         /* ����λ */
} PT_STORE_PARAM_INFO_S, *PPT_STORE_PARAM_INFO_S;

typedef struct
{
    uint32 tm_uint;		//0~23 ���ô洢ɾ������ʱ��
    uint32 reserve;    /* ����λ */
} PT_STORE_DEL_TIME_S, *PPT_STORE_DEL_TIME_S;

//ͼƬ�洢����
typedef struct
{
    sint16  snapshot_type;          // ��ͼ����:�ֶ�����ʱ���ƶ�������,PT_RECTYPE_E
    uint16  snapshot_resolution;    // ������:CIF
    uint8   snapshot_quality;       // ����:1~6
    uint8   snapshot_period;        // ��ͼ���
    uint16  snapshot_num;           // ��ͼ����
    uint8   snapshot_link[MAX_CH];  // ������ͼͨ��
    PT_TMSCHEDULE_S snapshot_plan;  // ��ʱ��ͼʱ��
    uint8  snapshot_en_plan;        // ��ͼ���ض�ʱ
    uint8  snapshot_en_motion;      // ��ͼ�����ƶ�
    uint8  snapshot_en_alm;         // ��ͼ���ر���
    uint8  snapshot_en_manu;        // ��ͼ�����ֶ�
    uint32 reserve;//
} PT_SNAPSHOT_CONFIG_S, *PPT_SNAPSHOT_CONFIG_S;

// ����ʱ��������ʱ��
typedef struct
{
    uint16    month;        //����ʱ�������ã���
    uint16    weeks;        //����ʱ�������ã���
    uint16    week;         //����ʱ�������ã�����
    uint16    hour;         //����ʱ��������,     ʱ
    uint16    min;          //����ʱ�������ã���
    uint16    sec;          //����ʱ�������ã���
} PT_DST_WEEK_TIME_S;

//����ʱʱ������
typedef struct
{
    sint16  dst_en;                     //����ʱʹ�ܼ�
    uint16  dsttype_en;                 //��������Ϊ0, ����������Ϊ1

    PT_MFSTIME_S start_date;            //���������õĿ�ʼʱ��
    PT_MFSTIME_S end_date;              //���������õĽ���ʱ��
    PT_DST_WEEK_TIME_S  start_time;     //�������õĿ�ʼʱ��
    PT_DST_WEEK_TIME_S  end_time;       //�������õĽ���ʱ��
    uint32  reserve;
} PT_DST_TIME_S;


typedef enum
{
    SECFILE_QUERY_MONTH = 0,    //¼���ļ�������ѯ
    SECFILE_QUERY_DATA,         //¼�����ݲ�ѯ
    SECFILE_QUERY_PAGEUP,       //¼�����ݲ�ѯ��ҳ���Ϸ�
    SECFILE_QUERY_PAGEDOWN,     //¼�����ݲ�ѯ��ҳ���·�
    SECFILE_QUERY_PAGEGOTO,     //¼�����ݲ�ѯ��ҳ����ת
} PT_SECFILE_OP_TYPE_E;

/*���ݷ�ʽѡ��Ŀǰ֧�ְ��Ρ����졢���±���*/
typedef enum
{
    BACKUP_BY_SEG = 0,
    BACKUP_BY_DAY,
    BACKUP_BY_MON,
    BACKUP_BY_YEAR,
    BACKUP_BY_TIMESEG,          //��ʱ��α��ݣ����Լ��ݿ��� ���µ�
    BACKUP_BY_FILES,            //���ļ�����
} PT_SECFILE_BACKUP_TYPE_E;

typedef enum
{
    DATA_CODETYPE_REC = 0x00,       /* ��Ƶ�� */
    DATA_CODETYPE_PIC = 0x80,       /* ͼƬ�� */
    DATA_CODETYPE_PIC_IPC = 0x90,   /* ����ͼƬ�� */
    DATA_CODETYPE_BACKUP = 0x100,   /* ������*/
    DATA_CODETYPE_IPPRI = 0x10,     /* ��������Ƶ��*/
    DATA_CODETYPE_IPSEC = 0x11,     /* �������Ƶ�� */
    DATA_CODETYPE_IPTHR = 0x12,     /* ���������Ƶ�� */
    DATA_CODETYPE_MULTI = 0x13,      /* ��ͨ����Ƶ�� */
    DATA_CODETYPE_CARD = 0xFF,      /*������Ƶ��*/
} PT_DATA_CODETYPE_E;


/* �洢�ļ�����(��λ��ʾ),���֧��8������ */
typedef enum
{
    PT_FILEATTR_UNKNOWN = 0x00,
    PT_FILEATTR_RREAD = 0x01,      /* �ɶ� */
    PT_FILEATTR_WRITE = 0x02,      /* ��д */
    PT_FILEATTR_LOCK = 0x04,       /* ���� */
    PT_FILEATTR_DELETE = 0x08,     /* ɾ�� */
} PT_FILEATTR_E;

/* �洢����������˾�����ʹ���,���֧��255�� */
typedef enum
{
    PT_COMPANYCODE_HBGK = 0x00,        /* ����߿� */
    PT_COMPANYCODE_HIKVISION = 0x01,   /* �������� */
    PT_COMPANYCODE_DAHUA = 0x02,       /* �㽭�� */
} PT_COMPANYCODE_E;

typedef enum
{
    OPT_NORMAL = 0,
    OPT_REPLAY,
    OPT_FORMAT,
    OPT_BACKUP,
    OPT_UPGRADE,
    OPT_LOCK,
    OPT_UNLOCK,
    OPT_DEL,
    OPT_OTHER,
} PT_OPT_TYPE_E;

/* �ļ���ʽ */
typedef enum
{
    PT_FILELAYOUT_DAT,      /* ����ר���ļ�,��չ��Ϊ.dat */
    PT_FILELAYOUT_AVI,      /* ��׼AVI��Ƶ,��չ��Ϊ.avi */
    PT_FILELAYOUT_JPG,      /* ��׼JPGͼƬ,��չ��Ϊ.jpg */
    PT_FILELAYOUT_LOG,      /* ����ר���ļ�,��չ��Ϊ.log */
} PT_FILELAYOUT_E;

// ¼�����ݲ�ѯ���(ͼƬ��¼��),ÿ�ε���Ϣ
typedef struct
{
    PT_MFSTIME_S time_start;// ���ݶο�ʼʱ��
    PT_MFSTIME_S time_stop; // ���ݶν���ʱ��
    uint64  data_size;      // �����ݳ���,�ֽ�
    uint16  idx_amount;     // ����洢����Ϊ����Ƶ����,���ʾI֡����������;����洢����ΪͼƬ,���ʾͼƬ����
    uint8   channel;        // ������ͨ����(0~255)
    uint8   store_type;     // ����������(PT_RECTYPE_E)
    uint8   code_type;      // �洢���ݱ�������(PT_DATA_CODETYPE_E)
    uint8   dev_type;       // �豸����(PT_DEVTYPE_E)
    uint8   dev_num;        // �豸��(0~63)
    uint8   dev_part;       // ������(0~31)
    uint16  file_num;       // �ļ����(0~16383)
    uint8   file_attr;      // �ļ����ļ������ͱ��(PT_FILEATTR_E)
    uint8   company_code;   // ���̵����ʹ���(PT_COMPANYCODE_E)
    uint8   segment;        // �洢���ݶ���Ϣ���(0~254)
    uint8   use_stat;       // �����ݶ�ʹ��״̬
    uint8   is_link;        // �Ƿ�ƴ��(MFS_FLASE-δƴ��,MFS_TRUE-��ƴ��)
    uint8   reserve;        // ����λ
} PT_RECFILE_SEGINFO_S, *PPT_RECFILE_SEGINFO_S;

// �ļ������ѯ(����������ѯ)
typedef struct
{
    sint32     ch_no;			    // ͨ����
    uint8      dev_type;            // Դ�豸���� ,��PT_DEVTYPE_E
    uint8      dev_no;              // ��ѯ�豸��
    uint8      data_type;		    // ��������,��PT_DATA_CODETYPE_E
    uint8      rec_type;			// ��¼���� :�ֶ�����ʱ���ƶ���������ȫ��,PT_RECTYPE_E
    sint8      card_no[32];         // ����
    uint16     data_attri;			// ��д���ԣ�0--ȫ����1--������2--δ����
    uint16     file_type;           // ���ݵ��ļ���ʽ 0---���� 1---AVI 2-jpg
    uint32     start_num;           // ��ѯ��ʼ������Ĭ��Ϊ0,SYSNETAPI_CMD_QUERY_REC_DATAʱ��Ч
    uint32     limit_num;           // ������ѯ������SYSNETAPI_CMD_QUERY_REC_DATAʱ��Ч
    uint32     rec_status;     	    // �������룬SYSNETAPI_CMD_QUERY_REC_DATEʱ�˲���Ϊ�����������λ��ʾ�����ݵ�����
    PT_MFSTIME_S    start_date;	    // ��ѯ��ʼ����
    PT_MFSTIME_S    end_date;	    // ��ѯ�������ڣ���ʱ��β�ѯʱ��Ч
    uint8      move_area[PT_MAX_INTEL_BLOCK_NUM];      // �������������ǣ���λ��ʾ��1����ѡ�У��ܼ�22*18=396λ����˳�����У�����������ѯʱ��Ч
    uint16     intel_flag;//����������ǣ�Ϊ1ʱ��move_area��Ч
    uint16     intel_mode;//��������ģʽ��1:�Զ� 0:�ֶ�
} PT_RECFILE_QUERY_S, *PPT_RECFILE_QUERY_S;


typedef struct
{
    uint32 query_num;   // ʵ�ʲ����������
    uint32 total_num;   // ��ǰ��ѯ�����µ�������
    PPT_RECFILE_SEGINFO_S   recfile_seginfo;    //ÿ�����ݶε���Ϣ��������buf���ⲿ����
} PT_RECFILE_QUERYINFO_S, *PPT_RECFILE_QUERYINFO_S;


typedef struct
{
    PT_RECFILE_QUERY_S        query_condition;  // ��ѯ��������
    PT_RECFILE_QUERYINFO_S    query_info;       // ��ѯ�������
} PT_QUERY_RECFILE_ALL_S, *PPT_QUERY_RECFILE_ALL_S;

//�ļ��������
typedef struct
{
    uint32  op_type;            // �������� : ������������ɾ��������,��PT_OPT_TYPE_E
    uint8	bk_ch[PT_MAX_REC_CH_NUM];   // ����ͨ�� 1λ����һ��ͨ��
    uint32	rec_type;           // ¼�����ͣ��ֶ�����ʱ���ƶ�������,PT_RECTYPE_E
    uint32  data_type;          // ��������  ͼƬ ��¼�񣬼�PT_DATA_CODETYPE_E����
    uint32  backup_type;        // op_typeΪOPT_BACKUPʱ��Ч����PT_SECFILE_BACKUP_TYPE_E
    uint32  backup_dev_ch;      // op_typeΪOPT_BACKUPʱ��Ч�������豸����ͨ��
    uint32  backup_dev_type;    //�����豸���ͣ���PT_DEVTYPE_E
    uint16  backup_foramt;      //op_typeΪOPT_BACKUPʱ��Ч�������ļ���ʽ(.dat .avi .jpg�ȣ���PT_FILELAYOUT_E)
    uint16  data_attri;			// ��д���ԣ�0--ȫ����1--������2--δ����
    PT_MFSTIME_S start_time;    // ��ʼʱ�䣬��ʱ��Ρ����졢���µȱ���ʱ��Ч
    PT_MFSTIME_S end_time;      // ����ʱ�䣬��ʱ��Ρ����졢���µȱ���ʱ��Ч
    uint32  op_num;             // Ĭ��Ϊ0��Ҫ��ָ�����ݶν��в���ʱ��Ч����ʾѡ������������
    uint32	backup_opt;			// ���ݲ��� 0--�ֶ����� 1--���ٱ��� 2--��ʱ���� ��PT_BACKUP_OP_E
    PPT_RECFILE_SEGINFO_S   recfile_seginfo;// Ĭ��ΪNULL��Ҫ��ָ�����ݶν��в���ʱ��Ч��ѡ����ÿ�����ݶε���Ϣ
} PT_RECFILE_OP_S, *PPT_RECFILE_OP_S;

// ��־�����ѯ
typedef struct
{
    PT_MFSTIME_S date;          // ����  input
    sint16  pri_type;           // ������
    sint16  sec_type;           // ������
    uint32  log_status;         // ��-��    ��־״̬���������ʾ output
    PT_DEVTYPE_E  dev_type;     // Դ�豸���� ,��PT_DEVTYPE_E input
} PT_QUERY_LOGMASK_S, *PPT_QUERY_LOGMASK_S; //���²�ѯ��ȡ��־����

typedef struct
{
    sint32      ch_no;			    // ͨ����
    sint32      data_type;		    // ��������,��PT_DATA_CODETYPE_E
    PT_MFSTIME_S    start_date;	    // ��ѯ��ʼ����
    PT_MFSTIME_S    end_date;	    // ��ѯ�������ڣ���ʱ��β�ѯʱ��Ч
    uint8      move_area[PT_MAX_INTEL_BLOCK_NUM];      // �������������ǣ���λ��ʾ��1����ѡ�У��ܼ�22*18=396λ����˳�����У�����������ѯʱ��Ч
    uint16     intel_mode;//��������ģʽ��1:�Զ� 0:�ֶ�
} PT_INTEL_PB_S, *PPT_INTEL_PB_S;

typedef struct
{
    sint32      ch_no;			    // ͨ����
    sint32      data_type;		    // ��������,��PT_DATA_CODETYPE_E
    PT_MFSTIME_S    start_date;	    // ��ѯ��ʼ����
    PT_MFSTIME_S    end_date;	    // ��ѯ�������ڣ���ʱ��β�ѯʱ��Ч
    uint8       move_area[PT_MAX_INTEL_BLOCK_NUM];      // �������������ǣ���λ��ʾ��1����ѡ�У��ܼ�22*18=396λ����˳�����У�����������ѯʱ��Ч
    uint32      limit_num;          // ������ѯ����
    uint32      query_num;          // ʵ�ʲ����������
    PPT_RECFILE_SEGINFO_S   recfile_seginfo;//ÿ�����ݶε���Ϣ��������buf���ⲿ����
} PT_INTEL_QUERYINFO_S, *PPT_INTEL_QUERYINFO_S;


//һ���������
typedef struct
{
    sint16	x;          //������
    sint16	y;          //������
} PT_POINT_S, *PPT_POINT_S;

/**************** ����ģ��ʹ����Ϣ****************/

//��������
typedef struct
{
    uint32 left;            //����������
    uint32 top;             //����������
    uint32 right;           //����������
    uint32 bottom;          //����������
} PT_ATMI_RECT, *PPT_ATMI_RECT;

//����α�ʾ�ṹ�壬����������
typedef struct
{
    PT_POINT_S  point[10];      //����ζ�������
    sint32 	   point_num;       //��ĸ���
    sint32      region_type;    //��������
} PT_ATMI_POLYGON_S, *PPT_ATMI_POLYGON_S;

//�������򣬴���������
typedef struct
{
    PT_ATMI_RECT region;        //������������
    sint32 region_type;         //��������
} PT_ATMI_RECT_TYPE_S, *PPT_ATMI_RECT_TYPE_S;

//��������Ȥ�����Լ��������������Ĵ�С
typedef struct
{
    PT_ATMI_RECT_TYPE_S roi;    //����
    sint32 min_face;            //��С�ߴ�
    sint32 max_face;            //���ߴ�
} PT_ATMI_FACE_ROI_S, *PPT_ATMI_FACE_ROI_S;

// 1.����ͨ���������õ�����
typedef struct
{
    sint32 num;
    PT_ATMI_FACE_ROI_S face_roi[10];
} PT_ATMI_FACEROI_ALL_S, *PPT_ATMI_FACEROI_ALL_S;

// 2.���ͨ���������õ�����
typedef struct
{
    sint32 num;
    PT_ATMI_POLYGON_S atmi_panel_region[20];
} PT_ATMI_PANEL_REGION_S, *PPT_ATMI_PANEL_REGION_S;

// 3.�ӳ���ͨ���������õ����򼰲���
typedef struct
{
    PT_ATMI_POLYGON_S pol_proc_region;	// ��������Ĭ��4���㣬����ȫͼ
    PT_ATMI_RECT_TYPE_S no_process[10]; // ����������
    sint32 no_process_num;		        // ������������� (0)
    sint32 warn_interval;	            // ���α���ʱ������(100 ��)
} PT_ATMI_DISTRICTPARA_S, *PPT_ATMI_DISTRICTPARA_S;

// 4.����ͨ���������õ�����
typedef	struct
{
    PT_ATMI_POLYGON_S pol_proc_region;  // ͼ���еĴ������򣬶���α�ʾ

    /*����ATM��ǰβ��ȡ����Ĳ�������ʶATMǰ��վ��������*/
    PT_ATMI_POLYGON_S tail_region[10];  // Region in polygon.
    sint32 tail_num;				    // Region number. default: 0

    /*���ڽ�ֹ������뱨������ʶѡ���Ľ�ֹ���������*/
    PT_ATMI_POLYGON_S forbid_region[10];// Region in polygon.
    sint32 forbid_num;					// Region number.	default: 0

    //sint32 obj_height;		        // Ŀ�꣨�ˣ���ͼ���еĸ߶ȣ�Ĭ��85
    PT_ATMI_POLYGON_S obj_height;
} PT_ATMI_SCENE_COMMONPARA_S, *PPT_ATMI_SCENE_COMMONPARA_S;

// 5.����ͨ�����õĲ���,������֡Ϊ��λ�ģ������ڽ�������Ϊ�룬Ȼ�����ڲ���ת��Ϊ֡��
typedef struct
{
    /*��Ʒ�����㷨��ز���*/
    sint32 objlv_frames_th;				// ��Ʒ����ʱ����ֵ(֡) (30)

    /*��Ա�ǻ��㷨��ز���*/
    sint32 mv_block_cnt;			    // �ƶ�����(20��0��ʾ�˹�����Ч)
    sint16 mv_stay_frames;			    // �����г���ʱ����ֵ(֡),������ʱ��(0��ʾ�˹�����Ч)
    sint16 mv_stay_valid_frames;	    // ATM����ͣ��ʱ����ֵ(֡),ATM����ǰͣ��ʱ��(200, 0��ʾ�˹�����Ч)

    /*���˾ۼ��㷨��ز���*/
    sint16 gather_cnt;				    // ���ۼ�����(4)
    sint16 gather_interval_frames;	    // �������ʱ��(֡)(1000 frames,Լ100��)
    sint32 gather_frame_cnt;		    // ���˾ۼ�ʱ����ֵ(֡) (100)

    /*��Ա�����㷨��ز���*/
    sint32 liedown_frame_cnt;		    // ����ʱ����ֵ(֡).(20 frames)

    /*β��ȡ���㷨��ز���*/
    sint16 after_frame_cnt;				// ������Ϊʱ����ֵ(֡)(20 frames)
    sint16 after_interval_frames;	    // �������ʱ��(֡)(1000 frames,Լ100��)

    /*��ֹ�����㷨��ز���*/
    sint16 forbid_frame_cnt;		    // ��ֹվ��ʱ����ֵ(֡)(20 frames)
    sint16 reserve;                                            // ����
} PT_ATMI_SCENE_WARN_PARAM_S, *PPT_ATMI_SCENE_WARN_PARAM_S;

// 1.����ͨ�����ýṹ��
typedef struct
{
    sint16 face_unusual;                //�Ƿ���쳣�����������֡�����ȣ���⹦�ܣ�1 Ϊ�򿪣�0 Ϊ�رա�Ĭ��Ϊ 0
    sint16 output_oneface;              //��������ֻ���һ�����0Ϊ��1Ϊ�ǣ�Ĭ��Ϊ1
    sint32 fd_rate;                     //�������������ټ��
    PT_ATMI_FACEROI_ALL_S face_roi;     //����ͨ����������������
} PT_ATMI_SET_FACE_S, *PPT_ATMI_SET_FACE_S;

// 2.���ͨ�����ýṹ��
typedef struct
{
    sint32 timeout_enable;              //��ʱʱ��
    PT_ATMI_PANEL_REGION_S panel_region;//���ͨ��������������
} PT_ATMI_SET_PANEL_S, *PPT_ATMI_SET_PANEL_S;

// 3.�ӳ���ͨ�����ýṹ��
typedef struct
{
    PT_ATMI_DISTRICTPARA_S money_para; //�ӳ���ͨ��������������
} PT_ATMI_SET_MONEY_S, *PPT_ATMI_SET_MONEY_S;

// 4.����ͨ�����ýṹ��
typedef struct
{
    PT_ATMI_SCENE_WARN_PARAM_S envi_para;   //����ͨ������
    PT_ATMI_SCENE_COMMONPARA_S envi_region; //����ͨ������
} PT_ATMI_SET_ENVI_S, *PPT_ATMI_SET_ENVI_S;

//GUI���õ����ص��ܵĽṹ��
typedef struct
{
    sint32 chn;                             //ͨ����
    sint32 chn_attri;                       //ͨ������(��������塢�ӳ�������)��Ŀǰδ�ã���ֹ�Ժ���

    sint16 channel_enable;                  //ͨ�����أ�0�رգ�1��
    sint16 if_pic;                          //�Ƿ���ҪץȡͼƬ
    sint16 enc_type;                        //ץȡͼƬ�ĸ�ʽ
    sint16 email_linkage;                   //����email
    uint32 sensor_num;                      //̽ͷ���,λ��ʾ
    uint32 rec_linkage;                     //����¼��λ��ʾ

    /*��ͨ���ŷֱ�ȡ����Ľṹ��ÿ��ֻ�ܶ�Ӧһ��*/
    PT_ATMI_SET_FACE_S face_set_para;       //����ͨ�����ýṹ��
    PT_ATMI_SET_PANEL_S panel_set_para;     //���ͨ�����ýṹ��
    PT_ATMI_SET_MONEY_S money_set_para;     //�ӳ���ͨ�����ýṹ��
    PT_ATMI_SET_ENVI_S envi_set_para;       //����ͨ�����ýṹ��
} PT_ATMI_NET_SYS_S, *PPT_ATMI_NET_SYS_S;

//�������ͼ�λ����Ϣ
typedef struct
{
    sint32 alarm_type;          //����,GUI_ATMI_ALARM_TYPE_E
    PT_ATMI_RECT position;      //����λ��
} PT_ATMI_ALARM_POSITION_S, *PPT_ATMI_ALARM_POSITION_S;

// 1.����ͨ�������ṹ��
typedef struct
{
    sint32 alarm_num;                           //��������
    PT_ATMI_ALARM_POSITION_S alarm_area[10];    //��������ֵ,һ����alarm_num���������ȫΪ0
} PT_ATMI_FACE_ALARM_S, *PPT_ATMI_FACE_ALARM_S;

// 2.���ͨ�������ṹ��
typedef struct
{
    sint32 alarm_num;                           //��������
    PT_ATMI_ALARM_POSITION_S alarm_area[10];    //��������ֵ,һ����alarm_num���������ȫΪ0
} PT_ATMI_PANEL_ALARM_S, *PPT_ATMI_PANEL_ALARM_S;

// 3.�ӳ����������Ϣ
typedef struct
{
    sint32 type; //�Ƿ����˴��룬0��ʾ�ޣ�1��ʾ��
} PT_ATMI_MONEY_ALARM_S, *PPT_ATMI_MONEY_ALARM_S;

// 4.���������ṹ��,alarm_num����Ӧ��������ǰ��track_num����Ӧ�����������alarm_num�����
typedef struct
{
    sint32 alarm_num;  //����Ŀ������
    sint32 track_num;   //����Ŀ������
    PT_ATMI_ALARM_POSITION_S envi_alarm_region[25];
} PT_ATMI_ENVI_ALARM_S, *PPT_ATMI_ENVI_ALARM_S;

//������Ϣ���ص������أ��ٴ���GUI
enum
{
    PT_ATMI_FACE_BLOCK = 0,                 //�����ڵ�
    PT_ATMI_FACE_NOSIGNAL,                  // ����ͨ����Ƶ��ʧ
    PT_ATMI_FACE_UNUSUAL,                   //�����쳣
    PT_ATMI_FACE_NORMAL,                    //��������

    PT_ATMI_PANEL_BLOCK  = 40,              //����ڵ�
    PT_ATMI_PANEL_NOSIGNAL,                 //���ͨ����Ƶ��ʧ
    PT_ATMI_PANEL_PASTE,                    //����
    PT_ATMI_PANEL_KEYBOARD,                 //װ�ټ���
    PT_ATMI_PANEL_KEYMASK,                  //�ƻ����������
    PT_ATMI_PANEL_CARDREADER,               //�ƻ�������
    PT_ATMI_PANEL_TMIEOUT,                  //��ʱ����

    PT_ATMI_ENTER,                          //���˽���
    PT_ATMI_EXIT,                           //�˳���

    PT_ATMI_MONEY_BLOCK = 80,               //�ӳ�����Ƶ�ڵ�
    PT_ATMI_MONEY_NOSIGNAL,                 //�ӳ���ͨ����Ƶ��ʧ
    PT_ATMI_MONEY_UNUSUAL,                  //�ӳ����쳣,�����˴���ӳ���

    PT_ATMI_ENVI_BLOCK = 120,               //����ͨ����Ƶ�ڵ�
    PT_ATMI_ENVI_NOSIGNAL,                  //����ͨ����Ƶ��ʧ
    PT_ATMI_ENVI_GATHER,                    //���˾ۼ�
    PT_ATMI_ENVI_MANYPEOPLEINREGION,        //Υ��ȡ��
    PT_ATMI_ENVI_LINGERING,                 //��Ա�ǻ�
    PT_ATMI_ENVI_LIEDOWN,                   //��Ա����
    PT_ATMI_ENVI_FORBIDREGION,              //�Ƿ����뾯����
    PT_ATMI_ENVI_LEAVEOBJECT,               //��Ʒ����
} PT_ATMI_ALARM_TYPE_E;


//ͼƬ��Ϣ
typedef struct
{
    sint32 pic_alarm_type;  //PT_ATMI_ALARM_TYPE_E
    sint32 pic_format;      //ͼƬ��ʽCIF:0  D1:1
    uint32 pic_size;        //ͼƬ��С
} PT_ATMI_ALARM_PICINFO_S, *PPT_ATMI_ALARM_PICINFO_S;

//����ʱ�������ص��ܽṹ��
typedef struct
{
    sint32 chn;                             // ͨ����,ÿ�α����󣬸���ͨ���ţ�ȥ��ȡ�����ĸ��ṹ���ж�Ӧ����һ��

    /*��ͨ���ŷֱ�ȡ����Ľṹ��ÿ��ֻ�ܶ�Ӧһ��*/
    PT_ATMI_FACE_ALARM_S atmi_face_alarm;   // 1.����ͨ�������ṹ��
    PT_ATMI_PANEL_ALARM_S atmi_panel_alarm; // 2.���ͨ�������ṹ��
    PT_ATMI_MONEY_ALARM_S atmi_money_alarm; // 3.�ӳ���ͨ�������ṹ��
    PT_ATMI_ENVI_ALARM_S atmi_envi_alarm;   // 4.����ͨ�������ṹ��

    PT_ATMI_ALARM_PICINFO_S   alarm_picinfo;// ����ͼƬ��Ϣ
    PT_MFSTIME_S alarmtime;                 //����ʱ��
} PT_ATMI_ALARM_INFO_S, *PPT_ATMI_ALARM_INFO_S;


/*****************��Ƶ������չ�ṹ��*************************/

//�ؼ�֡��صĽṹ��
typedef struct
{
    PT_AUSTREAMADD_E byStreamType;          //��Ƶ������
    PT_RESOLUTION_E byResolution;           //��Ƶ�ֱ���
    PT_BITRATETYPE_E byBitrateType;         //��������
    PT_VQUALITY_E byPicQuality;             //ͼ������
    uint16 dwVideoBitrate;                  //��Ƶ���� ʵ������
    uint16 dwVideoFrameRate;                //֡�� PAL 2-30 N 2-30
    uint16 quant;                           //�������� 1-31
    uint16 key_interval;                    // �ؼ�֡���0-65535
} PT_ENCCONFIG_EXL_S, *PPT_ENCCONFIG_EXL_S;

typedef struct
{
    PT_STREAMTYPE_E streamtype;             //Ҫ���û��߻�ȡ����������
    PT_RECTYPE_E       rectype;             //¼������
    PT_ENCCONFIG_EXL_S enc;                 //�������
} PT_STREAMENCPARAM_EXL_S, *PPT_STREAMENCPARAM_EXL_S;

typedef struct
{
    PT_VERSION_S swver;             // ��������
    sint8 oem_ver[32];              // oem�汾����  ��ʹ�õĻ���ȫ����0
    sint32 reserve;
} PT_SYSVERSION_S, *PPT_SYSVERSION_S;

//ģ��汾�ṹ��
typedef struct
{
    int   num;//��ȡ�汾�ŵ�ģ����
    sint8 vi[MAX_VER_LEN];
    sint8 vo[MAX_VER_LEN];
    sint8 venc[MAX_VER_LEN];
    sint8 vdec[MAX_VER_LEN];
    sint8 ai[MAX_VER_LEN];
    sint8 ao[MAX_VER_LEN];
    sint8 rec[MAX_VER_LEN];
    sint8 pb[MAX_VER_LEN];
    sint8 statm[MAX_VER_LEN];
    sint8 upgrade[MAX_VER_LEN];
    sint8 uart[MAX_VER_LEN];
    sint8 ptz[MAX_VER_LEN];
    sint8 event[MAX_VER_LEN];
    sint8 fifo[MAX_VER_LEN];
    sint8 mshead[MAX_VER_LEN];
    sint8 mfs[MAX_VER_LEN];
    sint8 timer[MAX_VER_LEN];
    sint8 shmem[MAX_VER_LEN];
    sint8 msg[MAX_VER_LEN];
    sint8 ddns[MAX_VER_LEN];
    sint8 network[MAX_VER_LEN];
    sint8 trans_uart[MAX_VER_LEN];
    sint8 daemon[MAX_VER_LEN];
    sint8 aenc[MAX_VER_LEN];
    sint8 adec[MAX_VER_LEN];
    sint8 m_uboot[MAX_VER_LEN];
    sint8 m_kernel[MAX_VER_LEN];
    sint8 sdk[MAX_VER_LEN];
    sint8 serial[MAX_VER_LEN];
    sint8 svn_info[MAX_VER_LEN];
    sint8 p2p_sn[MAX_VER_LEN];

    sint8 reserve[13][MAX_VER_LEN];//����,����չ
} PT_COMPVERSION_S, *PPT_COMPVERSION_S;


// ͼ�����Ե����
typedef struct
{
    uint16 x, y; // xy����
    uint16 w, h; // ��Ⱥ͸߶�
} PT_RECT, *PPT_RECT;

typedef struct
{
    uint16  channel;        // ͨ��
    uint16  enable;    //��/��EQ
    uint16  type;      //������
    uint16  length;    //�߳���
} PT_EQ_CONFIG, *PPT_EQ_CONFIG;

typedef struct
{
    uint32 split;                   // �ָʽ1-1, 2-2 4-2x2, 9-3x3, 16-4x4
    uint32 anti_flicker;      // �Ƿ���CVBS���� 0-���� 1-����
    PT_RECT vo_coordinate;          // ��Ƶ���ƫ�ƣ�x,y��ʼ���� w-x�����ϵ����� h-y�����ϵ�����
    PT_RECT vi_coordinate[MAX_CH];  // ��Ƶ����ƫ��
} PT_VRECT_CONFIG, *PPT_VRECT_CONFIG;

typedef enum
{
    PT_CONFIG_CHANAGE = 0X100,	    //֪ͨƽ̨�����ļ��б仯
    PT_STATUS_NOTIFY,			    //ƽ̨״̬����֪ͨ
} PT_SGPT_NOTIFY_E;

typedef struct
{
    uint8 dvr_start;                //DVRϵͳ������0-δ������1-����
    uint8 dvr_normal_shutdown;      //DVRϵͳ�˳���0-δ�˳���1-�˳�
    uint8 dvr_abnormal_down;        //DVR�쳣�˳���0-δ������1-����
    uint8 dvr_setparam;             //DVR�������ã�0-δ������1-����
    uint8 dvr_videolost;            //DVR��Ƶ��ʧ��0-δ������1-����
    uint8 dvr_motion_detection;     //DVR�ƶ���⣬0-δ������1-����
    uint8 dvr_outtigger;            //DVR�ⲿ������0-δ������1-����
    uint8 dvr_alarmremove;          //ϵͳ���������0-δ������1-����
    uint8 dvr_illegal_quit;         //DVR�Ƿ��˳���0-δ������1-����
    uint8 dvr_local_playback;       //DVR���ػطţ�0-δ������1-����
    uint8 dvr_remote_playback;      //DVRԶ�̻طţ�0-δ������1-����
    uint8 dvr_disk_err;             //DVR���̴���0-δ������1-����
    uint8 sys_heart_out;            //ϵͳ������ʱ��0-δ������1-����
    uint8 sys_heart_remove;         //ϵͳ�����ָ���0-δ������1-����
    uint8 other_videothing;         //��Ƶ�����¼���0-δ������1-����
    uint8 reserver[9];
} PT_SGPT_STATUE_S, *PPT_SGPT_STATUE_S; //ƽ̨״̬�ṹ��

typedef enum
{
    OSD_NOTIFY,
    NET_NOTIFY,
    MFS_NOTIFY,
    SERIAL_NOTIFY,
    NETMS_PRI_DATA,
    NETMS_SEC_DATA,
} CALLBACK_TYPE_E; //ע��PNETAPICALLBACKʱ�Ļص�����


typedef struct
{
    uint32 en_time_reboot;
    uint32 week;                        //����ʱ��-��(0-ÿ�죬1---7��Ӧ��һ������)
    uint32 hour;
    uint32 reserve;
} PT_TIME_REBOOT_S, *PPT_TIME_REBOOT_S;

// ��ʱ����
typedef struct
{
    uint8 ch;                           //��ʱ�����豸����ͨ��
    uint8 dev_type;                     //�����豸����
    sint8 rec_type;                     //¼������ -1---ȫ����0---�ֶ�¼��1---��ʱ¼�� 2---�ƶ�¼��3---����¼��
    uint8 en_time_backup;               //�Ƿ�����ʱ����  0---�������� 1---����
    uint8 cycle;                        //��������  0---ÿ�죬1-7---��һ������
    uint8 ch_no[PT_MAX_REC_CH_NUM];        //��Ч��ʱ����ͨ����(1Ϊѡ�У�0Ϊδѡ��)
    uint8 time;                         //0-23---0����23��
    uint8 cover_mode;                   //����������ģʽ 0---�Զ�����, 1---�ֶ�����
    sint8 file_type;                    // ���ݵ��ļ���ʽ 0---���� 1---AVI
    sint8 reserve[2];
} PT_TIME_BACKUP_S, *PPT_TIME_BACKUP_S;


//ʱ����¼��״̬
typedef enum
{
    PT_TIME_RULE_NONE,
    PT_TIME_RULE_MANUAL,
    PT_TIME_RULE_TIME,
    PT_TIME_RULE_MOTION,
    PT_TIME_RULE_ALARM,
    PT_TIME_RULE_CARD,
    PT_TIME_RULE_INTELSEARCH,
} PT_REC_STAT_TYPE_E;

typedef struct
{
    char data_mask[PT_GRAPH_DATA_MASK_NUM]; //24Сʱ12���Ӿ��ȣ�2Сʱ1���Ӿ��ȣ�1Сʱ30�뾫�ȣ���Сʱ15�뾫��  PT_REC_STAT_TYPE_E
} PT_SEARCH_REC_DATA_GRAPH_MAKS_S;

typedef struct
{
    PT_SEARCH_REC_DATA_GRAPH_MAKS_S	graph_data[PT_REC_DATA_GRAPH_PAGE_NUM];	//ͼ����ʾ��������
    sint32 precision;													    //ͼ�ξ��ȣ���λΪ��
} PT_SEARCH_REC_DATA_GRAPH_DATA_S;

typedef struct
{
    sint16		ch_s[PT_GRAPH_REC_CH_NUM];				    //ͨ�����ݣ�Ŀǰ���һ�β�8��ͨ�������ѡ�е�ͨ����
    PT_MFSTIME_S 	start_time;								//��ʼʱ��
    PT_MFSTIME_S 	end_time;								//����ʱ�䣬Ŀǰ��ʱ���Ӧ����24Сʱ��2Сʱ��1Сʱ����Сʱ�е�һ�����
    sint32 		dev_no;									    //�豸�ţ���ѯ�����豸ʹ�ã���ʱ��ʹ��
    sint16		rec_type;								    //¼����������,Ŀǰ���õ�Ӧ�ö���ȫ����
    sint16      data_type;                                  //0x00-��Ƶ��,  0x80-ͼƬ��
    PT_SEARCH_REC_DATA_GRAPH_DATA_S	data_graph_data;
    uint32 	    reserve;
} PT_SEARCH_REC_DATA_GRAF_S;

typedef struct
{
    sint32  type;       /* PT_RECTYPE_E */
    PT_MFSTIME_S start_time;
    PT_MFSTIME_S end_time;
} PT_REC_SEG_S;

typedef struct
{
    PT_MFSTIME_S query_date;
    sint16  rec_type;   /* PT_RECTYPE_E */
    sint16  file_type;  /* ���ݵ��ļ���ʽ 0---���� 1---AVI 2-jpg */
    sint16  data_type;  /* PT_DATA_CODETYPE_E */
    sint16  dev_type;   /* ����Դ�豸���� ,��PT_DEVTYPE_E */
    sint32  seg_max;    /* ��������С buf_size/sizeof(PT_REC_SEG_S) */
    sint32  seg_num;    /* �����ܹ���ȡ�Ķ��� */
    uint8      move_area[PT_MAX_INTEL_BLOCK_NUM];      // �������������ǣ���λ��ʾ��1����ѡ�У��ܼ�22*18=396λ����˳�����У�����������ѯʱ��Ч
    uint16     intel_flag;//����������ǣ�Ϊ1ʱ��move_area��Ч
    PT_REC_SEG_S * rec_seg;
} PT_REC_DATE_SEG_S;

typedef struct
{
    PT_SEARCH_REC_DATA_GRAPH_MAKS_S	graph_data;	//ͼ����ʾ��������
    sint32 precision;   //ͼ�ξ��ȣ���λΪ��
} PT_SMART_SEARCH_DATA_GRAPH_DATA_S;

typedef struct
{
    sint32		ch;				                            //ͨ�����ݣ�Ŀǰ���һ�β�8��ͨ�������ѡ�е�ͨ����
    PT_MFSTIME_S 	start_time;								//��ʼʱ��
    PT_MFSTIME_S 	end_time;								//����ʱ�䣬Ŀǰ��ʱ���Ӧ����24Сʱ��2Сʱ��1Сʱ����Сʱ�е�һ�����
    PT_SMART_SEARCH_DATA_GRAPH_DATA_S data_graph_data;
} PT_SMART_SEARCH_DATA_GRAF_S;

typedef struct
{
    uint16 x;
    uint16 y;
    uint16 w;
    uint16 h;
} PT_RCWH_S;

//��Ƶ�ֲ��Ŵ�
typedef struct
{
    sint32 enable; 					// ʹ�� 1-��������Ŵ� 0-ȡ������Ŵ�
    sint32 video_mode; 			    // 0-Ԥ�� 1-�ط�
    sint32 ch_no; 					// Ԥ����--ʵ��ͨ���ţ���0��ʼ  �ط���---0
    sint32 output_dev;              /* ������Ŵ������豸 */  
    PT_RCWH_S src_area;             // Դ����
    PT_RCWH_S dest_area;            // Ŀ������
} PT_VIDEO_ZOOMIN_S;

typedef enum
{
    SDK_SPLIT_ONE = 1,
    SDK_SPLIT_TWO = 2,
    SDK_SPLIT_FOUR = 4,
    SDK_SPLIT_SIX = 6,          // ֻ���豸HD֧��
    SDK_SPLIT_EIGHT = 8,        // 8·����
    SDK_SPLIT_NINE = 9,         // 16·����
    SDK_SPLIT_NINE_EX = 10,     //9������չ���������,ʵ����ʾ6����(1��+5С)
    SDK_SPLIT_TWELVE = 12,
    SDK_SPLIT_SIXTEEN = 16,
    SDK_SPLIT_SIXTEEN_EX = 17,  //16������չ���������,ʵ����ʾ8����(1��+7С)
    SDK_SPLIT_SIXTEEN_EX2 = 18, //16������չ���������,ʵ����ʾ13����(�м�1��+����12С)
    SDK_SPLIT_TWENTY = 20,
    SDK_SPLIT_TWENTYFOUR = 24,
    SDK_SPLIT_TWENTYFIVE = 25,
    SDK_SPLIT_THIRTYTWO = 32,
    SDK_SPLIT_THIRTYSIX = 36,
    SDK_SPLIT_TWENTYFIVE_EX = 40,///* 25���治�������,ʵ����ʾ13����,��4+С9,9012X3���� */
    SDK_SPLIT_THIRTYSIX_EX = 41, ///* 36���治�������,ʵ����ʾ24����,��4+С20,9020X3���� */
    SDK_SPLIT_PATTERN144    = 44,/* 12*12���������� */
    SDK_SPLIT_PATTERN144_EX = 45,/* 12*12���治�������,ʵ����ʾ20����,��4+С16��9020X3���� */
} SDK_SPLIT_E;

/* ��ǰʵʱ�ط�״̬ */
typedef enum
{
    PT_VIDEO_MODE_LIVE = 0,
    PT_VIDEO_MODE_REPLAY = 1,
    PT_VIDEO_MODE_NVD = 2,      /* ����Ԥ��ģʽ */
} PT_VIDEO_MODE_E;

/* ����Ԥ��ʱ�л����� */
typedef enum
{
    PT_IPD_MODE_NVD = 0,
    PT_IPD_MODE_IPC = 1,
}PT_IPD_MODE_E;

typedef enum
{
    PT_SPLIT_SCREEN0 = 0,
    PT_SPLIT_SCREEN1 = 1,
    PT_SPLIT_SCREEN2 = 2,
    PT_SPLIT_SCREEN3 = 3,
    PT_SPLIT_SCREEN4 = 4,
    PT_SPLIT_SCREEN5 = 5,
    PT_SPLIT_SCREEN6 = 6,
    PT_SPLIT_SCREEN7 = 7,
    PT_SPLIT_SCREEN8 = 8,
    PT_SPLIT_SCREEN9 = 9,

    PT_SPLIT_SCREEN_PREV = 0xFE,    /* previous ��һ�� */
    PT_SPLIT_SCREEN_NEXT = 0xFF,    /* ��һ�� */
} PT_SPLIT_SCREEN_E;

//�������û�ȡ
typedef struct
{
    uint16  type;                           // SDK_SPLIT_E �ָʽ1-1,4-2x2,6-3x2,9-3x3,16-4x4
    uint16  video_mode;                     // 0--live;	1--replay PT_VIDEO_MODE_E
    sint16  ch_list[PT_MAX_REC_CH_NUM];     // ͨ��˳��
    uint16  main_ch;                        /* ָ����Ƶͨ��,����ch_list�е�ͨ�� */
} PT_IMAGE_SPLIT_S, *PPT_IMAGE_SPLIT_S;

/* ��ָ����ʽ��ǰ������ */
typedef struct
{
    sint32 type;                /* SDK_SPLIT_E */
    sint32 screen;              /* PT_SPLIT_SCREEN_E */
}PT_SCREEN_SPLIT_S;

//��Ƶ�����ʽ
typedef struct
{
    uint32 split_ch_num;        //���ַ�����ʽӵ�е�ͨ����
    uint16 x_cell_num;          //��ִ���
    uint16 y_cell_num;          //�ݷִ���
    PT_RECT ch_info[PT_MAX_REC_CH_NUM];
} PT_VOSPLIT_S;

typedef enum
{
    LAMP_NETWORK,        //�����
    LAMP_ALARM,          //������
    LAMP_PTZ,            //��̨����ָʾ��
    LAMP_REC,            //¼��ָʾ��
    LAMP_PPPOE,          //����ָʾ��
    LAMP_REMOTE_LOCK,    //ң������ָʾ��
} PT_LAMP_TYPE_E;


//����״̬
typedef enum
{
    PT_NET_STAT_COMMON = 0,     //����
    PT_NET_STAT_IP_CONFLICT,    //IP��ͻ
    PT_NET_STAT_DISCONNECT,     //����Ͽ�
    PT_NET_INTERNET_OK,         //����������������״̬��ͼ����ʾ������ͼ��*/
    PT_NET_INTERNET_ERR,        //����������ʧ�ܣ�״̬��ͼ����ʾ����̾�ŵ�ͼ��*/
} PT_NET_STAT;

//wifi״̬
typedef enum
{
    PT_WIFI_CARD_ERR = 20, //�������쳣�γ�
    PT_WIFI_CARD_IN, // �����Ѳ���
    PT_WIFI_CARD_OUT, // �����Ѱγ�
} PT_WIFI_STAT;

typedef enum
{
    PT_PPPOE_STAT_NOCONNECT,    // δ����
    PT_PPPOE_STAT_CONNECTING,   // ��������
    PT_PPPOE_STAT_CONNECTED,    // ������
    PT_PPPOE_STAT_CONNECTERR    // ���Ӵ���
} PT_PPPOE_STAT_E;

/* ���ݲ������� --add by xcli 2015/11/25 */
typedef enum
{
    PT_BACKUP_OP_MANUAL = 0,    /* �ֶ����� */
    PT_BACKUP_OP_FAST,   		/* ���ٱ��� */
    PT_BACKUP_OP_TIME,    		/* ��ʱ���� */
} PT_BACKUP_OP_E;

typedef struct
{
    sint32      pb_cmd;         //�طſ�������(����ʱ��Ч) PT_PLAYBACKSTATUS_E
    sint32 		source;		    //�洢�������ͣ�0-���ش��̣�1-USB�豸��2-esata 3-CD/DVD�豸
    sint32 		rec_type; 	    //¼�����ͣ�PT_RECTYPE_E
    sint32      data_type;      //��������,��PT_DATA_CODETYPE_E����
    SYSTIME 	start_time;	    //¼��ʼʱ��
    SYSTIME     end_time;       //¼�����ʱ��(���̻ط�ʱ��ֵ��Ч)
    sint32      percent;        //������ת����ʱ���ݰٷֱ�
    sint32      pb_handle;      //�ط������(�����ط�ʱ��Ч)�������.

    /*����Ϊ�����˻ط�ʹ��*/
    uint32 		length;		    //�����ļ�����
    uint32 		ch;			    //��ͨ��
    uint32 		ch_mask;	    //�ط�ͨ������
    uint8 		sync; 		    //ͬ����־
    uint8 		pb_split;	    //�طŻ����ʽSDK_SPLIT_E
    uint16      reserve;
} PT_PLAYBCK_S;

typedef struct
{
    SYSTIME start;  /* ��ʼʱ�� */
    SYSTIME stop;   /* ����ʱ�� */
} PT_PLAYBACK_SETTIME;

typedef enum
{
    PT_ATTR_STATUS_OK = 0,		    /* ����������,δ�������� */
    PT_ATTR_STATUS_FAILED_BEFORE,   /* ������������������ */
    PT_ATTR_STATUS_FAILING          /* �����Ե�ǰ�������� */
} PT_ATTR_STATUS;

typedef struct
{
    sint8   attr_name[32];          /* ���� */
    sint8   raw_string[32];         /* ԭʼֵ */
    uint16  current;			    /* ��ǰֵ */
    uint16  worst;			        /* ���ֵ */
    uint16  flags;                  /* ��־λ */
    uint16  type;                   /* ����(������flags) */
    uint16  update;                 /* ��������(������flags) */
    uint16  threshold;              /* ��ֵ */
    uint16  attr_status;            /* ��ǰ״̬PT_ATTR_STATUS_ ( OK | FAILED_BEFORE | FAILING ) ��ö��PT_ATTR_STATUS */
    uint16  reserve;
} PT_SMART_ATTR_S, *PPT_SMART_ATTR_S;

#define PT_MAX_SMART_ATTR_NUM  32
typedef struct
{
    uint32          attr_bit_table;
    PT_SMART_ATTR_S attrs[PT_MAX_SMART_ATTR_NUM];

    char  hdd_type[64];             //�����ͺ�
    char  hdd_serial_no[64];        //�������к�
    char  hdd_firmware_ver[64];     //�̼��汾
    uint16  hdd_entire_status;      //�ۺϽ���״̬(��Ҫ�ײ㶨������Щ����״̬)
    uint16  hdd_tmp;                //�����¶�
    uint32	reserve;
} PT_SMART_INFO_S, *PPT_SMART_INFO_S;

//�ʼ�����״̬
typedef enum
{
    PT_SSMTP_STAT_NOCMD, 			// û���������
    PT_SSMTP_STAT_SENDINGMAIL, 	    // ���ڷ����ʼ�,��һ��������Ϣ
    PT_SSMTP_STAT_SENDMAILOK, 		// �����ʼ��ɹ�
    PT_SSMTP_STAT_SENDMAILERR, 	    // �����ʼ�ʧ��
    PT_SSMTP_STAT_AUTHFAIL,		    // ��֤ʧ�ܣ��û������������
    PT_SSMTP_STAT_STARTMAIL		    // ��ʼ�����ʼ�
} PT_SSMTP_STAT_E;

typedef struct
{
    uint32  mdev_num;
    uint32  lckdev_num;
} PT_DEV_NUM, *PPT_DEV_NUM;

//�ط�OSD ��Ϣ
typedef struct
{
    uint32  x;                    // X�����꣨��λΪ���أ�
    uint32  y;                    // Y�����꣨��λΪ���أ�
    uint8   data[MAX_STRING];     // ����Ϣ�������ݣ���Ϊ�ַ���������˽�����'\0'
    uint32  reserve;
} PT_PB_OSD_S, *PPT_PB_OSD_S;

typedef struct
{
    PT_PB_OSD_S gui_pb_name[PT_MAX_PB_NAME];
    uint32  pb_name_type;/*0: ˢ��ͨ��OSD�� 1:ˢ�ط�����OSD��ʾ*/
} PT_PB_OSD_CH_S, *PPT_PB_OSD_CH_S;

//�ط�OSD ͨ����
typedef struct
{
    uint16 			chlist[PT_MAX_REC_CH_NUM];	    //ͨ����˳���б�
    PT_PB_OSD_CH_S  ch_name[PT_MAX_REC_CH_NUM];    	//����˳�����е�OSD
    uint16  		main_ch;						//��ͨ����
    uint16 			pb_split;						//�طŻ����ʽ
} PT_PB_OSD_MULTIPLE_S, *PPT_PB_OSD_MULTIPLE_S;
typedef struct
{
    uint16 			chlist[MAX_CH];	    //�ط�ͨ��������״̬1-������0-��Դ����
} PT_PB_CH_LIMIT_S, *PPT_PB_CH_LIMIT_S;

typedef struct
{
    PT_MFSTIME_S     start_time;//������ʼʱ��
    PT_MFSTIME_S     end_time;  //��������ʱ��
    uint64      bkup_cap;       //������������
    uint8       file_num;       //�����ļ���Ŀ
    uint8       bkup_dev;       //�����豸
    uint8       player_flag;    //�Ƿ񱸷ݲ�����   0---�����ݣ�1---����
    uint8       file_type;      //��������ļ����� 0---DVR��   1---AVI
    uint32 		ch_mask;		//�ط�ͨ������
    sint32 		rec_type; 		//��ǰ�ط�����
    uint8       cut_flag;       //��ȡ������ִ�м����ı�־��0-��ȡ��Ϣ��1-ִ�м���
    uint8       dev_type;       //�豸���� 0-���豸
    uint8       reserve[2];
} PT_PB_CUT_S, *PPT_PB_CUT_S;

typedef struct
{
    char  ip_addr[MAX_IPADDR_STR_LEN];
    PT_RECT rect;                   /* ����λ��(��ֱ�) */
} PT_DISCOVER_VIEW_S;

typedef struct
{
    SYSTIME start_time;	            /* ¼�����ݿ�ʼʱ�� */
    PT_RECT rect;                   /* ����λ��(��ֱ�) */
} PT_PB_WINDOW_VIEW_S;

typedef enum
{
    PT_REALPB_CTRL_PLAY = 0,
    PT_REALPB_CTRL_PAUSE = 1,
} PT_REALPB_CTRL_E;

typedef struct
{
    uint16  stat; // RAID��Ա��״̬
    uint16  dev_type;               // �豸���� 0-���豸
    uint16  hdd_id;
    uint16  is_raid_dev;            // �Ƿ���RAIDӲ��: 1-��ͨӲ��; 2-RAIDӲ��; 3-�ȱ���
    uint64  capacity;               // Ӳ������
} PT_HDD_RAID_INFO_S;

typedef struct
{
    uint16  raid_lev;                   // Raid����: 0-�޼���,û�д���RAID; 1-RAID5, �Ѵ���RAID;
    uint16  status_mode;                // ״̬ģʽ: 0-����; 1-����; 2-�ؽ�; 3-��
    uint16  percent;                    // �ؽ�ģʽ�ٷֱ�: 1-100
} PT_GRP_STATE_S, *PPT_GRP_STATE_S;

// �½ṹ��RAID��Ϣ
typedef struct
{
    PT_GRP_STATE_S     raid_state[2];
    PT_HDD_RAID_INFO_S disk_info[10];   // �������˿�����Ӳ����Ϣ
} PT_RAID_INFO_S, *PPT_RAID_INFO_S;

// �½ṹ��RAID��Ϣ
typedef struct
{
    PT_RAID_INFO_S raid_info;   // RAID����Ϣ, ����: 0��, 1��
    uint32  reserve;
} PT_RAIDINFO_GRP_S, *PPT_RAIDINFO_GRP_S;


/* RAID��Ϣ */
typedef struct
{
    uint8 stat;         /* �豸RAID״̬(MFS_RAIDSTAT_E) */
    uint8 level;        /* �豸RAIDģʽ�ļ���(MFS_RAIDLEVEL_E) */
    uint8 raid_ctrlor;  /* ���������*/
    uint8 PortType;     /* Port type (Null, Disk, RAID, Optical Drive,Bad Port)*/
    uint32 table;       /* ÿ��RAID���ϵ��豸����λ����� */
    PT_RAIDDEVINFO_S infos[PT_MAX_RAID_DEV_NUM];
} PT_RAIDINFOS_S, *PPT_RAIDINFOS_S;


/* �洢�豸��Ϣ */
typedef struct
{
    uint8 dev_type;             /* �豸����(MFS_DEVTYPE_EĬ��Ӳ��) */
    uint8 dev_stat;             /* �豸״̬(MFS_DEVSTAT_E) */
    uint8 dev_num;              /* �豸��(0~63) */
    uint8 dev_attr;             /* �洢�豸����(MFS_DEVATTR_E) */
    uint8 partitions;           /* �豸������ */
    uint8 fs_stat;              /* �豸�ļ�ϵͳ�Ǹ�ʽ��(MFS_FSSTAT_E) */
    uint8 removable;            /* �豸�Ƿ���ƶ�װ��(Ĭ�Ϸ�) */
    uint8 backup;               /* �豸�Ƿ񱸷�װ��(Ĭ�Ϸ�) */
    uint8 is_raid;              /* �豸�Ƿ�RAIDװ��(0-Ĭ�Ϸ�,1-SOFT RAID,2-HARD RAID) */
    uint8 wufile_num;           /* ��Ҫ���ļ���(0~255) */
    uint16 rwfile_num;          /* ��д�ļ���(0~65535) */
    uint8 group;                /* ���ڷ���(0~63) */
    sint8 alloc_dat_fsize;      /* Ԥ���������ļ���С MFS_DATAFILESIZE_E*/
    sint8 alloc_log_fsize;      /* Ԥ������־�ļ���С MFS_LOGFILESIZE_E*/
    uint8 reserve;              /* ����λ */
    uint64 capability;          /* �豸����(�ֽ�) */
    uint64 format_capability;   /* �ļ�ϵͳ��������(��ʽ���������(�ֽ�)) */
    uint64 format_free;         /* ��ǰ��������(�ֽ�) */
    PT_RAIDINFOS_S raidinfos;   /* ��ǰ�豸RAIDװ�õ���ϸ��Ϣ */
} PT_DEVINFO_S, *PPT_DEVINFO_S;

/* �洢�豸״̬��Ϣ */
typedef struct
{
    uint64 dev_stat_tab;        /* �洢�豸״̬,��λ��ʾ0-������,1-���� */
    PT_DEVINFO_S devinfos[PT_MAX_DEV_NUM];
} PT_DEVSTATINFO_S, *PPT_DEVSTATINFO_S;

/* �洢�豸����ͳ����Ϣ*/
typedef struct
{
    PT_DEVSTATINFO_S dev_info;  /*���������λ��Ϣ*/
    uint64 grp_capability;      /*����������*/
    uint64 grp_fmt_capability;  /*�����ʽ��������*/
    uint64 grp_fmt_free;        /*����ʣ������*/
    uint32 strm_rate;           /*�����ϵ������ʹ���octets per sec*/
    uint64 freespace2sec;       /*����ʣ��ռ�ͳ�ƣ������ܹ��洢��ʱ�䳤��,����*/
    uint8 grp_ch_tbl[PT_MAX_REC_CH_NUM];    /*ͨ�����ñ���0Ϊ���ø�ͨ��*/
} PT_STOREGRP_STATS_INFO_S, *PPT_STOREGRP_STATS_INFO_S;

typedef enum
{
    PT_VOSD_TIME_24H = 0,
    PT_VOSD_TIME_12H = 1
} PT_VOSD_TIMEFORAMT_E;

typedef struct
{
    PT_RESOLUTION_E pri_vtype;              //��������������
    PT_RESOLUTION_E sec_vtype;              //��������������
    PT_RESOLUTION_E snap_vtype;             //��������������
    uint8  show_chname;                     //�Ƿ��ͨ����,1:����,0������������,����ͬ
    uint8  show_date;                       //�Ƿ��������
    uint8  show_time;                       //�Ƿ����ʱ��
    uint8  show_week;                       //�Ƿ��������
    PT_POINT_S chname_pos;                  //ͨ����λ��
    PT_POINT_S datetime_pos;                //����ʱ��λ��
    uint8  chname[PT_MAX_STRING_EXT + 1];          //����ͨ����
    PT_TIMEFORMAT_E     timeshow_format;
    PT_DATEFORMAT_E     dateshow_format;
} PT_VOSD_OVERLAYPARAM_S, *PPT_VOSD_OVERLAYPARAM_S;

typedef enum
{
    PT_NETALM_UN = 1,//�ر����籨��ʹ��
    PT_NETALM_EN,//�����籨��ʹ��
} PT_NETALM_TYPE_E;

typedef enum
{
    PT_DST_MANU_CLOSE = 0,//�ֶ��ر�����ʱ
    PT_DST_START,//����ʱ��ʼ
    PT_DST_END ,//��������
} PT_DSTTIME_TYPE_E; //����ʱ����

/*¼��ͳ��*/
typedef struct
{
    uint32  code_type;       /*¼������*/
    uint32  total_day;       /* ¼��������*/
    SYSTIME time_start;      /* ��ʼʱ�� */
    SYSTIME time_stop;       /* ����ʱ�� */
    uint64  file_count;      /* �ļ����� */
    uint64  times;           /* ��ʱ�� */
    uint64  data_size;       /* �ܳ��� */
} PT_STORAGE_INFO_S, *PPT_STORAGE_INFO_S;

typedef struct
{
    int storage_cov_day;			//ָ��Ӳ���ϸ���¼��ʱ��¼������������������ֵ
    int reserve[3];           		//����
} PT_STORAGE_COV_DAY_S, *PPT_STORAGE_COV_DAY_S;

typedef struct
{
    uint32 day;  			   /* ¼��ʵ������*/
    uint32 store_days_thres; /* ¼�񸲸����ñ�������*/
} PT_DAY_INFO_S, *PPT_DAY_INFO_S;

typedef struct
{
    uint32 addr;    /* �ֿ��ȡ���ڴ��е��׵�ַ */
    sint32 size;    /* �ֿ��С,��ȡʱ���ܳ����˴�С. */
    uint32 addr16;  /* 16�����ֿ��ַ */
    sint32 size16;
} PT_FONT_ADDR_S;

typedef struct
{
    uint32 ptz_type;          //��̨Э������
    uint32 ptz_baudrate;      //������
    uint32 reserve[4];        //�����ֶ�
} PTZ_PARAM, *PPTZ_PARAM;

typedef struct
{
    uint8 stop_flag;               //ֹͣλ 1ֹͣ 0����
    uint8 show_split_time;         //��ʾ����ָ�ʱ��
    uint8 show_page_time;          //��ʾҳ��ʱ��
    uint8 switch_screen_time;      //����ʱ��
    uint8 playback_channel[64];    //�ط�ͨ��
    uint32 playback_time;          //�ط�ʱ��
    uint32 alarm_out_time;         //�������ʱ��
    PT_MFSTIME_S sys_time;         //ϵͳʱ��
    PTZ_PARAM ptz_param;           //������̨����
    uint32 show_disk_info_time;     //��ʾ������Ϣ�������ʱ��+
    uint32 show_logo_time;          //��ʾlogo��ʱ��+
    uint32 show_system_info_time;   //��ʾϵͳ��Ϣ��ʱ��+
    uint32 reserved[5];
} PT_AUTO_TEST, *PPT_AUTO_TEST;    //�����Զ�������

//Ԥ��splits����

/* ��ʾ�豸���� */
typedef enum
{
    PT_VGA0_HDMI0_CVBS0 = 0,    //������ͬԴ����������0�д洢������ָ����  ����� display_setting[PT_MAX_DISPLAY_TYPE_NUM]
    PT_VGA0_HDMI0_CVBS1,        //VGA��HDMIͬԴ��������0��,CVBS������1��
    PT_VGA0_HDMI1_CVBS1,        //VGA�ڽṹ������0�У�HDMI��CVBSͬԴ������1��
    PT_VGA0_HDMI1_CVBS0,        //VGA��CVBSͬԴ������0�У�HDMI������1��
    PT_VGA0_HDMI1_CVBS2,        //VGA������0��HDMI������1��CVBS������2
    PT_VGA0_HDMI0,              //VGA��HDMIͬԴ,��֧��CVBS
    PT_VGA0_HDMI1,              //VGA������0,HDMI������1����֧��CVBS
    PT_VGA0_CVBS0,              //VGA��CVBSͬԴ,��֧��HDMI
    PT_VGA0_CVBS1,              //VGA������0,CVBS������1,��֧��HDMI
    PT_HDMI0_CVBS0,             //HDMI��CVBSͬԴ������0,��֧��VGA
    PT_HDMI0_CVBS1,             //HDMI������0��CVBS������1����֧��VGA
    PT_VGA0,                    //VGA������0����֧��CVBS��HDMI
    PT_HDMI0,                   //HDMI������0����֧��CVBS��VGA
    PT_CVBS0,                   //CVBS������0����֧��VGA��HDMI
} PT_DISPLAY_TYPE_E;

typedef enum
{
    NET_UPGRADE,
    USB_UPGRADE,
    FTP_UPGRADE,
} SYS_UPGRADE_AVENUE;

typedef enum
{
    FILE_COPY_UPGRADE,  //�����ļ���ʽ����
    POINTER_ROUT_UPGRADE, //����ָ�뷽ʽ����
} SYS_UPGRADE_TYPE;

typedef struct
{
    uint16  main_ch;                        /* ��ͨ�� */
    uint16  splite_type;                    /* ��ǰ�����ʽ */
    uint32  reserve;
    uint16  ch_list[PT_MAX_REC_CH_NUM];     /* �໭��ͨ��˳�� */
} PT_PREVIEW_SPLITS_SETTING_S, *PPT_PREVIEW_SPLITS_SETTING_S;

typedef struct
{
    uint16  dif_origin;
    uint16  display_type;        /* ��ʾ�豸���� */
    uint32  reserve;
    PT_PREVIEW_SPLITS_SETTING_S  display_setting[PT_MAX_DISPLAY_TYPE_NUM];  /* ���ݾݽṹ������ */
} PT_PAGE_PREVIEW_S, *PPT_PAGE_PREVIEW_S;

typedef struct
{
    uint16 pb_num; 			/* �ط�·�� */
    uint16 venc_resolution;	/* ���������� */
    uint32 venc_frams; 		/* ���Ƶ�������֡�� */
    uint32 pri_bitrate_max;    /* ������������� 0---�����ƣ���0ֵ---����ֵ*/

    sint16 sec_venc_limit_flag; /* ������������־*/
    sint16 sec_venc_frame;      /* ����������ʱ��֡�ʴ�С*/
    sint16 sec_venc_bitrate;    /* ����������ʱ�����ʴ�С 0---�����ƣ���0ֵ---����ֵ*/
    sint16 reserve;
} PT_VENC_CFG_LIMIT_S;

/* ��ȡʣ��֡��*/
typedef struct
{
    int cif_frame;     /* CIFʣ��֡�� */
    int fd_frame;	     /* FD1ʣ��֡��*/
    int qh_frame;      /* Q960ʣ��֡�� */
    int h_frame;	     /* 960ʣ��֡��*/
    int reserve[2];    /* ���� */
} PT_REMAIN_FRAME_S, *PPT_REMAIN_FRAME_S;

/* ��ȡ�ʺ�֡��*/
typedef struct
{
    int channel;      /*ͨ����*/
    int resolution;   /* �ֱ��� */
    int frame;        /* ֡�� */
    int reserve[2];   /* ����*/
} PT_CALC_FRAME_S, *PPT_CALC_FRAME_S;

typedef struct
{
    int resolution;   /* �ֱ��� */
    int frame;        /* ֡�� */
    int reserve[2];   /* ���� */
} MEDIA_USE_FRAME_S;

#if 1
#define AGENTID_LEN  16
//#define IP_LEN  128
#define PSD_LEN 32
#define MAX_CH_NUM 32

typedef enum
{
    SGPT_ING_TALK_FAULT = 0,                       //¥��Խ�����
    SGPT_PERIMETER_ALARM_FAULT,                      //�ܽ籨������
    SGPT_NET_ALARM_FAULT,                              //������������
    SGPT_LOCAL_ALARM_FAULT,                             //���ر�������
    SGPT_VIDEO_MONITOR_FAULT,                           //��Ƶ��ع���
    SGPT_IOCTROL_FAULT,                                 //������ƹ���
    SGPT_ELECTRONIC_PATROL_FAULT,                     //����Ѳ������
    SGPT_OTHER_SYS_FAULT,                            //����ϵͳ����
} SGPT_PT_WARNAME_E;

typedef enum
{
    SGPT_FRONT_FAULT = 0,                       //ǰ�˹���
    SGPT_TERMINAL_FAULT,                         //�ն˹���
    SGPT_SYSTEM_FAULT,                           //ϵͳ����
} SGPT_PT_WARSYS_E;

typedef enum
{
    SGPT_NOTHING = 0,                      //��ѡ
    SGPT_NOMAL,                            //����
    SGPT_ABNOMAL_REPAIRED,                 //�쳣���޸�
    SGPT_ABNOMAL_NOREPAIR,                 //�쳣δ�޸�
} SGPT_PT_REPAIR_E;

typedef struct
{
    int            second ; // ��: 0~59
    int            minute ; // ��: 0~59
    int            hour ; // ʱ: 0~23
} PT_TIME_OEM_S;

typedef struct
{
    char AgentID[AGENTID_LEN];           //agentID
    char addr[128];          //��ط�����IP
    int port;                 //�������˿ں�
    int run_statue;                       //����״̬����   0-�����ã�1-����
    int alm_pic_enable;//����ͼƬʹ��
    int normal_pic_enable;//�ճ���ͼʹ��
} PT_INFO_S, *LPPT_INFO_S;

typedef struct
{
    SGPT_PT_WARNAME_E pt_warname;         //����ϵͳ����
    SGPT_PT_WARSYS_E pt_warsys;           //����ϵͳ����
} PT_WARRANTY_S, *LPPT_WARRANTY_S;

typedef struct
{
    SGPT_PT_REPAIR_E pt_maintenance;         //�豸ά��
    SGPT_PT_REPAIR_E pt_repair;            //�豸ά��
} PT_MAINTREPAIR_S, *LPPT_MAINTREPAIR_S;

typedef struct
{
    int testpic_upload;            //����ͼƬ�ϴ���0-���ϴ���1-�ϴ�
    int maintpic_upload;           //����ͼƬ�ϴ���0-���ϴ���1-�ϴ�
    int channel[24];           //ͨ����
} PT_TESTMAINT_S, *LPPT_TESTMAINT_S;

typedef struct
{
    int intfront_time;              //ǰ��ʱ��   1-60��
    int intinterval_time;           //���ʱ��   1-5��
    int probe;                  //�������(̽ͷ)
    int intdyrecard_time;          //��¼ʱ��  1-60��
    int channel[24];
} PT_ALARMLINK_S, *LPPT_ALARMLINK_S;

typedef struct
{
    int enable1;       //ʱ��1ʹ�ܣ�0-��ѡ����ʱ��1���ϴ�ͼƬ��1-ѡ������ʱ��1�ϴ���Ӧͨ��ͼƬ
    int enable2;
    int channel1[24];
    int channel2[24];
    PT_TIME_OEM_S time1;               //ʱ��1����ֵ
    PT_TIME_OEM_S time2;
} PT_DAILYUPLOAD_S, *LPPT_DAILYUPLOAD_S;

typedef struct
{
    char password[PSD_LEN];           //����
    int  intacceptenceusrID;              //����ԱID
    int result;              //�����Ƿ�ͨ����0-δͨ����1-ͨ��
    int channel[24];
} PT_ACCEPTANCEUPLOAD_S, *LPPT_ACCEPTANCEUPLOAD_S;

typedef struct
{
    int ch_no;       //��Ӧ��ʾ̽ͷ��
    PT_ALARMLINK_S pt_alarmlink[24];           //������������ṹ��
} PT_ALARMPAGE_S, *LPPT_ALARMPAGE_S;

#if 0
typedef struct
{
    short int guipage_id;                   //GUI����ID����Ӧ��ʾ���ڲ�����GUI
    ����
    short int save_flag;                    //0-���棬1-�ϴ�
    PT_INFO_S pt_info;                      //ƽ̨���ý���ṹ��
    PT_WARRANTY_S pt_warranty;              //�û����޽���ṹ��
    PT_MAINTREPAIR_S pt_maintrepair;        //ά��ά������ṹ��
    PT_TESTMAINT_S pt_testmaint;            //���Ա�������ṹ��
    PT_ACCEPTANCEUPLOAD_S pt_acceptanceupload;
//����ͼƬ�ϴ�����ṹ��
    PT_ALARMPAGE_S pt_almpic;          		 //������������ṹ��
    PT_DAILYUPLOAD_S pt_dailyupload;        //�ճ�ͼƬ�ϴ�����ṹ��
} PT_SGPT_INFO_S, *PPT_SGPT_INFO_S; 			//���ƽ̨���ýṹ��
#endif

typedef struct
{
    sint32 guipage_id;                   //GUI����ID����Ӧ��ʾ���ڲ�����GUI����
    sint32 save_flag;                    //0-���棬1-�ϴ�
    PT_INFO_S pt_info;                      //ƽ̨���ý���ṹ��
    PT_WARRANTY_S pt_warranty;              //�û����޽���ṹ��
    PT_MAINTREPAIR_S pt_maintrepair;        //ά��ά������ṹ��
    PT_TESTMAINT_S pt_testmaint;            //���Ա�������ṹ��
    PT_ACCEPTANCEUPLOAD_S pt_acceptanceupload;             //����ͼƬ�ϴ�����ṹ��
    PT_ALARMPAGE_S pt_almpic;          		 //������������ṹ��
    PT_DAILYUPLOAD_S pt_dailyupload;        //�ճ�ͼƬ�ϴ�����ṹ��
} PT_SGPT_INFO_S, *PPT_SGPT_INFO_S; 			//���ƽ̨���ýṹ��

#endif

typedef struct
{
    sint16 hbydt_support;                       /* һ��ͨ����֧�� 0: ��֧�� 1: ֧�� */
    sint16 hbydt_enable;                        /* һ��ͨ�������� 0: �ر� 1: ���� �� ����hbydt_supportΪ1ʱ��Ч*/
    uint8  hbydt_domain[PT_MAX_YDTDOMAIN];      /* һ��ͨ������ַ ����: www.hbydt.cn ����: www.ivview.com */
} PT_HBYDT_S;                                   /* һ��ͨ���ܽṹ�� */

typedef struct
{
    sint16 p2p_status;  //p2p ״̬�� 0: δ����  1:������  -2:��Ч��Կ -3:��ЧUUID
    sint16 reserve;
} PT_P2P_STATUS_S;

typedef struct 
{
    sint16 alarm_push_status;
    sint16 reserve;
}PT_ALARM_PUSH_STATE_S;

typedef struct 
{
    sint16 alarm_push_enable;
    sint16 reserve;
}PT_ALARM_PUSH_CONF_S;

/*IPC���*********************************************************************/
#define IPC_IPDEV_CMD_NUM 64    /*IPDEVģ�����֧��������*/
#define IPC_SEARCH_MAX_NUM 256  /*IPDEV֧����������豸��*/

enum
{
    PT_MSG_IPC_INVALID,
    PT_MSG_IPC_AUTH_ERR,       // IPC�û������������
    PT_MSG_IPC_NET_DISCONNECT, // ����Ͽ����豸������
    PT_MSG_IPC_BATCH_ADD_ERR,       // IPC������Ӵ���
} PT_MSG_IPC_RET_E;

/*IPC �豸Э����*/
typedef enum
{
    IPC_IPDEV_PROTOCOL_HB = 0,    /* ����Э�� */
    IPC_IPDEV_PROTOCOL_ONVIF = 1, /* ONVIF Э�� */
    IPC_IPDEV_PROTOCOL_NUM,
    IPC_IPDEV_PROTOCOL_MAX = 8,
} IPC_IPDEV_PROTOCOL_TYPE_E;

typedef enum
{
    PT_IPD_TYPE_DVR = 0x1,      /* IP�豸����ΪDVR,��ӦidΪnvd_id */
    PT_IPD_TYPE_IPC = 0x8,      /* IP�豸����ΪIPC,��ӦidΪipc_id */
    PT_IPD_TYPE_NVR = 0x10,     /* IP�豸����ΪNVR,��ӦidΪnvd_id */
    PT_IPD_TYPE_ALL = 0xFF,
}PT_IPD_TYPE_E;/* ��δʹ�õ�Ԥ�� */

typedef enum
{
    PT_STAT_LOSE        = 0,    /* �������� */
    PT_STAT_PRI_LOSE    = 1,    /* ������ʧ */
    PT_STAT_SEC_LOSE    = 2,    /* ������ʧ */
    PT_STAT_NORMAL      = 3,    /* ���� */
} PT_STRM_STAT_E;


typedef struct
{
    sint32 support;
    uint32 devid;
    sint32 port;
} PT_IPC_PROTOCOL_S;

typedef struct
{
    uint32 devid;                   /* �豸id��(��ipc_id��nvd_idͳ��) */
    uint32 ipd_type;                /* �豸����PT_IPD_TYPE_E,֧��PT_IPD_TYPE_IPC|PT_IPD_TYPE_NVR���ָ�ʽ */
    sint8  ip_addr[BUFF_SIZE_128];  /* ip addr*/
    sint8  mac_addr[BUFF_SIZE_32];  /* mac addr*/
    char vendor_name[BUFF_SIZE_32]; /*������(���豸���ֽ���н�������)*/
    char memo[BUFF_SIZE_32];        /* �豸˵�� (����Э���������Ľ������ǰ׺ΪHBxxxx,DVRxxxx��DVR�����˴���)*/
    sint32 authority;               /* �˺������Ƿ���̽��ɹ�,�����̽��ɹ�,���ʱ���Բ��������˺�����  */
    PT_RES_S resolution;            /* ���������豸�ֱ���,�豸����ΪIPC��̽��ɹ�ʱ��Ч */
    PT_IPC_PROTOCOL_S protocol[IPC_IPDEV_PROTOCOL_MAX]; /* �豸֧��������Э��*/
} PT_IPC_DEVSEARCHCONTENT_S;

typedef struct
{
    sint32 count; /*�ѵ���IPC�豸����*/
    PT_IPC_DEVSEARCHCONTENT_S ipc_devsearch_content[IPC_SEARCH_MAX_NUM]; /* �ѵ���IPC�豸����*/
} PT_IPC_DEVSEARCHINFO_S,PT_IPD_DEVSEARCHINFO_S;

typedef struct
{
    char manufacture[BUFF_SIZE_32]; /* ������ */
    char model[BUFF_SIZE_32];       /* �ͺ�  */
    char firmware_ver[BUFF_SIZE_32];/* �̼��汾 */
}PT_IPC_INFO_S;

typedef struct
{
    PT_STRM_STAT_E dev_stream;  /*��״̬*/
    PT_STRM_STAT_E pic_stream;   /* ͼƬ��״̬ PT_STAT_LOSE:��ʧ PT_STAT_NORMAL:����*/
} PT_IPC_DEVSTATUS_S, *PPT_IPC_DEVSTATUS_S;

/* �豸��½��Ϣ */
typedef struct
{
    uint32  devid;                  /* �豸id��(��ipc_id��nvd_idͳ��) */
    uint32  protocol;               /* Э��,�Զ����ʱ��Ч  */
    sint32  poe_ch;                 /* ��ӵ��Ƿ�Ϊpoeͨ�� 0--��1--��*/
    sint32  port;                   /* �˿ں� */
    char    username[BUFF_SIZE_32]; /* ipc�û��� */
    char    password[BUFF_SIZE_32]; /* ipc������֤���� */
    char    ipaddr[BUFF_SIZE_128];  /* IP ��ַ */
}PT_IPD_LOGIN_S;

/* nvd�豸��½��Ϣ���� */
typedef struct
{
    sint32 count;
    PT_IPD_LOGIN_S login[PT_MAX_NVD];
}PT_NVD_CFG_S;

/* ��ȡNVR������Ϣ */
typedef struct
{
    sint32 status;                  /* ��½�Ƿ�ɹ�״̬ */
    sint32 video_no;
    char device_name[BUFF_SIZE_32];
    char manufacture[BUFF_SIZE_32]; /* ������ */
    char model[BUFF_SIZE_32];       /* �ͺ�  */
    char firmware_ver[BUFF_SIZE_32];/* �̼��汾 */
    PT_VOSPLIT_S split;             /* ����ͨ��������ʽ */
}PT_NVD_INFO_S;

typedef struct
{
    uint32 nvd_id;
    sint32 channel;                 /* ��nvr��ӵ��ĸ�ͨ�� */
    char ipaddr[BUFF_SIZE_32];
    char dev_name[BUFF_SIZE_32];
    char username[BUFF_SIZE_32];
    char password[BUFF_SIZE_32];    
}PT_ALLOT_NVD_S;

/*
* ������Ϣ,ÿ��ipc��Ӧ��nvr��Ϣ
*/
typedef struct
{
    uint32 ipc_id;
    uint32 authority;
    uint32 port;
    uint32 nvd_cnt;                 /* ͬʱ������nvr���,Ϊ0��ʾδ��NVR��� */
    char ipaddr[BUFF_SIZE_32];
    char osd_name[BUFF_SIZE_32];
    PT_RES_S resolution;            /* ipc�������ֱ��� */
    PT_ALLOT_NVD_S allot_nvd[PT_MAX_ALLOT_NVD];  /* �����nvr��ӵ���Ϣ�б�*/
}PT_ALLOT_IPC_S;

typedef struct
{
    sint32 view_mode;   /* PT_IPD_MODE_E */
    sint32 nvd_idx;     /* ��view_mode��PT_IPD_MODE_NVD�л���PT_IPD_MODE_IPCģʽʱ,���֪nvd���� */
}PT_NVD_VIEW_MODE_S;

/* �Ͻṹ�岻��ʹ�� */
typedef struct
{
    sint32      ch;                 /* IPͨ��ͨ���� */
    sint32      poech;              /* �Ƿ�ΪPOE�豸,0��,1��(���ʱ��ֵΪ0) */
    uint32      devid;              /* �豸id,�Զ����ʱ��Ч */
    uint32      protocol;           /* Э��,�Զ����ʱ��Ч  */
    char        usrname[32];        /* ipc�û��� */
    char        pwd[32];            /* ipc������֤���� */
    char        ip_addr[MAX_IPADDR_STR_LEN];       /* IP ��ַ */
    sint32      port;               /* �˿ں� */
    sint32      dev_ch_num;         /* �豸ͨ���� */
    sint32      dev_ch;             /* �豸ͨ��(������ţ���0��ʼ) */
    sint32      ch_list_idx;        /*ָ��λ�����IPCʱ������ǰ������λ����������ָ��λ��ʱ��-1*/
    char        vendor_name[32];    /*������*/
    char        memo[32];           /*�豸�ͺ�*/
    char        firmware_ver[32];   /*ipc�̼��汾��*/
} PT_IPC_CONFIG_S, *PPT_IPC_CONFIG_S;

typedef struct
{
    sint32      ch;                 /* ����ͨ�� */
    char        ch_name[32];        /* ͨ������*/
    char        dev_name[32];       /* �豸����*/
    uint8       mac_addr[8];        /* MAC��ַ */
    uint32      dev_resol;          /* �豸�ֱ��� PT_RESOLUTION_E*/
    char        dev_softver[32];    /* �豸����汾�� */
    uint8       dev_type;           /* �豸����*/
    uint8       reserve[3];           /* ����λ*/
} PT_IPC_DEVINFO_S, *PPT_IPC_DEVINFO_S;

typedef struct
{
    sint32 ptz_support;             /* ipc������̨֧�� */
    sint32 motion_support;          /* �ƶ�����֧�� */
    sint32 snap_support;            /* ץͼ֧��(����ץͼԤ��,ץͼ¼��) */
    sint32 sensor_support;          /* ̽ͷ��������֧�� */
    sint32 sensorout_support;       /* ̽ͷ�������֧�� */
} PT_IPC_CAPABILITIES_S;

typedef struct
{
    sint32      ch;                 /* ����ͨ�� */
    char        ip_addr[MAX_IPADDR_STR_LEN];       /* IP ��ַ */
    uint8       subnet_mask[8];     /* �������� */
    uint8       gateway[8];         /* ���� */
    uint8       dns_server[8];      /* dns������ */
    sint32      port;               /* �˿ں� */
    sint32      http_port;          /* http�˿ں� */
} PT_IPC_NETWORKCFG_S, *PPT_IPC_NETWORKCFG_S;

typedef struct
{
    sint32 count;
    PT_RES_S list[PT_MAX_LIST];
} PT_RES_LIST_S;

typedef struct
{
    PT_RES_LIST_S pri_res;  /*IPC�������ֱ��� PT_RESOLUTION_E*/
    PT_RES_LIST_S sec_res;  /*IPC�������ֱ��� PT_RESOLUTION_E*/
} PT_IPC_COMMONRANGE_S, *PPT_IPC_COMMONRANGE_S; //ͨ�÷�Χ

typedef enum 
{ 
    PT__VideoEncoding__H264 = 0,  
    PT__VideoEncoding__H265 = 1,
    PT__VideoEncoding__JPEG = 2, 
    PT__VideoEncoding__MPEG4 = 3, 
    PT__VideoEncoding__MAX,
} PT_VIDEO_ENCODING_E;
typedef struct
{
    PT_RES_S resolution;            /* PT_RES_S �������*/

    PT_RANGE_S pri_frame_rate;      /*IPC������֡��*/
    PT_RANGE_S pri_bit_rate;        /*IPC����������*/
    PT_RANGE_S pri_quality;         /* ͼ��������Χ */
    PT_LIST_S  pri_encode;          /*���������б�PT_VIDEO_ENCODING_E*/

    PT_RANGE_S sec_frame_rate;      /*IPC������֡��*/
    PT_RANGE_S sec_bit_rate;        /*IPC����������*/
    PT_RANGE_S sec_quality;
    PT_LIST_S  sec_encode;          /*���������б�PT_VIDEO_ENCODING_E*/
} PT_IPC_ENCPARAM_RANGE_S, *PPT_IPC_ENCPARAM_RANGE_S;

typedef enum
{
    PT_IPC_NOT_ADD = 0,         /* ͨ��δ����豸 */
    PT_IPC_ADDED = 1,           /* ͨ��������豸 */
    PT_IPC_POE_CONNECT = 2,     /* POE�豸���� */
    PT_IPC_POE_DISCONNECT = 3,  /* POE�豸�Ͽ� */
} PT_CH_STAT_E;

typedef struct
{
    uint32 channel;
    sint32 ch_stat;     /* PT_CH_STAT_E */
} PT_CH_STATUS_S;

typedef enum
{
    PT_IPC_TEST_CONNECT = 1,
    PT_IPC_TEST_PROTOCAL = 2,
    PT_IPC_TEST_STREAM  = 3,
    PT_IPC_TEST_DETAIL  = 4,
} PT_IPC_TEST_STEP_E;

typedef enum
{
    PT_RESULT_TEST_FAILED   = 0,
    PT_RESULT_TEST_PASSED   = 1,
    PT_RESULT_CONNECT_FAILED = 11,  /*���粻ͨ ����:(1)����Դ (2)����������� */
    PT_RESULT_AUTH_FAILED   = 12,   /*�˺�������� ����:(1)�û���������� */
    PT_RESULT_NO_RESPONSE   = 13,   /*�豸����Ӧ ����:(1)ȷ���豸 (2)ȷ��֧��onvif (3)��������ipc */
    PT_RESULT_NOT_SUPPORT   = 14,   /*�豸��֧�� ����: (1)���Ը�λipc (2)��ѯ�豸���̽�� */
    PT_RESULT_STREAM_ERROR  = 15,   /* �������򿪴��� ����:(1)��鱻�����豸���� (2)��������ipc */
    PT_RESULT_RES_ERROR     = 16,   /* �ֱ���̫�߲�֧�� ����:(1)�ֱ��ʸ߲�֧��,���ͷֱ��� */
} PT_IPC_TEST_RESULT_E;

typedef struct
{
    sint32 step;    /* PT_IPC_TEST_STEP_E */
    sint32 result;  /* PT_IPC_TEST_RESULT_E */
} PT_IPC_TEST_S;

typedef struct
{
    sint32 section;     //���״̬0-δ���,1-��ϳɹ�,2-���ʧ��*//*˵�������ڹ��������ʱ��Ҫ���ѡ����������������ϣ����Ҫ��ÿ�����������״̬����˵��
    char server[64];    //��������ַ
} PT_NET_DIAGNOSIS_SERVER_S;//��ϵĹ�������ַ

typedef enum 
{
	PT_NET_DIAGNOSIS_LAN_START, /*��ʼ���������*/
	PT_NNET_DIAGNOSIS_LAN_END, /*��������Ͻ�������ϵĽ���뿴DIAGNOSIS_RESULT_S �ṹ���result �ֶ�*/
	PT_NNET_DIAGNOSIS_NET_START,/* ��ʼ���������*/
	PT_NNET_DIAGNOSIS_NET_END,/* ��������Ͻ�������ϵĽ���뿴DIAGNOSIS_RESULT_S �ṹ���result �ֶ�*/
	PT_NNET_DIAGNOSIS_END, /*ȫ����Ͻ���*/
	PT_NNET_DIAGNOSIS_STOP, /*����ж�*/
} PT_NET_DIAGNOSIS_STEP_E; /*��ϲ���*/

typedef enum 
{
	PT_NET_DIAGNOSIS_ETH_DOWN=0, /*����δ���ӣ�����ʾ����߶Ͽ�����ȷ�������Ƿ��������ϣ�*/
	PT_NET_DIAGNOSIS_NET_OK, /*��������������*/
	PT_NET_DIAGNOSIS_NET_ERR, /*����������ʧ��*/
	PT_NET_DIAGNOSIS_LAN_OK,/*��������������*/
	PT_NET_DIAGNOSIS_LAN_ERR,/*����������ʧ��*/
	PT_NET_DIAGNOSIS_REPAIR_ERR=5,/*�޸�ʧ��,��ȷ��DHCP�������Ƿ�������������*/
	PT_NET_DIAGNOSIS_REPAIR_IP_ERR,/*�޸�ʧ�ܣ�ip��ַ���Զ���ȡ�����ز���ͬһ�����ϣ����޸�ip�����أ�dns*/
	                        /*˵��������ʾ����ֶ�����ip�ĳ��������Ϊ�Զ���ȡip���򲻻��д���ʾ*/
	PT_NET_DIAGNOSIS_REPAIR_ROUTE_ERR,/*�޸�ʧ�ܣ���ȷ��DVR��·����֮��������Ƿ�����*/
	PT_NET_DIAGNOSIS_REPAIR_DNS_ERR,/*�޸�ʧ�ܣ�DNS���������ô������޸�DNS*/
	PT_NET_DIAGNOSIS_REPAIR_NET_ERR,/*�޸�ʧ�ܣ���ȷ��·�����Ƿ�������������*/
	PT_NET_DIAGNOSIS_REPAIR_GW_ERR,/*�޸�ʧ�ܣ���ȷ����������ҳ���ϵ������Ƿ���������*/
	PT_NET_DIAGNOSIS_IP_CONFLICT,/*ip��ͻ*/
} PT_NET_DIAGNOSIS_STAT_E; /*��Ͻ��*/

typedef struct
{
    sint32 step;        //��ϲ���:0-��ʼ���������,1-��������Ͻ���,2-��ʼ���������,3-��������Ͻ���,4-ȫ����Ͻ����������ӦNET_DIAGNOSIS_STEP_E��
    sint32 result;      //��Ͻ������GUI��ʾ���Ͻ���ʱ�����ֶβ������壬NET_DIAGNOSIS_STAT_E
    PT_NET_DIAGNOSIS_SERVER_S server[3];    //��������������
} PT_NET_DIAGNOSIS_RESULT_S;                //��ϻص��ṹ��

typedef struct
{
    sint32 type;        /* �������� PT_STREAMTYPE_E */
    void * user_data;   /* �û����ݵ��׵�ַ(������ʱ��ԭ���ص���ȥ) */
    sint32 data_size;   /* �û����ݳ���(��ص���ȥ) */
    sint32 ipv4;        /* ip��ַ(��ѡ,��������) */
    sint32 flag;        /* ƽ̨��ʶ(�� *(sint32 *)"rtmp"��),ͬmac��ͬflag,���ò�ͬ�̷߳��� */
    char   macstr[32];  /* �����豸��mac��ַ,�û������ʶ,�ַ���,��"E4:7D:5A:0B:DB:81" */
    PNETDATACALLBACK datacb; /* ע�����ݻص����� */
} PT_STRM_REQUEST_S;

typedef struct
{
    uint64 running_sec; // ��������ʱ�� s
    uint32 port_power; // ��ȡ����port�ڹ���mA*V
} PT_POECTRL_POWER_STAT_PORT_S;

typedef struct
{
    PT_POECTRL_POWER_STAT_PORT_S port_params[PT_MAX_POE_NUM]; // �˿ڲ���
    uint32 total_power; // ��ȡ��������port���ܹ���mA*V
} PT_POECTRL_POWER_STAT_S, *PPT_POECTRL_POWER_STAT_S;

typedef struct
{
    uint32 max_bitrate;     /* ϵͳ֧�ֵ��������*/
    uint32 total_bitrate;   /* ϵͳ��ǰ�������*/
} PT_BITRATE_PARAM, *PPT_BITRATE_PARAM;

typedef enum
{
    PT_OUTPUT_MODE_STANDARD,    /* ��׼ */
    PT_OUTPUT_MODE_BRIGHT,      /* ���� */
    PT_OUTPUT_MODE_SOFT,        /* ��� */
    PT_OUTPUT_MODE_VIVID,       /* ���� */
    PT_OUTPUT_MODE_SHARP,       /* ���� */
    PT_OUTPUT_MODE_BUTT
} PT_VO_OUTPUT_MODE_E;

typedef enum
{
    PT_AO_DEV_NORMAL,   /* ͨ����Ƶ��� */
    PT_AO_DEV_HDMI,     /* HDMI��Ƶ��� */
    PT_AO_DEV_ALL,      /* ������Ƶ��� */
    PT_AO_DEV_BUTT
} PT_AO_DEV_E;



#define  PT_MAX_UART_DEV_NUM  (4)
typedef struct
{
   uint32 uart_dev_no;
   char   uart_dev_type[32];
   char   uart_dev_name[32];
   uint16 full_duplex_support;//ȫ˫��
   uint16 half_duplex_support;//��˫��
}PT_CFG_UART_DEV_PARA, *PPT_CFG_UART_DEV_PARA;
typedef struct
{
    uint32 dev_count;
    PT_CFG_UART_DEV_PARA dev_list[PT_MAX_UART_DEV_NUM];
}PT_CFG_UART_DEV_LIST, *PPT_CFG_UART_DEV_LIST;
#endif

