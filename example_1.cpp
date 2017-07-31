// UTF-8 with BOM

#include <iostream>

#include "unicodesetting.hpp"

int main()
{
    auto loc = InitUnicodeStreams();

    std::wcout << L"English:  Hello!" << std::endl;
    std::wcout << L"Russian:  Привет!" << std::endl;
    std::wcout << L"Greek:    Χαίρετε!" << std::endl;
    std::wcout << L"Japanese: こんにちは!" << std::endl;
    std::wcout << L"Czech:    Ahoj!" << std::endl;

    return 0;
}
