/**************************************************************
* 简述：这个必须先安装glib
* 1 编译命令：gcc dello.c -o hello -lglib-2.0
*             gcc test_glib.c -o hello -lglib-2.0
**************************************************************/

#if 1 /****************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "glib.h"

#define MAX_LEN 100

int test_printHello(){
    g_printf("Hello world!\n");
    return 0;
}

int g_ascii_strtoll_demo(){
	gchar * pfilename = "houjiao";
	gchar * strdouble = "11.11";
    gchar * strint = "-1234569.343;89.10";
    gchar *test_str = NULL,* hj = NULL;
    gint len = 0;
    gchar buff_str[MAX_LEN+1];
    guint64 imsi = 123456789;
    gdouble test_duble = 0.0;
    gchar **str_array = NULL;
	
	/*测试g_ascii_strtoll将字符串转成对应整形的功能第三个参数是指的几进制*/
	   test_str =strchr(strint,';');
	   len = (gint)g_ascii_strtoll(strint,NULL,10);
	   g_print("[%s][%d]%d\n", __func__, __LINE__,len);//输出123456
	   strint = test_str +1;
	   len = (gint)g_ascii_strtoll(strint,NULL,10);
	   g_print("[%s][%d]:%d\n",__func__, __LINE__, len);//输出8910
	   printf("**************************************\n");
	   g_free(test_str);
	   test_str = NULL;
	   return TRUE;

	return 0;
}

int test_g_strdup(){
	gchar * pfilename = "hello";
    //gchar * strdouble = "11.11";
    //gchar * strint = "123456;8910";
    gchar *test_str = NULL,* hj = NULL;
	hj = g_strdup(pfilename);
	printf("[%s][%d]:hj=%s\n", __func__, __LINE__, (char*)hj);
    test_str = g_strdup(hj);
    g_free(hj);
    hj = NULL;
    g_print("%s\n",test_str); //输出good
	return 0;
}

int test_g_str_equal(){
	gchar buffer1[32] = {"hello"}, buffer2[32] = {"hello"};
	gint ret =  g_str_equal(buffer1, buffer2);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	//ret = strncmp(buffer1, buffer2, strlen(buffer1));
	ret = strcmp(buffer1, buffer2);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, (int)ret);
	return 0;
}

int test_g_utf8_strchr(){
	gchar uri_copy[32] = {"helAlo"}, *tmp, *ret = NULL;
	tmp = g_utf8_strrchr(uri_copy, -1, '/');
	printf("[%s][%d]:tmp=%s\n", __func__, __LINE__, tmp);
	tmp = NULL;
	tmp = g_utf8_strchr(uri_copy, -1, 'A');
	printf("[%s][%d]:tmp=%s\n", __func__, __LINE__, tmp);
	tmp = NULL;
	tmp  = memchr((char*)uri_copy, 'A', strlen(uri_copy));
	//char *strret	= memchr((char*)uri_copy, 'A', strlen(uri_copy));
	printf("[%s][%d]:tmp=%s\n", __func__, __LINE__, (char*)tmp);
	return 0;
}

gchar *g_utf8_strchr1(const char *p, int len, int c){
	return memchr(p, c, strlen(p));
}

int test_g_str_has_prefix(){
	gchar data[128] = {"#EXT-XJ-VERSION:hello"}; 
	int ret = g_str_has_prefix(data, "#EXT-X-VERSION:");
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, (int)ret);

	return 0;
}

int g_str_has_prefix1(gchar *src, gchar *target){
	if(NULL != strstr(src, target)){
		return 1;
	}
	return -1;
}

int test_g_utf8_next_char(){
	return 0;
}

int test_g_strcmp0(){
	gchar buffer1[32] = {"BhelJlo"}, buffer2[32] = {"Bhello"};
	int ret = g_strcmp0(buffer1, buffer2);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, (int)ret);
	ret = strncmp(buffer1, buffer2, strlen(buffer1));
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, (int)ret);
	return 0;
}

#if 0
int test_g_strcasecmp(){
	gchar buffer1[32] = {"Hello"}, buffer2[32] = {"hello"};
	gint ret = g_strcasecmp(buffer1, buffer2);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, (int)ret);
	return 0;
}
#endif

char *formateData(){
	gchar *ret = NULL;
	sprintf(ret, "%s=%d", "hello", 12);
	printf("[%s][%d]:ret=%s\n", __func__, __LINE__, (char*)ret);
	return ret;
}

int test_g_strdup_printf(){
	gchar *ret =  g_strdup_printf("%s=%d", "hello", 12);
	printf("[%s][%d]:ret=%s\n", __func__, __LINE__, (char*)ret);
	sprintf(ret, "%s=%d", "hello", 12);
	printf("[%s][%d]:ret=%s\n", __func__, __LINE__, (char*)ret);
	ret = NULL;
	ret = formateData();
	printf("[%s][%d]:ret=%s\n", __func__, __LINE__, (char*)ret);
	return 0;
}

int test_g_ascii_isalpha(){
	gchar buffer[32] = {"hello"};
	int ret = g_ascii_isalpha(*buffer);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	ret = isalpha(*buffer);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	return 0;
}

int test_g_ascii_isalnum(){
	gchar buffer[32] = {"hello"};
	gchar cdata = '2';
	//int ret = g_ascii_isalnum(buffer[3]);
	int ret = g_ascii_isalnum(cdata);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	//ret = isalnum(*buffer);
	ret = isalnum(cdata);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);

	return 0;
}

int test_g_ascii_xdigit_value(){
	gchar cdata = '9';
	gint ret = g_ascii_xdigit_value(cdata);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	ret = 0;
	ret = atoi(&cdata);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	return 0;
}

int test_simple_func(){
	double ret = G_GINT64_CONSTANT(983928328329832939);
	printf("[%s][%d]:ret=%lf\n", __func__, __LINE__, ret);

	gchar buffer[32] = {"123eretet"}, *retstr = NULL;
	retstr = g_utf8_next_char(buffer);
	printf("[%s][%d]:retstr=%s\n", __func__, __LINE__, retstr);
	//retstr = buffer ++;
	retstr++;
	printf("[%s][%d]:retstr=%s\n", __func__, __LINE__, retstr);
	
	return 0;
}

typedef struct _t_data{
	int intData;
	char buf[102400];
	double dData;
	char *ptr;
}T_DATA, *P_T_DATA;

void *test_malloc(){
	T_DATA *ret = malloc(sizeof(T_DATA));
	ret->ptr = malloc(1026);
	ret->dData = 123.7659;
	ret->intData = 12;
	sprintf((ret->buf), "%s", "helloiupouuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuussndsndm,E");
	sprintf((ret->ptr), "%s", "helloiupouuuuuuuuuuuuuuuuuuuuuuuuuuussndsndm,ED");
	printf("[%s][%d]:ret=%p\n", __func__, __LINE__, ret);
	return ret;;
}

void* test_t_data(){
	T_DATA *ret = NULL;
	ret = test_malloc();
	printf("[%s][%d]:ret=%p\n", __func__, __LINE__, ret);
	return ret;
}

void* test_t_data1(){
	T_DATA *ret = NULL;
	ret = test_t_data();
	printf("[%s][%d]:ret=%p\n", __func__, __LINE__, ret);
	test_free_t_data(ret);
	return NULL;
}

int test_free_t_data(T_DATA *ptrdata){
	printf("[%s][%d]:ptr=%p\n", __func__, __LINE__, ptrdata);
	free(ptrdata->ptr);
	free(ptrdata);
	return 0;
}

static gboolean
int_from_string(gchar * ptr, gchar ** endptr, gint * val)
{
	#if 1 /**********************************/
	char *end = NULL;
	long long int ret = 0;
	if((ptr == NULL) || (val == NULL)){
		printf("[YTB][Er][%s][%d]:input param error\n", __func__, __LINE__);
		return FALSE;
	}
	ret = strtoll(ptr, &end, 10);
	if ((errno == ERANGE && ((*val) == LONG_MAX || (*val) == LONG_MIN)) || ((errno != 0) && ((*val) == 0))) {
		printf("[YTB][Er][%s][%d]:%s\n", __func__, __LINE__, strerror(errno));
		return FALSE;
	}
	if (ret > LONG_MAX || ret < LONG_MIN) {
		printf("[YTB][Er][%s][%d]: %s\n", __func__, __LINE__, strerror(errno));
		return FALSE;
	}
	printf("[YTB][%s][%d]:ret=%lld\n", __func__, __LINE__, ret);
	if (endptr){
		*endptr = end;
	}
	(*val) = ret;
	printf("[YTB][De][%s][%d]:val=%d\n", __func__, __LINE__, (*val));
	if(end != ptr){
		printf("[YTB][De][%s][%d]:!=\n", __func__, __LINE__);
		return 1;
	}else{
				printf("[YTB][De][%s][%d]:==\n", __func__, __LINE__);
		return FALSE;
	}
	#endif /***********************************/
}

int sss_main(int argc, char *argv[])
	  {
		  int base = 10;
		  char *endptr, *str;
		  long val;

		  if (argc < 2) {
			  fprintf(stderr, "Usage: %s str [base]\n", argv[0]);
			  exit(EXIT_FAILURE);
		  }

		  str = argv[1];
		  base = (argc > 2) ? atoi(argv[2]) : 10;

		  errno = 0;	/* To distinguish success/failure after call */
		  val = strtol(str, &endptr, base);

		  /* Check for various possible errors */

		  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
				  || (errno != 0 && val == 0)) {
			  perror("strtol");
			  exit(EXIT_FAILURE);
		  }

		  if (endptr == str) {
			  fprintf(stderr, "No digits were found\n");
			  exit(EXIT_FAILURE);
		  }

		  /* If we got here, strtol() successfully parsed a number */

		  printf("strtol() returned %ld\n", val);

		  if (*endptr != '\0')		  /* Not necessarily an error... */
			  printf("Further characters after number: %s\n", endptr);

		  exit(EXIT_SUCCESS);
	  }


int test_int_from_string(){
	char value[64] = {"34343"};
	int initData = 0;
	int ret = int_from_string(value, NULL, &initData);
	printf("[%s][%d]:ret=%d initData=%d\n", __func__, __LINE__, ret, initData);
	return 0;
}

int test_g_ascii_strtod(){
	double ret = 0;
	gchar *end = NULL;
	char buffer[32] = {"121.31"};
	ret = g_ascii_strtod(buffer,&end);
	printf("[%s][%d]:ret=%lf\n", __func__, __LINE__, ret);
	ret = 0;
	ret = strtod(buffer,NULL);
	printf("[%s][%d]:ret=%lf\n", __func__, __LINE__, ret);
}

int test_point(){
	char *ptr = NULL;
	int ret = (NULL == ptr);
	printf("[%s][%d]:ret=%d\n", __func__, __LINE__, ret);
	return 0;
}


#if 1
int main(int agrc, char **argv){
	//test_printHello();
	//g_ascii_strtoll_demo();
	//test_g_strdup();
	//test_g_str_equal();
	//test_g_utf8_strchr();
	//test_g_str_has_prefix();
	//test_g_strcmp0();
	//test_g_strcasecmp();
	//test_g_strdup_printf();
	//test_g_ascii_isalpha();
	//test_g_ascii_isalnum();
	//test_g_ascii_xdigit_value();
	//test_simple_func();
	//test_t_data1();
	//test_int_from_string();
	//test_point();
	test_g_ascii_strtod();
	
	
	return 0;
}
#endif


#if 0 /********************************************************************************/
{
				if(NULL == saveptr1){
					break;
				}
				ALOGD("[YTB][%s][%d]:p=%s\n", __func__, __LINE__, p);
				//sscanf(p, "%s=%s", a, v);
				//ALOGD("[YOU][%s][%d]:a=%s v=%s" ,__func__, __LINE__, a, v);
				//if (g_str_equal(a, "BANDWIDTH")) {
				if(NULL!=strstr(p, "BANDWIDTH")){
					if(0>sscanf(p, "%*[^=]=%d", &(new_list->bandwidth))){
						ALOGD("[YTB][%s][%d]:Error while reading BANDWIDTH\n", __func__, __LINE__);
					}
					//if (!int_from_string(v, NULL, &new_list->bandwidth))
						//GST_WARNING("Error while reading BANDWIDTH");
				}
				else if (NULL!=strstr(p, "PROGRAM-ID")) {
					if(0>sscanf(p, "%*[^=]=%d", &(new_list->program_id))){
						ALOGD("[YTB][%s][%d]:Error while reading PROGRAM-ID\n", __func__, __LINE__);
					}
					//if (!int_from_string(v, NULL, &new_list->program_id))
						//GST_WARNING("Error while reading PROGRAM-ID");
				}
				else if (NULL!=strstr(p,"CODECS")) {
					char buffer[64] = {0};
					if(0>sscanf(p, "%*[^=]=%s", buffer)){
						ALOGD("[YTB][%s][%d]:Error while reading CODECS\n", __func__, __LINE__);
					}
					g_free(new_list->codecs);
					new_list->codecs = g_strdup(buffer);
				}
				else if ((NULL!=strstr(p, "RESOLUTION")) && (NULL!=memchr(p, 'x', strlen(p)))) {
				//else if ((NULL!=strstr(p, "RESOLUTION"))) {
					sscanf(p, "RESOLUTION=%dx%d", &(new_list->width), &(new_list->height));
					ALOGD("[YTB][%s][%d]:res=%dx%d\n", __func__, __LINE__, (new_list->width), (new_list->height));
					/*if (!int_from_string(v, &v, &new_list->width))
						GST_WARNING("Error while reading RESOLUTION width");
					if (!v || *v != 'x') {
						GST_WARNING("Missing height");
					}
					else {
						v = g_utf8_next_char(v);
						if (!int_from_string(v, NULL, &new_list->height))
							GST_WARNING("Error while reading RESOLUTION height");
					}*/
				}
				else if (iframe && (NULL!=strstr(p, "URI"))) {
					char buffer[64] = {0};
					if(0>sscanf(p, "%*[^=]=%s", buffer)){
						ALOGD("[YTB][%s][%d]:Error while reading VIDEO\n", __func__, __LINE__);
					}
					gchar *uri = g_strdup(buffer);
					gchar *urip = uri;
					int len = strlen(uri);

					/* handle the \"uri\" case */
					if (uri[len - 1] == '"')
						uri[len - 1] = '\0';
					if (uri[0] == '"')
						uri += 1;

					data = uri_join(self->uri, uri);
					g_free(urip);

					if (data == NULL)
						continue;
					gst_m3u8_set_uri(new_list, data);
				}
				else if (NULL!=strstr(p, "VIDEO")) {
					char buffer[64] = {0};
					if(0>sscanf(p, "%*[^=]=%s", buffer)){
						ALOGD("[YTB][%s][%d]:Error while reading VIDEO\n", __func__, __LINE__);
					}
					g_free(new_list->video);
					new_list->video = g_strdup(buffer);
				}
				else if (NULL!=strstr(a, "AUDIO")) {
					char buffer[64] = {0};
					if(0>sscanf(p, "%*[^=]=%s", buffer)){
						ALOGD("[YTB][%s][%d]:Error while reading AUDIO\n", __func__, __LINE__);
					}
					g_free(new_list->audio);
					new_list->audio = g_strdup(buffer);
				}
				else if (g_str_equal(a, "SUBTITLES")) {
					char buffer[64] = {0};
					if(0>sscanf(p, "%*[^=]=%s", buffer)){
						ALOGD("[YTB][%s][%d]:Error while reading SUBTITLES\n", __func__, __LINE__);
					}
					g_free(new_list->subtitles);
					new_list->subtitles = g_strdup(buffer);
				}
			}

#endif /****************************************************/

#endif /****************************************************/


