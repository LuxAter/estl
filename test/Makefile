SHELL = /bin/bash

DIR = $(TEST_DIR)
SUB_NAME = "Test"

SOURCE_LIB = $(BASE_PATH)/$(BUILD_DIR)/lib$(NAME).a

GTEST_INCLUDE = -I$(BASE_PATH)/$(EXTERNAL_DIR)/googletest/googletest/include
GTEST_LIB = $(BASE_PATH)/$(BUILD_DIR)/libgtest.a $(BASE_PATH)/$(BUILD_DIR)/libgtest_main.a -lpthread

EXE_FILES = $(shell find -name "*.cpp")

EXE_OBJ = $(EXE_FILES:%.cpp=$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o)

EXE_DEP = $(EXE_OBJ:.o=.d)

EXE = $(BASE_PATH)/unit-test

define print
printf "%b%s%b\n" "$(2)" "$(1)" "$(NO_COLOR)"
endef

all: $(EXE)

.PHONY : exe
exe: $(EXE)

.PHONY : clean
clean:
	$(call print,Removing $(DIR),$(CLEAN_COLOR))
	if [ -d "$(BASE_PATH)/$(BUILD_DIR)/$(DIR)" ]; then rm $(BASE_PATH)/$(BUILD_DIR)/$(DIR) -r; fi
	$(call print,Removing $(shell basename $(EXE)),$(CLEAN_COLOR))
	if [ -e "$(EXE)" ]; then rm $(EXE); fi


-include $(EXE_OBJ:.o=.d)

$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(call print,Building $@,$(COMPILE_COLOR))
	$(COMPILER) $(COMMON_INCLUDE) $(GTEST_INCLUDE) $(CXXFLAGS) $(GCOV_FLAGS) $< -o $@

$(EXE): exe_start $(LIB) $(EXE_OBJ)
	$(call print,Linking $(shell basename $(EXE)),$(LINK_COLOR))
	if [ -e "$(SOURCE_LIB)" ]; then $(COMPILER) $(EXE_OBJ) $(GTEST_LIB) $(SOURCE_LIB) $(LINK) $(GCOV_LINK) -o $(EXE); fi
	if [ ! -e "$(SOURCE_LIB)" ]; then $(COMPILER) $(EXE_OBJ) $(GTEST_LIB) $(LINK) $(GCOV_LINK) -o $(EXE); fi

.PHONY : exe_start
exe_start:
	$(call print,$(SUB_NAME) Executable,$(TARGET_COLOR))
