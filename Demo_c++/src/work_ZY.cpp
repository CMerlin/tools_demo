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


