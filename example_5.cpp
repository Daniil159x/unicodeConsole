// UTF-8 with BOM

#include <iostream>
#include <string>
#include <fstream>

#include "unicodesetting.hpp"

int main()
{
    auto loc = InitUnicodeStreams();

    std::wstring wstr;

    std::wcout << L"Input string: ";
    std::getline(std::wcin, wstr);

    std::wcout << L"Writes..." << std::endl;
    std::wofstream wfile_out("out.txt");
    wfile_out.imbue(loc);
    wfile_out << wstr;
    wfile_out.close();

    wstr.clear();

    std::wcout << L"Reads..." << std::endl;
    std::wifstream wfile_in("out.txt");
    wfile_in.imbue(loc);
    std::getline(wfile_in, wstr);
    wfile_in.close();

    std::wcout << L"String: '" << wstr << "'" << std::endl;

    return 0;
}
