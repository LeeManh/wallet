# 🛠️ Hướng Dẫn Quy Trình Làm Việc Với Git

## 1. 🚀 Tạo và chuyển sang nhánh mới

```bash
git checkout -b feature/your-feature-name
```

> 📌 **Lưu ý:**
>
> - Tên nhánh nên theo quy ước: `feature/`, `bugfix/`, `hotfix/`
> - Tránh làm việc trực tiếp trên nhánh `main`

---

## 2. 💻 Làm việc trên nhánh mới

- Thực hiện các thay đổi trong code.
- Commit các thay đổi:

```bash
git add .
git commit -m "Mô tả ngắn gọn về thay đổi"
```

> ✏️ **Gợi ý:** Viết commit message rõ ràng, ngắn gọn và mô tả đúng nội dung thay đổi.

---

## 3. 🔄 Khi muốn merge code

### Cập nhật nhánh `main` mới nhất:

```bash
git checkout main
git pull origin main
```

### Quay lại nhánh `feature` và **rebase** với `main`:

```bash
git checkout feature/your-feature-name
git rebase main
```

> ⚠️ Nếu có conflict, hãy giải quyết rồi tiếp tục bằng:

```bash
git add .
git rebase --continue
```

---

## 4. 📥 Tạo Pull Request (PR)

### Đẩy nhánh lên remote:

```bash
git push origin feature/your-feature-name
```

### Tạo PR trên GitHub/GitLab:

- Nhánh nguồn: `feature/your-feature-name`
- Nhánh đích: `main`
- Thêm tiêu đề & mô tả PR
- Yêu cầu review từ các thành viên liên quan

---

## 5. 👀 Quy trình review

- Các thành viên **review code**
- Nếu có góp ý:

  - Cập nhật code
  - Push lại lên cùng nhánh `feature`

- Khi được **approve**, tiến hành **merge vào `main`**

---

## 6. 🧹 Sau khi merge

### Xóa nhánh `feature` ở local:

```bash
git checkout main
git branch -d feature/your-feature-name
```

### Xóa nhánh `feature` ở remote:

```bash
git push origin --delete feature/your-feature-name
```

---

## 7. 🔄 Cập nhật nhánh `main` local

```bash
git checkout main
git pull origin main
```

---

## ✅ Ghi nhớ

- Luôn tạo **nhánh mới** cho mỗi tính năng hoặc bug fix.
- **Không** push trực tiếp lên `main`.
- Luôn tạo PR và yêu cầu review trước khi merge.
