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
#define ALOGD LOGD
#define ALOGE LOGE
#define ALOGI LOGI
#define ALOGV LOGV
#endif

void modifyBootClassPath();


#endif  // MBCP_H_
