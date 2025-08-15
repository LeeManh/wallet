# Yêu cầu phiên bản CMake tối thiểu là 3.10
# Điều này đảm bảo rằng các tính năng mới của CMake sẽ hoạt động đúng
cmake_minimum_required(VERSION 3.10)

# Đặt tên project là wallet và phiên bản 1.0
# Tên project sẽ được sử dụng làm tên mặc định cho file thực thi
project(wallet VERSION 1.0)

# Thiết lập chuẩn C++17 và bắt buộc phải sử dụng
# C++17 cung cấp nhiều tính năng mới như std::optional, std::variant,...
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thiết lập phiên bản policy tối thiểu để đảm bảo tính tương thích
# Policy version 3.5 giúp tránh các vấn đề về tương thích ngược
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Thêm cờ cảnh báo cho compiler
# -Wall: bật tất cả các cảnh báo thông thường
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Thêm cờ debug: 
# -g: thêm thông tin debug vào file thực thi
# -DDEBUG: định nghĩa macro DEBUG để có thể sử dụng #ifdef DEBUG trong code
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")

# Thêm cờ release: 
# -O3: tối ưu hóa code ở mức cao nhất, có thể làm tăng thời gian biên dịch
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Thêm các thư mục include cho project
# Các thư mục này sẽ được thêm vào đường dẫn tìm kiếm header files
include_directories(
    ${CMAKE_SOURCE_DIR}/include        # Thư mục chứa các header files của project
    ${CMAKE_SOURCE_DIR}/deps/libbcrypt/include  # Header files của thư viện bcrypt
    ${CMAKE_SOURCE_DIR}/deps/json/include      # Header files của thư viện json
)

# Thêm thư viện libbcrypt như một subdirectory
# libbcrypt là thư viện mã hóa mật khẩu
add_subdirectory(deps/libbcrypt)

# Thêm thư viện libcotp như một subdirectory
# libcotp là thư viện tạo mã OTP (One-Time Password)
add_subdirectory(deps/libcotp)

# Tìm tất cả các file nguồn .cpp trong thư mục src
# GLOB_RECURSE sẽ tìm kiếm trong tất cả các thư mục con
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Thiết lập các thư mục output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # Thư mục chứa file thực thi
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Thư mục chứa file thư viện tĩnh (.a)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # Thư mục chứa file thư viện động (.so/.dll)

# Macro đường dẫn tuyệt đối (dùng được trên Win/mac/Linux)
target_compile_definitions(${PROJECT_NAME} PRIVATE
  DATA_DIR="${CMAKE_SOURCE_DIR}/data"
  BACKUP_DIR="${CMAKE_SOURCE_DIR}/backup"

# Tạo file thực thi từ các file nguồn
# ${PROJECT_NAME} sẽ được thay thế bằng "wallet"
add_executable(${PROJECT_NAME} ${SOURCES})

# Liên kết các thư viện cần thiết
# bcrypt: thư viện mã hóa mật khẩu
# cotp: thư viện tạo mã OTP
target_link_libraries(${PROJECT_NAME} bcrypt cotp)

# Thêm target hiển thị thông tin giúp đỡ
# Target này sẽ hiển thị danh sách các lệnh có sẵn khi chạy
add_custom_target(show_help
    COMMAND ${CMAKE_COMMAND} -E echo "Các lệnh có sẵn:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target run    - Build và chạy chương trình"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target show_help   - Hiển thị thông tin giúp đỡ"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target clean   - Xóa các file build"
)

# Thêm target để build và chạy chương trình
# Target này sẽ tự động build và chạy chương trình
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E echo "Building ${PROJECT_NAME}..."  # In thông báo đang build
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}  # Build project
    COMMAND ${CMAKE_COMMAND} -E echo "Running ${PROJECT_NAME}..."   # In thông báo đang chạy
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}       # Chạy chương trình
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}  # Đặt thư mục làm việc là thư mục gốc của project
)

# Thêm target để tạo tài liệu bằng Doxygen
# Chỉ thêm target này nếu Doxygen được cài đặt trên hệ thống
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile  # Chạy Doxygen với file cấu hình
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}  # Đặt thư mục làm việc
        COMMENT "Generating documentation..."  # Thông báo đang tạo tài liệu
    )
endif()

# Bật tính năng testing của CMake
# Cho phép sử dụng các lệnh testing như add_test
enable_testing()

# Thêm test case cho project
# Tạo một test case tên là wallet_test
# Test case này sẽ chạy file thực thi tests trong thư mục bin
add_test(NAME wallet_test COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests) 

# test message
