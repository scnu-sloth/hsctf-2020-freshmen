#
# Android Shell 编译配置文件
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# 当前脚本文件名
APP_BUILD_SCRIPT := crack1.mk

APP_ABI := armeabi-v7a
APP_PLATFORM := android-21 # >= 4.1
APP_STL := c++_static

# NDK_HAS_OLLVM
ifeq ($(NDK_HAS_OLLVM), 1)
    ifeq ($(ENABLE_OLLVM), 1)
        APP_CFLAGS += -mllvm -bcf_prob=100 -mllvm -bcf_loop=3

        APP_CFLAGS += -DENABLE_OLLVM
        APP_CPPFLAGS += -DENABLE_OLLVM
    endif
endif

NDK_APP_DST_DIR := $(LOCAL_PATH)/build/
PROJECT_ROOT_DIR := $(LOCAL_PATH)/src

# Debug / Production
ifeq ($(DEBUG),1)
    APP_CFLAGS += -O0 -g
    APP_OPTIM := debug
else
    APP_CFLAGS += -O3
    APP_OPTIM := release
endif


# 本动态库配置
LOCAL_MODULE := babeCrack1 # 本动态库名称
LOCAL_LDLIBS := -llog -landroid -lz # 调用系统库

# 包含源文件
# LOCAL_C_INCLUDES += $(PROJECT_ROOT_DIR)/includes/
LOCAL_SRC_FILES += $(wildcard $(PROJECT_ROOT_DIR)/*.cc)

include $(BUILD_EXECUTABLE)
