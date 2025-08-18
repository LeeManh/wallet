#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
  #include <windows.h>
#endif

namespace vnconsole {

/* ===========================
   Console UTF-8 (Windows only)
   =========================== */
inline void initVietnameseConsole() {
#ifdef _WIN32
    // Đặt code page cho I/O là UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Bật VT processing để xử lý Unicode tốt hơn (Windows 10+)
    if (HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            mode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
    // Không đổi _setmode -> tiếp tục in bằng std::cout (UTF-8)
#endif
}

// In UTF-8 qua std::cout (portable)
inline void print(const std::string& utf8) {
    std::cout << utf8;
}

// In wstring trực tiếp (khi bạn thật sự cần wide)
inline void wprint(const std::wstring& w) {
#ifdef _WIN32
    DWORD written = 0;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),
                  w.c_str(), (DWORD)w.size(), &written, nullptr);
#else
    std::wcout << w;
#endif
}

/* =======================================
   UTF-8 helpers cho căn cột/bảng trong console
   (đếm theo số ký tự Unicode, không phải byte)
   ======================================= */

// Đếm số code point trong chuỗi UTF-8 (đủ cho tiếng Việt thường dùng)
inline size_t utf8_length(const std::string& s) {
    size_t count = 0;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if ((c & 0x80) == 0)        i += 1; // 0xxxxxxx
        else if ((c & 0xE0) == 0xC0) i += 2; // 110xxxxx
        else if ((c & 0xF0) == 0xE0) i += 3; // 1110xxxx
        else if ((c & 0xF8) == 0xF0) i += 4; // 11110xxx
        else                         i += 1; // fallback
        ++count;
    }
    return count;
}

// Pad phải (left = true) hoặc pad trái (left = false) theo số ký tự Unicode
inline std::string utf8_pad(const std::string& s, size_t width, bool left = true) {
    size_t len = utf8_length(s);
    if (len >= width) return s;
    size_t spaces = width - len;
    return left ? (s + std::string(spaces, ' '))
                : (std::string(spaces, ' ') + s);
}

// Tiện dụng: pad trái/phải rõ ràng
inline std::string pad_left (const std::string& s, size_t width)  { return utf8_pad(s, width, false); }
inline std::string pad_right(const std::string& s, size_t width)  { return utf8_pad(s, width, true ); }

} // namespace vnconsole
