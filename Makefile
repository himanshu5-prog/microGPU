# Compiler
CXX ?= clang++
# CXX := g++

# Target binary
TARGET := microGPU

# Directories
SRC_DIR := src
BUILD_DIR := build

# Automatically find all source files
SOURCES := $(shell find $(SRC_DIR) -name "*.cc")

# Build mode (default = debug)
BUILD ?= debug

OBJ_DIR := $(BUILD_DIR)/$(BUILD)
OBJECTS := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

##################################################
# Flags
##################################################

WARNING_FLAGS := -Wall -Wextra -Wpedantic -Werror
COMMON_FLAGS := -std=c++20 -MMD -MP -fno-omit-frame-pointer

DEBUG_FLAGS := -O0 -g
RELEASE_FLAGS := -O3 -DNDEBUG

SANITIZE_FLAGS := -fsanitize=address,undefined

CXXFLAGS := $(COMMON_FLAGS) $(WARNING_FLAGS)

ifeq ($(BUILD),release)
	CXXFLAGS += $(RELEASE_FLAGS)
else ifeq ($(SAN),1)
	CXXFLAGS += $(SANITIZE_FLAGS) -O1 -g
	LDFLAGS += $(SANITIZE_FLAGS)
else
	CXXFLAGS += $(DEBUG_FLAGS)
endif

##################################################
# Targets
##################################################

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile rule with auto-directory creation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

-include $(DEPS)

.PHONY: all clean rebuild
