# The name of your library
NAME = libft.a

# The compiler to use
CC = cc

# The archiver to use
AR = ar

# The flags to use with the archiver
ARFLAGS = -rc

# The flags to use with the compiler
CFLAGS = -Wall -Wextra -Werror

# The command to remove files
RM = rm -f

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

# A list of all .c files wanted
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
	ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
	printf/ft_printf.c printf/ft_printnumbers.c printf/ft_printcharacters.c \
	gnl/get_next_line.c gnl/get_next_line_utils.c

# A list of all .o files that correspond to the .c files
OBJS = $(SRCS:.c=.o)

# The default target. Builds the library
all: $(NAME)

# A rule to build the library from the .o files
$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@printf "$(MAGENTA)All libft source files compiled ✅$(RST)\033[0K\r"
	@echo "\n$(BG_GREEN)libft compiled!$(BG_RST)"

# A 
%.o: %.c
	@printf "$(MAGENTA)Compiling $< ✅$(RST)\033[0K\r"; $(CC) $(CFLAGS) -c $< -o $@ -c

# A rule to remove all the .o files
clean:
	@$(RM) $(OBJS) $(BNS)

# A rule to remove all the .o files and the library
fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)libft fully cleaned!$(BG_RST)🧹"

# A rule to rebuild everthing from scratch
re: fclean all

# A especial rule to tell Makefile that these targets aren't files
.PHONY: all clean fclean re
