/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:HTTP�ͻ��˵�ʵ��
 * History:
 * *************************************************************/

#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include "common.h"
#include "user_socket.h"
#include "xml_common.h"

/*�շ�������֡���ص�����*/
typedef enum
{
	PACKET_ATTR_MIN_E,
	PACKET_ATTR_HEADANDTAIL_E, //��ͷ��β
	PACKET_ATTR_HEAD_E, //��ͷ��β
	PACKET_ATTR_LEN_E, //�̶�����
	PACKET_ATTR_SPECIAL_E, //�����ַ���
	PACKET_ATTR_TAIL_E, //ֻ��β��
	PACKET_ATTR_MAX_E,
} PACKET_ATTR_E;

/*HTTP����*/
typedef enum
{
	HTTP_GET, //get
	HTTP_PUT, //put
	HTTP_POST, //post
} HTTP_METHODS_E;

/*���ݰ���������Ϣ*/
typedef struct _package_attr
{
	char head[32]; // ����֡��ͷ
	char tail[32]; //����֡��β
	char special[32]; //����֡�е�ĳЩ�����ַ���
	int len; //����֡�ĳ���
	int attr; //����֡������ PACKET_ATTR_E  1-��ͷ��β 2-��ͷ��β 3-�̶�����[��ͷ��β] 4-�����ַ���
} PACKET_ATTR_S, *PPACKET_ATTR_S;

/*HTTP����������ص���Ϣ*/
typedef enum
{
	KEEP_ALIVE, //������
	CLOSE, //������
} CONNECTION_E;

/*�豸�ı���������Ϣ*/
typedef struct _local_network_attr
{
	char ip[64]; //IP
	char gateway[64]; //����
	char mask[64]; //����Դ��
	char dns1[64]; //��ѡDND
	char dns2[64]; //����DNS
	char hwaddr[64]; //MAC��ַ
} SLOCAL_NETWORK_ATTR, *P_SLOCAL_NETWORK_ATTR;

/*HTTP�������ͷ���������*/
typedef struct _http_attr
{
	char name[64]; //�û���
	char password[64]; //����
	char ip[64]; //http Web�������˵ĵ�ַ����ʽ��192.168.xx.xx
	sint32 port; //�������Ӻ�Ķ˿ں�
	CONNECTION_E connection; //http�ͻ��˺ͷ������˵����ӷ�ʽ,���õ�ֵ�� CONNECTION_E
} HTTP_ATTR_S, *PHTTP_ATTR_S; 

/*�������ӵ�������Ϣ*/
typedef struct _network_attr_S
{
	int fd; //�ļ�������
	int connect; //����״̬
	CONNECTION_E type; //���ӷ�ʽ
	time_t btime; //�������ӿ�ʼ��ʱ��
	char ip[64]; //IP��ַ
	int port; //�˿ں�	
	int complete; //���ͺ��Ƿ�����˽���
} NETWORK_ATTR_S, *PNETWORK_ATTR_S;

/*���û��ȡhttp��ص�����*/
extern sint32 isapi_set_http_attr(HTTP_ATTR_S *attr);
extern sint32 isapi_get_http_attr(HTTP_ATTR_S *attr);
/*���û��ȡ��ǰHTTP��ͨ��״̬*/
extern sint32 isapi_get_connect_status(NETWORK_ATTR_S *attr);
extern sint32 isapi_set_connect_status(NETWORK_ATTR_S *attr);
/*httpͨ����صĽӿ�*/
extern sint32 retry_connect_server_block(NETWORK_ATTR_S *server);
extern sint32 read_write_process(NETWORK_ATTR_S *server, const void* src, void *dest, sint32 dest_size);
extern sint32 checkHttpData(const void *buffer);
extern sint32 send_receive_data(const void *tx_buffer, void *rx_buffer, const sint32 rx_len);
extern sint32 get_http_package(const void *url, const void *http_body, void *buffer, const int size);
extern sint32 create_http_package(HTTP_METHODS_E methods,  const void *url, const void *xml, void *buffer, const int buffer_len);
extern sint32 put_http_head(const void *url, void *buffer, const int size, const int body_len);
//extern int getXmlData(const void *src, uint8 *dest, int dest_size, uint8 *node_name);
//extern int getXmlDataFromHttp(const void *src, uint8 *dest, int dest_size);
extern sint32 http_package(HTTP_METHODS_E methods,  const void *url, const void *tx_data, void *rx_data, const int data_len);

#endif
