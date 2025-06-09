# Hệ thống quản lý ví điểm thưởng

## Giới thiệu

Hệ thống quản lý ví điểm thưởng là một ứng dụng cho phép người dùng quản lý điểm thưởng của họ. Hệ thống cung cấp các chức năng như đăng ký, đăng nhập, và quản lý điểm thưởng.

## Cài đặt

### Yêu cầu hệ thống

- C++17 trở lên
- CMake 3.10 trở lên
- Make
- Git

### Các bước cài đặt

1. Clone repository:

```bash
git clone <repository-url>
```

2. Lấy các dependencies (submodules):

```bash
git submodule update --init --recursive
```

3. Build project:

```bash
make
```

## Sử dụng

### Chạy chương trình

```bash
make run
```

### Các lệnh make có sẵn

- `make` - Build chương trình (debug mode)
- `make debug` - Build với debug flags
- `make release` - Build với release flags
- `make run` - Build và chạy chương trình
- `make clean` - Xóa các file build
- `make docs` - Tạo documentation
- `make test` - Chạy tests
- `make help` - Hiển thị thông tin giúp đỡ

## Cấu trúc thư mục

```
.
├── bin/            # Thư mục chứa file thực thi
├── deps/           # Thư mục chứa các dependencies
│   ├── json/       # Thư viện JSON
│   └── libbcrypt/  # Thư viện mã hóa mật khẩu
├── include/        # Thư mục chứa các file header
├── src/           # Thư mục chứa mã nguồn
└── tests/         # Thư mục chứa các test
```

## Thành viên tham gia

- [Tên thành viên] - [Công việc được giao]

## Tài liệu tham khảo

- [Tên tài liệu] - [Link tài liệu]
