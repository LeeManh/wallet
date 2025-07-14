# 🛠️ Hướng Dẫn Setup & Làm Việc Trên WSL

## 1. 🚀 Cài Đặt WSL và Ubuntu

### Cài WSL (trên Windows)

```bash
wsl --install
```

### Mở WSL đã cài sẵn (trên Windows)

```bash
wsl
```

> Lệnh này sẽ mở default Linux distro (e.g: Ubuntu) trên terminal

Sau khi cài đặt xong và đã vào WSL terminal (Ubuntu), chạy:

```bash
sudo apt update
sudo apt install libgcrypt20-dev cmake g++ make
```

> Lệnh này sẽ cài đặt:
> GNU compilers (gcc/g++)
> pkg-config (required cho việc tìm kiếm libraries)
> libgcrypt20-dev (cài đặt GCRYPT_LIBRARIES và GCRYPT_INCLUDE_DIR)

---

## 2. 🔐 Tạo SSH Key để Kết Nối với GitHub

### Tạo SSH Key trong WSL

Mở terminal trong WSL và chạy:

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

> 📝 **Lưu ý**: Thay `your_email@example.com` bằng email bạn đã dùng để đăng ký GitHub.

Sau đó lấy nội dung public key:

```bash
cd ~/.ssh
cat id_ed25519.pub
```

> 📋 Copy toàn bộ nội dung public key hiển thị.

---

### Thêm SSH Key vào GitHub

1. Đăng nhập GitHub.
2. Click vào avatar → **Settings**.
3. Chọn **SSH and GPG keys** → click **New SSH key**.
4. Điền:
   - **Title**: tùy chọn
   - **Key type**: Authentication Key
   - **Key**: Dán public key đã copy
5. Click **Add SSH key**.

---

## 3. 📦 Clone Project và Tải Dependencies về WSL

Tạo thư mục và clone dự án:

```bash
mkdir -p ~/projects/wallet
cd ~/projects/wallet
git clone git@github.com:LeeManh/wallet.git
cd wallet

# Tải về các dependencies (submodules)
git submodule update --init --recursive
```

---

## 4. 💻 Mở Dự Án trong VS Code (Kết Nối qua WSL)

### ✅ Cách 1: Mở từ Terminal

```bash
cd ~/projects/wallet/wallet
code .
```

> Khi VS code được mở, chọn đường dẫn:  
> `/home/<your_wsl_username>/projects/wallet/wallet`

---

### ✅ Cách 2: Mở Từ Giao Diện VS Code

1. Mở **VS Code** (trên Windows).
2. Trong trang Welcome → chọn **Connect to WSL**.
3. Sau khi vào WSL, chọn **File > Open Folder**.
4. Điều hướng đến:  
   `/home/<your_wsl_username>/projects/wallet/wallet`

---

## 5. 🔨 Build Project

```bash
mkdir build
cd build
cmake ..
make
```

---

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

**Cách 4: Kiểm tra quyền WSL**

```bash
# Nếu WSL không có quyền ghi vào Windows filesystem
# Chuyển project vào WSL filesystem
cp -r /mnt/c/path/to/wallet ~/wallet
cd ~/wallet
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

---

## ✅ Hoàn Tất

Giờ bạn có thể build và phát triển dự án ngay bên trong WSL + VS Code.
