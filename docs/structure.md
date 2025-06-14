### Services :

**Chức năng chính :**

- xử lý logic nghiệp vụ
- thực hiện các tính toán phức tạp

### Controllers :

**Chức năng chính :**

- xử lý yêu cầu từ view
- giao tiếp giữa view và service
- quản lý luồng xử lý

### Views :

**Chức năng chính :**

- hiển thị giao diện người dùng
- nhận đầu vào từ người dùng

### Luồng xử lý :

- View nhận đầu vào từ người dùng
- Controller xử lý yêu cầu và gọi service
- Service thực hiện các tính toán và trả về kết quả cho controller
- View hiển thị kết quả cho người dùng

**Ví dụ :**

- Đăng nhập :
  - View nhận đầu vào từ người dùng
  - Controller xử lý yêu cầu và gọi service
  - Service thực hiện các tính toán và trả về kết quả
  - View hiển thị kết quả
