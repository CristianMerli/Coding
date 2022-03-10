######################################
###        LECTURE MAKEFILE        ###
######################################
###                                ###
###   Author: Cristian Merli       ###
###   Code title: L-makefile  	 	 ###
###   Code version: 3.0            ###
###   Creation date: 03/02/2022    ###
###   Last mod. date: 09/02/2022   ###
###                                ###
######################################


################################
#          (1) FILES:          #
################################

# (1.1) File-names
MAIN_NM  			=		lecture
LIB_UI_NM			=		lib_ui
LIB_LECT_NM		=		lib_lecture

# (1.2) File-folders
MAIN_FLD			=		main/
LIB_UI_FLD		=		lib/ui/
LIB_LECT_FLD	=		lib/lecture/

# (1.3) File-extensions
CPP_EXT				=		.cpp
HEADER_EXT		=		.h
OBJ_EXT				=		.o
LIB_EXT				=		.so
EXE_EXT				=		.exe

# (1.4) Source-files
MAIN_IN       =   $(MAIN_FLD)$(MAIN_NM)$(CPP_EXT)
LIB_UI_IN 		=		$(LIB_UI_FLD)$(LIB_UI_NM)$(CPP_EXT)
LIB_LECT_IN		=		$(LIB_LECT_FLD)$(LIB_LECT_NM)$(CPP_EXT)

# (1.5) Header-files
LIB_UI_H 			=		$(LIB_UI_FLD)$(LIB_UI_NM)$(HEADER_EXT)
LIB_LECT_H		=		$(LIB_LECT_FLD)$(LIB_LECT_NM)$(HEADER_EXT)

# (1.6) Output-files
MAIN_OUT      =   $(MAIN_FLD)$(MAIN_NM)$(OBJ_EXT)
LIB_UI_OUT		=		$(LIB_UI_FLD)$(LIB_UI_NM)$(LIB_EXT)
LIB_LECT_OUT	=		$(LIB_LECT_FLD)$(LIB_LECT_NM)$(LIB_EXT)

# (1.7) Extecutable-file
MAIN_EXE			=		$(MAIN_NM)$(EXE_EXT)


################################
#   (2) COMMANDS AND FLAGS:    #
################################

# (2.1) Compiler info
COMP_NAME			=		g++
COMP_LANG			=		c++
COMP_VERS			= 	11

# (2.2) Compile & run commands vars
COMPILE_LIB   =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o
COMPILE_MAIN  =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o
LINK          =   $(COMP_NAME) -std=$(COMP_LANG)$(COMP_VERS) -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o
RUN           =   ./


################################
#        (3) MAKE CMDS:        #
################################

# (3.1) Compile and link all files
all: $(MAIN_IN) $(LIB_UI_IN) $(LIB_LECT_IN) $(LIB_UI_H) $(LIB_LECT_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_LECT_OUT) $(LIB_LECT_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_LECT_OUT)

# (3.2) Run software (main)
run: $(MAIN_EXE)
	$(RUN)$<

# (3.3) Compile and link all files + run software (main) --> [3.1 + 3.2]
all_run: $(MAIN_IN) $(LIB_UI_IN) $(LIB_LECT_IN) $(LIB_UI_H) $(LIB_LECT_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_LECT_OUT) $(LIB_LECT_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_LECT_OUT)
	$(RUN)$(MAIN_EXE)

# (3.4) Commands to compile and link step-by-step
compile_lib_ui: $(LIB_UI_IN) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $<
compile_lib_lecture: $(LIB_LECT_IN) $(LIB_LECT_H)
	$(COMPILE_LIB) $(LIB_LECT_OUT) $<
compile_main: $(MAIN_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
link_all: $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_LECT_OUT)
	$(LINK) $(MAIN_EXE) $^

# (3.5) Clear
clr:
	rm $(MAIN_EXE) $(MAIN_OUT) $(LIB_UI_OUT) $(LIB_LECT_OUT)
