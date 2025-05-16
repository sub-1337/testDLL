#define LOCALEDLL_EXPORTS
#include "../testDLL/LocaleDll.h"

extern "C" __declspec(dllexport) const char* getString() {
    return "Hello America";
}