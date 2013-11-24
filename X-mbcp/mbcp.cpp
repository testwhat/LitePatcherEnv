#include "mbcp.h"
#include <stdlib.h>
#include <utils/Log.h>

static bool isMbcpEnable()
{
    if (access(MBCP_DISABLE, F_OK) == 0) {
        return false;
    }
    if (access(MBCP_PATH, F_OK) == 0) {
        return true;
    }
    return false;
}

void modifyBootClassPath()
{
    if (!isMbcpEnable()) {
        if (MBCP_PRINT_LOG) ALOGI("[MBCP] modifyClassPath off");
        return;
    }
    FILE* fp = fopen(MBCP_PATH, "r");
    if (fp == NULL) {
        if (MBCP_PRINT_LOG) ALOGW("[MBCP] Cannot read bcp file");
        return;
    }

    const char* bcp = getenv("BOOTCLASSPATH");
    char bcpBuf[4096];
    strncpy(bcpBuf, bcp, strlen(bcp));

    // file format: patch.jar:target_to_override.jar
    char tmpBcp[4096];
    memset(tmpBcp, 0, sizeof(tmpBcp));

    char buf[1024];
    char *line;
    while ((line = fgets(buf, sizeof(buf), fp)) != NULL) {
        int lineLen = strlen(line);
        if (lineLen < 2) {
            continue;
        }
        char *trimTail = line + lineLen - 1;
        while (*trimTail == '\r' || *trimTail == '\n' || *trimTail == ' ') {
            *trimTail = '\0';
            trimTail--;
        }
        if (line[0] == '#') {
            if (MBCP_PRINT_LOG) ALOGI("[MBCP] Skip: %s", line);
            continue;
        }
        if (MBCP_PRINT_LOG) ALOGI("[MBCP] Read: %s", line);

        // Split patch and target by ':'
        const char *target = strstr(line, ":");
        //if (MBCP_PRINT_LOG) ALOGI("[MBCP] target=%s", target);
        if (target == NULL) {
            if (MBCP_PRINT_LOG) ALOGW("[MBCP] Wrong line format");
            continue;
        }
        char patch[128];
        memset(patch, 0, sizeof(patch));
        unsigned int patchLen = target - line;
        if (patchLen >= sizeof(patch)) {
            if (MBCP_PRINT_LOG) ALOGW("[MBCP] Patch length too long %d", patchLen);
            continue;
        }
        strncpy(patch, line, patchLen);
        //if (MBCP_PRINT_LOG) ALOGI("[MBCP] patch=%s", patch);

        // Find target in current bcp
        target++; // Skip char ':'
        const char *fromTarget = strstr(bcpBuf, target);
        if (fromTarget == NULL) {
            if (MBCP_PRINT_LOG) ALOGW("[MBCP] Target not found, bcpBuf=%s target=%s", bcpBuf, target);
            continue;
        }
        int targetPos = fromTarget - bcpBuf;

        // Insert patch before target
        memset(tmpBcp, 0, sizeof(tmpBcp));
        strncat(tmpBcp, bcpBuf, targetPos); // part before target
        strncat(tmpBcp, patch, strlen(patch)); // what we insert
        strncat(tmpBcp, ":", 1);
        strncat(tmpBcp, bcpBuf + targetPos, strlen(bcpBuf)); // remain part

        memset(bcpBuf, 0, sizeof(bcpBuf));
        strncpy(bcpBuf, tmpBcp, strlen(tmpBcp));
    }
    fclose(fp);

    setenv("BOOTCLASSPATH", bcpBuf, 1);
    if (MBCP_PRINT_LOG) ALOGI("[MBCP] New BOOTCLASSPATH=%s", bcpBuf);
}
