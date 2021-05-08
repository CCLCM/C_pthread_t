//
// Created by chencl on 21-5-8.
//

#include "JavaListener.h"
#include "AndroidLog.h"
JavaListener::JavaListener(JavaVM *vm, _JNIEnv *env, jobject job) {
   jvm = vm;
   jobj = job;
   jenv= env;
   jclass clz = env->GetObjectClass(jobj);
   if (!clz) {
        LOGD("获取的 clz 对象获取为空，返回");
       return;
   }
    jmid = env->GetMethodID(clz,"onError","(ILjava/lang/String;)V");
}

void JavaListener::onError(int threadType, int code, const char *msg) {
    if (threadType == 0)
    {
        LOGD("主线程回调。。。")
        jstring  jmsg = jenv->NewStringUTF(msg);
        jenv->CallVoidMethod(jobj,jmid,code,jmsg);
        jenv->DeleteLocalRef(jmsg);
    }
    else if (threadType == 1)
    {
        LOGD("子线程回调----")
        JNIEnv *env;
        jvm->AttachCurrentThread(&env,0);
        jstring  jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj,jmid,code,jmsg);
        env->DeleteLocalRef(jmsg);
        jvm->DetachCurrentThread();
    }
}
