# A simple test for the minimal standard C++ library
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#for opencl.h
LOCAL_C_INCLUDES := $(ADRENO_SDK)/Development/Inc/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/
#LOCAL_CPPFLAGS += -I$(ADRENO_SDK)/Development/Inc
LOCAL_CFLAGS := -DUSE_GPU -c -g -O0  -W  -std=c++11 -D_QUALCOMM
#LOCAL_LDLIBS := -llog -landroid $(LOCAL_PATH)/libs/libOpenCL.so
LOCAL_LDLIBS := -llog -landroid -lOpenCL
LOCAL_MODULE := ocl_videoproc
LOCAL_SRC_FILES := ocl_videoproc.cpp
LOCAL_SHARED_LIBRARIES += libcutils libOpenCL
#include $(PREBUILT_SHARED_LIBRARY)
include $(BUILD_EXECUTABLE)


#ifeq ($(ARCH),x86_64)
#	g++ -g -std=gnu++11 -I /opt/intel/opencl-1.2-sdk-5.0.0.43/include -L /opt/intel/opencl-1.2-5.0.0.43/lib64 -o v4l_snapshot v4l_snapshot.cpp -Wl,-rpath,/opt/intel/opencl-1.2-5.0.0.43/lib64 -lOpenCL -D_INTEL -I. -D_DEBUG -D_WITH_INVERT -D_WITH_IMAGEDESC -D_WITH_FREEIMAGE -lfreeimage -D_WITH_VIDEO -D_WITH_SNAPSHOT
#	g++ -g -std=gnu++11 -I /opt/intel/opencl-1.2-sdk-5.0.0.43/include -L /opt/intel/opencl-1.2-5.0.0.43/lib64 -o v4l_camera v4l_camera.cpp -Wl,-rpath,/opt/intel/opencl-1.2-5.0.0.43/lib64 -lOpenCL -D_INTEL -I. -D_DEBUG -D_WITH_INVERT -D_WITH_IMAGEDESC -D_WITH_FREEIMAGE -lfreeimage -D_WITH_SDL -lSDL -D_WITH_KEYLOGGER -D_WITH_FPS -D_WITH_FRAMECPY -D_WITH_PERF_LOGDUMP
#	g++ -g -std=gnu++11 -I /opt/intel/opencl-1.2-sdk-5.0.0.43/include -L /opt/intel/opencl-1.2-5.0.0.43/lib64 -o ocl_videoproc ocl_videoproc.cpp -Wl,-rpath,/opt/intel/opencl-1.2-5.0.0.43/lib64 -lOpenCL -D_INTEL -I. -D_DEBUG -D_WITH_INVERT -D_WITH_IMAGEDESC -D_WITH_FREEIMAGE -lfreeimage -D_WITH_SDL -lSDL -D_WITH_KEYLOGGER -D_WITH_FPS -D_WITH_FRAMECPY -D_WITH_PERF_LOGDUMP -D_WITH_PREF_REC
#else
#	g++ -g -std=gnu++11 -I /opt/intel/opencl-1.2-sdk-5.0.0.43/include -L /opt/intel/opencl-1.2-5.0.0.43/lib64 -o v4l_snapshot v4l_snapshot.cpp -Wl,-rpath,/opt/intel/opencl-1.2-5.0.0.43/lib64 -lOpenCL -D_FREESCALE -I. -D_DEBUG -D_WITH_INVERT -D_WITH_FREEIMAGE -lfreeimage -D_WITH_VIDEO -D_WITH_SNAPSHOT
#	g++ -g -std=gnu++11 -I /opt/intel/opencl-1.2-sdk-5.0.0.43/include -L /opt/intel/opencl-1.2-5.0.0.43/lib64 -o v4l_camera v4l_camera.cpp -Wl,-rpath,/opt/intel/opencl-1.2-5.0.0.43/lib64 -lOpenCL -D_FREESCALE -I. -D_DEBUG -D_WITH_INVERT -D_WITH_FREEIMAGE -lfreeimage -D_WITH_SDL -lSDL -D_WITH_FPS -D_WITH_FRAMECPY -D_WITH_PERF_LOGDUMP
#	g++ -g -std=gnu++11 -I /opt/intel/opencl-1.2-sdk-5.0.0.43/include -L /opt/intel/opencl-1.2-5.0.0.43/lib64 -o ocl_videoproc ocl_videoproc.cpp -Wl,-rpath,/opt/intel/opencl-1.2-5.0.0.43/lib64 -lOpenCL -D_FREESCALE -I. -D_DEBUG -D_WITH_INVERT -D_WITH_FREEIMAGE -lfreeimage -D_WITH_SDL -lSDL -D_WITH_KEYLOGGER -D_WITH_FPS -D_WITH_FRAMECPY -D_WITH_PERF_LOGDUMP
#endif
