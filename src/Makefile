
NAME	:= philo

SRC_DIR	:= src/
SRCS	:= activities.c add_forks.c create_philos.c free.c \
		   get_set.c main.c output.c setup.c start_end.c utils.c

OBJ_DIR	:= .build/
OBJS	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC		:= cc
CFLAGS	:= -g -Wall -Wextra -Werror -Wunused -Wuninitialized -Wunreachable-code
LDFLAGS	:= -fsanitize=thread
RM		:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(D@)
	$(CC) $(CLFAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	@printf "$(REMOVED)" $(OBJ_DIR) $(CUR_DIR)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean flcean re

# ----------------------------------- colors --------------------------------- #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# ----------------------------------- messages ------------------------------- #

CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED	:= $(MAGENTA) $(BOLD) REMOVED %s (%s) $(RESET)\n\n
CREATED	:= $(GREEN) $(BOLD) CREATED %s (%s) $(RESET)\n\n
UPDATED	:= $(GREEN) $(BOLD) CREATED OR UPDATED %s (%s) $(RESET)\n\n
