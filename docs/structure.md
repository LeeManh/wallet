```txt
wallet/
├── src/                   # Thư mục chứa source code
│   ├── core/              # Core functionality
│   ├── utils/             # Utility functions
│   ├── models/            # Data models
│   └── services/          # Business logic services
├── include/               # Header files
│   ├── core/
│   ├── utils/
│   ├── models/
│   └── services/
├── tests/                 # Unit tests
├── docs/                  # Documentation
├── obj/                   # Object files (generated)
├── bin/                   # Executables (generated)
└── Makefile               # Build configuration
```

Giải thích cấu trúc:

1. **src/**: Chứa tất cả source code (.cpp files)

   - `core/`: Chứa các chức năng cốt lõi của ứng dụng
   - `utils/`: Chứa các hàm tiện ích
   - `models/`: Chứa các class định nghĩa cấu trúc dữ liệu
   - `services/`: Chứa logic nghiệp vụ

2. **include/**: Chứa tất cả header files (.h/.hpp)

   - Cấu trúc tương tự như src/
   - Giúp tách biệt interface và implementation

3. **tests/**: Chứa unit tests

   - Có thể sử dụng framework như Google Test

4. **docs/**: Chứa documentation

   - Có thể sử dụng Doxygen để tạo docs

5. **obj/**: Thư mục chứa các file object (.o)

   - Được tạo tự động khi build

6. **bin/**: Thư mục chứa executable
   - Được tạo tự động khi build

Makefile mới có các tính năng:

1. **Build modes**:

   - `make`: Build debug mode
   - `make debug`: Build với debug flags (-g -DDEBUG)
   - `make release`: Build với release flags (-O3)

2. **Tự động tìm source files**:

   - Tự động tìm tất cả .cpp files trong thư mục src
   - Tự động tạo cấu trúc thư mục obj tương ứng

3. **Các target hữu ích**:
   - `make run`: Build và chạy chương trình
   - `make clean`: Xóa các file build
   - `make docs`: Tạo documentation
   - `make test`: Chạy tests
   - `make help`: Hiển thị hướng dẫn

Để bắt đầu sử dụng cấu trúc này:

1. Đặt các file .cpp vào thư mục `src/` tương ứng
2. Đặt các file header vào thư mục `include/` tương ứng
3. Sử dụng các lệnh make để build và chạy

Ví dụ về cách tổ chức code:

```cpp
// include/core/wallet.hpp
#pragma once
namespace wallet {
class Wallet {
    // Interface definition
};
}

// src/core/wallet.cpp
#include "core/wallet.hpp"
namespace wallet {
// Implementation
}
```

Mở rộng project bằng cách:

1. Thêm module mới vào thư mục src/ và include/ tương ứng
2. Code mới sẽ tự động được include vào build process
3. Không cần sửa Makefile khi thêm file mới
