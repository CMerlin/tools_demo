#ifndef _ISAPI_SYSTEM_ADAPTER_H_
#define _ISAPI_SYSTEM_ADAPTER_H_

#include "isapi_adapter.h"
#include "config_usr.h"
#include "config.h"
#include "sys_net.h"
#include "sys_netapi.h"

#define UPGRADE_TEMP_FILE	"/tmp/upgrade.bin"

#define MAX_DEVINFO_STR_LEN 32
#define MAX_IP_ADDR_LEN     64

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

#if 0
typedef struct
{
    uint16  autontp_enable;                     /* NTPУʱʹ�� */// ����ntp����,0- ������ ,1-��ʾ�Զ� ��2-��ʾ�ֶ�
    //uint16  ntp_mt;                     /* �ֶ�Уʱʹ�� */
    uint16 server_index;         // ������������
    char    ntp_host[MAX_IP_ADDR_LEN];   /* NTP���������� */
    uint32  ntp_port;               /* NTP�������˿� */
    uint16  ajust_period;               /* NTPУʱ����() */
    uint16 sync_unit;                   /* ���ڵ�λ��0-���� 1-Сʱ 2-�� 3-���� 4-��*/
    SYSTEM_TIME_S dev_time;        /* ����ʱ�� */
    SYSTEM_TIME_S set_time;        /* ����ʱ�� */
    uint16 syn_systime;             /* �뱾��ʱ��ͬ��ʹ�� */
    uint16 reserve;                 /* ����λ */
}SYSTEM_NTP_CFG_S;

typedef struct
{
    SYSTEM_NTP_CFG_S   ntp_set;            /* ntp���� */
    sint32           time_zone;            /* ʱ�� */
}SYSTEM_TIME_CFG_S, *PSYSTEM_TIME_CFG_S;
#else
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
    SYSTEM_TIME_S    dev_time;        /* ����ʱ�� */
}SYSTEM_TIME_CFG_S, *PSYSTEM_TIME_CFG_S;
#endif

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
    char   isRegular[32];
    sint32 splitSum;
    sint32 type;
}SYSTEM_ZERO_SPLIT_S, *PSYSTEM_ZERO_SPLIT_S;

typedef struct
{
    sint32              zeropb_support; //�Ƿ�֧����ͨ���ط� 0:��֧�� 1:֧��
    sint32              talk_support;	//�Ƿ�֧�ֶԽ� 0 --��֧��	1--֧�� 
    SYSTEM_ZERO_SPLIT_S zero_split;  //��ͨ�������ʽ SYSTEM_ZERO_SPLIT_E
}SYSTEM_DEVICE_SUPPORT_S, *PSYSTEM_DEVICE_SUPPORT_S;

sint32 system_set_device_reboot(int param);

sint32 system_set_device_reset(sint32 flag, WEB_CMD_INFO_S *webinfo);

sint32 system_get_device_info(SYSTEM_DEVICE_INFO_S * dev_info);

sint32 system_set_device_info(SYSTEM_DEVICE_INFO_S * dev_info, WEB_CMD_INFO_S *webinfo);

sint32 system_get_device_capabilities(SYSTEM_DEVICE_SUPPORT_S *device_support);

sint32 system_get_device_time(SYSTEM_TIME_CFG_S * time_cfg);

sint32 system_set_device_time(SYSTEM_TIME_CFG_S * time_cfg, WEB_CMD_INFO_S *webinfo);

sint32 system_set_io_inputs(int almin_num, SYSTEM_IO_INPUTLIST_S *inputlist, WEB_CMD_INFO_S *webinfo);

sint32 system_set_io_outputs(int almout_num, SYSTEM_IO_OUTPUTLIST_S *io_outputlist, WEB_CMD_INFO_S *webinfo);

#endif

