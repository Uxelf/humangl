# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Iincludes -std=c++20 -MMD -MP -Wall -Werror -Wextra -g -O0

# Linker flags
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -g -O0

# Directories
SRCS_DIR = src
BUILD_DIR = build
OTHERS_DIR = others
GLAD_DIR = $(OTHERS_DIR)/GLAD
IMGUI_DIR = $(OTHERS_DIR)/imgui

INCLUDE_DIRS = -I./include -I./$(GLAD_DIR)/include -I./$(IMGUI_DIR)

# Create directories if they don't exist
$(shell mkdir -p $(BUILD_DIR))

# Source files
SRCS = \
	$(SRCS_DIR)/Animation_controller.cpp \
	$(SRCS_DIR)/Camera.cpp \
	$(SRCS_DIR)/create_window.cpp \
	$(SRCS_DIR)/Human.cpp \
	$(SRCS_DIR)/inputs_manager.cpp \
	$(SRCS_DIR)/instructions.cpp \
	$(SRCS_DIR)/main.cpp \
	$(SRCS_DIR)/Material.cpp \
	$(SRCS_DIR)/Matrix4x4.cpp \
	$(SRCS_DIR)/Mesh.cpp \
	$(SRCS_DIR)/Object.cpp \
	$(SRCS_DIR)/scene.cpp \
	$(SRCS_DIR)/Shader.cpp \
	$(SRCS_DIR)/UI.cpp \
	$(SRCS_DIR)/uniform_buffers.cpp \
	$(SRCS_DIR)/Vector3.cpp \
	$(SRCS_DIR)/Vector4.cpp \
	$(GLAD_DIR)/src/glad.c \
	$(IMGUI_DIR)/imgui_demo.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_impl_glfw.cpp \
	$(IMGUI_DIR)/imgui_impl_opengl3.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp \
	$(IMGUI_DIR)/imgui.cpp

# Object files
OBJS = $(patsubst $(SRCS_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(patsubst $(GLAD_DIR)/src/%.c,$(BUILD_DIR)/%.o,$(patsubst $(IMGUI_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))))

# Dependency files
DEPS = $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/%.d,$(OBJS))

# Output executable
TARGET = humangl

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	@printf "\e[95m\e[0;94mCompiled \e[1m\e[95m\e[92m$(TARGET)\e[0m\n"

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@
	@mkdir -p $(dir $@)

$(BUILD_DIR)/%.o: $(GLAD_DIR)/src/%.c
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@
	@mkdir -p $(dir $@)

$(BUILD_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@
	@mkdir -p $(dir $@)


# Include the generated dependency files
-include $(DEPS)

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET)

re: clean all

run: all
	./$(TARGET)

.PHONY: all clean re run
