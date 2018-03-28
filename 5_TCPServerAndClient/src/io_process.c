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

/***************************************************************************
 * Description:�õ��ļ���������Ϣ
 ****************************************************************************/
int getFileAttr(struct dirent *entry, char *filePath, char* dest)
{
	char buffer[512] = {0}, s_time[32] = {0}, m_time[32] = {0}, c_time[32] = {0};
	struct stat attr;
	if(0 > (stat(filePath, &attr))){
		return -1;
	}
	time_utoc((attr.st_atime), s_time, 0);
	time_utoc((attr.st_mtime), m_time, 0);
	time_utoc((attr.st_ctime), c_time, 0);
	sprintf(buffer, "no=%lu name:%s type=%d", (entry->d_ino), (entry->d_name ), (int)(entry->d_type));
	//sprintf(dest, "attr=%s no:%lu size=%ld st_atime=%ld st_mtime:%ld st_ctime=%ld", buffer, (attr.st_ino), (attr.st_size), (attr.st_atime), (attr.st_mtime), (attr.st_ctime));
	sprintf(dest, "attr=%s no:%lu size=%ld byte st_atime=%s st_mtime:%s st_ctime=%s", buffer, (attr.st_ino), (attr.st_size), s_time, m_time, c_time);

	return 0;
}

/*****************************************************************************
 * Description:�ݹ�Ĵ�ӡ����Ŀ¼�ļ������ļ���Ϣ
 * Input :dir-�ļ���·�� depth-��ӡ��ʱ���ļ�������
 *****************************************************************************/
void showDirAttr(char *dir, int depth)
{
	char fileAttr[1024] = {0}, subDir[256] = {0};
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if ((dp = opendir(dir)) == NULL) {
		trace(ERROR, "[%s]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
		return ;
	}

	chdir(dir);
	while ((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..")) == 0 ){
				continue;
			} /* ���������ļ����д��� */
			/* ��ȡ�ļ�������Ϣ����ӡ */
			sprintf(subDir,"./%s",entry->d_name);
			getFileAttr(entry, subDir, fileAttr);
			trace(DEBUG,"%*s%s/ %s\n", depth, "", entry->d_name, fileAttr);
			showDirAttr(entry->d_name, depth+3); /* �ݹ�Ķ�ȡ��Ŀ¼�ļ� */
		} else{
			sprintf(subDir,"./%s",entry->d_name);
			getFileAttr(entry, subDir, fileAttr);
			trace(DEBUG,"%*s%s/ %s\n", depth, "", entry->d_name, fileAttr);
		}
	}
	chdir("..");
	closedir(dp);
}

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

#if 1
/***************************************************
* Brief:将输入的文件拆分成两个文件
* Input
*****************************************************/
int demo_cave_file(const char *inpath, const char *outpath, const int begin, const int size){
	int fCount = 0, file_size = 0, ret = 0, buflen = 1024;
	FILE *fpin = NULL, *fpout = NULL;
	char buffer[1025] = {0}, newPath[256] = {0};

	fpin = fopen(inpath, "r");
	if(NULL == fpin){
		printf("[%s]:info=%s inpath=%s LINE:%d\n", __func__, strerror(errno), inpath, __LINE__);
		return -1;
	}
	fpout = fopen(outpath, "a+");
	if(NULL == fpout){
		printf("[%s]:info=%s outpath=%s LINE:%d\n", __func__, strerror(errno), outpath, __LINE__);
		return -1;
	}

	if(0>fseek(fpin, begin, SEEK_SET)){
		printf("[%s]:info=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
	}

	while(1){
		//usleep(1000*1000);
		ret = fread(buffer, 1, buflen, fpin);
		if(0 >= ret){
			printf("[%s]:ret=%d info=%s LINE:%d\n", __func__, ret, strerror(errno), __LINE__);
			break;
		}
		printf("[%s]:ret=%d line:%d\n", __func__, ret, __LINE__);
		file_size += ret;	
		ret = fwrite(buffer, 1, ret, fpout);
		if(0 >= ret){
			printf("[%s]:ret=%d info=%s LINE:%d\n", __func__, ret, strerror(errno), __LINE__);
			break;
		}
		
		if(size>file_size){
			continue;
		}
		printf("[%s]:file_size=%d  size=%d line:%d\n", __func__, file_size, size, __LINE__);
		fCount++;
		sprintf(newPath, "%s_%d", outpath, fCount);
		printf("[%s][Debug]:create new file path=%s line:%d\n", __func__, newPath, __LINE__);
		fclose(fpout);
		fpout = NULL;
		fpout = fopen(newPath, "a+");
		if(NULL == fpout){
			printf("[%s]:info=%s outpath=%s LINE:%d\n", __func__, strerror(errno), outpath, __LINE__);
			return -1;
		}
		if(0>fseek(fpin, file_size, SEEK_SET)){
			printf("[%s]:info=%s LINE:%d\n", __func__, strerror(errno), __LINE__);
			return -1;
		}
		file_size = 0;
	}
	

	return 0;
}


int tttt()
{
	char inpath[64] = {"./src.txt"};
	char outpath[64] = {"./out.txt"};
	int begin = 0;
	int size = 1024*1024*9;
	
	demo_cave_file(inpath, outpath, begin, size);
	return 0;
}
#endif

