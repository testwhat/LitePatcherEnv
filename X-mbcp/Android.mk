LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)

LOCAL_SRC_FILES := \
	mbcp.cpp

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils

LOCAL_MODULE := libmbcp
LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)

