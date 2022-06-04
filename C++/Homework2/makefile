######################################
###       HOMEWORK MAKEFILE        ###
######################################
###                                ###
###   Author: Cristian Merli       ###
###   Code title: HW-makefile      ###
###   Code version: 3.0            ###
###   Creation date: 11/05/2022    ###
###   Last mod. date: 03/06/2022   ###
###                                ###
######################################


################################
#          (1) PATHS:          #
################################

# (1.1) Software paths
SRCPATH           =   src
MAINPATH          =   $(SRCPATH)/main
LIBPATH           =   $(SRCPATH)/lib

# (1.2) Data paths [UNUSED]
#DATAPATH         =   data
#DATAINPATH       =   $(DATAPATH)/input
#DATAOUTPATH      =   $(DATAPATH)/output

# (1.3) Documentation paths
DOC_FLD           =   doc
DOC_CODE_FLD      =   $(DOC_FLD)/code
DOC_CODE_EXP_FLD  =   $(DOC_CODE_FLD)/exports
#ABSTR_FLD        =   $(DOC_FLD)/abstract [UNUSED]


################################
#       (2) PARAMETERS:        #
################################

# (2.1) Main command-line-parameters [SEPARATE PARAMETERS WITH SPACES] [UNUSED]
PARAMETERS        =   0


################################
#     (3) SOFTWARE FILES:      #
################################

# (3.1) Software file-names
MAIN_NM           =   homework
LIB_UI_NM         =   lib_ui
LIB_BUILDING_NM   =   lib_building

# (3.2) Software file-folders
MAIN_FLD          =   $(MAINPATH)/
LIB_UI_FLD        =   $(LIBPATH)/ui/
LIB_BUILDING_FLD  =   $(LIBPATH)/building/

# (3.3) Software file-extensions
CPP_EXT           =   .cpp
HEADER_EXT        =   .hpp
OBJ_EXT           =   .o
LIB_EXT           =   .o
EXE_EXT           =   .exe

# (3.4) Software source-files
MAIN_IN           =   $(MAIN_FLD)$(MAIN_NM)$(CPP_EXT)
LIB_UI_IN         =   $(LIB_UI_FLD)$(LIB_UI_NM)$(CPP_EXT)
LIB_BUILDING_IN   =   $(LIB_BUILDING_FLD)$(LIB_BUILDING_NM)$(CPP_EXT)

# (3.5) Software header-files
LIB_UI_H          =   $(LIB_UI_FLD)$(LIB_UI_NM)$(HEADER_EXT)
LIB_BUILDING_H    =   $(LIB_BUILDING_FLD)$(LIB_BUILDING_NM)$(HEADER_EXT)

# (3.6) Software output-files
MAIN_OUT          =   $(MAIN_FLD)$(MAIN_NM)$(OBJ_EXT)
LIB_UI_OUT        =   $(LIB_UI_FLD)$(LIB_UI_NM)$(LIB_EXT)
LIB_BUILDING_OUT  =   $(LIB_BUILDING_FLD)$(LIB_BUILDING_NM)$(LIB_EXT)

# (3.7) Software extecutable-file
MAIN_EXE          =   $(MAIN_NM)$(EXE_EXT)


################################
#   (4) DOCUMENTATION FILES:   #
################################

# (4.1) Doxygen-documentation-files
DOC_CONFIG        =   $(DOC_CODE_FLD)/doxygen_config
DOC_HTML          =   $(DOC_CODE_EXP_FLD)/html/index.html

# (4.2) Abstract-pdf-file (from LaTeX) [UNUSED]
#ABSTR_PDF        =    $(ABSTR_FLD)/relazione-finale-CRISTIAN-MERLI.pdf


################################
#        (5) COMPILER:         #
################################

# (5.1) Compiler info
COMP_NAME       =   g++
COMP_LANG       =   c++
COMP_VERS       =   11

# (5.2) Compile & run commands
COMPILE_LIB     =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o
COMPILE_MAIN    =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o
LINK            =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o
RUN             =	  ./


################################
#      (6) SOFTWARE CMDS:      #
################################

# (6.1) Compile and link all files
all: $(MAIN_IN) $(LIB_UI_IN) $(LIB_BUILDING_IN) $(LIB_UI_H) $(LIB_BUILDING_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_BUILDING_OUT) $(LIB_BUILDING_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_BUILDING_OUT)

# (6.2) Run software (main)
run: $(MAIN_EXE)
	$(RUN)$< $(PARAMETERS)

# (6.3) Compile and link all files + run software (main) --> [6.1 + 6.2]
all_run: $(MAIN_IN) $(LIB_UI_IN) $(LIB_BUILDING_IN) $(LIB_UI_H) $(LIB_BUILDING_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_BUILDING_OUT) $(LIB_BUILDING_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_BUILDING_OUT)
	$(RUN)$(MAIN_EXE) $(PARAMETERS)

# (6.4) Commands to compile and link step-by-step
compile_lib_ui: $(LIB_UI_IN) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $<
compile_lib_building: $(LIB_BUILDING_IN) $(LIB_BUILDING_H)
	$(COMPILE_LIB) $(LIB_BUILDING_OUT) $<
compile_main: $(MAIN_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
link_all: $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_BUILDING_OUT)
	$(LINK) $(MAIN_EXE) $^

# (6.5) Clear
clr: $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_BUILDING_OUT)
	rm $^


###############################
#   (7) DOCUMENTATION CMDS:   #
###############################

# (7.1) Detect Linux/Mac OS to define open command
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	OPEN_CMD += xdg-open
else
	OPEN_CMD += open
endif

# (7.2) Open doxygen-html documentation
doc_open: $(DOC_HTML)
	$(OPEN_CMD) $<

# (7.3) Generate doxygen-html documentation
doc_gen: $(DOC_CONFIG)
	doxygen $<

# (7.4) Clear doxygen-html documentation
doc_clr: $(DOC_CODE_EXP_FLD)
	rm -r $</*

# (7.5) Clear + generate + open doxygen-html documentation --> [7.4 + 7.2 + 7.3]
doc_clr_gen_open: $(DOC_CODE_EXP_FLD) $(DOC_CONFIG)
	rm -r $</*
	doxygen $(DOC_CONFIG)
	$(OPEN_CMD) $(DOC_HTML)

# (7.6) Open abstract pdf file (made with LaTeX) [UNUSED]
#abstract_open: $(ABSTR_PDF)
#	$(OPEN_CMD) $(ABSTR_PDF)
