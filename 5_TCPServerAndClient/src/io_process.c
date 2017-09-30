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
int getFileAttr(char *filePath, char* dest)
{
	 struct stat attr;
	if(0 > (stat(filePath, &attr))){
		return -1;
	}
	sprintf(dest, "no:%lu size=%ld st_atime=%ld st_mtime:%ld st_ctime=%ld", (attr.st_ino), (attr.st_size), (attr.st_atime), (attr.st_mtime), (attr.st_ctime));
	return 0;
}

/*****************************************************************************
 * Description:递归的打印所有目录文件的中文件信息
 * Input :一级目录文件的文件路径
 *****************************************************************************/
int showDirAttr(char *dirPath)
{
	DIR *pDir = NULL;
	struct dirent *ent = NULL;
	char subDir[1024] = {0}, buffer[1024] = {0}, fileAttr[1024] = {0};

	if(NULL == dirPath){
		return -1;
	}
	/* 打开目标文件 */
	pDir = opendir(dirPath);
	if(NULL == pDir){
		return -1;
	}
	trace(DEBUG, "[%s]:openDir=%s ************************* line:%d\n", __func__, dirPath, __LINE__);
	/* 读取所有的子文件 */
	while((ent = readdir(pDir))!=NULL)
	{
		/* 递归的处理目录文件 */
		if(ent->d_type & DT_DIR){
			if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0){
				continue; /* 不对隐藏文件进行处理 */
			}
			sprintf(subDir,"%s/%s",dirPath,ent->d_name);
			showDirAttr(dirPath);
		}
		else{
			sprintf(subDir,"%s/%s",dirPath,ent->d_name);
			getFileAttr(subDir, fileAttr);
			sprintf(buffer, "no=%lu name:%s type=%d attr=%s", (ent->d_ino), (ent->d_name ), (int)(ent->d_type), fileAttr);
			trace(DEBUG, "[%s]:%s line:%d\n", __func__, buffer,  __LINE__);
		}
	}

	return 0;
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


