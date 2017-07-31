#ifndef UNICODESETTING_HPP
#define UNICODESETTING_HPP

#ifdef WIN32
    #include "winunicodebuf.hpp"
    #include <Windows.h>
#endif

#include <iostream>
#include <codecvt>
#include <memory>

template <typename CHAR_T = wchar_t>
std::locale configureLocale_Unicode(std::locale base = std::locale::classic(),
                            std::initializer_list<std::locale::category> category_copy = {std::locale::ctype}){

    if(category_copy.size() > 0) {

        constexpr const char* names_locs[] = {
            // POSIX OS
            "ru_RU.UTF-8",
            "en_US.UTF-8",
            // windows
            "Russia_Russia"
        };

        std::locale loc_new; // one of the 'names_locs' or the global

        for(size_t i = 0; i < sizeof(names_locs)/sizeof(const char*); ++i){
            try {
                loc_new = std::locale( names_locs[i] );
                break;
            } catch (...) {}
        }

        for(auto category : category_copy){
            base = std::locale(base, loc_new, category);
        }
    }

    return { base, new std::codecvt_utf8<CHAR_T> };
}


std::locale InitUnicodeStreams(std::locale base = {}){
#ifdef WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

	DWORD consoleMode;
	if (!!GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &consoleMode)) {
		std::wcin.rdbuf(new details::winUnicodeBuf(*std::wcin.rdbuf()));
	}
#endif

    auto locUnicode = configureLocale_Unicode(base, {});

    std::wcin.imbue(locUnicode);
    std::wcout.imbue(locUnicode);
    std::wcerr.imbue(locUnicode);
    std::wclog.imbue(locUnicode);

    return locUnicode;
}

#endif // UNICODESETTING_HPP
