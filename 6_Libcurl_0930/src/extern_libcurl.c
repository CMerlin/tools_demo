/****************************************************************
 * Copyright(C), 2016, Hanbang Tech.Co.,Ltd
 * File Name:slave_http
 * Author:merlin
 * Version:v1
 * Data:20160613
 * Description:这是一个HTTP协议的客户端程序
 * History:
 * 编译：gcc resume.c -o resume –lcurl
 * *************************************************************/
#include "common.h"

//采用CURLOPT_RESUME_FROM_LARGE 实现文件断点续传功能
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include <curl/curl.h>

#if 1
//这个函数为CURLOPT_HEADERFUNCTION参数构造
/* 从http头部获取文件size*/
size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	int r;
	long len = 0;

	/* _snscanf() is Win32 specific */
	// r = _snscanf(ptr, size * nmemb, "Content-Length: %ld\n", &len);
	r = sscanf(ptr, "Content-Length: %ld\n", &len);
	if (r){
		*((long *) stream) = len;
	} /* Microsoft: we don't read the specs */

	return size * nmemb;
}

/* 保存下载文件 */
size_t wirtefunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	return fwrite(ptr, size, nmemb, stream);
}

/*读取上传文件 */
size_t readfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
	FILE *f = stream;
	size_t n;

	if (ferror(f))
		return CURL_READFUNC_ABORT;

	n = fread(ptr, size, nmemb, f) * size;

	return n;
}

// 下载 或者上传文件函数
/******************************************************************************************************
* Description:上传或是下载文件
* Input:
* Return:
******************************************************************************************************/
int download(CURL *curlhandle, const char * remotepath, const char * localpath, long timeout, long tries)
{
	FILE *f;
	curl_off_t local_file_len = -1 ;
	long filesize =0 ;

	CURLcode r = CURLE_GOT_NOTHING;
	//int c;
	struct stat file_info;
	int use_resume = 0;
	/* 得到本地文件大小 */
	//if(access(localpath,F_OK) ==0)

	//trace(ERROR, "[%s]:remotepath=%s line:%d\n", __func__, remotepath, __LINE__);
	//trace(ERROR, "[%s]:localpath=%s line:%d\n", __func__, localpath, __LINE__);

	printf("[%s]: ----------------------- line:%d\n", __func__, __LINE__);
	if(stat(localpath, &file_info) == 0) 
	{
		local_file_len =  file_info.st_size; /* 文件的大小 */
		use_resume  = 1;
	}
	//采用追加方式打开文件，便于实现文件断点续传工作
	f = fopen(localpath, "ab+"); 
	if (f == NULL) {
		perror(NULL);
		return 0;
	}
	//curl_easy_setopt(curlhandle, CURLOPT_UPLOAD, 1L);

	curl_easy_setopt(curlhandle, CURLOPT_URL, remotepath);
	curl_easy_setopt(curlhandle, CURLOPT_CONNECTTIMEOUT, timeout);  // 设置连接超时，单位秒
	//设置http 头部处理函数
	curl_easy_setopt(curlhandle, CURLOPT_HEADERFUNCTION, getcontentlengthfunc);
	curl_easy_setopt(curlhandle, CURLOPT_HEADERDATA, &filesize);
	// 设置文件续传的位置给libcurl
	curl_easy_setopt(curlhandle, CURLOPT_RESUME_FROM_LARGE, use_resume?local_file_len:0);
	curl_easy_setopt(curlhandle, CURLOPT_WRITEDATA, f);
	curl_easy_setopt(curlhandle, CURLOPT_WRITEFUNCTION, wirtefunc);

	//curl_easy_setopt(curlhandle, CURLOPT_READFUNCTION, readfunc);
	//curl_easy_setopt(curlhandle, CURLOPT_READDATA, f);
	curl_easy_setopt(curlhandle, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curlhandle, CURLOPT_VERBOSE, 1L);

	r = curl_easy_perform(curlhandle);

	fclose(f);

	if (r == CURLE_OK)
		return 1;
	else {
		fprintf(stderr, "%s\n", curl_easy_strerror(r));
		return 0;
	}
}

/*******************************************************************************************************
* Description:断点续传的例子(breakpoint resume)
*******************************************************************************************************/
int testBreakpointResume() {
	//int main(int argc, const char *argv[]){
	CURL *curlhandle = NULL;
	char src_url[1024] = {"https://www.baidu.com"}; /* 需要下载的文件的url */
	char local_path[1024] = {"./local_file"};

	curl_global_init(CURL_GLOBAL_ALL); /* 初始化libcurl库，多线程的时候一定要调用 */
	curlhandle = curl_easy_init(); /* 初始化curl指针 */

	//download(curlhandle, "ftp://user:pass@host/path/file", "C:\\file", 0, 3);
	//download(curlhandle , "https://www.baidu.com/","/work/index.asp",1,3);
	download(curlhandle, src_url, local_path, 0, 3);
	curl_easy_cleanup(curlhandle);
	curl_global_cleanup();
	
	return 0;
}
#endif

