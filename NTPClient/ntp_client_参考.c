/*http://blog.csdn.net/rich_baba/article/details/6052863*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
 
int daemon_init(void)
{
    pid_t pid;
    if((pid = fork()) < 0)
        return(-1);
    else if(pid != 0)
        exit(0);  /* parent exit */
     /* child continues */
    setsid();  /* become session leader */
    chdir("/");  /* change working directory */
    umask(0);  /* clear file mode creation mask */
    close(0);  /* close stdin */
    close(1);  /* close stdout */
    close(2);  /* close stderr */
    return(0);
}
 
void sig_term(int signo)
{
    if(signo == SIGTERM)  //catched signal sent by kill(1) command 
    {
        syslog(LOG_INFO, "program terminated.");
        closelog();
        exit(0);
    }
}
 
int main(void)
{
    daemon_init();
    openlog("daemontest", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "program started.");
    signal(SIGTERM, sig_term);  /* arrange to catch the signal */
    while(1)
    {
        sleep(1);  /* put your main program here */
    }
    return(0);
}

/************************************************************************
1.  src子目录：
实验代码stdinc.h，这是程序使用到的标准头文件的一个集合，这样做不仅可以减少编码工作量，也不至于因为修改了头文件的内容而减慢编译的速度。
**********************************************************************************/
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <stdarg.h>
#include   <unistd.h>
#include   <netinet/in.h>
#include   <sys/socket.h>
#include   <sys/types.h>
#include   <arpa/inet.h>
#include   <netdb.h>
#include   <sys/time.h>
#include   <time.h>
#include   <sys/select.h>
#include   <stdbool.h>
#include   <signal.h>
#include   <sys/param.h>
#include   <sys/stat.h>
#include   <fcntl.h>

/*实验代码def.h，这里主要是一些宏定义和结构类型定义。另外，调试宏函数PDEBUG的定义方式值得大家注意。*/
 
#ifndef  __DEF_H__
     #define  __DEF_H__
 
#define  CMD_NAME    "ntpclient"
//ntp时间从年开始，本地时间从年开始，这是两者之间的差值
#define  JAN_1970   0x83aa7e80      //3600s*24h*(365days*70years+17days)
//x*10^(-6)*2^32 微妙数转 NtpTime 结构的 fraction 部分
#define  NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))  
//NTPFRAC的逆运算
#define  USEC(x) (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))
 
#define  DEF_NTP_SERVER  "210.72.145.44"    //国家授时中心 ip
//#define DEF_NTP_SERVER "stdtime.gov.hk" //香港标准时间
//#define DEF_NTP_SERVER "pool.ntp.org"     //ntp官方时间
#define  DEF_NTP_PORT   123
#define  DEF_PSEC       10
#define  DEF_PMIN       0
#define  DEF_PHOUR      0
#define  DEF_TIMEOUT    10
#define  DEF_LOGEN      1
#define  DEF_LOGPATH     "/tmp/" CMD_NAME ".log"
 
#define  CONF_PATH       "/etc/" CMD_NAME "/" CMD_NAME ".conf"
#define  DAE_PID_PATH    "/var/run/" CMD_NAME ".pid"
#define  INIT_PATH       "/etc/init.d/" CMD_NAME
 
//ntp时间戳结构
typedef   struct   
{
     unsigned   int  integer;
     unsigned   int  fraction;
} NtpTime;
 
//校准信息结构
typedef   struct
{
     struct  timeval dlytime;
     struct  timeval offtime;
     struct  timeval newtime;
} NtpServResp;
 
//ntp客户端配置结构，对应 ntpclient.conf 中各项
typedef   struct
{
     char  servaddr[256];
     unsigned   int  port;
     int  psec;
     int  pmin;
     int  phour;
     int  timeout;
     bool  logen;
     char  logpath[256];
} NtpConfig;
 
#ifndef  DEBUG
     #define  PDEBUG(fmt, args...)/
     do {}  while (0)
#else
     #define  PDEBUG(fmt, args...)/
    printf( "[%s:%d]" fmt, __func__, __LINE__,  # #args)
#endif
 
#endif




#include   "stdinc.h"
#include   "def.h"
 
extern   int  log_record( char  *record, ...);
extern   void  log_dlytime( struct  timeval dly);
extern   void  log_offtime( struct  timeval off);
extern   void  log_newtime( struct  timeval  new );
extern   void  sig_log_term( int  signo);
 
extern   int  get_cfg_from_menu();
extern   void  init_daemon( void );
extern   int  record_pid_to_file( const   char  *pidfn);
extern   int  get_cfg_from_file( const   char  *cfn);
 
 
//配置信息变量
NtpConfig NtpCfg; 
 
/*
 * 构造并发送 ntp 协议包
 * */
void  send_packet( int  fd)
{
     unsigned   int  data[12];
     int  ret;
     struct  timeval now;
 
#define  LI 0 //协议头中的元素
#define  VN 3             //版本
#define  MODE 3           //模式 : 客户端请求
#define  STRATUM 0
#define  POLL 4           //连续信息间的最大间隔
#define  PREC -6          //本地时钟精度
     if  ( sizeof (data) != 48)
    {
        printf( "data size error!/n" );
        exit(1);
    }
    memset(( char *)data, 0,  sizeof (data));
    data[0] = htonl((LI << 30) | (VN << 27) | (MODE << 24) 
        | (STRATUM << 16) | (POLL << 8) | (PREC & 0xff));
    data[1] = htonl(1 << 16);
    data[2] = htonl(1 << 16);
     //获得本地时间
    gettimeofday(&now, NULL);
 
    data[10] = htonl(now.tv_sec + JAN_1970);
    data[11] = htonl(NTPFRAC(now.tv_usec));
    PDEBUG( "tratime.fraction=%d/n" , data[11]);
    ret = send(fd, data, 48, 0);
    PDEBUG( "send packet to ntp server, ret: %d/n" , ret);
}
 
/*
 * 获得并解析 ntp 协议包
 * @sock -- 与时间服务器通讯的套接字
 * @resp -- 从服务器应答中提取的有用信息
 * */
bool  get_server_time( int  sock, NtpServResp *resp)
{
     int  ret;
     unsigned   int  data[12];    
    NtpTime oritime, rectime, tratime, destime;
     struct  timeval offtime, dlytime;
     struct  timeval now;
    
    bzero(data,  sizeof (data));
    ret = recvfrom (sock, data,  sizeof (data), 0, NULL, 0);
     if  (ret == -1)
    {
        PDEBUG( "recvfrom was failed!/n" );
        log_record( "recvfrom was failed!被迫终止 !/n" );
        exit(1);
    }
     else   if  (ret == 0)
    {
        PDEBUG( "recvfrom receive 0!/n" );
         return   false ;
    }
    
    gettimeofday(&now, NULL);
    destime.integer  = now.tv_sec + JAN_1970;
    destime.fraction = NTPFRAC (now.tv_usec);
 
#define  DATA(i) ntohl((( unsigned   int  *)data)[i])
    oritime.integer  = DATA(6);
    oritime.fraction = DATA(7);
    rectime.integer  = DATA(8);
    rectime.fraction = DATA(9);
    tratime.integer  = DATA(10);
    tratime.fraction = DATA(11);
#undef  DATA
     //与 send_packet 中发送的 tratime.faction 一致
    PDEBUG( "oritime.faction=%d/n" ,htonl(oritime.fraction));
 
     //Originate Timestamp       T1        客户端发送请求的时间
     //Receive Timestamp        T2        服务器接收请求的时间
     //Transmit Timestamp       T3        服务器答复时间
     //Destination Timestamp     T4        客户端接收答复的时间
     //网络延时 d 和服务器与客户端的时差 t
     //d = (T2 - T1) + (T4 - T3); t = [(T2 - T1) + (T3 - T4)] / 2;
#define  MKSEC(ntpt)   ((ntpt).integer - JAN_1970)
#define  MKUSEC(ntpt)  (USEC((ntpt).fraction))
#define  TTLUSEC(sec,usec)   (( long   long )(sec)*1000000 + (usec))
#define  GETSEC(us)    ((us)/1000000) 
#define  GETUSEC(us)   ((us)%1000000) 
 
     long   long  orius, recus, traus, desus, offus, dlyus;
 
    orius = TTLUSEC(MKSEC(oritime), MKUSEC(oritime));
    recus = TTLUSEC(MKSEC(rectime), MKUSEC(rectime));
    traus = TTLUSEC(MKSEC(tratime), MKUSEC(tratime));
    desus = TTLUSEC(now.tv_sec, now.tv_usec);
    
    offus = ((recus - orius) + (traus - desus))/2;
    dlyus = (recus - orius) + (desus - traus);
    
    offtime.tv_sec  = GETSEC(offus);
    offtime.tv_usec = GETUSEC(offus);
    dlytime.tv_sec  = GETSEC(dlyus);
    dlytime.tv_usec = GETUSEC(dlyus);
 
     struct  timeval  new ;
 
     //粗略校时
     //new.tv_sec = tratime.integer - JAN_1970;
     //new.tv_usec = USEC(tratime.fraction);
     //精确校时
     new .tv_sec = destime.integer - JAN_1970 + offtime.tv_sec;
     new .tv_usec = USEC(destime.fraction) + offtime.tv_usec;
    
    resp->newtime =  new ;
    resp->dlytime = dlytime;
    resp->offtime = offtime;
 
     return   true ;
}
 
/*
 * 更新本地时间
 * @newtime -- 要新的时间
 * */
int  mod_localtime( struct  timeval newtime)
{
     //只有 root 用户拥有修改时间的权限
     if  (getuid() != 0 &&geteuid () != 0)
    {
        log_record( "不是 root 用户，无法进行时间校准，被迫终止 !/n" );
        exit(1);
    }
     if  (settimeofday(&newtime, NULL) == -1)
    {
        log_record( "设置时间失败 !/n" );
         return  -1;
    }
     else
    {
        log_record( "设置时间成功 !/n" );
    }
     return  0;
}
 
/*
 * 连接时间服务器
 * */
int  ntp_conn_server( const   char  *servname,  int  port)
{
     int  sock;
 
     int  addr_len =  sizeof ( struct  sockaddr_in);
     struct  sockaddr_in addr_src; //本地 socket  <netinet/in.h>
     struct  sockaddr_in addr_dst; //服务器 socket
    
     //UDP数据报套接字
    sock = socket(PF_INET, SOCK_DGRAM, 0);
     if  (sock == -1)
    {
        log_record( "套接字创建失败，被迫终止 ! /n" );
        exit(1);
    }
    memset(&addr_src, 0, addr_len);
    addr_src.sin_family = AF_INET;
    addr_src.sin_port = htons(0);
    addr_src.sin_addr.s_addr = htonl(INADDR_ANY); //<arpa/inet.h>
     //绑定本地地址
     if  (-1 == bind(sock, ( struct  sockaddr *) &addr_src, addr_len))
    {
        log_record( "绑定失败，被迫终止 !/n" );
        exit (1);
    }
    memset(&addr_dst, 0, addr_len);
    addr_dst.sin_family = AF_INET;
    addr_dst.sin_port = htons(port);
 
     struct  hostent *host = gethostbyname(servname); //<netdb.h>
     if  (host == NULL)
    {
        log_record( "主机名获取错误，被迫终止 !/n" );
        exit (1);
    }
    memcpy (&(addr_dst.sin_addr.s_addr), host->h_addr_list[0], 4);
    PDEBUG( "Connecting to NTP_SERVER: %s ip: %s  port: %d.../n" , 
        servname, inet_ntoa(addr_dst.sin_addr), port);
 
     if  (-1 == connect(sock, ( struct  sockaddr *) &addr_dst, addr_len))
    {
        log_record( "连接服务器失败，被迫终止 !/n" );
        exit (1);
    }
    
     return  sock;
}
 
 
/*
 * 装入默认的配置
 * */
void  load_default_cfg()
{
        strcpy(NtpCfg.servaddr, DEF_NTP_SERVER);
        NtpCfg.port = DEF_NTP_PORT;
        NtpCfg.psec = DEF_PSEC;
        NtpCfg.pmin = DEF_PMIN;
        NtpCfg.phour = DEF_PHOUR;
        NtpCfg.timeout = DEF_TIMEOUT;
        NtpCfg.logen = DEF_LOGEN;
        strcpy(NtpCfg.logpath, DEF_LOGPATH);
}
 
/*
 * 初始化 ntp 客户端程序
 * */
int  ntpclient_init( int  argc,  char  **argv)
{
     int  ret;
    bzero(&NtpCfg,  sizeof (NtpCfg));
     if  (!access(DAE_PID_PATH, F_OK))
    {
        PDEBUG(DAE_PID_PATH "已经存在，服务正在后台运行 !/n" );
        exit(1);
    }
     //装入默认配置
    load_default_cfg();
    
     if  (1 == argc || !strcmp(argv[1],  "-D" ))   //后台运行
    {
         //从配置文件获取配置
        get_cfg_from_file(CONF_PATH);   
        
        init_daemon(); //初始化为 Daemon
        ret= record_pid_to_file(DAE_PID_PATH);  //记录 pid 
         if  (ret==-1)
        {
            PDEBUG(DAE_PID_PATH "创建失败 !/n" );
        }
        
        log_record( "NTP服务开始在后台为您校准时间 !/n" );
        
    }
     else   if  (2 == argc && !strcmp(argv[1],  "-i" ))   //交互式运行
    {
         while ((ret=get_cfg_from_menu())==0);
         if  (ret==-1)
        {
            exit(1);
        }
        log_record( "NTP服务开始在终端为您校准时间 !/n" );
    }   
     else
    {
        printf( "/n用法 : %s -i/-D/n"
             "   Or: %s/n"
             "   -i,            以交互方式在终端运行 /n"
             "   -D,            以守护进程方式运行 ( 默认 )/n/n"
             "守护进程 PID 文件 : " DAE_PID_PATH "/n"
             "配置文件 : " CONF_PATH "/n"
             "启动脚本 : " INIT_PATH "/n"
             "日志文件 : %s/n/n" ,
            CMD_NAME, CMD_NAME, NtpCfg.logpath);
        exit(1);
    }
    
     //保证日志存在
     if  (NtpCfg.logen)
    {
         int  fd;
         if  ((fd=open(NtpCfg.logpath, O_RDONLY|O_CREAT))==-1)
        {
            PDEBUG( "日志打开失败，将关闭日志标志 !/n" );
        }
        close(fd);
    }
     return  0;
}
 
/*
 * 程序入口
 * */
int  main( int  argc,  char  **argv)
{
     int  sock;
     int  ret;
    NtpServResp response;
     struct  timeval timeout; //<sys/time.h>
     //初始化 ntpclient
    ntpclient_init(argc, argv);
     //注册 signal 处理函数
    signal(SIGTERM, sig_log_term);
    signal(SIGINT, sig_log_term);
 
     //连接 ntp 服务器
    sock = ntp_conn_server(NtpCfg.servaddr, NtpCfg.port);
 
     //发送 ntp 包
    send_packet(sock);   
     while  (1)
    {
        fd_set fds_read;
        FD_ZERO(&fds_read);
        FD_SET(sock, &fds_read);
 
        timeout.tv_sec = NtpCfg.timeout;
        timeout.tv_usec = 0;
 
        ret = select(sock + 1, &fds_read, NULL, NULL, &timeout);
         if  (ret == -1)
        {
            log_record( "select函数出错，被迫终止 !/n" );
            exit(0);
        }
         if  (ret == 0 || !FD_ISSET (sock, &fds_read))
        {
            log_record( "等待服务器响应超时，重发请求 !/n" );
             //向服务器发送数据
            send_packet(sock);
             continue ;
        }
 
         if  ( false  == get_server_time(sock, &response))
        {
             continue ;
        }
        mod_localtime(response.newtime);
 
        log_offtime(response.offtime);
        log_dlytime(response.dlytime);
        log_newtime(response.newtime);
         //间隔指定时间校准一次
        sleep(NtpCfg.phour*3600+NtpCfg.pmin*60+NtpCfg.psec);
         //发送 ntp 包
        send_packet(sock);
    }
 
    close(sock);
    exit(0);
}
 
实验代码interact.c，这里定义了交互运行相关的函数。
#include   "stdinc.h"
#include   "def.h"
 
extern  NtpConfig NtpCfg;
 
/*
 * 通过交互界面配置菜单获取配置信息
 * 返回值： -1 --  退出程序
 *          0 -- 设置完成
 *          1 -- 开始校准
 * */
int  get_cfg_from_menu()
{
#define  BACKALIGN  "/r/t/t/t/t/t/t/t###/n"
    fflush(stdout);
    system( "clear" );
    printf( "###########################################################/n"
         "### 1. ntp服务器地址 : servaddr= %s" BACKALIGN
         "### 2. 每隔多少秒校准一次 : psec= %d" BACKALIGN
         "### 3. 每隔多少分校准一次 : pmin= %d" BACKALIGN
         "### 4. 每隔多少时校准一次 : phour= %d" BACKALIGN
         "### 5. 等待超时时间阀值 : timeout= %d" BACKALIGN
         "### 6. 日志开关标志位 : logen= %d" BACKALIGN
         "### 7. 日志存放路径 : logpath= %s" BACKALIGN
         "### ### ###" BACKALIGN
         "### r/R. 开始校准 " BACKALIGN
         "### q/Q. 退出 " BACKALIGN
         "###########################################################/n"
         "输入操作命令或需要修改的参数序号 : " ,
        NtpCfg.servaddr, NtpCfg.psec, NtpCfg.pmin, NtpCfg.phour,
        NtpCfg.timeout, NtpCfg.logen, NtpCfg.logpath);
    
     char  str[256];
    fgets(str, 256, stdin);
     switch  (str[0])
    {
         case   '1' :
        {
            printf( "servaddr = " );
            scanf( "%s" , NtpCfg.servaddr);
             break ;
        }
         case   '2' :
        {
            printf( "psec = " );
            scanf( "%d" , &NtpCfg.psec);
             if  (NtpCfg.psec<0)
            {
                NtpCfg.psec=0;
            }
             break ;
        }
         case   '3' :
        {
            printf( "pmin = " );
            scanf( "%d" , &NtpCfg.pmin);
             if  (NtpCfg.pmin<0)
            {
                NtpCfg.pmin=0;
            }
             break ;
        }
         case   '4' :
        {
            printf( "phour = " );
            scanf( "%d" , &NtpCfg.phour);
             if  (NtpCfg.phour<0)
            {
                NtpCfg.phour=0;
            }
             break ;
        }
         case   '5' :
        {
            printf( "timeout = " );
            scanf( "%d" , &NtpCfg.timeout);
             if  (NtpCfg.timeout<0)
            {
                NtpCfg.timeout=0;
            }
             break ;
        }
         case   '6' :
        {  
            printf( "logen = " );
            fgets(str, 256, stdin);
             if  (atoi(str))
            {
                NtpCfg.logen =  true ;
            }
             else  
            {
                NtpCfg.logen =  false ;
            }
             break ;
        }
         case   '7' :
        {
            printf( "logpath = " );
            scanf( "%s" , NtpCfg.logpath);
             break ;
        }
         case   'r' :
         case   'R' :
        {
             return  1;
        }
         case   'q' :
         case   'Q' :
        {
             return  -1;
        }
         default :
             break ;
    }
     return  0;
}
实验代码daemon.c，这里定义了后台运行相关的函数。
#include   "stdinc.h"
#include   "def.h"
 
extern  NtpConfig NtpCfg;
 
/*
 * 初始化本进程为守护进程
 * */
void  init_daemon( void )
{
     int  pid;
     int  i;
     if ((pid=fork())>0)
    {
        exit(0);   //是父进程，结束父进程
    }
     else   if (pid< 0)
    {
        exit(1);   //fork失败，退出
    }
     //是第一子进程，后台继续执行
    setsid();      //第一子进程成为新的会话组长和进程组长
     //并与控制终端分离
     if ((pid=fork())>0)
    {
        exit(0);   //是第一子进程，结束第一子进程
    }
     else   if (pid< 0)
    {
        exit(1);   //fork失败，退出
    }
 
     //是第二子进程，继续
     //第二子进程不再是会话组长
     for (i=0;i< NOFILE;++i)  //关闭打开的文件描述符
    {
        close(i);
    }
    chdir( "/tmp" ); //改变工作目录到 /tmp
    umask(0); //重设文件创建掩模
     return ;
}
 
/*
 *   记录 pid 到文件
 * @ 在 init_daemon 之后调用
 * */
int  record_pid_to_file( const   char  *pidfn)
{
     int  fd;
     char  pid[30];
     if  ((fd=open(pidfn, O_WRONLY|O_CREAT))==-1)
    {
         return  -1;
    }
    sprintf(pid,  "%d/n" , getpid());
    write(fd, pid, strlen(pid));
    close(fd);
     return  0;
}
 
/*
 * 在字符串中找到第一个不是指定字符的位置
 * */
char * strnchr( char  *str,  char  ch)
{
     char  *pstr = str;
     while  (*pstr)
    {
         if  (*pstr!=ch)
        {
             return  pstr;
        }
        pstr++;
    }
     return  NULL;
}
 
/*
 * 解析配置文件并加载配置信息
 * */
int  get_cfg_from_file( const   char  *cfn)
{
    FILE *fp;
     if  ((fp = fopen(cfn,  "r" ))==NULL)
    {
        PDEBUG( "配置文件打开失败 /n" );
         return  -1;
    }
     char  line[256], arg[256], val[256];
     char  *pst;
     while  (fgets(line, 256, fp)!=NULL)
    {
         if  ((pst=strnchr(line,  ' ' ))==NULL || pst[0]== '#' )
        {
             continue ;
        }
        strcpy(arg, strtok(pst,  " =" ));
         if  ((pst=strtok(NULL,  " =" ))==NULL)
        {
             continue ;
        }
        strcpy(val, pst);
         if  (val[strlen(val)-1]== '/n' )
        {
            val[strlen(val)-1]=0;
        }
         //根据 arg 和 val 给 NtpCfg 结构赋值
         if  (!strcmp(arg,  "servaddr" ))
        {
            strcpy(NtpCfg.servaddr, val); 
        }
         else   if (!(strcmp(arg,  "psec" )))
        {
            NtpCfg.psec=atoi(val); 
        }
         else   if (!(strcmp(arg,  "pmin" )))
        {
            NtpCfg.pmin=atoi(val); 
        }
         else   if (!(strcmp(arg,  "phour" )))
        {
            NtpCfg.phour=atoi(val); 
        }
         else   if (!(strcmp(arg,  "timeout" )))
        {
            NtpCfg.timeout=atoi(val); 
        }
         else   if (!(strcmp(arg,  "logen" )))
        {
             if  (atoi(val))
            {
                NtpCfg.logen= true ;
            }
             else
            {
                NtpCfg.logen= false ;
            }
        }
         else   if (!(strcmp(arg,  "logpath" )))
        {
            strcpy(NtpCfg.logpath, val); 
        }
 
         //PDEBUG("%s = %s/n", arg, val);
    }
     return  0;
}

/*************************
实验代码log.c，这里定义了日志相关的函数。
*************************************/

#include   "stdinc.h"
#include   "def.h"
 
extern  NtpConfig NtpCfg;
 
/*
 * 日志记录
 * */
int  log_record( char  *record, ...)
{
     int  fd;
     char  rbuf[256], str[256];
    time_t now = time(NULL);
    va_list ap;
    va_start(ap, record);
    bzero(rbuf, 256);
    bzero(str, 256);
    vsprintf(str, record, ap);
    va_end(ap);
    PDEBUG( "%s/n" , str);
     if  (!NtpCfg.logen)  //日志标志没有打开
    {
         return  0;
    }
    sprintf(rbuf,  "%s/t%s/n" , asctime(localtime(&now)), str);
     if  ((fd=open(NtpCfg.logpath, O_WRONLY|O_APPEND))==-1)
    {
         return  -1;
    }
    write(fd, rbuf, strlen(rbuf));
    close(fd);
     return  0;
}
 
/*
 * 记录 dlytime 、 offtime 、 newtime
 * */
void  log_dlytime( struct  timeval dly)
{
     char  str[256];
    sprintf(str,  "网络延时 : %7.3f s/n" , 
        dly.tv_sec+( double )dly.tv_usec/1000000.0;
    log_record(str);
}
 
void  log_offtime( struct  timeval off)
{
     char  str[256];
    sprintf(str,  "本地时差 : %7.3f s/n" , 
        off.tv_sec+ ( double ) off.tv_usec/1000000.0);
    log_record(str);
}
 
void  log_newtime( struct  timeval  new )
{
     char  str[256];
     struct  tm *ltm;
    ltm = localtime(& new .tv_sec);
    sprintf(str,  "正确时间 : %.4d-%.2d-%.2d %.2d:%.2d:%.2d/n" ,
        ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday, 
        ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    log_record(str);
}
 
/*
 *   信号处理函数
 * @ 程序被信号终止时，记录日志
 * */
void  sig_log_term( int  signo)
{
     if  (SIGTERM==signo)
    {
        log_record( "接收到 SIGTERM 信号 , 服务被终止 /n" );
    }
     else
    {
        log_record( "接收到 SIGINT 信号 , 服务被终止 /n" );
    }
    raise(SIGKILL);
}

#if 0
2.  Init.d子目录：
实验代码 ntpclient 是该服务的初始化脚本，它的实现还利用到了系统定义的一些脚本函数，如 killproc 和 daemon 等，它们定义在 /etc/init.d/functions 中 。读者可以深入分析 /etc/init.d/functions ，弄明白 killproc是如何杀死相应的 daemon 进程的。
#!/bin/sh
 
# 默认目录 :
cmd=ntpclient
pidfile=/var/run/ntpclient.pid
logpath=/tmp/ntpclient.pid
config=/etc/ntpclient/ntpclient.conf
 
# Source function library.
if [ -f /etc/init.d/functions ] ; then
  . /etc/init.d/functions
elif [ -f /etc/rc.d/init.d/functions ] ; then
  . /etc/rc.d/init.d/functions
else
  exit 1
fi
 
# Avoid using root's TMPDIR
unset TMPDIR
 
# Source networking configuration.
. /etc/sysconfig/network
 
# Check that networking is up.
[ ${NETWORKING} = "no" ] && exit 1
 
# Check that ${cmd}.conf exists.
[ -f $config ] || exit 6
 
RETVAL=0
 
start() 
{
       KIND=$cmd
echo -n $"Starting $KIND services: "
daemon $cmd
RETVAL=$?
echo
return $RETVAL
}
 
stop() 
{
       KIND=$cmd
echo -n $"Shutting down $KIND services: "
killproc $cmd
RETVAL=$?
echo
return $RETVAL
}
 
restart() 
{
stop
start
}
 
rhstatus() 
{
status $cmd
RETVAL=$?
if [ $RETVAL -ne 0 ] ; then
return $RETVAL
fi
}
 
# Allow status as non-root.
if [ "$1" = status ]; then
       rhstatus
       exit $?
fi
 
# Check that we can write to it... so non-root users stop here
[ -w $config ] || exit 4
 
case "$1" in
  start)
   start
;;
  stop)
   stop
;;
  restart)
   restart
;;
  reload)
   reload
;;
  status)
   rhstatus
;;
  *)
echo $"Usage: $0 {start|stop|restart|status}"
exit 2
esac
 
exit $?
3.  安装脚本：
实验代码 install 是该服务的安装脚本，值得注意的是该脚本中一些会产生终端输出的命令后加的：2>&1 >/dev/null ，它的作用是将标准出错并入标准输出，并将标准输出送入 /dev/null 丢弃。
#!/bin/sh
cmd=ntpclient
cfgpath=/etc/${cmd}/${cmd}.conf
initpath=/etc/init.d/${cmd}
logpath=/tmp/${cmd}.log
binpath=/usr/sbin/$cmd
 
Usage()
{
    echo "Usage: "
    echo -e "/t${cmd} -i/t安装 ${cmd}"
    echo -e "/t${cmd} -d/t卸载 ${cmd}/n"
}
 
if [ -n "$1" -a -z "$2" ];then
    if [ "$1" = "-i" ];then
        make clean -f .Makefile 2>&1 >/dev/null
        make -f .Makefile 2>&1 >/dev/null
        [ -d /etc/${cmd} ] || mkdir /etc/${cmd}
        cp config/${cmd}.conf ${cfgpath} 2>&1 >/dev/null
        cp init.d/${cmd} ${initpath} 2>&1 >/dev/null
        cp src/${cmd} ${binpath}  2>&1 >/dev/null
        [ -f ${logpath} ] || touch ${logpath}
        chmod 761 ${binpath} ${initpath} 2>&1 >/dev/null
        chmod 640 ${cfgpath} ${logpath} 2>&1 >/dev/null
        make clean -f .Makefile 2>&1 >/dev/null
        echo -n "安装 ${cmd}  服务 :"
        echo -e "/r/t/t/t/t/t/t/t   [/033[32;32;5m确定 /033[0m]"
    elif [ "$1" = "-d" ];then
        [ -x ${initpath} ] && ${initpath} stop 2>&1 >/dev/null
        rm -rf /etc/${cmd} 
        rm -f ${initpath} ${initpath} ${binpath}  ${logpath}
        echo -n "卸载 ${cmd}  服务 :"
        echo -e "/r/t/t/t/t/t/t/t   [/033[32;32;5m确定 /033[0m]"
    else
        Usage
    fi
else
    Usage
fi

#endif