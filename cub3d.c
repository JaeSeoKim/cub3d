/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeskim <jaeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:50:30 by jaeskim           #+#    #+#             */
/*   Updated: 2021/01/19 15:15:08 by jaeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define SCALE 0.1
# define mapWidth 24
# define mapHeight 24

int	worldMap[mapWidth * mapHeight] = {
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7,
	4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7,
	4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1,
	4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8,
	4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1,
	4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8,
	4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1,
	4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
	6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2,
	4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2,
	4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2,
	4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2,
	4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3};

t_vec	new_vec(float x, float y)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	return (result);
}

int		load_texture(t_cub3d *g, t_img *img, char *path)
{
	if (!(img->ptr = \
		mlx_png_file_to_image(g->mlx, path, &img->width, &img->height)))
		return (ERROR);
	img->data = (t_color *)mlx_get_data_addr(\
		img->ptr, &img->bpp, &img->size_l, &img->endian);
	img->line = img->size_l / (img->bpp / 8);
	return (SUCCES);
}

/*
** TODO: fix init_texture
*/

void	init_texture(t_cub3d *g)
{
	if (!(g->texture = malloc(sizeof(t_img) * 8)))
	{
		free(g->rays);
		mlx_destroy_image(g->mlx, g->img.ptr);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		exit(ERROR);
	}
	load_texture(g, &g->texture[0], "./img/coal_ore.png");
	load_texture(g, &g->texture[1], "./img/cobblestone.png");
	load_texture(g, &g->texture[2], "./img/diamond_ore.png");
	load_texture(g, &g->texture[3], "./img/dirt.png");
	load_texture(g, &g->texture[4], "./img/emerald_ore.png");
	load_texture(g, &g->texture[5], "./img/gold_ore.png");
	load_texture(g, &g->texture[6], "./img/green_concrete_powder.png");
	load_texture(g, &g->texture[7], "./img/oxeye_daisy.png");
}

void	init_key(t_key *key)
{
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->up = 0;
	key->down = 0;
	key->left = 0;
	key->right = 0;
}

void	init_player(t_player *player, int x, int y)
{
	player->pos.x = x;
	player->pos.y = y;
	player->move_s = 5.0;
	player->rotate_s = 2 * (M_PI / 180);
	player->angle = 270 * (M_PI / 180);
	player->turn_d = 0;
	player->walk_d = 0;
}

void	init_map(t_cub3d *g)
{
	g->map.x = mapWidth;
	g->map.y = mapHeight;
	g->map.data = (int *)worldMap;
}

void	init_rays(t_cub3d *g)
{
	g->num_rays = (g->img.width) / WALL_STRIP_WIDTH;

	if (!(g->rays = malloc(sizeof(t_ray) * g->num_rays)))
	{
		mlx_destroy_image(g->mlx, g->img.ptr);
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		exit(ERROR);
	}
}

void	init_connect(t_cub3d *g, int width, int height, char *title)
{
	if (!(g->mlx = mlx_init()))
		exit(ERROR);
	if (!(g->win = mlx_new_window(g->mlx, width, height, title)))
	{
		mlx_destroy_display(g->mlx);
		exit(ERROR);
	}
}

void	init_img(t_cub3d *g, int width, int height)
{
	g->img.width = width;
	g->img.height = height;
	if (!(g->img.ptr = mlx_new_image(g->mlx, width, height)))
	{
		mlx_destroy_window(g->mlx, g->win);
		mlx_destroy_display(g->mlx);
		exit(ERROR);
	}
	g->img.data = (t_color *)mlx_get_data_addr(
		g->img.ptr, &g->img.bpp, &g->img.size_l, &g->img.endian);
	g->img.line = g->img.size_l / (g->img.bpp / 8);
}

void	init(t_cub3d *g, int width, int height, char *title)
{
	init_connect(g, width, height, title);
	init_img(g, width, height);
	g->fov = 66 * (M_PI / 180);
	init_player(&g->p, width / 3, height / 2);
	init_key(&g->key);
	init_rays(g);
	init_map(g);
	init_texture(g);
}

int		has_wall_at(t_cub3d *g, int x, int y)
{
	if (x < 0 || y < 0 || x / TILE_SIZE > g->map.x || y / TILE_SIZE > g->map.y)
		return (1);
	return (g->map.data[y / TILE_SIZE * g->map.y + x / TILE_SIZE]);
}

float	normal_angle(float angle)
{
	if ((angle = fmodf(angle, M_2PI)) < 0)
		angle += M_2PI;
	return (angle);
}

t_ray	*init_ray(t_ray *ray, float ray_angle)
{
	ray->angle = normal_angle(ray_angle);
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

float	distance_point(t_vec a, t_vec b)
{
	return (sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

void	cast_ray_vert(t_cub3d *g, t_ray *ray, t_vec p)
{
	t_vec	n;

	ray->intercept.x = floor(p.x / TILE_SIZE) * TILE_SIZE;
	ray->intercept.x += ray->right ? TILE_SIZE : 0;
	ray->intercept.y = p.y + (ray->intercept.x - p.x) * tan(ray->angle);
	ray->step.x = ray->left ? -TILE_SIZE : TILE_SIZE;
	ray->step.y = TILE_SIZE * tan(ray->angle);
	ray->step.y *= ray->up && ray->step.y > 0 ? -1 : 1;
	ray->step.y *= ray->down && ray->step.y < 0 ? -1 : 1;
	n = ray->intercept;
	while (n.x >= 0 && n.x <= g->map.x * TILE_SIZE \
		&& n.y >= 0 && n.y <= g->map.y * TILE_SIZE)
	{
		if ((ray->verthit = has_wall_at(g, n.x - (ray->left ? 1 : 0), n.y)))
		{
			ray->vertwallhit = n;
			break ;
		}
		else
		{
			n.x += ray->step.x;
			n.y += ray->step.y;
		}
	}
}

void	cast_ray_horz(t_cub3d *g, t_ray *ray, t_vec p)
{
	t_vec	n;

	ray->intercept.y = floor(p.y / TILE_SIZE) * TILE_SIZE;
	ray->intercept.y += ray->down ? TILE_SIZE : 0;
	ray->intercept.x = p.x + (ray->intercept.y - p.y) / tan(ray->angle);
	ray->step.y = ray->up ? -TILE_SIZE : TILE_SIZE;
	ray->step.x = TILE_SIZE / tan(ray->angle);
	ray->step.x *= ray->left && ray->step.x > 0 ? -1 : 1;
	ray->step.x *= ray->right && ray->step.x < 0 ? -1 : 1;
	n = ray->intercept;
	while (n.x >= 0 && n.x <= g->map.x * TILE_SIZE \
		&& n.y >= 0 && n.y <= g->map.y * TILE_SIZE)
	{
		if ((ray->horzhit = has_wall_at(g, n.x, n.y - (ray->up ? 1 : 0))))
		{
			ray->horzwallhit = n;
			break ;
		}
		else
		{
			n.x += ray->step.x;
			n.y += ray->step.y;
		}
	}
}

void	cast_all_rays(t_cub3d *g)
{
	int		i;
	float	ray_angle;
	t_ray	*ray;

	ray_angle = g->p.angle - g->fov / 2;
	i = 0;
	while (i < g->num_rays)
	{
		ray = init_ray(&g->rays[i++], ray_angle);
		cast_ray_vert(g, ray, g->p.pos);
		cast_ray_horz(g, ray, g->p.pos);
		ray->vert_d = ray->verthit ? \
			distance_point(g->p.pos, ray->vertwallhit) : __INT_MAX__;
		ray->horz_d = ray->horzhit ? \
			distance_point(g->p.pos, ray->horzwallhit) : __INT_MAX__;
		ray->wallhit = ray->vert_d > ray->horz_d ? \
						ray->horzwallhit : ray->vertwallhit;
		ray->distance = ray->vert_d > ray->horz_d ? \
						ray->horz_d : ray->vert_d;
		ray->was_vertical = ray->vert_d > ray->horz_d ? 0 : 1;
		ray_angle += g->fov / g->num_rays;
	}
}

void	update_player(t_cub3d *g)
{
	t_vec		pos[2];
	float		step[2];

	g->p.turn_d = g->key.a ? -1 : 0;
	g->p.turn_d += g->key.d ? 1 : 0;
	g->p.walk_d = g->key.w ? 1 : 0;
	g->p.walk_d += g->key.s ? -1 : 0;
	g->p.angle = normal_angle(g->p.angle + g->p.turn_d * g->p.rotate_s);
	step[0] = g->p.walk_d * g->p.move_s;
	step[1] = g->p.walk_d * TILE_SIZE / 2;
	pos[0].x = g->p.pos.x + cos(g->p.angle) * step[0];
	pos[0].y = g->p.pos.y + sin(g->p.angle) * step[0];
	pos[1].x = g->p.pos.x + cos(g->p.angle) * step[1];
	pos[1].y = g->p.pos.y + sin(g->p.angle) * step[1];

	if (!has_wall_at(g, pos[0].x, pos[0].y) && \
		!has_wall_at(g, pos[1].x, pos[1].y))
		g->p.pos = pos[0];
}

void	update(t_cub3d *g)
{
	update_player(g);
	cast_all_rays(g);
}

void	render_ceiling(t_cub3d *g)
{
	t_vec	pos;

	pos = new_vec(0, 0);
	no_stroke();
	fill_rgba(80, 188, 233, 1);
	rect(&g->img, pos, g->img.width, g->img.height / 2);
}

void	render_floor(t_cub3d *g)
{
	t_vec	pos;

	pos = new_vec(0, g->img.height / 2);
	no_stroke();
	fill_rgba(252, 206, 177, 1);
	rect(&g->img, pos, g->img.width, g->img.height / 2);
}

void	render_2dmap(t_cub3d *g)
{
	int		i;
	t_vec	vec;
	t_img	*img;

	img = &g->img;
	vec = new_vec(0, 0);
	fill_rgba(50, 50, 50, 1);
	rect(&g->img, vec, SCALE * g->map.x * TILE_SIZE, \
						SCALE * g->map.y * TILE_SIZE);
	stroke_rgba(255, 255, 255, 1);
	fill_rgba(0, 0, 0, 1);
	i = 0;
	while (i < g->map.x * g->map.y)
	{
		if (g->map.data[i] > 0)
		{
			vec.x = SCALE * ((i % g->map.x) * TILE_SIZE);
			vec.y = SCALE * ((i / g->map.x) * TILE_SIZE);
			rect(&g->img, vec, SCALE * TILE_SIZE, SCALE * TILE_SIZE);
		}
		++i;
	}
}

void	render_2dmap_player(t_cub3d *g)
{
	int		i;

	no_stroke();
	fill_rgba(255, 255, 0, 1);
	mid_point_rect(&g->img, \
		new_vec(SCALE * g->p.pos.x, SCALE * g->p.pos.y), 2, 2);

	stroke_rgba(255, 0, 0, 0.1);
	i = -1;
	while (++i < g->num_rays)
		line(&g->img, new_vec(SCALE * g->p.pos.x, SCALE * g->p.pos.y), \
			new_vec(SCALE * g->rays[i].wallhit.x,\
			SCALE * g->rays[i].wallhit.y));

	stroke_rgba(0, 255, 0, 1);
	line(&g->img, \
		new_vec(SCALE * g->p.pos.x, SCALE * g->p.pos.y), \
		new_vec(SCALE * (g->p.pos.x + cos(g->p.angle) * 30),\
			SCALE * (g->p.pos.y + sin(g->p.angle) * 30)));
}

void	render_3d_wall(t_cub3d *g)
{
	int		i;
	t_vec	position;
	float	wall_dist;
	float	distanceProjPlane;
	float	wallStripHeight;

	no_stroke();
	i = -1;
	while (++i < g->num_rays)
	{
		wall_dist = g->rays[i].distance * cos(g->p.angle - g->rays[i].angle);
		distanceProjPlane = g->img.width / 2 / tan(g->fov / 2);
		wallStripHeight = TILE_SIZE * distanceProjPlane / wall_dist;
		position.x = i * WALL_STRIP_WIDTH;
		position.y = g->img.height / 2 - wallStripHeight / 2;
		if (position.x < 0)
			position.x = 0;
		else if (position.x > g->img.width)
			position.x = g->img.width - 1;
		if (position.y < 0)
			position.y = 0;
		else if (position.y > g->img.height)
			position.y = g->img.height - 1;
		int index;
		if (g->rays[i].was_vertical)
			index  = g->rays[i].left ? 3 : 4;
		else
			index  = g->rays[i].up ? 1 : 2;
		int x = g->rays[i].was_vertical ? \
			(int)g->rays[i].wallhit.y % TILE_SIZE * g->texture[index].width / TILE_SIZE  : \
			(int)g->rays[i].wallhit.x % TILE_SIZE * g->texture[index].width / TILE_SIZE;
		int	j = -1;
		while (++j < wallStripHeight && position.y < g->img.height)
		{
			int texY = ((position.y) - (g->img.height / 2 - wallStripHeight / 2))
				/ wallStripHeight * g->texture[index].height;
			g_color = g->texture[index].data[texY * g->texture[index].line + x];
			put_pixel(&g->img, position.x, position.y++);
		}
	}
}

void	render(t_cub3d *g)
{
	render_floor(g);
	render_ceiling(g);
	render_3d_wall(g);
	render_2dmap(g);
	render_2dmap_player(g);
}

int		draw(t_cub3d *g)
{
	update(g);
	render(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.ptr, 0, 0);
	mlx_do_sync(g->mlx);
	return (0);
}

int		handle_exit_window(t_cub3d *g)
{
	free(g->rays);
	mlx_destroy_image(g->mlx, g->img.ptr);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	exit(SUCCES);
}

int		handle_key_pressed(int keycode, t_cub3d *g)
{
	(keycode == KEY_W ? g->key.w = 1 : 0);
	(keycode == KEY_A ? g->key.a = 1 : 0);
	(keycode == KEY_S ? g->key.s = 1 : 0);
	(keycode == KEY_D ? g->key.d = 1 : 0);
	(keycode == KEY_UP ? g->key.up = 1 : 0);
	(keycode == KEY_DOWN ? g->key.down = 1 : 0);
	(keycode == KEY_LEFT ? g->key.left = 1 : 0);
	(keycode == KEY_DOWN ? g->key.down = 1 : 0);
	if (keycode == KEY_ESC)
		handle_exit_window(g);
	return (0);
}

int		handle_key_released(int keycode, t_cub3d *g)
{
	(keycode == KEY_W ? g->key.w = 0 : 0);
	(keycode == KEY_A ? g->key.a = 0 : 0);
	(keycode == KEY_S ? g->key.s = 0 : 0);
	(keycode == KEY_D ? g->key.d = 0 : 0);
	(keycode == KEY_UP ? g->key.up = 0 : 0);
	(keycode == KEY_DOWN ? g->key.down = 0 : 0);
	(keycode == KEY_LEFT ? g->key.left = 0 : 0);
	(keycode == KEY_DOWN ? g->key.down = 0 : 0);
	if (keycode == KEY_ESC)
		handle_exit_window(g);
	return (0);
}

int		main(void)
{
	t_cub3d		g;

	init(&g, 1280, 720, CUB3D_TITLE);
	mlx_hook(g.win, X_KEY_PRESS, X_KEY_PRESS_MASK, handle_key_pressed, &g);
	mlx_hook(g.win, X_KEY_RELEASE, X_KEY_RELEASE_MASK, handle_key_released, &g);
	mlx_hook(g.win, X_DESTROY_NOTIFY,
			X_SUB_STRUCTURE_NOTIFY_MASK, handle_exit_window, &g);
	mlx_loop_hook(g.mlx, draw, &g);
	mlx_loop(g.mlx);
	return (0);
}
