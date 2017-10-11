/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:è¿™æ˜¯ä¸€ä¸ªHTTPåè®®çš„å®¢æˆ·ç«¯ç¨‹åº
 * History:
 * *************************************************************/
#include "common.h"

/****************************************************************************************************
* Description:å†…å­˜ä¸­æŸ¥æ‰¾æŒ‡å®šçš„å­—ç¬¦ä¸²
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
* Description:¸ñÊ½»¯Ê±¼ä£¬½«time_tÀàĞÍµÄÊ±¼ä±ä³É×Ö·û´®
* input src_time:ĞèÒª½øĞĞ¸ñÊ½»¯µÄÊ±¼ä
* input rank:1-¾«È·µ½Î¢Ãë 0-¾«È·µ½·ÖÖÓ
* outPut dest_time:ÒÑ¾­¸ñÊ½»¯ºÃµÄÊ±¼ä
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

