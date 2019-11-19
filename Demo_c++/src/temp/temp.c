
#if 1 /*[B][glib test]:*****************************************************************/
/*Glib 程序的编译命令*/
#define MAX_LEN 100
gchar * demo (char* msg, ...)
{
    gchar * pcfgfile = NULL,* para = NULL;
    va_list argp;
    va_start(argp,msg);//msg其实指的是第一个参数，这个函数是让argp指向demo实参的栈底，参数是按从右往左的顺序压入栈的，argp不包含msg
    pcfgfile = g_strdup_vprintf("%s %s %s %d",argp);
    va_end(argp);
    return pcfgfile;
}

int test_main(void){
    gchar * pfilename = "houjiao";
    gchar * strdouble = "11.11";
    gchar * strint = "123456;8910";
    gchar *test_str = NULL,* hj = NULL;
    gint len = 0;
    gchar buff_str[MAX_LEN+1];
    guint64 imsi = 123456789;
    gdouble test_duble = 0.0;
    gchar **str_array = NULL;

    //----------------------------------------------------------一 ------------------------------------------------------------------------
    //下面的这些函数会返回一个新的字符串缓冲区的指针，所以你在使用完后必须要释放它们。
    //--------------------------------------------------------------------------------------------------------------------------------------
    /*
    gchar *g_strdup(const gchar *str)
    复制str并返回它的一个拷贝。并非返回原来字符串的指针而是重新申请一块内存将其指针返回。*/
    hj = g_strdup(pfilename);
    test_str = g_strdup(hj);
    g_free(hj);
    hj = NULL;
    g_print("%s\n",test_str); //输出good

    /*
    gchar *strnfill(gsize length, gchar *fill_char)
    创建一个长度为length并被fill_char填充的字符串。如果fill_char为0则创建一个空字符串 */
    test_str = g_strnfill(10,0);
    g_print("%s\n",test_str);
    g_free(test_str);
    test_str = NULL;


    /*
    gchar *g_strdup_printf(const gchar *format, ...)
    像sprintf()一样格式化字符串和参数。但是，你没必要像sprintf()一样创建和指定一个缓冲区，GLib将这些自动做了。适合用于字符串拼 */
    test_str = g_strdup_printf("%s_%u",pfilename,1);
    g_print("%s\n",test_str);

    /*测试g_strdup_vprintf的拼接功能 类似上面g_strdup_printf函数的功能*/
    test_str = demo("","hj","is","number",1);//输出this is a demo！
    g_print("%s\n",test_str);
    g_free(test_str);
    test_str = NULL;

    /*
    gchar *g_strconcat(const gchar *string1, ..., NULL)
    它接受任意数量的string作为参数，并返回它们的连接后的字符串。必须将NULL作为这个函数的最后一个参数 */
    hj = g_strdup(pfilename);
    test_str = g_strconcat("   ",hj,":","good person",NULL);//输出   houjiao:good person
    g_print("%s\n",test_str);
    g_free(test_str);
    test_str = NULL;


    //----------------------------------------------------------二 ------------------------------------------------------------------------
    //在下面的函数中，你应该为返回的结果申请空间。GLib并不会返回一个拷贝给你。它们与C相对应的函数非常像，参数要包含一个足够大的缓冲区来进行字符串处理。
    //--------------------------------------------------------------------------------------------------------------------------------------
    /*
    gchar *g_stpcpy(gchar *dest, const gchar *src)
    拷贝src到dest，包括最后的NULL字符。如果它执行成功，会返回dest中结束符拷贝的指针。*/
    test_str = (gchar *)g_malloc0(strlen(hj));
    g_stpcpy(test_str,hj);//函数返回的是结束符拷贝的指针这里即返回空字符串
    g_print("%s\n",test_str);//输出，good
    g_slice_free1(strlen(hj),test_str);
    test_str = NULL;

    /*
    gint g_snprintf(gchar *string, gulong n, const gchar *format, ...)
    你必须确保string有足够大的空间。而且你必须要用n来指定这个缓冲区的大小。返回值是输出字符串的长度，也有可能这个输出字符串为了适应缓冲区的大小而被截断 */
    len += g_snprintf(buff_str+len,MAX_LEN-len,"%d,%d,%d,%"G_GINT64_FORMAT"",1,2,3,imsi);
    g_print("%s\n",buff_str);//输出1，2,3,123456789

    /*测试g_strchug删除字符串开始的空格*/
    test_str = g_strconcat("   ",hj,":","good person     ",NULL);
    test_str = g_strchug(test_str);//输出houjiao:good person     光标在这
    g_print("%s\n",test_str);

    /*
    gchar *g_strchomp(gchar *string)
    将string结尾的空格都删掉，返回string */
    test_str = g_strchomp(test_str);
    g_print("%s\n",test_str);//houjiao:good person
    g_free(test_str);
    test_str = NULL;

    /*
    gchar *g_strstrip(gchar *string)
    将string开头和结尾的空白字符都删掉，返回string。*/
    test_str = g_strconcat("   ",hj,":","good person     ",NULL);
    test_str = g_strstrip(test_str);
    g_print("%s\n",test_str);//输出houjiao:good person

    /*
    gchar *g_strdelimit(gchar *string, const gchar *delimiters, gchar *new_delimiter)
    将string中的delimiters各个字符都替换为new_delimiter这一个字符 */
    test_str = g_strdelimit(test_str,"good",'a');
    g_print("%s\n",test_str);//haujiaa:aaaa persan 
    g_free(test_str);
    test_str = NULL;

    //----------------------------------------------------------三、 ------------------------------------------------------------------------
    //在下面的函数中，除了g_ascii_dtostr()之外，都不改变它们的参数。
    //--------------------------------------------------------------------------------------------------------------------------------------
    
    /*
    gchar *g_strstr_len(const gchar *haystack, gssize haystack_len, const gchar *needle)
    在haystack中遍历haystack_len长度，如果找到了needle字串，则返回这个位置的指针，如果没有找到则返回NULL。*/
    test_str = g_strstr_len(pfilename,strlen(pfilename),"jia");
    g_print("%s\n",test_str);//输出jiao
    test_str = NULL;

    /*  
    gchar *g_strrstr(const gchar *haystack, const gchar *needle)
    类似于g_strstr_len，这个函数将会从后面开始查找，但是它并没有haystack_len参数。 */
    test_str = g_strrstr(pfilename,"jia");
    g_print("%s\n",test_str);//输出jiao
    test_str = NULL;

    /*
    gchar *g_strrstr_len(gchar *haystack, gssize haystack_len, gchar *needle)
    与g_strrstr()相同，但是它只在前haystack_len个字符中查找,第二个参数是-1表示在整个字符串中找*/
    test_str = g_strrstr_len(pfilename,-1,"a");
    g_print("%s\n",test_str);
    test_str = g_strrstr_len(pfilename,5,"a");
    g_print("%s\n",test_str);//输出(null)

    /*
    gdouble g_ascii_strtod(const gchar *nptr, gchar **endptr)
    将string转为双字长度的浮点数。如果你提供了一个有效的endptr指针地址，这个函数会将指针设置到string中被转换的最后一个字符的位置*/
    test_duble = g_ascii_strtod(strdouble,NULL);
    g_print("%.2f\n",test_duble);//输出11.11

    /*
    gchar **g_strsplit(const gchar *string, const gchar *delimiter, gint max_tokens)
    使用delimiter来将string切割成至多max_tokens个部分。返回值是新申请的一个字符串数组，用来保存被切割的这些部分。
    这个字符串数组必须由你自己释放。 如果输入字符串是空的，这个返回值也是一个空的数组。 该法不改变原string */
    str_array = g_strsplit(strint,";",3);
    g_print("%s,%s\n",str_array[0],str_array[1]);//123456,8910
    
    /*
    gchar *g_str_joinv(const gchar *separator, gchar **str_array)
    将字符串数组组合成单个字符串，并将这个新申请的字符串返回。如果separator不空，g_str_joinv()会在每个字符串之间添加上一个separator分隔符。*/
    test_str = g_strjoinv(",",str_array);
    g_print("%s\n",test_str);//123456,8910    
    g_strfreev(str_array);
    str_array = NULL;
    g_free(test_str);
    test_str = NULL;

    /*测试g_ascii_strtoll将字符串转成对应整形的功能第三个参数是指的几进制*/
    test_str =strchr(strint,';');
    len = (gint)g_ascii_strtoll(strint,NULL,10);
    g_print("%d\n",len);//输出123456
    strint = test_str +1;
    len = (gint)g_ascii_strtoll(strint,NULL,10);
    g_print("%d\n",len);//输出8910
    g_free(test_str);
    test_str = NULL;
    return TRUE;
}

/*
自定义的事件源是一个继承 GSource 的结构体,即自定义事件源的结构体 的第一个成员是 GSource 结构体, 其后便可放置程序所需数据, 例如:*/
typedef struct _MySource MySource;
struct _MySource
{
    GSource source;
    gchar text[256];
};
/*
实现了事件源数据结构的定义之后,还需要实现事件源所规定的接口,主要为 prepare, check, dispatch, finalize 等事件处理函数(回调函数),它们包含于 GSourceFuncs 结构体中。
将 GSourceFuncs 结构以及事件源结构的存储空间宽度作为参数传给 g_source_new 便可构造一个新的事件源,继而可使用 g_source_attach 函数将新的事件源添加到主循环上下文中
*/
static gboolean prepare(GSource *source, gint *timeout)
{
    *timeout = 0;

    return TRUE;
}

static gboolean check(GSource *source)
{
    return TRUE;
}

static gboolean dispatch(GSource *source, GSourceFunc callback, gpointer user_data)
{
    int i = 0;
    MySource *mysource = (MySource *)source;

    for (;i<6;i++)
    {
        g_print("%s%d\n", mysource->text,i);
    }

    return TRUE;
}
/*
g_main_loop_run 函数运行时,会迭代访问 GMainContext 的事件源列表,步骤大致如下:
a. g_main_loop_run 通过调用事件源的 prepare 接口并判断其返回值以确定各事件源是否作好准备。如果各事件源的 prepare 接口的返回值为 TRUE,即表示该事件源已经作好准备,否则表示尚未做好准备。显然,上述程序所定义的事件源是已经作好了准备。
b. 若某事件源尚未作好准备 ,那么 g_main_loop 会在处理完那些已经准备好的事件后再次询问该事件源是否作好准备 ,这一过程是通过调用事件源的 check 接口而实现的,如果事件源依然未作好准备,即 check 接口的返回 FALSE,那么 g_main_loop_run 会让主事件循环进入睡眠状态。
主事件循环的睡眠时间是步骤 a 中遍历时间源时所统计的最小时间间隔 ,例如在 prepare 接口中可以像下面这样设置时间间隔。到达一定时间后, g_main_loop_run 会唤醒主事件循环,再次询问。如此周而复始,直至事件源的 prepare 接口返回值为 TRUE。*/
int main1(void)
{
    GMainLoop *loop = g_main_loop_new(NULL, TRUE);
    GMainContext *context = g_main_loop_get_context(loop);
    GSourceFuncs source_funcs = {prepare, check, dispatch, NULL};
    GSource *source = g_source_new(&source_funcs, sizeof(MySource));

    g_sprintf(((MySource *)source)->text, "Hello world");

    g_timeout_add(100, timeout_func, loop);
    g_source_attach(source, context);
    g_source_unref(source);

    g_main_loop_run(loop);

    g_main_context_unref(context);
    g_main_loop_unref(loop);

    return 0;
}
/*
该函数执行结果是大致上可以看出来事件源是串行的即单线程
*/
#if 0
三、glib的xml解析功能顺便使用简单的回调函数

//程序功能:使用回调函数的方式调用xml和txt两种文件的读取函数。
xml文件里面的内容如下
<?xml version="1.0" encoding="UTF-8"?>
  <NM id="15009244480" name="houjiao">
      <title>name ege sex what emotion</title>
        <v>hq 24 female friend love</v> 
        <v>ld 24 female friend love</v>
        <v>wj 25 female friend love</v>
        <v>wff 25 female friend love</v>
  </NM>
txt文件里面内容如下
hq is 24 years older,and she is my friend.
ld is 24 years older,and she is my friend.
wj is 25 years older,and she is my friend.
wff is 25 years older,and she is my friend.
然后程序如下，注释已经很清晰了
#endif

#include "glib.h"
#include "string.h"
#include "stdio.h"
//定义函数指针即回调函数的类型
typedef gboolean (*CallBackFileRead)(gchar *);
typedef struct _FriendNode
{
    gchar * myname;
    gchar * hername;
    gchar * what;
    gchar * emotion;
    guint8 ege;
    guint64 tel_id;
    gboolean txt_pasre_flag;
}FriendNode;

/*当遇到元素开始时，将其属性名全存到attribute_name数组中，对应的属性值存入value_cursor数组中，所以属性名和属性值是同时++然后就会取到下一个属性直到取完*/
static void start( GMarkupParseContext * context,
                  const gchar * element_name,
                  const gchar * * attribute_names,
                  const gchar * * attribute_values,
                  gpointer user_data,
                  GError * * error )
{
    const gchar * * name_cursor = attribute_names;
    const gchar * * value_cursor = attribute_values;
    FriendNode * friend_node =(FriendNode *)user_data ; 
    if (g_strcmp0(element_name,"v") == 0)
    {    
        friend_node->txt_pasre_flag = TRUE;        
    }
    else if (g_strcmp0(element_name,"NM") == 0)
    {
        while (*name_cursor)
        {
            if (g_strcmp0(*name_cursor, "id") == 0)
            {
                friend_node->tel_id = (guint64)g_ascii_strtoull(*value_cursor,NULL,10);

            }
            else if (g_strcmp0(*name_cursor, "name") == 0)
            {
                friend_node->myname = g_strdup (*value_cursor);
            }
            name_cursor++;
            value_cursor++;
        }
        g_print("My name is %s,my telphone num is %"G_GUINT64_FORMAT" \n",friend_node->myname,friend_node->tel_id);
    }
}
//一个元素结束时调用，一般可以在你想要取值的元素设置标记。
static void end( GMarkupParseContext * context,
                const gchar * element_name,
                gpointer user_data,
                GError * * error )
{
    FriendNode * friendnode = (FriendNode*)user_data;
    if (g_strcmp0(element_name,"v") == 0)
    {
        friendnode->txt_pasre_flag = FALSE;
    }
}

//一般xml里面要取得最重要的是内容，因此按照内容格式不同，拆分字符串的方式不同。
static void text( GMarkupParseContext * context,
                 const gchar * text,
                 gsize text_len,
                 gpointer user_data,
                 GError * * error )
{
    const gchar * s = text;
    gchar * ss = NULL;
    int i=0;    //列索引
    FriendNode * friendnode = (FriendNode *)user_data;

    if (friendnode->txt_pasre_flag)
    {
        while ((ss = strchr((gchar *)s,' ')) && i<=3)
        {
            switch (i)
            {
            case 0:                
                friendnode->hername = g_strndup(s,ss-s);
                break;
            case 1:
                friendnode->ege =(gint8)g_ascii_strtoull(s,NULL,10);
                break;
            case 3:                
                friendnode->what = g_strndup(s,ss-s);
                break;

            default:
                break;
            }
            s = ss + 1;
            i++;
        }
        if (i == 4)
        {
            friendnode->emotion =g_strdup(s);
        }
        g_print("%s is %d years older,and she is my %s who I %s\n",friendnode->hername,friendnode->ege,friendnode->what,friendnode->emotion);
        g_free(friendnode->hername);
        g_free(friendnode->what);
        g_free(friendnode->emotion);
    }
}
//xml解析类回调函数的实现
gboolean ReadXmlFile(gchar * filename){
    GMarkupParser gparser = {0};               //GMarkup解析器
    GMarkupParseContext *gparsecontext = NULL; //GMarkup解析上下文
    FriendNode friend_node = {0};
    char * buf;
    gsize length;
    /*创建解析器上下文第三个参数是用来传给 GMarkupParser解析器函数即start，text和end里面用的 */
    gparsecontext = g_markup_parse_context_new(&gparser,(GMarkupParseFlags)0, &friend_node, NULL);

    if (gparsecontext == NULL)
    {
        return FALSE;
    }
    /*给gparser的函数指针赋值*/
    gparser.start_element = start;
    gparser.text = text;
    gparser.end_element =end;


    /* g_file_get_contents(const gchar *filename,gchar **contents,gsize *length,GError **error);
    是用于将文件的内容读入到一个buf中,length是用来存储字符串长度的变量可设为null，读取成功返回ture读取失败返回false和最后一个参数 */
    if ((FALSE == g_file_get_contents(filename, &buf, &length,NULL)))
    {
        return FALSE;
    }


    /*开始解析buf里面的字符串，调用gparser的三个函数，xml文件里面一个元素包括，元素名，属性值和元素内容，一个元素的start标志为：<元素名[属性]>，元素的end标志为：</元素名> 包含在元素开始和元素结束之间的变是该元素的text*/
    if (g_markup_parse_context_parse(gparsecontext, buf, length, NULL) == FALSE)
    {
        g_message("load xml file failed!");
        g_free(buf);
        g_markup_parse_context_free(gparsecontext);
        gparsecontext = NULL;
        return FALSE;
    }
}
//csv解析类回调函数实现
gboolean ReadTxtFile(gchar * filename){
    FILE * ftxt_file = NULL;
    gchar buf[100] = {'\0'};
    if (fopen_s(&ftxt_file,filename,"rb") != 0)
    {
        g_print("open file error");
        return FALSE;
    }
    //fgets遇到文件结束或读取错误时返回null
    while(fgets(buf, 100, ftxt_file))
    {
       g_print("%s",buf);
    }
    fclose(ftxt_file);
    return TRUE;
}

void XmlTxtParseCallBack(gchar* filename, CallBackFileRead pFun)  //模拟API函数  
{ 
    //回调解析文件类函数
    if (!pFun(filename))
    {
        g_print("parse error");
    }
}
//1.在main中的XmlTxtParseCallBack接口函数调用了回调函数，当然xml解析和txt解析的两个函数可以像普通函数一样被调用，但是当它作为参赛传递给被调函数时就称为回调函数了。
//2.回调函数实际上就是在调用某个函数(通常是API函数时)，将自己的一个函数(这个函数叫回调函数)的地址作为参数传递给那个函数，那个函数在需要的时候利用传递的地址调用回调函数，这种模式很适合异步模块之间的调用。
//3.用计算机原理来说，回调函数就是一个中断处理函数，由系统在符合你设定条件时自动调用，你要做的只有三步，一声明回调函数类型，二实现回调函数，三，设置触发条件(即把你的回调函数名转化为函数指针作为参数用于调用)。
int main_glib_test()
{
    gchar * filename = "F:\\test\\input\\hj.txt";
    if (g_str_has_suffix(filename,".xml"))
    {
        XmlTxtParseCallBack(filename,ReadXmlFile);
    }
    else if (g_str_has_suffix(filename,".txt"))
    {
        XmlTxtParseCallBack(filename,ReadTxtFile);
    }
    else 
    {
        g_print("can't parse this file type");
    }
    return 0;

}
#endif /*[E][glib test]:*****************************************************************/


#if 1 /*Glist[B]:***************************************/
 Chinaunix首页 | 论坛 | 博客  登录 | 注册
   
hebingyue的ChinaUnix博客
7月12日12点博客新版上线，暂停写入操作
ITPUB博客全新升级 夜间维护暂停公告
为响应国家“净网2018”行动号召进行内容整治
首页　| 　博文目录　| 　关于我

hebingyue

博客访问： 135683
博文数量： 28
博客积分： 398
博客等级： 一等列兵
技术积分： 1109
用 户 组： 普通用户
注册时间： 2011-01-07 22:28
文章分类
全部博文（28）

未分配的博文（28）
文章存档
2017年（1）

2014年（3）

2013年（7）

2012年（4）

2011年（13）

我的朋友

athsonxy


jmy24462


liuyun88

最近访客

yangyefe


dean_hua


vnc1405


zh312611


lingowei


Junior88


asdmusic


abcdex


99willic

推荐博文
·ats 连接原站分析
·Shell脚本应用 – for、while...
·WINE 搭建常用工具
·ubuntu关闭内核自动更新...
·linux下如何释放命令行的占用...
相关博文
·低代码智能填报平台到底如何...
·高云半导体参加FPGA全球大会...
·玩手机有这3方面表现，那么你...
·手机的无线充电技术是什么原...
·嵌入式工控机NIS-H899在智能E...
·三星OEM高通5G处理器退出Soc...
·物流快递单号查询接口种类及...
·物联网学习教程—Linux 可执...
·基带混用导致信号弱？iPhone...
·要想成为一名物联网工程师，...
glibc 下的双向链表 GList 使用
 分类： C/C++2013-09-26 15:42:45
网上的例子大多只是基于字符串的链表结合使用方法，特提供一个基于结构体的使用，同时对不常用的 自定义排序g_list_sort ， 自定义查找 g_list_find_custom使用。
以下是实例代码:

点击(此处)折叠或打开

/*
 * file: g_list.c
 * desc: 这个文件用于演示glib库里双向链表GList的用法
 * compile: gcc -o g_list g_list.c `pkg-config --cflags --libs glib-2.0`
 */

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stu{
    long id; 
    int age;
    char *name;
}person_t;


/* 构建一个节点 */
person_t * get_person_node( int id, int age, char *name)
{
    person_t *pstu = (person_t *)calloc( sizeof(person_t), 1 );
    if ( pstu == NULL ) return NULL;
    pstu->id = id; 
    pstu->age = age;
    pstu->name = (char *)strdup( (const char*)name );

    return pstu;
}

/*遍历整个链表,打印显示*/
void display_list(GList *list)
{
    GList *it = NULL;
    person_t *pstu = NULL;

    /* 遍历链表 */
    for (it = list; it; it = it->next) {
        pstu = it->data;
        printf( "id=%d, age=%d, name=%s\r\n", pstu->id, pstu->age, pstu->name );
    } 

    printf("\n");
}

/*删除一个节点*/
GList *list_remove_by_name(GList *list, char *name )
{
    GList *it = NULL;
    person_t *pstu = NULL;

    /* 遍历链表 */
    for (it = list; it; it = it->next) {
        pstu = it->data;
        if ( memcmp(pstu->name, name, strlen(name)) == 0)
        {
            //fprintf(stdout, "delete node:%s\r\n", pstu->name );
            free( pstu->name );
            free( pstu );
            //GList *ret_list = g_list_remove(list,it);
            GList *ret_list = g_list_remove_link(list,it);
        }
    }
    return list;
}

/*释放链表，及其结点*/
void free_list_data(GList *list)
{
    GList *it = NULL;
    person_t *pstu = NULL;

    /* 遍历链表 */
    for (it = list; it; it = it->next) {
        pstu = it->data;
        free( pstu->name );
    }

    g_list_free(list);

    printf("free list success \n");
}

/*按照名称比较*/
int my_comparator_by_name(gconstpointer item1, gconstpointer item2) {
     person_t *psrc = (person_t *)(item1);
     person_t *pdst = (person_t *)(item2);
     //fprintf(stdout, "src:%s,dst:%s\r\n", psrc->name, pdst->name );
     if ( memcmp(psrc->name,pdst->name,strlen(pdst->name) ) == 0 )
         return 0;
     else
         return -1;
}

/*按照年龄比较*/
int my_comparator_by_age(gconstpointer item1, gconstpointer item2) {
     person_t *psrc = (person_t *)(item1);
     person_t *pdst = (person_t *)(item2);
     if ( psrc->age > pdst->age )
         return 1;
     else if ( psrc->age < pdst->age )
         return -1;
     else
         return 0;
}


int main(int argc, char *argv[])
{
    GList *list = NULL;

    /* 向链表尾部追加节点 */
    list = g_list_append(list, get_person_node(1,18,"hby") );
    list = g_list_append(list, get_person_node(2,42,"tli") );
    list = g_list_append(list, get_person_node(3,39,"gl") );
    fprintf(stdout, "初始化链表输出.......\r\n");
    display_list(list);

    /*指定位置插入节点*/
    list = g_list_insert(list, get_person_node(0,89,"sf"), 0 );
    /*尾部追加*/
    list = g_list_append(list, get_person_node(4,76,"fsd") );
    fprintf(stdout, "插入更新后的链表输出.......\r\n");
    display_list(list);

    /*删除指定结点*/
    list = list_remove_by_name(list, "tli");
    list = list_remove_by_name(list, "hby");
    fprintf(stdout, "删除结点后输出 [tli, hby].......\r\n");
    display_list(list);


    fprintf(stdout, "反转方式输出链表.......\r\n");
    /* 从最后一个节点开始遍历链表 */
    GList *it = NULL;
    person_t *pstu = NULL;
    it = g_list_last(list);
    for (; it; it = it->prev) {
        pstu = it->data;
        fprintf( stdout, "id=%d, age=%d, name=%s\r\n", pstu->id, pstu->age, pstu->name );
    }
    fprintf(stdout, "\r\n");

    /*自定义函数排序*/
    list = g_list_insert(list, get_person_node(8,32,"skds"), 0 );
    list = g_list_insert(list, get_person_node(6,45,"ff"), 0 );
    list = g_list_sort(list, my_comparator_by_age);
    fprintf(stdout, "自定义排序(按照年龄大小)后输出.......\r\n");
    display_list(list);

    /*自定义函数查找*/
    fprintf(stdout, "自定义函数(按照姓名)查找.......\r\n");
    person_t sfind;
    memset(&sfind, 0x00, sizeof(person_t) );
    sfind.name = g_strdup("fsd");
    GList *item = g_list_find_custom(list,&sfind, my_comparator_by_name);
    if ( item )
    { // 查找到
        person_t *pdata = item->data;
        fprintf(stdout, "find name[%s] age is:%d, id is:%d\r\n",
                pdata->name, pdata->age, pdata->id );
    }
    else
        fprintf(stdout, "find name[%s] NULL\r\n", sfind.name );
    free(sfind.name);
    fprintf(stdout, "\r\n");


    /* 销毁链表 */
    fprintf(stdout, "释放链表及结点内存.......\r\n");
    free_list_data(list);

    return 0;
}



===============================================================
编译：
#gcc -o g_list g_list.c `pkg-config --cflags --libs glib-2.0`

运行输出：
10122-hby-2:/home/hby/work/test/glibc # ./g_list 
初始化链表输出.......
id=1, age=18, name=hby
id=2, age=42, name=tli
id=3, age=39, name=gl

插入更新后的链表输出.......
id=0, age=89, name=sf
id=1, age=18, name=hby
id=2, age=42, name=tli
id=3, age=39, name=gl
id=4, age=76, name=fsd

删除结点后输出 [tli, hby].......
id=0, age=89, name=sf
id=3, age=39, name=gl
id=4, age=76, name=fsd

反转方式输出链表.......
id=4, age=76, name=fsd
id=3, age=39, name=gl
id=0, age=89, name=sf

自定义排序(按照年龄大小)后输出.......
id=8, age=32, name=skds
id=3, age=39, name=gl
id=6, age=45, name=ff
id=4, age=76, name=fsd
id=0, age=89, name=sf

自定义函数(按照姓名)查找.......
find name[fsd] age is:76, id is:4

释放链表及结点内存.......
free list success 
阅读(4018) | 评论(0) | 转发(1) |
0
上一篇：oracle11g 多实例启动问题

下一篇：通过 ssh 方式远程管理 esxi5.0

给主人留下些什么吧！~~
评论热议
请登录后评论。
登录 注册


关于我们 | 关于IT168 | 联系方式 | 广告合作 | 法律声明 | 免费注册
Copyright 2001-2010 ChinaUnix.net All Rights Reserved 北京皓辰网域网络信息技术有限公司. 版权所有

感谢所有关心和支持过ChinaUnix的朋友们
16024965号-6

#endif /*[Glist][E]:**********************************************/



