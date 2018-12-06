
LOLLIPOP_PATH := $(call my-dir)
include $(call all-subdir-makefiles)
LOCAL_PATH := $(LOLLIPOP_PATH)
#$(warning $(LOCAL_PATH))
##$(warning "[BUILD]: LOCAL_PATH is $(LOCAL_PATH)")
include $(CLEAR_VARS)
#指定源文件的位置
LOCAL_SRC_FILES := \
	main.cpp\
	hello1.cpp
#指定动态库
LOCAL_SHARED_LIBRARIES := \
	libShare \
	libcutils
#指定头文件的位置
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/
#$(warning "[BUILD]: LOCAL_C_INCLUDES is $(LOCAL_C_INCLUDES)")

LOCAL_CFLAGS += -fpermissive -fno-strict-aliasing -DADDPROTECTION1 -DADDPROTECTION2 -DADDPROTECTION3 -DUSEGARBAGECODE
LOCAL_CFLAGS += -Wno-error=date-time -Wno-c++11-narrowing -ferror-limit=0 

LOCAL_MODULE:= merlinFunc
include $(BUILD_EXECUTABLE)
$(warning "[BUILD]: LOCAL_MODULE is $(LOCAL_MODULE)")

