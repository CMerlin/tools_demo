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

/****************************************************************************************************
* Description:内存中查找指定的字符串
****************************************************************************************************/
char* memstr(char* full_data, int full_data_len, char* substr)  
{  
    if (full_data == NULL || full_data_len <= 0 || substr == NULL) {  
        return NULL;  
    }  
  
    if (*substr == '\0') {  
        return NULL;  
    }  
  
    int sublen = strlen(substr);  
  
    int i;  
    char* cur = full_data;  
    int last_possible = full_data_len - sublen + 1;  
    for (i = 0; i < last_possible; i++) {  
        if (*cur == *substr) {  
            //assert(full_data_len - i >= sublen);  
            if (memcmp(cur, substr, sublen) == 0) {  
                //found  
                return cur;  
            }  
        }  
        cur++;  
    }  
  
    return NULL;  
} 

/******************************************************************************************************
* Description:��ʽ��ʱ�䣬��time_t���͵�ʱ�����ַ���
* input src_time:��Ҫ���и�ʽ����ʱ��
* input rank:1-��ȷ��΢�� 0-��ȷ������
* outPut dest_time:�Ѿ���ʽ���õ�ʱ��
********************************************************************************************************/
int time_utoc(time_t src_time, char *dest_time, int rank)
{
	struct timeval tv;
	struct timezone tz;
	struct tm *tm = localtime(&src_time);

	gettimeofday(&tv, &tz);
	if(1==rank){
		sprintf(dest_time, "%d%02d%02d-%02d:%02d:%02d.%ld",
			tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
	}
	else if(0 == rank){
		sprintf(dest_time, "%d%02d%02d-%02d:%02d:%02d",
			tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
	}

	return 0;
}

