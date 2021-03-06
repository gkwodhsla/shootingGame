LOCAL_PATH := $(call my-dir)

FIREBASE_CPP_SDK_DIR := ../../../../firebase_cpp_sdk_8.4.0/firebase_cpp_sdk

ifeq ($(FIREBASE_CPP_SDK_DIR),)
$(error FIREBASE_CPP_SDK_DIR must specify the Firebase package location.)
endif

# With Firebase libraries for the selected build configuration (ABI + STL)
STL:=$(firstword $(subst _, ,$(APP_STL)))
FIREBASE_LIBRARY_PATH:=\
$(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/libs/android/$(TARGET_ARCH_ABI)/$(STL)

include $(CLEAR_VARS)
LOCAL_MODULE:=firebase_analytics
LOCAL_SRC_FILES:=$(FIREBASE_LIBRARY_PATH)/libfirebase_analytics.a
LOCAL_EXPORT_C_INCLUDES:=$(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=firebase_auth
LOCAL_SRC_FILES:=$(FIREBASE_LIBRARY_PATH)/libfirebase_auth.a
LOCAL_EXPORT_C_INCLUDES:=$(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=firebase_database
LOCAL_SRC_FILES:=$(FIREBASE_LIBRARY_PATH)/libfirebase_database.a
LOCAL_EXPORT_C_INCLUDES:=$(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE:=firebase_app
LOCAL_SRC_FILES:=$(FIREBASE_LIBRARY_PATH)/libfirebase_app.a
LOCAL_EXPORT_C_INCLUDES:=$(LOCAL_PATH)/$(FIREBASE_CPP_SDK_DIR)/include
include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE:=firebase_admob
#LOCAL_SRC_FILES:=$(FIREBASE_LIBRARY_PATH)/libfirebase_admob.a
#LOCAL_EXPORT_C_INCLUDES:=$(FIREBASE_CPP_SDK_DIR)/include
#include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := main


SDL_PATH := ../SDL
FIREBASE_PATH := ../../../../firebase_cpp_sdk_8.4.0/firebase_cpp_sdk
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
#$(LOCAL_PATH)/$(FIREBASE_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp \
Framework.cpp\
HPlayerController.cpp\
AirplaneController.cpp\
TitleController.cpp\
Vector2D.cpp\
GlobalFunction.cpp\
DBManager.cpp\
HObject.cpp\
Components/HSceneComponent.cpp\
Components/HPrimitiveComponent.cpp\
Components/ImageComponent.cpp\
Components/TTFComponent.cpp\
Components/MovementComponent.cpp\
Components/SpritesheetComponent.cpp\
Components/CollisionBoxComponent.cpp\
Components/SplineComponent.cpp\
Components/AudioComponent.cpp\
Components/AmbientMusicComponent.cpp\
Actors/AttackStrategy/CircleStrategy.cpp\
Actors/AttackStrategy/Fire3Strategy.cpp\
Actors/AttackStrategy/Fire5Strategy.cpp\
Actors/AttackStrategy/Fire7Strategy.cpp\
Actors/AttackStrategy/FlowerStrategy.cpp\
Actors/AttackStrategy/StarStrategy.cpp\
Actors/AttackStrategy/TargetingStrategy.cpp\
Actors/HActor.cpp\
Actors/BackgroundActor.cpp\
Actors/Bullet.cpp\
Actors/HPawn.cpp\
Actors/AirplaneParent.cpp\
Actors/Airplane.cpp\
Actors/EnemyAirplane.cpp\
Actors/Spawner.cpp\
Actors/StageManager.cpp\
Actors/Crystal.cpp\
Level/MainLevel.cpp\
Level/TitleLevel.cpp\
UI/Canvas.cpp\
UI/ShopCanvas.cpp\
UI/CashShopCanvas.cpp\
UI/YesNoCanvas.cpp\
UI/InGameCanvas.cpp\
UI/LoginCanvas.cpp\
UI/Widget.cpp\
UI/TextWidget.cpp\
UI/ButtonWidget.cpp\
UI/ImageWidget.cpp\
UI/EditBoxWidget.cpp

LOCAL_SHARED_LIBRARIES := SDL2 \
SDL2_image \
SDL2_mixer \
SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog


LOCAL_STATIC_LIBRARIES := firebase_analytics \
                        firebase_auth \
                        firebase_database \
                        firebase_app
                        #firebase_admob \

include $(BUILD_SHARED_LIBRARY)