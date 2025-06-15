# Hệ thống quản lý ví điểm thưởng

## Giới thiệu

Hệ thống quản lý ví điểm thưởng là một ứng dụng cho phép người dùng quản lý điểm thưởng của họ. Hệ thống cung cấp các chức năng như đăng ký, đăng nhập, và quản lý điểm thưởng.

## Cài đặt

### Windows

Xem hướng dẫn chi tiết tại [docs/windows.md](docs/windows.md)

### Yêu cầu hệ thống

- C++17 trở lên
- CMake 3.5 trở lên
- Git

### Các bước cài đặt

1. Clone repository:

```bash
git clone https://github.com/LeeManh/wallet.git
cd wallet
```

2. Lấy các dependencies (submodules):

```bash
git submodule update --init --recursive
```

3. Tạo thư mục build và cấu hình project:

```bash
mkdir build
cd build
cmake ..
```

## Sử dụng

### Chạy chương trình

```bash
cd build
cmake --build . --target run
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

## Cấu trúc thư mục

```
.
├── build/          # Thư mục build (tự động tạo)
│   └── bin/        # Thư mục chứa file thực thi
├── data/           # Thư mục chứa dữ liệu
├── deps/           # Thư mục chứa các dependencies
│   ├── json/       # Thư viện JSON
│   └── libbcrypt/  # Thư viện mã hóa mật khẩu
├── include/        # Thư mục chứa các file header
├── src/            # Thư mục chứa mã nguồn
├── tests/          # Thư mục chứa các test
└── CMakeLists.txt  # File cấu hình CMake
```

## Thành viên tham gia

- [Tên thành viên] - [Công việc được giao]

## Tài liệu tham khảo

- [Tên tài liệu] - [Link tài liệu]
