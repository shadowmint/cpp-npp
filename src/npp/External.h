#pragma once

#include "./OS.h"

#if TARGET_WIN
#define EXTERN_C extern "C" __declspec(dllexport)
#else
#define EXTERN_C extern "C"
#endif
