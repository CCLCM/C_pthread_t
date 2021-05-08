#include <jni.h>
#include <string>

#include "pthread.h"
#include "AndroidLog.h"
#include "queue"
#include "unistd.h"
#include "JavaListener.h"
pthread_t thread;

void *normalCallback(void *data) {
    LOGD("create normal thread form C++ !");
    pthread_exit(&thread);
}

extern "C" JNIEXPORT void JNICALL
Java_com_chencl_mmpeg_ThreadDemo_normalThread(JNIEnv *env, jobject thiz) {
    // TODO: implement normalThread()
    pthread_create(&thread,NULL,normalCallback,NULL);
}


pthread_t product;
pthread_t custom;
pthread_mutex_t mutex;
pthread_cond_t cond;
std::queue<int> queue;

JavaVM *jvm;
JavaListener *javaListener;

void * productCallBack(void * data) {
    while (1) {
        //javaListener->onError(1,100,"底层错误回调 from C++");
        pthread_mutex_lock(&mutex);
        queue.push(1);
        LOGD("生产者生产了产品，通知消费者消费 数量%d ",queue.size());
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void * customCallBack(void * data) {
    while (1){
        pthread_mutex_lock(&mutex);
        if (queue.size() > 0) {
            LOGD("产品已经消费 数量还剩余%d ",queue.size());
            queue.pop();
        } else {
            pthread_cond_wait(&cond,&mutex);
            //pthread_cond_signal(&cond);
            LOGD("产品已经消费完了。。。。。。。。。");
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}


extern "C" JNIEXPORT void JNICALL
Java_com_chencl_mmpeg_ThreadDemo_mutexThread(JNIEnv *env, jobject thiz) {
    // TODO: implement mutexThread()
    for (int i = 0; i < 10 ; ++i) {
        queue.push(i);
    }

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&product,NULL,productCallBack,NULL);
    pthread_create(&custom,NULL,customCallBack,NULL);




}

extern "C" JNIEXPORT void JNICALL
Java_com_chencl_mmpeg_ThreadDemo_callBackFromC(JNIEnv *env, jobject thiz) {

    javaListener = new JavaListener(jvm,env,env->NewGlobalRef(thiz));
    javaListener->onError(0,100,"底层错误回调 from C++");
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *javaVm,void *reserved) {
      JNIEnv *env;
      jvm = javaVm;
      if (javaVm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
          return -1;
      }
    return JNI_VERSION_1_6;
}
