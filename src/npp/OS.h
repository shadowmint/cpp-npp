#pragma once

/// OS detection
#define NPP_WIN64 0
#define NPP_WIN 0
#define NPP_WIN32 0
#define NPP_IPHONE 0
#define NPP_IOS 0
#define NPP_IOS_SIM 0
#define NPP_IOS_SIMULATOR 0
#define NPP_IPHONE_SIM 0
#define NPP_IPHONE_SIMULATOR 0
#define NPP_APPLE 0
#define NPP_OSX 0
#define NPP_ANDROID 0
#define NPP_UNIX 0
#define NPP_LINUX 0
#define NPP_BSD 0
#define NPP_UNKNOWN 0

#ifdef _WIN32
  #undef NPP_WIN
  #define NPP_WIN 1
  #ifdef _WIN64
    #undef NPP_WIN64
    #define NPP_WIN64 1
  #else
    #undef NPP_WIN32
    #define NPP_WIN32 1
  #endif
#elif __APPLE__
  #include "TargetConditionals.h"
  #if TARGET_OS_IPHONE
    #undef NPP_IPHONE
    #undef NPP_IOS
    #define NPP_IPHONE 1
    #define NPP_IOS 1
  #elif TARGET_IPHONE_SIMULATOR
    #undef NPP_IPHONE
    #undef NPP_IOS
    #undef NPP_IOS_SIM
    #undef NPP_IOS_SIMULATOR
    #undef NPP_IPHONE_SIM
    #undef NPP_IPHONE_SIMULATOR
    #define NPP_IPHONE 1
    #define NPP_IOS 1
    #define NPP_IOS_SIM 1
    #define NPP_IOS_SIMULATOR 1
    #define NPP_IPHONE_SIM 1
    #define NPP_IPHONE_SIMULATOR 1
  #elif TARGET_OS_MAC
    #undef NPP_APPLE
    #undef NPP_OSX
    #define NPP_APPLE 1
    #define NPP_OSX 1
  #endif
#elif __ANDROID__
  #undef NPP_ANDROID
  #define NPP_ANDROID 1
#elif __unix || __unix__
  #undef NPP_UNIX
  #define NPP_UNIX 1
  #if __linux
    #undef NPP_LINUX
    #define NPP_LINUX 1
  #else
    #include <sys/param.h>
    #if (defined(BSD) && (BSD >= 199103))`
      #undef NPP_BSD
      #define NPP_BSD 1
    #endif
  #endif
#else
  #undef NPP_UNKNOWN
  #define NPP_UNKNOWN 1
#endif
