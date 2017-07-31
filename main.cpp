#define _CRT_SECURE_NO_WARNINGS
#ifndef _UNICODE
	#define _UNICODE
#endif

#include <iostream>
#include <string>
#include <fstream>

#include "unicodesetting.hpp"

int main() {

    auto loc = InitUnicodeStreams();

    std::locale::global(loc);

    std::ios::sync_with_stdio(false);

    std::wstring wstr = L"English Ελληνικά Русский Հայերեն עברית Español Deutsch 日本語";
//    std::wcout.imbue(loc);
    std::wcout << "wcout: " << wstr << std::endl;

    wstr.clear();

//    std::wcin.imbue(loc);
	std::wcout << "getline wcin: ";
    std::getline(std::wcin, wstr);

	std::wcout << "wfile_out..." << std::endl;
    std::wofstream wfile_out("file.txt");
    wfile_out.imbue(loc);
    wfile_out << wstr;
    wfile_out.close();

    wstr.clear();

    std::wifstream wfile_in("file.txt");
    wfile_in.imbue(loc);
    std::getline(wfile_in, wstr);

    std::wcout << "wfile_in: " << wstr << std::endl;

	system("pause");
    return 0;
}
