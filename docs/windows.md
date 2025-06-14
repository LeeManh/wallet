# 🛠️ Hướng Dẫn Setup & Làm Việc Trên WSL

## 1. 🚀 Cài Đặt WSL và Ubuntu

### Cài WSL (trên Windows)

```bash
wsl --install
```

Sau khi cài đặt xong và đã vào WSL terminal (Ubuntu), chạy:

```bash
sudo apt update
sudo apt install libgcrypt20-dev cmake g++ make
```

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

## 3. 📦 Clone Project về WSL

Tạo thư mục và clone dự án:

```bash
mkdir -p ~/projects/wallet
cd ~/projects/wallet
git clone git@github.com:LeeManh/wallet.git
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

## ✅ Hoàn Tất

Giờ bạn có thể build và phát triển dự án ngay bên trong WSL + VS Code.
