// UTF-8 with BOM

#include <iostream>
#include <string>

#include "unicodesetting.hpp"

int main()
{
    auto loc = InitUnicodeStreams();

    std::wstring wstr_arr[] {
        L"English:  Hello!",
        L"Russian:  Привет!",
        L"Greek:    Χαίρετε!",
        L"Japanese: こんにちは!",
        L"Czech:    Ahoj!"
    };

    for(const auto &i : wstr_arr){
        std::wcout << i << std::endl;
    }

    return 0;
}
