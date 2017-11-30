/*********************************************************************************************
 * Description:一些笔试中会编写的测试程序
 * name:merlin time:2017-11-30
 * *******************************************************************************************/

#include <stdio.h>
#include <string.h>

/*brif:删除字符串中的空格，返回空格的数目*/
int strDBlank(char*pStr) 
{
	int count = 0;
	char *ptemp = pStr; 

	while (*pStr != '\0') 
	{ 
		if (*pStr != ' '){ 
			*ptemp++ = *pStr; 
		}
		else{
			count++;
		}
		++pStr;
	} 
	*ptemp = '\0'; 
	return count;
} 



int main(int argc, const char *argv[])
{
#if 1
	int ret = 0;
	char str[] = {"1 2 3 4 5 6 7"};
	printf("[%s]:str=%s line:%d\n", __func__, str, __LINE__);
	ret = strDBlank(str);
	printf("[%s]:ret=%d str=%s line:%d\n", __func__, ret, str, __LINE__);
#endif
	
	return 0;
}
