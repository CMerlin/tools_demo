/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:����һ��HTTPЭ��Ŀͻ��˳���
 * History:
 * *************************************************************/
#include "common.h"

/******************************************************************************
 * Description����ȡ�����ļ�����ȡhttp�������˿ں�
 * Input path�������ļ�·��
 * Output port���˿ں�
 * Return��0-�ɹ� -1-ʧ��
 * *****************************************************************************/
sint32 get_config_info(void *path, sint32 *port)
{
	sint32 ret = 0;
	uint8 buffer[1024] = {0};

	ret = open(path, O_RDONLY);
	if(ret < 0)
	{
		trace(ERROR, "[%s]:open=%s LINE:%d\n", __func__,  strerror(errno),__LINE__);
		return -1;
	}

	while(1)
	{
		ret = read(ret, buffer, sizeof(buffer));
		if(ret <= 0)
			break;
		*port = atoi((char*)buffer);
		trace(TRACE, "[%s]:buffer=%s port=%d LINE:%d\n", __func__, buffer, (*port), __LINE__);	
	}

	return 0;
}

/*******************************************************
 * Description�����Ŀ���ļ��Ƿ�ɶ���д
 * Input file����Ҫ�����ļ�
 * Return��0-�ɶ� 1-��д -1-��ʱ�����
 * *****************************************************/
sint32 is_read_write(const sint32 *file) 
{
	sint32 ret = 0;
	struct pollfd fds[1];
	memset(fds, '\0', sizeof(struct pollfd) * 1);
	fds[0].fd = (*file);
	fds[0].events = (POLLIN | POLLOUT);
	ret = poll(fds, 1, 3000); //1000����ĳ�ʱʱ��
	if(ret <= 0) //��ʱ�����
		return -1;
	if(fds[0].revents & POLLIN) //�ɶ�
		return 0;
	else if(fds[0].revents & POLLOUT) //��д
		return 1;

	return -1;
}

/*
 * ��������˵������������
 * �����������Ҫ���͵�����֡
 * ���������
 * ��������ֵ��
 * */
/******************************************************************************
 * Description��������д��Ŀ���ļ���
 * Input file��Ŀ���ļ�
 * Input data����Ҫд���ļ�������
 * Input size�����ݵĴ�С
 * Return��0-�ɹ� -1-ʧ��
 * *****************************************************************************/
sint32 send_data(const sint32 *file, const void *data, const sint32 size)
{
	if((*file < 0) || (size <= 0))
	{
		return -1;
	}

	sint32 ret = 0;

	/*����ļ��Ƿ��д*/
	if(1 != is_read_write(file))
	{
		//trace(ERROR, "[%s]:the targer file cannot be written! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	/*��������*/
	tcflush(*file, TCIOFLUSH);
	ret = write(*file, data, size);
	//trace(DEBUG, "[%s]:[write:%d]:data=%s LINE:%d\n", __func__, ret, data, __LINE__);
	if(ret <= 0)
	{
		trace(ERROR, "[%s]:write=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	//tcflush(file, TCIOFLUSH);

	return ret;
}

/******************************************************************************
 * Description����Ŀ���ļ��϶�ȡ����
 * Input file����Ҫ��ȡ���ļ�
 * Input size������ȥ���Ĵ�С
 * Output data����ȡ��������
 * Return��-1:���� !=-1:��ȡ��������֡�ĳ���
 * *****************************************************************************/
sint32 read_data(const sint32 *file, void *data, sint32 size)
{
	if((*file < 0) || (size <= 0))
		return -1;

	sint32 ret = 0;
	
	/*����ļ��Ƿ�ɶ�*/
	if(0 != is_read_write(file)) 
	{
		//trace(ERROR, "[%s]:the targer file cannot read! file=%d LINE:%d\n", __func__, (*file), __LINE__);
		return -1;
	}
	/*��ȡ�ļ��е�����*/
	ret = read(*file, data, size);
	//trace(DEBUG, "[%s]:[read:%d] LINE:%d\n", __func__, ret, __LINE__);
	if(ret < 0)
	{
		trace(ERROR, "[%s]:read=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
		return -1;
	}
	//tcflush(*file, TCIOFLUSH);

	return ret;
}

/******************************************************************************
 * Description�����Ŀ������֡
 * Input buffer����Ҫ���м�������֡
 * Input attr������֡����������
 * Return��0-�ɹ� -1-δ��⵽ͷ -2-δ��⵽β -3-δ��⵽������ַ���  -4-����֡�ĳ��Ȳ���
 * *****************************************************************************/
sint32 packet_check(const void *buffer, PACKET_ATTR_S *attr)
{
	switch(attr->attr)
	{
	case PACKET_ATTR_HEADANDTAIL_E: //head and tail
		if(NULL == strstr(buffer, attr->head))
			return PACKET_ATTR_HEAD_E; //δ��⵽ͷ
		if(NULL == strstr(buffer, attr->tail))
			return PACKET_ATTR_TAIL_E; //δ��⵽β
		break;
	case PACKET_ATTR_HEAD_E: //only the head
		if(NULL == strstr(buffer, attr->tail))
			return  PACKET_ATTR_HEAD_E; //δ��⵽ͷ
		break;
	case PACKET_ATTR_SPECIAL_E: //only special string 
		if(NULL == strstr(buffer, attr->special))
			return PACKET_ATTR_SPECIAL_E; //δ����������ַ���
		break;
	case PACKET_ATTR_LEN_E: //fixed length
		if(attr->len > strlen(buffer))
			return PACKET_ATTR_LEN_E; //���Ȳ���
		break;
	default:
		break;
	}
	return 0;
}


