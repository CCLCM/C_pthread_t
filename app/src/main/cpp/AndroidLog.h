//
// Created by chencl on 21-5-7.
//


#ifndef MMPEG_ANDROIDLOG_H
#define MMPEG_ANDROIDLOG_H

#endif //MMPEG_ANDROIDLOG_H
#include <android/log.h>
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG,"chencl_",FORMAT,##__VA_ARGS__);