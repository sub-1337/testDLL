#pragma once

#ifdef LOCALEDLL_EXPORTS
#define LOCALEDLL_API __declspec(dllexport)
#else
#define LOCALEDLL_API __declspec(dllimport)
#endif

extern "C" {
    LOCALEDLL_API const char* getString();
}
#pragma once
