/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:这是一个HTTP协议的客户端程序
 * History:
 * *************************************************************/
#include "common.h"

/***************************************************************************
 * Description:得到文件的属性信息
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
 * Description:递归的打印所有目录文件的中文件信息
 * Input :dir-文件的路径 depth-打印的时候文件的缩进
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
			} /* 不对隐藏文件进行处理 */
			/* 获取文件属性信息并打印 */
			sprintf(subDir,"./%s",entry->d_name);
			getFileAttr(entry, subDir, fileAttr);
			trace(DEBUG,"%*s%s/ %s\n", depth, "", entry->d_name, fileAttr);
			showDirAttr(entry->d_name, depth+3); /* 递归的读取子目录文件 */
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
 * Description：读取配置文件，获取http服务器端口号
 * Input path：配置文件路径
 * Output port：端口号
 * Return：0-成功 -1-失败
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
 * Description：检测目标文件是否可读可写
 * Input file：需要检测的文件
 * Return：0-可读 1-可写 -1-超时或错误
 * *****************************************************/
sint32 is_read_write(const sint32 *file) 
{
	sint32 ret = 0;
	struct pollfd fds[1];
	memset(fds, '\0', sizeof(struct pollfd) * 1);
	fds[0].fd = (*file);
	fds[0].events = (POLLIN | POLLOUT);
	ret = poll(fds, 1, 3000); //1000毫秒的超时时间
	if(ret <= 0) //超时或出错
		return -1;
	if(fds[0].revents & POLLIN) //可读
		return 0;
	else if(fds[0].revents & POLLOUT) //可写
		return 1;

	return -1;
}

/*
 * 函数功能说明：发送数据
 * 输入参数：需要发送的数据帧
 * 输出参数：
 * 函数返回值：
 * */
/******************************************************************************
 * Description：将数据写到目标文件中
 * Input file：目标文件
 * Input data：需要写入文件的数据
 * Input size：数据的大小
 * Return：0-成功 -1-失败
 * *****************************************************************************/
sint32 send_data(const sint32 *file, const void *data, const sint32 size)
{
	if((*file < 0) || (size <= 0))
	{
		return -1;
	}

	sint32 ret = 0;

	/*检测文件是否可写*/
	if(1 != is_read_write(file))
	{
		//trace(ERROR, "[%s]:the targer file cannot be written! LINE:%d\n", __func__, __LINE__);
		return -1;
	}
	/*发送数据*/
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
 * Description：从目标文件上读取数据
 * Input file：需要读取的文件
 * Input size：缓存去区的大小
 * Output data：读取到的数据
 * Return：-1:出错 !=-1:读取到的数据帧的长度
 * *****************************************************************************/
sint32 read_data(const sint32 *file, void *data, sint32 size)
{
	if((*file < 0) || (size <= 0))
		return -1;

	sint32 ret = 0;
	
	/*检测文件是否可读*/
	if(0 != is_read_write(file)) 
	{
		//trace(ERROR, "[%s]:the targer file cannot read! file=%d LINE:%d\n", __func__, (*file), __LINE__);
		return -1;
	}
	/*读取文件中的数据*/
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
 * Description：检查目标数据帧
 * Input buffer：需要进行检测的数据帧
 * Input attr：数据帧的属性描述
 * Return：0-成功 -1-未检测到头 -2-未检测到尾 -3-未检测到特殊的字符串  -4-数据帧的长度不够
 * *****************************************************************************/
sint32 packet_check(const void *buffer, PACKET_ATTR_S *attr)
{
	switch(attr->attr)
	{
	case PACKET_ATTR_HEADANDTAIL_E: //head and tail
		if(NULL == strstr(buffer, attr->head))
			return PACKET_ATTR_HEAD_E; //未检测到头
		if(NULL == strstr(buffer, attr->tail))
			return PACKET_ATTR_TAIL_E; //未检测到尾
		break;
	case PACKET_ATTR_HEAD_E: //only the head
		if(NULL == strstr(buffer, attr->tail))
			return  PACKET_ATTR_HEAD_E; //未检测到头
		break;
	case PACKET_ATTR_SPECIAL_E: //only special string 
		if(NULL == strstr(buffer, attr->special))
			return PACKET_ATTR_SPECIAL_E; //未检测带特殊的字符串
		break;
	case PACKET_ATTR_LEN_E: //fixed length
		if(attr->len > strlen(buffer))
			return PACKET_ATTR_LEN_E; //长度不够
		break;
	default:
		break;
	}
	return 0;
}


