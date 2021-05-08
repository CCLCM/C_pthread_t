//
// Created by chencl on 21-5-8.
//
#include <jni.h>
#ifndef MMPEG_JAVALISTENER_H
#define MMPEG_JAVALISTENER_H


class JavaListener {
public:
    JavaVM *jvm;
    jobject jobj;
    jmethodID jmid;
    _JNIEnv *jenv;
public:
    JavaListener(JavaVM * vm,_JNIEnv *env,jobject job);
    ~JavaListener();
    /**
     * 0 主线程
     * 1 子线程
     * @param threadType
     * @param code
     * @param msg
     */
    void onError(int threadType,int code , const char * msg);

};


#endif //MMPEG_JAVALISTENER_H
