SHELL = /bin/bash
ifndef .VERBOSE
  .SILENT:
endif

NAME=estl

CC=clang
CXX=clang++
CFLAGS=-Wall
CXXFLAGS=-Wall -std=c++17 -fPIC -Wall -Wextra -Wpedantic -Wno-gnu-zero-variadic-macro-arguments -Wno-ignored-optimization-argument
LINK=
INCLUDE=

SOURCE_DIR=source
INCLUDE_DIR=estl
BUILD_DIR=build
DOC_DIR=docs
TEST_DIR=test
EXAMPLE_DIR=example
EXTERNAL_DIR=external
INSTALL_PATH?=/usr/local
ROOT=$(shell pwd)

SCAN_COLOR=\033[1;35m
BUILD_COLOR=\033[32m
CLEAN_COLOR=\033[1;33m
LINK_COLOR=\033[1;32m
INSTALL_COLOR=\033[01;36m
CMD_COLOR=\033[1;34m
HELP_COLOR=\033[1;34m

# FUNCTIONS{{{
define scan_target
printf "%b%s%b\n" "$(SCAN_COLOR)" "Scaning dependencies for target $(1)" "\033[0m"
endef
define complete_target
printf "%s\n" "Built target $(1)"
endef
define clean_target
printf "%b%s%b\n" "$(CLEAN_COLOR)" "Cleaning target $(1)" "\033[0m"
endef
define install_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Installing target $(1)" "\033[0m"
endef
define uninstall_target
printf "%b%s%b\n" "$(INSTALL_COLOR)" "Unnstalling target $(1)" "\033[0m"
endef
define print_build_c
str=$$(realpath --relative-to="$(ROOT)" "$(1)");\
    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building C object $$str" "\033[0m"
endef
define print_build_cpp
str=$$(realpath --relative-to="$(ROOT)" "$(1)");\
    printf "%b%s%b\n" "$(BUILD_COLOR)" "Building Cpp object $$str" "\033[0m"
endef
define print_link_lib
str=$$(realpath --relative-to="$(ROOT)" "$(1)");\
    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking static library $$str" "\033[0m"
endef
define print_link_exe
str=$$(realpath --relative-to="$(ROOT)" "$(1)");\
    printf "%b%s%b\n" "$(LINK_COLOR)" "Linking executable $$str" "\033[0m"
endef
define print_run_cmd
printf "%b%s%b\n" "$(CMD_COLOR)" "Running '$(1)'" "\033[0m"
endef
define help
printf "%b%*s%b: %s\n" "$(HELP_COLOR)" 20 "$(1)" "\033[0m" "$(2)"
endef
# }}}

GTEST_DIR=$(ROOT)/$(EXTERNAL_DIR)/googletest/googletest

LIB=$(ROOT)/$(BUILD_DIR)/lib$(NAME).a
EXE=$(ROOT)/$(NAME).out
TEST_EXE=$(ROOT)/unit-test

LIB_FILES = $(filter-out $(SOURCE_DIR)/main.cpp, $(filter-out $(SOURCE_DIR)/main.c, $(shell find "$(SOURCE_DIR)" -name "*.c")))
LIB_OBJS = $(LIB_FILES:%=$(ROOT)/$(BUILD_DIR)/%.o)
EXE_FILES = $(shell find "$(SOURCE_DIR)" -name "main.c") $(shell find "$(SOURCE_DIR)" -name "main.cpp")
EXE_OBJS = $(EXE_FILES:%=$(ROOT)/$(BUILD_DIR)/%.o)
TEST_FILES = $(shell find "$(TEST_DIR)" -name "*.c") $(shell find "$(TEST_DIR)" -name "*.cpp")
TEST_OBJS = $(TEST_FILES:%=$(ROOT)/$(BUILD_DIR)/%.o)

all: source test

clean: clean-source clean-docs clean-test

install: install-source

uninstall: uninstall-source

test: build-test

# DOCS{{{
doc:
	$(call print_run_cmd,doxygen)
	doxygen

clean-docs:
	$(call clean_target,docs)
	if [ -d "$(DOC_DIR)/html" ]; then rm "$(DOC_DIR)/html" -r ;fi
	if [ -d "$(DOC_DIR)/latex" ]; then rm "$(DOC_DIR)/latex" -r ;fi
	if [ -d "$(DOC_DIR)/xml" ]; then rm "$(DOC_DIR)/xml" -r ;fi
# }}}
# SOURCE{{{
source: build-exe

clean-source: clean-lib clean-exe
	if [ -e "$(ROOT)/$(BUILD_DIR)/$(SOURCE_DIR)" ]; then rm $(ROOT)/$(BUILD_DIR)/$(SOURCE_DIR) -r; fi

install-source: install-lib

uninstall-source: uninstall-lib
# }}}
# LIB {{{
build-lib: pre-lib $(LIB)
	$(call complete_target,$(shell basename $(LIB)))

clean-lib:
	$(call clean_target,$(shell basename $(LIB)))
	if [ -e "$(LIB)" ]; then rm $(LIB); fi

install-lib: build-lib
	$(call install_target,$(shell basename $(LIB)))
	mkdir -p $(INSTALL_PATH)/lib/
	mkdir -p $(INSTALL_PATH)/include/$(NAME)/
	if [ -e "$(LIB)" ]; then cp $(LIB) $(INSTALL_PATH)/lib; fi
	if [ ! -z "$(INCLUDE_DIR)" ]; then cp -R $(INCLUDE_DIR)/ $(INSTALL_PATH)/include/$(NAME)/; fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.h")" ]; then cd $(SOURCE_DIR) && cp --parents $(shell cd $(SOURCE_DIR) && find . -name "*.h") $(INSTALL_PATH)/include/$(NAME); fi
	if [ ! -z "$(shell find $(SOURCE_DIR) -name "*.hpp")" ]; then cd $(SOURCE_DIR) && cp --parents $(shell cd $(SOURCE_DIR) && find . -name "*.hpp") $(INSTALL_PATH)/include/$(NAME); fi

uninstall-lib:
	$(call uninstall_target,$(shell basename $(LIB)))
	if [ ! -e "$(INSTALL_PATH)/lib/$(shell basename $(LIB))" ]; then rm "$(INSTALL_PATH)/lib/$(shell basename $(LIB))"; fi
	if [ ! -e "$(INSTALL_PATH)/include/$(NAME)" ]; then rm "$(INSTALL_PATH)/include/$(NAME)" -r; fi

$(LIB): $(LIB_OBJS)
	if [ ! -z "$(LIB_OBJS)" ]; then $(call print_link_lib,$(shell basename $(LIB))); fi
	if [ ! -z "$(LIB_OBJS)" ]; then ar rcs $@ $(LIB_OBJS); fi

pre-lib:
	$(call scan_target,$(shell basename $(LIB)))
# }}}
# EXE {{{
build-exe: build-lib pre-exe $(EXE)
	$(call complete_target,$(shell basename $(EXE)))

clean-exe:
	$(call clean_target,$(shell basename $(EXE)))
	if [ -e "$(EXE)" ]; then rm $(EXE); fi

install-exe:
	$(call install_target,$(shell basename $(EXE)))
	mkdir -p $(INSTALL_PATH)/bin/
	cp $(EXE) $(INSTALL_PATH)/bin

uninstall-exe:
	$(call uninstall_target,$(shell basename $(EXE)))
	if [ -e "$(INSTALL_PATH)/bin/$(shell basename $(EXE))" ]; then rm $(INSTALL_PATH)/bin/$(shell basename $(EXE)); fi

$(EXE): $(EXE_OBJS)
	$(call print_link_exe,$(shell basename $(EXE)))
	if [ -e "$(LIB)" ]; then $(CC) $(CFLAGS) $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) $(EXE_OBJS) $(LIB) $(LINK) -o $@; \
	else $(CXX) $(CXXFLAGS) $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) $(EXE_OBJS) $(LINK) -o $@; fi

pre-exe:
	$(call scan_target,$(shell basename $(EXE)))
# }}}
# GTEST {{{
build-gtest: pre-gtest $(ROOT)/$(BUILD_DIR)/libgtest.a
	$(call complete_target,gtest)

$(ROOT)/$(BUILD_DIR)/libgtest.a: $(GTEST_DIR)/src/gtest-all.cc $(GTEST_DIR)/src/gtest_main.cc
	mkdir -p $(ROOT)/$(BUILD_DIR)/gtest
	$(call print_build_cpp,$(ROOT)/$(BUILD_DIR)/gtest/gtest-all.cpp.o)
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc -o $(ROOT)/$(BUILD_DIR)/gtest/gtest-all.cpp.o
	$(call print_build_cpp,$(ROOT)/$(BUILD_DIR)/gtest/gtest-main.cpp.o)
	$(CXX) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest_main.cc -o $(ROOT)/$(BUILD_DIR)/gtest/gtest-main.cpp.o
	$(call print_link_lib,libgtest.a)
	ar -rcs $(ROOT)/$(BUILD_DIR)/libgtest.a  $(ROOT)/$(BUILD_DIR)/gtest/gtest-all.cpp.o $(ROOT)/$(BUILD_DIR)/gtest/gtest-main.cpp.o

pre-gtest:
	$(call scan_target,gtest)

clean-gtest:
	$(call clean_target,gtest)
	if [ -e "$(ROOT)/$(BUILD_DIR)/libgtest.a" ]; then rm $(ROOT)/$(BUILD_DIR)/libgtest.a; fi
	if [ -e "$(ROOT)/$(BUILD_DIR)/gtest" ]; then rm -r $(ROOT)/$(BUILD_DIR)/gtest; fi
# }}}
# TEST {{{
build-test: build-gtest pre-test $(TEST_EXE)
	$(call complete_target,test)

clean-test: clean-gtest
	$(call clean_target,test)
	if [ -e "$(TEST_EXE)" ]; then rm $(TEST_EXE); fi
	if [ -e "$(ROOT)/$(BUILD_DIR)/$(TEST_DIR)" ]; then rm -r $(ROOT)/$(BUILD_DIR)/$(TEST_DIR); fi

$(TEST_EXE): $(TEST_OBJS)
	$(call print_link_exe,$(TEST_EXE))
	if [ -e "$(LIB)" ]; then $(CXX) $(CXXFLAGS) $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) $(LINK) $(LIB) $(ROOT)/$(BUILD_DIR)/libgtest.a -lpthread $^ -o $@;\
	else $(CXX) $(CXXFLAGS) $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) $(LINK) $(ROOT)/$(BUILD_DIR)/libgtest.a -lpthread $^ -o $@; fi

pre-test:
	$(call scan_target,test)

$(ROOT)/$(BUILD_DIR)/$(TEST_DIR)/%.c.o: $(ROOT)/$(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(call print_build_c,$@)
	str=$$(realpath --relative-to="$(ROOT)" "$^");\
	$(CC) $(CFLAGS) -MMD -c $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) -I$(GTEST_DIR)/include $$str -o $@

$(ROOT)/$(BUILD_DIR)/$(TEST_DIR)/%.cpp.o: $(ROOT)/$(TEST_DIR)/%.cpp
	mkdir -p $(@D)
	$(call print_build_cpp,$@)
	str=$$(realpath --relative-to="$(ROOT)" "$^");\
	$(CXX) $(CXXFLAGS) -MMD -c $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) -I$(GTEST_DIR)/include $$str -o $@
# }}}
$(ROOT)/$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(@D)
	$(call print_build_c,$@)
	str=$$(realpath --relative-to="$(ROOT)" "$^");\
	$(CC) $(CFLAGS) -MMD -c $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) $$stt -o $@

$(ROOT)/$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(@D)
	$(call print_build_cpp,$@)
	str=$$(realpath --relative-to="$(ROOT)" "$^");\
	$(CXX) $(CXXFLAGS) -MMD -c $(INCLUDE) -I$(ROOT)/$(INCLUDE_DIR) $$str -o $@
