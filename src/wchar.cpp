#include <iostream>
#include <cwchar>
#include <cstring>

int main() {
    char str[] = "Hello";
    std::cout << "Length: " << strlen(str) << std::endl;  // 5
    
    wchar_t wstr[] = L"Hallå!";
    std::wcout << L"Length: " << wcslen(wstr) << std::endl;  // 6
    
    // Wide character literal
    wchar_t swedish = L'Ö';
    
    return 0;
}
