#define LOCALEDLL_EXPORTS
#include <windows.h>
#include "../testDLL/LocaleDll.h"

extern "C" __declspec(dllexport) const char* getString() {
    return "Hello Russia";
}