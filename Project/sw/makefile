######################################
###     GRAPH-PROJECT MAKEFILE     ###
######################################
###                                ###
###   Author: Cristian Merli       ###
###   Code title: Graph makefile   ###
###   Code version: 3.0            ###
###   Creation date: 03/07/2021    ###
###   Last mod. date: 16/07/2021   ###
###                                ###
######################################


################################
#     (1) VARS AND FILES:      #
################################

# (1.1) Compile & run commands vars
COMPILE_LIB   =   gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o
COMPILE_MAIN  =   gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c -o
LINK          =   gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o
RUN           =   ./

# (1.2) Source-files
LIB_GRAPH_IN  =   lib/graph/lib_graph.c
LIB_UI_IN     =   lib/ui/lib_ui.c
LIB_FILES_IN  =   lib/files/lib_files.c
LIB_TIMER_IN  =   lib/timer/lib_timer.c
MAIN_IN       =   main/graph_test.c

# (1.3) Header-files
LIB_GRAPH_H   =   lib/graph/lib_graph.h
LIB_UI_H      =   lib/ui/lib_ui.h
LIB_FILES_H   =   lib/files/lib_files.h
LIB_TIMER_H   =   lib/timer/lib_timer.h

# (1.4) Output-files
MAIN_NAME     =   graph_test
LIB_GRAPH_OUT =   lib/graph/lib_graph.so
LIB_UI_OUT    =   lib/ui/lib_ui.so
LIB_FILES_OUT =   lib/files/lib_files.so
LIB_TIMER_OUT =   lib/timer/lib_timer.so
MAIN_OUT      =   main/graph_test.o

# (1.5) Doxygen documentation
DOX_STP       =   ../doc/doxygen/doxygen_config
DOX_FLD       =   ../doc/doxygen/exports/
DOX_HTML      =   ../doc/doxygen/exports/html/index.html

# (1.6) Abstract pdf file (from LaTeX)
ABSTR_PDF     =   ../doc/abstract/relazione-finale-CRISTIAN-MERLI.pdf


################################
#        (2) MAKE CMDS:        #
################################

# (2.1) Compile and link all files
all: $(MAIN_IN) $(LIB_GRAPH_IN) $(LIB_UI_IN) $(LIB_FILES_IN) $(LIB_TIMER_IN) $(LIB_GRAPH_H) $(LIB_UI_H) $(LIB_FILES_H) $(LIB_TIMER_H)
	$(COMPILE_LIB) $(LIB_GRAPH_OUT) $(LIB_GRAPH_IN)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_FILES_OUT) $(LIB_FILES_IN)
	$(COMPILE_LIB) $(LIB_TIMER_OUT) $(LIB_TIMER_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_TIMER_OUT)

# (2.2) Run test software (main)
run: $(MAIN_NAME)
	$(RUN)$<

# (2.3) Compile and link all files + run test software (main) --> [2.1 + 2.2]
all_run: $(MAIN_IN) $(LIB_GRAPH_IN) $(LIB_UI_IN) $(LIB_FILES_IN) $(LIB_TIMER_IN) $(LIB_GRAPH_H) $(LIB_UI_H) $(LIB_FILES_H) $(LIB_TIMER_H)
	$(COMPILE_LIB) $(LIB_GRAPH_OUT) $(LIB_GRAPH_IN)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_LIB) $(LIB_FILES_OUT) $(LIB_FILES_IN)
	$(COMPILE_LIB) $(LIB_TIMER_OUT) $(LIB_TIMER_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
	$(LINK) $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_TIMER_OUT)
	$(RUN)$(MAIN_NAME)

# (2.4) Commands to compile and link step-by-step
compile_lib_graph: $(LIB_GRAPH_IN) $(LIB_GRAPH_H)
	$(COMPILE_LIB) $(LIB_GRAPH_OUT) $<
compile_lib_ui: $(LIB_UI_IN) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $<
compile_lib_files: $(LIB_FILES_IN) $(LIB_FILES_H)
	$(COMPILE_LIB) $(LIB_FILES_OUT) $<
compile_lib_timer: $(LIB_TIMER_IN) $(LIB_TIMER_H)
	$(COMPILE_LIB) $(LIB_TIMER_OUT) $<
compile_main: $(MAIN_IN)
	$(COMPILE_MAIN) $(MAIN_OUT) $<
link_all: $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_TIMER_OUT)
	$(LINK) $^

# (2.5) Clear
clr:
	rm $(LIB_GRAPH_OUT) $(LIB_UI_OUT) $(LIB_FILES_OUT) $(LIB_TIMER_OUT) $(MAIN_OUT) $(MAIN_NAME)

# (2.6) Export/view/clear doxygen documentation
docs: $(DOX_HTML)
	firefox $(DOX_HTML)
docs_gen: $(DOX_STP)
	doxygen $(DOX_STP)
docs_gen_view: $(DOX_STP)
	doxygen $(DOX_STP)
	firefox $(DOX_HTML)
docs_clr: $(DOX_FLD)
	rm -r $(DOX_FLD)*
docs_clr_gen: $(DOX_FLD)
	rm -r $(DOX_FLD)*
	doxygen $(DOX_STP)

# (2.7) Open abstract pdf file (made with LaTeX)
abstract: $(ABSTR_PDF)
	xdg-open $(ABSTR_PDF)
