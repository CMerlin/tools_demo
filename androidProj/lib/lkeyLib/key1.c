/*************************************************
* Brief:
***************************************************/
#include "lkey.h"

int func1(unsigned char* pstr){
	printf("[%s][%d]:pstr=%s\n", __func__, __LINE__, pstr);
	return 0;
}

int func2(unsigned char* pstr){
	printf("[%s][%d]:pstr=%s\n", __func__, __LINE__, pstr);
	return 0;
}



