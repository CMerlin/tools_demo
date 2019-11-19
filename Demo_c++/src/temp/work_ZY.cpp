#include "print.h"

/****************************************************************************
* Brief:TS数据保存到文件中
******************************************************************************/
int writeTsData(uint8_t *data, int len){
        static FILE *pfile = NULL;
        char path[64] = {"/data/local/tmp/media.ts"};
        if(NULL == pfile){
                pfile = fopen(path, "a+");
                if(pfile == NULL){
                        ALOGD("[%s][merlin][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
                        printf("[%s][merlin][Error]:info=%s line:%d\n", __func__, strerror(errno), __LINE__);
                }
        }

        fwrite(data,len,1,pfile);
        //fclose(pfile);

        return 0;
}

/************************************************************************************
* Brief:获取音视频数据参数
* Out param vformat:获取到的视频参数
* Out param aformat:获取到的音频参数
*************************************************************************************/
int getVideoFromate(char *vformat, char *aformat){
	int count = 0;
	char buffer[1024] = {0}, path[64] = {"/data/local/tmp/merlin.file"};
	FILE *fpin = NULL;
		
	fpin = fopen(path, "r");
	if(NULL == fpin){
		//printf("[%s]:info=%s inpath=%s LINE:%d\n", __func__, strerror(errno), path, __LINE__);
		ALOGD("[%s]:info=%s inpath=%s LINE:%d\n", __func__, strerror(errno), path, __LINE__);
		return -1;
	}

	if(0 > fgets(buffer, 1024, fpin)){
		return 0;
	}
	char *p = NULL, *saveptr1 = NULL;
	for(p = strtok_r(buffer, ";", &saveptr1); p != NULL; p = strtok_r(NULL, ";", &saveptr1))
	{
		count++;
		if(NULL == saveptr1){
			break;
		}
		if(1==count){
			sprintf(vformat, "%s", p);			
		}else if(2==count){
			sprintf(aformat, "%s", p);
		}
		//printf("[%s][%d]: saveptr1=%s p=%s line:%d\n", __func__, count, saveptr1, p, __LINE__);
		ALOGD("[%s][%d]: saveptr1=%s p=%s line:%d\n", __func__, count, saveptr1, p, __LINE__);
	}
	fclose(fpin);
	fpin = NULL;
	
	return 0;
}


