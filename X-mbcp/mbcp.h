#ifndef MBCP_H_
#define MBCP_H_

#define MBCP_PATH "/data/mbcp.txt"
#define MBCP_PROPERTY_NAME "app.mbcp.enable"
#define MBCP_DISABLE_DEX_DEP "/data/mbcp_nodexdep"
#define MBCP_INFO "    MBCP version 1, support from SDK 16(4.1), build base on SDK 18(4.3)\n"

#ifndef MBCP_PRINT_LOG
#define MBCP_PRINT_LOG true
#endif

#ifndef ALOGD
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)

#define ALOGD LOGD
#define ALOGE LOGE
#define ALOGI LOGI
#define ALOGV LOGV
#endif

void modifyBootClassPath();


#endif  // MBCP_H_
