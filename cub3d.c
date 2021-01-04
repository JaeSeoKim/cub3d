/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:50:30 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/04 21:45:19 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "cub3d.h"

#define WIDTH 1024
#define HEIGHT 512
#define TILE_SIZE 64

const float FOV_ANGLE = 60 * (M_PI / 180);

int		check_key_press(int keycode, t_ll *key);

int mapx = 8, mapy = 8;
int map[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,1,0,0,1,
	1,1,1,1,1,1,1,1,
};

float	normalize_angle(float angle)
{
	angle = fmodf(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int		has_wall_at(t_cub3d *game, float x, float y)
{
	if (x < 0 || y < 0 || x > game->width || y > game->height)
		return (1);
	return (map[(int)floor(y / TILE_SIZE) * mapx + (int)floor(x / TILE_SIZE)] == 1 ? 1 : 0);
}

void	init(t_cub3d *game, int width, int height, char *title)
{
	int			i;
	t_img		*img;

	img = &game->img;
	if (!(game->mlx = mlx_init()))
		exit(1);
	if (!(game->win = mlx_new_window(game->mlx, width, height, title)))
		exit(1);
	game->width = WIDTH;
	game->height = HEIGHT;
	img->ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	img->data = (t_ui *)mlx_get_data_addr(
		game->img.ptr, &img->bpp, &img->size_l, &img->endian);
	img->line = img->size_l / (img->bpp / 8);
	game->player.vec.x = width / 3;
	game->player.vec.y = height / 4;
	game->player.move_speed = 3.0;
	game->player.rotate_speed = 3 * (M_PI / 180);
	game->player.rotate_angle = M_PI / 2;
	game->player.turn_direct = 0;
	game->player.walk_direct = 0;
	i = 0;
	while (i < 6)
		game->key[i++] = 0;
}

int init_img(t_cub3d *game)
{
	int length;
	int i;

	i = 0;
	length = game->img.line * game->height;
	while (i < length)
		game->img.data[i++] = 0x111111;
	return (0);
}

int render_map_2d(t_cub3d *game)
{
	t_vec	vec;
	t_ui	*data;

	data = game->img.data;

	stroke_rgba(255, 255, 255, 255);
	fill_rgba(0, 0, 0, 255);
	for (int i = 0; i < TILE_SIZE; i++)
	{
		if (map[i])
		{
			vec.y = (i / 8) * TILE_SIZE;
			vec.x = (i % 8) * TILE_SIZE;
			rect(&game->img, vec, TILE_SIZE, TILE_SIZE);
		}
	}
	return (0);
}

int		render_player_2d(t_cub3d *game)
{
	t_ui	*data;
	t_vec	target;

	data = game->img.data;

	no_stroke();
	fill_rgba(255, 255, 0, 1);
	mid_point_rect(&game->img, game->player.vec, 10, 10);
	target.x = game->player.vec.x + cos(game->player.rotate_angle) * 20;
	target.y = game->player.vec.y + sin(game->player.rotate_angle) * 20;
	stroke_rgba(0, 255, 0, 1);
	line(&game->img, game->player.vec, target);
	return (0);
}

void	update_player(t_cub3d *game)
{
	t_vec		new_vec;
	float		move_step;
	t_player	*p;
	t_ll		*key;

	p = &game->player;
	key = game->key;
	game->player.turn_direct = check_key_press(KEY_LEFT, key) ? -1 : 0;
	game->player.turn_direct += check_key_press(KEY_RIGHT, key) ? 1 : 0;
	game->player.walk_direct = check_key_press(KEY_UP, key) ? 1 : 0;
	game->player.walk_direct += check_key_press(KEY_DOWN, key) ? -1 : 0;
	game->player.rotate_angle =
		normalize_angle(game->player.rotate_angle + \
						game->player.turn_direct * game->player.rotate_speed);
	move_step = game->player.walk_direct * game->player.move_speed;
	new_vec.x = game->player.vec.x + cos(game->player.rotate_angle) * move_step;
	new_vec.y = game->player.vec.y + sin(game->player.rotate_angle) * move_step;
	if (!has_wall_at(game, new_vec.x, new_vec.y))
	{
		game->player.vec.x = new_vec.x;
		game->player.vec.y = new_vec.y;
	}
}

t_ray	*setup_ray(t_ray *ray, float ray_angle)
{
	ray->angle = normalize_angle(ray_angle);
	ray->vertwallhit.x = 0;
	ray->vertwallhit.y = 0;
	ray->distance = 0;
	ray->down = ray->angle > 0 && ray->angle < M_PI;
	ray->up = !ray->down;
	ray->right = ray->angle < 0.5 * M_PI || ray->angle > 1.5 * M_PI;
	ray->left = !ray->right;
	ray->verthit = 0;
	ray->horzhit = 0;
	ray->vertwallhit.x = 0;
	ray->vertwallhit.y = 0;
	ray->horzwallhit.x = 0;
	ray->horzwallhit.y = 0;

	return (ray);
}

void	cast_ray_vert(t_cub3d *game, t_ray *ray, t_vec p)
{
	t_vec	next;

	ray->intercept.x = floor(p.x / TILE_SIZE) * TILE_SIZE;
	ray->intercept.x += ray->right ? TILE_SIZE : 0;
	ray->intercept.y = p.y + (ray->intercept.x - p.x) * tan(ray->angle);
	ray->step.x = ray->left ? -TILE_SIZE : TILE_SIZE;
	ray->step.y = TILE_SIZE * tan(ray->angle);
	ray->step.y *= ray->up && ray->step.y > 0 ? -1 : 1;
	ray->step.y *= ray->down && ray->step.y < 0 ? -1 : 1;
	next = ray->intercept;
	while (
		next.x >= 0 &&
		next.x <= WIDTH / 2 &&
		next.y >= 0 &&
		next.y <= HEIGHT
	)
	{
		if (has_wall_at(
				game,
				next.x - (ray->left ? 1 : 0),
				next.y
			))
		{
			ray->verthit = 1;
			ray->vertwallhit = next;
			break ;
		}
		else
		{
			next.x += ray->step.x;
			next.y += ray->step.y;
		}
	}
}

void	cast_ray_horz(t_cub3d *game, t_ray *ray, t_vec p)
{
	t_vec	next;

	ray->intercept.y = floor(p.y / TILE_SIZE) * TILE_SIZE;
	ray->intercept.y += ray->down ? TILE_SIZE : 0;

	ray->intercept.x = p.x + (ray->intercept.y - p.y) / tan(ray->angle);
	ray->step.y = ray->up ? -TILE_SIZE : TILE_SIZE;
	ray->step.x = TILE_SIZE / tan(ray->angle);
	ray->step.x *= ray->left && ray->step.x > 0 ? -1 : 1;
	ray->step.x *= ray->right && ray->step.x < 0 ? -1 : 1;
	next = ray->intercept;
	while (
		next.x >= 0 &&
		next.x <= WIDTH / 2 &&
		next.y >= 0 &&
		next.y <= HEIGHT
	)
	{
		if (has_wall_at(
				game,
				next.x,
				next.y - (ray->up ? 1 : 0)
			))
		{
			ray->horzhit = 1;
			ray->horzwallhit = next;
			break ;
		}
		else
		{
			next.x += ray->step.x;
			next.y += ray->step.y;
		}
	}
}

double	distance_point(t_vec a, t_vec b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	cast_all_rays(t_cub3d *game)
{
	int		i;
	float	ray_angle;
	t_vec	player;
	t_ray	*ray;

	player = game->player.vec;
	ray_angle = game->player.rotate_angle - FOV_ANGLE / 2;
	i = 0;
	while (i < 512)
	{
		ray = setup_ray(&game->rays[i++], ray_angle);
		cast_ray_vert(game, ray, player);
		cast_ray_horz(game, ray, player);
		ray->vertDistance = ray->verthit ? \
			distance_point(player, ray->vertwallhit) : __INT_MAX__;
		ray->horzDistance = ray->horzhit ? \
			distance_point(player, ray->horzwallhit) : __INT_MAX__;
		ray->wallhit = ray->vertDistance > ray->horzDistance ? \
						ray->horzwallhit : ray->vertwallhit;
		stroke_rgba(255, 0, 0, 0.1);
		line(&game->img, player, ray->wallhit);
		ray_angle += FOV_ANGLE / 512;
	}
}

void	update(t_cub3d *game)
{
	update_player(game);
	cast_all_rays(game);
}

int 	draw(t_cub3d *game)
{
	init_img(game);
	update(game);

	render_map_2d(game);
	render_player_2d(game);
	// draw_map_ray(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	mlx_do_sync(game->mlx);
	return (0);
}

int		handle_key_pressd(int keycode, t_cub3d *game)
{
	game->key[keycode / 64] |= (1 << (keycode % 64));
	return (0);
}

int		handle_key_released(int keycode, t_cub3d *game)
{
	game->key[keycode / 64] &= ~(1 << (keycode % 64));
	return (0);
}

int		check_key_press(int keycode, t_ll *key)
{
	if (key[keycode / 64] & 1 << (keycode % 64))
		return (1);
	return (0);
}

int		main(void)
{
	t_cub3d game;

	init(&game, WIDTH, HEIGHT, CUB3D_TITLE);
	mlx_hook(game.win, X_KEY_PRESS, X_KEY_PRESS_MASK, handle_key_pressd, &game);
	mlx_hook(game.win, X_KEY_RELEASE, X_KEY_RELEASE_MASK, handle_key_released,&game);
	// mlx_hook(game.win, X_DESTROY_NOTIFY,
	// 		 X_SUB_STRUCTURE_NOTIFY_MASK, handle_exit_window, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (0);
}
