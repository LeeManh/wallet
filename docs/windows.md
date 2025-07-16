# 🪟 Hướng Dẫn Cài Đặt trên Windows (Native)

## 1. Cài Đặt Visual Studio

- Tải về **Visual Studio Installer** từ [trang chủ của Microsoft](https://visualstudio.microsoft.com/downloads/).
- Khi cài đặt, chọn Workload **"Desktop development with C++"**. Workload này đã bao gồm:
  - Trình biên dịch MSVC C++.
  - **CMake**.
  - **Git for Windows**.

## 2. Clone Project và Tải Dependencies

Mở **Git Bash** (được cài cùng với Git for Windows) hoặc Command Prompt và chạy:

```bash
# Clone project
git clone https://github.com/LeeManh/wallet.git
cd wallet

# Tải về các dependencies (submodules)
git submodule update --init --recursive
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

File thực thi `wallet.exe` sẽ được tạo trong thư mục `build/Debug` (hoặc `build/Release`).

## 5. 🔐 Cấp Quyền Tạo Files và Chạy Seed Data

### Kiểm tra quyền hiện tại

```cmd
dir
```

### Tạo thư mục data

```cmd
mkdir data
```

### Kiểm tra quyền ghi

```cmd
echo test > data\test.txt
del data\test.txt
```

### Nếu gặp lỗi quyền truy cập, thử các cách sau:

**Cách 1: Chạy Command Prompt với quyền Administrator**

1. Nhấn `Win + X`
2. Chọn "Windows PowerShell (Admin)" hoặc "Command Prompt (Admin)"
3. Điều hướng đến thư mục project và chạy lại

**Cách 2: Thay đổi quyền thư mục**

1. Chuột phải vào thư mục `wallet`
2. Chọn "Properties"
3. Tab "Security" → "Edit"
4. Chọn user của bạn → "Full Control" → "Apply"

**Cách 3: Tắt Windows Defender hoặc Antivirus tạm thời**

- Một số antivirus có thể chặn việc tạo file
- Tắt tạm thời để test

## 6. 🚀 Chạy Chương Trình

```cmd
cd build\Debug
wallet.exe
```

Hoặc nếu build ở Release mode:

```cmd
cd build\Release
wallet.exe
```

Nếu thành công, bạn sẽ thấy thông báo:

```
✅ Khởi tạo dữ liệu thành công!
```

Nếu gặp lỗi quyền truy cập, hãy thực hiện các bước trong phần 5.
