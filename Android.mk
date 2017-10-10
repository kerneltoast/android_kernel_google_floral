# Copyright 2016 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS := \
  -Wall \
  -Werror \
  -Wno-sign-compare \
  -Wno-missing-field-initializers \
  -Wno-unused-parameter
LOCAL_SRC_FILES := \
  checks.c \
  data.c \
  dtc.c \
  dtc-lexer.l \
  dtc-parser.y \
  flattree.c \
  fstree.c \
  livetree.c \
  srcpos.c \
  treesource.c \
  util.c

LOCAL_STATIC_LIBRARIES := \
  libfdt
LOCAL_CXX_STL := none

LOCAL_MODULE := dtc

include $(BUILD_HOST_EXECUTABLE)

$(call dist-for-goals, dist_files, $(ALL_MODULES.dtc.BUILT):dtc/dtc)
