LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp \
Framework.cpp\
Components/HSceneComponent.cpp\
Components/HPrimitiveComponent.cpp\
Components/ImageComponent.cpp\
Actors/HActor.cpp\
Actors/BackgroundActor.cpp\
Level/MainLevel.cpp


LOCAL_SHARED_LIBRARIES := SDL2 \
SDL2_image \
SDL2_mixer \
SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
