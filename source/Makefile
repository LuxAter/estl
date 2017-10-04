SHELL = /bin/bash

DIR = $(SOURCE_DIR)
SUB_NAME = "Source"

LIB_FILES = $(filter-out ./main.cpp, $(shell find -name "*.cpp"))
EXE_FILES = $(shell find -name "main.cpp")

LIB_OBJ = $(LIB_FILES:%.cpp=$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o)
EXE_OBJ = $(EXE_FILES:%.cpp=$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o)

LIB_DEP = $(LIB_OBJ:.o=.d)
EXE_DEP = $(EXE_OBJ:.o=.d)

LIB = $(BASE_PATH)/$(BUILD_DIR)/lib$(NAME).a
EXE = $(BASE_PATH)/$(NAME)

define print
printf "%b%s%b\n" "$(2)" "$(1)" "$(NO_COLOR)"
endef

all: $(LIB) $(EXE)

.PHONY : lib exe
lib: $(LIB)

exe: $(EXE)

.PHONY : clean
clean:
	$(call print,Removing $(DIR),$(CLEAN_COLOR))
	if [ -d "$(BASE_PATH)/$(BUILD_DIR)/$(DIR)" ]; then rm $(BASE_PATH)/$(BUILD_DIR)/$(DIR) -r; fi
	$(call print,Removing $(shell basename $(LIB)),$(CLEAN_COLOR))
	if [ -e "$(LIB)" ]; then rm $(LIB); fi
	$(call print,Removing $(shell basename $(EXE)),$(CLEAN_COLOR))
	if [ -e "$(EXE)" ]; then rm $(EXE); fi

.PHONY : install
install:
	if [ "$(TYPE)" == "lib" ] && [ -e "$(LIB)" ]; then\
	  $(call print,Installing $(shell basename $(LIB)),$(INSTALL_COLOR));\
	  sudo mkdir $(INSTALL_PATH)/lib/ -p;\
	  sudo cp $(LIB) $(INSTALL_PATH)/lib/;\
	fi
	if [ "$(TYPE)" == "exe" ] && [ -e "$(EXE)" ]; then\
	  $(call print,Installing $(shell basename $(EXE)),$(INSTALL_COLOR));\
	  sudo mkdir $(INSTALL_PATH)/bin/ -p;\
	  sudo cp $(EXE) $(INSTALL_PATH)/bin/;\
	fi

.PHONY : uninstall
uninstall:
	if [ "$(TYPE)" == "lib" ] && [ -e "$(INSTALL_PATH)/lib/$(shell basename $(LIB))" ]; then\
	  $(call print,Uninstalling $(shell basename $(LIB)),$(INSTALL_COLOR));\
	  sudo rm $(INSTALL_PATH)/lib/$(shell basename $(LIB));\
	fi
	if [ "$(TYPE)" == "exe" ] && [ -e "$(INSTALL_PATH)/bin/$(shell basename $(EXE))" ]; then\
	  $(call print,Uninstalling $(shell basename $(EXE)),$(INSTALL_COLOR));\
	  sudo rm $(INSTALL_PATH)/bin/$(shell basename $(EXE));\
	fi


-include $(EXE_OBJ:.o=.d)
-include $(LIB_OBJ:.o=.d)

$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(call print,Building $@,$(COMPILE_COLOR))
	$(COMPILER) $(COMMON_INCLUDE) $(CXXFLAGS) $(GCOV_FLAG) $< -o $@

$(LIB): lib_start $(LIB_OBJ)
	$(call print,Linking $(shell basename $(LIB)),$(LINK_COLOR))
	if [[ ! -z "$(LIB_OBJ)" ]]; then ar rcs $(LIB) $(LIB_OBJ); fi

.PHONY : lib_start
lib_start:
	$(call print,$(SUB_NAME) Library,$(TARGET_COLOR))

$(EXE): exe_start $(LIB) $(EXE_OBJ)
	$(call print,Linking $(shell basename $(EXE)),$(LINK_COLOR))
	if [ -e "$(LIB)" ]; then $(COMPILER) $(EXE_OBJ) $(LIB) $(LINK) $(GCOV_LINK) -o $(EXE); fi
	if [ ! -e "$(LIB)" ]; then $(COMPILER) $(EXE_OBJ) $(LINK) $(GCOV_LINK) -o $(EXE); fi

.PHONY : exe_start
exe_start:
	$(call print,$(SUB_NAME) Executable,$(TARGET_COLOR))
