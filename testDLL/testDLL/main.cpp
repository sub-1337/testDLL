#include <windows.h>
#include <iostream>
#include <string>
#include "LocaleDll.h"

std::string getSystemLocale() {
    wchar_t wlocaleName[LOCALE_NAME_MAX_LENGTH] = { 0 };

    if (GetUserDefaultLocaleName(wlocaleName, LOCALE_NAME_MAX_LENGTH)) {
        // Преобразуем из wchar_t в std::string (UTF-8)
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, wlocaleName, -1, nullptr, 0, nullptr, nullptr);
        std::string locale(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, wlocaleName, -1, &locale[0], size_needed, nullptr, nullptr);
        return locale;
    }

    return "en-US"; // fallback
}

int main() {
    std::string locale = getSystemLocale();
    std::string dllName;

    if (locale.find("ru") == 0) {
        dllName = "RuLocale.dll";
    }
    else {
        dllName = "EnLocale.dll";
    }

    HMODULE hLocaleDll = LoadLibraryA(dllName.c_str());
    if (!hLocaleDll) {
        std::cerr << "Failed to load DLL: " << dllName << std::endl;
        return 1;
    }

    typedef const char* (*GetStringFunc)();
    GetStringFunc getString = (GetStringFunc)GetProcAddress(hLocaleDll, "getString");

    if (!getString) {
        std::cerr << "Failed to get function from DLL." << std::endl;
        FreeLibrary(hLocaleDll);
        return 1;
    }

    std::cout << getString() << std::endl;

    FreeLibrary(hLocaleDll);
    return 0;
}