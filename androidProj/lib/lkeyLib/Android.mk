LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

#指定源文件的位置
LOCAL_SRC_FILES:= key1.c \
	 key2.c
#指头文件的位置	 
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/
#$(warning "[BUILD]: LOCAL_C_INCLUDES is $(LOCAL_C_INCLUDES)")
LOCAL_CFLAGS += -Wno-multichar -O3
LOCAL_MODULE_TAGS := optional
#LOCAL_PRELINK_MODULE := false
LOCAL_MODULE:= libkeyMerlin
include $(BUILD_STATIC_LIBRARY)
$(warning "[BUILD]: LOCAL_MODULE is $(LOCAL_MODULE)")



