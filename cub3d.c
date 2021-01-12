/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:50:30 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/12 12:52:49 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

#define TILE_SIZE 64
#define MAP_SCALE 0.3

const float FOV_ANGLE = 60 * (M_PI / 180);

int		check_key_press(int keycode, t_ll *key);

int mapx = 8, mapy = 8;
int map[] = {
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
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
	int		index;

	if (x < 0 || y < 0 || x > game->width || y > game->height)
		return (1);
	index = (int)(y / TILE_SIZE) * mapx + (int)(x / TILE_SIZE);
	return (map[index] == 1 ? 1 : 0);
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
	game->width = width;
	game->height = height;

	img->ptr = mlx_new_image(game->mlx, width, height);
	img->data = (t_ui *)mlx_get_data_addr(
		game->img.ptr, &img->bpp, &img->size_l, &img->endian);
	img->line = img->size_l / (img->bpp / 8);

	game->player.vec.x = width / 3;
	game->player.vec.y = height / 4;
	game->player.move_speed = 3.0;
	game->player.rotate_speed = 3 * (M_PI / 180);
	game->player.angle = 45 * (M_PI / 180);
	game->player.turn_direct = 0;
	game->player.walk_direct = 0;

	game->wall_strip_width = 4;
	game->num_rays = (width) / game->wall_strip_width;
	game->fov_angle = 60 * (M_PI / 180);

	if (!(game->rays = malloc(sizeof(t_ray) * game->num_rays)))
		exit(1);

	i = 0;
	while (i < 6)
		game->key[i++] = 0;
}

int		init_img(t_cub3d *game)
{
	int		length;
	int		i;

	i = 0;
	length = game->img.line * game->height;
	while (i < length)
		game->img.data[i++] = 0x00000000;
	return (0);
}

int		render_map_2d(t_cub3d *game)
{
	t_vec	vec;
	t_ui	*data;

	data = game->img.data;

	vec.x = 0;
	vec.y = 0;
	fill_rgba(50, 50, 50, 1);
	rect(&game->img, vec, MAP_SCALE * game->width, MAP_SCALE * game->height);
	stroke_rgba(255, 255, 255, 1);
	fill_rgba(0, 0, 0, 1);
	for (int i = 0; i < TILE_SIZE; i++)
	{
		if (map[i])
		{
			vec.y = MAP_SCALE * ((i / 8) * TILE_SIZE);
			vec.x = MAP_SCALE * ((i % 8) * TILE_SIZE);
			rect(&game->img, vec, MAP_SCALE * TILE_SIZE, MAP_SCALE * TILE_SIZE);
		}
	}
	return (0);
}

int		render_player_2d(t_cub3d *game)
{
	int		i;
	t_ui	*data;
	t_vec	player;
	t_vec	target;

	data = game->img.data;

	no_stroke();
	fill_rgba(255, 255, 0, 1);
	player.x = MAP_SCALE * game->player.vec.x;
	player.y = MAP_SCALE * game->player.vec.y;
	mid_point_rect(&game->img, player, MAP_SCALE * 10, MAP_SCALE * 10);

	i = 0;
	stroke_rgba(255, 0, 0, 1);
	while (i < game->num_rays)
	{
		target.x = game->rays[i].wallhit.x * MAP_SCALE;
		target.y = game->rays[i].wallhit.y * MAP_SCALE;
		line(&game->img, player, target);
		++i;
	}

	target.x = MAP_SCALE * (game->player.vec.x + cos(game->player.angle) * 20);
	target.y = MAP_SCALE * (game->player.vec.y + sin(game->player.angle) * 20);
	stroke_rgba(0, 255, 0, 1);
	line(&game->img, player, target);
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
	game->player.angle =
		normalize_angle(game->player.angle + \
						game->player.turn_direct * game->player.rotate_speed);
	move_step = game->player.walk_direct * game->player.move_speed;
	new_vec.x = game->player.vec.x + cos(game->player.angle) * move_step;
	new_vec.y = game->player.vec.y + sin(game->player.angle) * move_step;
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
		next.x <= game->width &&
		next.y >= 0 &&
		next.y <= game->height
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
		next.x <= game->width &&
		next.y >= 0 &&
		next.y <= game->height
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
	t_ray	*ray;

	ray_angle = game->player.angle - game->fov_angle / 2;
	i = 0;
	while (i < game->num_rays)
	{
		ray = setup_ray(&game->rays[i++], ray_angle);
		cast_ray_vert(game, ray, game->player.vec);
		cast_ray_horz(game, ray, game->player.vec);
		ray->vertDistance = ray->verthit ? \
			distance_point(game->player.vec, ray->vertwallhit) : __INT_MAX__;
		ray->horzDistance = ray->horzhit ? \
			distance_point(game->player.vec, ray->horzwallhit) : __INT_MAX__;
		ray->wallhit = ray->vertDistance > ray->horzDistance ? \
						ray->horzwallhit : ray->vertwallhit;
		ray->distance = ray->vertDistance > ray->horzDistance ? \
						ray->horzDistance : ray->vertDistance;
		ray_angle += game->fov_angle / game->num_rays;
	}
}

void	update(t_cub3d *game)
{
	update_player(game);
	cast_all_rays(game);
}

void	draw_map_ray(t_cub3d *game)
{
	int		i;
	t_vec	position;
	t_ray	ray;
	float	wall_dist;
	float	distanceProjPlane;
	float	wallStripHeight;
	t_vec	vec;

	no_stroke();
	fill_rgba(80, 188, 233, 1);
	vec.x = 0;
	vec.y = 0;
	rect(&game->img, vec, game->width, game->height / 2);
	fill_rgba(252, 206, 177, 1);
	vec.x = 0;
	vec.y = game->height / 2;
	rect(&game->img, vec, game->width, game->height / 2);

	// no_stroke();
	stroke_rgba(0, 255, 0, 1);
	i = 0;
	while (i < game->num_rays)
	{
		ray = game->rays[i];
		wall_dist = ray.distance * cos(game->player.angle - ray.angle);
		distanceProjPlane = game->width / 2 / tan(game->fov_angle / 2);
		wallStripHeight = (TILE_SIZE / wall_dist) * distanceProjPlane;
		float alpha = 200 / wall_dist;
		(alpha > 1.0 ? alpha = 1 : 0);
		position.x = i++ * game->wall_strip_width;
		position.y = game->height / 2 - wallStripHeight / 2;
		fill_rgba(255, 255, 255, alpha);
		g_fill = calc_rgba(0x000000, g_fill);
		rect(&game->img, position, game->wall_strip_width, wallStripHeight);
	}
}

int		draw(t_cub3d *game)
{
	init_img(game);

	update(game);

	draw_map_ray(game);
	render_map_2d(game);
	render_player_2d(game);
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

	init(&game, TILE_SIZE * mapx, TILE_SIZE * mapy, CUB3D_TITLE);
	mlx_hook(game.win, X_KEY_PRESS, X_KEY_PRESS_MASK, handle_key_pressd, &game);
	mlx_hook(game.win, X_KEY_RELEASE, X_KEY_RELEASE_MASK, handle_key_released,&game);
	// mlx_hook(game.win, X_DESTROY_NOTIFY,
	// 		 X_SUB_STRUCTURE_NOTIFY_MASK, handle_exit_window, &game);
	mlx_loop_hook(game.mlx, draw, &game);
	mlx_loop(game.mlx);
	return (0);
}
