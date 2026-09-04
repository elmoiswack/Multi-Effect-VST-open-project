PLUGIN_NAME = MultiEffectVST
BUILD_DIR = build

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    APP_PATH = $(BUILD_DIR)/MultiEffectVST_artefacts/Standalone/$(PLUGIN_NAME).app
    EXECUTABLE_PATH = $(APP_PATH)/Contents/MacOS/$(PLUGIN_NAME)

    PLATFORM_CLEAN = delete_appledouble
    PLATFORM_OPEN = openapp

else ifeq ($(UNAME_S),Linux)
    EXECUTABLE_PATH = $(BUILD_DIR)/MultiEffectVST_artefacts/Standalone/$(PLUGIN_NAME)

    PLATFORM_CLEAN =
    PLATFORM_OPEN =

else
    $(error Unsupported operating system: $(UNAME_S))
endif


.PHONY: all app re delete_appledouble cmake_build openapp executable clean


all: $(PLATFORM_CLEAN) cmake_build executable

app: $(PLATFORM_CLEAN) cmake_build $(PLATFORM_OPEN)

re: clean $(PLATFORM_CLEAN) cmake_build executable

delete_appledouble:
	@echo "Deleting AppleDouble files..."
	@find . -name '._*' -type f -delete

cmake_build:
	@echo "Configuring and building project..."
	@cmake -S . -B $(BUILD_DIR) -DFETCHCONTENT_QUIET=Off
	@cmake --build $(BUILD_DIR)

openapp:
	@echo "Opening the app..."
	@open $(APP_PATH)

executable:
	@echo "Running debug mode..."
	@./$(EXECUTABLE_PATH)

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
