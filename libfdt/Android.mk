LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
  fdt.c \
  fdt_ro.c \
  fdt_wip.c \
  fdt_sw.c \
  fdt_rw.c \
  fdt_strerror.c \
  fdt_empty_tree.c \
  fdt_addresses.c

LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
LOCAL_MODULE := libfdt
include $(BUILD_HOST_STATIC_LIBRARY)
