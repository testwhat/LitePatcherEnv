#ifndef MBCP_H_
#define MBCP_H_

#ifndef PLATFORM_SDK_VERSION
#define PLATFORM_SDK_VERSION 17
#endif

#define MBCP_PATH "/data/mbcp.txt"
#define MBCP_DISABLE "/data/mbcp_disable"
#define MBCP_DISABLE_DEX_DEP "/data/mbcp_nodexdep"
#define _to_string(n) #n
#define __to_string(n) _to_string(n)
#define MBCP_INFO "    MBCP version 1, Build base on SDK " __to_string(PLATFORM_SDK_VERSION) "\n"

#ifndef MBCP_PRINT_LOG
#define MBCP_PRINT_LOG true
#endif

#if PLATFORM_SDK_VERSION < 16
#ifndef ALOGD
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)

#define ALOGD LOGD
#define ALOGV LOGV
#define ALOGI LOGI
#define ALOGW LOGW
#define ALOGE LOGE
#define ALOGF LOGF
#endif
#endif

void modifyBootClassPath();


#endif // MBCP_H_
