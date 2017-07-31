// UTF-8 with BOM

#include <iostream>
#include <string>
#include <fstream>

#include <cwctype>

#include "unicodesetting.hpp"

int main()
{
    auto loc = InitUnicodeStreams();

    std::wstring wstr;

    std::wcout << L"Input string: ";
    std::getline(std::wcin, wstr);


    std::wofstream wfile_out("out.txt");
    wfile_out.imbue(loc);

    // std::towlower
    std::wstring res = wstr;
    for(auto &i: res){
        i = std::towlower(i);
    }
    wfile_out << L"std::towlower: " << res << std::endl;

    // std::towlower locale
    res = wstr;
    for(auto &i: res){
        i = std::tolower(i, loc);
    }
    wfile_out << L"std::towlower locale: " << res << std::endl;

    // std::ctype::tolower
    auto &ctype_loc = std::use_facet<std::ctype<wchar_t>>(loc);
    res = wstr;
    ctype_loc.tolower(&res[0], &res[0] + res.size());
    wfile_out << L"std::ctype::tolower: " << res << std::endl;

    return 0;
}
