/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:52:21 by hchadili          #+#    #+#             */
/*   Updated: 2025/04/08 20:39:09 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
void	ft_display_error(char *s, map_context_h *map)
{
	ft_free_map(map);
	printf("%s\n", s);
	exit(1);
}
