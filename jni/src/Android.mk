LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
#LOCAL_C_INCLUDES := /usr/include/SDL2
#LOCAL_C_INCLUDES := /usr/include

LOCAL_CFLAGS := -std=c++11

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	GameManager.cpp \
	Spawner.cpp \
	Thing.cpp \
	ProjectRunner.cpp \
	LTexture.cpp \
	Game.cpp \
	Transform.cpp \
	Vector2.cpp \
	ConstantMovement.cpp \
	Player.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
