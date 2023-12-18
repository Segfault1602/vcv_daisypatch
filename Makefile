# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

OPT = -O0

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -Isrc/not_daisy -Iexternals/daisySP/Source
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS += -Lexternals/daisySP/Build -ldaisysp

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)
SOURCES += $(wildcard src/not_daisy/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)
DISTRIBUTABLES += $(wildcard presets)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

.PHONY: build_daisysp

build_daisysp:
	./build_daisysp.sh
