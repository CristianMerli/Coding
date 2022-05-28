######################################
###       HOMEWORK1 MAKEFILE       ###
######################################
###                                ###
###   Author: Cristian Merli       ###
###   Code title: HW-makefile      ###
###   Code version: 3.0            ###
###   Creation date: 30/04/2022    ###
###   Last mod. date: 28/05/2022   ###
###                                ###
######################################


################################
#   (1) PATHS AND PARAMETERS:  #
################################

# (1.1) Software paths
SRCPATH           =   src
MAINPATH          =   $(SRCPATH)/main
LIBPATH           =   $(SRCPATH)/lib

# (1.2) Data paths
DATAPATH          =   data
DATAINPATH        =   $(DATAPATH)/input
DATAOUTPATH       =   $(DATAPATH)/output

# (1.3) Main-parameters [separate parameters with spaces]
PARAMETERS        =   $(DATAINPATH)/matrix.txt $(DATAINPATH)/kernel.txt $(DATAOUTPATH)/maxpool.txt $(DATAOUTPATH)/avgpool.txt $(DATAOUTPATH)/relu.txt $(DATAOUTPATH)/convol.txt


################################
#          (2) FILES:          #
################################

# (2.1) File-names
MAIN_NM           =   homework
LIB_UI_NM         =   lib_ui
LIB_FILES_NM      =   lib_files
LIB_MATRICES_NM   =   lib_matrices
LIB_CNN_NM        =   lib_cnn

# (2.2) File-folders
MAIN_FLD          =   $(MAINPATH)/
LIB_UI_FLD        =   $(LIBPATH)/ui/
LIB_FILES_FLD     =   $(LIBPATH)/files/
LIB_MATRICES_FLD  =   $(LIBPATH)/matrices/
LIB_CNN_FLD       =   $(LIBPATH)/cnn/

# (2.3) File-extensions
CPP_EXT           =   .cpp
HEADER_EXT        =   .h
OBJ_EXT           =   .o
LIB_EXT           =   .o
EXE_EXT           =   .exe

# (2.4) Source-files
MAIN_IN           =   $(MAIN_FLD)$(MAIN_NM)$(CPP_EXT)
LIB_UI_IN         =   $(LIB_UI_FLD)$(LIB_UI_NM)$(CPP_EXT)
LIB_FILES_IN      =   $(LIB_FILES_FLD)$(LIB_FILES_NM)$(CPP_EXT)
LIB_MATRICES_IN   =   $(LIB_MATRICES_FLD)$(LIB_MATRICES_NM)$(CPP_EXT)
LIB_CNN_IN        =   $(LIB_CNN_FLD)$(LIB_CNN_NM)$(CPP_EXT)

# (2.5) Header-files
LIB_UI_H          =   $(LIB_UI_FLD)$(LIB_UI_NM)$(HEADER_EXT)
LIB_FILES_H       =   $(LIB_FILES_FLD)$(LIB_FILES_NM)$(HEADER_EXT)
LIB_MATRICES_H    =   $(LIB_MATRICES_FLD)$(LIB_MATRICES_NM)$(HEADER_EXT)
LIB_CNN_H         =   $(LIB_CNN_FLD)$(LIB_CNN_NM)$(HEADER_EXT)

# (2.6) Output-files
MAIN_OUT          =   $(MAIN_FLD)$(MAIN_NM)$(OBJ_EXT)
LIB_UI_OUT        =   $(LIB_UI_FLD)$(LIB_UI_NM)$(LIB_EXT)
LIB_FILES_OUT     =   $(LIB_FILES_FLD)$(LIB_FILES_NM)$(LIB_EXT)
LIB_MATRICES_OUT  =   $(LIB_MATRICES_FLD)$(LIB_MATRICES_NM)$(LIB_EXT)
LIB_CNN_OUT       =   $(LIB_CNN_FLD)$(LIB_CNN_NM)$(LIB_EXT)

# (2.7) Extecutable-file
MAIN_EXE          =   $(MAIN_NM)$(EXE_EXT)


################################
#   (3) COMMANDS AND FLAGS:    #
################################

# (3.1) Compiler info
COMP_NAME       =   g++
COMP_LANG       =   c++
COMP_VERS       =   11

# (3.2) Compile & run commands vars
COMPILE_LIB     =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o
COMPILE_MAIN    =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o
LINK            =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o
RUN             =	  ./


################################
#        (4) MAKE CMDS:        #
################################

# (4.1) Compile and link all files
all: $(MAIN_IN) $(LIB_UI_IN) $(LIB_CNN_IN) $(LIB_UI_H) $(LIB_CNN_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_FILES_OUT) $(LIB_FILES_IN)
	$(COMPILE_LIB) $(LIB_MATRICES_OUT) $(LIB_MATRICES_IN)
	$(COMPILE_LIB) $(LIB_CNN_OUT) $(LIB_CNN_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_MATRICES_OUT) $(LIB_CNN_OUT)

# (4.2) Run software (main)
run: $(MAIN_EXE)
	$(RUN)$< $(PARAMETERS)

# (4.3) Compile and link all files + run software (main) --> [4.1 + 4.2]
all_run: $(MAIN_IN) $(LIB_UI_IN) $(LIB_CNN_IN) $(LIB_UI_H) $(LIB_CNN_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_FILES_OUT) $(LIB_FILES_IN)
	$(COMPILE_LIB) $(LIB_MATRICES_OUT) $(LIB_MATRICES_IN)
	$(COMPILE_LIB) $(LIB_CNN_OUT) $(LIB_CNN_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_MATRICES_OUT) $(LIB_CNN_OUT)
	$(RUN)$(MAIN_EXE) $(PARAMETERS)

# (4.4) Commands to compile and link step-by-step
compile_lib_ui: $(LIB_UI_IN) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $<
compile_lib_files: $(LIB_FILES_IN) $(LIB_FILES_H)
	$(COMPILE_LIB) $(LIB_FILES_OUT) $<
compile_lib_matrices: $(LIB_MATRICES_IN) $(LIB_MATRICES_H)
	$(COMPILE_LIB) $(LIB_MATRICES_OUT) $<
compile_lib_cnn: $(LIB_CNN_IN) $(LIB_CNN_H)
	$(COMPILE_LIB) $(LIB_CNN_OUT) $<
compile_main: $(MAIN_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
link_all: $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_MATRICES_OUT) $(LIB_CNN_OUT)
	$(LINK) $(MAIN_EXE) $^

# (4.5) Clear
clr: $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_MATRICES_OUT) $(LIB_CNN_OUT)
	rm $^
