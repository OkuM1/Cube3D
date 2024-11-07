# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 14:51:22 by mokutucu          #+#    #+#              #
#    Updated: 2024/11/07 15:12:20 by mokutucu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME    = cub3D

OBJDIR  = obj
CC      = cc

CFLAGS  = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

RM      = rm -rf

SRC_DIR = src
SRCS    = 

OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all:    $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
