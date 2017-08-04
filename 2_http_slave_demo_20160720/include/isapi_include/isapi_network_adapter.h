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

#ifndef _ISAPI_NETWORKADAPTER_H_
#define _ISAPI_NETWORKADAPTER_H_

#include "isapi_adapter.h"
#include "sys_net.h"
#include "sys_netapi.h"
#include "config_usr.h"
#include "config.h"

typedef enum
{
    SINGLE  = 0,
    DUAL    = 1
} LIPVER_E;

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

typedef enum
{
    half = 0,
    full = 1
} DUPLEX_E;

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
    int id;
    IPADDR_S ip;
    DISCOVERY_S discovery;
    LINK_S link;
}NETWORK_DEVICE_INFO_S, *PNETWORK_DEVICE_INFO_S;

typedef struct
{
    NETWORK_DEVICE_INFO_S neti_list[2];
} NETWORK_DEVICE_INFOLIST_S, *PNETWORK_DEVICE_INFOLIST_S;

/********************************************************/

typedef struct
{
    char userName[MAX_STRING];
    char pwd[MAX_STRING];
    int  status;
    int  autologin;
} NETWORK_PPPOE_S, *PNETWORK_PPPOE_S;

typedef struct
{
    NETWORK_PPPOE_S pppoe_list[1];
} NETWORK_PPPOE_LIST_S, *PNETWORK_PPPOE_LIST_S;

/*DDNSList*******************************************************/
#if 0
typedef enum
{
    HANBANG = 0,
    ORAY,
    DYNDNS,
    NO_IP,
    MEIBU,
    FREEDNS
} PROVIDER_E;

typedef struct
{
    addrtype_e addr_type;
    char hname[32];
} DSERVER_ADDR_S, *PDSERVER_ADDR_S;

typedef struct
{
    int id;
    int enable;
    PROVIDER_E provider;
    DSERVER_ADDR_S serv_addr;
    int port;
    char domainame[32];
    char usr[32];
} NETWORK_DDNS_S, *PNETWORK_DDNS_S;

typedef struct
{
    NETWORK_DDNS_S ddns_list[1];
} NETWORK_DDNS_LIST_S, *PNETWORK_DDNS_LIST_S;
#else
typedef enum
{
    ISAPI_DDNS_HANBANG = 0,
    ISAPI_DDNS_ORAY,
    ISAPI_DDNS_DYNDNS,
    ISAPI_DDNS_NO_IP,
    ISAPI_DDNS_MEIBU,
    ISAPI_DDNS_FREEDNS
} DDNS_SERVER_E;

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
#endif

/*mailingList*******************************************************/

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

typedef struct
{
    NETWORK_SMTP_S mail_list[1];
} NETWORK_SMTPLIST_S, *PNETWORK_SMTPLIST_S;

/*UPnP*******************************************************/

typedef enum internalPort
{
    http = 1,
    admin = 2,
    rtsp = 3,
    https = 4

} interp_e;

#if 0
char interp_c[][16] =
{
    "http",
    "admin",
    "rtsp",
    "https"
};
#endif

typedef enum nipVersion
{
    v4 = 1,
    v6 = 2
} nipver_e;

typedef struct
{
    char rout_ip[20];            //·����ip
    char wan_ip[20];             //wan�˿ڵ�ַ
} NETWORK_UPNP_SEARCH;

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

//UPNP����
typedef struct
{
    uint32  upnp_en;                     // UPNP ʹ��
    uint16  pat_count;                   //ת���˿ڸ���
    uint16  status;                    //·��������
    NETWORK_PAT_UPNP_S  pat_info[MAX_PAT];   //ת���˿���Ϣ
    NETWORK_UPNP_SEARCH rout_info; //�����ӵ�·��������Ϣ
} NETWORK_UPNP_S, *PNETWORK_UPNP_S;


int network_get_device_info(NETWORK_DEVICE_INFO_S * net_param);
int network_set_device_info(NETWORK_DEVICE_INFO_S * net_param, WEB_CMD_INFO_S *webinfo);
int network_get_pppoe_info(NETWORK_PPPOE_S * pppoe_param);
int network_set_pppoe_info(NETWORK_PPPOE_S * pppoe_param, WEB_CMD_INFO_S *webinfo);
int network_get_smtp_info(NETWORK_SMTP_S * smtp_param);
int network_set_smtp_info(NETWORK_SMTP_S * smtp_param, WEB_CMD_INFO_S *webinfo);
int network_email_test(NETWORK_SMTP_S * smtp_param);
int network_get_ddns_info(NETWORK_DDNS_S * ddns_param);
int network_set_ddns_info(NETWORK_DDNS_S * ddns_param, WEB_CMD_INFO_S *webinfo);
int network_get_upnp_info(NETWORK_UPNP_S * upnp_param);
int network_set_upnp_info(NETWORK_UPNP_S * upnp_param, WEB_CMD_INFO_S *webinfo);

#endif
