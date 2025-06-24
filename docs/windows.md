# 🪟 Hướng Dẫn Cài Đặt trên Windows (Native)

## 1. Cài Đặt Visual Studio

- Tải về **Visual Studio Installer** từ [trang chủ của Microsoft](https://visualstudio.microsoft.com/downloads/).
- Khi cài đặt, chọn Workload **"Desktop development with C++"**. Workload này đã bao gồm:
  - Trình biên dịch MSVC C++.
  - **CMake**.
  - **Git for Windows**.

## 2. Clone Project

Mở **Git Bash** (được cài cùng với Git for Windows) hoặc Command Prompt và chạy:

```bash
git clone https://gitlab.com/LeeManh/wallet.git
cd wallet
```

## 3. Build Project (Sử dụng Visual Studio)

1.  Mở Visual Studio.
2.  Chọn **"Open a local folder"** và trỏ đến thư mục `wallet` bạn vừa clone.
3.  Visual Studio sẽ tự động nhận diện `CMakeLists.txt` và cấu hình project.
4.  Để build, chọn **Build > Build All** từ menu.
5.  File thực thi `wallet.exe` sẽ được tạo trong thư mục `build/Debug` (hoặc `build/Release`).

## 4. Build Project (Sử dụng Command Line)

Mở **Developer Command Prompt for VS** (tìm trong Start Menu) và chạy các lệnh sau:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

File thực thi `wallet.exe` sẽ được tạo trong thư_mục `build/Debug` (hoặc `build/Release`).
