##################################
#															   #
#   Author: Cristian Merli       #
#   Code title: Graph makefile   #
#   Code version: 1.0            #
#   Creation date: 03/07/2021    #
#   Last mod. date: 03/07/2021   #
#															   #
##################################

##########################
# GRAPH-PROJECT MAKEFILE #
##########################

# VARS AND FILES:
# Compile & run commands
COMPILE_LIB = gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -fpic -shared -o
COMPILE_MAIN = gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -c
LINK = gcc -std=c99 -O2 -Wall -Werror -Wextra -Wconversion -Wfloat-equal -pedantic-errors -o
RUN = ./
# In-files
LIB_GRAPH_IN = lib/graph/lib_graph.c
LIB_UI_IN = lib/ui/lib_ui.c
MAIN_IN = graph.c
# Header-files
LIB_GRAPH_H = lib/graph/lib_graph.h
LIB_UI_H = lib/ui/lib_ui.h
# Out-files
LIB_GRAPH_OUT = lib/graph/lib_graph.so
LIB_UI_OUT = lib/ui/lib_ui.so
MAIN_OUT = graph.o
MAIN_NAME = graph

# CMDS:
# Compile
all: $(MAIN_IN) $(LIB_GRAPH_IN) $(LIB_UI_IN) $(LIB_GRAPH_H) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_GRAPH_OUT) $(LIB_GRAPH_IN)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_MAIN) $(MAIN_IN)
	$(LINK) $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT)
# Run
run: $(MAIN_NAME)
	$(RUN)$(MAIN_NAME)
# Compile & run
all_run: $(MAIN_IN) $(LIB_GRAPH_IN) $(LIB_UI_IN) $(LIB_GRAPH_H) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_GRAPH_OUT) $(LIB_GRAPH_IN)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
	$(COMPILE_MAIN) $(MAIN_IN)
	$(LINK) $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT)
	$(RUN)$(MAIN_NAME)
# Compile step-by-step
compile_lib_graph: $(LIB_GRAPH_IN) $(LIB_GRAPH_H)
	$(COMPILE_LIB) $(LIB_GRAPH_OUT) $(LIB_GRAPH_IN)
compile_lib_ui: $(LIB_UI_IN) $(LIB_UI_H)
	$(COMPILE_LIB) $(LIB_UI_OUT) $(LIB_UI_IN)
compile_main: $(MAIN_IN)
	$(COMPILE_MAIN) $(MAIN_IN)
link_all: $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT)
	$(LINK) $(MAIN_NAME) $(MAIN_OUT) $(LIB_GRAPH_OUT) $(LIB_UI_OUT)
