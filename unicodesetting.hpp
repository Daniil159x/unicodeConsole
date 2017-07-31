// UTF-8 with BOM

#ifndef UNICODESETTING_HPP
#define UNICODESETTING_HPP

#ifdef WIN32
    #include "winunicodebuf.hpp"
    #include <Windows.h>
#endif

#include <iostream>
#include <codecvt>
#include <memory>

#include "ctype/ctype_unicode.hpp"

std::locale configureLocale_Unicode(std::locale base = {})
{
    // TODO: to add other languages

    base = std::locale(base, new ctype_unicode);

    return { std::move(base), new std::codecvt_utf8<wchar_t> };
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

    std::ios::sync_with_stdio(false);

    auto locUnicode = configureLocale_Unicode(base);

    std::wcin.imbue(locUnicode);
    std::wcout.imbue(locUnicode);
    std::wcerr.imbue(locUnicode);
    std::wclog.imbue(locUnicode);

    return locUnicode;
}

#endif // UNICODESETTING_HPP
