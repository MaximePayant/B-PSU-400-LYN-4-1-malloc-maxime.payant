##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

## VARIABLES
## --------------------------------------------->
EXEC :=	libmy_malloc.so
FLAG :=	-shared -fPIC -g3 -W -Wall -Wextra -pedantic
CC :=	gcc
EXT :=	c
## --------------------------------------------->

## SOURCES VARIABLES
## --------------------------------------------->
SRC_FOLDER :=	. \
				utils/
IGNORE_SRC := 	.
SRC :=	$(filter-out $(IGNORE_SRC), $(sort $(shell find $(SRC_FOLDER) -ignore_readdir_race -maxdepth 1 -name '*.$(EXT)')))
## --------------------------------------------->

## INCLUDE VARIABLES
## --------------------------------------------->
INC_FOLDER =	.
IGNORE_INC := 	.
INC := $(filter-out $(IGNORE_INC), $(addprefix -I, $(INC_FOLDER)))
## --------------------------------------------->

## LIBRARY VARIABLES
## --------------------------------------------->
LFOLDER :=
LIB_FOLDER := 	#-L $(LFOLDER)
LIB_NAME :=
LIB_EXT :=
## --------------------------------------------->

## OBJECT VARIABLES
## --------------------------------------------->
OBJ_PATH :=	obj/
OBJ_FOLDER := $(addprefix $(OBJ_PATH), $(SRC_FOLDER))
OBJ :=	$(addprefix $(OBJ_PATH), $(SRC:.$(EXT)=.o))
## --------------------------------------------->

## DON'T TOUCH
## --------------------------------------------->
SYSFILES :=	.minfo .minfo/process .minfo/builded .minfo/fails .minfo/errors
N = $(shell ls $(SRC_FOLDER) -I $(notdir $(IGNORE_SRC)) 2> .minfo/tmp | grep -e "\.$(EXT)" -c)
SHELL := /bin/bash
MAKEFLAGS += --no-print-directory --silent --silence
REDIRECT := 2>> .minfo/errors_list
## --------------------------------------------->

## COLOR AND SPEACH
## --------------------------------------------->
WHITE =		"\e[0;1m"
GREEN =		"\e[92;1m"
RED =		"\e[91;1m"
GRAY =		"\e[90;1m"
MAGENTA =	"\e[95;1m"
YELLOW =	"\e[93;1m"
BYELLOW =	"\e[103m"
CYAN =		"\e[36;1m"
BCYAN =		"\e[46m"

RESET = echo -ne "\e[0;49m"
SLINE = "\n ╔══════════════════════════════\e[0;49m"
COMPILE_S =	echo -e "\e[0;49m" ; echo -ne $(BCYAN)   $(GRAY) "     Compiling sources ...     " ; echo -e "\e[0;49m"$(CYAN)$(SLINE)
COMPILE_O =	echo -e "\e[0;49m" ; echo -ne $(BYELLOW) $(GRAY) "     Building objects ...      " ; echo -e "\e[0;49m"$(YELLOW)$(SLINE)
## --------------------------------------------->

.PHONY: re clean fclean introduce compile_obj

## RULES
## --------------------------------------------->
all: introduce $(EXEC)
	if [ $(shell cat .minfo/builded) == $(N) ] \
	|| [ $(shell cat .minfo/errors) == 0 ] \
	&& [ $(shell cat .minfo/fails) == 0 ]; \
		then \
			echo -e $(MAGENTA)"\nIt seems like you finally succeed to code decently"; \
		else \
			echo -e $(MAGENTA)"\n(Renomme le nom du binaire pour voir?)Aannd you failed, try this out : http://cforbeginners.com/"; \
	fi
	rm -f .minfo/builded
	rm -f .minfo/errors
	rm -f .minfo/fails
	rm -f .minfo/process
	rm -f .minfo/tmp
	$(RESET)

introduce: $(SYSFILES) $(OBJ_FOLDER)
	$(COMPILE_S)

$(EXEC): compile_obj
	$(RESET)
	$(COMPILE_O)
	if [ $(shell cat .minfo/errors) == 0 ]; \
		then \
			($(RESET) ; \
			$(CC) -o $@ $(OBJ) $(LIB_FOLDER) $(LIB_NAME) $(LIB_EXT) $(INC) $(FLAG) \
				&& (echo -e $(YELLOW)" ╚═> " $(GREEN) "Everything Builded") \
				|| (echo -e $(YELLOW)" ╚═> " $(RED) "Coudn't Build" ; $(MAKE) increment_fails)); \
		else \
			echo -e $(YELLOW)" ╚═> " $(RED) "Coudn't Build"; \
	fi
	$(RESET)

compile_obj: $(OBJ)
	$(RESET)
	if [ $(shell cat .minfo/errors) == 0 ]; \
		then \
			echo -e $(CYAN)" ╚═> " $(GREEN) "Everything Compiled"; \
		else \
			echo -e $(CYAN)" ╚═> " $(RED) "Coudn't Compile"; \
	fi
	$(RESET)
	echo -e $(MAGENTA)"\nWarning list :"
	$(RESET)
	cat .minfo/errors_list
	$(RESET)

$(OBJ): $(OBJ_PATH)%.o: %.$(EXT)
	$(RESET)
	$(CC) -o $@ -c $< $(INC) $(FLAG) $(REDIRECT) \
		&& (echo -e $(CYAN) \
			╠[$(WHITE)$(shell cat .minfo/process) $(CYAN)/ $(WHITE)$(N)$(CYAN)] \
			$(WHITE)$< "\t" $(GREEN)Builded ; $(MAKE) increment_builded) \
		|| (echo -e $(CYAN) \
			╠[$(WHITE)$(shell cat .minfo/process) $(CYAN)/ $(WHITE)$(N)$(CYAN)] \
			$(WHITE)$< "\t" $(RED)Faild ; $(MAKE) increment_errors)
	$(MAKE) increment_process
	$(RESET)

clean:
	rm -rf $(OBJ_PATH)
	rm -f *.hi

fclean: clean
	rm -f $(EXEC)
	rm -rf .minfo

re: fclean all
## --------------------------------------------->

# LIBRARY RULES
#------------------------------------------>
lib:
		make -C $(LFOLDER)

libre:
		make -C $(LFOLDER) re

libclean:
		make -C $(LFOLDER) clean

libfclean:
		make -C $(LFOLDER) fclean
#------------------------------------------>

## SYSTEM RULES
## --------------------------------------------->
$(SYSFILES):
	mkdir -p .minfo
	echo 1 > .minfo/process
	echo 0 > .minfo/builded
	echo 0 > .minfo/errors
	echo 0 > .minfo/fails
	echo "" > .minfo/errors_list

$(OBJ_FOLDER):
	mkdir -p $@

increment_builded: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/builded"` + 1)) > .minfo/builded)

increment_fails: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/fails"` + 1)) > .minfo/fails)

increment_errors: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/errors"` + 1)) > .minfo/errors)

increment_process: $(SYSFILES)
	$(shell echo $$((`cat ".minfo/process"` + 1)) > .minfo/process)
## --------------------------------------------->