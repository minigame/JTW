LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \

CPPSRC := $(wildcard $(LOCAL_PATH)/../../Src/*.cpp)				   
CLASSES_FILES   := $(CPPSRC:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(CLASSES_FILES)

CPPSRC := $(wildcard $(LOCAL_PATH)/../../thirdpart/tinyxml/*.cpp)				   
CLASSES_FILES   := $(CPPSRC:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(CLASSES_FILES)

CPPSRC := $(wildcard $(LOCAL_PATH)/../../thirdpart/CoordinateConversion/*.cpp)				   
CLASSES_FILES   := $(CPPSRC:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(CLASSES_FILES)


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Src
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../thirdpart

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
