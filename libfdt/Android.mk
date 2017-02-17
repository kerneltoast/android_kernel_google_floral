LOCAL_PATH:= $(call my-dir)

common_src_files := \
  fdt.c \
  fdt_ro.c \
  fdt_wip.c \
  fdt_sw.c \
  fdt_rw.c \
  fdt_strerror.c \
  fdt_empty_tree.c \
  fdt_addresses.c \
  fdt_overlay.c

#################################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(common_src_files)
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
LOCAL_MODULE := libfdt

include $(BUILD_STATIC_LIBRARY)

#################################################


include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(common_src_files)
LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)
LOCAL_MODULE := libfdt

include $(BUILD_HOST_STATIC_LIBRARY)

