LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	app_main.cpp

LOCAL_STATIC_LIBRARIES := \
	libmbcp

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog \
	libbinder \
	libandroid_runtime \
	libdvm \
	libdl

LOCAL_C_INCLUDES += \
	X-mbcp \
	dalvik \
	dalvik/vm \
	external/stlport/stlport \
	bionic \
	bionic/libstdc++/include

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= app_process2

LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)

ifeq ($(TARGET_CPU_SMP),true)
    LOCAL_CFLAGS += -DANDROID_SMP=1
else
    LOCAL_CFLAGS += -DANDROID_SMP=0
endif

# Fix old version compiler optimization will trim thumb/arm bit
NO_OPT := $(shell if [ $(PLATFORM_SDK_VERSION) -gt 16 ] ; then echo 0 ; else echo 1 ; fi)
ifeq ($(NO_OPT),1)
    LOCAL_CFLAGS += -O0
endif

include $(BUILD_EXECUTABLE)


ifneq ($(strip $(WITH_ADDRESS_SANITIZER)),)
# Build a variant of app_process binary linked with ASan runtime.
# ARM-only at the moment.
ifeq ($(TARGET_ARCH),arm)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	app_main.cpp

LOCAL_STATIC_LIBRARIES := \
	libmbcp

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog \
	libbinder \
	libandroid_runtime \
	libdvm \
	libdl

LOCAL_MODULE := app_process2__asan
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE_PATH := $(TARGET_OUT_EXECUTABLES)/asan
LOCAL_MODULE_STEM := app_process2
LOCAL_ADDRESS_SANITIZER := true

include $(BUILD_EXECUTABLE)

endif # ifeq($(TARGET_ARCH),arm)
endif # ifneq ($(strip $(WITH_ADDRESS_SANITIZER)),)
