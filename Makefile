# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/06 21:07:58 by jaeskim           #+#    #+#              #
#    Updated: 2021/02/08 18:30:15 by jaeskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS := -o3
# CFLAGS := -g3 -fsanitize=address

# libft
LIBFT = libft.a
LIBFT_DIR = lib/libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
LIBFT_INC_DIR = $(LIBFT_DIR)/include
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft
CFLAGS += -I $(LIBFT_INC_DIR)

ifeq ($(DEBUG),true)
	CDEBUG = -g
endif

# minilibx
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_SUBMODULE = git submodule update --init
	MLX = libmlx.a
	MLX_DIR = lib/minilibx-linux
	MLX_FLAGS = -L./$(MLX_DIR) -lmlx -lXext -lX11 -lm
	MLX_NOTIC = @printf "✅ $(FG_TEXT_PRIMARY)If you having trouble building minilibx library, \
	try installing the package below.\n\
	$(FG_TEXT)$(CL_BOLD)gcc make xorg libxext-dev libbsd-dev$(NO_COLOR)\n"
endif
ifeq ($(UNAME_S),Darwin)
	MLX = libmlx.dylib
	MLX_DIR = lib/minilibx_mms_20200219
	MLX_FLAGS = -L./$(MLX_DIR) -lmlx
	MLX_CP = cp $(MLX_FILE) $(MLX)
	MLX_RM = rm -f $(MLX)
endif
MLX_FILE = $(MLX_DIR)/$(MLX)
MLX_INC_DIR = $(MLX_DIR)
CFLAGS += -I $(MLX_INC_DIR)

RM = rm
RMFLAGS = -f

INC_DIR = include
CFLAGS += -I $(INC_DIR)
SRC_DIR = src
OBJ_DIR = obj

HEADERS = $(wildcard $(INC_DIR)/*.h)

MINILIBX_TOOL_DIR = $(SRC_DIR)/minilibx_tool
MINILIBX_TOOL_SRCS = $(wildcard $(MINILIBX_TOOL_DIR)/*.c)

INIT_DIR = $(SRC_DIR)/init
INIT_SRCS = $(wildcard $(INIT_DIR)/*.c)

SRCS = \
	$(wildcard $(SRC_DIR)/*.c) \
	$(MINILIBX_TOOL_SRCS) \
	$(INIT_SRCS)

vpath %.c \
	$(SRC_DIR) \
	$(MINILIBX_TOOL_DIR) \
	$(INIT_DIR)

ifeq ($(UNAME_S),Linux)
endif
ifeq ($(UNAME_S),Darwin)
	SRCS += $(wildcard $(SRC_DIR)/dummy_mac/*.c)
	vpath %.c $(SRC_DIR)/dummy_mac
endif

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

# Color
CL_BOLD	 = \e[1m
CL_DIM	= \e[2m
CL_UDLINE = \e[4m

NO_COLOR = \e[0m

BG_TEXT = \e[48;2;45;55;72m
BG_BLACK = \e[48;2;30;31;33m

FG_WHITE = $(NO_COLOR)\e[0;37m
FG_TEXT = $(NO_COLOR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOR)$(CL_BOLD)\e[38;2;255;121;198m

LF = \e[1K\r$(NO_COLOR)
CRLF= \n$(LF)

all : $(NAME)

clean :
	@$(RM) $(RMFLAGS) $(OBJS) $(OBJS_BONUS)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)'s Object files...\n"

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n"

lib_clean : $(LIBFT)_fclean $(MLX)_clean

re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	@$(CC) $(CDEBUG) $(CFLAGS) $(CINCLUDES) -c $< -o $@
	@printf "$(LF)🚧 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

$(NAME) : cub3d.c $(MLX_FILE) $(LIBFT_FILE) $(HEADERS) $(OBJS)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$(NAME)'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)cub3D$(FG_TEXT)!\n"
	@$(CC) $(CDEBUG) $(CFLAGS) $(CINCLUDES) $(OBJS) -o $(NAME) $(LIBFT_FLAGS) $(MLX_FLAGS)
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"

test : $(NAME)
	@./cub3D

# Libft
$(LIBFT) : $(LIBFT_FILE)

$(LIBFT_FILE) :
	@make --no-print-directory -C $(LIBFT_DIR)

$(LIBFT)_clean :
	@make --no-print-directory -C $(LIBFT_DIR) clean

$(LIBFT)_fclean :
	@make --no-print-directory -C $(LIBFT_DIR) fclean

# minilibx
$(MLX) : $(MLX_FILE)

$(MLX_FILE) :
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)minilibx$(FG_TEXT)!\n"
	$(MLX_SUBMODULE)
	@$(MLX_NOTIC)
	@make --no-print-directory -C $(MLX_DIR)
	@printf "$(CRLF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)minilibx $(FG_TEXT)!\n"
	@$(MLX_CP)

$(MLX)_clean :
	@make --no-print-directory -C $(MLX_DIR) clean
	@$(MLX_RM)

.PHONY: all clean fclean re test\
	$(LIBFT) $(LIBFT)_clean $(LIBFT)_fclean \
	$(MLX) $(MLX)_clean lib_clean
