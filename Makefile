NAME		=	miniRT

MAKEFLAGS	+=	--no-print-directory

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -lm
RM			=	rm -rf

# Libft
LIBFT		=	./libs/libft/
LIBFT_LIB	=	$(LIBFT)libft.a
LIBS 		=	-lreadline -lncurses -ltermcap

# MLX
MLX_PATH	=	./libs/MLX42
MLX_BUILD	=	$(MLX_PATH)/build
MLX_NAME	=	$(MLX_BUILD)/libmlx42.a
MLX_INCLUDE	=	$(MLX_PATH)/include/MLX42
MLX_FLAG	=	-L $(MLX_BUILD) -l mlx42 -l glfw -l dl -l m -pthread

OBJ_DIR		=	obj/

INC_DIR		=	include/
SRC_DIR		=	source/

VPATH		=  $(SRC_DIR) $(addprefix $(SRC_DIR), \
				mlx\
				parse\
				render\
				)

SRC			=	main.c error_handling.c

# Parsing
SRC			+=	parse_file.c read_scene.c parse_objects.c

BUILTINS	=	

# SRCS		=	$(addprefix source/, $(SRC))

OBJS		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

define SIGNATURE
      _                                 _
     | |                               | |
   __| | __ _ _ __ _ __ ___   __ _ _ __| |_ _ 
  / _` |/ _` | '__| '_ ` _ \ / _` | '__| __| |  ╱|、
 | (_| | (_| | |  | | | | | | (_| | |  | |_| | (`O -  7
  \__,_|\__,_|_|  |_| |_| |_|\__,_|_|   \__|_|   |、⁻〵
                                                 じしˍ,)ノ
endef
export SIGNATURE

# Colors
RST			=	\033[0m
RED			=	\033[1;31m
BLUE		=	\033[1;34m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
MAGENTA		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

# Background colors
BG_RST		=	\033[0m
BG_RED		=	\033[41m
BG_GREEN	=	\033[42m
BG_YELLOW	=	\033[43m
BG_BLUE		=	\033[44m
BG_MAGENTA	=	\033[45m
BG_CYAN		=	\033[46m
BG_WHITE	=	\033[47m

all: $(NAME)

$(NAME): $(MLX_NAME) $(LIBFT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAG) -o $(NAME)
	@printf "$(MAGENTA)All $(NAME) source files compiled ✅$(RST)\033[0K\r"
	@echo "\n$(BG_GREEN)$(NAME) compiled!$(BG_RST)"
	@echo "$(MAGENTA)$$SIGNATURE$(RST)"

$(LIBFT_LIB):
	@echo "$(BG_BLUE)Compiling libft...$(RST)"
	@make -C $(LIBFT) -f Makefile
	@echo "$(BG_BLUE)Compiling $(NAME)...$(RST)"

$(MLX_NAME): $(MLX_PATH)
	@echo "$(BG_BLUE)Compiling MLX42...$(RST)"
	cmake $(MLX_PATH) -B $(MLX_BUILD)
	make -C $(MLX_BUILD) -j4
	@echo "$(BG_BLUE)MLX42 compiled!$(RST)"

$(MLX_PATH):
	@echo "$(BG_BLUE)Cloning MLX42...$(RST)"
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_PATH)
	@echo "$(BG_BLUE)MLX42 cloned!$(RST)"

$(OBJ_DIR)%.o: %.c include/miniRT.h | $(OBJ_DIR)
	@printf "$(MAGENTA)Compiling $< ✅$(RST)\033[0K\r"; $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

test:
	gcc test.c -o test

clean:
	@echo "$(BG_BLUE)Cleaning...$(BG_RST)"
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT) clean
	@echo "$(CYAN)libft objs cleaned!$(BG_RST)🧹"
	@echo "$(CYAN)$(NAME) objs cleaned!$(BG_RST)🧹"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT) fclean
	@$(RM) $(MLX_BUILD)
	@echo "$(CYAN)MLX42 fully cleaned!$(BG_RST)🧹"
	@echo "$(CYAN)$(NAME) fully cleaned!$(BG_RST)🧹"
	@echo "$(BG_GREEN)All cleaned!$(BG_RST)"

re: fclean all

norme:
	@echo "$(BG_CYAN)SOURCES$(BG_RST)"
	@for file in $(SRC_DIR); do \
		norminette $$file | grep "OK!" > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$file: OK!$(RST)"; \
		else \
			echo "$(RED)"; \
			norminette $$file; \
			echo "$(RST)"; \
		fi \
	done
	@echo "$(BG_CYAN)HEADERS$(BG_RST)"
	@for header in $(INC_DIR); do \
		norminette $$header | grep "OK!" > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$header: OK!$(RST)"; \
		else \
			echo "$(RED)"; \
			norminette $$header; \
			echo "$(RST)"; \
		fi \
	done

.PHONY: all clean fclean re check
