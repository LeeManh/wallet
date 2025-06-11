cmake_minimum_required(VERSION 3.10)
project(wallet VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set minimum policy version for compatibility
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")

# Release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/deps/libbcrypt/include
    ${CMAKE_SOURCE_DIR}/deps/json/include
)

# Add libbcrypt as a subdirectory
add_subdirectory(deps/libbcrypt)

# Add libcotp as a subdirectory
add_subdirectory(deps/libcotp)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} bcrypt cotp)

# Add custom targets
add_custom_target(show_help
    COMMAND ${CMAKE_COMMAND} -E echo "Các lệnh có sẵn:"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target run    - Build và chạy chương trình"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target show_help   - Hiển thị thông tin giúp đỡ"
    COMMAND ${CMAKE_COMMAND} -E echo "  cmake --build . --target clean   - Xóa các file build"
)

# Add run target
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E echo "Building ${PROJECT_NAME}..."
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E echo "Running ${PROJECT_NAME}..."
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Add documentation target
find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating documentation..."
    )
endif()

# Enable testing
enable_testing()
add_test(NAME wallet_test COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests) 