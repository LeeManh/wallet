# 🍎 Hướng Dẫn Cài Đặt trên macOS

## 1. Cài Đặt Xcode Command Line Tools

Mở Terminal và chạy lệnh sau để cài đặt các công cụ cần thiết như Git và trình biên dịch Clang:

```bash
xcode-select --install
```

## 2. Cài Đặt Homebrew

Homebrew là trình quản lý gói phổ biến cho macOS. Dán lệnh sau vào Terminal để cài đặt:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## 3. Cài Đặt CMake

Sử dụng Homebrew để cài đặt CMake:

```bash
brew install cmake
```

## 4. Clone Project

```bash
git clone https://gitlab.com/LeeManh/wallet.git
cd wallet
```

## 5. Build Project

Tạo thư mục build và chạy CMake:

```bash
mkdir build
cd build
cmake ..
make
```

Sau khi build thành công, file thực thi `wallet` sẽ nằm trong thư mục `build`.

## 6. 🔐 Cấp Quyền Tạo Files và Chạy Seed Data

### Kiểm tra quyền hiện tại

```bash
ls -la
```

### Tạo thư mục data với quyền đầy đủ

```bash
mkdir -p data
chmod 755 data
```

### Kiểm tra quyền ghi

```bash
touch data/test.txt
rm data/test.txt
```

### Nếu gặp lỗi quyền truy cập, thử các cách sau:

**Cách 1: Thay đổi quyền sở hữu**

```bash
sudo chown $USER:$USER data/
```

**Cách 2: Chạy với sudo (tạm thời)**

```bash
sudo ./build/bin/wallet
```

**Cách 3: Kiểm tra quyền thư mục cha**

```bash
ls -la ../
chmod 755 ../
```

## 7. 🚀 Chạy Chương Trình

```bash
cd build
./wallet
```

Nếu thành công, bạn sẽ thấy thông báo:

```
✅ Khởi tạo dữ liệu thành công!
```

Nếu gặp lỗi quyền truy cập, hãy thực hiện các bước trong phần 6.
