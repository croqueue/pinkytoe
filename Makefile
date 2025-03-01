WFLAGS		:= -Wall -Werror -Wextra -pedantic
CPPSTD		:= c++17
LIBS		:= -lgtest_main -lgtest -lpthread
INCLUDE		:= -Iinclude
TEST_SRC	:= tests/libt3-test.cpp
BUILD_DIR	:= build

# Build targets
.PHONY		= test clean

test: $(BUILD_DIR)/libt3-test

clean:
	@rm -rf $(BUILD_DIR)

$(BUILD_DIR)/libt3-test: $(BUILD_DIR)
	@g++ -o $@ $(INCLUDE) $(WFLAGS) -std=$(CPPSTD) $(TEST_SRC) $(LIBS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
