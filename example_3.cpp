// UTF-8 with BOM

#include <iostream>
#include <string>

#include "unicodesetting.hpp"

int main()
{
    auto loc = InitUnicodeStreams();

    std::wstring wstr;

    std::wcout << L"Input word: ";
    std::wcin >> wstr;
    std::wcin.ignore(100, L'\n');
    std::wcout << L"You enter: '" << wstr << L"'" << std::endl << std::endl;

    wstr.clear();

    std::wcout << L"Input line: ";
    std::getline(std::wcin, wstr);
    std::wcout << L"You enter: '" << wstr << L"'" << std::endl << std::endl;


    return 0;
}
