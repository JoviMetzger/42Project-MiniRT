# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smclacke <smclacke@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/03/07 19:30:43 by smclacke      #+#    #+#                  #
#    Updated: 2024/03/15 21:11:04 by smclacke      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Executable
NAME 			= miniRT
INPUT_FILE		= ./images_rt/test1.rt

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra
CFLAGS			+= -Werror
CFLAGS			+= -g -fsanitize=address

# Libraries
LIBFT_PATH		= ./libraries/libft
LIBFT 			= $(LIBFT_PATH)/libft.a

MLX42_HEADER	= -I include -lglfw -I $(MLX42_PATH)/include/MLX42/
MLX42_PATH		= ./libraries/mlx42
MLX42			= $(MLX42_PATH)/build/libmlx42.a

# Sources files
SRC_HEADER		= ./header

SRCS			= main.c											\
					movement.c 										\
					open_window.c									\
					colour.c										\
					render.c										\
					ray.c											\
					parser/check_elements/check_caps.c				\
					parser/check_elements/check_elements.c			\
					parser/check_elements/check_utils.c				\
					parser/validate/validate.c						\
					parser/validate/validate_utils.c				\
					parser/convert/convert.c						\
					parser/convert/ft_atof.c						\
					parser/convert/sort_caps.c						\
					parser/convert/sort_other.c						\
					parser/convert/valid_nums.c						\
					parser/convert/valid_nums_2.c					\
					parser/convert/valid_caps.c						\
					parser/convert/valid_other.c					\
					parser/convert/add_rgb.c						\
					parser/convert/add_coord.c						\
					parser/convert/convert_utils.c					\
					parser/parse_input.c							\
					parser/parser_free.c							\
					parser/parser_error.c							\
					parser/parser_utils.c							\
					parser/parser_utils_2.c							\

SRC_DIR			= src
SRC				= ($(addprefix $(SRC_DIR)/, $(SRCS)))

# Objects files
OBJ_PATH		= obj
OBJ				= $(addprefix $(OBJ_PATH)/, $(SRCS:%.c=%.o))

# Colours
PINK 			= \033[35m
BLUE			= \033[34;1m
GREEN			= \033[32;1m
CORAL			= \033[38;2;255;127;80m
BOLD			= \033[1m
ITALIC			= \033[3m
UNDER 			= \033[4m
RESET			= \033[0m

# Targets
all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX42) $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLX42_HEADER) -lm -I $(SRC_HEADER) -o $(NAME)
		@echo "$(CORAL) $(UNDER) $(BOLD) $(ITALIC)   ✨Compilation Done✨      $(RESET)"

$(LIBFT):
		@$(MAKE) -C $(LIBFT_PATH)
		@echo "$(BLUE)$(BOLD) --- Compiling Libft Done --- $(RESET)"

$(MLX42):
		@cd	$(MLX42_PATH) && cmake -B build && cmake --build build -j4
		@echo "$(BLUE)$(BOLD) --- Compiling Minilibx Done --- $(RESET)"

$(OBJ_PATH)/%.o: $(SRC_DIR)/%.c $(SRC_HEADER)
		@mkdir -p $(OBJ_PATH)
		@mkdir -p $(OBJ_PATH)/parser
		@mkdir -p $(OBJ_PATH)/parser/check_elements
		@mkdir -p $(OBJ_PATH)/parser/validate
		@mkdir -p $(OBJ_PATH)/parser/convert
		@$(CC) $(CFLAGS) -c -o $@ $<


# Executest the program
open: $(NAME)
		@echo "$(PINK)$(BOLD) Opening Window... $(RESET)"
		@./$(NAME) $(INPUT_FILE)
		@echo "$(PINK)$(BOLD) Window Closed $(RESET)"

# Clean
clean:
		@$(MAKE) clean -C $(LIBFT_PATH)
		@rm -rf $(MLX42_PATH)/build
		@rm -rf $(OBJ_PATH)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@$(MAKE) fclean -C $(LIBFT_PATH)
		@rm -rf $(OBJ_DIR)
		@rm -rf $(NAME)
		@echo "$(GREEN) $(ITALIC)   ✅ Cleaned executer ✅$(RESET)"

re:	fclean all

.PHONY:	all clean fclean re open
