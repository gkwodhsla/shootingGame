
# Uncomment this if you're using STL in your project
# You can find more information here:
# https://developer.android.com/ndk/guides/cpp-support

APP_PLATFORM:=android-20
NDK_TOOLCHAIN_VERSION=clang
APP_ABI:=armeabi-v7a arm64-v8a x86 x86_64
APP_STL:=c++_static

APP_CPPFLAGS+=-std=c++17
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS := -frtti

#APP_STL := c++_shared

#APP_ABI := armeabi-v7a arm64-v8a x86 x86_64

# Min runtime API level
#APP_PLATFORM=android-16
