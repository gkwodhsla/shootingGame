LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp \
Framework.cpp\
HPlayerController.cpp\
Vector2D.cpp\
Components/HSceneComponent.cpp\
Components/HPrimitiveComponent.cpp\
Components/ImageComponent.cpp\
Components/TTFComponent.cpp\
Components/MovementComponent.cpp\
Components/SpritesheetComponent.cpp\
Components/CollisionBoxComponent.cpp\
Components/SplineComponent.cpp\
Actors/HActor.cpp\
Actors/BackgroundActor.cpp\
Actors/Bullet.cpp\
Actors/HPawn.cpp\
Actors/Airplane.cpp\
Actors/EnemyAirplane.cpp\
Actors/Spawner.cpp\
Actors/StageManager.cpp\
Level/MainLevel.cpp\
UI/Canvas.cpp\
UI/ShopCanvas.cpp\
UI/Widget.cpp\
UI/TextWidget.cpp\
UI/ButtonWidget.cpp


LOCAL_SHARED_LIBRARIES := SDL2 \
SDL2_image \
SDL2_mixer \
SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
