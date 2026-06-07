#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#define MODULE_API extern "C" __declspec(dllexport)
#else
#define MODULE_API extern "C" __attribute__((visibility("default")))
#endif
