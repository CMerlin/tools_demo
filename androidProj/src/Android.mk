LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
#指定源文件的位置
LOCAL_SRC_FILES:= demo.cpp\
	 hello.cpp
#指定获取静态库的位置
#LOCAL_STATIC_LIBRARIES  += libkeyMerlin
LOCAL_LDFLAGS += $(LOCAL_PATH)/../lib/libDir/libkeyMerlin.a
$(warning "[BUILD]: LOCAL_LDFLAGS is $(LOCAL_LDFLAGS)")
#指头文件的位置	
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include/
#$(warning "[BUILD]: LOCAL_C_INCLUDES is $(LOCAL_C_INCLUDES)")
LOCAL_CFLAGS += -Wno-multichar -O3
LOCAL_MODULE_TAGS := optional
#LOCAL_PRELINK_MODULE := false
LOCAL_MODULE:= libShare
#include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_EXECUTABLE)
include $(BUILD_SHARED_LIBRARY)
$(warning "[BUILD]: LOCAL_MODULE is $(LOCAL_MODULE)")

