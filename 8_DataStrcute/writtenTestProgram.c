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

 /* brief:冒泡排序(一次比较两个相邻的元素，如果他们的顺序错误就将它们交换过来 n2) */
int bubble_sort(int *data, int n){
	int i = 0, j = 0, temp = 0;
	for(i=0; i<n-1; i++){
		for(j=0; j<n-1-i; j++){
			if(data[j]>data[j+1]){
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}	
	}
	return 0;
}
/* brief:选择排序(从等待排序数据中找到最大或是最小的的那个数放到首位 n2) */
int select_sort(int *data, int n){
	int i = 0, j = 0, min = 0, temp = 0;

	for(i=0; i<n-1; i++){
		min = i;
		for(j=i+1; j<n; j++){
			if(data[min]>data[j]){ /*升序*/
				//if(data[min]<data[j]){ /*降序*/
				min = j;
			}
		}
		if(min!= i){
			temp = data[min];
			data[min] = data[i];
			data[i] = temp;
		}
	}
	return 0;
}

/*brif:快速排序*/
void first_sort(int *a, int left, int right)
{
    if(left >= right){
        return ;
    }
    int i = left;
    int j = right;
    int key = a[left];
     
    while(i < j)                               /*控制在当组内寻找一遍*/
    {
        while(i < j && key <= a[j]){
            j--;
        }
        a[i] = a[j];
        while(i < j && key >= a[i]){
            i++;
        }
        a[j] = a[i];
    }
     
    a[i] = key;
    first_sort(a, left, i - 1);
    first_sort(a, i + 1, right);
}

int main(int argc, const char *argv[])
{
#if 0
	int ret = 0;
	char str[] = {"1 2 3 4 5 6 7"};
	printf("[%s]:str=%s line:%d\n", __func__, str, __LINE__);
	ret = strDBlank(str);
	printf("[%s]:ret=%d str=%s line:%d\n", __func__, ret, str, __LINE__);
#endif

#if 1
	int i = 0;
	int data[6] = {6, 1, 5, 3, 1, 2};
	//bubble_sort(data, 6);
	//select_sort(data, 6);
	first_sort(data, 0, 5);
	for(i=0; i<6; i++){
		printf("%d ", data[i]);
	}
	printf("\n");
	return 0;

#endif
	return 0;
}
