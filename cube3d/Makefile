# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 14:51:22 by mokutucu          #+#    #+#              #
#    Updated: 2024/11/14 16:27:02 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = cub3D

# Directories
OBJDIR  = obj
SRC_DIR = src
LIBDIR  = libs/libft
MLX_DIR = libs/minilibx-linux

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline -L$(LIBDIR) -lft -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

# Cleanup
RM      = rm -rf

# Source files and objects
SRCS    = src/main.c
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# External libraries
LIBFT   = $(LIBDIR)/libft.a
MLX     = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

# Targets
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Library dependencies
$(LIBFT):
	make -C $(LIBDIR)

$(MLX):
	git -C $(MLX_DIR) pull || git clone $(MLX_REPO) $(MLX_DIR)
	make -C $(MLX_DIR)

# Clean up
clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re
