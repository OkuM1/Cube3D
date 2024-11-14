/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:20:48 by mokutucu          #+#    #+#             */
/*   Updated: 2024/11/14 18:11:08 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


#include "../libs/libft/libft.h"
#include "../libs/minilibx-linux/mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_img
{
    void *mlx;
    void *mlx_win;
    void *img;
    char *img_address;
    int     bpp;
    int     line_length;
    int     endian;
} t_img;

typedef struct s_player
{
    int player_id;
    
} t_player;

typedef struct s_game 
{
    t_img img;
    t_player player;
} t_game;

#endif