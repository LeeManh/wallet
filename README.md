# Hệ thống quản lý ví điểm thưởng

## Giới thiệu

Hệ thống quản lý ví điểm thưởng là một ứng dụng cho phép người dùng quản lý điểm thưởng của họ. Hệ thống cung cấp các chức năng như đăng ký, đăng nhập, và quản lý điểm thưởng.

## Hướng dẫn cài đặt

Để bắt đầu, vui lòng tham khảo các tài liệu hướng dẫn chi tiết dưới đây:

- **[⚙️ Yêu Cầu Hệ Thống](docs/system_requirements.md)**
- **[🪟 Hướng Dẫn Cài Đặt trên Windows](docs/windows.md)**
- **[🍎 Hướng Dẫn Cài Đặt trên macOS](docs/macos.md)**
- **[🛠️ Hướng Dẫn Cài Đặt trên WSL (Windows Subsystem for Linux)](docs/wsl.md)**

## Sử dụng

Sau khi đã cài đặt và build project theo hướng dẫn, bạn có thể chạy chương trình.

### Chạy chương trình

```bash
cd build
./wallet # Trên macOS/Linux
.\wallet.exe # Trên Windows
```

### Các lệnh có sẵn

- `cmake --build . --target run` - Build và chạy chương trình
- `cmake --build . --target show_help` - Hiển thị thông tin giúp đỡ

### Clean project

```bash
# Cách 1: Sử dụng target clean
cmake --build . --target clean

# Cách 2: Xóa toàn bộ thư mục build (khuyến nghị)
rm -rf build
```

## 🔐 Vấn Đề Thường Gặp

### Lỗi quyền truy cập files

Nếu gặp lỗi "Không thể mở file: data/users.json", hãy tham khảo:

- **[🔧 Troubleshooting](docs/troubleshooting.md)** - Hướng dẫn chi tiết
- **[🍎 macOS](docs/macos.md#6--cấp-quyền-tạo-files-và-chạy-seed-data)** - Cấp quyền trên macOS
- **[🪟 Windows](docs/windows.md#5--cấp-quyền-tạo-files-và-chạy-seed-data)** - Cấp quyền trên Windows
- **[🛠️ WSL](docs/wsl.md#6--cấp-quyền-tạo-files-và-chạy-seed-data)** - Cấp quyền trên WSL

### Lỗi build

Nếu gặp lỗi duplicate symbol hoặc build fail, hãy:

```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```

## Thành viên tham gia

- [Tên thành viên] - [Công việc được giao]

## Tài liệu tham khảo

- [Tên tài liệu] - [Link tài liệu]
