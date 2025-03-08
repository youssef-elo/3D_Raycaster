#include "cub3d.h"

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	index;

	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
	{
		index = (y * img->width + x) * 4;
		img->pixels[index + 0] = (color >> 24) & 0xFF;
		img->pixels[index + 1] = (color >> 16) & 0xFF;
		img->pixels[index + 2] = (color >> 8) & 0xFF;
		img->pixels[index + 3] = (color) & 0xFF;
	}
}

void	draw_filled_disk(mlx_image_t *img, int xc, int yc, int r)
{
	int			y;
	int			x;
	uint32_t	color;
	int			y_max;

	x = xc - r;
	color = rgb(255, 0, 0, 255);
	while (x <= xc + r)
	{
		y_max = sqrt(r * r - (x - xc) * (x - xc));
		y = yc - y_max;
		while (y <= yc + y_max)
		{
			put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

uint32_t	rgb(int r, int g, int b, int a)
{
	return (((r & 0xFF) << 24) | ((g & 0xFF) << 16)
		| ((b & 0xFF) << 8) | (a & 0xFF));
}

// REMOVE LATER
void	draw_line_2(mlx_image_t *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		put_pixel(img, x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}