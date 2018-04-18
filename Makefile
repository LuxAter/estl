SHELL = /bin/bash

export NAME= estl.out
export LINK=
export INCLUDE=
export TYPE= lib

export SOURCE_DIR= source
export TEST_DIR= test
export EXTERNAL_DIR = external
export BUILD_DIR= build
export INCLUDE_DIR= estl
export DOC_DIR= docs

export BASE_PATH=$(shell pwd)

export COMPILER=clang++
export CXXFLAGS= -MMD -std=c++17 -w -c -fPIC

export INSTALL_PATH=/usr/local


# ifdef CI
export GCOV_LINK = --coverage
export GCOV_FLAG = -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline
# else
# export GCOV_LINK =
# export GCOV_FLAG =
# endif

export COMMON_INCLUDE=-I$(BASE_PATH)/$(INCLUDE_DIR) $(INCLUDE)

export SECTION_COLOR=\033[1;97m
export TARGET_COLOR=\033[0;34m
export LINK_COLOR=\033[0;35m
export CLEAN_COLOR=\033[0;33m
export COMPILE_COLOR=\033[0;32m
export INSTALL_COLOR=\033[0;36m
export ERROR_COLOR=\033[1;31m
export NO_COLOR=\033[m

ifndef .VERBOSE
  .SILENT:
endif

define print_section
str="$(1)";\
    line_length=$${#str};\
    printf "%b%s\n" "$(SECTION_COLOR)" "$$str";\
    while [ $$line_length -gt 0 ]; do\
      printf "=";\
      let line_length=line_length-1;\
    done;\
    printf "%b\n" "$(NO_COLOR)"
endef

define print
printf "%b%s%b\n" "$(2)" "$(1)" "$(NO_COLOR)"
endef

define help
printf "%b%*s%b: %s\n" "$(TARGET_COLOR)" 14 "$(1)" "$(NO_COLOR)" "$(2)"
endef

.PHONY : all
all: external source test
# all: source

.PHONY : clean
clean: clean-source clean-test

.PHONY : install
install: source root-access install-source
	if [ $(TYPE) == "lib" ] && ! [ -d "$(INSTALL_PATH)/include/$(NAME)" ]; then \
	  $(call print,Installing include directory,$(INSTALL_COLOR));\
	  sudo mkdir $(INSTALL_PATH)/include/ -p;\
	  sudo cp $(INCLUDE_DIR)/ $(INSTALL_PATH)/include/ -r;\
	fi

.PHONY : uninstall
uninstall: root-access uninstall-source
	if [ $(TYPE) == "lib" ] && [ -d "$(INSTALL_PATH)/include/$(NAME)" ]; then \
	  $(call print,Uninstalling include directory,$(INSTALL_COLOR));\
	  sudo rm $(INSTALL_PATH)/include/$(NAME) -rf;\
	fi

.PHONY : help
help:
	$(call print_section,Makefile Help)
	printf "List of all acceptable make targets\n\n"
	$(call help,all,Builds external, source, and test files and projects)
	$(call help,clean,Clean files created from external, source, and test)
	$(call help,help,Display this help page)
	$(call help,external,Builds external files and projects)
	$(call help,clean-external,Cleans files created from external)
	$(call help,source,Builds source files and projects)
	$(call help,clean-source,Cleans files created from source)
	$(call help,test,Builds test files and projects)
	$(call help,clean-test,Cleans files created from test)

.PHONY : root-access
root-access:
	if [[ $$UID != 0 ]]; then \
	  $(call print,Target requiers root access,$(ERROR_COLOR)); \
	  exit 1; \
	fi

.PHONY : external
external:
	$(call print_section,External Dependencies)
	if [ -d "$(EXTERNAL_DIR)" ]; then cd "$(EXTERNAL_DIR)" && $(MAKE); fi
.PHONY : clean-external
clean-external:
	$(call print_section,External Dependencies)
	if [ -d "$(EXTERNAL_DIR)" ]; then cd "$(EXTERNAL_DIR)" && $(MAKE) clean; fi

.PHONY : source
source:
	$(call print_section,Source Files)
	if [ -d "$(SOURCE_DIR)" ]; then cd "$(SOURCE_DIR)" && $(MAKE); fi
.PHONY : clean-source
clean-source:
	$(call print_section,Source Files)
	if [ -d "$(SOURCE_DIR)" ]; then cd "$(SOURCE_DIR)" && $(MAKE) clean; fi
.PHONY : install-source
install-source:
	$(call print_section,Source Files)
	if [ -d "$(SOURCE_DIR)" ]; then cd "$(SOURCE_DIR)" && $(MAKE) install; fi
.PHONY: uninstall-source
uninstall-source:
	$(call print_section,Source Files)
	if [ -d "$(SOURCE_DIR)" ]; then cd "$(SOURCE_DIR)" && $(MAKE) uninstall; fi

.PHONY : test
test:
	$(call print_section,Unit Tests)
	if [ -d "$(TEST_DIR)" ]; then cd "$(TEST_DIR)" && $(MAKE); fi
.PHONY : clean-test
clean-test:
	$(call print_section,Unit Tests)
	if [ -d "$(TEST_DIR)" ]; then cd "$(TEST_DIR)" && $(MAKE) clean; fi

.PHONY: docs
docs:
	$(call print_section,Documentation)
	$(call print,Running doxygen...,$(COMPILE_COLOR))
	doxygen

.PHONY: clean-docs
clean-docs:
	$(call print_section,Documentation)
	if [ -d "$(DOC_DIR)/html" ]; then rm "$(DOC_DIR)/html" -r; fi
	if [ -d "$(DOC_DIR)/latex" ]; then rm "$(DOC_DIR)/latex" -r; fi
	if [ -d "$(DOC_DIR)/xml" ]; then rm "$(DOC_DIR)/xml" -r; fi
	$(call print,Cleaned Documentation,$(CLEAN_COLOR))

.PHONY: runtest
runtest: test
	./unit-test --gtest_color=yes
