# Tên chương trình
TARGET = wallet

# Trình biên dịch và flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O3

# Thư mục chứa source code và object files
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Tìm tất cả các file .cpp trong thư mục src và các thư mục con
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Tạo thư mục bin và obj nếu chưa tồn tại
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(OBJ_DIR))

# Target mặc định
all: $(BIN_DIR)/$(TARGET)

# Build chương trình
$(BIN_DIR)/$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@

# Build các file object
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build chương trình với debug flags
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Build chương trình với release flags
release: CXXFLAGS += $(RELEASE_FLAGS)
release: clean all

# Chạy chương trình
run: all
	./$(BIN_DIR)/$(TARGET)

# Clean project
clean:
	@echo "Cleaning..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Tạo documentation
docs:
	@echo "Generating documentation..."
	doxygen Doxyfile

# Chạy tests
test: all
	@echo "Running tests..."
	./$(BIN_DIR)/tests

# Help
help:
	@echo "Các lệnh có sẵn:"
	@echo "  make        - Build chương trình (debug mode)"
	@echo "  make debug  - Build với debug flags"
	@echo "  make release - Build với release flags"
	@echo "  make run    - Build và chạy chương trình"
	@echo "  make clean  - Xóa các file build"
	@echo "  make docs   - Tạo documentation"
	@echo "  make test   - Chạy tests"
	@echo "  make help   - Hiển thị thông tin giúp đỡ"

.PHONY: all debug release run clean docs test help
