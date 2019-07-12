//
// Created by Administrator on 2019/7/4.
//
#include <jni.h>
#include <stdlib.h>
#include "Java_com_ndk_ndktestdemo_jni_MyJni_giveArray.h"
#include "android/log.h"
#define LOG_TAG  "LISON_TAG"

#include "assert.h"
#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
//定义服务端
#define SERVER_PORT 9999


#define  LOG_TAG    "LISON"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

//排序规则，小的在前
int compare(const void *a,const void *b){
    return  (*(int*)a - *(int*)b );
}

//首次未加  extern "C"程序一直显示未实现该方法
extern "C" JNIEXPORT void JNICALL Java_com_ndk_ndktestdemo_jni_MyJni_giveArray
  (JNIEnv *env, jobject jthiz, jintArray Attr){


    jint *elems =  env->GetIntArrayElements(Attr,NULL);

    //数组的长度
    int len = env->GetArrayLength( Attr);

    //排序
    /**
     * base -- 指向要排序的数组的第一个元素的指针。
        nitems -- 由 base 指向的数组中元素的个数。
        size -- 数组中每个元素的大小，以字节为单位。
        compar -- 用来比较两个元素的函数。
     */
    qsort(elems,len,sizeof(jint), compare);

    //C中操作同步到java,并释放资源
    env->ReleaseIntArrayElements( Attr, elems, 0);
}

extern "C"
JNIEXPORT jintArray JNICALL Java_com_ndk_ndktestdemo_jni_MyJni_getArray(JNIEnv *env, jobject instance, jint arrLen) {
    //创建指定大小的数组
    jintArray  jarray = env->NewIntArray(arrLen);
    jint  *elements = env->GetIntArrayElements(jarray,NULL);

    //给数组赋值
    for(int i=0;i<arrLen;i++){
        elements[i] = i+10;
    }
    env->ReleaseIntArrayElements(jarray,elements,0);
    return jarray;
}

jobject globalStr;
extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_createGlobalRef(JNIEnv *env, jobject instance) {
    jstring  obj = env->NewStringUTF("Hello World!!!");
    globalStr = env->NewGlobalRef(obj);   //全局引用
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_getGlobalRef(JNIEnv *env, jobject instance) {

//    char returnValue[] ={};


    return nullptr;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_deleteGlobalRef(JNIEnv *env, jobject instance) {



}extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_testException(JNIEnv *env, jobject instance) {   //测试C异常
    jclass clz = env->GetObjectClass(instance);
    if(clz == NULL){
        LOGD("%s","clz为NULL");
    }
    jfieldID fid = env->GetFieldID(clz ,"key","Ljava/lang/String;");
    jobject jo = env->GetObjectField(instance, fid);

//    const char * str = env->GetStringUTFChars(jo, false);
 //Windows®7 Pro OA China  李亚勋
    LOGD("%s","C could not run , this will not print ");
}

int add(int a,int b = 30){
    return a+b;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_funOrraride(JNIEnv *env, jobject instance) {
    int a = 100;
    int b = 200;
    int result = 0;

    //传值计算
    result  =  add(a,b);
    LOGD("函数传值重载 01  %d",result);
    //重载
    result = add(a);
    LOGD("函数传值重载 02  %d",result);
}
//不定参数函数
void func(int i,...){
    LOGD("=============>%d",i);
    //可变参数指针
    va_list args_p;
    //开始读取可变参数，i是最后一个固定参数
    va_start(args_p, i);
    int a = va_arg(args_p, int);
    int b =  va_arg(args_p, int);
    int c = va_arg(args_p, int);
    int d = va_arg(args_p, int);
    int e = va_arg(args_p, int);
    int f = va_arg(args_p, int);
    va_end(args_p);
    LOGD("得到可变参数%d",a);
    LOGD("得到可变参数%d",b);
    LOGD("得到可变参数%d",c);
    LOGD("得到可变参数%d",d);
    LOGD("得到可变参数%d",e);
    LOGD("得到可变参数%d",f);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_nofirmParameterFunction(JNIEnv *env, jobject instance) {
    func(9,10,12,14,16,18,52);
}extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_ndktestdemo_jni_MyJni_audioPrepare(JNIEnv *env, jobject instance) {


}


extern "C"
JNIEXPORT jint JNICALL
Java_com_ndk_ndktestdemo_jni_SocketUtils_startServer(JNIEnv *env, jobject instance) {   //启动服务端
    //创建服务端socket
    int server_socket_fd;
    //创建客户端socket
    int client_socket_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    //初始化网络地址
    //参数一：传变量的地址($server_addr)
    //参数二：开始为止
    //参数三：大小
    //初始化服务端网络地址
    memset(&server_addr,0, sizeof(server_addr));
    server_addr.sin_family == AF_INET;
    //设置服务端IP地址（自动获取系统默认的本机Ip,自动分配）

    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    server_socket_fd = socket(PF_INET,SOCK_STREAM,0);
    LOGD("%s","开启服务端");
    //判断是否创建成功
    if(server_socket_fd<0){
        LOGD("%s","创建服务端失败");
        return 1;
    }
    //服务端绑定地址
    bind(server_socket_fd,(struct sockaddr*)&server_addr, sizeof(server_addr));
    //监听客户端连接请求
    listen(server_socket_fd,6);  //监听的服务器socket 客户端数量
    socklen_t sin_size = sizeof(struct sockaddr_in);
    //获取一个客户端
    client_socket_fd= accept(server_socket_fd,(struct sockaddr*)&client_socket_fd,&sin_size);
    //判断客户端是否连接成功
    if(client_socket_fd < 0){
        LOGD("%s","连接失败");
        return 1;
    }
    //连接成功:读取客户端数据
    //BUFSIZ:默认值
    char buffer[BUFSIZ];
    int len=0;
    while(1){
        //参数一:读取客户端数据(数据源)
        //参数二:读取到哪里(我们要读取到缓冲区buffer)
        //参数三:每次读取多大BUFSIZ
        //参数四:从哪里开始读0

        len = recv(client_socket_fd,buffer,BUFSIZ,0);
        if(len > 0){
            //说明读取到了数据
            LOGD("服务端接受到客户端数据%s",buffer);
            break;
        }
    }
    //关闭服务端和客户端Socket
    //参数一：关闭的源
    //参数二：关闭的类型(设置权限)
    //SHUT_RD：关闭读(只允许写，不允许读)
    //SHUT_WR：关闭写(只允许读，不允许写)
    //SHUT_RDWR：读写都关闭(书写都不允许)
    shutdown(client_socket_fd,SHUT_RDWR);
    shutdown(server_socket_fd,SHUT_RDWR);


    LOGD("%s","server end.....");
    getchar();
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_ndk_ndktestdemo_jni_SocketUtils_startClient(JNIEnv *env, jobject instance) {  //开启客户端

//客户端socket
    int client_socket_fd;

    //服务端网络地址
    struct sockaddr_in  server_addr;
    //客户端网络地址
    struct sockaddr_in client_addr;

    //初始化网络地址
    //参数一：传变量的地址($server_addr)
    //参数二：开始位置
    //参数三：大小
    //初始化服务端网络地址
    memset(&server_addr,0,sizeof(server_addr ));
    //AF_INET:TCP/IP协议、UDP
    //AF_ISO:ISO 协议
    server_addr.sin_family = AF_INET;

    //设置服务端IP地址(自动获取系统默认的本机IP，自动分配)
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //设置服务端端口
    server_addr.sin_port = htons(SERVER_PORT);

    //创建客户端
    client_socket_fd = socket(PF_INET,SOCK_STREAM,0);
    //判断是否创建成功
    if(client_socket_fd < 0){
        LOGD("%s","create error!!!");
        //关闭
        shutdown(client_socket_fd,SHUT_RDWR);
        return 1;
    }

    //连接服务器
    //参数一：哪一个客户端
    //参数二：连接服务器地址
    //参数三：地址大小
    int con_result = connect(client_socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(con_result<0){
        LOGD("%s","connect error!");
        //关闭
        shutdown(client_socket_fd,SHUT_RDWR);
        return -1;
    }
    LOGD("%s","create Socket Client ");

    //发送消息(向服务器发送内容)
    char buffer[BUFSIZ] = "Hello, Socket Server!";
    //参数一：指定客户端
    //参数二：指定缓冲区(冲那里数据读取)
    //参数三：实际读取的大小strlen(buffer)(其实读取到"\0"结束)
    //参数四：从哪里开始读取
    send(client_socket_fd,buffer,strlen(buffer),0);

    //关闭
    shutdown(client_socket_fd,SHUT_RDWR);
    LOGD("%s","client--- end-----");

    return 0;
}