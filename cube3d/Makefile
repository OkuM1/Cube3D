#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chris <chris@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 14:51:22 by mokutucu          #+#    #+#              #
#    Updated: 2024/11/16 14:07:42 by chris            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME    = cube3D

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
SRCS    = src/main.c src/map_checker/check_input.c
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# External libraries
LIBFT   = $(LIBDIR)/libft.a
MLX     = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

# Targets
all: $(MLX) $(LIBFT) $(NAME)

# Check if MLX_DIR exits, if not download from MLX_REPO
check_directory:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Directory does not exist, downloading file..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Library dependencies
$(LIBFT):
	make -C $(LIBDIR)

$(MLX): check_directory
#	git -C $(MLX_DIR) pull || git clone $(MLX_REPO) $(MLX_DIR)
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
