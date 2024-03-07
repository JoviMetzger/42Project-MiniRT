NAME			= account

INCLUDE			= -Iinclude

CC				= c++
CPPFLAGS		= -Wall -Wextra -Werror -std=c++98

HEADERS			= Account.hpp
HEADER_DIR		= include
HEADER			= $(addprefix $(HEADER_DIR)/, $(HEADERS))

SRCS			= Account.cpp		\
				test.cpp			\

SRC_DIR			= src
SRC				= $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR			= obj
OBJ				= $(addprefix $(OBJ_DIR)/, $(SRCS:%.cpp=%.o))


all			: $(NAME)

$(NAME)		: $(OBJ)
	@ echo "${BLACK} $(NAME) compiling...${RESET}"
	@ $(CC) $^ $(CPPFLAGS) $(INCLUDE) -o $(NAME)
	@ echo "${BLACK} $(NAME) made!${RESET}"
	
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp $(HEADER)
	@ mkdir -p $(OBJ_DIR)
	@ $(CC) $(CPPFLAGS) $(iNCLUDE) -c $< -o $@

clean		: 
	@ rm -rf $(OBJ_DIR)

fclean		: clean
	@ rm -f $(NAME)
	@ echo "${YELLOW} $(NAME) fcleaned!${RESET}"

re			: fclean all

.PHONY: all clean flcan re



NAME			= minishell

MAKEFLAGS		= --no-print-directory
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address

LFLAGS			= -L$(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
CC				= cc
INCLUDES		= -Iinclude -Iinclude/libft/include
HEADERS			= shelly.h structs.h prompt.h colour.h
IFLAGS			= -I$(HOME)/.brew/Cellar/readline/8.2.1/include

HEADER_DIR		= include
HEADER			= $(addprefix $(HEADER_DIR)/, $(HEADERS))

## SRC FILES ##

SRCS			= main.c								\
					utils/errors.c						\
					utils/more_space.c					\
					utils/errors2.c						\
					utils/execute_utils.c				\
					utils/parser_errors.c				\
					utils/free_procs.c					\
					utils/signals.c						\
					utils/utils.c						\
					utils/cleanup.c						\
					utils/hd_fd_utils.c					\
					lexer/lexer.c						\
					lexer/lexer_utils.c					\
					lexer/tokens.c						\
					lexer/meta_check.c					\
					parser/parser.c						\
					parser/parser_utils.c				\
					parser/sort_procs.c					\
					parser/get_procs.c					\
					parser/proc_utils.c					\
					expander/expand_utils_2.c			\
					expander/expand.c					\
					expander/expand_utils.c				\
					expander/expand_quotes.c			\
					expander/remove_quotes.c			\
					expander/expand_quote_utils.c		\
					expander/expand_dollar.c			\
					expander/dollars.c					\
					expander/d_quotes.c					\
					expander/s_quotes.c					\
					expander/hd_expand.c				\
					builtin/echo.c						\
					builtin/cd.c 						\
					builtin/pwd.c 						\
					builtin/export.c 					\
					builtin/unset.c 					\
					builtin/env.c 						\
					builtin/builtin_utils_one.c 		\
					builtin/builtin_utils_two.c 		\
					builtin/exit.c						\
					executor/execute.c					\
					executor/make_env.c					\
					executor/list_utils.c 				\
					executor/utils.c					\
					executor/execute_utils_one.c		\
					executor/execute_utils_two.c		\
					executor/heredoc_utils.c			\
					executor/redirect.c					\


SRC_DIR		= src
SRC			= ($(addprefix $(SRC_DIR)/, $(SRCS)))


OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

all				: libft $(NAME)

libft			:
	@ make -C include/libft


$(NAME)			:	$(OBJ)
	@ $(CC) $^ $(CFLAGS) $(LFLAGS) $(IFLAGS) $(INCLUDES) include/libft/libft.a -o $(NAME)
	@ echo "${PURPLE} ---> Made!${RESET}"

norm:
	@ norminette $(SRC_DIR) $(HEADER_DIR)

## OBJECTS

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@ mkdir -p $(OBJ_DIR)
	@ mkdir -p $(OBJ_DIR)/parser
	@ mkdir -p $(OBJ_DIR)/lexer
	@ mkdir -p $(OBJ_DIR)/expander
	@ mkdir -p $(OBJ_DIR)/builtin
	@ mkdir -p $(OBJ_DIR)/executor
	@ mkdir -p $(OBJ_DIR)/utils
	@ $(CC) $(CFLAGS) $(IFLAGS) $(INCLUDES) -c $< -o $@

## COLOURS ##

RESET		:= \033[0m
RED			:= \033[1;91m
GREEN		:= \033[1;92m
YELLOW		:= \033[1;93m
BLUE		:= \033[1;94m
PURPLE		:= \033[1;95m
CYAN		:= \033[1;96m
WHITE		:= \033[1;97m
BLACK		:= \033[1;90m

clean		:
	@make $(MAKEFLAGS) -C include/libft clean
	@rm -rf $(OBJ_DIR)

fclean		:
	@make $(MAKEFLAGS) -C include/libft fclean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@echo "${YELLOW} // Minishell fCleaned!${RESET}"

re			: fclean all

